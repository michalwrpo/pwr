#ifndef ORDER_HPP
#define ORDER_HPP

#include <array>
#include <iostream>
#include <map>
#include <vector>

enum class Compare {
    Incomparable,
    Equal,
    Greater,
    Less,
};

template <size_t N>
Compare compare(std::array<int, N> a, std::array<int, N> b) {
    Compare first{};
    if (a[0] > b[0]) first = Compare::Greater;
    else if (a[0] < b[0]) first = Compare::Less;
    else first = Compare::Equal;

    for (size_t j = 1; j < N; ++j) {
        if ((a[j] > b[j] && first == Compare::Less) ||
            (a[j] < b[j] && first == Compare::Greater)) {
            return Compare::Incomparable;
        }
        if (first == Compare::Equal && a[j] > b[j]) first = Compare::Greater;
        else if (first == Compare::Equal && a[j] < b[j]) first = Compare::Less;
    }

    return first;
}

std::ostream& operator<<(std::ostream& out, Compare v);

template <size_t N>
std::ostream& operator<<(std::ostream& out, std::array<int, N> arr) {
    out << "(";
    for (int x : arr) out << x << ", ";
    
    return out << "\b\b)";
}

template <size_t N>
void find_min(std::vector<std::array<int, N>>& data, std::vector<std::array<int, N>>& out) {
    out.clear();
    
    for (auto x : data) {
        bool added = false;
        bool incomparable = true;
        size_t j = 0;
        while (j < out.size()) {
            Compare res = compare(x, out[j]);
            if (res == Compare::Equal || res == Compare::Greater) {
                incomparable = false;
                break;
            } 
            if (res == Compare::Less) {
                if (!added) {
                    incomparable = false;
                    added = true;
                    out[j] = x;
                } else {
                    out.erase(out.begin() + static_cast<long>(j));
                }
            }
            ++j;
        }

        if (incomparable) out.push_back(x);
    }
}

void calc_A(std::vector<std::array<int,2>>& out, int a, int b);
void calc_B(std::vector<std::array<int,4>>& out, int c, int d, int e, int f);

#endif // ORDER_HPP