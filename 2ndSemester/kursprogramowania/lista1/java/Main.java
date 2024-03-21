public final class Main
{
    private Main() throws InstantiationError
    {
        throw new InstantiationError("This is a static class!");
    }

    public static void main(final String[] args)
    {
        if (args.length == 0)
        {
            System.out.println("Usage: java Main <number> ...");
            return;
        }

        PrimeNumbers p = null;

        try 
        {
            final int plength = Integer.parseInt(args[0]);
            p = new PrimeNumbers(plength);
        } 
        catch (IllegalArgumentException e) 
        {
            System.err.println("Invalid Argument Error: " + e.getMessage());
            System.exit(1);
        }

        for (int i = 1; i < args.length; i++)
        {
            try
            {
                final int argNumber = Integer.parseInt(args[i]);
                final int prime = p.mthPrime(argNumber);

                System.out.println(argNumber + " -> " + prime);
            }
            catch (final NumberFormatException e)
            {
                System.err.println(args[i] + " -> Invalid Argument Error: " + e.toString());
            }
            catch (final IllegalArgumentException e)
            {
                System.err.println(args[i] + " -> Invalid Argument Error: " + e.toString());
            }
        }
    }
}