#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class ComplexArg
{
public:
	static inline int GetAbilityType(int ability)
	{
	   return ability & 0x0000000f;
	}

	static inline int GetAbilityIndex(int ability)
	{
	   return (ability & 0x00000ff0)>>4;
	}

	static inline int GetAbilityValue(int type,int index)
	{
	   return (type & 0x0000000f)|((index<<4) & 0x00000ff0);
	}
};

int main(int argc, char *argv[])
{
	if( argc < 3 )
	{
		printf("Usage:  ComplexArg [-t][-i][-v] arg2 arg3\n");
		return 1;
	}
	if(strcmp(argv[1],"-v")==0 && argc >=4)
	{	
		int type=atoi(argv[2]);
		int index=atoi(argv[3]);
		int ret=ComplexArg::GetAbilityValue(type,index);
		printf("%d\n",ret);	
        return 0;		
	}
	if(strcmp(argv[1],"-i")==0)
	{	
		int ability=atoi(argv[2]);
		int ret=ComplexArg::GetAbilityIndex(ability);
		printf("%d\n",ret);	
        return 0;		
	}
	if(strcmp(argv[1],"-t")==0)
	{	
		int ability=atoi(argv[2]);
		int ret=ComplexArg::GetAbilityType(ability);
		printf("%d\n",ret);	
        return 0;		
	}
	
	return 0;
}