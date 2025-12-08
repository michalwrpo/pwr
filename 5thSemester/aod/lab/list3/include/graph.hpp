#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>

typedef unsigned long long ull;

class Graph {
public:
    Graph();
    Graph(ull vertices);
    Graph(ull vertices, bool directed);
    void addEdge(ull u, ull v, ull weight);
    const std::vector<std::pair<ull, ull>>& getNeighbors(ull u) const;


    ull getVerticesCount() const;
    void setEdgeCount(ull e);
    ull getEdgeCount();
    void setMaxCost(ull c);
    ull getMaxCost();

private:
    ull vertices;
    ull edges;
    ull maxCost;
    std::vector<std::vector<std::pair<ull, ull>>> adjList;
    bool directed;
};

#endif // GRAPH_HPP