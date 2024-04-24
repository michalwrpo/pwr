import java.util.ArrayList;
import java.util.logging.Level;

import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import javafx.stage.Popup;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;

public class GUIButton extends Button
{
    public GUIButton(String name, TextField triangleSize, Text triangle)
    {
        super(name);

        setOnAction(new EventHandler<ActionEvent>() 
        {
            @Override
            public void handle(ActionEvent event) 
            {
                try
                {
                    
                    
                    int n = Integer.parseInt(triangleSize.getText());
                    
                    PascalsTriangleRow.pascalsRow(n);
                    
                    String message = " ";
                    
                    for(int i = 0; i <= n; i++)
                    {
                        ArrayList<Long> row =  PascalsTriangleRow.pascalsRow(i);
                        for (long j : row)
                        message += (j + "  ");
                        message += "\n ";
                    }
                    
                    triangle.setText(message);
                    MyLogger.logger.log(Level.FINE, "Generated a triangle");
                }
                catch(final IllegalArgumentException e)
                {
                    MyLogger.logger.log(Level.INFO, "Invalid Argument: " + e.getMessage());
                    
                    Popup popup = new Popup();
                    popup.getContent().add(new Text("Invalid Argument: " + e.getMessage()));
                    popup.show(getScene().getWindow());

                    System.out.println(popup.getContent());
                }
            }
        });
    }
}
