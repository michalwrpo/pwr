import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Rectangle;

public class ShapeRectangle extends Rectangle implements IShape
{
    public ShapeRectangle(double cornerX, double cornerY, double width, double height, Color color)
    {
        super(width, height, Paint.valueOf(color.toString()));
        setX(cornerX);
        setY(cornerY);
    }
}
