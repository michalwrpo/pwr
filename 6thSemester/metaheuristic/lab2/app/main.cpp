#include "annealing.hpp"
#include "graph.hpp"
#include "permutation.hpp"
#include "taboo_search.hpp"

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

    size_t iterations {};
    long long sol_sum {};
    long long total_steps {};
    
    if (argv[1][0] == '1') {
        if (argc < 5) {
            std::println(stderr, "Usage: {} 1 FILE TEMPERATURE COOLING", argv[0]);
            return 1;
        }

        double starting_temperature{};
        double cooling_coefficient{};

        {
            std::stringstream ss{ argv[3]};
            ss >> starting_temperature;
            ss << argv[4];
            ss >> cooling_coefficient;
        }

        iterations = (g.n < 1000) ? g.n : 100;

        #pragma omp parallel
        {
            long thread_best = 0;
            std::vector<size_t> thread_solution(g.n, 0);
            long long thread_sol_sum = 0;
            long long thread_steps = 0;
            
            #pragma omp for
            for (size_t i = 0 ; i < iterations; ++i) {
                Permutation p{ g };
                int steps{ simulated_annealing(p, starting_temperature, cooling_coefficient, p.n) };
            
                if (p.len < thread_best || thread_best == 0) {
                    thread_best = p.len;
                    thread_solution = p.elements;
                }
        
                thread_sol_sum += p.len;
                thread_steps += steps;
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
    } else if (argv[1][0] == '2') {
        if (argc < 4) {
            std::println(stderr, "Usage: {} 2 FILE TENURE", argv[0]);
            return 1;
        }

        iterations = (g.n < 1000) ? g.n : 100;
        size_t taboo_tenure{};

        {
            std::stringstream ss{ argv[3]};
            ss >> taboo_tenure;
        }

        #pragma omp parallel
        {
            long thread_best = 0;
            std::vector<size_t> thread_solution(g.n, 0);
            long long thread_sol_sum = 0;
            long long thread_steps = 0;
            
            #pragma omp for
            for (size_t i = 0 ; i < iterations; ++i) {
                Permutation p{ g };
                size_t steps{ taboo_search(p, taboo_tenure) };
            
                if (p.len < thread_best || thread_best == 0) {
                    thread_best = p.len;
                    thread_solution = p.elements;
                }
        
                thread_sol_sum += p.len;
                thread_steps += steps;
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
    } else {
        std::println(stderr, "Unknown exercise: {}", argv[1]);
        return 1;
    }


    std::println("Average solution: {}", static_cast<double>(sol_sum) / static_cast<double>(iterations));
    std::println("Average steps: {}", static_cast<double>(total_steps) / static_cast<double>(iterations));
    std::println("Best solution: {}", best);
    for (size_t x : solution) std::print("{} ", x);
    std::println("");

    return 0;
}