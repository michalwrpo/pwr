public class Selector 
{
    private static IShape selected = null;
    private static IShape ghost = null;
    
    public static IShape getSelected()
    {
        return selected;
    }

    public static IShape getGhost()
    {
        return ghost;
    }

    public static void setGhost(IShape newGhost)
    {
        ghost = newGhost;
    }
    
    public static void unselect()
    {
        if (selected != null)
        {
            selected.unselect();
            selected = null;
        }
    }

    public static void select(IShape newSelected)
    {
        unselect();
        selected = newSelected;
        selected.select();
    }
}
