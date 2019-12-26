// 加上行号
#include <stdio.h>
#include <stdlib.h> 

int main(int argc,char *argv[])/*这是程序执行时的标准参数写法,argc是参数的个数,argv是参数具体的字串*/ 
{ 
	FILE *fsource;/*指向源文件*/  
	if(argc<2) 
	{ 
		printf("Incorrect Argument Numbers.\nUsage:catn srcfile\n"); 
		exit(1); 
	} 
	if((fsource=fopen(argv[1],"rt"))==NULL) 
	{ 
		printf("Can't open source file %s.\n",argv[1]); 
		exit(1); 
	}  
	int ln=1; 
	char line[600]={0};
	while(fgets(line,512,fsource)!=NULL) 
	if(fprintf(stdout,"%-6d%s",ln++,line)==EOF) 
	{ 
		printf("Can't write to stdout.\n"); 
		fclose(fsource); 
		exit(1); 
	} 
	fclose(fsource); 
	return 0;
}