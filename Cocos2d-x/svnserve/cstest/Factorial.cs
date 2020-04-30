using System;
class Factorial
{
public static void Main(string[] args)
{
long nFactorial = 1, nCurDig=1;
long nComputeTo = Int64.Parse(args[0]);
try
{
checked
{
for (;nCurDig <= nComputeTo; nCurDig++)
nFactorial *= nCurDig;
}
}
catch (OverflowException oe)
{
Console.WriteLine("Computing {0} caused an overflow exception", nComputeTo);
return;
}
Console.WriteLine("{0}! is {1}",nComputeTo, nFactorial);
}
}