import java.util.logging.Level;

import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.StrokeType;

public class ShapeTriangle extends Polygon implements IShape, java.io.Serializable
{
    private double x1;
    private double y1;

    private double x2;
    private double y2;

    private double x3;
    private double y3;    

    private double colorRed;
    private double colorGreen;
    private double colorBlue;    

    private double scale = 1;
    private double angle = 0;

    private boolean selected = false;

    public ShapeTriangle(double x1, double y1, double x2, double y2, double x3, double y3, Color color)
    {
        super(x1, y1, x2, y2, x3, y3);
        setFill(color);

        this.x1 = x1;
        this.y1 = y1;

        this.x2 = x2;
        this.y2 = y2;

        this.x3 = x3;
        this.y3 = y3;        
        
        this.colorRed = color.getRed();
        this.colorGreen = color.getGreen();
        this.colorBlue = color.getBlue();
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
        setTranslateX(x - (x1 + x2 + x3)/3);
        setTranslateY(y - (y1 + y2 + y3)/3);
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
