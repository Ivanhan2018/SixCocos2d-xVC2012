#include <thread>  
#include <iostream>  
#include <string>  
#include <chrono>  
#include <assert.h>  
#include <mutex>  
int counter=0;  
std::mutex mtx;  
void func()  
{  
    for (int i=0; i<10000; ++i)  
    {  
            mtx.lock();  
            ++counter;  
            mtx.unlock();  
    }  
}  
  
int main()  
{  
    std::thread workerThreads[10];  
    for (int i=0; i<10; ++i)  
    {  
        workerThreads[i] = std::thread(func);  
    }  
    for (auto& workerThread : workerThreads)  
    {  
        workerThread.join();  
    }  
    std::cout << counter << " successful increases of the counter"<<std::endl;  
  
    return 0;  
} 