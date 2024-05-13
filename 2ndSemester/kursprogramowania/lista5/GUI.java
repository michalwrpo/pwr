import java.util.logging.Level;

import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.control.ToolBar;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class GUI 
{
    public GUI(Stage stage)
    {
        Pane canvas = new Pane();
        final BorderPane borderPane = new BorderPane();

        MenuButton file = new MenuButton("File");
        file.getItems().addAll(new MenuItem("Save"), new MenuItem("Open"));

        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);

        ShapePair Circle = new ShapePair("Circle", new CircleGenerator());
        ShapePair Rectangle = new ShapePair("Rectangle", new RectangleGenerator());
        ShapePair Triangle = new ShapePair("Triangle", new TriangleGenerator());

        
        StateButton stateButton = new StateButton();
                
        MouseHandler mouseHandler = new MouseHandler(canvas);

        GUIComboBox comboBox = new GUIComboBox(new ShapePair[]{Circle, Rectangle, Triangle}, mouseHandler);
        
        ToolBar toolBar = new ToolBar(file, spacer, stateButton, comboBox);
        toolBar.setPrefHeight(33);
        toolBar.setPadding(new Insets(0, 10, 0, 10));
        
        
        borderPane.setCenter(canvas);
        borderPane.setTop(toolBar);
        
        
        Scene scene = new Scene(borderPane, 800, 500, Color.DARKGRAY);
        
        stage.setScene(scene);
        stage.setTitle("Paint at home:");
        stage.show();
        
        MyLogger.logger.log(Level.INFO, "Created scene");    
    }
};