#include "graph.hpp"

Graph::Graph() {}

Graph::Graph(ull vertices) : vertices(vertices), maxCost(0), adjList(vertices), directed(true) {}

Graph::Graph(ull vertices, bool directed) : vertices(vertices), maxCost(0), adjList(vertices), directed(directed) {}

void Graph::addEdge(ull u, ull v, ull weight) {
    adjList[u].emplace_back(v, weight);
    if (!directed) {
        adjList[v].emplace_back(u, weight);
    }
}

const std::vector<std::pair<ull, ull>>& Graph::getNeighbors(ull u) const {
    return adjList[u];
}

ull Graph::getVerticesCount() const {
    return vertices;
}

void Graph::setEdgeCount(ull e) {
    edges = e;
}

ull Graph::getEdgeCount() {
    return edges;
}

void Graph::setMaxCost(ull c) {
    maxCost = c;
}

ull Graph::getMaxCost() {
    return maxCost;
}


