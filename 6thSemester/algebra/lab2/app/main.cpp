#include "order.hpp"
#include "polynomial.hpp"
#include "polynomial_reduce.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

int main() {
    int idx{};
    // std::cout << "Input your student number: ";
    // std::cin >> idx;

    // int f = idx % 10;
    // int e = (idx /= 10) % 10;
    // int d = (idx /= 10) % 10;
    // int c = (idx /= 10) % 10;
    // int b = (idx /= 10) % 10;
    // int a = (idx /= 10) % 10;

    std::cout << "====================\n     Exercise 4\n====================\n";

    std::array<size_t, 3> perm{ 0, 1, 2 };
    Polynomial<double, 3> f{ {{{3, 0, 0}, 1}, {{2, 1, 0}, -1}, {{2, 0, 1}, -1}}, perm, GradedLex };
    Polynomial<double, 3> g1{ {{{2, 1, 0}, 1}, {{0, 0, 1}, -1}}, perm, GradedLex };
    Polynomial<double, 3> g2{ {{{1, 1, 0}, 1}, {{0, 0, 0}, -1}}, perm, GradedLex };



    auto r1{ reduce(f, {g1, g2}) };
    std::cout << "f = (" << r1[0] << ") * g1 + (" << r1[1] << ") * g2 + (" << r1[2] << ")\n";

    auto r2{ reduce(f, {g2, g1}) };
    std::cout << "f = (" << r2[0] << ") * g2 + (" << r2[1] << ") * g1 + (" << r2[2] << ")\n";


    return 0;
}