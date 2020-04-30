using System;
using System.Text;

public sealed class StringBuilderTest 
{
    static void Main() 
    {
        // Create a StringBuilder that expects to hold 50 characters.
        // Initialize the StringBuilder with "ABC".
        StringBuilder sb = new StringBuilder("ABC", 50);

        // Append three characters (D, E, and F) to the end of the StringBuilder.
        //sb.Append(new char[] { 'D', 'E', 'F' });

        // Append a format string to the end of the StringBuilder.
        //sb.AppendFormat("GHI{0}{1}", 'J', 'k');
		sb.AppendFormat("{0}Append方法{1}AppendFormat方法", 'a', 'b');
        // Display the number of characters in the StringBuilder and its string.
        Console.WriteLine("{0} chars: {1}", sb.Length, sb.ToString());

        // Insert a string at the beginning of the StringBuilder.
        //sb.Insert(0, "Alphabet: ");
		sb.Insert(0, "Insert方法");
        // Replace all lowercase k's with uppercase K's.
        //sb.Replace('k', 'K');
		sb.Replace('A', 'a');
        // Display the number of characters in the StringBuilder and its string.
        Console.WriteLine("{0} chars: {1}", sb.Length, sb.ToString());
    }
}
