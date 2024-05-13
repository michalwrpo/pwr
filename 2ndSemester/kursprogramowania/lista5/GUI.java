import java.util.logging.Level;

import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.control.ToolBar;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class GUI 
{
    public GUI(Stage stage)
    {
        Pane canvas = new Pane();
        final BorderPane borderPane = new BorderPane();
        final HBox hBox = new HBox(10);

        hBox.setPrefHeight(50);
        hBox.setAlignment(Pos.CENTER_RIGHT);

        MenuButton file = new MenuButton("File");
        file.getItems().addAll(new MenuItem("Save"), new MenuItem("Open"));

        ToolBar toolBar = new ToolBar(file);
        toolBar.setPrefHeight(33);
        toolBar.setPadding(new Insets(0, 10, 0, 10));

        borderPane.setTop(toolBar);
        borderPane.setCenter(canvas);
        
        CircleGenerator g = new CircleGenerator();
        
        canvas.setOnMouseClicked(new EventHandler<MouseEvent>() 
        {
            @Override
            public void handle(MouseEvent mouseEvent)
            {
                g.addPoint(mouseEvent.getX(), mouseEvent.getY());
                if (g.isReady()) 
                {
                    canvas.getChildren().add(g.generate()); 
                }
            }    
        });
        
        Scene scene = new Scene(borderPane, 800, 500, Color.DARKGRAY);

        stage.setScene(scene);
        stage.setTitle("Paint at home:");
        stage.show();
        
        MyLogger.logger.log(Level.INFO, "Created scene");
    }    
}
