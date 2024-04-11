/**
 * Figure
 */
public class Figure 
{
    public interface ISingle 
    {
        public double area(final double side);
        public double perimeter(final double side);
        public String figureName();
    }

    public interface IDual 
    {
        public double area(final double arg1, final double arg2);
        public double perimeter(final double arg1, final double arg2);
        public String figureName();
    }

    public static enum Single implements ISingle
    {
        CIRCLE
        {
            @Override
            public final double area(final double radius)
            {
                if (radius <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + radius);    
                }
                return Math.PI * radius * radius;
            }

            @Override
            public final double perimeter(final double radius)
            {
                if (radius <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + radius);    
                }
                return 2* Math.PI * radius;
            }

            @Override
            public final String figureName()
            {
                return "Circle";
            }
        },
        SQUARE
        {
            @Override
            public final double area(final double side)
            {
                if (side <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + side);    
                }
                return side * side;
            }

            @Override
            public final double perimeter(final double side)
            {
                if (side <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + side);    
                }
                return 4 * side;
            }

            @Override
            public String figureName()
            {
                return "Square";
            }
        },
        PENTAGON
        {
            @Override
            public final double area(final double side) 
            {
                if (side <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + side);    
                }
                return 1.7204774005 * side * side;
            } 
        
            @Override
            public final double perimeter(final double side)
            {
                if (side <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + side);    
                }
                return 5 * side;
            }
        
            @Override
            public String figureName()
            {
                return "Pentagon";
            }
        
        },
        HEXAGON
        {
            @Override
            public final double area(final double side) 
            {
                if (side <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + side);    
                }
                return 2.5980762113 * side * side;
            } 

            @Override
            public final double perimeter(final double side)
            {
                if (side <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + side);    
                }
                return 6 * side;
            }

            @Override
            public String figureName()
            {
                return "Hexagon";
            }
        }
    }    

    public static enum Dual implements IDual
    {
        RECTANGLE
        {
            @Override
            public double area(final double side1, final double side2) 
            {
                if (side1 <= 0 || side2 <= 0) 
                {
                    throw new IllegalArgumentException("Side lengths should be positive, got " + side1 + " and " + side2);    
                }
                return side1 * side2;
            } 

            @Override
            public double perimeter(final double side1, final double side2)
            {
                if (side1 <= 0 || side2 <= 0) 
                {
                    throw new IllegalArgumentException("Side lengths should be positive, got " + side1 + " and " + side2);    
                }
                return 2 * side1 + 2 * side2;
            }

            @Override
            public String figureName()
            {
                return "Rectangle";
            }
        },
        RHOMBUS
        {
            @Override
            public double area(final double side, final double angle) 
            {
                if (side <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + side);    
                }
                else if (angle <= 0 || angle >= 180)
                {
                    throw new IllegalArgumentException("Angle should be between 0 and 180 degrees, got " + angle);    
                }

                return side * side * Math.sin(Math.PI/180 * angle);
            } 

            @Override
            public double perimeter(final double side, final double angle)
            {
                if (side <= 0) 
                {
                    throw new IllegalArgumentException("Side length should be positive, got " + side);    
                }
                else if (angle <= 0 || angle >= 180)
                {
                    throw new IllegalArgumentException("Angle should be between 0 and 180 degrees, got " + angle);    
                }
                
                return 4 * side;
            }

            @Override
            public String figureName()
            {
                return "Rhombus";
            }
        }
    }
}
