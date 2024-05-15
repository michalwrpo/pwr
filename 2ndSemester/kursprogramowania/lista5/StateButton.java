import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;

public class StateButton extends Button
{
    public StateButton()
    {
        super(StateMachine.getState().toString());
        setPrefWidth(70);


        setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event)
            {
                updateState();
            }    
        });
    }

    public final void updateState()
    {
        StateMachine.changeSelectDraw();
        setText(StateMachine.getState().toString());    
    }
}
