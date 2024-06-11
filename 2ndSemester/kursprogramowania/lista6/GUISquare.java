import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;

public class GUISquare extends Region implements IGUIField
{
    private final LSquare lSquare;

    private Color color;

    private final Runnable updater = new Runnable() 
    {
        @Override
        public void run()
        {
            setBackground(new Background(new BackgroundFill(color, new CornerRadii(0), new Insets(0))));
        }
    };
    
    public GUISquare(LSquare lSquare)
    {
        this.lSquare = lSquare;
        this.color = lSquare.getColor();

        lSquare.setGUISquare(this);

        setBackground(new Background(new BackgroundFill(color, new CornerRadii(0), new Insets(0))));
    }

    public final void update(Color newColor)
    {
        updateColor(newColor);
        Platform.runLater(updater);
    }

    @Override
    public final LSquare getLSquare()
    {
        return lSquare;
    }

    public final void updateColor(Color newColor)
    {
        if (newColor == null)
            color = lSquare.getColor();
        else
            color = newColor;
    }
}
