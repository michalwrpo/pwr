#include "graph.hpp"
#include "local_search.hpp"
#include "permutation.hpp"

#include <filesystem>
#include <iostream>
#include <print>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::println(stderr, "Usage: {} FILE", argv[0]);
        return 1;
    }

    Graph g{ argv[1] };
    Permutation p{ g };

    std::println("{}", p.len);

    int steps{ local_search_all(p) };

    std::println("Found: {}", p.len);

    std::println("Steps: {}", steps);
}