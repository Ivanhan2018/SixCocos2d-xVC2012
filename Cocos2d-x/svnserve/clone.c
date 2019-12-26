#define _GNU_SOURCE   /*注意摆放位置*/         
#include <sched.h>   /*注意摆放位置*/   
#include <stdio.h>

char stack[1024];		// used by the cloned process as stack space
int  sharedVariable;	// the shared variable

int clone_process(void)
{
	while (1) {
		sleep(2);
		sharedVariable++;
		printf("cloned process: %d \n", sharedVariable);
	}
    return 0;	
}

int main()
{
	int rc;

	rc = clone(clone_process, &stack[1024], CLONE_VM, 0);
	if (rc < 0) {
		printf("main process: clone() failed \n");
		exit(1);
	}
	while (1) {
		sleep(3);
		sharedVariable--;
		printf("main process: %d \n", sharedVariable);
	}
    return 0;
}