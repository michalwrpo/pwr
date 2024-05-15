import java.util.ArrayList;
import java.util.logging.Level;

import javafx.scene.paint.Color;

/**
 * @brief generates rectangle
 */
public class RectangleGenerator implements IGenerator
{
    private ArrayList<Double[]> points = new ArrayList<Double[]>();

    RectangleGenerator()
    {

    }

    public final boolean isReady() 
    {
        if (points.size() == 2) 
            return true;
        else
            return false;

    }

    public final void addPoint(double x, double y)
    {
        if (isReady()) 
            points.clear();

        Double[] pair = {x, y};
        points.add(pair);            
    }

    public final ShapeRectangle generate() throws IndexOutOfBoundsException
    {
        if (isReady()) 
        {
            double leftX = Math.min(points.get(0)[0], points.get(1)[0]);
            double rightX = Math.max(points.get(0)[0], points.get(1)[0]);
            double topY = Math.min(points.get(0)[1], points.get(1)[1]);
            double bottomY = Math.max(points.get(0)[1], points.get(1)[1]);
            MyLogger.logger.log(Level.FINER, "Created a Rectangle");
            return new ShapeRectangle(leftX, topY, rightX - leftX , bottomY - topY, Color.rgb(0, 0, 0, 1.0));
        }
        else
            throw new IndexOutOfBoundsException("Not enough points were given");
    }

    public final ShapeRectangle ghost(double x, double y)
    {
        if (points.size() == 1)
        {
            double leftX = Math.min(points.get(0)[0], x);
            double rightX = Math.max(points.get(0)[0], x);
            double topY = Math.min(points.get(0)[1], y);
            double bottomY = Math.max(points.get(0)[1], y);
            return new ShapeRectangle(leftX, topY, rightX - leftX, bottomY - topY, Color.rgb(0, 0, 0, 0.65));
        }
        else
            return new ShapeRectangle(x, y, 3, 3, Color.rgb(0, 0, 0, 0.65));
    }
}
