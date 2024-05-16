import java.util.logging.Level;

/**
 * @brief contains methods related to app states
 */
public class StateMachine 
{
    private StateMachine() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    private static AppState state = AppState.SELECT;
    
    /**
     * @brief returns the current state
     * 
     * @return state
     */
    public final static AppState getState()
    {
        return state;
    }

    /**
     * @brief changes the state between SELECT and DRAW
     */
    public final static void changeSelectDraw()
    {
        if (state == AppState.SELECT) 
        {
            Selector.unselect();
            state = AppState.DRAW;
            MyLogger.logger.log(Level.FINE, "Changed state from SELECT to DRAW");
        }
        else if (state == AppState.DRAW)
        {
            state = AppState.SELECT;
            Selector.setGhost(null);
            MyLogger.logger.log(Level.FINE, "Changed state from DRAW to SELECT");

        }
    }
}
