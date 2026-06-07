#include "genetic.hpp"

#include "permutation.hpp"

#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

#include <iostream>

static void mutate(Permutation& p, std::mt19937& gen, std::uniform_int_distribution<size_t>& vertex) {
    size_t v1{ vertex(gen) };
    size_t v2{ vertex(gen) };

    if (v1 > v2) std::swap(v1, v2);

    p.invert(v1, v2);
}

static void ordered_crossover(const Permutation& p1, const Permutation& p2,
                                size_t from, size_t to, 
                                std::vector<bool> added, Permutation& child) {
    if (from > to) std::swap(from, to);

    size_t n = p1.n;
    std::fill(added.begin(), added.end(), false);
    
    child.elements = p1.elements;

    for (size_t j = from; j <= to; ++j) {
        added[child.elements[j]] = true;
    }

    size_t i = (to + 1);
    if (i >= n) i = 0;

    size_t p2_idx = (to + 1);
    if (p2_idx >= n) p2_idx = 0;

    for (size_t j = 0; j < n; ++j) {
        if (!added[p2.elements[p2_idx]]) {
            child.elements[i] = p2.elements[p2_idx];
            i++;
            if (i >= n) i = 0; 
        }
        
        p2_idx++;
        if (p2_idx >= n) p2_idx = 0;
    }

    child.recalculate();
}

std::pair<Permutation, int> genetic(Graph& g, size_t population_size, size_t parent_pool, double mutation_chance) {
    int steps{ 0 };
    int last_changed{ 0 };
    const size_t n{ g.n };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> chance(0, 1);
    std::uniform_int_distribution<size_t> vertex(0, n - 1);
    std::uniform_int_distribution<size_t> pop(0, population_size - 1);

    std::vector<bool> crossover_mask(n, false);

    std::vector<Permutation> population{};
    std::vector<Permutation> next_population{};
    population.reserve(population_size);
    next_population.resize(population_size, Permutation{g});
    
    Permutation best{ g };

    for (size_t i = 0; i < population_size; ++i) {
        population.push_back(Permutation{ g });
        if (population[i].len < best.len) {
            best.elements = population[i].elements;
            best.len = population[i].len;
        }
    }
        
    while (last_changed < NO_IMPROVEMENT_ITERATIONS) {
        ++last_changed;
        ++steps;

        for (size_t i{ 0 }; i < population_size / 2; ++i) {
            size_t parent1{ pop(gen) };
            for (size_t j = 0; j < parent_pool - 1; j++) {
                size_t v{ pop(gen) };
                if (population[v].len < population[parent1].len) {
                    parent1 = v;
                }
            }

            size_t parent2{ pop(gen) };
            for (size_t j = 0; j < parent_pool - 1; j++) {
                size_t v{ pop(gen) };
                if (v == parent1) continue;
                if (population[v].len < population[parent2].len) {
                    parent2 = v;
                }
            }

            size_t c1_idx{ i * 2 };
            ordered_crossover(
                population[parent1], population[parent2], vertex(gen), vertex(gen), crossover_mask, next_population[c1_idx]
            );
            
            if (chance(gen) < mutation_chance) {
                mutate(next_population[c1_idx], gen, vertex);
            }

            if (next_population[c1_idx].len < best.len) {
                best.elements = next_population[c1_idx].elements;
                best.len = next_population[c1_idx].len;
                last_changed = 0;
            }

            size_t c2_idx{ i * 2 + 1};
            ordered_crossover(
                population[parent2], population[parent1], vertex(gen), vertex(gen), crossover_mask, next_population[c2_idx]
            );
            
            if (chance(gen) < mutation_chance) {
                mutate(next_population[c2_idx], gen, vertex);
            }
            if (next_population[c2_idx].len < best.len) {
                best.elements = next_population[c2_idx].elements;
                best.len = next_population[c2_idx].len;
                last_changed = 0;
            }
        }

        std::swap(population, next_population);
    }

    return std::pair{best, steps};
}