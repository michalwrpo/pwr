import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.logging.Level;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.StrokeType;

public class ShapeCircle extends Circle implements IShape
{
    private static final long serialVersionUID = 512L;

    private boolean selected = false;

    public ShapeCircle(double centerX, double centerY, double radius, Color color)
    {
        super(centerX, centerY, radius, color);
    }

    public final void select()
    {
        setStroke(Color.LIME);
        setStrokeWidth(4 / getScaleX());
        setStrokeType(StrokeType.CENTERED);
        getStrokeDashArray().add(5d / getScaleX());

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
        setCenterX(x);
        setCenterY(y);
    }

    public final void scale(double y)
    {
        setScaleX(getScaleX() * (1 + y/1000));
        setScaleY(getScaleX() * (1 + y/1000));

        if (selected) 
        {
            setStrokeWidth(4 / getScaleX());
            getStrokeDashArray().removeFirst();
            getStrokeDashArray().add(5d / getScaleX());
        }

        MyLogger.logger.log(Level.FINEST, "Circle scaled: " + getScaleX());
    }

    public final void rotate(double x)
    {
        setRotate(getRotate() + x/10);
    }

    private void writeObject(ObjectOutputStream out) throws IOException
    {
        out.defaultWriteObject();

        out.writeDouble(getCenterX());
        out.writeDouble(getCenterY());
        out.writeDouble(getRadius());

        out.writeDouble(((Color) getFill()).getRed());
        out.writeDouble(((Color) getFill()).getGreen());
        out.writeDouble(((Color) getFill()).getBlue());

        out.writeDouble(getRotate());
        out.writeDouble(getScaleX());
    }

    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException
    {
        in.defaultReadObject();

        double x = in.readDouble();
        double y = in.readDouble();
        double radius = in.readDouble();

        double red = in.readDouble();
        double green = in.readDouble();
        double blue = in.readDouble();

        double rotate = in.readDouble();
        double scale = in.readDouble();

        setCenterX(x);
        setCenterY(y);
        setRadius(radius);

        setFill(new Color(red, green, blue, 1));

        setRotate(rotate);
        setScaleX(scale);
        setScaleY(scale);
    }

}
