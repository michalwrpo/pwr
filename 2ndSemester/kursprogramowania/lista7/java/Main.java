/**
 * @brief Main class of the program, used to run it
 */
public final class Main 
{
    /**
     * @brief main method used to start the whole program
     * 
     * @param args console inputs
     */
    public static void main(String[] args)
    {
        System.out.println("Which type of tree do you want to create?");
        System.out.println("[i]nterger, [d]ouble, [s]tring");

        char treeType = System.console().readLine().charAt(0);
        Character.toLowerCase(treeType);

        switch (treeType) 
        {
            case 'i':
                IParser<Integer> intParser = new IntParser();
                CLI<Integer> intCLI = new CLI<Integer>(intParser);
                intCLI.start();
                break;
            case 'd':
                IParser<Double> doubleParser = new DoubleParser();
                CLI<Double> doubleCLI = new CLI<Double>(doubleParser);
                doubleCLI.start();
                break;
            case 's':
                IParser<String> stringParser = new StringParser();
                CLI<String> stringCLI = new CLI<String>(stringParser);
                stringCLI.start();
                break;
            default:
                System.out.println("Invalid type");
                break;
        }
    }
    
}