#include <stdio.h>

int main()
{
   int pid;

   pid = fork( );  // fork another process
   if (pid < 0) {  // parent process, an error occurred
	   printf("parent: fork failed\n");
	   exit(-1);
   } else if (pid > 0) {  // parent process
	   sleep(2);            // position 1
	printf("parent: fork succeed\n");
	printf("parent: child process number is %d\n", pid);
	pid = getpid();
	printf("parent: my pid is %d\n", pid);
	wait(NULL);  // wait for the child to complete
	printf("parent: child completed\n");
	exit(0);
	   } else {       // pid==0, child process
	sleep(5);       // position 2
	pid = getpid();
	printf("child: my pid is %d\n", pid);
	pid = getppid();
	printf("child: my parent pid is %d\n", pid);
	sleep(30);      // position 3
	execlp("/bin/ls", "ls", NULL);   // position 4
	printf("child: can you see this line on the screen?\n");
   }
   return 0;   
}