import java.util.List;
import java.util.logging.Level;

/**
 * @brief class contatining methods for handling inputs 
 */
public class MyInputHandler 
{
    private MyInputHandler() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }    

    /**
     * @brief check if inputs for creation of a grid are correct
     * 
     * @param args
     * @return true if inputs are correct, false otherwise
     * @throws IllegalArgumentException
     */
    public static final boolean checkInputs(List<String> args) throws IllegalArgumentException
    {
        if (args.size() == 0) 
        {
            MyLogger.logger.log(Level.FINE, "No arguments given");

            return false;
        }
        else if (args.size() == 4)
        {
            try
            {
                int height = Integer.parseInt(args.get(0));
                int width = Integer.parseInt(args.get(1));

                double probability = Double.parseDouble(args.get(2));
                long delay = Long.parseLong(args.get(3));

                if (height <= 0 || width <= 0 || probability < 0 || probability > 1 || delay <= 0) 
                {
                    MyLogger.logger.log(Level.FINE, "Invalid values of arguments given");
                    return false;
                }

                MyLogger.logger.log(Level.FINE, "Inputs passed");

                return true;
            }
            catch (IllegalArgumentException e)
            {
                MyLogger.logger.log(Level.INFO, "Wrong inputs", e);
                return false;
            }
        }
        else
        {
            MyLogger.logger.log(Level.INFO, "Wrong amount of inputs");
            return false;
        }
    }
}
