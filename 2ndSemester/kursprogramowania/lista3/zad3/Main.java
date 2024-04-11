public final class Main 
{
    public static void main(String[] args)
    {
        if (args.length == 0)
        {
            System.err.println("Usage: java Main <arg1> <arg2> ...");
            return;
        }
        else if (args.length != 2 && args.length != 3)
        {
            System.err.println("Arguments should be a char and 1 or 2 doubles");
            return;
        }

        if (args.length == 2)
        {
            try
            {
                final double side = Double.parseDouble(args[1]);

                switch (args[0]) {
                    case "c":
                        System.out.println(Figure.Single.CIRCLE.figureName());
                        System.out.println("Area: " + Figure.Single.CIRCLE.area(side));
                        System.out.println("Perimeter: " + Figure.Single.CIRCLE.perimeter(side));
                        break;
                    
                    case "s":
                        System.out.println(Figure.Single.SQUARE.figureName());
                        System.out.println("Area: " + Figure.Single.SQUARE.area(side));
                        System.out.println("Perimeter: " + Figure.Single.SQUARE.perimeter(side));
                        break;
                    
                    case "p":
                        System.out.println(Figure.Single.PENTAGON.figureName());
                        System.out.println("Area: " + Figure.Single.PENTAGON.area(side));
                        System.out.println("Perimeter: " + Figure.Single.PENTAGON.perimeter(side));
                        break;

                    case "h":
                        System.out.println(Figure.Single.HEXAGON.figureName());
                        System.out.println("Area: " + Figure.Single.HEXAGON.area(side));
                        System.out.println("Perimeter: " + Figure.Single.HEXAGON.perimeter(side));
                        break;

                    default:
                        System.err.println("Invalid Argument Error: When given 2 arguments, the former should be 'c', 's', 'p' or 'h'");
                        return;
                }
            }
            catch (IllegalArgumentException e) 
            {
                System.err.println("Illegal Argument Exception: " + e.getMessage());
                return;
            }
        }
        else
        {
            try
            {
                final double arg1 = Double.parseDouble(args[1]);
                final double arg2 = Double.parseDouble(args[2]);

                switch (args[0]) {
                    case "r":
                        System.out.println(Figure.Dual.RECTANGLE.figureName());
                        System.out.println("Area: " + Figure.Dual.RECTANGLE.area(arg1, arg2));
                        System.out.println("Perimeter: " + Figure.Dual.RECTANGLE.perimeter(arg1, arg2));
                        break;
                
                    case "d":
                        System.out.println(Figure.Dual.RHOMBUS.figureName());
                        System.out.println("Area: " + Figure.Dual.RHOMBUS.area(arg1, arg2));
                        System.out.println("Perimeter: " + Figure.Dual.RHOMBUS.perimeter(arg1, arg2));
                        break;

                    default:
                    System.err.println("Invalid Argument Error: When given 3 arguments, the first one should be 'r' or 'd'");
                    return;
                }
            }
            catch (IllegalArgumentException e) 
            {
                System.err.println("Illegal Argument Exception: " + e.getMessage());
                return;
            }
        }
    }
}
