import javafx.geometry.Pos;
import javafx.scene.layout.HBox;

public class GUIHBar extends HBox
{
    public GUIHBar()
    {
        super(new GUIQuit());
        setAlignment(Pos.TOP_RIGHT);
    }
        
}
