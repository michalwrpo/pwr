#include "gauss.hpp"
#include "order.hpp"
#include "polynomial.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

int main() {
    int idx{};
    std::cout << "Input your student number: ";
    std::cin >> idx;

    int f = idx % 10;
    int e = (idx /= 10) % 10;
    int d = (idx /= 10) % 10;
    int c = (idx /= 10) % 10;
    int b = (idx /= 10) % 10;
    int a = (idx /= 10) % 10;

    std::cout << "====================\n     Exercise 1\n====================\n";

    {
        Gauss z = a + b * i;
        std::cout << "Norm(" << z << ") = " << Gaussian::norm(z) << "\n";
    }

    {
        Gauss w = (c + a) + (d + b) * i;
        Gauss z = e + f * i;

        auto solutions = Gaussian::allDivisions(w, z);

        std::cout << "Possible results of division of " << w << " by " << z << ":\n";

        for (size_t j = 0; j < solutions.size(); ++j) {
            std::cout << j + 1 << ") " 
                      << std::setw(5) << solutions[j].first 
                      << " remainder " 
                      << std::setw(5) << solutions[j].second 
                      << " (norm " << Gaussian::norm(solutions[j].second) << ")\n";
        }
    }  

    {
        Gauss v = a + b * i;
        Gauss w = c + d * i;
        Gauss z = e + d * i;
        
        auto gcds = Gaussian::gcd({v, w, z});

        std::cout << "gcd(" << v << ", " << w << ", " << z << ") = {";

        for (auto x : gcds) {
            std::cout << x << ", ";
        }

        std::cout << "\b\b}\n";

        auto lcms = Gaussian::lcm({v, w, z});

        std::cout << "lcm(" << v << ", " << w << ", " << z << ") = {";

        for (auto x : lcms) {
            std::cout << x << ", ";
        }

        std::cout << "\b\b}\n";

    }

    std::cout << "====================\n     Exercise 2\n====================\n";

    {
        Polynomial<double, 1> p{{{{a}, c}, {{0}, b}}};
        std::cout << "N(" << p << ") = " << p.norm() << "\n";
        
        Polynomial<double, 1> q{{{{1}, 1}, {{0}, 1}}};
        auto div = p / q;
        std::cout << "(" << p << ") / (" << q << ") = " << div.first << " remainder " << div.second << "\n"; 
    }

    {
        Polynomial<double, 1> p{{{{3}, a}, {{2}, b}, {{1}, c}, {{0}, d}}};
        Polynomial<double, 1> q{{{{3}, d}, {{2}, e}, {{1}, f}, }};
        auto r = gcd(p, q);
        std::cout << "(" << r[1] << ") * (" << p << ") + (" << r[2] << ") * (" << q << ") = " << r[0] << "\n";         
        // std::cout << r[1] * p + r[2] * q << "\n";
    }

    std::cout << "====================\n     Exercise 3\n====================\n";

    {
        std::array<int, 2> x{ a, b };
        std::array<int, 2> y{ c, d };
        std::array<int, 2> z{ e, f };

        std::cout << x << " compared to " << y << " is " << compare(x, y) << "\n";
        std::cout << x << " compared to " << z << " is " << compare(x, z) << "\n";
        std::cout << y << " compared to " << z << " is " << compare(y, z) << "\n";
    }

    {
        std::array<int, 3> x{ a, c, e };
        std::array<int, 3> y{ b, d, f };

        std::cout << x << " compared to " << y << " is " << compare(x, y) << "\n";
    }

    {
        std::vector<std::array<int, 2>> a_min{};
        calc_A(a_min, a, b);

        std::cout << "min(A) = {";
        for (auto x : a_min) std::cout << x << ", ";
        std::cout << "\b\b}\n";
    }

    {
        std::vector<std::array<int, 4>> b_min{};
        calc_B(b_min, c, d, e, f);

        std::cout << "min(B) = {";
        for (auto x : b_min) std::cout << x << ", ";
        std::cout << "\b\b}, " << b_min.size() << " elements\n";
    }

    return 0;
}