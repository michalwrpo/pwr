/**
 * @brief interface contatining methods related to parsing arbitrary type T
 */
public interface IParser<T>
{
    /**
     * @brief parses given String to type T 
     * 
     * @param value String to be parsed
     * @return input as type T
     * @throws NumberFormatException if given String cannot be parsed
     */
    public T parse(String value) throws NumberFormatException;    
}
