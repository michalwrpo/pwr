import java.util.Random;

import javafx.scene.paint.Color;

/**
 * @brief class containing methods related to pseudorandom numbers
 */
public class MyRandom 
{
    private MyRandom()
    {
        throw new InstantiationError("MyRandom is a fully static class");
    }

    private static final Random gen = new Random();
    
    /**
     * @brief returns a random integer between a and b
     * 
     * @param a
     * @param b
     * @return random int
     */
    public static final int randomInt(final int a, final int b)
    {
        return gen.nextInt(b - a) + a;
    }

    /**
     * @brief returns a random double between a and b
     * 
     * @param a
     * @param b
     * @return random double
     */
    public static final double randomDouble(final double a, final double b)
    {
        return gen.nextDouble() * (b - a) + a;
    }

    /**
     * @brief returns a random color
     * 
     * @return random color
     */
    public static final Color randomColor()
    {
        return Color.rgb(MyRandom.randomInt(0, 256), MyRandom.randomInt(0, 256), MyRandom.randomInt(0, 256));
    }
}
