import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.Border;
import javafx.scene.layout.BorderStroke;
import javafx.scene.layout.BorderStrokeStyle;
import javafx.scene.layout.BorderWidths;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.paint.Color;

/**
 * @brief GUI class responsible for creating toolbar
 */
public class GUIToolbar extends GridPane 
{
    public GUIToolbar(GUIGrid grid)
    {
        super();

        class ToolbarLabel extends Label
        {
            public ToolbarLabel(String text)
            {
                super(text);

                setTextFill(Color.rgb(230, 230, 230));
                setHalignment(this, HPos.RIGHT);
            }
        }

        class ToolbarButton extends Button
        {
            
            public ToolbarButton(String text)
            {
                super(text);

                setPrefWidth(125);
                setPrefHeight(27);

                setBackground(new Background(new BackgroundFill(Color.rgb(20, 20, 30), new CornerRadii(3), new Insets(0))));
                
                setTextFill(Color.rgb(230, 230, 230));

                setBorder(new Border(new BorderStroke(Color.rgb(240, 240, 240), BorderStrokeStyle.SOLID, new CornerRadii(3), BorderWidths.DEFAULT)));
            }
        }
        
        setVgap(5);
        setHgap(10);

        setPadding(new Insets(5, 10, 5, 20));

        ToolbarLabel widthLabel = new ToolbarLabel("Width");
        ToolbarLabel heightLabel = new ToolbarLabel("Height"); 

        ToolbarLabel probabilityLabel = new ToolbarLabel("Probability");
        ToolbarLabel delayLabel = new ToolbarLabel("Delay");

        add(widthLabel, 0, 0);
        add(heightLabel, 0, 1);

        add(probabilityLabel, 2, 0);
        add(delayLabel, 2, 1);

        TextField widthField = new TextField();
        TextField heightField = new TextField();

        TextField probabilityField = new TextField();
        TextField delayField = new TextField();

        add(widthField, 1, 0);
        add(heightField, 1, 1);

        add(probabilityField, 3, 0);
        add(delayField, 3, 1);
        
        Pane separator = new Pane();
        setHgrow(separator, Priority.ALWAYS);

        add(separator, 4, 0);

        Button clearButton = new ToolbarButton("Clear");
        Button startButton = new ToolbarButton("Start");

        startButton.setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event)
            {
                // grid.initialize((int)heightField.getText(), widthField.getText(), probabilityField.getText(), delayField.getText());
            }    
        });

        setHalignment(clearButton, HPos.RIGHT);
        setHalignment(startButton, HPos.RIGHT);        

        add(clearButton, 5, 0);
        add(startButton, 5, 1);

        setPrefHeight(75);

        setBackground(new Background(new BackgroundFill(Color.rgb(30, 30, 40), new CornerRadii(0), new Insets(0))));
    }
}
