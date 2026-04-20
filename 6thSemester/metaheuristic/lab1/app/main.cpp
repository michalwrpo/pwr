#include "graph.hpp"
#include "local_search.hpp"
#include "mst.hpp"
#include "permutation.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <omp.h>
#include <print>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::println(stderr, "Usage: {} (1-3) FILE", argv[0]);
        return 1;
    }

    Graph g{ argv[2] };
    long best {};
    std::vector<size_t> solution(g.n, 0);

    size_t iterations {};
    long long sol_sum {};
    long long total_steps {};
    
    int (*f)(Permutation&);

    if (argv[1][0] == '1') {
        iterations =
            (g.n < 1000) ? g.n :
            (g.n < 2000) ? 60 : 
            (g.n < 5000) ? 6 : 2;

        f = local_search_all;
    } else if (argv[1][0] == '2') {
        iterations = (g.n < 5000) ? g.n : 500;

        f = local_search_random;
    } else if (argv[1][0] == '3') {
        iterations = (g.n < 500) ? g.n :
        static_cast<size_t>(std::sqrt(g.n)) + 1;

        f = local_search_all;

        Prim(g);
    } else {
        std::println(stderr, "Unknown exercise: {}", argv[1]);
        return 1;
    }

    std::println(stderr, "Doing {} iterations.", iterations);

    #pragma omp parallel
    {
        long thread_best = 0;
        std::vector<size_t> thread_solution(g.n, 0);
        long long thread_sol_sum = 0;
        long long thread_steps = 0;
        
        #pragma omp for
        for (size_t i = 0 ; i < iterations; ++i) {
            std::print(stderr, "{} ", i);
            Permutation p{ g };
            int steps{ f(p) };
        
            if (p.len < thread_best || thread_best == 0) {
                thread_best = p.len;
                thread_solution = p.elements;
            }
    
            thread_sol_sum += p.len;
            thread_steps += steps;
            std::println("{} {}", p.len, steps);
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


    std::println(stderr, "");
    if (argv[1][0] == '3') std::println("MST weight: {}", g.mst_weight);
    std::println("Average solution: {}", static_cast<double>(sol_sum) / static_cast<double>(iterations));
    std::println("Average steps: {}", static_cast<double>(total_steps) / static_cast<double>(iterations));
    std::println("Best solution: {}", best);
    for (size_t x : solution) std::print("{} ", x);
    std::println("");

    return 0;
}