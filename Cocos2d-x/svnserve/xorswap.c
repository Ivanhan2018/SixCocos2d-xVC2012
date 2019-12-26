// 在一行里交换两个整型数：用异或操作符可以做到
#include<stdio.h>

int main()
{
int a=5, b=4;
a^=b^=a^=b;
printf("a=%d,b=%d\n",a,b);
return 0;
}