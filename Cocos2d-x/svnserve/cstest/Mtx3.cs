using System;
using System.Runtime.InteropServices;

public class Mtx3
{ 
	[DllImport("libmathlib52.so", EntryPoint="poly3")]
	public static extern int poly3(double[] mtx3,double[] abcd);//计算三阶方阵的特征多项式,返回值0表示是对称矩阵，1表示不是对称矩阵
	[DllImport("libmathlib52.so", EntryPoint="Cardano")]
	public static extern int Cardano(double a,double b,double c,double d,double[] y);	
	public static void Main()
	{
		double [] a=new double[9];
		double [] b=new double[4];
		Console.WriteLine("输入3*3矩阵中的9个数:");
		for(int i=0;i<a.Length;i++)
			a[i]= Convert.ToDouble(Console.ReadLine());
		int ret=poly3(a,b);
		Console.WriteLine("ret={0}",ret);
		Console.WriteLine("特征多项式为"+b[0].ToString()+"x^3"+b[1].ToString()+"x^2"+b[2].ToString()+"x"+(b[3]>0?"+":"")+b[3].ToString());
		double [] y=new double[6];
		int ret1=Cardano(b[0],b[1],b[2],b[3],y);
		Console.WriteLine("ret1={0}",ret1);
		Console.WriteLine("3个根为:");
		Console.WriteLine("x1={0}+{1}i",y[0],y[1]);
		Console.WriteLine("x2={0}+{1}i",y[2],y[3]);
		Console.WriteLine("x3={0}+{1}i",y[4],y[5]);
		if(ret==0)
		{
			if(y[0]>0 && y[2]>0 && y[4]>0)
			{
				Console.WriteLine("该3*3矩阵是对称正定矩阵！");
			}
			else
			{
				Console.WriteLine("该3*3矩阵是对称非正定矩阵！");
			}
		}
	}
} 