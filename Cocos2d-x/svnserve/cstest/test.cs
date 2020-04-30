using System;

class test 
{
public static void Main(String[] args) 
{
	test t=new test(); 
    t.show(); 
}

public void show() 
{ 
 for(int i=1;i<=9;i++) 
  for(int j=1;j<=i;j++) 
  { 
   //System.Out.Printf("%d*%d=%-3d",j,i,j*i); 
   Console.WriteLine("{0}*{1}={2}",j,i,j*i);
  } 
  Console.WriteLine("\n"); 
} 

} 
