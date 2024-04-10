/**
 * Hexagon
 */
public final class Hexagon extends Figure 
{
    private final double side;
    
    public Hexagon(final double side)
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
        return 2.5980762113 * side * side;
    } 

    @Override
    public double perimeter()
    {
        return 6 * side;
    }

    @Override
    public String name()
    {
        return "Hexagon";
    }
}
