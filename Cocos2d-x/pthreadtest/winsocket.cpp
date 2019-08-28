#include"windows.h"
#include<stdio.h>
#define MYCALL __stdcall
int main()
{
int WSAReturn;
WSADATA WSAData;
hostent *h;
char *str="HEMEI-20180102W";
typedef struct hostent*(MYCALL *pF1)(char *szHost);
typedef char*(MYCALL *pF2)(struct in_addr in);
typedef int(MYCALL *pF3)(WORD wVersionRequested,LPWSADATA lpWSAData);
typedef int(MYCALL *pF4)(void);  
HINSTANCE hDLL;
pF1 F1;
pF2 F2;
pF3 F3;
pF4 F4;  
hDLL=LoadLibrary("WS2_32.DLL");
F1=(pF1)GetProcAddress (hDLL, "gethostbyname");
F2=(pF2)GetProcAddress (hDLL, "inet_ntoa");
F3=(pF3)GetProcAddress (hDLL, "WSAStartup");
F4=(pF4)GetProcAddress (hDLL, "WSACleanup");
WSAReturn=F3(0x0101,&WSAData); 
h=F1(str);
if(h)
{
printf("Host name : %s\n", h->h_name);
printf("IP Address : %s\n",F2(*((struct in_addr *)h->h_addr)));
}
else
{
printf("h==0\n");
}
F4(); 
FreeLibrary(hDLL);
getchar();
return 0;
}