public final class TestCircle 
{
    private TestCircle() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    static private void testCircleExceptions(final double radius)
    {
        try
        {
            new Circle(radius);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    static public void testCircle()
    {
        {
            testCircleExceptions(0);
            testCircleExceptions(-100);
            testCircleExceptions(-1);
            testCircleExceptions(-12345678);
            testCircleExceptions(-20.48);
        }
        {
            Circle testCirc = new Circle(1);
            assert(Math.abs(testCirc.area() - 3.1415926535) < 0.00001);
            assert(Math.abs(testCirc.perimeter() - 6.2831853071) < 0.00001);
            assert(testCirc.name() == "Circle");
        }
        {
            Circle testCirc = new Circle(5);
            assert(Math.abs(testCirc.area() - 25 * 3.1415926535) < 0.00001);
            assert(Math.abs(testCirc.perimeter() - 5 * 6.2831853071) < 0.00001);
            assert(testCirc.name() == "Circle");
        }
        {
            Circle testCirc = new Circle(0.05);
            assert(Math.abs(testCirc.area() - 0.0025 * 3.1415926535) < 0.00001);
            assert(Math.abs(testCirc.perimeter() - 0.05 * 6.2831853071) < 0.00001);
            assert(testCirc.name() == "Circle");
        }
        {
            Circle testCirc = new Circle(123);
            assert(Math.abs(testCirc.area() - 15129 * 3.1415926535) < 0.00001);
            assert(Math.abs(testCirc.perimeter() - 123 * 6.2831853071) < 0.00001);
            assert(testCirc.name() == "Circle");
        }
    }
}
