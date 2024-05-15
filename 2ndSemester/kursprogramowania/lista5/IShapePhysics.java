/**
 * @brief interface having declarations of methods connected with shapes position and size
 */
public interface IShapePhysics 
{
    /**
     * @brief returns x value of the shape according to the screen not parent
     * 
     * @return screenX - position of shape on the screen 
     */
    public double getAbsoluteX();

    /**
     * @brief returns y value of the shape according to the screen not parent
     * 
     * @return screenY - position of shape on the screen 
     */
    public double getAbsoluteY();

    /**
     * @brief moves shape to the given coordinates
     * 
     * @param x
     * @param y
     */
    public void move(double x, double y);

    /**
     * @brief changes shape's scale by a thousandth of a given scale
     * 
     * @param y
     */
    public void scale(double y);

    /**
     * @brief rotates shape by a tenth of a given angle
     * 
     * @param x
     */
    public void rotate(double x);      
}
