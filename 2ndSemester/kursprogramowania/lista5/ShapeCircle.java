import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class ShapeCircle extends Circle implements IShape
{
    // private double centerX;
    // private double centerY;
    // private double radius;

    public ShapeCircle(double centerX, double centerY, double radius, Color color)
    {
        super(centerX, centerY, radius, color);
    }

}
