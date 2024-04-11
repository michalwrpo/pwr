public final class TestFigure 
{
    private TestFigure() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    private static void testCircleExceptions(final double radius)
    {
        try
        {
            double val = Figure.Single.CIRCLE.area(radius);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
        try
        {
            double val = Figure.Single.CIRCLE.perimeter(radius);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }
    
    private static void testSquareExceptions(final double side)
    {
        try
        {
            double val = Figure.Single.SQUARE.area(side);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
        try
        {
            double val = Figure.Single.SQUARE.perimeter(side);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    private static void testPentagonExceptions(final double side)
    {
        try
        {
            double val = Figure.Single.PENTAGON.area(side);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
        try
        {
            double val = Figure.Single.PENTAGON.perimeter(side);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    private static void testHexagonExceptions(final double side)
    {
        try
        {
            double val = Figure.Single.HEXAGON.area(side);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
        try
        {
            double val = Figure.Single.HEXAGON.perimeter(side);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    private static void testRectangleExceptions(final double side1, final double side2)
    {
        try
        {
            double val = Figure.Dual.RECTANGLE.area(side1, side2);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
        try
        {
            double val = Figure.Dual.RECTANGLE.perimeter(side1, side2);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    private static void testRhombusExceptions(final double side, final double angle)
    {
        try
        {
            double val = Figure.Dual.RHOMBUS.area(side, angle);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
        try
        {
            double val = Figure.Dual.RHOMBUS.perimeter(side, angle);
            assert false: "Exception should be raised.";
        }
        catch(final IllegalArgumentException e)
        {

        }
    }

    private static void testExceptions()
    {
        {
            testCircleExceptions(0);
            testCircleExceptions(-1);
            testCircleExceptions(-1234);
            testCircleExceptions(-2.56);
        }
        {
            testSquareExceptions(0);
            testSquareExceptions(-1);
            testSquareExceptions(-1234);
            testSquareExceptions(-2.56);
        }
        {
            testPentagonExceptions(0);
            testPentagonExceptions(-1);
            testPentagonExceptions(-1234);
            testPentagonExceptions(-2.56);
        }
        {
            testHexagonExceptions(0);
            testHexagonExceptions(-1);
            testHexagonExceptions(-1234);
            testHexagonExceptions(-2.56);
        }
        {
            testRectangleExceptions(0, 1);
            testRectangleExceptions(-1, 0);
            testRectangleExceptions(2.43, -1234);
            testRectangleExceptions(-2.56, 1.76);
        }
        {
            testRhombusExceptions(0, 123);
            testRhombusExceptions(-1, 0);
            testRhombusExceptions(-1234, 123);
            testRhombusExceptions(7, -2.56);
            testRhombusExceptions(4, 180);
            testRhombusExceptions(2, 1234);
        }
    }

    private static void testCircle(final double radius, final double expectedPerimeter, final double expectedArea)
    {
        assert(Math.abs(Figure.Single.CIRCLE.area(radius) - expectedArea) < 0.00001);
        assert(Math.abs(Figure.Single.CIRCLE.perimeter(radius) - expectedPerimeter) < 0.00001);
    }

    private static void testSquare(final double side, final double expectedPerimeter, final double expectedArea)
    {
        assert(Math.abs(Figure.Single.SQUARE.area(side) - expectedArea) < 0.00001);
        assert(Math.abs(Figure.Single.SQUARE.perimeter(side) - expectedPerimeter) < 0.00001);
    }

    private static void testPentagon(final double side, final double expectedPerimeter, final double expectedArea)
    {
        assert(Math.abs(Figure.Single.PENTAGON.area(side) - expectedArea) < 0.00001);
        assert(Math.abs(Figure.Single.PENTAGON.perimeter(side) - expectedPerimeter) < 0.00001);
    }

    private static void testHexagon(final double side, final double expectedPerimeter, final double expectedArea)
    {
        assert(Math.abs(Figure.Single.HEXAGON.area(side) - expectedArea) < 0.00001);
        assert(Math.abs(Figure.Single.HEXAGON.perimeter(side) - expectedPerimeter) < 0.00001);
    }

    private static void testRectangle(final double side1, final double side2, final double expectedPerimeter, final double expectedArea)
    {
        assert(Math.abs(Figure.Dual.RECTANGLE.area(side1, side2) - expectedArea) < 0.00001);
        assert(Math.abs(Figure.Dual.RECTANGLE.perimeter(side1, side2) - expectedPerimeter) < 0.00001);
    }

    private static void testRhombus(final double side, final double angle, final double expectedPerimeter, final double expectedArea)
    {
        assert(Math.abs(Figure.Dual.RHOMBUS.area(side, angle) - expectedArea) < 0.00001);
        assert(Math.abs(Figure.Dual.RHOMBUS.perimeter(side, angle) - expectedPerimeter) < 0.00001);
    }
    
    private static void testFigures()
    {
        {
            testCircle(1, 6.2831853071, 3.1415926535); 
            testCircle(0.05, 0.05 * 6.2831853071, 0.0025 * 3.1415926535);
            testCircle(5, 5 * 6.2831853071, 25 * 3.1415926535);
            testCircle(123, 123 * 6.2831853071, 15129 * 3.1415926535);
        }
        {
            testSquare(1, 4, 1);
            testSquare(0.05, 0.2, 0.0025);
            testSquare(5, 20, 25);
            testSquare(123, 492, 15129);
        }
        {
            testPentagon(1, 5, 1.7204774005);
            testPentagon(0.05, 0.25, 0.0025 * 1.7204774005);
            testPentagon(5, 25, 25 * 1.7204774005);
            testPentagon(123, 615, 15129 * 1.7204774005);
        }
        {
            testHexagon(1, 6, 2.5980762113);
            testHexagon(0.05, 0.3 , 0.0025 * 2.5980762113);
            testHexagon(5, 30, 25 * 2.5980762113);
            testHexagon(123, 738, 15129 * 2.5980762113);

        }
        {
            testRectangle(1, 2, 6, 2);
            testRectangle(0.05, 0.3, 0.7, 0.015);
            testRectangle(12.23, 4, 32.46, 48.92);
            testRectangle(123, 20.48, 286.96, 2519.04);
        }
        {
            testRhombus(1, 90, 4, 1);
            testRhombus(5, 30, 20, 12.5);
            testRhombus(0.05, 60, 0.2, 0.00216506);
            testRhombus(1.23, 22, 4.92, 0.566742);
        }
    }

    public static void testFigure()
    {
        testExceptions();
        testFigures();

        assert(Figure.Single.CIRCLE.figureName().equals("Circle"));
        assert(Figure.Single.SQUARE.figureName().equals("Square"));
        assert(Figure.Single.PENTAGON.figureName().equals("Pentagon"));
        assert(Figure.Single.HEXAGON.figureName().equals("Hexagon"));
        assert(Figure.Dual.RECTANGLE.figureName().equals("Rectangle"));
        assert(Figure.Dual.RHOMBUS.figureName().equals("Rhombus"));
    }

}
