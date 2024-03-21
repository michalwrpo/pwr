public final class TestPrimeNumbers 
{
    private TestPrimeNumbers() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    static private void testPrimeNumbersExceptions(final int n)
    {
        try
        {
            final PrimeNumbers val = new PrimeNumbers(n);
            assert false: "Exception should be raised";
        }
        catch( final IllegalArgumentException e)
        {

        }
    }

    static private void testMthPrimeExceptions(final int m, PrimeNumbers plist)
    {
        try
        {
            plist.mthPrime(m);
            assert(false);
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    static private void testPrimeNumbersConstructor()
    {
        testPrimeNumbersExceptions(1);
        testPrimeNumbersExceptions(0);
        testPrimeNumbersExceptions(-1);
        testPrimeNumbersExceptions(-10000);

        {
            PrimeNumbers ptest = new PrimeNumbers(2);
            testMthPrimeExceptions(-1, ptest);
            testMthPrimeExceptions(-1000, ptest);
            testMthPrimeExceptions(1, ptest);
            testMthPrimeExceptions(10, ptest);
            testMthPrimeExceptions(1024, ptest);
        }
        {
            PrimeNumbers ptest = new PrimeNumbers(20);
            testMthPrimeExceptions(8, ptest);
            assert ptest.mthPrime(7) == 19;            
            assert ptest.mthPrime(0) == 2;            
            assert ptest.mthPrime(2) == 5;
        }
        {
            PrimeNumbers ptest = new PrimeNumbers(100);
            testMthPrimeExceptions(25, ptest);
            assert ptest.mthPrime(24) == 97;            
            assert ptest.mthPrime(0) == 2;            
            assert ptest.mthPrime(10) == 31;            
        }
    }

    static public void testPrimeNumbers()
    {
        testPrimeNumbersConstructor();
    }
}
