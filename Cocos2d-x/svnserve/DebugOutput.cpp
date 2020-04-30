#include<iostream>
//#include<cstring>
//#include<cstdarg>
#include<stdarg.h>
//using namespace std;


//输出窗口输出调试信息
static void DebugOutput(const char* format,...)
{
//#ifdef _DEBUG
	va_list arg_ptr;
	char str[2048]={0};
	va_start(arg_ptr,format);
	vsprintf(str,format,arg_ptr);
	va_end(arg_ptr);
	//strcat(str,"\r\n");
	puts(str);
//#endif
}

int main()
{
	int a=3;
    DebugOutput("a=%d",a);
	return 0;
}