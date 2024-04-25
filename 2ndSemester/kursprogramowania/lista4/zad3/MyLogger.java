import java.io.IOException;
import java.util.logging.*;

public class MyLogger
{
    private MyLogger()
    {
        throw new InstantiationError("MyLogger is a full statc class");
    }

    public static final Logger logger = Logger.getGlobal();
    public static void loggerConfig()
    {
        Handler[] handlers = logger.getHandlers();
        for(Handler handler : handlers)
            logger.removeHandler(handler);

        logger.setUseParentHandlers(false);

        ConsoleHandler ch = new ConsoleHandler();
        ch.setLevel(Level.INFO);
        logger.addHandler(ch);

        try
        {
            FileHandler fh = new FileHandler("./log.txt");
            fh.setLevel(Level.ALL);
            fh.setFormatter(new SimpleFormatter());
            logger.addHandler(fh);
        }
        catch (IOException | SecurityException e)
        {

        }

        logger.setLevel(Level.ALL);
    }
}