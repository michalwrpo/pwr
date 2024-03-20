#include <primes.hpp>

#include <string>
#include <cmath>
#include <vector>


std::vector<bool> Primes::sieve(const int n) noexcept(false)
{
    if (n <= 1)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter n should be greater than 1, got " + std::to_string(n));
    }
    
    std::vector<bool> primes = {false, false};

    for (int i = 2; i <= n; i++)
    {
        primes.push_back(true);
    }

    for (int i = 2; i <= static_cast<int>(std::floor(std::sqrt(static_cast<double>(n)))); i++)
    {
        if(primes[static_cast<size_t>(i)])
        {
            for (int j = i * i; j <= n; j += i)
                primes[static_cast<size_t>(j)] = false;
        }
    }
    
    return primes;
}

std::vector<int> Primes::primesList(const int n) noexcept(false)
{
    if (n <= 1)
    {
        throw std::invalid_argument(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " [" + __func__ + "] " + "parameter n should be greater than 1, got " + std::to_string(n));
    }

    std::vector<int> primesList;
    std::vector<bool> isPrime = Primes::sieve(n);

    for (int i = 2; i <= n; i++)
    {
        if (isPrime[static_cast<size_t>(i)])
        {
            primesList.push_back(i);
        }
    }
    return primesList;
    
}

