import java.util.ArrayList;

/**
 * @class PrimeNumbers
 * 
 * @brief creates an object with vector of all primes smaller than n, has a method returning mth prime
 */
public final class PrimeNumbers {
    private ArrayList<Integer> primes;

    public PrimeNumbers(final int n) throws IllegalArgumentException
    {
        if (n < 2) 
        {
            throw new IllegalArgumentException("parameter n should be greater than 1, got " + n);
        }
        primes = Primes.primesList(n);
    }

    public int mthPrime(final int m) throws IllegalArgumentException
    {
        if (m < 0) 
        {
            throw new IllegalArgumentException("parameter m should be nonnegative");
        }

        int plength = primes.size();

        if (m > plength - 1) 
        {
            throw new IllegalArgumentException("parameter m should be smaller than the length of the primes vector (" + plength + "), got " + m);
        }

        return primes.get(m);
    }
}
