#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 由内码（与汉字的GBK内码一致）求得一字符，多对一函数
const char * ChrFromAnsi(short CharCode)
{
	static 	char str[80]={0};
	memset(&str[0],0,2);
    if((CharCode>32 && CharCode<128)||((char)(CharCode)>32 && (char)(CharCode)<128))
	{
		memset(&str[0],(char)(CharCode),1);
	    memset(&str[1],0,1);
		return str;
	}
	if((char)(CharCode>>8)>32 && (char)(CharCode>>8)<128)
	{
		memset(&str[0],(char)(CharCode>>8),1);
	    memset(&str[1],0,1);
		return str;
	}
	memset(&str[0],(char)(CharCode>>8),1);
    memset(&str[1],(char)(CharCode),1);
	return str;
}

// 求字符的内码
short AscFromChr(const char *str)
{
	   int n=strlen(str);
	   if(n==0||n>2)
		   return 0;
	   if(n==1)
		   return str[0];
	   if(n==2)
		   //return ((unsigned char)str[0])*256+((unsigned char)str[1]);
	   return (((short)(unsigned char)str[0])<<8)|((short)(unsigned char)str[1]);
}

int main(int argc, char *argv[])
{
	if( argc < 3 )
	{
		printf("Usage:  chrasc [-c][-a] arg2\n");
		return 1;
	}
	if(strcmp(argv[1],"-c")==0)
	{	
		short CharCode=atoi(argv[2]);
		const char *p=ChrFromAnsi(CharCode);
		printf("%s\n",p);	
        return 0;		
	}
	if(strcmp(argv[1],"-a")==0)
	{	
		int ret=AscFromChr(argv[2]);
		printf("%d\n",ret);	
        return 0;		
	}
	
	return 0;
}