#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

struct Edge {
    std::size_t to;
    long long capacity;
    long long flow;
    std::size_t rev; // Index of the reverse edge in adj[to]
};

class Graph {
public:
    std::size_t k;
    std::size_t n;
    std::size_t i;
    std::vector<std::vector<Edge>> adj;

    Graph(std::size_t k_val, std::size_t i_val);

    void add_edge(std::size_t u, std::size_t v);
};

#endif // GRAPH_HPP