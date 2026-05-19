#ifndef ANNEALING_HPP
#define ANNEALING_HPP

#include "permutation.hpp"

#include <vector>

constexpr int NO_IMPROVEMENT_ITERATIONS{5};

int simulated_annealing(Permutation& p, double temperature, double cooling_coefficient, size_t attempts);

#endif // ANNEALING_HPP