#ifndef GENETIC_HPP
#define GENETIC_HPP

#include "permutation.hpp"

constexpr int NO_IMPROVEMENT_ITERATIONS{ 10 };

std::pair<Permutation, int> genetic_ox(Graph& g, size_t population_size, size_t parent_pool, double mutation_chance);

std::pair<Permutation, int> genetic_pmx(Graph& g, size_t population_size, size_t parent_pool, double mutation_chance);

std::pair<Permutation, int> genetic_meme(Graph& g, size_t population_size, size_t parent_pool, double mutation_chance);

std::pair<Permutation, int> genetic_islands(Graph& g, size_t islands, size_t island_populaiton, size_t parent_pool, double mutation_chance, size_t migration_interval);


#endif // GENETIC_HPP