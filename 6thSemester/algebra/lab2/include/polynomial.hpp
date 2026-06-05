#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include "order.hpp"

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
bool mono_divisible(const std::array<int, N>& a, const std::array<int, N>& b) {
    for (size_t i{ 0 }; i < N; ++i) {
        if (b[i] > a[i]) return false;
    }

    return true;
}

template <size_t N>
std::array<int, N> mono_divide(const std::array<int, N>& a, const std::array<int, N>& b) {
    std::array<int, N> r{};
    for (size_t i{ 0 }; i < N; ++i) {
        r[i] = a[i] - b[i];
    }

    return r;
}

template <typename T, size_t N>
class Polynomial {
public:
    std::vector<std::array<int, N>> exponents{};
    std::map<std::array<int, N>, T> coeffs{};
    std::array<size_t, N> perm{};
    Compare (*comp)(std::array<int, N>, std::array<int, N>, std::array<size_t, N>);

    Polynomial() = default;

    Polynomial(
        const std::vector<std::pair<std::array<int, N>, T>>& coeffs, 
        const std::array<size_t, N>& permutation,
        Compare (*comparisonFunction)(std::array<int, N>, std::array<int, N>, std::array<size_t, N>)
    ) : perm{ permutation }, comp{ comparisonFunction } {
        for (std::pair<std::array<int, N>, T> p : coeffs) insertMonomial(p.first, p.second);
    }
    
    int norm() const { return degree; }

    std::array<int, N> LT() const { return exponents.back(); } 

    T LC() const { return coeffs.at(exponents.back()); }

    friend Polynomial<T, N> operator-(Polynomial<T, N>& p) {
        for (auto& pair : p.coeffs) {
            pair.second = -pair.second;
        }

        return p;
    }

    friend Polynomial<T, N> operator-(const Polynomial<T, N>& p) {
        Polynomial<T, N> res{ p };

        for (const auto& pair : res.coeffs) {
            res.coeffs[pair.first] = -pair.second;
        }

        return res;
    }

    friend Polynomial<T, N> operator+(const Polynomial<T, N>& p, const Polynomial<T, N>& q) {
        Polynomial<T, N> res{ p };

        auto& qe = q.exponents;
        auto& qc = q.coeffs;
        auto& re = res.exponents;
        auto& rc = res.coeffs;
        
        size_t i{ 0 };


        for (const auto& exp : qe) {
            if (std::abs(qc.at(exp)) < 1e-15) continue;
            
            while (i < re.size() && (res.comp(re[i], exp, res.perm) == Compare::Less)) ++i;
            if (i == re.size() || re[i] != exp) {
                re.insert(re.begin() + static_cast<long>(i), exp);
                rc[exp] = qc.at(exp);
            } else {
                rc[exp] += qc.at(exp);
            }

            if (std::abs(rc[exp]) < 1e-15) {
                re.erase(re.begin() + static_cast<long>(i));
                rc.erase(exp);
            }
        }

        if (re.size() > 0) {
            res.degree = std::accumulate(re.back().begin(), re.back().end(), 0);
        } else {
            res.degree = -1;
        }

        return res;
    }

    friend Polynomial<T, N> operator-(const Polynomial<T, N>& p, const Polynomial<T, N>& q) {
        return p + (-q);
    }

    friend Polynomial<T, N> operator*(const Polynomial<T, N>& p, const Polynomial<T, N>& q) {
        Polynomial<T, N> res{};
        res.perm = p.perm;
        res.comp = p.comp;

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
                while (j < re.size() && p.comp(newe, re[j], p.perm) == Compare::Less) ++j;
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

private:
    int degree{ -1 };

    void insertMonomial(std::array<int, N> exp, T v) {
        if (std::abs(v) < 1e-15) return;

        size_t j = 0;
        int newDegree = std::accumulate(exp.begin(), exp.end(), 0);
        while (j < exponents.size() && comp(exponents[j], exp, perm) == Compare::Less) ++j;

        if (newDegree > degree) degree = newDegree;

        exponents.insert(exponents.begin() + static_cast<long>(j), exp);
        coeffs.emplace(exp, v);
    }
};

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const Polynomial<T, N>& p) {
    for (const auto& mono : p.exponents) {
        out << p.coeffs.at(mono) << " * " << mono;
        if (mono != p.exponents.back()) {
            out << " + ";
        }
    }

    if (p.exponents.size() == 0) {
        out << "0";
    }

    return out;
}

#endif // POLYNOMIAL_HPP