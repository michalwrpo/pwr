#include "local_search.hpp"

#include <print>

int local_search_all(Permutation& p) {
    int steps{ 0 };
    long best{ p.len };
    size_t id1 { 0 };
    size_t id2 { 0 };

    bool changed{ false };
    size_t n{ p.g.get().n };

    do {
        changed = false;
        for (size_t i{ 0 }; i < n - 2; i++) {
            for (size_t j{ i + 1 }; j < n - 1; j++) {
                long cost = p.invert_cost(i, j);
                
                if (cost < best) {
                    best = cost;
                    id1 = i;
                    id2 = j;
                    changed = true;
                }
            }
        }

        if (id2 > 0) p.invert(id1, id2);
        steps++;
    } while (changed);

    return steps;
}
