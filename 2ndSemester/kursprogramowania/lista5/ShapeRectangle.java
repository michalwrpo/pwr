import java.util.logging.Level;

import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.StrokeType;

public class ShapeRectangle extends Rectangle implements IShape
{
    private double scale = 1;

    public ShapeRectangle(double cornerX, double cornerY, double width, double height, Color color)
    {
        super(width, height, Paint.valueOf(color.toString()));
        setX(cornerX);
        setY(cornerY);
    }

    public final void select()
    {
        setStroke(Color.LIME);
        setStrokeWidth(4);
        setStrokeType(StrokeType.CENTERED);
        getStrokeDashArray().add(5d);
    }

    public final void unselect()
    {
        setStroke(null);
    }

    public final void move(double x, double y)
    {
        setX(x);
        setY(y);
    }

    public final void scale(double y)
    {
        scale = scale * (1 + y/1000);
        setScaleX(scale);
        setScaleY(scale);
        MyLogger.logger.log(Level.FINEST, "Scale: " + scale);
    }
}
