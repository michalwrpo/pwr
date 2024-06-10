import java.util.ArrayList;
import java.util.logging.Level;

import javafx.scene.paint.Color;

public class LSquare extends Thread
{
    private final int ID;
    private GUISquare guiSquare = null;

    private final double probability;
    private final long delay;

    private Color color;
    private final Object locker;

    private ArrayList<LSquare> neighbors = new ArrayList<LSquare>();
    private ArrayList<Color> neighborColors = new ArrayList<Color>();
    
    public LSquare(LGrid lGrid, double probability, long delay, int ID)
    {
        this.color = MyRandom.randomColor();
        this.locker = lGrid.getLocker();

        this.probability = probability;
        this.delay = delay;

        this.ID = ID;
    }

    public void changeColor()
    {
        synchronized(locker)
        {
            synchronized(this)
            {
                System.out.println("Start " + ID);
    
                double rtd = MyRandom.randomDouble(0, 1);
                
                if (rtd > probability) 
                {
                    color = MyRandom.randomColor();
                }
                else
                {
                    neighborColors.clear();
    
                    for (LSquare neighbor : neighbors) 
                    {
                        neighborColors.add(neighbor.getColor());    
                    }
                    
                    Color newColor = MyAverage.averageColor(neighborColors);
                    
                    if (newColor == null)
                        return;
                    
                    color = newColor;
                }
                System.out.println("End " + ID);
            }
        }
    }

    public final void addNeighbors(LSquare neighbor1, LSquare neighbor2, LSquare neighbor3, LSquare neighbor4) throws IllegalArgumentException
    {
        if (!neighbors.isEmpty()) 
            throw new IllegalArgumentException("Neighbors already initialized");
        else
        {
            neighbors.add(neighbor1);
            neighbors.add(neighbor2);
            neighbors.add(neighbor3);
            neighbors.add(neighbor4);
        }

    }
    
    public synchronized final Color getColor()
    {
        return color;
    }

    public final void setGUISquare(GUISquare guiSquare)
    {
        this.guiSquare = guiSquare;
    }

    @Override
    public void run()
    {
        while (isAlive()) 
        {            
            changeColor();

            if (guiSquare != null) 
            {
                guiSquare.update();    
            }
            try
            {
                sleep((long)(delay * MyRandom.randomDouble(0.5, 1.5)));
            }
            catch (InterruptedException e)
            {
                MyLogger.logger.log(Level.WARNING, "Wywrotka", e);
            }
        }
    }
}
