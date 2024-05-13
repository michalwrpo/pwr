import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Button;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

public class ShapeButton extends Button
{
    public ShapeButton(String name, Canvas canvas)
    {
        super(name);

        setPrefSize(50, 50);

        setFont(Font.font("sans serif", FontWeight.BOLD, 30));

        setOnAction(new EventHandler<ActionEvent>()
        {
            @Override
            public void handle(ActionEvent event)
            {
                
            }

        });

    }
}
