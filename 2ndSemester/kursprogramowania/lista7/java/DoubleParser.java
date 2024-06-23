/**
 * @brief parser for Doubles
 */
public class DoubleParser implements IParser<Double>
{
    @Override
    public Double parse(String value) throws NumberFormatException
    {
        return Double.parseDouble(value);
    }
}
