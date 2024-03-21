import java.util.ArrayList;

/**
 *@class PascalsTriangleRow 
 * 
 *@brief class containing methods to create nth row of Pascal's triangle
 * 
 */
public final class PascalsTriangleRow 
{
    private ArrayList<Integer> row;

    /**
     * @brief returns full nth row of Pascal's Triangle
     * 
     * @param n - should be nonnegative and smaller than 34
     * @return std::vector<int> of all binomials n over something
     */
    static public ArrayList<Integer> pascalsRow(int n) throws IllegalArgumentException
    {
        if (n < 0)
        {
            throw new IllegalArgumentException("parameter n should be nonnegative, got " + n);
        }
        
        if (n > 33)
        {
            throw new IllegalArgumentException("parameter n should be smaller than 34, got " + n);
        }
        
        ArrayList<Integer> nthRow = new ArrayList<Integer>();
        nthRow.add(1);
        
        for (int i = 0; i < n; i++)
        {
            nthRow.add((int) ( ((long)nthRow.get(i)) * ((long)(n - i)) / ((long) (i + 1))) );
        }
        
        return nthRow;
    }

    public PascalsTriangleRow(final int n) throws IllegalArgumentException
    {
        if (n < 0)
        {
            throw new IllegalArgumentException("parameter n should be nonnegative, got " + n);
        }
        
        if (n > 33)
        {
            throw new IllegalArgumentException("parameter n should be smaller than 34, got " + n);
        }

        row = pascalsRow(n);
    }

    public int mthElement(final int m) throws IllegalArgumentException
    {
        if (m < 0)
        {
            throw new IllegalArgumentException("parametr m should be nonnegative, got " + m);
        }

        int n = (int) row.size() - 1;

        if (m > n) 
        {
            throw new IllegalArgumentException("parametr m should be smaller or equal to n (" + n + "), got " + m);
        }
        return row.get(m);
    }
}
