#include <bit>

#include "bits.hpp"

std::size_t H(std::size_t x) {
    return static_cast<std::size_t>(std::popcount(x));
}

// Count zero bits in the first k bits
std::size_t Z(std::size_t x, std::size_t k) {
    return k - H(x);
}