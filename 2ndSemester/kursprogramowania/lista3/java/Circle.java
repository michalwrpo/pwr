/**
 * Circle
 */
public final class Circle extends Figure 
{
    private final double radius;
    
    public Circle(final double radius)
    {
        if (radius <= 0) 
        {
            throw new IllegalArgumentException("Radius should be positive, got " + radius);    
        }
        this.radius = radius;
    }

    @Override
    public double area() 
    {
        return Math.PI * radius * radius;
    } 

    @Override
    public double perimeter()
    {
        return 2 * Math.PI * radius;
    }

    @Override
    public String name()
    {
        return "Circle";
    }
}
