#include<stdio.h>
#include<sys/stat.h>

// 判断一个文件是否存在,1存在，0不存在
int FileExists(const char *str)
{
	FILE *fp;
	if((fp=fopen(str, "r"))!=NULL)
	{
		fclose(fp);
		return 1;
	}
	return 0;
}

// 检测文件是否存在
bool FileExist(const char *fileName)  
{
	struct stat my_stat;
	return (stat(fileName,&my_stat)==0);	
}

int main(int argc, char *argv[])
{
	if( argc < 2 )
	{
		printf("Usage:  FileExists arg1\n");
		return 1;
	}	
	int ret=FileExist(argv[1]);
	const char* p = (ret==1?"文件存在":"文件不存在");
	printf("%s%s\n",argv[1],p);
	
	return 0;
}