import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.logging.Level;

import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import javafx.stage.Popup;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;

public class GUIButton extends Button
{
    public GUIButton(String name, TextField length, TextField arguments, Text outputText)
    {
        super(name);

        setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event) 
            {
                try
                {
                    String arg1 = length.getText();
                    String[] args = arguments.getText().trim().split("\\s*,\\s*");
                    ArrayList<String> allArgs = new ArrayList<>(Arrays.asList(args));
                    allArgs.add(0, "./cpp/app.out");
                    allArgs.add(1, arg1);

                    MyLogger.logger.log(Level.FINEST, "Created args list");

                    String message = "";
                    
                    Process process = new ProcessBuilder(allArgs).start();
                    
                    try
                    {
                        Integer.parseInt(arg1);
                        
                        try (BufferedReader input = new BufferedReader(new InputStreamReader(process.getInputStream())))
                        {
                            String line;
                            
                            while ((line = input.readLine()) != null)
                            {
                                message += line + "\n";
                            }
                        } 
                        try (BufferedReader err = new BufferedReader(new InputStreamReader(process.getErrorStream())))
                        {
                            String line;
    
                            while ((line = err.readLine()) != null)
                            {
                                message += line.substring(0, line.indexOf(':')) + "\n";
                            }
                        }
    
                        outputText.setText(message);
                        MyLogger.logger.log(Level.FINE, "Generated answers");
                    }
                    catch (NumberFormatException e)
                    {
                        Popup popup = new GUIPopUp("Invalid Argument: " + arg1);
                        popup.show(getScene().getWindow());
                        MyLogger.logger.log(Level.FINE, "Invalid Argument");
                    }
                }
                catch (IOException e)
                {
                    MyLogger.logger.log(Level.WARNING, "Error: " + e.getMessage());
                    
                    Popup popup = new GUIPopUp("Invalid Argument: " + e.getMessage());
                    popup.show(getScene().getWindow());
                }
                
            }
        });
    }
}
