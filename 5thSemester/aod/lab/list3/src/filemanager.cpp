#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "filemanager.hpp"


Graph loadGraph(const std::string &filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Blad: nie mozna otworzyc pliku z danymi: " << filename << "\n";
        exit(1);
    }

    Graph g;
    std::string line;

    while (getline(in, line)) {
        if (line.size() == 0 || line[0] == 'c') continue;

        std::string type;
        std::stringstream ss(line);
        ss >> type;

        if (type == "p") {
            std::string sp;
            ull n, m;
            ss >> sp >> n >> m;
            g = Graph(n);
            g.setEdgeCount(m);
        } else if (type == "a") {
            ull u, v;
            ull cost;
            ss >> u >> v >> cost;
            g.addEdge(u - 1, v - 1, cost);
            if (cost > g.getMaxCost()) g.setMaxCost(cost);
        }
    }
    return g;
}

std::vector<ull> loadSources(const std::string &filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Blad: nie mozna otworzyc pliku ze zrodlami: " << filename << "\n";
        exit(1);
    }

    std::vector<ull> sources;
    std::string line;

    while (getline(in, line)) {
        if (line.size() == 0 || line[0] == 'c') continue;
        std::string type;
        std::stringstream ss(line);
        ss >> type;
        if (type == "s") {
            ull s;
            ss >> s;
            sources.push_back(s - 1);
        }
    }
    return sources;
}

std::vector<std::pair<ull, ull>> loadPairs(const std::string &filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Blad: nie mozna otworzyc pliku ze zrodlami: " << filename << "\n";
        exit(1);
    }

    std::vector<std::pair<ull, ull>> pairs;
    std::string line;

    while (getline(in, line)) {
        if (line.size() == 0 || line[0] == 'c') continue;
        std::string type;
        std::stringstream ss(line);
        ss >> type;
        if (type == "q") {
            ull u, v;
            ss >> u >> v;
            pairs.push_back({u - 1, v - 1});
        }
    }
    return pairs;
}