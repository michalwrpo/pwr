#include "graph.hpp"
#include "annealing.hpp"
#include "permutation.hpp"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <omp.h>
#include <print>
#include <sstream>
#include <vector>


int main(int argc, char** argv) {
    if (argc < 6) {
        std::println(stderr, "Usage: {} (1-3) FILE ATTEMPTS TEMPERATURE COOLING", argv[0]);
        return 1;
    }

    size_t attempts{};
    double starting_temperature{};
    double cooling_coefficient{};

    {
        std::stringstream ss{ argv[3]};
        ss >> attempts;
        ss << argv[4];
        ss >> starting_temperature;
        ss << argv[5];
        ss >> cooling_coefficient;
    }

    Graph g{ argv[2] };
    long best {};
    std::vector<size_t> solution(g.n, 0);

    size_t iterations {};
    long long sol_sum {};
    long long total_steps {};
    
    int (*f)(Permutation&, double, double, size_t);

    if (argv[1][0] == '1') {
        iterations = (g.n < 1000) ? g.n : 100;

        f = simulated_annealing;
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
            Permutation p{ g };
            int steps{ f(p, starting_temperature, cooling_coefficient, attempts) };
        
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

    std::println("Average solution: {}", static_cast<double>(sol_sum) / static_cast<double>(iterations));
    std::println("Average steps: {}", static_cast<double>(total_steps) / static_cast<double>(iterations));
    std::println("Best solution: {}", best);
    for (size_t x : solution) std::print("{} ", x);
    std::println("");

    return 0;
}