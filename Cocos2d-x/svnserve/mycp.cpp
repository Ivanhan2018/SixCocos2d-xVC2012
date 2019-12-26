/*
::CopyFile复制文件：
BOOL CopyFile(
  LPCTSTR lpExistingFileName, // name of an existing file
  LPCTSTR lpNewFileName,      // name of new file
  BOOL bFailIfExists          // operation if file exists
)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#else
#define FALSE 0
int CopyFile(const char* src, const char* des,int bFailIfExists)
{
	char cmd[128];
	memset(cmd,0,128);
	sprintf(cmd,"cp %s %s -f",src,des);
	system(cmd);
	return 0;
}
#endif	

int main(int argc,char *argv[])
{
	if(argc<3) 
	{ 
		printf("Incorrect Argument Numbers.\nUsage:./mycp src des\n"); 
		exit(1); 
	} 
	CopyFile(argv[1],argv[2],FALSE);
	return 0;
}