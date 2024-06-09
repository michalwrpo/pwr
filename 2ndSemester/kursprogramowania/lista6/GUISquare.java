import javafx.geometry.Insets;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.Region;

public class GUISquare extends Region
{
    LSquare lSquare;
    
    public GUISquare(LSquare lSquare)
    {
        this.lSquare = lSquare;

        // to be changed
        setBackground(new Background(new BackgroundFill(lSquare.getColor(), new CornerRadii(0), new Insets(0))));

    }
}
