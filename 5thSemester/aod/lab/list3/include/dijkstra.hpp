#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <utility>

#include "graph.hpp"

std::vector<ull> dijkstra(const Graph& graph, ull start);
std::vector<ull> dial(const Graph& graph, ull start, ull maxWeight);
std::vector<ull> radix(const Graph &g, ull start);

ull dijkstra_path(const Graph& graph, ull start, ull end);
ull dial_path(const Graph& graph, ull start, ull end, ull maxWeight);
ull radix_path(const Graph &g, ull start, ull end);


#endif // DIJKSTRA_HPP