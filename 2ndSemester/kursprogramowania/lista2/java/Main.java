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

        PascalsTriangleRow p = null;

        try
        {
            final int rowNumber = Integer.parseInt(args[0]);
            p = new PascalsTriangleRow(rowNumber);
        }
        catch (final IllegalArgumentException e)
        {
            System.err.println("Invalid Argument Error: " + e.getMessage());
            System.exit(1);
        }

        for (int i = 1; i < args.length; i++)
        {
            try{
                final int argNumber = Integer.parseInt(args[i]);
                final int nChooseM = p.mthElement(argNumber);

                System.out.println(argNumber + " -> " + nChooseM);
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
