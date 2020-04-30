/*
pthread_join, pthread_exit
*/
 
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

typedef void * (*THREADFUNC)();

//全局变量g从0加到1998
int g;
unsigned long ChildProcess(void* p)
{
	for (int i = 1; i < 1000; i ++) {
		g ++;
		printf( "This is Child Thread: %d\n", g );
	}
	//ExitThread(0);
	//_endthreadex(0);
	pthread_exit((void*)0);  //线程退出
	return 0;
};
 
int main(int argc, char * argv [ ])
{
    int iRet = 0;
    void *rval = NULL;
    pthread_t pid1;
	g = 0;
	//CreateThread( NULL, 0, ChildProcess, NULL, 0, &threadID );
    //HANDLE hThrd = (HANDLE)_beginthreadex(NULL,0,(PBEGINTHREADEX_THREADFUNC)ChildProcess,(LPVOID)1,0,(unsigned int *)&threadID);
    iRet = pthread_create(&pid1, NULL, (THREADFUNC)ChildProcess, NULL);     //创建一个线程
    if(0 != iRet)
    {
        printf("pthread_create error, %s,%d\n", (char *)strerror(errno), errno);
        return -1;
    }
    else {
        printf("Thread launched\n");
    }
	for (int i = 1; i < 1000; i ++) {
		g ++;
		printf( "This is Parent Thread: %d\n", g );
	}
    pthread_join(pid1, &rval);  //线程等待，线程退出的值存放在rval中
    printf("rval= %d\n", (int)rval);
    
    return 0;
}