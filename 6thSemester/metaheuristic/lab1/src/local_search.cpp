#include "local_search.hpp"

#include <print>

int local_search_all(Permutation& p) {
    int steps{ 0 };
    
    bool changed{ false };
    const size_t n{ p.g.get().n };
    const size_t shift{ p.g.get().shift };
    const auto& d = p.g.get().dist;
    
    do {
        changed = false;
        long best_delta { 0 };
        size_t best_i { 0 };
        size_t best_j { 0 };

        const size_t* elem = p.elements.data();

        for (size_t i{ 0 }; i < n - 2; i++) {
            const size_t first_shift = elem[i] << shift;
            const size_t prev = elem[i == 0 ? n - 1 : i - 1];
            const long partial_delta = -d[first_shift + prev];

            for (size_t j{ i + 1 }; j < n - 1; j++) {
                const size_t last_shift = elem[j] << shift;
                const size_t next = elem[j + 1];

                const long delta = partial_delta + d[first_shift + next] + d[last_shift + prev]  - d[last_shift + next];
                
                if (delta < best_delta) {
                    best_delta = delta;
                    best_i = i;
                    best_j = j;
                    changed = true;
                }
            }
        }

        if (changed) p.invert(best_i, best_j);
        steps++;
    } while (changed);

    return steps;
}
