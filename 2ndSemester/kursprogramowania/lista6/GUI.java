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

        boolean inputCorrect = MyInputHandler.checkInputs(inputs);

        GUIGrid grid;

        if (inputCorrect)
        {
            int height = Integer.parseInt(inputs.get(0));
            int width = Integer.parseInt(inputs.get(1));

            double probability = Double.parseDouble(inputs.get(2));
            long delay = Long.parseLong(inputs.get(3));

            grid = new GUIGrid(height, width, probability, delay);
        }
        else
        {
            grid = new GUIGrid(10, 10, 0.5, 1000);
        }

        GUIToolbar toolbar = new GUIToolbar(grid);
        toolbar.prefWidthProperty().bind(vBox.widthProperty());
        

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
