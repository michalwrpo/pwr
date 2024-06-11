import java.util.ArrayList;

import javafx.scene.paint.Color;

/**
 * @brief class containing methods for calculating averages
 */
public class MyAverage 
{
    private MyAverage() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }    

    /**
     * @brief calculates the average of several colors
     * 
     * @param colors
     * @return average color
     */
    public static final Color averageColor(ArrayList<Color> colors)
    {
        if (colors.size() == 0)
        {
            return null;
        }

        double redSum = 0;
        double greenSum = 0;
        double blueSum = 0;

        for (Color color : colors)
        {
            redSum += color.getRed();
            greenSum += color.getGreen();
            blueSum += color.getBlue();
        }

        return Color.color(redSum / colors.size(), greenSum / colors.size(), blueSum / colors.size());
    }
}
