#include <stdio.h>

int main()
{
	int pid1, pid2, pid3, pid4;

	pid1 = fork();
	if (pid1 == 0) {
		printf("first child\n");
		sleep(10);
		printf("first child terminates\n");
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0) {
		printf("second child\n");
		sleep(20);
		printf("second child terminates\n");
		exit(0);
	}
	pid3 = fork();
	if (pid3 == 0) {
		printf("third child\n");
		sleep(30);
		printf("third child terminates\n");
		exit(0);
	}
	pid4 = fork();
	if (pid4 == 0) {
		printf("fourth child\n");
		sleep(40);
		printf("fourth child terminates\n");
		exit(0);
	}

	waitpid(pid2, NULL, NULL);
	printf("parent: second child terminated\n");
	return 0;
}