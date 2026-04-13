#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include "graph.hpp"

#include <functional>
#include <vector>

class Permutation {
    public:
        std::vector<size_t> elements;
        long len;
        std::reference_wrapper<Graph> g;

        Permutation(Graph& graph);

        long invert_cost(size_t from, size_t to) const;
        void invert(size_t from, size_t to);

    private:
        Permutation() = delete;
};

#endif