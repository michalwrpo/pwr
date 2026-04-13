#include "permutation.hpp"

#include <algorithm>
#include <iterator>
#include <print>
#include <random>

long Permutation::invert_cost(size_t from, size_t to) const {
    long cost = len;
    auto n = g.get().n;

    const size_t first = elements[from];
    const size_t last = elements[to];
    const size_t prev = elements[(n + from - 1) % n];
    const size_t next = elements[(to + 1) % n];

    cost -= g.get().dist[prev][first];
    cost -= g.get().dist[last][next];
    cost += g.get().dist[prev][last];
    cost += g.get().dist[first][next];


    return cost;
}


void Permutation::invert(size_t from, size_t to) {
    len = invert_cost(from, to);

    std::reverse(
        elements.begin() + static_cast<long>(from), 
        elements.begin() + static_cast<long>(to) + 1
    );
}

Permutation::Permutation(Graph& graph) : len{0}, g{graph} {
    elements.resize(g.get().n);

    std::iota(elements.begin(), elements.end(), 0);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(elements.begin(), elements.end(), gen);

    for (size_t i{ 0 }; i < g.get().n; i++) {
        len += g.get().dist[elements[i]][elements[(i + 1) % g.get().n]];
    }
}
