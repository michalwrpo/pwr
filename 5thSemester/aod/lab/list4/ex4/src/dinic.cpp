#include "dinic.hpp"

DinicSolver::DinicSolver(Graph& g) : graph(g), level(g.n), ptr(g.n) {}

// O(E)
bool DinicSolver::bfs(std::size_t s, std::size_t t) {
    std::fill(level.begin(), level.end(), -1);
    level[s] = 0;
    
    std::queue<std::size_t> q;
    q.push(s);

    while (!q.empty()) {
        std::size_t u = q.front();
        q.pop();

        for (const auto& edge : graph.adj[u]) {
            if (edge.capacity - edge.flow > 0 && level[edge.to] == -1) {
                level[edge.to] = level[u] + 1;
                q.push(edge.to);
            }
        }
    }

    return level[t] != -1;
}

long long DinicSolver::dfs(std::size_t u, std::size_t t, long long pushed) {
    // Base case: If we reached the sink, we found a path
    if (pushed == 0) return 0;
    if (u == t) return pushed;

    // Iterate over edges starting from the last checked index (ptr[u])
    // This is the "Current Arc Optimization" which ensures O(VE) for this phase
    for (std::size_t& cid = ptr[u]; cid < graph.adj[u].size(); ++cid) {
        auto& edge = graph.adj[u][cid];
        std::size_t v = edge.to;

        // Condition 1: Level graph constraint (v must be exactly 1 step further)
        // Condition 2: Residual capacity exists
        if (level[v] != level[u] + 1 || edge.capacity - edge.flow == 0) {
            continue;
        }

        // Recursive step: try to push flow to the child
        long long tr = dfs(v, t, std::min(pushed, edge.capacity - edge.flow));
        
        if (tr == 0) {
            continue;
        }

        // Apply flow
        edge.flow += tr;                    // Add flow to forward edge
        graph.adj[v][edge.rev].flow -= tr;  // Subtract flow from reverse edge
        
        return tr;
    }
    
    return 0;
}

std::pair<long long, std::size_t> DinicSolver::solve(std::size_t source, std::size_t sink) {
    long long max_flow = 0;
    std::size_t iterations = 0;

    // While the sink is reachable (BFS finds a way) 
    while (bfs(source, sink)) {
        // Reset the current arc pointers for the new level graph
        std::fill(ptr.begin(), ptr.end(), 0);

        // Push as much flow as possible using DFS until blocking flow is reached
        while (long long pushed = dfs(source, sink, std::numeric_limits<long long>::max())) {
            max_flow += pushed;
            iterations++;
        }
    }

    return std::make_pair(max_flow, iterations);
}