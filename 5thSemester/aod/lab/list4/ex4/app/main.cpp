#include <print>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

#include "dinic.hpp"
#include "graph.hpp"

int main(int argc, char* argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();

    if (argc < 3 || argc > 4) {
        std::println(stderr, "Usage: ./maxflow.out --size <k> [--printFlow]");
        return 1;
    }

    std::string arg1 = argv[1];
    if (arg1 != "--size") {
        std::println(stderr, "Usage: ./maxflow.out --size <k> [--printFlow]");
        return 1;
    }

    bool flow = false;
    if (argc == 4) {
        std::string arg3 = argv[3];
        if (arg3 != "--printFlow") {
        std::println(stderr, "Usage: ./maxflow.out --size <k> [--printFlow]");
            return 1;
        }
        flow = true;
    }
    
    std::size_t k = std::stoul(argv[2]);

    Graph graph(k);

    std::size_t source = 0;
    std::size_t sink = (1 << k) - 1;

    DinicSolver solver(graph);
    auto result = solver.solve(source, sink);

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


    return 0;
}