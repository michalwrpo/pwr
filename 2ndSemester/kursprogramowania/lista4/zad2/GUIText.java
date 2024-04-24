import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;

public class GUIText extends Text
{
    public GUIText(String text, Integer size, Boolean bold)
    {
        super(text);

        setTextAlignment(TextAlignment.CENTER);

        if (bold)
            setFont(Font.font("sans serif", FontWeight.BOLD, size));
        else
            setFont(Font.font("sans serif", FontWeight.NORMAL, size));        
    }
}
