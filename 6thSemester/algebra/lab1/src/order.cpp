#include "order.hpp"

#include <array>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

std::ostream& operator<<(std::ostream& out, Compare v) {
    switch (v) {
    case Compare::Incomparable: return out << "incomparable";
    case Compare::Equal:        return out << "equal";
    case Compare::Greater:      return out << "greater";
    case Compare::Less:         return out << "less";
    }
}

void calc_A(std::vector<std::array<int,2>>& out, int a, int b) {
    std::vector<std::array<int, 2>> A{};
    auto r1 = std::views::iota((a - 3 < 0) ? 0 : a - 3, a + 4);
    auto r2 = std::views::iota((b - 3 < 0) ? 0 : b - 3, b + 4);

    auto prod = std::views::cartesian_product(r1, r2);

    for (auto [x, y] : prod) {
        if ((x - a) * (x - a) + (y - b) * (y - b) < 5) {
            A.push_back({x, y});
        }
    }

    find_min(A, out);
}  

void calc_B(std::vector<std::array<int,4>>& out, int c, int d, int e, int f) {
    std::vector<std::array<int, 4>> B{};
    auto r1 = std::views::iota(0, c + 16);
    auto r2 = std::views::iota(0, d + 16);
    auto r3 = std::views::iota(0, e + 16);
    auto r4 = std::views::iota(0, f + 16);

    auto prod = std::views::cartesian_product(r1, r2, r3, r4);

    for (auto [w, x, y, z] : prod) {
        if ((w - c) * (w - c) + (x - d) * (x - d) 
            + (y - e) * (y - e) + (z - f) * (z - f) > 224) {
            B.push_back({w, x, y, z});
        }
    }

    find_min(B, out);
}
