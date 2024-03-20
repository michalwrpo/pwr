#include <primeNumbers.hpp>



PrimeNumbers::PrimeNumbers(int n) noexcept(false)
{   
    if (n < 2)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter n should be greater than 1, got " + std::to_string(n));
    
    primes = Primes::primesList(n);
}

int PrimeNumbers::mthprime(int m) noexcept(false)
{
    if (m < 0)
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter n should be nonnegative, got " + std::to_string(m));

    int plenght = static_cast<int>(primes.size());

    if (m > plenght - 1)
        throw std::out_of_range(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter m should be smaller than length of the primes vector (" + std::to_string(plenght) + "), got " + std::to_string(m));

    return primes[static_cast<size_t>(m)];
}
