import java.util.ArrayList;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.control.ScrollPane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;
 

public class App extends Application {
    
    @Override
    public void start(Stage primaryStage) {
        Button btn = new Button();
        btn.setText("Generate");
        
        ScrollPane scrollPane = new ScrollPane();
        scrollPane.setFitToWidth(true);
        scrollPane.setFitToHeight(true);

        GridPane grid = new GridPane();
        grid.setAlignment(Pos.TOP_CENTER);
        grid.setHgap(100);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));
        grid.setGridLinesVisible(true);
        grid.add(btn, 0, 2);
        GridPane.setHalignment(btn, HPos.CENTER);
        
        Text title = new Text("Pascal's Triangle Generator");
        title.setFont(Font.font("sans serif", FontWeight.BOLD, 20));
        grid.add(title, 0, 0);
        GridPane.setHalignment(title, HPos.CENTER);
        
        
        TextField triangleSize = new TextField();
        grid.add(triangleSize, 0, 1);
        GridPane.setHalignment(triangleSize, HPos.CENTER);
        
        Text triangle = new Text("");
        triangle.setTextAlignment(TextAlignment.JUSTIFY);
        triangle.setFont(Font.font("sans serif", FontWeight.NORMAL, 18));
        grid.add(triangle, 0, 3);
        GridPane.setHalignment(triangle, HPos.CENTER);

        btn.setOnAction(new EventHandler<ActionEvent>() {
    
            @Override
            public void handle(ActionEvent event) {
                int n = Integer.parseInt(triangleSize.getText());
            String message = "";
            for(int i = 0; i < n; i++)
            {
                for (int k = 0; k < 2*(n - i); k++)
                {
                    message += " ";
                }
                ArrayList<Integer> row =  PascalsTriangleRow.pascalsRow(i);
                for (int j : row)
                    message += (j + "  ");
                message += "\n";
            }
                System.out.println(message);
                triangle.setText(message);
            }
        });
        
        scrollPane.setContent(grid);;

        Scene scene = new Scene(scrollPane, 300, 250);
        
        primaryStage.setTitle("Grid");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
    public static void main(String[] args) {
        launch(args);
    }
}