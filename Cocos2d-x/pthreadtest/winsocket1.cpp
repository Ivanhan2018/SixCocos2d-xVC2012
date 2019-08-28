#include"windows.h"
#include<stdio.h>
#pragma comment(lib,"WSOCK32.LIB")
#define MYCALL __stdcall
int main()
{
int WSAReturn;
WSADATA WSAData;
hostent *h=0;
//char *str="HEMEI-20180102W";
char str[256];
gethostname(str,256);
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
WSAReturn=F3(0x0202,&WSAData);
if(WSAReturn==0)h=F1(str);
if(h)
{
printf("Host name : %s\n", h->h_name);
printf("IP Address : %s\n",F2(*((struct in_addr *)h->h_addr)));
char ip[256];
wsprintf(ip,"%d.%d.%d.%d",(h->h_addr_list[0][0]&0x00ff),(h->h_addr_list[0][1]&0x00ff),(h->h_addr_list[0][2]&0x00ff),(h->h_addr_list[0][3]&0x00ff));
MessageBox(NULL,ip,h->h_name,MB_OK);
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

