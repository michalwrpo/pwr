import java.util.logging.Level;

import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.StrokeType;

public class ShapeRectangle extends Rectangle implements IShape
{
    private double scale = 1;
    private double angle = 0;

    private boolean selected = false;

    public ShapeRectangle(double cornerX, double cornerY, double width, double height, Color color)
    {
        super(width, height, Paint.valueOf(color.toString()));
        setX(cornerX);
        setY(cornerY);
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
        return getX() + getWidth()/2;
    }

    public final double getLocationY()
    {
        return getY() + getHeight()/2;
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
        setTranslateX(x - getLocationX());
        setTranslateY(y - getLocationY());
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

        MyLogger.logger.log(Level.FINEST, "Rectangle scaled: " + scale);
    }

    public final void rotate(double x)
    {
        angle += x/10;
        setRotate(angle);
    }
}
