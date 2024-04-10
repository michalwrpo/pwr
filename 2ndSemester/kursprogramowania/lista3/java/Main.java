public final class Main 
{
    private Main() throws InstantiationError 
    {
        throw new InstantiationError("This is a static class!");
    }
    
    public static void main(String[] args)
    {
        if (args.length == 0)
        {
            System.err.println("Usage: java Main <arg1> <arg2> ...");
            return;
        }
        else if (args.length != 2 && args.length != 6)
        {
            System.err.println("Arguments should be a char and 1 or 5 doubles");
            return;
        }

        Figure f = null;

        if (args.length == 2) 
        {
            try 
            {
                final double side = Double.parseDouble(args[1]);               
                
                if (side <= 0) 
                {
                    System.err.println("Invalid Argument Error: Double argument should be greater than 0");
                    return;    
                }    

                if (args[0].equals("o"))
                {
                    f = new Circle(side);
                } 
                else if (args[0].equals("p"))
                {
                    f = new Pentagon(side);
                } 
                else if (args[0].equals("s"))
                {
                    f = new Hexagon(side);
                } 
                else
                {
                    System.err.println("Invalid Argument Error: When given 2 arguments, the former should be 'o', 'p' or 's'");
                    return;
                }
            } 
            catch (IllegalArgumentException e) 
            {
                System.err.println("Illegal Argument Exception: " + e.getMessage());
                return;
            }
        }
        else if (args.length == 6)
        {
            try 
            {
                final double side1 = Double.parseDouble(args[1]);
                final double side2 = Double.parseDouble(args[2]);
                final double side3 = Double.parseDouble(args[3]);
                final double side4 = Double.parseDouble(args[4]);
                final double angle = Double.parseDouble(args[5]);
            
                if (side1 <= 0 || side2 <= 0 || side3 <= 0 || side4 <= 0 || angle <= 0)
                {
                    System.err.println("Invalid Argument Error: Double argument should be greater than 0");
                    return;
                } else if (angle >= 180)
                {
                    System.err.println("Invalid Argument Error: Last double argument should be smaller than 180");
                    return;
                }
                
                if (!args[0].equals("c"))
                {
                    System.err.println("Invalid Argument Error: When given 5 arguments, the first should be 'c'");
                    return;
                }

                if (angle != 90)
                {
                    if (side1 == side2 && side2 == side3 && side3 == side4)
                    {
                        f = new Rhombus(side1, angle);
                    } else
                    {
                        System.err.println("Invalid Argument Error: Side lengths should be equal or angle 90 degrees");
                        return;
                    }
                }
                else
                {
                    if (side1 == side2 && side2 == side3 && side3 == side4)
                    {
                        f = new Square(side1);
                    } else if (side1 == side2 && side3 == side4)
                    {
                        f = new Rectangle(side1, side3);
                    } else if ((side1 == side3 && side2 == side4) || (side1 == side4 && side2 == side3))
                    {
                        f = new Rectangle(side1, side2);
                    } else
                    {
                        System.err.println("Invalid Argument Error: There should be at least 2 pairs of equal side lengths");
                        return;
                    }
                }
            }
            catch (IllegalArgumentException e) 
            {
                System.err.println("Illegal Argument Exception: " + e.getMessage());
                return;
            }    
        }

        System.out.println(f.name() + "\nArea: " + f.area() + "\nPerimeter: " + f.perimeter());
    }
}
