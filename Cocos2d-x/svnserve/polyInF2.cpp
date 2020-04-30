#include<stdio.h>
#include<string.h>
#include<vector>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<functional>
using namespace std;
/*
GF(2)上的多项式f(x)=x^2+1的剩余类全体为：
~0，~1，~x，~(x+1)
GF(2)上的多项式f(x)=x^2+x+1的剩余类全体为：
~0，~1，~x，~(x+1)
对所定义的加法和乘法运算，前者构成剩余类环，后者构成域。
结论：若n次首一多项式f(x)在域F_p上既约，则f(x)的剩余类环构成一个有p^n个元素的有限域。
多项式环F_p[x]的一切理想均是主理想。
多项式剩余类环F_p[x]/f(x)中的每一个理想都是主理想。
多项式(1+x+x^4+x^6)mod(1+x+x^3+x^4+x^8)的乘法逆元是(x+x^3+x^6+x^7)
*/

// 欧几里得算法
template<class T>
T gcd(T a, T b)
{
 int temp;
 if(b == 0) return a;
 if(a == 0) return b;
 if(a%b == 0) return b;
 else return gcd(b, a%b);
}

// 多项式a乘以多项式b得到多项式c，deg(a)=m-1,deg(b)=n-1,deg(c)=m+n-2=k
int polymul(int* a,int m,int* b,int n,int* c,int* k) 
{ 
 int i,j; 
 if(k)*k=m+n-2;
 for(i=0;i<m+n-2;i++) 
  c[i]=0; 
 for(i=0;i<m;i++) 
  for(j=0;j<n;j++) 
   c[i+j]=a[i]*b[j]+c[i+j];
 return 0;
} 

int Mod(int ret,unsigned int n)
{
 //assert(n>0);
 if(ret<0)
 {
  int ret1=ret+(-ret+1)*n;
  return ret1%n;
 }
 return ret%n;
}

auto Mod2=std::bind(Mod,std::placeholders::_1,2);
auto AddInF2=[](int a,int b)->bool{
        int ret=Mod2(a+b);
        return ret;
    };
auto MulInF2=[](int a,int b)->bool{
        int ret=Mod2(a*b);
        return ret;
    };
	
int AddInvInF2(int a)
{
 static int F_2[5]={0,1};
 for(int i=0;i<2;i++)
 {
  if(AddInF2(F_2[i],Mod2(a))==0)
   return F_2[i];
 }
 return -1;//错误值
}

int MulInvInF2(int a)
{
 static int F_2[2]={0,1};
 for(int i=0;i<2;i++)
 {
  if(MulInF2(F_2[i],Mod2(a))==1)
   return F_2[i];
 }
 return -1;//错误值
}

/*取余函数(被除数a,除数b)*/
vector<int> polymodInF2( vector<int>& a, vector<int>& b)
{  
 vector<int> m=a,n=b;
 int coe;/*商系数*/  
 if( m.size() < n.size() ) 
  return m;  
 else for( unsigned int i = 0 ; i < m.size() - n.size() + 1 ; i++ )
 {   
  for( int ma = m[m.size()-1-i] ; ; )
  {    
   if( !( ma % n[n.size()-1] ))
   {     
    coe = ma / n[n.size()-1];     
    break;    
   }    
   ma += 2;   
  }   
  for( unsigned int j=0;j<n.size();j++) 
   m[m.size()-1-i-j] = ( m[m.size()-1-i-j] - coe*n[n.size()-1-j] % 2 + 2 ) % 2;  
 }  
/* while( !m.empty() && !m.back() ) 
  m.pop_back();*/ 
	while (m.size() && *(m.rbegin()) == 0) {	// 清除高位无效零
		m.pop_back();
	}
	if (m.empty()) {	// 补零
		m.push_back(0);
	}  
 return m; 
}

/*乘法函数*/
vector<int> polymulInF2(vector<int>& a,vector<int>& b)
{
#if 1
    int m=a.size();
	int n=b.size();
	vector<int> c(m+n-1);
	int k=0;
	int ret=polymul(&a[0],m,&b[0],n,&c[0],&k);
	for_each(c.begin(),c.end(),[](int& i)->void{i=Mod2(i);});//Mod2(a[i]*b[j]+c[i+j])=Mod2(Mod2(a[i]*b[j])+c[i+j])
	while (c.size() && *(c.rbegin()) == 0) {	// 清除高位无效零
		c.pop_back();
	}
	if (c.empty()) {	// 补零
		c.push_back(0);
	}
	return c;
#else
 vector<int> c;  
 c.assign( a.size() + b.size() - 1 , 0 );  
 for(unsigned int i=0 ; i < a.size() ; i++ ) 
  for( unsigned int j=0 ; j < b.size() ; j++ ) 
   c[i+j] =(( c[i+j] + a[i] * b[j] ) % 2 +2 ) % 2 ; 
	while (c.size() && *(c.rbegin()) == 0) {	// 清除高位无效零
		c.pop_back();
	}
	if (c.empty()) {	// 补零
		c.push_back(0);
	}
	return c;
#endif
} 

