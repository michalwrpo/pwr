import java.util.logging.Level;

import javafx.scene.control.ComboBox;

/**
 * @brief creates a combo box allowing to change shape type
 */
public class GUIComboBox extends ComboBox<String>
{
    public GUIComboBox(final ShapePair[] pairs)
    {
        super();
        for (ShapePair shapePair : pairs) 
        {
            getItems().add(shapePair.getName());
        }

        setOnAction(e ->
        {
            for (ShapePair shapePair : pairs) 
            {
                if (shapePair.getName() == getValue()) 
                {
                MouseHandler.setGenerator(shapePair.getGenerator());    
                }
            }
            MyLogger.logger.log(Level.INFO, "Changed type to " + getValue());
        });

    }
}
