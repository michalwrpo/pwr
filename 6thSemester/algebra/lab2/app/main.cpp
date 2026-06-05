#include "order.hpp"
#include "polynomial.hpp"
#include "polynomial_reduce.hpp"

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

    std::cout << "====================\n     Exercise 4\n====================\n";

    {
        std::array<size_t, 3> perm{ 0, 1, 2 };
        Polynomial<double, 3> f1{ {{{3, 0, 0}, 1}, {{2, 1, 0}, -1}, {{2, 0, 1}, -1}}, perm, GradedLex };
        Polynomial<double, 3> g1{ {{{2, 1, 0}, 1}, {{0, 0, 1}, -1}}, perm, GradedLex };
        Polynomial<double, 3> g2{ {{{1, 1, 0}, 1}, {{0, 0, 0}, -1}}, perm, GradedLex };
    
        auto r1{ reduce(f1, {g1, g2}) };
        std::cout << "f = (" << r1[0] << ") * g1 + (" << r1[1] << ") * g2 + (" << r1[2] << ")\n";
    
        auto r2{ reduce(f1, {g2, g1}) };
        std::cout << "f = (" << r2[0] << ") * g2 + (" << r2[1] << ") * g1 + (" << r2[2] << ")\n\n";
    }

    {
        std::array<size_t, 3> perm1{ 0, 1, 2 };
        std::array<size_t, 3> perm2{ 1, 2, 0 };
        std::array<size_t, 3> perm3{ 2, 0, 1 };
    
        Polynomial<double, 3> h1{ {{{a, b, 0}, 1}, {{0, c, d}, -1}, {{e, 0, f}, 1}}, perm1, Lex };
        Polynomial<double, 3> h2{ {{{a, b, 0}, 1}, {{0, c, d}, -1}, {{e, 0, f}, 1}}, perm2, Lex };
        Polynomial<double, 3> h3{ {{{a, b, 0}, 1}, {{0, c, d}, -1}, {{e, 0, f}, 1}}, perm3, Lex };        

        Polynomial<double, 3> g1{ {{{0, b, 0}, 1}, {{0, 0, d}, -1}, {{e, 0, 0}, 1}}, perm1, Lex };
        Polynomial<double, 3> g2{ {{{0, b, 0}, 1}, {{0, 0, d}, -1}, {{e, 0, 0}, 1}}, perm2, Lex };
        Polynomial<double, 3> g3{ {{{0, b, 0}, 1}, {{0, 0, d}, -1}, {{e, 0, 0}, 1}}, perm3, Lex };


        std::cout << "h: " << h1 << "\n";
        std::cout << "g1: " << g1 << "\n";

        auto r1{ reduce(h1, {g1}) };
        auto r2{ reduce(h2, {g2}) };
        auto r3{ reduce(h3, {g3}) };


        std::cout << perm1 << " | alpha1 = " << r1[0] << "\nr = " << r1[1] << "\n";
        std::cout << perm2 << " | alpha1 = " << r2[0] << "\nr = " << r2[1] << "\n";
        std::cout << perm3 << " | alpha1 = " << r3[0] << "\nr = " << r3[1] << "\n";
    }




    return 0;
}