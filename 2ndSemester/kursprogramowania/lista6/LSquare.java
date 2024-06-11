import java.util.ArrayList;
import java.util.logging.Level;

import javafx.scene.paint.Color;

/**
 * @brief class handling the logic behind every thread
 */
public class LSquare extends Thread implements IStoppable
{
    private final int ID;
    private GUISquare guiSquare = null;
    private final Object locker;

    private final double probability;
    private final long delay;

    private Color color;

    private ArrayList<LSquare> neighbors = new ArrayList<LSquare>();
    private ArrayList<Color> neighborColors = new ArrayList<Color>();

    private boolean isActive = true;
    
    public LSquare(LGrid lGrid, double probability, long delay, int ID)
    {
        this.color = MyRandom.randomColor();
        this.locker = lGrid.getLocker();

        this.probability = probability;
        this.delay = delay;

        this.ID = ID;
    }

    /**
     * @brief changes color of the square
     * 
     * @throws IllegalArgumentException
     */
    public void changeColor() throws IllegalArgumentException
    {
        synchronized(locker)
        {
            synchronized(this)
            {
                if (neighbors.isEmpty()) 
                {
                    throw new IllegalArgumentException("Neighbors not initialized");    
                }
                synchronized(neighbors.get(0))
                {
                    synchronized(neighbors.get(1))
                    {
                        synchronized(neighbors.get(2))
                        {
                            synchronized(neighbors.get(3))
                            {
                                System.out.println("Start " + ID);
                    
                                double rtd = MyRandom.randomDouble(0, 1);
                                
                                if (rtd <= probability) 
                                {
                                    color = MyRandom.randomColor();
                                }
                                else
                                {
                                    neighborColors.clear();
                    
                                    for (LSquare neighbor : neighbors) 
                                    {
                                        if (neighbor.getColor() != null)
                                        {
                                            neighborColors.add(neighbor.getColor());    
                                        }
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
                }
            }
        }
    }

    @Override
    public synchronized final void changeState()
    {
        if (isActive)
        {
            isActive = false;

            updateGUI(Color.rgb(0, 0, 0));

            MyLogger.logger.log(Level.FINE, "Deactived thread " + ID); 
        }
        else
        {
            isActive = true;

            updateGUI(null);

            MyLogger.logger.log(Level.FINE, "Activated thread" + ID);
        }
    }

    /**
     * @brief add references to neighboring squares
     * 
     * @param neighbor1
     * @param neighbor2
     * @param neighbor3
     * @param neighbor4
     * @throws IllegalArgumentException
     */
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

    /**
     * @brief passes the color to GUI
     * 
     * @param newColor
     */
    private final void updateGUI(Color newColor)
    {
        if (guiSquare != null) 
            {
                guiSquare.update(newColor);    
            }
    }
    
    /**
     * @brief gives square's current color
     * 
     * @return color
     */
    public synchronized final Color getColor()
    {
        if (isActive)
        {
            return color;
        }
        else
        {
            return null;
        }
    }

    @Override
    public synchronized final boolean isActive()
    {
        return isActive;
    }

    /**
     * @brief initializes the GUISquare linked to this LSquare
     * 
     * @param guiSquare
     */
    public final void setGUISquare(GUISquare guiSquare)
    {
        this.guiSquare = guiSquare;
    }

    /**
     * @brief starts the thread 
     */
    @Override
    public void run()
    {
        while (isAlive()) 
        {            
            if (isActive) 
            {
                changeColor();
    
                updateGUI(null);    
            }
            
            try
            {
                sleep((long)(delay * MyRandom.randomDouble(0.5, 1.5)));
            }
            catch (InterruptedException e)
            {
                MyLogger.logger.log(Level.WARNING, "Sleep interupted", e);
            }
        }
    }
}
