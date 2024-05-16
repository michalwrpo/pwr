import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.logging.Level;

import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.StrokeType;

/**
 * @brief Shape class corresponding to rectangle
 * 
 */
public class ShapeRectangle extends Rectangle implements IShape
{
    private static final long serialVersionUID = 513L;

    private boolean selected = false;

    public ShapeRectangle(final double cornerX, final double cornerY, final double width, final double height, final Color color)
    {
        super(width, height, Paint.valueOf(color.toString()));
        setX(cornerX);
        setY(cornerY);
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
        setTranslateX(x - getX() - getWidth()/2);
        setTranslateY(y - getY() - getHeight()/2);
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

        MyLogger.logger.log(Level.FINEST, "Rectangle scaled: " + getScaleX());
    }

    public final void rotate(final double x)
    {
        setRotate(getRotate() + x/10);
    }

    private void writeObject(ObjectOutputStream out) throws IOException
    {
        out.defaultWriteObject();

        out.writeDouble(getX());
        out.writeDouble(getY());
        out.writeDouble(getWidth());
        out.writeDouble(getHeight());

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
        double width = in.readDouble();
        double height = in.readDouble();

        double red = in.readDouble();
        double green = in.readDouble();
        double blue = in.readDouble();

        double rotate = in.readDouble();
        double scale = in.readDouble();

        setX(x);
        setY(y);
        setWidth(width);
        setHeight(height);

        setFill(new Color(red, green, blue, 1));

        setRotate(rotate);
        setScaleX(scale);
        setScaleY(scale);
    }
}
