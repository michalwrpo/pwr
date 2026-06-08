#include "genetic.hpp"
#include "graph.hpp"
#include "permutation.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <omp.h>
#include <print>
#include <sstream>
#include <vector>


int main(int argc, char** argv) {

    if (argc < 3) {
        std::println(stderr, "Usage: {} (1-2) FILE [ARGS]", argv[0]);
        return 1;
    }

    Graph g{ argv[2] };

    long best {};
    std::vector<size_t> solution(g.n, 0);

    size_t iterations { 100 };
    long long sol_sum {};
    long long total_steps {};

    std::pair<Permutation, int> (*genetic)(Graph&, size_t, size_t, double) {};
    
    if (argv[1][0] == '1') {
        genetic = genetic_ox;
    } else if (argv[1][0] == '2') {
        genetic = genetic_pmx;
    } else if (argv[1][0] == '3') {
        genetic = genetic_meme;
    } else {
        std::println(stderr, "Unknown exercise: {}", argv[1]);
        return 1;
    }

    #pragma omp parallel
    {
        long thread_best = 0;
        std::vector<size_t> thread_solution(g.n, 0);
        long long thread_sol_sum = 0;
        long long thread_steps = 0;
        
        #pragma omp for
        for (size_t i = 0 ; i < iterations; ++i) {
            auto result{ genetic(g, 10, 10, 0.1 ) };
        
            if (result.first.len < thread_best || thread_best == 0) {
                thread_best = result.first.len;
                thread_solution = result.first.elements;
            }
    
            thread_sol_sum += result.first.len;
            thread_steps += result.second;
        }

        #pragma omp critical
        {
            if (thread_best < best || best == 0) {
                best = thread_best;
                solution = thread_solution;
            }

            sol_sum += thread_sol_sum;
            total_steps += thread_steps;
        }
    }


    std::println("Average solution: {}", static_cast<double>(sol_sum) / static_cast<double>(iterations));
    std::println("Average steps: {}", static_cast<double>(total_steps) / static_cast<double>(iterations));
    std::println("Best solution: {}", best);
    for (size_t x : solution) std::print("{} ", x);
    std::println("");

    return 0;
}