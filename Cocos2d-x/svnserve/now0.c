// 得到当前的时间
#include<stdio.h>
#include<time.h>

int main()
{
time_t now;
time(&now);
printf("Its %.24s\n",ctime(&now));
return 0;
}