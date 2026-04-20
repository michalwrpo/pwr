#include "mst.hpp"

#include "graph.hpp"

#include <limits>
#include <print>
#include <queue>
#include <unordered_set>

void Prim(Graph& g) {
    size_t n { g.n };
    g.mst.resize(n);

    std::vector<long> key(n, __LONG_MAX__);
    std::vector<bool> visited(n, false);

    std::priority_queue<std::pair<size_t, size_t>, 
        std::vector<std::pair<size_t, size_t>>, 
        std::greater<std::pair<size_t, size_t>>> pq {};

    g.mst[0] = 0;
    key[0] = 0;

    pq.push({0, 0});
    
    while(!pq.empty()) {
        size_t node { pq.top().second };
        pq.pop();
        visited[node] = true;

        for (size_t i { 0 }; i < n; ++i) {
            long dist { g.dist[(node << g.shift) + i] };
            g.mst_weight += dist;

            if (!visited[i] && dist > 0 && dist < key[i]) {
                pq.push({ dist, i });
                key[i] = dist;
                g.mst[i] = node;
            }
        }
    }
}