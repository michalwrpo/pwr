/**
 * @brief manages selected shape
 */
public class Selector 
{
    private Selector() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    private static IShape selected = null;
    private static IShape ghost = null;
    
    /**
     * @brief returns currently selected shape
     * 
     * @return selectedShape 
     */
    public static IShape getSelected()
    {
        return selected;
    }

    /**
     * @brief returns the currently existing ghost
     * 
     * @return ghost
     */
    public static IShape getGhost()
    {
        return ghost;
    }

    /**
     * @brief changes the currently existing ghost
     * 
     * @param newGhost
     */
    public static void setGhost(IShape newGhost)
    {
        ghost = newGhost;
    }
    
    /**
     * @brief unselects a shape
     */
    public static void unselect()
    {
        if (selected != null)
        {
            selected.unselect();
            selected = null;
        }
    }

    /**
     * @brief selects a new shape
     * 
     * @param newSelected
     */
    public static void select(IShape newSelected)
    {
        unselect();
        selected = newSelected;
        selected.select();
    }
}
