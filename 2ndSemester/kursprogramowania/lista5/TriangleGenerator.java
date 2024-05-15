import java.util.ArrayList;
import java.util.logging.Level;

import javafx.scene.paint.Color;

/**
 * @brief generates triangle
 * 
 * @implements IGenerator
 */
public class TriangleGenerator implements IGenerator
{
    private ArrayList<Double[]> points = new ArrayList<Double[]>();

    TriangleGenerator()
    {

    }

    public final boolean isReady() 
    {
        if (points.size() == 3) 
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

    public final ShapeTriangle generate() throws IndexOutOfBoundsException
    {
        if (isReady()) 
        {
            MyLogger.logger.log(Level.FINER, "Created a Triangle");
            return new ShapeTriangle(points.get(0)[0], points.get(0)[1], points.get(1)[0], points.get(1)[1], points.get(2)[0], points.get(2)[1], Color.rgb(0, 0, 0, 1.0));
        }
        else
            throw new IndexOutOfBoundsException("Not enough points were given");
    }

    public final ShapeTriangle ghost(double x, double y)
    {
        if (points.size() == 2)
            return new ShapeTriangle(points.get(0)[0], points.get(0)[1], points.get(1)[0], points.get(1)[1], x, y, Color.rgb(0, 0, 0, 0.65));
        else if (points.size() == 1)
        {
            ShapeTriangle ghost = new ShapeTriangle(points.get(0)[0], points.get(0)[1], x, y, x, y, Color.rgb(0, 0, 0, 0.65));
            ghost.setStroke(Color.rgb(0, 0, 0, 0.65));
            ghost.setStrokeWidth(2);
            return ghost;
        }
        else
            return new ShapeTriangle(x, y, x + 2, y, x + 1, y + 2, Color.rgb(0, 0, 0, 0.65));
    }    
}
