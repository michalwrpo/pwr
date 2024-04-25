import java.util.logging.Level;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;

public class GUIQuit extends Button
{
    public GUIQuit()
    {
        super("X");
        setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event)
            {
                Platform.exit();
                MyLogger.logger.log(Level.INFO, "Quit");            
            }
        }); 

    }    

            
}
