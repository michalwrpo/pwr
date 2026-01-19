#include <vector>
#include <queue>
#include <utility> 

#include "flow.hpp"

static bool bfs(Graph& graph, std::size_t source, std::size_t sink, std::vector<ParentInfo>& parent) {
    std::size_t n = static_cast<std::size_t>(graph.n);
    n = 2 * n + 2;
    std::vector<bool> visited(n, false);
    std::queue<std::size_t> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        std::size_t u = q.front();
        q.pop();

        if (u == sink) {
            return true;
        }

        for (std::size_t i = 0; i < graph.adj[u].size(); ++i) {
            Edge &e = graph.adj[u][i];
            if (!visited[e.to] && (e.capacity - e.flow) > 0) {
                visited[e.to] = true;
                parent[e.to] = {u, i};
                q.push(e.to);
                
                if (e.to == sink) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

long long Edmonds_Karp(Graph& graph, std::size_t source, std::size_t sink) {
    long long max_flow = 0;
    std::size_t n = graph.n;
    n = 2 * n + 2;
    std::vector<ParentInfo> parent(n, {__SIZE_MAX__, __SIZE_MAX__});

    while (true) {
        
        if (!bfs(graph, source, sink, parent)) {
            break; // No more augmenting paths
        }

        // Find the maximum flow through the path found by BFS
        long long path_flow = -1; 
        std::size_t curr = sink;

        while (curr != source) {
            std::size_t p = parent[curr].u;
            std::size_t idx = parent[curr].edge_idx;
            long long residual = graph.adj[p][idx].capacity - graph.adj[p][idx].flow;
            
            if (path_flow == -1 || residual < path_flow) {
                path_flow = residual;
            }
            curr = p;
        }

        curr = sink;
        while (curr != source) {
            std::size_t p = parent[curr].u;
            std::size_t idx = parent[curr].edge_idx;
            
            graph.adj[p][idx].flow += path_flow;
            
            std::size_t rev_idx = graph.adj[p][idx].rev;
            graph.adj[curr][rev_idx].flow -= path_flow;

            curr = p;
        }

        max_flow += path_flow;
    }

    return max_flow;
}