#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <filesystem>
#include <string_view>
#include <vector>

class Graph {
    public:
        size_t n;
        std::map<size_t, std::pair<double, double>> cords;
        // std::map<std::pair<size_t, size_t>, long> dist;
        std::vector<std::vector<long>> dist;

        Graph(std::filesystem::path path);

        void vInvert(size_t from, size_t to);
};

#endif