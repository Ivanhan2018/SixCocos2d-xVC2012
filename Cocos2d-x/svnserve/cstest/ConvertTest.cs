using System;

namespace Ch04Ex01
{
	/// <summary>
	/// Summary description for ConvertTest
	/// </summary>
	class ConvertTest
	{
		static void Main3(string[] args)
		{
            double firstNumber, secondNumber;
            string userName;
            Console.WriteLine("Enter your name:");
            userName = Console.ReadLine();
            Console.WriteLine("Welcome {0}!", userName);
            Console.WriteLine("Now give me a number:");
            firstNumber = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Now give me another number:");
            secondNumber = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("The sum of {0} and {1} is {2}.", firstNumber,
                           secondNumber, firstNumber + secondNumber);
            Console.WriteLine("The result of subtracting {0} from {1} is {2}.", 
                           secondNumber, firstNumber, firstNumber - secondNumber);
            Console.WriteLine("The product of {0} and {1} is {2}.", firstNumber,
                           secondNumber, firstNumber * secondNumber);
            Console.WriteLine("The result of dividing {0} by {1} is {2}.", firstNumber,
                           secondNumber, firstNumber / secondNumber);
            Console.WriteLine("The remainder after dividing {0} by {1} is {2}.", firstNumber,
                           secondNumber, firstNumber % secondNumber);
            Console.Read();
		}

		 static void Main2(string[] args) 
		 { 
			 Console.Write("请输入数组大小(0-50):"); 
			 string s = Console.ReadLine(); 
			 int n = int.Parse(s); 
			 Console.Write("请给每个数赋值:"); 
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
			 Console.WriteLine("最小值为{0},最大值为{1}.\n重新排序的数组为:", MyArray[0], MyArray[n - 1]); 
			 try 
			 {  
			 foreach (int i in MyArray) 
			 { 
			 Console.Write(i.ToString() + "\t"); 
			 } 
			 } 
			 catch (Exception e) { Console.WriteLine(e.ToString()); } 
		 } 		
		
		static void Main(string[] args)
		{
            Console.WriteLine("Enter an integer:");
            int myInt = Convert.ToInt32 (Console.ReadLine());
            Console.WriteLine("Integer less than 10? {0}", myInt < 10);
            Console.WriteLine("Integer between 0 and 5? {0}", (0 <= myInt) && (myInt <= 5));
            Console.WriteLine("Bitwise AND of Integer and 10 = {0}", myInt & 10); 
			//Console.Read();
			Main2(args);
			Main3(args);
		}
	}
}