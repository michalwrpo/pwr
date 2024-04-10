/**
 * @class Figure
 * 
 * @brief abstract class containing methods connected with geometrical shapes
 */
public abstract class Figure implements Formulae 
{
    @Override
    public abstract double area();

    @Override
    public abstract double perimeter();
    
    public abstract String name();
}
