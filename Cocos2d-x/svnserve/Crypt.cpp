#include <stdio.h>
#include <string.h>
#include<string>
using namespace std;

string EnCrypt(string texti,string salasana)
{
	string str;
	int x1=0;
	for(int i=0;i<salasana.size();i++)
	{
		x1+=salasana[i];
	}
	x1=(x1*0.1)/6;
	int x2=x1;
	int g=0;
	int x3=0;

	for(int i=0;i<texti.size();i++)
	{
		x3=texti[i];
		g++;
		if(g==6)
		{
			g=0;
		}
		x2=0;
		if(g==0)
		{
			x2=x3-(x1-2);
		}
		if(g==1)
		{
			x2=x3+(x1-5);
		}
		if(g==2)
		{
			x2=x3-(x1-4);
		}
		if(g==3)
		{
			x2=x3+(x1-2);
		}
		if(g==4)
		{
			x2=x3-(x1-3);
		}
		if(g==5)
		{
			x2=x3+(x1-5);
		}
		x2+=g;
		str.push_back(x2);
	}

	return str;
}

string DeCrypt(string texti,string salasana)
{
	string str;
	int x1=0;
	for(int i=0;i<salasana.size();i++)
	{
		x1+=salasana[i];
	}
	x1=(x1*0.1)/6;
	int x2=x1;
	int g=0;
	int x3=0;

	for(int i=0;i<texti.size();i++)
	{
		x3=texti[i];
		g++;
		if(g==6)
		{
			g=0;
		}
		x2=0;
		if(g==0)
		{
			x2=x3+(x1-2);
		}
		if(g==1)
		{
			x2=x3-(x1-5);
		}
		if(g==2)
		{
			x2=x3+(x1-4);
		}
		if(g==3)
		{
			x2=x3-(x1-2);
		}
		if(g==4)
		{
			x2=x3+(x1-3);
		}
		if(g==5)
		{
			x2=x3-(x1-5);
		}
		x2-=g;
		str.push_back(x2);
	}

	return str;
}

string CryptKey(int key)
{
	char sz[100]={0};
	sprintf(sz,"%d",key);
	return sz;
}

int main(int argc, char *argv[])
{
	if( argc < 2 )
	{
		printf("Usage:  Crypt [-e][-d] str\n");
		return 1;
	}
	if(strcmp(argv[1],"-d")==0 && argc >=3)
	{	
		char *str=argv[2];
		string key=CryptKey(strlen(str));
		string ret=DeCrypt(str,key);
		printf("%s\n",ret.c_str());	
        return 0;		
	}
	char *str=argv[1];
	if(strcmp(argv[1],"-e")==0 && argc >=3)
	{	
		str=argv[2];
	}
	string key=CryptKey(strlen(str));
	string ret=EnCrypt(str,key);
	printf("%s\n",ret.c_str());	
	
	return 0;
}