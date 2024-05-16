import java.util.ArrayList;
import java.util.logging.Level;

import javafx.scene.paint.Color;

/**
 * @brief generates circle
 * 
 */
public class CircleGenerator implements IGenerator
{
    private ArrayList<Double[]> points = new ArrayList<Double[]>();

    public CircleGenerator()
    {

    }

    public final boolean isReady() 
    {
        if (points.size() == 2) 
            return true;
        else
            return false;

    }

    public final void addPoint(final double x, final double y)
    {
        if (isReady()) 
            points.clear();

        Double[] pair = {x, y};
        points.add(pair);            
    }

    public final ShapeCircle generate() throws IndexOutOfBoundsException
    {
        if (isReady()) 
        {
            MyLogger.logger.log(Level.FINER, "Created a Circle");
            return new ShapeCircle(points.get(0)[0], points.get(0)[1], Math.sqrt(Math.pow(points.get(0)[0] - points.get(1)[0], 2) + Math.pow(points.get(0)[1] - points.get(1)[1], 2)), Color.rgb(0, 0, 0, 1.0));
        }
        else
            throw new IndexOutOfBoundsException("Not enough points were given");
    }

    public final ShapeCircle ghost(final double x, final double y)
    {
        if (points.size() == 1) 
            return new ShapeCircle(points.get(0)[0], points.get(0)[1], Math.sqrt(Math.pow(points.get(0)[0] - x, 2) + Math.pow(points.get(0)[1] - y, 2)), Color.rgb(0, 0, 0, 0.65));
        else
            return new ShapeCircle(x, y, 1, Color.rgb(0, 0, 0, 0.8));
    }
}
