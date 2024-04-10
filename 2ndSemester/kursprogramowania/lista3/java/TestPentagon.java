public final class TestPentagon 
{
    private TestPentagon() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }    

    static private void testPentagonExceptions(final double side)
    {
        try
        {
            new Pentagon(side);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    static public void testPentagon() 
    {
        {
            testPentagonExceptions(-100);
            testPentagonExceptions(-1);
            testPentagonExceptions(0);
            testPentagonExceptions(-12345678);
            testPentagonExceptions(-20.48);
        }
        {
            Pentagon testPenta = new Pentagon(1);
            assert(Math.abs(testPenta.area() - 1.7204774005) < 0.00001);
            assert(Math.abs(testPenta.perimeter() - 5) < 0.00001);
            assert(testPenta.name() == "Pentagon");
        }
        {
            Pentagon testPenta = new Pentagon(5);
            assert(Math.abs(testPenta.area() - 25 * 1.7204774005) < 0.00001);
            assert(Math.abs(testPenta.perimeter() - 25) < 0.00001);
            assert(testPenta.name() == "Pentagon");
        }
        {
            Pentagon testPenta = new Pentagon(0.05);
            assert(Math.abs(testPenta.area() - 0.0025 * 1.7204774005) < 0.00001);
            assert(Math.abs(testPenta.perimeter() - 0.25) < 0.00001);
            assert(testPenta.name() == "Pentagon");
        }
        {
            Pentagon testPenta = new Pentagon(1.23);
            assert(Math.abs(testPenta.area() - 1.5129 * 1.7204774005) < 0.00001);
            assert(Math.abs(testPenta.perimeter() - 6.15) < 0.00001);
            assert(testPenta.name() == "Pentagon");
        }
    }
}
