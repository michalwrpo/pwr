import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.layout.Pane;

/**
 * @brief creates menu with Save and Open options
 */
public class GUIFileButton extends MenuButton
{
    public GUIFileButton(Pane canvas, String filename)
    {
        super("File");

        MenuItem save = new MenuItem("Save");
        save.setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event)
            {
                SerializeShapes.serialize(canvas, filename);
            }    
        });

        MenuItem open = new MenuItem("Open");
        open.setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event)
            {
                SerializeShapes.deserialize(canvas, filename);
            }    
        });

        getItems().addAll(save, open);
    }
}
