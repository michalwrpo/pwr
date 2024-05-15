import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Node;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.layout.Pane;

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
                SerializeShapes.serialize(canvas.getChildren(), filename);
            }    
        });

        MenuItem open = new MenuItem("Open");
        open.setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event)
            {
                int childrenNum = canvas.getChildren().size();
                for (int i = 0; i < childrenNum; i++)
                {
                    canvas.getChildren().removeFirst();
                }
                ObservableList<Node> nodes = SerializeShapes.deserialize(filename);
                canvas.getChildren().addAll(nodes);
            }    
        });

        getItems().addAll(save, open);
    }
}
