/**
 * @brief creates a pair of a name and a generator, corresponding to a shape
 */
public class ShapePair 
{
    private String name;
    private IGenerator generator;
    
    /**
     * @brief creates a pair
     * 
     * @param name
     * @param generator
     */
    public ShapePair(String name, IGenerator generator)
    {
        this.name = name;
        this.generator = generator;
    }

    /**
     * @brief returns the name
     * 
     * @return name
     */
    public final String getName()
    {
        return name;
    }

    /**
     * @brief returns the generator
     * 
     * @return generator
     */
    public final IGenerator getGenerator()
    {
        return generator;
    }
}
