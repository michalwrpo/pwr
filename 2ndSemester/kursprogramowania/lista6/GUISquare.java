import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;

/**
 * @brief GUI for LSquare
 */
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

    /**
     * @brief updates the color of the square
     * 
     * @param newColor
     */
    public final void update(Color newColor)
    {
        if (newColor == null)
            color = lSquare.getColor();
        else
            color = newColor;

        Platform.runLater(updater);
    }

    @Override
    public final LSquare getLSquare()
    {
        return lSquare;
    }
}
