#include <iostream>
#include <fstream>
#include <string>

#include "glpk.hpp"

/**
 * Generates GNU MathProg (GMPL) code to solve the MaxFlow problem.
 * @param g   The graph object.
 * @param out The output stream (e.g., std::cout or a std::ofstream).
 */
void generate_mathprog(const Graph& g, std::ostream& out) {
    // ==========================================
    // 1. MODEL SECTION
    //    Defines the algebraic model
    // ==========================================
    
    out << "# =========================================================\n";
    out << "# Maximum Flow Problem - GMPL Model\n";
    out << "# Generated for Hypercube Graph (k=" << g.k << ")\n";
    out << "# =========================================================\n\n";

    out << "/* --- SETS AND PARAMETERS --- */\n";
    out << "set V;                       # Set of all nodes\n";
    out << "set E within V cross V;      # Set of directed edges\n";
    out << "param Capacity{E} >= 0;      # Capacity for each edge\n";
    out << "param Source symbolic in V;\n";
    out << "param Sink symbolic in V;\n\n";

    out << "/* --- DECISION VARIABLES --- */\n";
    out << "var Flow{(u,v) in E} >= 0, <= Capacity[u,v];\n\n";

    out << "/* --- OBJECTIVE FUNCTION --- */\n";
    out << "maximize Total_Flow:\n";
    out << "    sum {(Source, v) in E} Flow[Source, v];\n\n";

    out << "/* --- CONSTRAINTS --- */\n";
    out << "subject to Conservation {u in V diff {Source, Sink}}:\n";
    out << "    sum {(v,u) in E} Flow[v,u] = sum {(u,w) in E} Flow[u,w];\n\n";

    // ==========================================
    // 2. DATA SECTION
    //    Populates the model with specific graph data
    // ==========================================
    
    out << "data;\n\n";

    out << "/* --- GRAPH TOPOLOGY --- */\n";
    
    // In this graph structure:
    // Source = 0 (all 0 bits)
    // Sink = 2^k - 1 (all 1 bits)
    std::size_t source_node = 0;
    std::size_t sink_node = (1 << g.k) - 1;

    out << "param Source := " << source_node << ";\n";
    out << "param Sink := " << sink_node << ";\n\n";

    // Define Set V (Nodes 0 to 2^k - 1)
    out << "set V :=";
    for (std::size_t i = 0; i < g.n; ++i) {
        if (i % 16 == 0) out << "\n  "; // formatting
        out << i << " ";
    }
    out << ";\n\n";

    // Define Edges and Capacities
    out << "param: E: Capacity := \n";
    
    for (std::size_t u = 0; u < g.adj.size(); ++u) {
        for (const auto& edge : g.adj[u]) {
            if (edge.capacity > 0) {
                out << "  " << u << " " << edge.to << " " << edge.capacity << "\n";
            }
        }
    }
    out << ";\n\n";

    out << "end;\n";
}