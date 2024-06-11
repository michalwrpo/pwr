/**
 * @brief interface contatining methods neccessary for square to be paused 
 */
public interface IStoppable 
{
    /**
     * @brief changes state from active to not and vice versa
     */
    public void changeState();

    /**
     * @brief returns the current state of the square
     * 
     * @return boolean isActive
     */
    public boolean isActive();
    
} 
