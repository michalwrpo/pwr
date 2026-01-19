#include <print>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

#include "flow.hpp"
#include "graph.hpp"
#include "glpk.hpp"

int main(int argc, char* argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();

    if (argc < 5 || argc > 8) {
        std::println("Usage: ./matching.out --size <k> --degree <i> [--glpk <output>] [--printMatching]");
        return 1;
    }

    std::string arg1 = argv[1];
    if (arg1 != "--size") {
        std::println("Usage: ./matching.out --size <k> --degree <i> [--glpk <output>] [--printMatching]");
        return 1;
    }

    std::string arg3 = argv[3];
    if (arg3 != "--degree") {
        std::println("Usage: ./matching.out --size <k> --degree <i> [--glpk <output>] [--printMatching]");
        return 1;
    }

    bool matching = false, glpk = false;
    if (argc == 6 || argc == 8) {
        std::string arg4 = argv[argc - 1];
        std::string arg5 = argv[argc - 3];

        if (arg4 != "--printMatching" && arg5 != "--printMatching") {
            std::println("Usage: ./matching.out --size <k> --degree <i> [--glpk <output>] [--printMatching]");
            return 1;
        }
        matching = true;
    }

    std::string glpkfile = "";
    if (argc > 6) {
        std::string arg4 = argv[argc - 3];
        std::string arg5 = argv[argc - 2];
        std::string arg6 = argv[argc - 1];

        if (arg4 == "--glpk") {
            glpk = true;
            glpkfile = arg5;
        } else if (arg5 == "--glpk") {
            glpk = true;
            glpkfile = arg6;
        } else {
            std::println("Usage: ./matching.out --size <k> --degree <i> [--glpk <output>] [--printMatching]");
            return 1;
        }
    }

    std::size_t k = std::stoul(argv[2]);
    std::size_t i = std::stoul(argv[4]);

    if (i > k) {
        std::println("Error: i cannot be greater than k.");
        return 1;
    }

    Graph graph(k, i);

    std::size_t source = 0;
    std::size_t sink = (1 << (k + 1)) + 1;

    long long result = Edmonds_Karp(graph, source, sink);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::println("Edges: {}", result);

    std::cerr << std::fixed << std::setprecision(6) << elapsed.count() << std::endl;

    if (matching) {
        for (std::size_t u = 1; u < graph.n + 1; ++u) {
            for (const Edge& e : graph.adj[u]) {
                if (e.flow > 0) {
                    std::println("{} -> {}", u, e.to);
                }
            }
        }
    }

    if (glpk) {
        std::ofstream outfile(glpkfile);
        if (!outfile.is_open()) {
            std::println(stderr, "Error: Could not open file {} for writing.", glpkfile);
            return 1;
        }
        generate_mathprog(graph, outfile);
        outfile.close();
    }

    return 0;
}