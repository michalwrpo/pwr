import javafx.scene.paint.Color;

public interface IShape 
{
    public void select();
    public void unselect();
    public void setColor(Color color);

    public double getLocationX();
    public double getLocationY();

    public double getAbsoluteX();
    public double getAbsoluteY();

    public void move(double x, double y);
    public void scale(double y);
    public void rotate(double x);  
} 
