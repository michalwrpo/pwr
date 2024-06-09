import java.util.Random;

import javafx.scene.paint.Color;

public class MyRandom 
{
    private MyRandom()
    {
        throw new InstantiationError("MyRandom is a fully static class");
    }

    private static final Random gen = new Random();
    
    public static final int randomInt(final int a, final int b)
    {
        return gen.nextInt(b - a) + a;
    }

    public static final double randomDouble(final int a, final int b)
    {
        return gen.nextDouble() * (b - a) + a;
    }

    public static final Color randomColor()
    {
        return Color.rgb(MyRandom.randomInt(0, 256), MyRandom.randomInt(0, 256), MyRandom.randomInt(0, 256));
    }
}
