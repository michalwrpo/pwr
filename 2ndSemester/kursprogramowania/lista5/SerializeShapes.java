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

public class SerializeShapes 
{

    public final static void serialize(ObservableList<Node> nodes, String filename)
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

    public final static ObservableList<Node> deserialize(String filename)
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
}
