import javafx.event.EventHandler;
import javafx.scene.input.MouseEvent;

/**
 * @brief class handling mouse inputs
 */
public class GUIMouseHandler 
{
    /**
     * @brief handles mouse inputs
     * 
     * @param grid
     */
    public static void handleMouse(GUIGrid grid)
    {
        grid.setOnMouseClicked(new EventHandler<MouseEvent>() 
        {
            @Override
            public void handle(MouseEvent mouseEvent)
            {
                if (mouseEvent.getTarget() instanceof IGUIField)
                {                    
                    ((IGUIField) mouseEvent.getTarget()).getLSquare().changeState();
                }
            }    
        });
    }
}
