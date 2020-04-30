/*
pthread_join, pthread_exit
*/
 
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

typedef void * (*THREADFUNC)();

//全局变量
long num1=0,num2=0;
int bContinue=1;

//CRITICAL_SECTION cs;   //新建一CRITICAL_SECTION
pthread_mutex_t mylock1;

unsigned long ThreadFunc(void* p)
{
    while(bContinue)
    {
       //EnterCriticalSection(&cs);      //进入CRITICAL_SECTION
	   int intResult1 = pthread_mutex_lock(&mylock1);
       num1++;
       num2++;
	   pthread_mutex_unlock(&mylock1);
       //LeaveCriticalSection(&cs);       //退出CRITICAL_SECTION
     }
     return 0;
};
 
int main(int argc, char * argv [ ])
{
    pthread_mutex_init(&mylock1, NULL);
	int iRet[2] = {0};
    void *rval[2] = {NULL,NULL};
    pthread_t pid[2]= {0};
	for(int i=0;i<2;i++){
		iRet[i] = pthread_create(&pid[i], NULL, (THREADFUNC)ThreadFunc, NULL);
		if(0 != iRet[i])
		{
			printf("pthread_create i=%d error, %s,%d\n",i, (char *)strerror(errno), errno);
			pthread_mutex_destroy(&mylock1);
			return -1;
		}
		else {
			printf("Thread i=%d launched\n",i);
		}
	}
	sleep(3);
	bContinue=0;
    pthread_join(pid[0], &rval[0]);
    pthread_join(pid[1], &rval[1]);	
    //DeleteCriticalSection(&cs);  //销毁CRITICAL_SECTION
    printf("num1:%d\tnum2:%d\n",num1,num2); 
	
	pthread_mutex_destroy(&mylock1);
    return 0;
}