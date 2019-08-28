#include"windows.h"
#include<iostream>
using namespace std;

void hello(int* i)
{
    if(*i==0)
                cout<<"Hi"<<endl;
    if(*i==1)
                cout<<"world"<<endl;
}


int main()
{
HANDLE   h_thread[2];
DWORD   thread_ID;

int   i;
int   j[2]={0,1};

for(i=0;i<2;i++)
h_thread[i]=CreateThread(
            NULL,//必须为NULL
            0,//一般为0 ，表示堆栈与外部大小相同
            (LPTHREAD_START_ROUTINE)(hello),//线程函数名称
            &j[i],//传递给线程函数的参数，如果为多个，自定义结构体
            0,//0表示创建线程后立即启动线程，如果不是立即启动需要调用ResumeThread函数
            &thread_ID//用来标记该线程的名称
          );//由CreateThread指定一个函数，线程就从那个函数处开始运行
cout<<thread_ID<<endl;//3660
WaitForMultipleObjects(2,h_thread,TRUE,INFINITE);//监测多个对象
cout<<INFINITE<<endl;//4294967295
system("pause");
return 0;
}