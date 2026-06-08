#ifndef TABOO_SEARCH_HPP
#define TABOO_SEARCH_HPP

#include "graph.hpp"
#include "permutation.hpp"

#include <random>
#include <vector>

void taboo_search(Permutation& p, size_t steps_limit, size_t taboo_epoch,
                    std::vector<size_t>& taboo, 
                    std::uniform_int_distribution<size_t>& dist, 
                    std::mt19937& gen
);    
#endif // TABOO_SEARCH_HPP