#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

template <size_t N>
std::array<int, N> operator+(const std::array<int, N>& a, const std::array<int, N>& b) {
    std::array<int, N> res{};
    
    for (size_t j = 0; j < N; ++j) {
        res[j] = a[j] + b[j];
    }

    return res;
}

template <size_t N>
bool compareMonomial(const std::array<int, N>& a, const std::array<int, N>& b) {
    int dega = std::accumulate(a.begin(), a.end(), 0);
    int degb = std::accumulate(b.begin(), b.end(), 0);

    return (dega == degb) ? (a > b) : (dega > degb);
}

template <typename T, size_t N>
class Polynomial {
public:
    std::vector<std::array<int, N>> exponents{};
    std::map<std::array<int, N>, T> coeffs{};

    Polynomial() = default;

    Polynomial(std::vector<std::pair<std::array<int, N>, T>> coeffs) {
        for (std::pair<std::array<int, N>, T> p : coeffs) insertMonomial(p.first, p.second);
    }
    
    int norm() const { return degree; }

    friend Polynomial<T, N> operator-(Polynomial<T, N> p) {
        for (auto& pair : p.coeffs) {
            pair.second = -pair.second;
        }

        return p;
    }

    friend Polynomial<T, N> operator+(Polynomial<T, N> p, const Polynomial<T, N>& q) {
        auto& pe = p.exponents;
        auto& pc = p.coeffs;
        
        for (auto exp : q.exponents) {
            if (std::abs(q.coeffs.at(exp)) < 1e-15) continue;
            
            size_t j = 0;
            while (j < pe.size() && compareMonomial(exp, pe[j])) ++j;
            if (j == pe.size() || pe[j] != exp) {
                pe.insert(pe.begin() + static_cast<long>(j), exp);
                pc[exp] = q.coeffs.at(exp);
            } else {
                pc[exp] += q.coeffs.at(exp);
            }

            if (std::abs(pc[exp]) < 1e-15) {
                pe.erase(pe.begin() + static_cast<long>(j));
                pc.erase(exp);
            }
        }

        if (pe.size() > 0) {
            p.degree = std::accumulate(pe.back().begin(), pe.back().end(), 0);
        } else {
            p.degree = -1;
        }

        return p;
    }

    friend Polynomial<T, N> operator*(const Polynomial<T, N>& p, const Polynomial<T, N>& q) {
        Polynomial<T, N> res{};

        auto& pe = p.exponents;
        auto& pc = p.coeffs;
        auto& qe = q.exponents;
        auto& qc = q.coeffs;
        auto& re = res.exponents;
        auto& rc = res.coeffs;

        for (auto e1 : pe) {
            for (auto e2 : qe) {
                auto newe = e1 + e2;
                size_t j = 0;
                while (j < re.size() && compareMonomial(newe, re[j])) ++j;
                if (j < re.size() && re[j] == newe) {
                    rc[newe] += pc.at(e1) * qc.at(e2);
                } else {
                    re.insert(re.begin() + static_cast<long>(j), newe);
                    rc[newe] = pc.at(e1) * qc.at(e2);

                    int deg = std::accumulate(newe.begin(), newe.end(), 0);
                    if (deg > res.degree) res.degree = deg;
                }
            }
        }

        return res;
    }


    friend std::pair<Polynomial<T, 1>, Polynomial<T,1>> operator/(const Polynomial<T, 1>& p1, const Polynomial<T, 1>& p2) {
        Polynomial<T, 1> q{};
        Polynomial<T, 1> r{ p1 };
        auto& pe = p2.exponents;
        auto& pc = p2.coeffs;
        auto& re = r.exponents;
        auto& rc = r.coeffs;
        auto& qe = q.exponents;
        auto& qc = q.coeffs;

        while (r.norm() >= p2.norm()) {
            Polynomial<T, 1> c{{{{r.norm() - p2.norm()}, rc[re.back()] / pc.at(pe.back())}}};
            q = q + c;
            r = r + (-p2 * c);
        }

        size_t j = 0;
        while (j < qe.size()) {
            if (std::abs(qc[qe[j]]) < 1e-15) {
                qc.erase(qe[j]);
                qe.erase(qe.begin() + static_cast<long>(j));
            } else {
                ++j;
            }
        }

        j = 0;
        while (j < re.size()) {
            if (std::abs(rc[re[j]]) < 1e-15) {
                rc.erase(re[j]);
                re.erase(re.begin() + static_cast<long>(j));
            } else {
                ++j;
            }
        }
        
        if (q.exponents.size() > 0) {
            auto biggest = q.exponents.back();
            q.degree = std::accumulate(biggest.begin(), biggest.end(), 0);
        } else {
            q.degree = -1;
        }

        
        if (re.size() > 0) {
            auto biggest = re.back();
            r.degree = std::accumulate(biggest.begin(), biggest.end(), 0);
        } else {
            r.degree = -1;
        }

        return {q, r};
    }

    friend std::ostream& operator<<(std::ostream& out, const Polynomial<T, 1ul>& p) {
        bool first = true;
        for (auto mono : p.coeffs) {
            if (std::abs(mono.second) < 1e-15) continue;

            if (!first) {
                if (mono.first[0] != 0 && std::abs(mono.second - 1) < 1e-15) out << " + ";
                else if (mono.first[0] != 0 && std::abs(mono.second + 1) < 1e-15) out << " - ";
                else if (mono.second > 1) out << " + " << mono.second;
                else out << " - " << -mono.second;
            } else {
                first = false;
                if (mono.first[0] != 0 && std::abs(mono.second + 1) < 1e-15) out << "-";
                else if (mono.first[0] == 0 || std::abs(mono.second - 1) > 1e-15) out << mono.second;
            }

            if (mono.first[0] == 1) out << "x";
            else if (mono.first[0] != 0) out << "x^"  << mono.first[0];
        }

        if (first) out << 0;

        return out;
    }
private:
    int degree{ -1 };

    void insertMonomial(std::array<int, N> exp, T v) {
        if (std::abs(v) < 1e-15) return;

        size_t j = 0;
        int newDegree = std::accumulate(exp.begin(), exp.end(), 0);
        while (j < exponents.size() && compareMonomial(exp, exponents[j])) ++j;

        if (newDegree > degree) degree = newDegree;

        exponents.insert(exponents.begin() + static_cast<long>(j), exp);
        coeffs.emplace(exp, v);
    }
};

template <typename T>
std::array<Polynomial<T, 1>, 3> gcd(const Polynomial<T, 1>& a, const Polynomial<T, 1>& b) {
    if (b.norm() == -1 || (b.norm() == 0 && b.coeffs.at(b.exponents.at(0)) < 1e-6)) 
        return { a, Polynomial<T, 1>{{{{0}, 1}}}, Polynomial<T, 1>{{}} };

    auto [q, r] = a / b;
    auto [d, x, y] = gcd(b, r);
    std::cout << "OUT: " << b << " " << r << " " << x << " " << y << "\n";
    return { d, y, x + (-q) * y };
}


#endif // POLYNOMIAL_HPP