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

    if (argc < 3 || argc > 6) {
        std::println(stderr, "Usage: ./maxflow.out --size <k> [--glpk <output>] [--printFlow]");
        return 1;
    }

    std::string arg1 = argv[1];
    if (arg1 != "--size") {
        std::println(stderr, "Usage: ./maxflow.out --size <k> [--glpk <output>] [--printFlow]");
        return 1;
    }

    bool flow = false, glpk = false;
    if (argc == 4 || argc == 6) {
        std::string arg3 = argv[argc - 1];
        std::string arg4 = argv[argc - 3];

        if (arg3 != "--printFlow" && arg4 != "--printFlow") {
            std::println(stderr, "Usage: ./maxflow.out --size <k> [--glpk <output>] [--printFlow]");
            return 1;
        }
        flow = true;
    }

    std::string glpkfile = "";
    if (argc > 4) {
        std::string arg3 = argv[argc - 3];
        std::string arg4 = argv[argc - 2];
        std::string arg5 = argv[argc - 1];

        if (arg3 == "--glpk") {
            glpk = true;
            glpkfile = arg4;
        } else if (arg4 == "--glpk") {
            glpk = true;
            glpkfile = arg5;
        } else {
            std::println(stderr, "Usage: ./maxflow.out --size <k> [--glpk <output>] [--printFlow]");
            return 1;
        }
    }
    
    std::size_t k = std::stoul(argv[2]);

    Graph graph(k);

    std::size_t source = 0;
    std::size_t sink = (1 << k) - 1;

    std::pair<long long, int> result = Edmonds_Karp(graph, source, sink);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::println("Max Flow: {}.", result.first);

    std::cerr << std::fixed << std::setprecision(6) << elapsed.count() << " " << result.second << std::endl;

    if (flow) {
        for (std::size_t u = 0; u < graph.n; ++u) {
            for (const Edge& e : graph.adj[u]) {
                if (e.capacity > 0) {
                    std::println("Edge from {} to {} carries flow {}/{}", u, e.to, e.flow, e.capacity);
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