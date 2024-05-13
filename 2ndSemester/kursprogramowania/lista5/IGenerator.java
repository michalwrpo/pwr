import javafx.scene.shape.Shape;

public interface IGenerator 
{
    public boolean isReady();

    public void addPoint(double x, double y) throws IllegalArgumentException;

    public Shape generate() throws IndexOutOfBoundsException;

    public Shape ghost(double x, double y);
}
