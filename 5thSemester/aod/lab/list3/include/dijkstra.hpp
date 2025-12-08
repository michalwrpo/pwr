#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <utility>

#include "graph.hpp"

std::vector<ull> dijkstra(const Graph& graph, ull start);

std::vector<ull> dial(const Graph& graph, ull start, ull maxWeight);

std::vector<ull> radix(const Graph &g, ull start);

#endif // DIJKSTRA_HPP