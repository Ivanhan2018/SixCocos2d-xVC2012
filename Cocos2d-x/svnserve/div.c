//div.c将两个整数相除, 返回商和余数
#include <stdio.h>
#include <stdlib.h>
int main (void)
 {
   div_t result;//结构体
   result = div(11, 3);//MSVCRT.DLL中div
   printf("11 divided by 3 is %d Remainder %d\n",
     result.quot, result.rem);
  //getchar();
  return 0;
 }