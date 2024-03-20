#ifndef PRIMES_HPP
#define PRIMES_HPP

#include <stdexcept>
#include <vector>

/**
 * @class Primes
 *
 * @brief Primes class is a statitc class containing only statis methods related to prime numbers
 */
class Primes
{
public:
    // class is full statis so delete constructor
    Primes() = delete;
    ~Primes() = delete;

    /**
     * @brief creates a vector of booleans, for each number from 0 to n tells if the number is prime
     * 
     * @param n - any number, but for numbers <= 1 an exception will be raised
     * @return std::vector<bool> - true for a prime, false otherwise 
     */
    static std::vector<bool> sieve(const int n) noexcept(false);

    /**
     * @brief creates a vector of primes between 2 and n
     * 
     * @param n - any number, but for numbers <= 1 an exception will be raise
     * @return std::vector<int> containing primes
     */
    static std::vector<int> primesList(const int n) noexcept(false);
};

#endif
