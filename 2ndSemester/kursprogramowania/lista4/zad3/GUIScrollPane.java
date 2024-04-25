import javafx.scene.control.ScrollPane;
import javafx.scene.layout.GridPane;

public class GUIScrollPane extends ScrollPane
{
    public GUIScrollPane(GridPane grid)
    {
        super(grid);
        
        setFitToHeight(true);
        setFitToWidth(true);

        setHvalue(0.5);
    }
}
