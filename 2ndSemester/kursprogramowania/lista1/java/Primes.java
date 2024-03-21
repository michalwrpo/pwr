import java.util.ArrayList;

/**
 * @class Primes
 * 
 * @brief Primes class is a statitc class containing only statis methods related to prime numbers
 */
public final class Primes 
{
    private Primes() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    /**
     * @brief creates a vector of booleans, for each number from 0 to n tells if the number is prime
     * 
     * @param n - any number, but for numbers <= 1 an exception will be raised
     * @return std::vector<bool> - true for a prime, false otherwise 
     */
    public static ArrayList<Boolean> sieve(final int n) throws IllegalArgumentException
    {
        if (n <= 1) 
        {
            throw new IllegalArgumentException("parameter n should be greater than 1, got " + n);
        }

        ArrayList<Boolean> primes = new ArrayList<Boolean>();
        primes.add(false);
        primes.add(false);

        for (int i = 2; i <= n; i++)
        {
            primes.add(true);
        }

        for (int i = 2; i <= Math.floor(Math.sqrt(n)); i++)
        {
            if (primes.get(i)) 
            {
                for (int j = i * i; j <= n; j += i)
                {
                    primes.set(j, false);
                }
            }
        }
        return primes;
    }

    /**
     * @brief creates a vector of primes between 2 and n
     * 
     * @param n - any number, but for numbers <= 1 an exception will be raise
     * @return std::vector<int> containing primes
     */
    public static ArrayList<Integer> primesList(final int n) throws IllegalArgumentException
    {
        if (n <= 1) 
        {
            throw new IllegalArgumentException("parameter n should be greater than 1, got " + n);
        }

        ArrayList<Integer> plist = new ArrayList<Integer>();
        ArrayList<Boolean> isPrime = sieve(n);

        for (int i = 2; i <= n; i++)
        {
            if (isPrime.get(i))
            {
                plist.add(i);
            }
        }
        
        return plist;
    }
}
