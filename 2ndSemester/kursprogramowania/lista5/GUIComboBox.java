import java.util.logging.Level;

import javafx.scene.control.ComboBox;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.util.Callback;

/**
 * @brief creates a combo box allowing to change shape type
 */
public class GUIComboBox extends ComboBox<ShapePair>
{
    public GUIComboBox(ShapePair[] pairs)
    {
        super();
        getItems().addAll(pairs);

        setCellFactory(new Callback<ListView<ShapePair>,ListCell<ShapePair>>() 
        {
            @Override
            public ListCell<ShapePair> call(ListView<ShapePair> p)
            {
                return new ListCell<ShapePair>() 
                {
                    @Override
                    protected void updateItem(ShapePair item, boolean empty)
                    {
                        super.updateItem(item, empty);

                        if (item == null || empty) 
                        {
                            setText(null);    
                        }
                        else
                        {
                            setText(item.getName());
                        }
                    }
                };
            }
        });

        setOnAction(e ->
        {
           MouseHandler.setGenerator(getValue().getGenerator()); 
           MyLogger.logger.log(Level.INFO, "Changed type to " + getValue().getName());
        });

    }
}
