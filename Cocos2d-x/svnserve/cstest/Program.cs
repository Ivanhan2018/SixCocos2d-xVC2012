using System; 
namespace MyExample 
{ 
 class Program 
 { 
 static void Main(string[] args) 
 { 
 Console.Write("input array size n(0-50):"); 
 string s = Console.ReadLine(); 
 int n = int.Parse(s); 
 Console.Write("input n numbers:"); 
 int[] MyArray = new int[n]; 
 for(int i=0;i<n;i++) 
 { 
 Console.Write("a[{0}]=", i + 1); 
 string s1 =Console.ReadLine(); 
 MyArray[i] = int.Parse(s1); 
 } 
 for(int i=0;i<MyArray.Length;i++) 
 for (int j = i; j < MyArray.Length; j++) 
 { 
 if (MyArray[i] > MyArray[j]) 
 { 
 int t; 
 t = MyArray[i] + MyArray[j]; 
 MyArray[i] = t - MyArray[i]; 
 MyArray[j] = t - MyArray[i]; 
 } 
 }; 
 Console.WriteLine("min:{0},max:{1}.\narray after sorted:", MyArray[0], MyArray[n - 1]); 
 try 
 {  
 foreach (int i in MyArray) 
 { 
 Console.Write(i.ToString() + "\t"); 
 } 
 } 
 catch (Exception e) { Console.WriteLine(e.ToString()); } 
  Console.WriteLine("\n");
 } 
 } 
} 
