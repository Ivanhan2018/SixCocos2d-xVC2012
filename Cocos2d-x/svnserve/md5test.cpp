#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include"md5.h"

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
		char buf[1024]={0};
		CMD5Encrypt::EncryptData(argv[1],buf);
		printf("%s->%s(长度:%d)\n",argv[1],buf,strlen(buf));
        return 0;		
	}
	
	if(strcmp(argv[0],"./xor")==0)
	{
		if( argc < 2 )
		{
			printf("Usage:  xor [-e][-d] arg1\n");
			return 0;
		} 
		if(strcmp(argv[1],"-d")==0 && argc >2)
		{
			char buf[1024]={0};
			CXOREncrypt::CrevasseData(argv[2],buf,sizeof(buf));
			printf("%s->%s(长度:%d)\n",argv[2],buf,strlen(buf));			
		}
		else if(strcmp(argv[1],"-e")==0 && argc >2)
		{
			char buf[1024]={0};
			CXOREncrypt::EncryptData(argv[2],buf,sizeof(buf));
			printf("%s->%s(长度:%d)\n",argv[2],buf,strlen(buf));
		}
		else
		{
			char buf[1024]={0};
			CXOREncrypt::EncryptData(argv[1],buf,sizeof(buf));
			printf("%s->%s(长度:%d)\n",argv[1],buf,strlen(buf));
		}
        return 0;		
	}	
	return 0;
}
