#include <unistd.h>//sleep
//#include <pthread.h>
#include <thread>
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
    return 0;
}

int main(int argc, char *argv[])
{
    std::thread workerThreads[2]; 
	int j[2]={0,1};	
    for (int i=0; i<2; ++i)  
    {  
        workerThreads[i] = std::thread(ChildFunc, &j[i]);  
    }  
    for (auto& workerThread : workerThreads)  
    {  
        workerThread.join();  
    }  
    printf("main thread\n");

    return 0;
}