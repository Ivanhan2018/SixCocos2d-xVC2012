public class DPoint2
{
private double x;
private double y;
public DPoint2(double x, double y)
{
this.x = x;
this.y = y;
}
public double getDistance(DPoint2 p)
{
double _x = Math.abs(this.x - p.x);
double _y = Math.abs(this.y - p.y);
return Math.sqrt(_x*_x+_y*_y);
}
public static void main(String[] args)
{
DPoint2 p1 = new DPoint2(5, 5);
DPoint2 p2 = new DPoint2(10, 10);
System.out.println(p2.getDistance(p1));
}
}
