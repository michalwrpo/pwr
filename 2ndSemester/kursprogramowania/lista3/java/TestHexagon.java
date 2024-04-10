public final class TestHexagon 
{
    private TestHexagon() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }    

    static private void testHexagonExceptions(final double side)
    {
        try
        {
            new Hexagon(side);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }    

    static public void testHexagon()
    {
        {
            testHexagonExceptions(-100);
            testHexagonExceptions(-1);
            testHexagonExceptions(0);
            testHexagonExceptions(-12345678);
            testHexagonExceptions(-20.48);
        }
        {
            Hexagon testHex = new Hexagon(1);
            assert(Math.abs(testHex.area() - 2.5980762113) < 0.00001);
            assert(Math.abs(testHex.perimeter() - 6) < 0.00001);
            assert(testHex.name() == "Hexagon");
        }
        {
            Hexagon testHex = new Hexagon(5);
            assert(Math.abs(testHex.area() - 25 * 2.5980762113) < 0.00001);
            assert(Math.abs(testHex.perimeter() - 30) < 0.00001);
            assert(testHex.name() == "Hexagon");
        }
        {
            Hexagon testHex = new Hexagon(0.05);
            assert(Math.abs(testHex.area() - 0.0025 * 2.5980762113) < 0.00001);
            assert(Math.abs(testHex.perimeter() - 0.30) < 0.00001);
            assert(testHex.name() == "Hexagon");
        }
        {
            Hexagon testHex = new Hexagon(123);
            assert(Math.abs(testHex.area() - 15129 * 2.5980762113) < 0.00001);
            assert(Math.abs(testHex.perimeter() - 738) < 0.00001);
            assert(testHex.name() == "Hexagon");
        }
    }
}
