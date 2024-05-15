import java.util.logging.Level;

import javafx.event.EventHandler;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Shape;

public class MouseHandler 
{
    private static IGenerator generator = new CircleGenerator();
    
    /**
     * @brief handles mouse imputs
     * 
     * @param canvas
     */
    public static void handleMouse(Pane canvas)
    {
        canvas.setOnMouseClicked(new EventHandler<MouseEvent>() 
        {
            @Override
            public void handle(MouseEvent mouseEvent)
            {
                if (mouseEvent.getButton() == MouseButton.PRIMARY) 
                {
                    switch (StateMachine.getState()) 
                    {
                        case SELECT:
                            if (mouseEvent.getTarget() instanceof IShape) 
                            {
                                if (mouseEvent.isAltDown()) 
                                {
                                    MyLogger.logger.log(Level.FINE, "Removed " + mouseEvent.getTarget());
                                    canvas.getChildren().remove(mouseEvent.getTarget());    
                                }
                                else
                                {
                                IShape target = (IShape) mouseEvent.getTarget(); 
                                Selector.select(target);    
                                }
                            }
                            else
                            {
                                Selector.unselect();
                            }
                            break;
                        case DRAW:
                            generator.addPoint(mouseEvent.getX(), mouseEvent.getY());
                            if (generator.isReady()) 
                                canvas.getChildren().add(generator.generate()); 
                            break;
                    }
                }
                else if (mouseEvent.getButton() == MouseButton.SECONDARY && StateMachine.getState() == AppState.SELECT)
                {
                    if (mouseEvent.getTarget() instanceof IShape)
                    {
                        ColorPopUp.show(canvas.getScene().getWindow(), (IShape) mouseEvent.getTarget());
                    }
                }
            }    
        });

        canvas.setOnMouseMoved(new EventHandler<MouseEvent>() 
        {
            IShape ghost;
            @Override
            public void handle(MouseEvent mouseEvent)
            {
                if (StateMachine.getState() == AppState.DRAW) 
                {
                    canvas.getChildren().remove((Shape)ghost);
                    ghost = generator.ghost(mouseEvent.getX(), mouseEvent.getY());
                    Selector.setGhost(ghost);
                    
                    if (ghost != null)
                        canvas.getChildren().add((Shape)ghost);    
                }
                else
                    canvas.getChildren().remove((Shape)ghost);
            }    
        });

        canvas.setOnMouseDragged(new EventHandler<MouseEvent>() 
        {
            @Override
            public void handle(MouseEvent mouseEvent)
            {
                if (mouseEvent.getTarget() instanceof Shape && Selector.getSelected() == mouseEvent.getTarget()) 
                {
                    IShape target = (IShape) mouseEvent.getTarget();
                    target.move(mouseEvent.getX(), mouseEvent.getY());
                }
            }    
        });

        canvas.setOnScroll(new EventHandler<ScrollEvent>() 
        {
            @Override
            public void handle(ScrollEvent scrollEvent)
            {
                if (Selector.getSelected() != null) 
                {
                    if (scrollEvent.isControlDown()) 
                        Selector.getSelected().rotate(scrollEvent.getDeltaY());
                    else
                        Selector.getSelected().scale(scrollEvent.getDeltaY());                
                }
            }    
        });
    }

    public static final void setGenerator(IGenerator newGenerator)
    {
        generator = newGenerator;
    }

}
