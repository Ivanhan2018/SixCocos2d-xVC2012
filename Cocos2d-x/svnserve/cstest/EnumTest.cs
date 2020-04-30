using System;

public enum Color {Green=10, Orange=20, Red=30, Blue=40}
public class EnumTest
{
	public static void Main()
	{
		Console.WriteLine("Possible color choices: ");
		//Enum.GetNames returns a string array of named constants for the enum
		foreach(string s in Enum.GetNames(typeof(Color)))//调用 Enum 类型的 GetNames 方法来显示枚举的可用常量
		{
			Console.WriteLine(s);
		}
		Color FavoriteColor = Color.Blue;//然后，它将值赋给枚举，并显示该值。
		Console.WriteLine("Favorite Color is {0}",FavoriteColor);
		Console.WriteLine("Favorite Color value is {0}", (int)FavoriteColor);
	}
}