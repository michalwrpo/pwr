import java.util.logging.Level;

import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.control.ToolBar;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;
import javafx.scene.shape.Shape;
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

        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);

        ComboBox<String> comboBox = new ComboBox<String>();
        comboBox.getItems().addAll("Circle", "Triangle", "Rectangle");

        ToolBar toolBar = new ToolBar(file, spacer, comboBox);
        toolBar.setPrefHeight(33);
        toolBar.setPadding(new Insets(0, 10, 0, 10));
        

        borderPane.setCenter(canvas);
        borderPane.setTop(toolBar);
        
        IGenerator g = new CircleGenerator();
        
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
        canvas.setOnMouseMoved(new EventHandler<MouseEvent>() 
        {
            Shape ghost;
            @Override
            public void handle(MouseEvent mouseEvent)
            {
                canvas.getChildren().remove(ghost);
                ghost = g.ghost(mouseEvent.getX(), mouseEvent.getY());
                canvas.getChildren().add(ghost);
            }    
        });
        
        Scene scene = new Scene(borderPane, 800, 500, Color.DARKGRAY);

        stage.setScene(scene);
        stage.setTitle("Paint at home:");
        stage.show();
        
        MyLogger.logger.log(Level.INFO, "Created scene");
    }    
}
