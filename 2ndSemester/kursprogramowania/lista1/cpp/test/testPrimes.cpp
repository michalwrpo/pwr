#include <primes.hpp>

#include <cassert>
#include <stdexcept>

void testPrimes() noexcept(true);
static void testSieveExceptions(const int n) noexcept(true);
static void testSieve() noexcept(true);
static void testPrimesListExceptions(const int n) noexcept(true);
static void testPrimesList() noexcept(true);


static void testSieveExceptions(const int n) noexcept(true)
{
    try
    {
        const std::vector<bool> val = Primes::sieve(n);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;

        assert(true);
    }
} 

static void testSieve() noexcept(true)
{
    testSieveExceptions(0);
    testSieveExceptions(1);
    testSieveExceptions(-1);
    testSieveExceptions(-100);

    assert(Primes::sieve(5)[0] == false && "sieve(5)[0] == false");
    assert(Primes::sieve(1000)[0] == false);
    assert(Primes::sieve(2)[0] == false);
    assert(Primes::sieve(5)[4] == false);
    assert(Primes::sieve(5)[2] == true);
    assert(Primes::sieve(2)[2] == true);
    assert(Primes::sieve(5)[5] == true);
    assert(Primes::sieve(1000)[1000] == false);
    // assert(Primes::sieve(1234567892)[1234567892] == false );
}

static void testPrimesListExceptions(const int n) noexcept(true)
{
    try
    {
        const std::vector<int> val = Primes::primesList(n);
        (void)val;

        assert(false && "Exception should be raised");
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;

        assert(true);
    }
    
}


static void testPrimesList() noexcept(true)
{
    testPrimesListExceptions(0);
    testPrimesListExceptions(1);
    testPrimesListExceptions(-1);
    testPrimesListExceptions(-100);

    assert(Primes::primesList(5)[0] == 2);
    assert(Primes::primesList(100)[0] == 2);
    assert(Primes::primesList(5)[2] == 5);
    assert(Primes::primesList(5)[1] == 3);
    assert(Primes::primesList(100)[19] == 71);    
    assert(Primes::primesList(1000)[99] == 541);


}

void testPrimes() noexcept(true)
{
    testSieve();
    testPrimesList();
}
