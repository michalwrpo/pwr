import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;

public class GUIInfoButton extends Button
{
    public GUIInfoButton()
    {
        super("Info");

        setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public final void handle(ActionEvent event)
            {
                GUIInfoPopup.showInfoPopup();
            }
        });
    }    
}
