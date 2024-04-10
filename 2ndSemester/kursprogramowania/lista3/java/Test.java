public final class Test 
{
    private Test() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }    
    
    public static void main(final String[] args)
    {
        TestCircle.testCircle();
        TestPentagon.testPentagon();
        TestHexagon.testHexagon();
        TestSquare.testSquare();
        TestRectangle.testRectangle();
        TestRhombus.testRhombus();
    }
}
