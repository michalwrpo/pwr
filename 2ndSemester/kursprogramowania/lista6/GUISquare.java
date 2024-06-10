import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.Region;

public class GUISquare extends Region
{
    private final LSquare lSquare;

    private final Runnable updater = new Runnable() 
    {
        @Override
        public void run()
        {
            setBackground(new Background(new BackgroundFill(lSquare.getColor(), new CornerRadii(0), new Insets(0))));
        }
    };
    
    public GUISquare(LSquare lSquare)
    {
        this.lSquare = lSquare;

        lSquare.setGUISquare(this);
        // to be changed
        setBackground(new Background(new BackgroundFill(lSquare.getColor(), new CornerRadii(0), new Insets(0))));

    }

    public final void update()
    {
        Platform.runLater(updater);
    }
}
