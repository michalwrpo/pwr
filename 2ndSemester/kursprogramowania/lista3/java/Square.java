/**
 * Square
 */
public final class Square extends Quadrilateral 
{
    private final double side;
    
    public Square(final double side)
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
        return side * side;
    } 

    @Override
    public double perimeter()
    {
        return 4 * side;
    }

    @Override
    public String name()
    {
        return "Square";
    }
}
