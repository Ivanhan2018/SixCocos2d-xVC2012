// 得到RGB值的分量
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>

//AND，按位与
int Red(int color)
{
   return color & 0xff;
}
int Green(int color)
{
   return (color & 0xff00)/0xff;
}
int Blue(int color)
{
   //return (color & 0xff0000)/0xff00;
   return (color / 0x10000)& 0xff;
}

const int nWinBlueColor=16711680;
const int nWinRedColor=255;
const int nWinBlue255G195R198Color=16761798;

const char * WinRGBInfo(int color)
{
	static char sz[100]={0};
    sprintf(sz,"WinColor=%d,R=%d,G=%d,B=%d",color,Red(color),Green(color),Blue(color));
	return sz;
}

struct D3DCOLOR
{
public:
   D3DCOLOR(int argb)
   {
       memcpy(this,&argb,sizeof(int));
   }
public:
   unsigned char b1;//第一个字节分配给蓝色分量
   unsigned char g2;
   unsigned char r3;
   unsigned char a4;//第四个字节分配给Alpha分量
};

int main(int argc, char *argv[])
{
	if( argc < 2 )
	{
		printf("Usage:  WinRGBInfo [-a] color\n");		
		return 1;
	}
	if(strcmp(argv[1],"-a")==0 && argc >=3)
	{
        int p=10;
        std::string str=argv[2];
		if(str.size()>2 && str.substr(0,2)=="0x")
			p=16;
		char* pp=NULL;
		int color = strtol(argv[2], &pp, p); 	
		D3DCOLOR d3dcolor(color);
		printf("%d=>D3DCOLOR_ARGB(%d,%d,%d,%d)\n",color,d3dcolor.a4,d3dcolor.r3,d3dcolor.g2,d3dcolor.b1);
	}
	else
	{	
		int color=atoi(argv[1]);
		const char* p = WinRGBInfo(color);
		printf("%d=>%s\n",color,p);
	}
	return 0;
}
