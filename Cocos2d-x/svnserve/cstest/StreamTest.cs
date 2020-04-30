using System;
using System.IO;

class StreamTest
{
  static string filename = "StreamTest.txt";
  static void Main(string[] args)
  {
   CreateFile();
   ReadFile(filename);
   AppendFile(filename);
  }
  //创建文件
  public static void CreateFile()
  {
   StreamWriter sw;
   sw = File.CreateText(filename);
   sw.WriteLine("This is the first line!");
   sw.WriteLine("This is the Second line!");
   sw.Close();
   Console.WriteLine("文件建立成功！");
  }
  //读文件
  private static void ReadFile(string path)
  {
   StreamReader sr;
   sr = File.OpenText(path);
   string line;
   line = sr.ReadLine();
   while(line != null)
   {
    Console.WriteLine(line);
    line = sr.ReadLine();
   }
   sr.Close();
  }
  //追加文件
  private static void AppendFile(string path)
  {
   StreamWriter sw;
   sw = File.AppendText(path);
   sw.WriteLine("哈哈，追加成功了！");
   sw.Close();
   Console.WriteLine("追加文件成功！");
  }
}