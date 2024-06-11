import javafx.scene.layout.GridPane;
import javafx.scene.layout.Priority;

/**
 * @brief class creating GUI for LGrid
 */
public class GUIGrid extends GridPane 
{    
    private LGrid lGrid;

    public GUIGrid(int vSquares, int hSquares, double probability, long delay)
    {
        super();

        setVgap(0);
        setHgap(0);

        this.lGrid = new LGrid(vSquares, hSquares, probability, delay);
    
        for (int i = 0; i < vSquares; i ++)
        {
            for (int j = 0; j < hSquares; j ++)
            {
                GUISquare square = new GUISquare(lGrid.getSquares().get(i).get(j)); 
                setHgrow(square, Priority.ALWAYS);
                setVgrow(square, Priority.ALWAYS);
                add(square, j, i);
            }
        }
    }
}
