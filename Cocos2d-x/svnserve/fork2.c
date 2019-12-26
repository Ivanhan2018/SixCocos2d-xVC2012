#include <stdio.h>

int z = 0;

int main()
{
	int pid = getpid();
 	if (pid = fork())  {
		z = pid;	
		printf("z1 = %d\n", z);
	} else {
		z = pid;
		printf("z2 = %d\n", z);
	}
	printf("all done, pid = %d\n", pid);
    return 0;
}