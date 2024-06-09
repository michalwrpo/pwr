import javafx.scene.paint.Color;

public class LSquare extends Thread
{
    private Color color;
    private final Object locker;
    
    public LSquare(Object locker)
    {
        this.color = MyRandom.randomColor();
        this.locker = locker;
    }

    public synchronized void changeColor(double probability, Color neighbor1, Color neighbor2, Color neighbor3, Color neighbor4)
    {
        synchronized(locker)
        {
            double rtd = MyRandom.randomDouble(0, 1);
            
            if (rtd > probability) 
            {
                color = MyRandom.randomColor();
            }
            else
            {
                color = Color.color((neighbor1.getRed() + neighbor2.getRed() + neighbor3.getRed() + neighbor4.getRed())/4, (neighbor1.getGreen() + neighbor2.getGreen() + neighbor3.getGreen() + neighbor4.getGreen())/4, (neighbor1.getBlue() + neighbor2.getBlue() + neighbor3.getBlue() + neighbor4.getBlue())/4);
            }
        }
    }
    
    public synchronized final Color getColor()
    {
        return color;
    }
}
