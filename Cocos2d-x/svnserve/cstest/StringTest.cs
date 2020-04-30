using System;

public class StringTest {
	static void Main4(string[] args)
	{
		int myInteger;
		string myString;
		myInteger = 17;
		myString = "\"myInteger\" is";
		Console.WriteLine("{0} {1}.", myString, myInteger);
		Console.Read();//"myInteger" is 17.
	}	
	
	public static void Main3()
	{
		string s1 = "original string";
		string s2 = s1; //注意此时会创建一个新对象
		Console.WriteLine( "s1 is " + s1 );
		Console.WriteLine( "s2 is " + s2 );
		s1 = "changed string";
		Console.WriteLine( "s1 is now " + s1 );
		Console.WriteLine( "s2 is now " + s2 );
	}	
	
    public static void Main2() {

        string [] info = {"Name: Felica Walker", "Title: Mz.", "Age: 47", "Location: Paris", "Gender: F"};
        int found = 0;

        Console.WriteLine("The initial values in the array are:");
        foreach (string s in info)
            Console.WriteLine(s);

        Console.WriteLine("{0}We want to retrieve only the key information. That is:", Environment.NewLine);        

        foreach (string s in info) {
            found = s.IndexOf(":");//定位字符串中第一次出现某个给定子字符串或字符的位置
            Console.WriteLine(s.Substring(found + 1).Trim());//在字符串中获取给定位置的子字符串,删除首尾的空白

        }
    }	
	
    public static void Main() {
		string s ="Name: 第3章 为子系统设防";
		Console.WriteLine(s.Substring(2).Trim());
		int i=10;
		Console.WriteLine(i.ToString());
		
		Main2();
		Main3();
		Main4(null);		
    }
}