/*加法函数*/
vector<int> polyaddInF2(vector<int>& a,vector<int>& b)
{
    int m=a.size();
	int n=b.size();
	int k=(m>n?m:n);
	int ki=(m>n?n:m);	
	vector<int> c(k);	
	for(int i=0;i<ki;i++)
	{
		c[i]=Mod2(a[i]+b[i]);	
	}
	if(m>n)
	{
		memcpy(&c[n],&a[n],(m-n)*sizeof(int));	
	}
	else if(m<n)
	{
		memcpy(&c[m],&b[m],(n-m)*sizeof(int));	
	}
	while (c.size() && *(c.rbegin()) == 0) {	// 清除高位无效零
		c.pop_back();
	}
	if (c.empty()) {	// 补零
		c.push_back(0);
	}
	return c;
} 

#if 0
int fa[]={1,1,1};
int ga[]={1,0,1};
int f0a[]={0};
int f1a[]={1};
int f2a[]={0,1};
int f3a[]={1,1};
vector<int> f(fa,fa+sizeof(fa)/sizeof(int));
vector<int> g(ga,ga+sizeof(ga)/sizeof(int));;
vector<int> f0(f0a,f0a+sizeof(f0a)/sizeof(int));
vector<int> f1(f1a,f1a+sizeof(f1a)/sizeof(int));	
vector<int> f2(f2a,f2a+sizeof(f2a)/sizeof(int));
vector<int> f3(f3a,f3a+sizeof(f3a)/sizeof(int));
vector<int> g_F4[]={f,f0,f1,f2,f3};
vector<int> g_R4[]={g,f0,f1,f2,f3};
#else
vector<int> f={1,1,1};//x^2+x+1=0，在F_2中无根
vector<int> g={1,0,1};//x^2+1=0，在F_2中有一根：x_1=1
vector<int> f0={0};
vector<int> f1={1};	
vector<int> f2={0,1};
vector<int> f3={1,1};
vector<int> f4={0,0,1};
vector<int> f5={1,0,1};
vector<int> f6={0,1,1};
vector<int> f7={1,1,1};
vector<int> f8={0,0,0,1};
vector<int> f9={1,0,0,1};	
vector<int> f10={0,1,0,1};
vector<int> f11={1,1,0,1};
vector<int> f12={0,0,1,1};
vector<int> f13={1,0,1,1};
vector<int> f14={0,1,1,1};
vector<int> f15={1,1,1,1};
vector<int> g_F4[]={f,f0,f1,f2,f3};
vector<int> g_R4[]={g,f0,f1,f2,f3};
vector<int> f1101={1,1,0,1};//x^3+x+1=0，在F_2中无根
vector<int> f1011={1,0,1,1};//x^3+x^2+1=0，在F_2中无根
vector<int> g1001={1,0,0,1};//x^3+1=0，在F_2中有一根：x_1=1
vector<int> g1111={1,1,1,1};//x^3+x^2+x+1=0，在F_2中有一根：x_1=1
vector<int> g0101={0,1,0,1};//x^3+x=0，
vector<int> g0011={0,0,1,1};//x^3+x^2=0，
vector<int> g_F8[]={f1101,f0,f1,f2,f3,f4,f5,f6,f7};
vector<int> g_R8_51[]={g1001,f0,f1,f2,f3,f4,f5,f6,f7};
vector<int> g_R8_48[]={g0101,f0,f1,f2,f3,f4,f5,f6,f7};
vector<int> g_R8_46[]={g1111,f0,f1,f2,f3,f4,f5,f6,f7};
vector<int> g00001={0,0,0,0,1};//x^4=0，
vector<int> g01111={0,1,1,1,1};//x^4+x^3+x^2+x=0，
vector<int> g_R16_385[]={g00001,f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15};
vector<int> g_R16_382[]={g01111,f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15};
#endif

