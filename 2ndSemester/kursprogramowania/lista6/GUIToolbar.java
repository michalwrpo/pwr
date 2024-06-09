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

public class GUIToolbar extends GridPane 
{
    public GUIToolbar()
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

        Label widthLabel = new ToolbarLabel("Width");
        Label heightLabel = new ToolbarLabel("Height"); 
        Label probabilityLabel = new ToolbarLabel("Probability");

        add(widthLabel, 0, 0);
        add(heightLabel, 0, 1);
        add(probabilityLabel, 0, 2);

        add(new TextField(), 1, 0);
        add(new TextField(), 1, 1);
        add(new TextField(), 1, 2);
        
        Pane separator = new Pane();
        setHgrow(separator, Priority.ALWAYS);

        add(separator, 2, 1);

        Button clearButton = new ToolbarButton("Clear");
        Button startButton = new ToolbarButton("Start");

        setHalignment(clearButton, HPos.RIGHT);
        setHalignment(startButton, HPos.RIGHT);        

        add(clearButton, 3, 1);
        add(startButton, 3, 2);

        setPrefHeight(100);

        setBackground(new Background(new BackgroundFill(Color.rgb(30, 30, 40), new CornerRadii(0), new Insets(0))));
    }
}
