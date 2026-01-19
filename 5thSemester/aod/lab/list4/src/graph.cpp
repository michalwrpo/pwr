#include <random>
#include <algorithm>
#include <cmath>

#include "graph.hpp"
#include "bits.hpp"

Graph::Graph(std::size_t k_val) : k(k_val) {
    n = 1 << k; // 2^k
    adj.resize(n);
    
    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < k; ++j) {
            std::size_t num = i + (1 << j);
            
            if (num >= n) continue;

            if (H(i ^ num) == 1) {
                std::size_t h_i = H(i);
                std::size_t h_num = H(num);
                std::size_t z_i = Z(i, k);
                std::size_t z_num = Z(num, k);

                std::size_t l = std::max({h_i, h_num, z_i, z_num});
                
                long long max_cap = 1LL << l; 
                std::uniform_int_distribution<long long> dist(1, max_cap);
                long long capacity = dist(gen);

                add_edge(i, num, capacity);
            }
        }
    }
}

void Graph::add_edge(std::size_t u, std::size_t v, long long capacity) {
    Edge a = {v, capacity, 0, static_cast<std::size_t>(adj[v].size())};
    Edge b = {u, 0, 0, static_cast<std::size_t>(adj[u].size())}; // Back edge
    adj[u].push_back(a);
    adj[v].push_back(b);
}