int R4ElemToInt(vector<int>& a,vector<int> R4[],int n)
{
    for(int i=1;i<=n;i++)
    {
     if(R4[i].size()==a.size() && memcmp(&R4[i][0],&a[0],sizeof(int)*a.size())==0)
      return i;
    }
    return -1;
}

int R4mul(int a,int b,vector<int> R4[],int n)
{
	vector<int> fa=R4[a];
	vector<int> fb=R4[b];
	vector<int> fafb=polymulInF2(fa,fb);				
	vector<int> fc=polymodInF2(fafb,R4[0]);	
	int c=R4ElemToInt(fc,R4,n);
	return c;
}

int R4add(int a,int b,vector<int> R4[],int n)
{
	vector<int> fa=R4[a];
	vector<int> fb=R4[b];
	vector<int> fafb=polyaddInF2(fa,fb);				
	//vector<int> fc=polymodInF2(fafb,R4[0]);	
	int c=R4ElemToInt(fafb,R4,n);
	return c;
}

int main()
{
	{
		vector<int> *R4[]={g_F4,g_R4};
		const char *szName[]={"F4","R4"};
		int m=sizeof(R4)/sizeof(R4[0]);
		int n=4;		
		for(int i=0;i<m;i++)
		{
			auto add=std::bind(R4add,std::placeholders::_1,std::placeholders::_2,R4[i],n);
			printf("int g_%sAdd[]={\n",szName[i]);
			for(int i=1;i<=n;i++)
			{
				printf("%d,%d,%d,%d,\n",add(i,1),add(i,2),add(i,3),add(i,4));
			}
			printf("};\n");	
			auto mul=std::bind(R4mul,std::placeholders::_1,std::placeholders::_2,R4[i],n);
			printf("int g_%sMul[]={\n",szName[i]);
			for(int i=1;i<=n;i++)
			{
				printf("%d,%d,%d,%d,\n",mul(i,1),mul(i,2),mul(i,3),mul(i,4));
			}
			printf("};\n");			
		}
	}
	{
		vector<int> *R4[]={g_F8,g_R8_51,g_R8_48,g_R8_46};
		const char *szName[]={"F8","R8_51","R8_48","R8_46"};
		int m=sizeof(R4)/sizeof(R4[0]);
		int n=8;
		for(int i=0;i<m;i++)
		{
			auto add=std::bind(R4add,std::placeholders::_1,std::placeholders::_2,R4[i],n);
			printf("int g_%sAdd[]={\n",szName[i]);
			for(int i=1;i<=n;i++)
			{
				printf("%d,%d,%d,%d,%d,%d,%d,%d,\n",add(i,1),add(i,2),add(i,3),add(i,4),add(i,5),add(i,6),add(i,7),add(i,8));
			}
			printf("};\n");	
			auto mul=std::bind(R4mul,std::placeholders::_1,std::placeholders::_2,R4[i],n);
			printf("int g_%sMul[]={\n",szName[i]);
			for(int i=1;i<=n;i++)
			{
				printf("%d,%d,%d,%d,%d,%d,%d,%d,\n",mul(i,1),mul(i,2),mul(i,3),mul(i,4),mul(i,5),mul(i,6),mul(i,7),mul(i,8));
			}
			printf("};\n");			
		}
	}	
	{
		vector<int> *R4[]={g_R16_382,g_R16_385};
		const char *szName[]={"R16_382","R16_385"};
		int m=sizeof(R4)/sizeof(R4[0]);
		int n=16;
		for(int i=0;i<m;i++)
		{
			auto add=std::bind(R4add,std::placeholders::_1,std::placeholders::_2,R4[i],n);
			printf("int g_%sAdd[]={\n",szName[i]);
			for(int i=1;i<=n;i++)
			{
				printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\n",add(i,1),add(i,2),add(i,3),add(i,4),add(i,5),add(i,6),add(i,7),add(i,8),add(i,9),add(i,10),add(i,11),add(i,12),add(i,13),add(i,14),add(i,15),add(i,16));
			}
			printf("};\n");	
			auto mul=std::bind(R4mul,std::placeholders::_1,std::placeholders::_2,R4[i],n);
			printf("int g_%sMul[]={\n",szName[i]);
			for(int i=1;i<=n;i++)
			{
				printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\n",mul(i,1),mul(i,2),mul(i,3),mul(i,4),mul(i,5),mul(i,6),mul(i,7),mul(i,8),mul(i,9),mul(i,10),mul(i,11),mul(i,12),mul(i,13),mul(i,14),mul(i,15),mul(i,16));
			}
			printf("};\n");			
		}
	}	
    return 0;
}