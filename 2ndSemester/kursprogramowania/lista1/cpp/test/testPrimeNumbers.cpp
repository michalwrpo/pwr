#include <primeNumbers.hpp>

#include <cassert>
#include <stdexcept>

void testPrimeNumbers() noexcept(true);
static void testPrimeNumbersExceptions(const int n) noexcept(true);
static void testMthPrimeExceptions(const int m, const PrimeNumbers plist) noexcept(true);
static void testPrimeNumbersConstructor() noexcept(true);

static void testPrimeNumbersExceptions(const int n) noexcept(true)
{
    try
    {
        const auto primes = PrimeNumbers(n);
        (void)primes;

        assert(false);
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;
        assert(true);
    }
}

static void testMthPrimeExceptions(const int m, PrimeNumbers plist) noexcept(true)
{
    try
    {
        const int val = plist.mthprime(m);
        (void)val;

        assert(false);
    }
    catch(const std::invalid_argument& e)
    {
        (void)e;

        assert(true);
    }
    catch(const std::out_of_range& e)
    {
        (void)e;

        assert(true);
    }
}


static void testPrimeNumbersConstructor() noexcept(true)
{
    testPrimeNumbersExceptions(1);
    testPrimeNumbersExceptions(0);
    testPrimeNumbersExceptions(-1);
    testPrimeNumbersExceptions(-10000);

    {
        const PrimeNumbers ptest = PrimeNumbers(2);
        testMthPrimeExceptions(-1, ptest);
        testMthPrimeExceptions(-1000, ptest);
        testMthPrimeExceptions(1, ptest);
        testMthPrimeExceptions(10, ptest);
        testMthPrimeExceptions(1024, ptest);
    }
    {
        PrimeNumbers ptest = PrimeNumbers(20);
        testMthPrimeExceptions(8, ptest);
        assert(ptest.mthprime(7) == 19);
        assert(ptest.mthprime(0) == 2);
        assert(ptest.mthprime(2) == 5);
    }
    {
        PrimeNumbers ptest = PrimeNumbers(100);
        testMthPrimeExceptions(25, ptest);
        assert(ptest.mthprime(24) == 97);
        assert(ptest.mthprime(0) == 2);
        assert(ptest.mthprime(10) == 31);
    }

}

void testPrimeNumbers() noexcept(true)
{
    testPrimeNumbersConstructor();
}
