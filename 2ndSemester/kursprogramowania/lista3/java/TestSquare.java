public final class TestSquare 
{
    private TestSquare() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }    

    static private void testSquareExceptions(final double side)
    {
        try
        {
            new Square(side);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }        

    static public void testSquare()
    {
        {
            testSquareExceptions(-100);
            testSquareExceptions(-1);
            testSquareExceptions(0);
            testSquareExceptions(-12345678);
            testSquareExceptions(-20.48);
        }
        {
            Square testSqr = new Square(1);
            assert(Math.abs(testSqr.area() - 1) < 0.00001);
            assert(Math.abs(testSqr.perimeter() - 4) < 0.00001);
            assert(testSqr.name() == "Square");
        }
        {
            Square testSqr = new Square(5);
            assert(Math.abs(testSqr.area() - 25) < 0.00001);
            assert(Math.abs(testSqr.perimeter() - 20) < 0.00001);
            assert(testSqr.name() == "Square");
        }
        {
            Square testSqr = new Square(0.05);
            assert(Math.abs(testSqr.area() - 0.0025) < 0.00001);
            assert(Math.abs(testSqr.perimeter() - 0.2) < 0.00001);
            assert(testSqr.name() == "Square");
        }
        {
            Square testSqr = new Square(123);
            assert(Math.abs(testSqr.area() - 15129) < 0.00001);
            assert(Math.abs(testSqr.perimeter() - 492) < 0.00001);
            assert(testSqr.name() == "Square");
        }
    }
}
