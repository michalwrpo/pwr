public final class TestRectangle 
{
    private TestRectangle() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }    

    static private void testRectangleExceptions(final double side1, final double side2)
    {
        try
        {
            new Rectangle(side1, side2);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }    

    static public void testRectangle()
    {
        {
            testRectangleExceptions(-100, 100);
            testRectangleExceptions(123, -123);
            testRectangleExceptions(-1, -1);
            testRectangleExceptions(0, 1);
            testRectangleExceptions(100, 0);
            testRectangleExceptions(-12345678, -12345678);
            testRectangleExceptions(-20.48, 40.96);
    
        }
        {
            Rectangle testRect = new Rectangle(1, 1);
            assert(Math.abs(testRect.area() - 1) < 0.00001);
            assert(Math.abs(testRect.perimeter() - 4) < 0.00001);
            assert(testRect.name() == "Rectangle");
        }
        {
            Rectangle testRect = new Rectangle(5, 4);
            assert(Math.abs(testRect.area() - 20) < 0.00001);
            assert(Math.abs(testRect.perimeter() - 18) < 0.00001);
            assert(testRect.name() == "Rectangle");
        }
        {
            Rectangle testRect = new Rectangle(0.05, 0.2);
            assert(Math.abs(testRect.area() - 0.01) < 0.00001);
            assert(Math.abs(testRect.perimeter() - 0.5) < 0.00001);
            assert(testRect.name() == "Rectangle");
        }
        {
            Rectangle testRect = new Rectangle(240, 0.13);
            assert(Math.abs(testRect.area() - 31.2) < 0.00001);
            assert(Math.abs(testRect.perimeter() - 480.26) < 0.00001);
            assert(testRect.name() == "Rectangle");
        }
    }
}
