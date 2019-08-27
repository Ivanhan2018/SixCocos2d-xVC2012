//#include<stdio.h>
//#include<stdlib.h>
#include<iostream>
#include <vector>
#include <cassert>
using namespace std;

/*
http://www.docin.com/p-97076238.html
令a=4和b=20，考虑椭圆曲线E:y^2=x^3+4x+20(mod29)。
E上的全部点为：？

有限整点个数：36
(0,7),(0,22),(1,5),(1,24),(2,6),(2,23),(3,1),(3,28),(4,10),(4,19),(5,7),(5,22),(
6,12),(6,17),(8,10),(8,19),(10,4),(10,25),(13,6),(13,23),(14,6),(14,23),(15,2),(
15,27),(16,2),(16,27),(17,10),(17,19),(19,13),(19,16),(20,3),(20,26),(24,7),(24,
22),(27,2),(27,27)
*/

// y^2=x^3+ax+b
typedef int(*pFuncInt2)(int x,int a,int b);

int PolygonEC(int x,int a,int b)
{
	return x*x*x+a*x+b;
}

int Mod(int ret,unsigned int n)
{
	assert(n>0);
	if(ret<0)
	{
		int ret1=ret+(-ret+1)*n;
		return ret1%n;
	}
	return ret%n;
}

struct IntPoint
{
	int x;
	int y;
};

vector<IntPoint> FindrootInFp(pFuncInt2 fun,int p,int a,int b)
{
	vector<IntPoint> ret;
	if(fun!=NULL)
	{
		for(int i=0;i<p;i++)
		for(int j=0;j<p;j++)
		{
			if(Mod(fun(i,a,b),p)==Mod(j*j,p))
			{
				IntPoint pt={i,j};
				ret.push_back(pt);
			}
		}
	}
	return ret;
}

int main()
{
	vector<IntPoint> retVec=FindrootInFp(PolygonEC,29,4,20);

	int nSize=retVec.size();
	cout<<"有限整点个数："<<nSize<<endl;

	for(int i=0;i<nSize;i++)
	{
		cout<<"("<<retVec[i].x<<","<<retVec[i].y<<")";
		if(i<nSize-1)
			cout<<",";
	}
	if(nSize>0)
	{
		cout<<endl;
	}

	//system("pause");
	return 0;
}
