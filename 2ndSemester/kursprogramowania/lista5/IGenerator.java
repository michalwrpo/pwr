import javafx.scene.shape.Shape;

/**
 * @brief interface having methods related to shapes creation
 */
public interface IGenerator 
{
    /**
     * @brief returns if enough point were given to generate the shape
     * 
     * @return readiness
     */
    public boolean isReady();

    /**
     * @brief adds a point to the shape generator
     * 
     * @param x
     * @param y
     * @throws IllegalArgumentException
     */
    public void addPoint(double x, double y) throws IllegalArgumentException;

    /**
     * @brief generates a shape if enough points were given
     * 
     * @return shape
     * @throws IndexOutOfBoundsException
     */
    public Shape generate() throws IndexOutOfBoundsException;

    /**
     * @brief generate a semi-transparent shape if not enough points were given to generate
     * 
     * @param x
     * @param y
     * @return ghost
     */
    public IShape ghost(double x, double y);
}
