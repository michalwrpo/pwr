import java.util.logging.Level;

import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.StrokeType;

public class ShapeTriangle extends Polygon implements IShape
{
    private double scale = 1;
    private double angle = 0;

    private boolean selected = false;

    public ShapeTriangle(double x1, double y1, double x2, double y2, double x3, double y3, Color color)
    {
        super(x1, y1, x2, y2, x3, y3);
        setFill(color);
    }

    public ShapeTriangle(double x1, double y1, double x2, double y2, double x3, double y3, Color color, double strokeWidth, Color strokeColor)
    {
        super(x1, y1, x2, y2, x3, y3);
        setFill(color);
        setStroke(strokeColor);
        setStrokeWidth(strokeWidth);
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
        return (getPoints().get(0) + getPoints().get(2) + getPoints().get(4)) / 3;
    }

    public final double getLocationY()
    {
        return (getPoints().get(1) + getPoints().get(3) + getPoints().get(5)) / 3;
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
        
        MyLogger.logger.log(Level.FINEST, "Triangle scaled: " + scale);
    }

    public final void rotate(double x)
    {
        angle += x/10;
        setRotate(angle);
    }
}
