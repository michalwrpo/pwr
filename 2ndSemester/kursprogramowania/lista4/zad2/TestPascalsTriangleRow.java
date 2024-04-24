public final class TestPascalsTriangleRow 
{
    private TestPascalsTriangleRow() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    static private void testPascalsRowExceptions(final int n)
    {
        try
        {
            PascalsTriangleRow.pascalsRow(n);
            assert false : "Exception should be raised";
        }
        catch (final IllegalArgumentException e)
        {

        }
    }    

    static private void testPascalsRow()
    {
        testPascalsRowExceptions(-1);
        testPascalsRowExceptions(34);
        testPascalsRowExceptions(1000);
        testPascalsRowExceptions(-123);

        assert PascalsTriangleRow.pascalsRow(1).get(0) == 1;
        assert PascalsTriangleRow.pascalsRow(1).get(1) == 1;
        assert PascalsTriangleRow.pascalsRow(2).get(1) == 2;
        assert PascalsTriangleRow.pascalsRow(4).get(2) == 6;

        assert PascalsTriangleRow.pascalsRow(20).get(20) == 1;
        assert PascalsTriangleRow.pascalsRow(20).get(19) == 20;
        assert PascalsTriangleRow.pascalsRow(20).get(18) == 190;
        assert PascalsTriangleRow.pascalsRow(20).get(2) == 190;
    }

    static private void testPascalsTriangleRowExceptions(final int n)
    {
        try
        {
            new PascalsTriangleRow(n);
            assert false: "Exception should be raised";
        }
        catch (final IllegalArgumentException e)
        {

        }
    }

    static private void testMthElementExceptions(final int n, PascalsTriangleRow prow)
    {
        try
        {
            prow.mthElement(n);
            assert false : "Exception should be raised";
        }
        catch (final IllegalArgumentException e)
        {

        }
    }   

    static private void testPascalsTriangleRowGenerator()
    {
        {
            testPascalsTriangleRowExceptions(-1);
            testPascalsTriangleRowExceptions(35);
            testPascalsTriangleRowExceptions(100000);
            testPascalsTriangleRowExceptions(-123);
        }
        {
            PascalsTriangleRow ptest = new PascalsTriangleRow(2);
            testMthElementExceptions(-1, ptest);
            testMthElementExceptions(-123, ptest);
            testMthElementExceptions(3, ptest);
            testMthElementExceptions(12345678, ptest);
        }
        {
            PascalsTriangleRow ptest = new PascalsTriangleRow(10);
            testMthElementExceptions(11, ptest);
            assert ptest.mthElement(0) == 1;
            assert ptest.mthElement(1) == 10;
            assert ptest.mthElement(3) == 120;
        }
        {
            PascalsTriangleRow ptest = new PascalsTriangleRow(33);
            assert ptest.mthElement(33) == 1;
            assert ptest.mthElement(32) == 33;
            assert ptest.mthElement(16) == 1166803110;
            assert ptest.mthElement(0) == 1;

        }
    }

    static public void testPascalsTriangleRow()
    {
        testPascalsTriangleRowGenerator();
        testPascalsRow();
    }
}
