// gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.4) 下编译需要g++ -std=c++11 -o gf gf.cpp
#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

typedef unsigned char byte;

/* 获取字节ch中的第n位的数值 */
int GetBit(unsigned char ch,int n)
{
	return ((ch>>n)& 1);
}

// 字符串相加
string add(string a,string b){
    if (a.length()<b.length())
	{
		return add(b,a);
	}
	// a长度大于等于b
    int c=0,l1=(int)a.size()-1,l2=(int)b.size()-1;
    while (l2>0) {
        int t=(a[l1]-48)+(b[l2--]-48)+c;
        a[l1--]=(t%10)+48;
        c=t/10;
    }
    int t=(a[l1]-48)+(b[l2]-48)+c;
    if (l1==0){//当a长度等于b时
        a[l1]=(t%10)+48;
        char p=char(t/10+48);
        b.clear();
        b+=p;
        b+=a;
        a=b;
    }
    else
    {              //当a长度大于b时
        a[l1--]=(t%10)+48;
        a[l1]+=t/10;
    }
    return a;
}

int to10Base(int num,int base)
{
	int res = 0,factor = 1;
	while(num)
	{
		res += (num % 10) * factor;
		factor *= base;
		num /= 10;
	}
	return res;
}

vector<int> toNBase(int num,int n)
{
	vector<int> v;
	while(num)
	{
		v.push_back(num % n);
		num /= n;
	}
	return v;
}

// vadd是2进制(p=2)异或运算的推广
vector<int> vadd(vector<int>& a,vector<int>& b,int p)
{
	vector<int> ret;
	int na=a.size();
	int nb=b.size();
	if(na!=nb)
		return ret;
	for(int i=0;i<na;i++)
		ret.push_back((a[i]+b[i])%p);
	return ret;
}

vector<vector<int> >  ESet(int p,int n)
{
	auto powi=[](int a,int n)->int{int ret=a;for(int i=1;i<n;i++)ret*=a;return ret;};
	int q=powi(p,n);

	vector<vector<int> > ret;
	for(int i=0;i<q;i++)
	{
		vector<int> v;
		int num=i;
		while(num)
		{
			v.push_back(num%p);
			num /= p;
		}
		int r=n-v.size();
		for(int i=0;i<r;i++)
		{
			v.push_back(0);
		}
		//reverse(v.begin(),v.end());
		ret.push_back(v);
	}
	return ret;    	
}

int IsInESet(const vector<vector<int> >& FG,const vector<int> & m)
{
    int N=m.size();
	for(int i=0;i<FG.size();i++)
	{
        if(FG[i].size()!=N)
			continue;
		if(memcmp(&m[0],&FG[i][0],sizeof(int)*N)==0)
			return i;		
	}
	return -1;
}

int main()
{
/*
char bit = 0x41;//65,定义字符常量的写法
for (int i = 0; i < 8; i++)
 printf(GetBit(bit, 7-i) ? "1" : "0"); 
printf("\n");

int ret=to10Base(1000001,2);
printf("%d\n",ret);

vector<int> v = toNBase(65,2);
for(int i=v.size()-1;i>=0;--i)
printf("%d",v[i]);
printf("\n");
*/

// 生成初等Abel群E(2^n)的凯莱表
auto powi=[](int a,int n)->int{int ret=a;for(int i=1;i<n;i++)ret*=a;return ret;};
int p=2;
int n=3;
int q=powi(p,n);
printf("E(%d)\n",q);
for(int i=0;i<q;i++)
{
	for(int j=0;j<q;j++)
	{
		printf("%d ",(i^j)+1);
	}
	printf("\n");
}

// 生成Z/mZ上n维向量空间的加群(Z/mZ)^n的凯莱表
int P[]={2,3,2,4};
int N[]={3,2,4,2};
const char *szName[]={"E8","E9","E16","C_4×C_4"};
int num=sizeof(N)/sizeof(N[0]);
for(int k=0;k<num;k++)
{
p=P[k];
n=N[k];
q=powi(p,n);
printf("%s\n",szName[k]);
vector<vector<int> > vv=ESet(p,n);
/* for(int i=0;i<vv.size();i++)
{
	for(int j=0;j<vv[i].size();j++)
	{
		printf("%d,",vv[i][j]);
	}
	printf("\n");
} */
for(int i=0;i<q;i++)
{
	for(int j=0;j<q;j++)
	{
		printf("%d ",IsInESet(vv,vadd(vv[i],vv[j],p))+1);
	}
	printf("\n");
}
}
return 0;
}