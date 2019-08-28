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

void hello1(char* str)//线程函数名称
{
 printf("%s",str);//输出若干次，Scan新线程
}

void Start()
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
}

void Start1()
{
char* s="新年好!\n";//传递给线程函数的参数
HANDLE hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)hello1,s,0,NULL);
Sleep(2000);//主线程等待2秒
if(CloseHandle(hThread))//关闭打开的对象句柄
{
printf("\nClose Thread Success!\n");//总共输出10次，main主线程
}
else
{
printf("\nClose Thread Failed!");
}
}

int main()
{
//Start1();
Start();
cout<<INFINITE<<endl;//4294967295
system("pause");
return 0;
}