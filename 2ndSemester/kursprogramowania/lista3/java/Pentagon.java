/**
 * Pentagon
 */
public final class Pentagon extends Figure 
{
    private final double side;
    
    public Pentagon(final double side)
    {
        if (side <= 0) 
        {
            throw new IllegalArgumentException("Side length should be positive, got " + side);    
        }
        this.side = side;
    }

    @Override
    public double area() 
    {
        return 1.7204774005 * side * side;
    } 

    @Override
    public double perimeter()
    {
        return 5 * side;
    }

    @Override
    public String name()
    {
        return "Pentagon";
    }
}
