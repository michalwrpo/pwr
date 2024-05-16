import javafx.event.EventHandler;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Pane;

/**
 * @brief class containing methods responsible for handling keyboard inputs
 */
public class KeyboardHandler 
{
    private KeyboardHandler() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }
    /**
     * @brief method responsible for adding handlers for shortcut keys 
     * 
     * @param canvas
     * @param stateButton
     * @param filename
     */
    public static void handleKeyboard(final Pane canvas, final StateButton stateButton, final String filename)
    {
        canvas.getScene().setOnKeyPressed(new EventHandler<KeyEvent>() 
        {
            @Override
            public void handle(KeyEvent event)
            {
                if (event.getCode() == KeyCode.SLASH) 
                {
                    stateButton.updateState();
                }
                else if (event.getCode() == KeyCode.S && event.isControlDown())
                {
                    SerializeShapes.serialize(canvas, filename);
                }
                else if (event.getCode() == KeyCode.O && event.isControlDown()) 
                {
                    SerializeShapes.deserialize(canvas, filename);    
                }
            }
        });
    }
}
