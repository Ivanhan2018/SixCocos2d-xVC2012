#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>//gethostname
#include <limits.h>//HOST_NAME_MAX 
#endif
#include <string>
#include <iostream>
using namespace std;

int main()
{
#ifdef WIN32
 // 获取计算机名称的最大长度
 DWORD nSize=MAX_COMPUTERNAME_LENGTH+1;
 char Name[50]={0};
 // 获取计算机名称F5399C2E8A294C9
 GetComputerName(Name,&nSize);
#else
unsigned int nSize=HOST_NAME_MAX+1;
 char Name[nSize]={0};
 int iRet=gethostname(Name, nSize);
#endif
 string str=Name;
 cout << str<< endl;
 cout << Name<< endl;
 cin.get();
 return 0;
}
