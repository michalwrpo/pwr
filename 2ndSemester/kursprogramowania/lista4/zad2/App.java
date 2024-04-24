import java.util.ArrayList;
import java.util.logging.Level;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.control.ScrollPane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;
 

public class App extends Application 
{    
    @Override
    public void start(Stage stage) 
    {
        new GUI(stage);

        // VBox vBox = new VBox(0);
        
        // HBox toolBar = new HBox();
        // toolBar.setAlignment(Pos.TOP_RIGHT);
        
        // Button quit = new Button();
        // quit.setText("X");
        // quit.setOnAction((ActionEvent event) -> 
        //     {
        //         Platform.exit();
        //         MyLogger.logger.log(Level.INFO, "Quit");
        //     }
        //     );
            
        // toolBar.getChildren().add(quit);

        // ScrollPane scrollPane = new ScrollPane();
        // scrollPane.setFitToWidth(true);
        // scrollPane.setFitToHeight(true);
        
        // GridPane grid = new GridPane();
        // grid.setAlignment(Pos.TOP_CENTER);
        // grid.setHgap(100);
        // grid.setVgap(10);
        // grid.setPadding(new Insets(25, 25, 25, 25));
        // grid.setGridLinesVisible(true);
        
    
        // Button btn = new Button();
        // btn.setText("Generate");
        // grid.add(btn, 0, 2);
        // GridPane.setHalignment(btn, HPos.CENTER);
        
        
        // Text title = new Text("Pascal's Triangle Generator");
        // title.setFont(Font.font("sans serif", FontWeight.BOLD, 20));
        // grid.add(title, 0, 0);
        // GridPane.setHalignment(title, HPos.CENTER);
        
        
        // TextField triangleSize = new TextField();
        // grid.add(triangleSize, 0, 1);
        // GridPane.setHalignment(triangleSize, HPos.CENTER);
        
        // Text triangle = new Text("");
        // triangle.setTextAlignment(TextAlignment.CENTER);
        // triangle.setFont(Font.font("sans serif", FontWeight.NORMAL, 18));
        // grid.add(triangle, 0, 3);
        // GridPane.setHalignment(triangle, HPos.CENTER);

        // btn.setOnAction(new EventHandler<ActionEvent>() 
        // {
        //     @Override
        //     public void handle(ActionEvent event) 
        //     {
        //         MyLogger.logger.log(Level.FINE, "Generated a triangle");

        //         int n = Integer.parseInt(triangleSize.getText());
        //         String message = " ";
        //         for(int i = 0; i < n; i++)
        //         {
        //             ArrayList<Integer> row =  PascalsTriangleRow.pascalsRow(i);
        //             for (int j : row)
        //                 message += (j + "  ");
        //             message += "\n ";
        //         }
        //             triangle.setText(message);
        //             scrollPane.setHvalue(0.5);
        //     }
        // });

        // scrollPane.setContent(grid);
        // vBox.getChildren().addAll(toolBar, scrollPane);

        // Scene scene = new Scene(vBox, 300, 250);
        

        // primaryStage.setTitle("Pascal's Triangle");
        // primaryStage.setScene(scene);
        // primaryStage.show();

        // MyLogger.logger.log(Level.INFO, "Created scene");
    }
    public static void main(String[] args) {
        MyLogger.loggerConfig();
        launch(args);
    }
}