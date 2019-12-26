#include<unistd.h>
#include<stdio.h>

int main()
{  
if(fork() == 0)
{ 
// 子进程程序
for (int i = 1; i < 10; i ++ ) 
printf("This is child process\n"); 
} 
else
{ 
// 父进程程序
for (int i = 1; i < 10; i ++ ) 
printf("This is parent process\n"); 
}
getchar(); 
return 0;
}