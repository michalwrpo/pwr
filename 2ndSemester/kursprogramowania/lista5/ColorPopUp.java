import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.ColorPicker;
import javafx.scene.paint.Color;
import javafx.stage.Popup;
import javafx.stage.Window;

/**
 * @brief static class creating a popup that allows to change shapes color 
 */
public class ColorPopUp
{
    private ColorPopUp() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    private static final ColorPicker colorPicker = new ColorPicker(Color.BLACK);
    private static final Popup popup = new Popup();

    private static boolean initialized = false;

    private static final void initialize()
    {
        popup.getContent().add(colorPicker);
        initialized = true;
    }

    /**
     * @brief shows the popup with ColorPicker
     * 
     * @param window
     * @param target
     */
    public static final void show(Window window, IShape target)
    {
        if (!initialized)
        {
            initialize();
        }
        
        colorPicker.setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event)
            {
                target.setColor(colorPicker.getValue());
                hide();
            }    
        });

        popup.show(window, target.getAbsoluteX(), target.getAbsoluteY());
        colorPicker.show();
    }

    /**
     * @brief hides the popup
     */
    public static final void hide()
    {
        popup.hide();
    }

}
