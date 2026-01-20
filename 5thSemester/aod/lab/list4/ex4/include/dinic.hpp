#ifndef DINIC_HPP
#define DINIC_HPP

#include "graph.hpp"
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

class DinicSolver {
private:
    Graph& graph;
    std::vector<int> level;      // Stores the level (distance from source) of each node
    std::vector<std::size_t> ptr; // Current arc optimization: stores the index of the next edge to explore

public:
    explicit DinicSolver(Graph& g);

    // Main function to calculate Max Flow
    std::pair<long long, std::size_t> solve(std::size_t source, std::size_t sink);

private:
    // BFS: Builds the Level Graph
    // Returns true if the sink is reachable from the source in the residual graph
    bool bfs(std::size_t s, std::size_t t);

    // DFS: Finds blocking flow in the Level Graph
    // Pushes flow along paths where level[v] == level[u] + 1
    long long dfs(std::size_t u, std::size_t t, long long pushed);
};

#endif // DINIC_HPP