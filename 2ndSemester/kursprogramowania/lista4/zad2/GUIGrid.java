import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.layout.GridPane;

public class GUIGrid extends GridPane
{
    public GUIGrid(Node title, Node inputField, Node button, Node resultsField)
    {
        super();
    
        setAlignment(Pos.TOP_CENTER);
        setHgap(100);
        setVgap(10);
        setPadding(new Insets(25, 25, 25, 25));

        add(title, 0, 0);
        add(inputField, 0, 1);
        add(button, 0, 2);
        add(resultsField, 0, 3);

        setHalignment(title, HPos.CENTER);
        setHalignment(inputField, HPos.CENTER);
        setHalignment(button, HPos.CENTER);
        setHalignment(resultsField, HPos.CENTER);
    }

}
