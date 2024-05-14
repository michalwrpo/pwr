import java.util.logging.Level;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.StrokeType;

public class ShapeCircle extends Circle implements IShape
{
    // private double centerX;
    // private double centerY;
    // private double radius;
    private double scale = 1;
    private double angle = 0;

    private boolean selected = false;

    public ShapeCircle(double centerX, double centerY, double radius, Color color)
    {
        super(centerX, centerY, radius, color);
    }

    public final void select()
    {
        setStroke(Color.LIME);
        setStrokeWidth(4 / scale);
        setStrokeType(StrokeType.CENTERED);
        getStrokeDashArray().add(5d / scale);

        selected = true;
    }

    public final void unselect()
    {
        setStroke(null);
        getStrokeDashArray().removeFirst();

        selected = false;
    }

    public final void setColor(Color color)
    {
        setFill(color);
    }

    public final double getLocationX()
    {
        return getCenterX();
    }

    public final double getLocationY()
    {
        return getCenterY();
    }

    public final double getAbsoluteX()
    {
        return localToScreen(getBoundsInLocal()).getMinX() + localToScreen(getBoundsInLocal()).getWidth()/2;
    }

    public final double getAbsoluteY()
    {
        return localToScreen(getBoundsInLocal()).getMinY() + localToScreen(getBoundsInLocal()).getHeight()/2;
    }

    public final void move(double x, double y)
    {
        setCenterX(x);
        setCenterY(y);
    }

    public final void scale(double y)
    {
        scale = scale * (1 + y/1000);
        setScaleX(scale);
        setScaleY(scale);

        if (selected) 
        {
            setStrokeWidth(4 / scale);
            getStrokeDashArray().removeFirst();
            getStrokeDashArray().add(5d / scale);
        }
        
        MyLogger.logger.log(Level.FINEST, "Circle scaled: " + scale);
    }

    public final void rotate(double x)
    {
        angle += x/10;
        setRotate(angle);
    }

}
