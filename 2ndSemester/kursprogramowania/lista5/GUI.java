import java.util.logging.Level;


import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class GUI 
{
    public GUI(Stage stage)
    {
        Canvas canvas = new Canvas(250, 250);
        VBox vBox = new VBox(10, canvas);
        vBox.setAlignment(Pos.CENTER);

        GraphicsContext gc = canvas.getGraphicsContext2D();

        gc.setFill(Color.BLUE);
        gc.fillRect(75, 75, 100, 100);

        Scene scene = new Scene(vBox, 800, 500, Color.DARKGRAY);
        stage.setScene(scene);
        stage.setTitle("Paint at home:");
        stage.show();

        MyLogger.logger.log(Level.INFO, "Created scene");
    }    
}
