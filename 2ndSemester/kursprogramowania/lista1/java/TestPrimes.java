public final class TestPrimes 
{
    private TestPrimes() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    static private void testSieveException(final int n)
    {
        try
        {
            Primes.sieve(n);
            assert false: "Exception should be raised";
        }
        catch (final IllegalArgumentException e)
        {

        }
    }

    static private void testSieve()
    {
        testSieveException(0);
        testSieveException(1);
        testSieveException(-1);
        testSieveException(-100);

        assert Primes.sieve(5).get(0) == false;
        assert Primes.sieve(1000).get(0) == false;
        assert Primes.sieve(2).get(0) == false;
        assert Primes.sieve(5).get(4) == false;
        assert Primes.sieve(5).get(2) == true;
        assert Primes.sieve(2).get(2) == true;
        assert Primes.sieve(5).get(5) == true;
        assert Primes.sieve(1000).get(1000) == false;
    }

    static private void testPrimesListExceptions(final int n)
    {
        try
        {
            Primes.primesList(n);
            assert false: "Exception should be raised";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    static private void testPrimesList()
    {
        testPrimesListExceptions(0);
        testPrimesListExceptions(1);
        testPrimesListExceptions(-1);
        testPrimesListExceptions(-100);

        assert(Primes.primesList(5).get(0) == 2);
        assert(Primes.primesList(100).get(0) == 2);
        assert(Primes.primesList(5).get(2) == 5);
        assert(Primes.primesList(5).get(1) == 3);
        assert(Primes.primesList(100).get(19) == 71);
        assert(Primes.primesList(1000).get(99) == 541);
    }
    static public void testPrimes()
    {
        testSieve();
        testPrimesList();
    }
}
