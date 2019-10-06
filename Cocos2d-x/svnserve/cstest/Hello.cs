using System;
// 第一个C#程序
namespace HelloWorld
{
class Hello 
{
static void Main() 
{
double [][]shapes=new double[4][];
//之后shapes那4个元素的值还没有被初始化,还是null,不能直接使用shapes[0]~shapes[3] 
shapes[0]=new double[1]{10};//圆 
shapes[1]=new double[4]{3,4,3,4};//四边形 
shapes[2]=new double[3]{3,4,5};//三角形
Console.WriteLine(shapes[2].Length);//3 
shapes[3]=new double[5]{5,5,5,5,5};//五边形 
Console.WriteLine(shapes[3].Length);//5 
}
}
}
