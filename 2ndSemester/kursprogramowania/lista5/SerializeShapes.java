import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.logging.Level;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Node;
import javafx.scene.layout.Pane;

/**
 * @brief class containing methods to save and load shapes via Serialize
 */
public class SerializeShapes 
{
    private SerializeShapes() throws InstantiationError
    {
        throw new InstantiationError("This is a static class");
    }

    /**
     * @brief saves files from a Obeservable list
     * 
     * @param nodes - list of shapes to be saved
     * @param filename - name of file where shapes will be save
     */
    public final static void serializeFromList(ObservableList<Node> nodes, String filename)
    {
        if (new File(filename).isFile()) 
        {
            try
            {
                FileOutputStream f = new FileOutputStream(filename);
                ObjectOutputStream o = new ObjectOutputStream(f);
    
                o.writeInt(nodes.size());
                                
                for (Node shape : nodes) 
                {
                    if (shape instanceof Serializable) 
                    {
                        o.writeObject(shape);
                        MyLogger.logger.log(Level.FINE, "Saved: " + shape.toString());
                    }
                }
    
                o.close();
    
                MyLogger.logger.log(Level.INFO, "Serialized canvas");
            }
            catch (IOException e)
            {
                MyLogger.logger.log(Level.INFO, "IOException: ", e);
            }
        }
    }

    /**
     * @brief loads shaps from a file to a list
     * 
     * @param filename - name of file from which shapes are loaded
     * @return shapesList - list of loaded shapes
     */
    public final static ObservableList<Node> deserializeToList(String filename)
    {
        ObservableList<Node> shapes = FXCollections.observableArrayList();

        if (new File(filename).isFile()) 
        {
            try
            {
                ObjectInputStream inStream = new ObjectInputStream(new FileInputStream(filename));
    
                int shapesNum = inStream.readInt();
                for (int i = 0; i < shapesNum; i++)
                {
                    Node shape = (Node) inStream.readObject();

                    MyLogger.logger.log(Level.FINE, "Loaded: " + shape.toString());

                    shapes.add(shape);
                }
    
                inStream.close();
    
                MyLogger.logger.log(Level.INFO, "Loaded canvas");
            }
            catch (IOException e)
            {
                MyLogger.logger.log(Level.INFO, "IOException: ", e);
            }
            catch (ClassNotFoundException e)
            {
                MyLogger.logger.log(Level.INFO, "ClassNotFoundException: ", e);
            }
        }

        return shapes;
    }

    /**
     * @brief serializes shapes from canvas to a file
     * 
     * @param canvas
     * @param filename
     */
    public final static void serialize(Pane canvas, String filename)
    {
        serializeFromList(canvas.getChildren(), filename);
    }

    /**
     * @brief loads shaps from a file to a canvas
     * 
     * @param canvas
     * @param filename
     */
    public final static void deserialize(Pane canvas, String filename)
    {
        int childrenNum = canvas.getChildren().size();
                for (int i = 0; i < childrenNum; i++)
                {
                    canvas.getChildren().removeFirst();
                }
                ObservableList<Node> nodes = deserializeToList(filename);
                canvas.getChildren().addAll(nodes);
    }
}
