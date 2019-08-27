#include<iostream>
using namespace std;

int g_D4[8][4]=
{
	{1,0,0,1},
	{0,1,6,0},
	{6,0,0,6},
	{0,6,1,0},
	{0,1,1,0},
	{6,0,0,1},
	{0,6,6,0},
	{1,0,0,6},
};

int mul(int a,int b)
{
	int a4[4]={g_D4[a][0],g_D4[a][1],g_D4[a][2],g_D4[a][3]};
	int b4[4]={g_D4[b][0],g_D4[b][1],g_D4[b][2],g_D4[b][3]};
	int c4[4]=
	{
		(g_D4[a][0]*g_D4[b][0]+g_D4[a][1]*g_D4[b][2])%7,
		(g_D4[a][0]*g_D4[b][1]+g_D4[a][1]*g_D4[b][3])%7,
		(g_D4[a][2]*g_D4[b][0]+g_D4[a][3]*g_D4[b][2])%7,
		(g_D4[a][2]*g_D4[b][1]+g_D4[a][3]*g_D4[b][3])%7
	};
	for(int i=0;i<8;i++)
	{
		if(g_D4[i][0]==c4[0] && g_D4[i][1]==c4[1] && g_D4[i][2]==c4[2] && g_D4[i][3]==c4[3])
			return i;
	}
	return -1;
}

int g_D4_Mul[8][8]={
	0,1,2,3,4,5,6,7,
	1,2,3,0,7,4,5,6,
	2,3,0,1,6,7,4,5,
	3,0,1,2,5,6,7,4,
	4,5,6,7,0,1,2,3,
	5,6,7,4,3,0,1,2,
	6,7,4,5,2,3,0,1,
	7,4,5,6,1,2,3,0,
};

// 未知8阶群的群元的阶
int getG8EOrder(int a)
{
	if(a<0||a>=8)
		return -1;
	int t=0;
	for(int i=1;i<=8;i++)
	{
		t=g_D4_Mul[t][a];
		if(t==0)
			return i;
	}
	return -1;
}

int main(int argc,char *argv[])
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			printf("%d ",mul(i,j)+1);
			//printf("%d,",mul(i,j));
		}
		printf("\n");
	}

	for(int i=0;i<8;i++)
	{
		printf("%d\n",getG8EOrder(i));
	}
	
	//system("pause");
	return 0;
}