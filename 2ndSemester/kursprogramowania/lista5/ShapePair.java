public class ShapePair 
{
    private String name;
    private IGenerator generator;
    
    public ShapePair(String name, IGenerator generator)
    {
        this.name = name;
        this.generator = generator;
    }

    public final String getName()
    {
        return name;
    }

    public final IGenerator getGenerator()
    {
        return generator;
    }
}
