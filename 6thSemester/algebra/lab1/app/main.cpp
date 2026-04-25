#include "gauss.hpp"

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

    return 0;
}