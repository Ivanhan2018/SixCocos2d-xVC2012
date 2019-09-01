#include"windows.h"
#include<iostream>
#include<functional>
using namespace std;

int g_i=2;

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

int hello2(LPVOID lpparam)
{
int num=(int)lpparam;
g_i++;
printf("%d,%d\n",num,g_i);//1,3
return 0;
}

DWORD WINAPI hello3(LPVOID lpParameter,bool bChildThread){
for (int i = 1; i < 1000; i ++) {
g_i++;
printf("g_i=%d,bChildThread=%d\n", g_i,bChildThread);
}
if(bChildThread)ExitThread(0);
return 0;
};

//?一个用InterlockedIncrement，一个用++呢
long num1=0,num2=0;
BOOL bContinue=TRUE;
DWORD WINAPI hello4(LPVOID lpParam)
{
     while(bContinue)
     {
        num1++;
        num2++;
     }
     return 0;
}

CRITICAL_SECTION cs;   //新建一CRITICAL_SECTION
//让num1=num2
DWORD WINAPI hello4_cs(LPVOID lpParam)
{
    while(bContinue)
    {
       EnterCriticalSection(&cs);      //进入CRITICAL_SECTION
       num1++;
       num2++;
       LeaveCriticalSection(&cs);       //退出CRITICAL_SECTION
     }
     return 0;
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

void Start2()
{
int num=1;
HANDLE hthread;
DWORD dwthreadid;
//NULL,//必须为NULL
//0,//一般为0 ，表示堆栈与外部大小相同
//(LPTHREAD_START_ROUTINE)(hello2),//线程函数名称
//(LPVOID)num,//传递给线程函数的参数，如果为多个，自定义结构体
//0,//0表示创建线程后立即启动线程，如果不是立即启动需要调用ResumeThread函数
//&dwthreadid//用来标记该线程的名称
hthread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)(hello2),(LPVOID)num,0,&dwthreadid);
if(hthread==NULL)
{
printf("线程创建失败\n");
}
WaitForSingleObject(hthread,2000);//监测一个对象
CloseHandle(hthread);
}

void Start3()
{
//int threadID;
unsigned long threadID;
g_i = 0;
auto hello3t=[](LPVOID lpParameter)->DWORD{return hello3(lpParameter,true);};//不能用std::bind(hello3,placeholders::_1,true)
CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)hello3t, NULL, 0, &threadID );
hello3(0,false);
}

void Start4()
{
     DWORD dwThreadId,dwThreadId2;
 
     HANDLE hThread[2];

     hThread[0]=CreateThread(NULL,
                              0,
                              hello4,
                              NULL,
                              0,
                              &dwThreadId);

     hThread[1]=CreateThread(NULL,
                              0,
                              hello4,
                              NULL,
                              0,
                              &dwThreadId2);


      Sleep(3000);

      bContinue=FALSE;

      WaitForMultipleObjects(2,hThread,0,INFINITE);

      CloseHandle(hThread[0]);
      CloseHandle(hThread[1]);

      //num1:304753272  num2:259008517 
      printf("num1:%d\tnum2:%d\n",num1,num2);
}

void Start4_cs()
{
    DWORD dwThreadId,dwThreadId2;
 
    HANDLE hThread[2];

    InitializeCriticalSection(&cs);  //初始化CRITICAL_SECTION

    hThread[0]=CreateThread(NULL,
                            0,
                            hello4_cs,
                            NULL,
                            0,
                            &dwThreadId);

                            hThread[1]=CreateThread(NULL,
                            0,
                            hello4_cs,
                            NULL,
                            0,
                            &dwThreadId2);


      Sleep(3000);

      bContinue=FALSE;

      WaitForMultipleObjects(2,hThread,0,INFINITE);

      CloseHandle(hThread[0]);
      CloseHandle(hThread[1]);

 

      DeleteCriticalSection(&cs);  //销毁CRITICAL_SECTION
      //num1:5006660    num2:5006660
      printf("num1:%d\tnum2:%d\n",num1,num2); 
}

int main(int argc, char* argv[])
{
//Start1();
//Start();
//Start2();
//Start3();
//Start4();
Start4_cs();
cout<<INFINITE<<endl;//4294967295
system("pause");
return 0;
}