#ifndef POLYNOMIAL_REDUCE_HPP
#define POLYNOMIAL_REDUCE_HPP

#include "polynomial.hpp"

#include <iostream>
#include <vector>

template <size_t N>
std::vector<Polynomial<double, N>> reduce(
    const Polynomial<double, N>& f, 
    const std::vector<Polynomial<double, N>> G
) {
    std::vector<Polynomial<double, N>> coeffs(G.size() + 1);
    for (auto& poly : coeffs) {
        poly.comp = f.comp;
        poly.perm = f.perm;
    }
    Polynomial<double, N> r{ f };
    
    for (size_t i{ 0 }; i < G.size(); ++i) {
        const Polynomial<double, N>& g = G[i];

        size_t j{ r.exponents.size() };

        while (j > 0) {
            --j;

            const std::array<int, N>& exp{ r.exponents[j] };

            if (mono_divisible(exp, g.LT())) {
                Polynomial<double, N> q{ {{mono_divide(exp, g.LT()), r.coeffs[exp] / g.LC()}}, r.perm, r.comp };
                r = r - (q * g);
                coeffs[i] = coeffs[i] + q;
                j = r.exponents.size();
            }
        }
    }

    coeffs[G.size()] = r;

    return coeffs;
}

#endif // POLYNOMIAL_REDUCE_HPP