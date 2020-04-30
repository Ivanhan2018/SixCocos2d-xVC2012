using System;
using System.Runtime.InteropServices;

namespace ConsoleApp1
{
    public class RefComm
    {
#if MS_BUILD
        public static void Hello()
        {
            Console.WriteLine("Hello,VS.NET");
        }
#else
        public static void Hello()
        {
            Console.WriteLine("Hello,MONO");
        }
#endif		
    }

    class DLLSOTest
    {
#if USE_DLL
    [DllImport("MATHLIB52.DLL", EntryPoint="_brinv@8", CharSet=CharSet.Auto,CallingConvention=CallingConvention.StdCall)]
#else
    [DllImport("libmathlib52.so", EntryPoint="brinv")]
#endif
	public static extern int brinv(double[] a,int n);
  　//public static extern int brinv(ref double a,int n);
		public static void Main()
		{
			RefComm.Hello();
			//Console.ReadKey();
			double [] a=new double[9];
			Console.WriteLine("输入3*3矩阵中的9个数:");
			for(int i=0;i<a.Length;i++)
				a[i]= Convert.ToDouble(Console.ReadLine());
			int ret=brinv(a,3);
			if(ret!=0)
			{
				foreach(double j in a)
				Console.WriteLine(j.ToString()+"\t");
			}
		}
    }
}