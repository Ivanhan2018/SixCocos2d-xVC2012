#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <cstdlib>
#include <string>
#include"MD5.h"
#include"Encrypt.h"

using namespace std;

string MD5Encrypt(const string& str)
{
	char pSrc[1024]={0};
	strcpy(pSrc,str.c_str());
	char pDst[33]={0};
	ERROR_INFO ret=HashByMD5(pSrc,str.size(),pDst,false);
	return pDst;
}

//2jiw6lvj82011-11-15 11:43:13192.168.1.91->7fccc1982e1db1b9bd13ddf64fcfc106
int main(int argc, char* argv[])
{
	if(strcmp(argv[0],"./md5")==0)
	{
		if( argc < 2 )
		{
			printf("Usage:  md5 arg1\n");
			return 0;
		} 
		string str=MD5Encrypt(argv[1]);
		printf("%s->%s(长度:%d)\n",argv[1],str.c_str(),str.size());
        return 0;		
	}
	
	if(strcmp(argv[0],"./xor6601")==0)
	{
		if( argc < 2 )
		{
			printf("Usage:  xor6601 [-e][-d] arg1\n");
			return 0;
		} 
		if(strcmp(argv[1],"-d")==0 && argc >2)
		{
			char buf[1024]={0};
			CXOR6601Encrypt::CrevasseData(argv[2],buf,sizeof(buf));
			printf("%s->%s(长度:%d)\n",argv[2],buf,strlen(buf));			
		}
		else if(strcmp(argv[1],"-e")==0 && argc >2)
		{
			char buf[1024]={0};
			CXOR6601Encrypt::EncryptData(argv[2],buf,sizeof(buf));
			printf("%s->%s(长度:%d)\n",argv[2],buf,strlen(buf));
		}
		else
		{
			char buf[1024]={0};
			CXOR6601Encrypt::EncryptData(argv[1],buf,sizeof(buf));
			printf("%s->%s(长度:%d)\n",argv[1],buf,strlen(buf));
		}
        return 0;		
	}	
	return 0;
}
