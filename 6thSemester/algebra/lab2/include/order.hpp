#ifndef ORDER_HPP
#define ORDER_HPP

#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

enum class Compare {
    Incomparable,
    Equal,
    Greater,
    Less,
};

template <size_t N>
Compare Lex(std::array<int, N> a, std::array<int, N> b, std::array<size_t, N> perm) {
    for (size_t j : perm) {
        if (a[j] > b[j]) return Compare::Greater;
        if (a[j] < b[j]) return Compare::Less;
    }

    return Compare::Equal;
}

template <size_t N>
Compare GradedLex(std::array<int, N> a, std::array<int, N> b, std::array<size_t, N> perm) {
    int deg_a = std::accumulate(a.begin(), a.end(), 0);
    int deg_b = std::accumulate(b.begin(), b.end(), 0);
    if (deg_a > deg_b) return Compare::Greater;
    if (deg_a < deg_b) return Compare::Less;

    for (size_t j : perm) {
        if (a[j] > b[j]) return Compare::Greater;
        if (a[j] < b[j]) return Compare::Less;
    }

    return Compare::Equal;
}

std::ostream& operator<<(std::ostream& out, Compare v);

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const std::array<T, N>& arr) {
    out << "(";
    for (T x : arr) out << x << ", ";
    
    return out << "\b\b)";
}




#endif // ORDER_HPP