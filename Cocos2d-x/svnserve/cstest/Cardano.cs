using System;
using System.Runtime.InteropServices;

public class RefComm
{ 

[DllImport("libmathlib52.so", EntryPoint="Cardano")]
/* 

 函数功能： 计算实系数一元三次方程ax^3+bx^2+cx+d=0的3个复根
 参数：
      输入： 4个实系数
      输出： 3个复根(数组y依次存储第1个复根的实部、虚部、第2个复根的实部、虚部、第3个复根的实部、虚部)
     返回值：
      0: delta=0，有3个实根，其中y_2和y_3是重根
      1: delta>0 && delta2>=0||delta<0，有3个相异实根
      2: delta>0 && delta2<0，1实2虚	  
*/
public static extern int Cardano(double a,double b,double c,double d,double[] y);
public static void Main()
{
double [] y=new double[6];
Console.WriteLine("依次输入实系数a、b、c、d:");
for(int i=0;i<4;i++)
y[i]= Convert.ToDouble(Console.ReadLine());
double a=y[0],b=y[1],c=y[2],d=y[3];
int ret=Cardano(a,b,c,d,y);
Console.WriteLine("ret={0}",ret);
Console.WriteLine("一元三次方程"+a.ToString()+"x^3"+b.ToString()+"x^2"+c.ToString()+d.ToString()+"的3个根为:");
Console.WriteLine("x1={0}+{1}i",y[0],y[1]);
Console.WriteLine("x2={0}+{1}i",y[2],y[3]);
Console.WriteLine("x3={0}+{1}i",y[4],y[5]);
}
}