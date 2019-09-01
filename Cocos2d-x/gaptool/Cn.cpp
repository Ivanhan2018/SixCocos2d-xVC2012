//  生成循环群C_n的凯莱表Cn.exe
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
 char sz[100]={0};
 if(argc<2)
 {
  printf("请输入循环群C_n的阶n：");
  scanf("%s",sz);
 }
 else
  strcpy(sz,argv[1]);

 int n=atoi(sz);
 char sz1[100]={0};
 sprintf(sz1,"C%d.txt",n);

 // 生成循环群C_n的凯莱表
 FILE *fp=fopen(sz1,"w");
 for(int i=0;i<n;i++)
 {
  for(int j=i;j<i+n;j++)
  {
   fprintf(fp,"%d ",j%n+1);
  }
  fprintf(fp,"\n");
 }
 fclose(fp);

 //system("pause");
 return 0;
}