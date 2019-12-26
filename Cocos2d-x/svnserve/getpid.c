#include <stdio.h>

int main()
{
	int pid;

	pid = getpid();
	printf("my pid is %d\n", pid);

	pid = getppid();
	printf("my parent's pid is %d\n", pid);

	sleep(40);
    return 0;
}