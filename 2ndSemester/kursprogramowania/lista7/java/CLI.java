import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 * @brief CLI (Command Line Interface) for the BST responsible for interacting with it through the command line
 * 
 * @param <T> type of elements inside the BST
 */
public class CLI<T extends Comparable<T>>
{
    private BST<T> tree;
    private IParser<T> parser; 

    public CLI(IParser<T> parser)
    {
        this.tree = new BST<T>();
        this.parser = parser;
    }

    /**
     * Starts the CLI interacting with tree
     * List of valid commands
     * - p - prints the tree
     * - i / a [value] - inserts value into the tree
     * - r / d [value] - removes value from the tree
     * - s / f [value] - finds if value is in the tree
     * - q - quits from CLI
     * CLI will continue running until the user chooses to quit
     */
    public void start()
    {
        Scanner scanner = new Scanner(System.in);
        boolean quit = false;

        String command = null;

        while (!quit)
        {
            System.out.print("Enter command: ");

            try
            {
                command = scanner.nextLine();
            }
            catch (NoSuchElementException e)
            {
                System.out.println("Quiting by CTRL+D");
                System.exit(0);
            }

            if (command.equals("p")) 
            {
                System.out.println(tree.print());
                continue;
            }

            if (command.equals("q"))
            {
                System.out.println("Quiting...");
                quit = true;
                continue;
            }

            String[] commandParts = command.split("\\s+");

            if (commandParts.length != 2) 
            {
                System.out.println("Invalid command");
                continue;    
            }

            String operation = commandParts[0];
            T value = null;

            try
            {
                value = parser.parse(commandParts[1]);
            }
            catch (NumberFormatException e)
            {
                System.out.println("Invalid value");
                continue;
            }

            switch (operation) 
            {
                case "i":
                case "a":
                    System.out.println("Inserting " + value.toString() + " into the tree");
                    tree.insert(value);
                    break;
                case "r":
                case "d":
                    System.out.println("Deleting " + value.toString() + " from the tree");
                    tree.delete(value);
                    break;
                case "s":
                case "f":
                    System.out.println(value.toString() + (tree.search(value) ? " is" : " is not") + " in the tree");
                    break;
                default:
                    System.out.println("Invalid command");
                    break;
            }

        }

        scanner.close();
    }
}
