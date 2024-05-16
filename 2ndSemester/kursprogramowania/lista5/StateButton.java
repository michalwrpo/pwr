import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;

/**
 * @brief class creating button responsible for changing program state
 */
public final class StateButton extends Button
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

    /**
     * @brief method changing the state and updating the button
     */
    public final void updateState()
    {
        StateMachine.changeSelectDraw();
        setText(StateMachine.getState().toString());    
    }
}
