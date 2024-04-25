import java.util.logging.Level;

import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class GUI 
{
    public GUI(Stage stage)
    {
        HBox toolBar = new GUIHBar();

        Text title = new GUIText("Pascal's Triangle Row Generator", 20, true);
        Text triangle = new GUIText("", 18, false);
        
        TextField inputField = new TextField();
        inputField.setAlignment(Pos.CENTER);

        TextField argumentField = new TextField();
        argumentField.setAlignment(Pos.CENTER);

        Button button = new GUIButton("Generate", inputField, argumentField, triangle);

        GridPane grid = new GUIGrid(title, inputField, argumentField, button, triangle);
        ScrollPane scrollPane = new GUIScrollPane(grid);

        VBox root = new VBox(toolBar, scrollPane); 

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("Bionomials Generator");
        stage.show();
        
        MyLogger.logger.log(Level.INFO, "Created scene");
    }    
}
