using System;
//第一个C#程序“Hello World!”
namespace HelloWorld
{
class Hello2 
{
static void Main() 
{
int x = 1;
string s = x.ToString() + " ";
s += (x == 1 ? "man" : "men");//1 man
Console.WriteLine(s);
}
}
}
