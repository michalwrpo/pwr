#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <filesystem>
#include <map>
#include <string_view>
#include <vector>

class Graph {
    public:
        size_t n;
        size_t shift;
        std::map<size_t, std::pair<double, double>> cords;
        std::vector<long> dist;

        Graph(std::filesystem::path path);
};

#endif