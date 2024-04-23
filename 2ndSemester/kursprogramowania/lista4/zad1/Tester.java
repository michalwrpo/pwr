import java.util.ArrayList;

public class Tester 
{
    public static void main(String[] args) 
    {
        int n = 10;
        for(int i = 0; i < n; i++)
        {
            for (int k = 0; k < 2*(n - i); k++)
            {
                System.out.print(" ");
            }
            ArrayList<Integer> row =  PascalsTriangleRow.pascalsRow(i);
            for (int j : row)
            {
                System.out.print(j + "  ");
            }    
            System.out.print("\n");
        }
    }    
}
