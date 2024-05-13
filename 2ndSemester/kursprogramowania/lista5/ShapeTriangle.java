import java.util.logging.Level;

import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.StrokeType;

public class ShapeTriangle extends Polygon implements IShape
{
    private double scale = 1;

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
        setLayoutX(x);
        setLayoutY(y);
    }

    public final void scale(double y)
    {
        scale = scale * (1 + y/1000);
        setScaleX(scale);
        setScaleY(scale);
        MyLogger.logger.log(Level.FINEST, "Scale: " + scale);
    }
}
