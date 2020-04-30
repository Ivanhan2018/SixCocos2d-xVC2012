/*
root@iZ14rcmneyrcltZ:~/cpptest# g++ -o FindrootInF5 FindrootInF5.cpp
root@iZ14rcmneyrcltZ:~/cpptest# ./FindrootInF5
x^2+x=0在F_5中的根：0,4,
root@iZ14rcmneyrcltZ:~/cpptest# g++ -std=c++11 -o FindrootInF5 FindrootInF5.cpp
root@iZ14rcmneyrcltZ:~/cpptest# ./FindrootInF5
x^2+x=0在F_5中的根：0,4,
*/
#include <iostream>
#include <vector>
#include <cassert>
#include <functional>//std::placeholders
using namespace std;

int F_5[5]={0,1,2,3,4};

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

/*
int Mod5(int ret)
{
	return Mod(ret,5);
}
*/
auto Mod5=std::bind(Mod,std::placeholders::_1,5);
/*
int AddInF5(int a,int b)
{
	int ret=Mod5(a+b);
	return ret;
}

int MulInF5(int a,int b)
{

	int ret=Mod5(a*b);
	return ret;
}
*/
auto AddInF5=[](int a,int b)->bool{
		int ret=Mod5(a+b);
		return ret;
	};
	
auto MulInF5=[](int a,int b)->bool{
		int ret=Mod5(a*b);
		return ret;
	};	
	
int AddInvInF5(int a)
{
	static int F_5[5]={0,1,2,3,4};
	for(int i=0;i<5;i++)
	{
		if(AddInF5(F_5[i],Mod5(a))==0)
			return F_5[i];
	}
	return -1;//错误值
}

int MulInvInF5(int a)
{
	static int F_5[5]={0,1,2,3,4};
	for(int i=0;i<5;i++)
	{
		if(MulInF5(F_5[i],Mod5(a))==1)
			return F_5[i];
	}
	return -1;//错误值
}

typedef void(*pFuncVoid)(void);
typedef int(*pFuncInt0)(int x);

/*
int Polygon(int x)
{
    return x*x+1;
}
*/

vector<int> FindrootInF5(pFuncInt0 fun)
{
	vector<int> ret;
	if(fun!=NULL)
	{
		static int F_5[5]={0,1,2,3,4};
		for(int i=0;i<5;i++)
		{
			if(Mod5(fun(F_5[i]))==0)
				ret.push_back(F_5[i]);
		}
	}
	return ret;
}

void Print(const char *szName,vector<int>& tlVect) 
{
	printf("%s",szName);
	for (int i = 0; i < tlVect.size(); i++) {
		printf("%d,",tlVect[i]); 
	}

	printf("\n"); 
}

int main()
{
	//vector<int> retVec=FindrootInF5(Polygon);//2,3，即x^2+1=0在F_5中有两根：x_1=2,x_2=3
 	auto Polygon=[](int x)->int{
			return x*x+1;
		};
    vector<int> retVec=FindrootInF5([](int x)->int{return x*x+x;});
    Print("x^2+x=0在F_5中的根：",retVec);//x^2+x=0在F_5中的根：0,4,

	return 0;
}