import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;

public class StateButton extends Button
{
    public StateButton()
    {
        super("State");

        setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event)
            {
                StateMachine.changeSelectDraw();
            }
        });
    }
}
