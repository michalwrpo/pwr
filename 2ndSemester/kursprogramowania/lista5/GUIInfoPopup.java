import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.logging.Level;

import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

/**
 * @brief class containing a method to create info popup
 */
public class GUIInfoPopup 
{
    private GUIInfoPopup() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    /**
     * @brief creates info popup
     */
    public static void showInfoPopup()
    {   
        try
        {
            Text content = new Text(new String(Files.readAllBytes(Paths.get("info.txt"))));
            
            ScrollPane scrollPane = new ScrollPane();
            scrollPane.setFitToWidth(true);
            scrollPane.setFitToHeight(true);
            
            VBox vBox = new VBox(content);
            
            scrollPane.setContent(vBox);
            
            Alert infoAlert = new Alert(AlertType.INFORMATION);
            infoAlert.setTitle("Information");
            infoAlert.setHeaderText(null);
            infoAlert.getDialogPane().setContent(scrollPane);
            infoAlert.showAndWait();

            MyLogger.logger.log(Level.FINE, "Displayed info popup");
        }
        catch (IOException e)
        {
            MyLogger.logger.log(Level.WARNING, "Alert error ", e);
        }

    }
    
}
