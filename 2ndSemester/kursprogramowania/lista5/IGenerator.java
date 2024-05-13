public interface IGenerator 
{
    public boolean isReady();

    public void addPoint(double x, double y) throws IllegalArgumentException;


}
