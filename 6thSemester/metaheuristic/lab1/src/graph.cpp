#include "graph.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

static long calc_distance(std::pair<double, double> p1, std::pair<double, double> p2) {
    return std::lround(std::hypot(p1.first - p2.first, p1.second - p2.second));
}

Graph::Graph(std::filesystem::path path) {
    std::ifstream istrm{ path };

    if (!istrm.is_open()) {
        std::cerr << "Failed to open " << path << "\n";
        return;
    }

    std::string s{};
    while (s != "NODE_COORD_SECTION") istrm >> s;
    
    size_t x;
    double y, z;

    while (istrm >> x >> y >> z) {
        cords.insert({x - 1, {y, z}});
    }

    n = cords.size();
    
    dist.resize(n);

    for (size_t i = 0; i < n; i++) dist[i].resize(n);

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = i + 1; j < n; j++) {
            long d = calc_distance(this->cords[i], this->cords[j]);
            dist[i][j] = d;
            dist[j][i] = d;
        }
    }
}
