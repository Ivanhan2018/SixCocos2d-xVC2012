// 插值算法
#include<stdio.h>

//lglrcz.c
int lagrange(float *x0,float *y0,int n,float x,float *y);

int main()
{
	static float x0[4]={0.46,0.47,0.48,0.49};
	static float y0[4]={0.484655,0.493745,0.502750,0.511668};
	float x,y;
	int n,rtn;
	n=4;
	x=0.472;
	rtn=lagrange(x0,y0,n,x,&y);
	if(rtn==0)
		printf("Y(0.472)=%f\n",y);
	else
		printf("N must be larger than 1.\n");
	return 0;
}

int lagrange(float *x0,float *y0,int n,float x,float *y)
{
	int i,j;
	float p;
	*y=0;
	if(n<=1)
		return -1;
	else
	{
		for(i=0;i<n;i++)
		{
			p=1;
			for(j=1;j<n;j++)
			{
				if(i!=j)
					p=p*(x-x0[j])/(x0[i]-x0[j]);
		    }
			*y=*y+p*y0[i];
		}
		return 0;
	}
}