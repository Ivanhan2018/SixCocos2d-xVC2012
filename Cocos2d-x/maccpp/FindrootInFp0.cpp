#include<iostream>
#include <vector>
#include <cassert>
using namespace std;
/*
http://www.docin.com/p-544944854.html
令a=1和b=1，考虑椭圆曲线E:y^2=x^3+x+1(mod5)。
E上的全部点为：？
有限整点个数：8
(0,1),(0,4),(2,1),(2,4),(3,1),(3,4),(4,2),(4,3)
阶分别为：
9，，3，
因为9(0,1)=∞，3(2,1)=∞

令a=1和b=1，考虑椭圆曲线E:y^2=x^3+x+1(mod11)。
E上的全部点为：？
有限整点个数：13
(0,1),(0,10),(1,5),(1,6),(2,0),(3,3),(3,8),(4,5),(4,6),(6,5),(6,6),(8,2),(8,9)
阶分别为：
7，
因为7(0,1)=∞
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
int main(int argc, const char * argv[]) {
    if(argc>=3)
    {
        int p=atoi(argv[1]);
        int a=atoi(argv[2]);
        int b=atoi(argv[3]);
	vector<IntPoint> retVec=FindrootInFp(PolygonEC,p,a,b);
	int nSize=retVec.size();
	cout<<"椭圆曲线E:y^2=x^3+"<<a<<"x+"<<b<<"(mod"<<p<<")的有限整点个数："<<nSize<<endl;
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
    }
    else
    {
        int p=11;
        int a=1;
        int b=1;
	//vector<IntPoint> retVec=FindrootInFp(PolygonEC,5,1,1);
	vector<IntPoint> retVec=FindrootInFp(PolygonEC,11,1,1);
	int nSize=retVec.size();
	cout<<"椭圆曲线E:y^2=x^3+"<<a<<"x+"<<b<<"(mod"<<p<<")的有限整点个数："<<nSize<<endl;
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
    }
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}
