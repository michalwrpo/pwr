#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>

#include "graph.hpp"
#include "dijkstra.hpp"
#include "filemanager.hpp"

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string file_graph, file_sources, file_output;
    int algorithm;
    bool p2p = false;

    if (argc < 8) {
        std::cerr << "Użycie:\n"
             << "algorytm -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res\n";
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "dijkstra") algorithm = 0;
    else if (arg == "dial") algorithm = 1;
    else if (arg == "radixheap") algorithm = 2;
    else {
        std::cerr << "Nieznany algorytm, opcje: dijkstra | dial | radixheap\n";
        return 1;

    }

    for (int i = 2; i < argc; i++) {
        arg = argv[i];
        if (arg == "-d" && i + 1 < argc) file_graph = argv[++i];
        else if (arg == "-ss" && i + 1 < argc) file_sources = argv[++i];
        else if (arg == "-oss" && i + 1 < argc) file_output = argv[++i];
        else if (arg == "-p2p" && i + 1 < argc) {
            file_sources = argv[++i];
            p2p = true;
        } 
    }

    if (file_graph.empty() || file_sources.empty() || file_output.empty()) {
        std::cerr << "Użycie:\n"
             << "algorytm -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res\n";
        return 1;
    }

    Graph g = loadGraph(file_graph);

    if (!p2p) {
        std::vector<ull> sources = loadSources(file_sources);
    
        auto start = std::chrono::high_resolution_clock::now();
    
        std::vector<std::vector<ull>> results;
        results.reserve(sources.size());
    
        std::cout << "Read graph with " << g.getVerticesCount() << " vertices and max weight " << g.getMaxCost() << std::endl;
    
        switch (algorithm) {
            case 0:
                std::cout << "Algorithm: Dijkstra" << std::endl;
                break;
            case 1:
                std::cout << "Algorithm: Dial" << std::endl;
                break;
            case 2:
                std::cout << "Algorithm: Radixheap" << std::endl;
                break;
            default:
                break;
            }
    
        for (ull s : sources) {
            switch (algorithm) {
            case 0:
                results.push_back(dijkstra(g, s));
                break;
            case 1:
                results.push_back(dial(g, s, g.getMaxCost()));
                break;
            case 2:
                results.push_back(radix(g, s));
                break;
            default:
                break;
            }
        }
    
        auto end = std::chrono::high_resolution_clock::now();
        double avg_ms = std::chrono::duration<double, std::milli>(end - start).count() / static_cast<double>(sources.size());
    
        // ----------- zapis wyników -----------
        std::ofstream out(file_output);
        if (!out) {
            std::cerr << "Błąd: nie można otworzyć pliku wynikowego: " << file_output << "\n";
            return 1;
        }
    
        ull n = g.getVerticesCount();
    
        out << "c Wyniki algorytmu Dijkstry\n";
        out << "p res sp ss dijkstra\n";
        out << "f " << file_graph << " " << file_sources << "\n";
        out << "g " << n << " " << g.getEdgeCount() << " 0 " << g.getMaxCost() << "\n"; 
    
        out << "t " << std::fixed << std::setprecision(2) << avg_ms << "\n\n";
    } else {
        std::vector<std::pair<ull, ull>> pairs = loadPairs(file_sources);
    
        auto start = std::chrono::high_resolution_clock::now();
    
        std::vector<ull> results;
        results.reserve(pairs.size());
    
        std::cout << "Read graph with " << g.getVerticesCount() << " vertices and max weight " << g.getMaxCost() << std::endl;
    
        switch (algorithm) {
            case 0:
                std::cout << "Algorithm: Dijkstra" << std::endl;
                break;
            case 1:
                std::cout << "Algorithm: Dial" << std::endl;
                break;
            case 2:
                std::cout << "Algorithm: Radixheap" << std::endl;
                break;
            default:
                break;
            }
    
        for (auto [u, v] : pairs) {
            switch (algorithm) {
            case 0:
                results.push_back(dijkstra_path(g, u, v));
                break;
            case 1:
                results.push_back(dial_path(g, u, v, g.getMaxCost()));
                break;
            case 2:
                results.push_back(radix_path(g, u, v));
                break;
            default:
                break;
            }
        }
    
        auto end = std::chrono::high_resolution_clock::now();
        double avg_ms = std::chrono::duration<double, std::milli>(end - start).count() / static_cast<double>(pairs.size());
    
        // ----------- zapis wyników -----------
        std::ofstream out(file_output);
        if (!out) {
            std::cerr << "Błąd: nie można otworzyć pliku wynikowego: " << file_output << "\n";
            return 1;
        }
    
        ull n = g.getVerticesCount();
    
        out << "c Wyniki algorytmu Dijkstry\n";
        out << "p res sp ss dijkstra\n";
        out << "f " << file_graph << " " << file_sources << "\n";
        out << "g " << n << " " << g.getEdgeCount() << " 0 " << g.getMaxCost() << "\n"; 
    
        out << "t " << std::fixed << std::setprecision(2) << avg_ms << "\n\n";

        for (size_t i = 0; i < pairs.size(); i++) {
            auto [u, v] = pairs[i];
            ull d = results[i];
            out << "q " << u+1 << " " << v+1 << " " << d << "\n";
        }
    }


    return 0;
}
