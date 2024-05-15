public interface IShapePhysics 
{
    public double getAbsoluteX();
    public double getAbsoluteY();

    public void move(double x, double y);
    public void scale(double y);
    public void rotate(double x);      
}
