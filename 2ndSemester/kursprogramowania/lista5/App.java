import javafx.application.Application;
import javafx.stage.Stage;

public class App extends Application
{
    @Override
    public void start(Stage stage)
    {
        new GUI(stage);
    }

    public static void main(String[] args)
    {
        MyLogger.loggerConfig();
        launch(args);
    }
}
