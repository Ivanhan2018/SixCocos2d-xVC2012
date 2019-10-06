//
//  FindStr.cpp
//  g++ -o FindStr FindStr.cpp
//
//  Created by hxh on 19-9-21.
//
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const char *szArr[]={ \
	"BJL_Cannger_1.png", \
	"BJL_Cannger_10.png", \
	"BJL_Cannger_100.png", \
	"BJL_Cannger_1000.png", \
	"BJL_Cannger_10000.png", \
	"BJL_Cannger_50000.png", \
	"BJL_Cannger_100000.png", \
};

int main(int argc, char **argv)
{
	char szp[100]={0};
	if(argc<2)
	{
		printf("输入index：");
		scanf("%s",szp);
	}
	else
		strcpy(szp,argv[1]);

        int i=atoi(szp);
        int n=sizeof(szArr)/sizeof(szArr[0]);
	if(i>=0 && i<n)
          printf("[%d]--->%s\n",i,szArr[i]);
        else
	  printf("invalid index\n");
	
	return 0;
}