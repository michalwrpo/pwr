#include "permutation.hpp"

#include <algorithm>
#include <iterator>
#include <print>
#include <random>

long Permutation::invert_cost(size_t from, size_t to) const {
    const size_t first = elements[from];
    const size_t last = elements[to];
    const size_t prev = elements[from == 0 ? n - 1 : from - 1];
    const size_t next = elements[to == n - 1 ? 0 : to + 1];

    std::vector<long>& d = g.get().dist;
    size_t shift = g.get().shift;

    return len + d[(first << shift) + next] + d[(prev << shift) + last] - d[(prev << shift) + first] - d[(last << shift) + next];
}


void Permutation::invert(size_t from, size_t to) {
    len = invert_cost(from, to);

    std::reverse(
        elements.begin() + static_cast<long>(from), 
        elements.begin() + static_cast<long>(to) + 1
    );
}

Permutation::Permutation(Graph& graph) : n{graph.n}, len{0}, g{graph} {
    elements.resize(g.get().n);

    std::iota(elements.begin(), elements.end(), 0);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(elements.begin(), elements.end(), gen);

    for (size_t i{ 0 }; i < g.get().n; i++) {
        len += g.get().dist[(elements[i] << g.get().shift) + elements[(i + 1) % g.get().n]];
    }
}
