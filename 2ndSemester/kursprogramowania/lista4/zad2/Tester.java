import java.util.ArrayList;

public class Tester 
{
    public static void main(String[] args) 
    {
        int n = 10;
        String message = "";
        for(int i = 0; i < n; i++)
        {
            for (int k = 0; k < 2*(n - i); k++)
            {
                message += " ";
            }
            ArrayList<Integer> row =  PascalsTriangleRow.pascalsRow(i);
            for (int j : row)
            {
                message += j + "  ";
            }    
            message += "\n";
        }
        System.out.println(message);
    }    
}
