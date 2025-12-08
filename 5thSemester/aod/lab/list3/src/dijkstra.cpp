#include <queue>
#include <limits>
#include <unordered_set>
#include <print>
#include <bits/stdc++.h>
#include <print>

#include "dijkstra.hpp"

template<typename Key, typename Value>
class RadixHeap {
public:
    RadixHeap() : last(0) {
        buckets.resize(65); // enough for 64-bit integers
    }

    bool empty() const {
        return sz == 0;
    }

    void push(Key key, Value value) {
        ull b = bucketIndex(key);
        buckets[b].push_back({key, value});
        ++sz;
    }

    std::pair<Key, Value> pop_min() {
        if (!buckets[0].empty()) {
            auto [k, v] = buckets[0].back();
            buckets[0].pop_back();
            --sz;
            last = k;
            return {k, v};
        }

        // Find first non-empty bucket
        ull b = 1;
        while (b < buckets.size() && buckets[b].empty()) b++;

        // Rebucket elements
        Key new_last = std::numeric_limits<Key>::max();
        for (auto &p : buckets[b]) {
            new_last = std::min(new_last, p.first);
        }
        last = new_last;

        std::vector<std::pair<Key, Value>> tmp;
        swap(tmp, buckets[b]);

        for (auto &[k, v] : tmp) {
            buckets[bucketIndex(k)].push_back({k, v});
        }

        return pop_min(); // now bucket 0 is non-empty
    }

private:
    std::vector<std::vector<std::pair<Key, Value>>> buckets;
    Key last = 0;
    ull sz = 0;

    ull bucketIndex(Key key) const {
        Key diff = key ^ last;
        if (diff == 0) return 0;
        return static_cast<ull>(std::bit_width(static_cast<std::make_unsigned_t<Key>>(diff)));
    }
};


std::vector<ull> dijkstra(const Graph& graph, ull start) {
    ull n = graph.getVerticesCount();
    std::vector<ull> distances(n, std::numeric_limits<ull>::max());
    distances[start] = 0;

    using Pair = std::pair<ull, ull>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [dist, u] = pq.top();
        pq.pop();

        if (dist > distances[u]) continue;

        for (const auto& [v, weight] : graph.getNeighbors(u)) {
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.emplace(distances[v], v);
            }
        }
    }

    return distances;
}

std::vector<ull> dial(const Graph& graph, ull start, ull maxWeight) {
    ull n = graph.getVerticesCount();
    std::vector<ull> distances(n, std::numeric_limits<ull>::max());
    distances[start] = 0;
    ull d = 0;
    ull C = maxWeight + 1;
    int left = 1;

    std::vector<std::unordered_set<ull>> buckets(C);
    buckets[0].insert(start);

    ull currentBucket = 0;

    while (left > 0) {
        if (buckets[currentBucket].empty()) {
            currentBucket = (currentBucket + 1) % C;
            ++d;
            continue;
        }

        ull u = *buckets[currentBucket].begin();
        buckets[currentBucket].erase(u);
        --left;

        for (const auto& [v, weight] : graph.getNeighbors(u)) {
            ull newDist = distances[u] + weight;
            if (newDist < distances[v]) {
                if (distances[v] != std::numeric_limits<ull>::max()) {
                    buckets[(currentBucket + distances[v] - d) % C].erase(v);
                    --left;
                }
                ++left;
                distances[v] = newDist;
                buckets[(currentBucket + newDist - d) % C].insert(v);
            }
        }
    }

    return distances;
}


std::vector<ull> radix(const Graph &g, ull start) {
    ull n = g.getVerticesCount();
    const ull INF = std::numeric_limits<ull>::max();

    std::vector<ull> dist(n, INF);
    dist[start] = 0;

    RadixHeap<ull, ull> heap;
    heap.push(0, start);

    while (!heap.empty()) {
        auto [d, u] = heap.pop_min();
        if (d != dist[u]) continue; // skip outdated entries

        for (auto &[v, w] : g.getNeighbors(u)) {
            ull nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                heap.push(nd, v);
            }
        }
    }
    return dist;
}