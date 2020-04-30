#include <unistd.h>//sleep
#include <pthread.h>
#include <stdio.h>

unsigned int ChildFunc(void *pParam)
{
	int num=*(int *)pParam;
    // Do some	
	sleep(2*num+2);
    if(num==0)
        printf("Hi\n");
    if(num==1)
        printf("world\n");
    // Task finished
	//_endthreadex(0);
	//return 0;
}

int main(int argc, char *argv[])
{
	pthread_t h_thread[2];
	int j[2]={0,1};
	for(int i=0;i<2;i++)
	{
		//h_thread[i]=(HANDLE)::_beginthreadex(NULL,0,(PBEGINTHREADEX_THREADFUNC)ChildFunc,&j[i], 0, (unsigned int *)&thread_ID);
		//h_thread[i]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFunc,&j[i],0,&thread_ID);//also OK
        int ret=pthread_create(&h_thread[i], NULL, (void *(*)(void *))ChildFunc, &j[i]);
		if(ret==0)
		{
			printf("created %d ok\n", i); // Creating 2 asynchronous tasks
			pthread_join(h_thread[i],NULL);
		}
	}
	//WaitForMultipleObjects(2,h_thread,TRUE,INFINITE);//监测多个对象
	printf("main thread\n");

    return 0;
}