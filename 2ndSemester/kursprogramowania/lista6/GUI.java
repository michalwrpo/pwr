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
    public GUI(Stage stage)
    {
        VBox vBox = new VBox();
        GUIToolbar toolbar = new GUIToolbar();
        toolbar.prefWidthProperty().bind(vBox.widthProperty());
        
        GUIGrid grid = new GUIGrid(10, 10);

        grid.prefWidthProperty().bind(vBox.widthProperty());
        VBox.setVgrow(grid, Priority.ALWAYS);

        vBox.getChildren().addAll(toolbar, grid);

        

        Scene scene = new Scene(vBox, 800, 500);
    
        stage.setScene(scene);
        stage.setTitle("Colored Squares");
        stage.show();
    
        MyLogger.logger.log(Level.INFO, "Created scene");
    }
}
