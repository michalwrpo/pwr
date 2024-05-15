import javafx.scene.paint.Color;

/**
 * @brief interface having declarations of methods related to Shapes' color
 */
public interface IShapeColor 
{
    /**
     * @brief adds an outline to the shape and selects it 
     */
    public void select();

    /**
     * @brief removes the outline and unselects the shape
     */
    public void unselect();

    /**
     * @brief changes shape's color to a given one
     * 
     * @param color
     */
    public void setColor(Color color);
}
