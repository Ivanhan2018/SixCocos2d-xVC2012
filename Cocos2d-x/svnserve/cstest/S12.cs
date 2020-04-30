using System;

namespace Sn
{
 class MainClass
 {   

  public static void S12(){
   System.IO.StreamWriter file = new System.IO.StreamWriter(@"S12.txt", false);
   file.AutoFlush = true;
   file.WriteLine("static char *abcdefghijkl[] = {");
   int nCount = 0;
   int n=12;
   int a,b,c,d,e,f,g,h,i,j,k,l;  
   for (a=1;a<=n;a++)     
   for (b=1;b<=n;b++)      {  
    if (b==a)      continue;  
    for (c=1;c<=n;c++)      {  
     if(c==a||c==b)   continue;
     for (d=1;d<=n;d++)      {  
      if (d==a||d==b||d==c)    continue;
      for (e=1;e<=n;e++)      {  
       if (e==a||e==b||e==c||e==d)    continue;
       for (f=1;f<=n;f++)      {  
        if (f==a||f==b||f==c||f==d||f==e)    continue;
        for (g=1;g<=n;g++)      {  
         if (g==a||g==b||g==c||g==d||g==e||g==f)    continue;
         for (h=1;h<=n;h++)      {  
          if (h==a||h==b||h==c||h==d||h==e||h==f||h==g)    continue;
          for (i=1;i<=n;i++)      {  
           if (i==a||i==b||i==c||i==d||i==e||i==f||i==g||i==h)    continue;
           for (j=1;j<=n;j++)      {  
            if (j==a||j==b||j==c||j==d||j==e||j==f||j==g||j==h||j==i)    continue;
            for (k=1;k<=n;k++)      {  
             if (k==a||k==b||k==c||k==d||k==e||k==f||k==g||k==h||k==i||k==j) continue;
             for (l=1;l<=n;l++)      {  
              if (l==a||l==b||l==c||l==d||l==e||l==f||l==g||l==h||l==i||l==j||l==k) continue;
         string line=string.Format("\"{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11}\",",a,b,c,d,e,f,g,h,i,j,k,l);
         file.WriteLine(line);// 直接追加文件末尾，换行
         nCount++;
             }
            }
           }
          }
         }
        }
       }  
      }  
     }  
    }
   } 
   file.WriteLine("};");
   Console.WriteLine ("nCount="+nCount);
   Console.ReadLine ();
  }

  public static void Main (string[] args)
  {
   S12();
  }
 }
}