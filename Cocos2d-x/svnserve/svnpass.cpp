#include <stdio.h>
#include <string.h>

// f(x)=(x+k)mod26,f^(-1)(x)=(x-k)mod26
int fkmod26(int x,int k)
{
  int ret=(x+k)%26;
  if(ret<0)ret=ret+26;
  if(ret>25)ret=ret-26;
  return ret;
}

void ECode(char *str,int k)
{
	int nsize=strlen(str);
	for(int i=0;i<nsize;i++)
	{
	   if(str[i]<='z'&&str[i]>='a')
		  str[i]=fkmod26(str[i]-97,k)+97;
	   if(str[i]<='Z'&&str[i]>='A')
	      str[i]=fkmod26(str[i]-65,k)+65;
    }
}

int main(int argc, char *argv[])
{
	if( argc < 2 )
	{
		printf("Usage:  svnpass [-e][-d] str\n");
		return 1;
	}
	if(strcmp(argv[1],"-d")==0 && argc >=3)
	{	
		char *str=argv[2];
		ECode(str,-strlen(str));
		printf("%s\n",str);	
        return 0;		
	}
	char *str=argv[1];
	if(strcmp(argv[1],"-e")==0 && argc >=3)
	{	
		str=argv[2];
	}
	ECode(str,strlen(str));
	printf("%s\n",str);
	
	return 0;
}