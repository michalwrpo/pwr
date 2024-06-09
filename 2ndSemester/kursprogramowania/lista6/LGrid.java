import java.util.ArrayList;


public class LGrid 
{
    // private final int vSquares;
    // private final int hSquares;
    
    private final Object locker = new Object();

    private ArrayList<ArrayList<LSquare>> squares = new ArrayList<ArrayList<LSquare>>();
    
    public LGrid(int vSquares, int hSquares)
    {
        // this.vSquares = vSquares;
        // this.hSquares = hSquares;

        for (int i = 0; i < vSquares; i++)
        {
            ArrayList<LSquare> list = new ArrayList<LSquare>();
            for (int j = 0; j < hSquares; j++)
            {
                list.add(new LSquare(locker));
            }
    
            squares.add(list);
        }
    }

    public final ArrayList<ArrayList<LSquare>> getSquares()
    {
        return squares;
    }
}
