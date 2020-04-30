using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;

public class RefComm
{ 
  [DllImport("libmathlib52.so", EntryPoint="mean")]
  public static extern double mean(double[] a,int n);// 平均数
 
    // 计算由num个浮点数组成的数组的平均值
	private static double Mean(IEnumerable<double> values)
	{
		int num=values.Count();
		double avg=0;
		foreach (double v in values)
		{
			avg+=v;
		}
		avg/=num;
		return avg;
	}

    // 返回样本的众数值，如果众数超过一个，则返回最前面的一个
	static T find_mode<T>(T[] a)
	{
		int num=a.Length;
		T md=a[0],oldmode=a[0];
		int count,oldcount=0;
		for(int t=0;t<num;t++)
		{
			md=a[t];
			count=1;
			for(int w=t+1;w<num;w++)
			if(md.Equals(a[w]))//此处不能用==
				count++;//准众数值
			if(count>oldcount)
			{
				oldmode=md;
				oldcount=count;
			}
		}
		return oldmode;
	}
	
	private static double StdDev(IEnumerable<double> values)
	{
		double ret = 0;
		if (values.Count() > 0)
		{
			//  计算平均数   
			double avg = values.Average();
			//  计算各数值与平均数的差值的平方，然后求和 
			double sum = values.Sum(d => Math.Pow(d - avg, 2));
			//  除以数量，然后开方
			ret = Math.Sqrt(sum / values.Count());
		}
		return ret;
	}

    // 计算标准均方差
	private static double std_dev(IEnumerable<double> values)
	{
		double avg=Mean(values);
		double std=0;
		foreach (double v in values)
		{
			std+=(v-avg)*(v-avg);
		}
		std/=values.Count();
		std=Math.Sqrt(std);
		return std;
	}

	public static void Main()
	{
		{
			double[] a= {1, 2,2, 3, 4,4, 5};
			List<double> L = new List<double>(a);
			double avg=L.Average();
			double avg1=Mean(L);			
			double mode=find_mode<double>(a);
			double stdDev=StdDev(L);
			double stdDev1=std_dev(L);			
			Console.WriteLine("avg="+avg.ToString()+",avg1="+avg1.ToString()+",mode="+mode.ToString()+",stdDev="+stdDev.ToString()+",stdDev1="+stdDev1.ToString());
		}
		{
			int[] a= {1, 2, 2,3, 4, 4,5};
			List<int> L = new List<int>(a);
			var L1 = L.ToArray().Select(Convert.ToDouble);
			double avg=L.Average();
			double avg1=Mean(L1);
			int mode=find_mode<int>(a);
			double stdDev=StdDev(L1);
			double stdDev1=std_dev(L1);
			Console.WriteLine("avg="+avg.ToString()+",avg1="+avg1.ToString()+",mode="+mode.ToString()+",stdDev="+stdDev.ToString()+",stdDev1="+stdDev1.ToString());
		}		
	}
}