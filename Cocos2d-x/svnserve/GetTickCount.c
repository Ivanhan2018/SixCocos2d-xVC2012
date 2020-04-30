/*
pthread_join, pthread_exit,clock_gettime
*/
 
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

// 返回自系统开机以来的毫秒数（tick）
unsigned long GetTickCount()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

typedef void * (*THREADFUNC)();

unsigned long ThreadFunc(void* p)
{
    int val;

    for (int i=0; i<100; i++)
    {
		for (int j=0; j<100; j++)
		{
			val=i*j;
			printf("i=%d,j=%d,i*j=%d\n",i,j,val);
		}
    }
    
    return 0;
};
 
int main(int argc, char * argv [ ])
{
    unsigned long begin;
    unsigned long elapsed;
	printf("CLOCK_MONOTONIC=%d\n",CLOCK_MONOTONIC);
    printf("sizeof(unsigned int)=%d\n",sizeof(unsigned int));	
    printf("sizeof(unsigned long)=%d\n",sizeof(unsigned long));
    printf("sizeof(void *)=%d\n",sizeof(void *));	
    printf("sizeof(long long)=%d\n",sizeof(long long));

    puts("Timing normal function call...");
    begin = GetTickCount();
    ThreadFunc(0);
    elapsed = GetTickCount()-begin;
    printf("Function call took: %d.%.03d seconds\n\n",elapsed/1000, elapsed%1000);//0.092 seconds
    //return 0;
    puts("Timing thread + busy loop...");
    begin = GetTickCount();

    int iRet = 0;
    void *rval = NULL;
    pthread_t pid1;
    iRet = pthread_create(&pid1, NULL, (THREADFUNC)ThreadFunc, NULL);     //创建一个线程
    if(0 != iRet)
    {
        printf("pthread_create error, %s,%d\n", (char *)strerror(errno), errno);
        return -1;
    }
    else {
        printf("Thread launched\n");
    }
    pthread_join(pid1, &rval);  //线程等待，线程退出的值存放在rval中
    elapsed = GetTickCount()-begin;
    printf("Thread + busy loop took: %d.%.03d seconds\n",elapsed/1000, elapsed%1000);//1.162 seconds   
	
    return 0;
}