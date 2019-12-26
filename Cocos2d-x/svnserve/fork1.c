#include <stdio.h>

int main()
{
    int i=0;//‘for’ loop initial declarations are only allowed in C99 mode
	for (i=0; i<10; i++) {
		int pid = fork();
		if (pid == 0) {
			printf("child %d starts running\n", i);
			sleep(60+i*5);	// every child sleeps for a different period
			exit(0);
		} else {
			printf("parent: generate a new child with pid %d\n", pid);
			sleep(1);
		}
	}
    return 0;
}