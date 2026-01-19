#include <random>
#include <stdexcept>

#include "graph.hpp"

Graph::Graph(std::size_t k_val, std::size_t i_val) : k(k_val), i(i_val) {
    if (i_val > k_val) {
        throw std::invalid_argument("i cannot be greater than k");
    }

    n = 1 << k ; // 2^k
    adj.resize(2 * n + 2);
    
    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());

    for (std::size_t j = 1; j < n + 1; ++j) {
        add_edge(0, j);
        add_edge(n + j, 2 * n + 1);
    }

    for (std::size_t j = 1; j < n + 1; ++j) {
        std::uniform_int_distribution<std::size_t> dis(n + 1, 2 * n);
        for (std::size_t e = 0; e < i; ++e) {
            add_edge(j, dis(gen));
        }
    }
}

void Graph::add_edge(std::size_t u, std::size_t v) {
    Edge a = {v, 1, 0, static_cast<std::size_t>(adj[v].size())};
    Edge b = {u, 0, 0, static_cast<std::size_t>(adj[u].size())}; // Back edge
    adj[u].push_back(a);
    adj[v].push_back(b);
}