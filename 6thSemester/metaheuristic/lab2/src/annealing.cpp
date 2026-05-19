#include "annealing.hpp"

#include "permutation.hpp"

#include <algorithm>
#include <cmath>
#include <random>

#include <iostream>


int simulated_annealing(Permutation& p, double temperature, double cooling_coefficient, size_t attempts) {
    int steps{ 0 };
    int last_changed{ 0 };
    const size_t n{ p.g.get().n };
    const size_t shift{ p.g.get().shift };
    const auto& d = p.g.get().dist;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> chance(0, 1);
    std::uniform_int_distribution<size_t> vertex(0, n - 1);

    Permutation cur{ p };
    
    do {
        ++last_changed;
        const size_t* elem = cur.elements.data();

        for (size_t i{ 0 }; i < attempts; ++i) {
            size_t v1 { vertex(gen) };
            size_t v2 { vertex(gen) }; 
            while (v1 == v2) { v2 = vertex(gen); }
            if (v2 < v1) std::swap(v1, v2);
            if (v1 == 0 && v2 == n-1) {
                ++v1; 
                --v2; 
            }

            const size_t first_shift = elem[v1] << shift;
            const size_t prev = elem[v1 == 0 ? n - 1 : v1 - 1];

            const size_t last_shift = elem[v2] << shift;
            const size_t next = elem[v2 == n - 1 ? 0 : v2 + 1];

            const long delta = d[first_shift + next] + d[last_shift + prev] - d[first_shift + prev] - d[last_shift + next];
            
            if (delta < 0) {
                cur.invert(v1, v2);
                if (cur.len < p.len) {
                    p.elements = cur.elements;
                    p.len = cur.len;
                    last_changed = 0;
                }
            } else if (chance(gen) < std::exp(-static_cast<double>(delta) / temperature)) {
                cur.invert(v1, v2);
            }
        }

        steps++;
        temperature *= cooling_coefficient;
    } while (last_changed < NO_IMPROVEMENT_ITERATIONS);

    return steps;
}