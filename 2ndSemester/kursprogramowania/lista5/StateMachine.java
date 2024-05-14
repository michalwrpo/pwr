import java.util.logging.Level;

public class StateMachine 
{
    private static AppState state = AppState.SELECT;
    
    public static AppState getState()
    {
        return state;
    }

    public static void changeSelectDraw()
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
