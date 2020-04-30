import java.util.*;

public class Un
{

// 求2个数的最大公约数
public static int GCD(int a, int b) 
{ 
 if(a*b<0)
  return -GCD(Math.abs(a),Math.abs(b));
 int temp=0;
 if(a<b)
 {
  temp=a;
  a=b;
  b=temp;
 }
 if(a%b==0)
  return b;
 else
  return GCD(a%b,b);
}

public static int Iscoprime(int a, int b)
{
 int ret=0;
 if(GCD(a,b)==1)
  ret=1;
 return ret;
}

public static Vector totientEx(int num)
{
	Vector v = new Vector();
	if(num==1)
	{
		v.add(1); 
		return v;
	}
	for(int i=1;i<=num-1;i++)
	{
		if(Iscoprime(num,i)==1)
		{
			v.add(i);  
		}
	}
	return v;
}
 
public static void main(String[] args)
{
	int Arr[]={2,4,8,16};
	for(int i=0;i<4;i++)
	{
		int n=Arr[i];
		Vector v = totientEx(n);
		int size = v.size();
		System.out.printf("φ(%d)=%d，模%d的既约剩余类：\n",n,size,n);
		//遍历Vector中的元素
		for(int j = 0;j < v.size();j++)
		{ 
			System.out.println(v.get(j));
		}
	}
}

}