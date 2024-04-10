public final class TestRhombus 
{
    private TestRhombus() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }    

    static private void testRhombusExceptions(final double side, final double angle)
    {
        try
        {
            new Rhombus(side, angle);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    static public void testRhombus()
    {
        {
            testRhombusExceptions(-100, 100);
            testRhombusExceptions(123, -123);
            testRhombusExceptions(-1, -1);
            testRhombusExceptions(0, 1);
            testRhombusExceptions(100, 0);
            testRhombusExceptions(12345678, 12345678);
            testRhombusExceptions(-20.48, 40.96);
    
        }
        {
            Rhombus testRho = new Rhombus(1, 90);
            assert(Math.abs(testRho.area() - 1) < 0.00001);
            assert(Math.abs(testRho.perimeter() - 4) < 0.00001);
            assert(testRho.name() == "Rhombus");
        }
        {
            Rhombus testRho = new Rhombus(5, 30);
            assert(Math.abs(testRho.area() - 12.5) < 0.00001);
            assert(Math.abs(testRho.perimeter() - 20) < 0.00001);
            assert(testRho.name() == "Rhombus");
        }
        {
            Rhombus testRho = new Rhombus(0.05, 60);
            assert(Math.abs(testRho.area() - 0.00216506) < 0.00001);
            assert(Math.abs(testRho.perimeter() - 0.2) < 0.00001);
            assert(testRho.name() == "Rhombus");
        }
        {
            Rhombus testRho = new Rhombus(1.23, 22);
            assert(Math.abs(testRho.area() - 0.566742) < 0.00001);
            assert(Math.abs(testRho.perimeter() - 4.92) < 0.00001);
            assert(testRho.name() == "Rhombus");
        }
    }
}
