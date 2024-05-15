import javafx.event.EventHandler;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Pane;

public class KeyboardHandler 
{
    public static void handleKeyboard(Pane canvas, StateButton stateButton, String filename)
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
