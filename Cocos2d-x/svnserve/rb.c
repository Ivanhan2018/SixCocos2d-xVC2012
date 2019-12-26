// 读取文件的指定字节
#include<stdio.h>

int main()
{
FILE *fp;unsigned char ch;char fn[20];long a,b,i;
printf("continue with pressing 'y':");
while(getchar()=='y'){
printf("\nfilename,startpos,endpos:");
scanf("%s%ld%ld",fn,&a,&b);//输入文件名，起始字节和终止字节即可
fp=fopen(fn,"rb");
fseek(fp,a-1,0);
for(i=a;i<=b;i++)
{ch=fgetc(fp);
if(ch>=32&&ch<=126)//兼容文本文件
putchar(ch);
else printf("%u ",ch);
}
fclose(fp);
printf("\ncontinue with pressing 'y':");}
getchar();
return 0;
}