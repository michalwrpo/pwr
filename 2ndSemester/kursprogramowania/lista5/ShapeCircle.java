import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.StrokeType;

public class ShapeCircle extends Circle implements IShape
{
    // private double centerX;
    // private double centerY;
    // private double radius;

    public ShapeCircle(double centerX, double centerY, double radius, Color color)
    {
        super(centerX, centerY, radius, color);
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
        setCenterX(x);
        setCenterY(y);
    }

    

}
