/**
 * @brief parser for Integers
 */
public class IntParser implements IParser<Integer>
{
    @Override
    public Integer parse(String value) throws NumberFormatException
    {
        return Integer.parseInt(value);
    }
}
