import java.util.List;
import java.util.logging.Level;

import javafx.scene.Scene;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/**
 * @brief assembles the GUI
 */
public class GUI 
{
    public GUI(Stage stage, List<String> inputs)
    {
        VBox vBox = new VBox();

        GUIGrid grid = MyInputHandler.makeGrid(inputs);

        grid.prefWidthProperty().bind(vBox.widthProperty());
        VBox.setVgrow(grid, Priority.ALWAYS);
        
        vBox.getChildren().addAll(grid);

        GUIMouseHandler.handleMouse(grid);

        Scene scene = new Scene(vBox, 800, 500);
    
        stage.setScene(scene);
        stage.setTitle("Colored Squares");
        stage.show();
        stage.setOnCloseRequest(event -> {
            System.exit(0);
        });
    
        MyLogger.logger.log(Level.INFO, "Created scene");
    }
}
