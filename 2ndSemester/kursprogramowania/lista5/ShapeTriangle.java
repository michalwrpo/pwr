import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.logging.Level;

import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.StrokeType;

/**
 * @brief Shape class corresponding to triangle
 * 
 */
public class ShapeTriangle extends Polygon implements IShape
{
    private static final long serialVersionUID = 514L;

    private boolean selected = false;

    public ShapeTriangle(final double x1, final double y1, final double x2, final double y2, final double x3, final double y3, final Color color)
    {
        super(x1, y1, x2, y2, x3, y3);
        setFill(color);
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

    public final void setColor(final Color color)
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

    public final void move(final double x, final double y)
    {
        setTranslateX(x - (getPoints().get(0) + getPoints().get(2) + getPoints().get(4))/3);
        setTranslateY(y - (getPoints().get(1) + getPoints().get(3) + getPoints().get(5))/3);
    }

    public final void scale(final double y)
    {
        setScaleX(getScaleX() * (1 + y/1000));
        setScaleY(getScaleX() * (1 + y/1000));
        
        if (selected) 
        {
            setStrokeWidth(4 / getScaleX());
            getStrokeDashArray().removeFirst();
            getStrokeDashArray().add(5d / getScaleX());
        }

        MyLogger.logger.log(Level.FINEST, "Triangle scaled: " + getScaleX());
    }

    public final void rotate(final double x)
    {
        setRotate(getRotate() + x/10);
    }

    private void writeObject(ObjectOutputStream out) throws IOException
    {
        out.defaultWriteObject();

        for (int i = 0; i < 3; i++)
        {
            out.writeDouble(getPoints().get(2*i) + getTranslateX());
            out.writeDouble(getPoints().get(2*i + 1) + getTranslateY());
        }    

        out.writeDouble(((Color) getFill()).getRed());
        out.writeDouble(((Color) getFill()).getGreen());
        out.writeDouble(((Color) getFill()).getBlue());

        out.writeDouble(getRotate());
        out.writeDouble(getScaleX());
    }

    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException
    {
        in.defaultReadObject();

        for (int i = 0; i < 6; i++)
        {
            getPoints().add(in.readDouble());
        }

        double red = in.readDouble();
        double green = in.readDouble();
        double blue = in.readDouble();

        double rotate = in.readDouble();
        double scale = in.readDouble();

        setFill(new Color(red, green, blue, 1));

        setRotate(rotate);
        setScaleX(scale);
        setScaleY(scale);
    }
}
