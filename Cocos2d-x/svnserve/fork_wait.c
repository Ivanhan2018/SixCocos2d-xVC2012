#include <stdio.h>

int main()
{
	int pid;

	printf("begin ...\n");
	pid = fork();
	if (pid == 0) {
		printf("I am the child\n");
		sleep(20);
		exit(0);
	} else {
		printf("the child process pid is %d\n", pid);
		wait(NULL);
		printf("child process has terminated. \n");
		sleep(10);
	}
    return 0;	
}
