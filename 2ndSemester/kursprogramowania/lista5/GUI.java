import java.util.logging.Level;

import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.ToolBar;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

/**
 * @brief assembles the GUI
 */
public class GUI 
{
    public GUI(Stage stage)
    {
        Pane canvas = new Pane();
        final BorderPane borderPane = new BorderPane();

        String saveFileName = "savefile.txt";

        GUIFileButton file = new GUIFileButton(canvas, saveFileName);

        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);

        ShapePair Circle = new ShapePair("Circle", new CircleGenerator());
        ShapePair Rectangle = new ShapePair("Rectangle", new RectangleGenerator());
        ShapePair Triangle = new ShapePair("Triangle", new TriangleGenerator());

        
        StateButton stateButton = new StateButton();
                
        
        GUIComboBox comboBox = new GUIComboBox(new ShapePair[]{Circle, Rectangle, Triangle});
        
        ToolBar toolBar = new ToolBar(file, new GUIInfoButton(), spacer, stateButton, comboBox);
        toolBar.setPrefHeight(33);
        toolBar.setPadding(new Insets(0, 10, 0, 10));
        
        
        borderPane.setCenter(canvas);
        borderPane.setTop(toolBar);
        
        
        Scene scene = new Scene(borderPane, 800, 500, Color.DARKGRAY);
        
        MouseHandler.handleMouse(canvas);
        KeyboardHandler.handleKeyboard(canvas, stateButton, saveFileName);
        
        stage.setScene(scene);
        stage.setTitle("Paint at home:");
        stage.show();
        
        MyLogger.logger.log(Level.INFO, "Created scene");    
    }
};