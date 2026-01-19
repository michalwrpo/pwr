#ifndef GLPK_HPP
#define GLPK_HPP

#include <ostream>

#include "graph.hpp"

void generate_mathprog(const Graph& g, std::ostream& out);

#endif // GLPK_HPP