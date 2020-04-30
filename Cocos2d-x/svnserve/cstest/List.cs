using System;
//using System.Collections;
using System.Collections.Generic;

namespace ConsoleApplication1
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Class1
	{
		static void Main(string[] args)
		{
			Console.WriteLine("The first app in Beginning C# Programming!");
			
			List<int> vHitFishID = new List<int>{1, 3, 5, 4, 9, 6};
			List<int> vDeadFishID = vHitFishID.GetRange(2, 2);
			Console.WriteLine("Count={0}",vHitFishID.Count);	
			List<int>.Enumerator iter = vHitFishID.GetEnumerator();
			//foreach (int d in vHitFishID)
			while (iter.MoveNext())
			{
				Console.Write("{0} ",iter.Current);
			}
			Console.WriteLine("");
			for (int i = 0; i < vDeadFishID.Count; i++)
			{
				Console.Write("{0} ",vDeadFishID[i]);
			}
			Console.WriteLine("");
		}   
	}
}

