#ifndef PRIME_NUMBERS_HPP
#define PRIME_NUMBERS_HPP

#include <vector>

#include <primes.hpp>

/**
 * @class PrimeNumbers
 * 
 * @brief creates an object with vector of all primes smaller than n, has a method returning mth prime
 * 
 */
class PrimeNumbers
{
private:
    std::vector<int> primes;

public:

    PrimeNumbers() = delete;

    PrimeNumbers(int n) noexcept(false);
    
    /**
     * @brief returns mth primes if its smaller than n
     * 
     * @param m - integer, throws an exception for negative numbers
     * @return int - mth prime if its smaller than n
     */
    int mthprime(int m) noexcept(false);
};

#endif
