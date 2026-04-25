#include "gauss.hpp"

#include <cmath>
#include <string>

namespace Gaussian {
    int norm(Gauss z) { return z.re * z.re + z.im * z.im; }
    
    std::vector<std::pair<Gauss, Gauss>> allDivisions(Gauss w, Gauss z) {
        if (z.re == 0 && z.im == 0) return std::vector<std::pair<Gauss, Gauss>>{};
    
        double denominator = static_cast<double>(z.im * z.im + z.re * z.re);
        double numberator_real = static_cast<double>(w.re * z.re + w.im * z.im);
        double numerator_imag = static_cast<double>(w.im * z.re - w.re * z.im);
        double real = numberator_real / denominator;
        double imag = numerator_imag / denominator;
        int rounded_real = static_cast<int>(std::lround(real));
        int rounded_imag = static_cast<int>(std::lround(imag));
    
        std::vector<std::pair<Gauss, Gauss>> ans{};
    
        Gauss solution{rounded_real, rounded_imag};
        Gauss remainder = w - z * solution;

        ans.push_back({solution, remainder});
    
        int z_norm = norm(z);
    
        int re_diff = (rounded_real > real) ? -1 : 1;
        int im_diff = (rounded_imag > imag) ? -1 : 1;
    
        solution += re_diff;
        remainder -= re_diff * z;
        if (norm(remainder) < z_norm) ans.push_back({solution, remainder});
    
        solution += im_diff * i;
        remainder -= im_diff * i * z;
        if (norm(remainder) < z_norm) ans.push_back({solution, remainder});
    
        solution -= re_diff;
        remainder += re_diff * z;
        if (norm(remainder) < z_norm) ans.push_back({solution, remainder});
    
        return ans;
    }

    std::vector<Gauss> gcd(Gauss w, Gauss z) {
        std::vector<Gauss> ans{};

        if (z == 0) {
            ans.push_back(Gauss{0, 0});
            return ans;
        }

        while (z != 0) {
            Gauss r = w % z;
            w = z;
            z = r;
        }

        ans.push_back(w);
        ans.push_back(w * i);
        ans.push_back(-w);
        ans.push_back(-w * i);

        return ans;
    }

    std::vector<Gauss> gcd(std::vector<Gauss> v) {
        std::vector<Gauss> ans{};
        if (v.size() == 0) {
            ans.push_back(Gauss{1, 0});
            ans.push_back(Gauss{0, 1});
            ans.push_back(Gauss{-1, 0});
            ans.push_back(Gauss{0, -1});
            return ans;
        }
        if (v.size() == 1) {
            ans.push_back(v[0]);
            ans.push_back(v[0] * i);
            ans.push_back(-v[0]);
            ans.push_back(-v[0] * i);
            return ans;
        }

        Gauss gcd_v = gcd(v[0], v[1])[0];

        for (size_t j = 2; j < v.size(); j++) gcd_v = gcd(gcd_v, v[j])[0];

        ans.push_back(gcd_v);
        ans.push_back(gcd_v * i);
        ans.push_back(-gcd_v);
        ans.push_back(-gcd_v * i);

        return ans;
    }

    std::vector<Gauss> lcm(Gauss w, Gauss z) {
        Gauss multiple = w * z;
        auto ans = gcd(w, z);

        ans[0] = multiple / ans[0];
        for (size_t j = 1; j < ans.size(); ++j) {
            ans[j] = ans[j - 1] * i;
        }

        return ans;
    }

    std::vector<Gauss> lcm(std::vector<Gauss> v) {
        std::vector<Gauss> ans = gcd(v);

        if (v.size() == 0 || v.size() == 1) {
            return ans;
        }

        Gauss multiple{1, 0};

        for (Gauss z : v) multiple *= z;

        ans[0] = multiple / ans[0];
        for (size_t j = 1; j < ans.size(); ++j) {
            ans[j] = ans[j - 1] * i;
        }

        return ans;
    }
}

Gauss& Gauss::operator=(int z) {
    re = z;
    im = 0;
    return *this;
}

Gauss operator-(Gauss z) { return Gauss{-z.re, -z.im}; }
Gauss operator+(Gauss z) { return z; }

Gauss operator+(Gauss w, Gauss z) { return Gauss{w.re + z.re, w.im + z.im}; }
Gauss operator-(Gauss w, Gauss z) { return Gauss{w.re - z.re, w.im - z.im}; }
Gauss operator*(Gauss w, Gauss z) { return Gauss{w.re * z.re - w.im * z.im, w.re * z.im + w.im * z.re}; }

Gauss operator/(Gauss w, Gauss z) {
    // (a + bi) / (c + di) = (ac + bd + i(bc - ad) ) / (c^2 - d^2)
    if (z.re == 0 && z.im == 0) return Gauss{0, 0};

    double denominator = static_cast<double>(z.im * z.im + z.re * z.re);
    double numberator_real = static_cast<double>(w.re * z.re + w.im * z.im);
    double numerator_imag = static_cast<double>(w.im * z.re - w.re * z.im);
    int real = static_cast<int>(std::lround(numberator_real / denominator));
    int imag = static_cast<int>(std::lround(numerator_imag / denominator));

    return Gauss{real, imag};
}

Gauss operator%(Gauss w, Gauss z) { return w - ((w / z) * z); }

Gauss operator+(int w, Gauss z) { return Gauss{w + z.re, z.im}; }
Gauss operator-(int w, Gauss z) { return Gauss{w - z.re, - z.im}; }
Gauss operator*(int w, Gauss z) { return Gauss{w * z.re, w * z.im}; }
Gauss operator/(int w, Gauss z) { return Gauss{w, 0} / z; }
Gauss operator%(int w, Gauss z) { return Gauss{w, 0} % z; }

Gauss operator+(Gauss w, int z) { return z + w; }
Gauss operator-(Gauss w, int z) { return w + (-z); }
Gauss operator*(Gauss w, int z) { return z * w; }
Gauss operator/(Gauss w, int z) { return w / Gauss{z, 0}; }
Gauss operator%(Gauss w, int z) { return w % Gauss{z, 0}; }

Gauss& operator+=(Gauss& w, Gauss z) { return w = w + z; }
Gauss& operator+=(Gauss& w, int z) { return w = w + z; }
Gauss& operator-=(Gauss& w, Gauss z) { return w = w - z; }
Gauss& operator-=(Gauss& w, int z) { return w = w - z; }
Gauss& operator*=(Gauss& w, Gauss z) { return w = w * z; }
Gauss& operator*=(Gauss& w, int z) { return w = w * z; }
Gauss& operator/=(Gauss& w, Gauss z) { return w = w / z; }
Gauss& operator/=(Gauss& w, int z) { return w = w / z; }
Gauss& operator%=(Gauss& w, Gauss z) { return w = w % z; }
Gauss& operator%=(Gauss& w, int z) { return w = w % z; }

bool operator==(Gauss w, int z) { return w.im == 0 && w.re == z; }
bool operator==(int w, Gauss z) { return z.im == 0 && w == z.re; }


std::ostream& operator<<(std::ostream& out, Gauss z) {
    std::string s{};

    if (z.re == 0) {
        if (z.im == 0) s += "0";
        else if (z.im == 1) s += "i";
        else if (z.im == -1) s += "-i";
        else s += std::to_string(z.im) + "i";
    } else {
        s += std::to_string(z.re);
        if (z.im == 1) s += "+i";
        else if (z.im == -1) s += "-i";
        else if (z.im > 1) s += "+" + std::to_string(z.im) + "i";
        else if (z.im < -1) s += std::to_string(z.im) + "i";
    }

    return out << s;
}

