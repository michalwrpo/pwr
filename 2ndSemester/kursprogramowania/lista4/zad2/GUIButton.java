import java.util.ArrayList;
import java.util.logging.Level;

import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
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
                MyLogger.logger.log(Level.FINE, "Generated a triangle");

                int n = Integer.parseInt(triangleSize.getText());
                String message = " ";
                for(int i = 0; i < n; i++)
                {
                    ArrayList<Integer> row =  PascalsTriangleRow.pascalsRow(i);
                    for (int j : row)
                        message += (j + "  ");
                    message += "\n ";
                }
                    triangle.setText(message);
            }
        });
    }
}
