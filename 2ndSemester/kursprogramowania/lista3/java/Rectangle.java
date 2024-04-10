/**
 * Rectangle
 */
public final class Rectangle extends Quadrilateral 
{
    private final double side1;
    private final double side2;
    
    public Rectangle(final double side1, final double side2)
    {
        if (side1 <= 0 || side2 <= 0) 
        {
            throw new IllegalArgumentException("Side lengths should be positive, got " + side1 + " and " + side2);    
        }
        this.side1 = side1;
        this.side2 = side2;
    }

    @Override
    public double area() 
    {
        return side1 * side2;
    } 

    @Override
    public double perimeter()
    {
        return 2 * side1 + 2 * side2;
    }

    @Override
    public String name()
    {
        return "Rectangle";
    }
}
