#include "taboo_search.hpp"

#include <iostream>
#include <random>
#include <vector>

void taboo_search(Permutation& p, size_t steps_limit, size_t taboo_epoch,
                    std::vector<size_t>& taboo, 
                    std::uniform_int_distribution<size_t>& dist, 
                    std::mt19937& gen
    ) {    
    const size_t n{ p.g.get().n };
    const size_t shift{ p.g.get().shift };
    const auto& d = p.g.get().dist;
    
    Permutation cur{ p };


    for (size_t steps{ 0 }; steps < steps_limit; ++steps) {
        long best_delta { 0 };
        size_t best_i { 0 };
        size_t best_j { 0 };
        const auto& elem = cur.elements;

        for (size_t i{ 0 }; i < n; ++i) {
            size_t v1 { dist(gen) };
            size_t v2 { dist(gen) }; 
            while (v1 == v2) { v2 = dist(gen); }
            if (v2 < v1) std::swap(v1, v2);
            if (v1 == 0 && v2 == n-1) {
                ++v1; 
                --v2; 
            }

            if (taboo[v1 * n + v2] > steps + taboo_epoch) continue;

            const size_t first_shift = elem[v1] << shift;
            const size_t prev = elem[v1 == 0 ? n - 1 : v1 - 1];

            const size_t last_shift = elem[v2] << shift;
            const size_t next = elem[v2 == n - 1 ? 0 : v2 + 1];
            
            const long delta = d[first_shift + next] + d[last_shift + prev] - d[first_shift + prev] - d[last_shift + next];

            if (delta < best_delta) {
                best_delta = delta;
                best_i = v1;
                best_j = v2;
            }                
        }

        cur.invert(best_i, best_j);
        if (cur.len < p.len) {
            p.elements = cur.elements;
            p.len = cur.len;
        }
        taboo[best_i * n + best_j] = steps_limit + taboo_epoch;

    } 
}