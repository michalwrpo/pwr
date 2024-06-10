import java.util.ArrayList;


public class LGrid 
{
    // private final int vSquares;
    // private final int hSquares;
    
    private final Object locker = new Object();

    private ArrayList<ArrayList<LSquare>> squares = new ArrayList<ArrayList<LSquare>>();
    
    public LGrid(int vSquares, int hSquares, double probability, long delay)
    {
        // this.vSquares = vSquares;
        // this.hSquares = hSquares;

        for (int i = 0; i < vSquares; i++)
        {
            ArrayList<LSquare> list = new ArrayList<LSquare>();

            for (int j = 0; j < hSquares; j++)
            {
                list.add(new LSquare(this, probability, delay, i * hSquares + j));
            }
    
            squares.add(list);
        }

        for (int i = 0; i < vSquares; i ++)
        {
            for (int j = 0; j < hSquares; j++)
            {
                squares.get(i).get(j).addNeighbors(squares.get((i - 1 + hSquares) % hSquares).get(j), 
                                                   squares.get(i).get((j + 1) % vSquares), 
                                                   squares.get((i + 1) % hSquares).get(j),
                                                   squares.get(i).get((j - 1 + vSquares) % vSquares));
                
                squares.get(i).get(j).start();
            }
        }
    }

    public final ArrayList<ArrayList<LSquare>> getSquares()
    {
        return squares;
    }

    public final Object getLocker()
    {
        return locker;
    }
}
