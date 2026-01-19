#ifndef FLOW_HPP
#define FLOW_HPP

#include "graph.hpp"

struct ParentInfo {
    std::size_t u;          // The parent node index
    std::size_t edge_idx;   // Index in adj[u] that leads to current node
};

long long Edmonds_Karp(Graph& graph, std::size_t source, std::size_t sink);

#endif // FLOW_HPP