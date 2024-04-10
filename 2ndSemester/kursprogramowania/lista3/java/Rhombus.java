/**
 * Rhombus
 */
public final class Rhombus extends Quadrilateral 
{
    private final double side;
    private final double angle;
    
    public Rhombus(final double side, final double angle)
    {
        if (side <= 0) 
        {
            throw new IllegalArgumentException("Side length should be positive, got " + side);    
        }
        else if (angle <= 0 || angle >= 180)
        {
            throw new IllegalArgumentException("Angle should be between 0 and 180 degrees, got " + angle);    
        }
        this.side = side;
        this.angle = angle;
    }

    @Override
    public double area() 
    {
        return side * side * Math.sin(Math.PI/180 * angle);
    } 

    @Override
    public double perimeter()
    {
        return 4 * side;
    }

    @Override
    public String name()
    {
        return "Rhombus";
    }
}
