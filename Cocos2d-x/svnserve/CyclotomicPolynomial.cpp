#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

struct DComplex
{
	double x;
	double y;
};

void ocmul(double a,double b,double c,double d,double *e,double *f)
{ 
	double p,q,s;
    p=a*c; q=b*d; s=(a+b)*(c+d);
    *e=p-q; *f=s-p-q;
    return;
}

DComplex DCMul(const DComplex &a,const DComplex &b)
{
	DComplex c;
	ocmul(a.x,a.y,b.x,b.y,&c.x,&c.y);
	return c;
}

DComplex DCAdd(const DComplex &a,const DComplex &b)
{
	DComplex c={a.x+b.x,a.y+b.y};
	return c;
}


DComplex DCAddInv(const DComplex &a)
{
	DComplex c={-a.x,-a.y};
	return c;
}

DComplex DComplexObj(double x,double y) 
{
	DComplex c={x,y};
	return c;
}


// 复数域多项式乘法
int polyCmul(DComplex a[],int m,DComplex b[],int n,DComplex c[],int *k) 
{ 
 int i,j; 
 *k=m+n-2;
 for(i=0;i<m+n-2;i++) 
 {
    c[i].x=0;
	c[i].y=0;
 }
 for(i=0;i<m;i++) 
  for(j=0;j<n;j++) 
   c[i+j]=DCAdd(DCMul(a[i],b[j]),c[i+j]);
 return 0;
}

vector<DComplex> polyCmul(vector<DComplex> &a,vector<DComplex> &b) 
{ 
 vector<DComplex> c(a.size()+b.size()-1);
 int k=0;
 int ret=polyCmul(&a[0],a.size(),&b[0],b.size(),&c[0],&k);
 return c;
}
 


vector<DComplex> polyCmul(DComplex cnpr[],int m) 
{
	vector<vector<DComplex> > arr;
	for(int i=0;i<m;i++)
	{
		vector<DComplex> a;
		a.push_back(DCAddInv(cnpr[i]));
		a.push_back(DComplexObj(1,0));
		arr.push_back(a);
	}
	vector<DComplex> ret;
	int n=arr.size();
	if(n==0)
		return ret;
	if(n==1)
		return arr[0];
	ret=arr[0];
	for(int i=1;i<n;i++)
	{ 
		vector<DComplex> retMul=polyCmul(ret,arr[i]);
		ret=retMul;
	}
	return ret;
}

// 返回true，表示能转化成整系数多项式
bool CPolyToZPoly(const vector<DComplex> &c,vector<int> &z)
{
	z.clear();
	int n=c.size();
	for(int i=0;i<n;i++)
	{
		int ix=floor(c[i].x+0.5);
		int iy=floor(c[i].y+0.5);
		if(fabs(c[i].x-ix)<0.01 && iy==0 && fabs(c[i].y-iy)<0.01)
		{
		  z.push_back(ix);
		}
		else
		{
		   return false;
		}
	}
	return true;
}

void ontrt(double x,double y,int n,double *u,double *v)
{ 
 int k;
 double r,q,t;
 if(n<1) 
  return;
 q=atan2(y,x);
 r=sqrt(x*x+y*y);
 if(r+1.0!=1.0)
 { 
  r=(1.0/n)*log(r); 
  r=exp(r);
 }
 for(k=0; k<=n-1; k++)
 { 
  t=(2.0*k*3.1415926+q)/n;
  u[k]=r*cos(t); 
  v[k]=r*sin(t);
 }
 return;
}

vector<DComplex>  CRoot(const DComplex &z,int n)
{
 vector<DComplex> ret;
 vector<double> u(n);
 vector<double> v(n);
 ontrt(z.x,z.y,n,&u[0],&v[0]);
 for(int i=0;i<n;i++)
 {
  DComplex uv={u[i],v[i]};
  ret.push_back(uv);
 }
 return ret;
}

// 求2个数的最大公约数
int GCD(int a, int b) 
{ 
 if(a*b==0)
  return (a==0?b:a);
 if(a*b<0)
  return -GCD(abs(a),abs(b));
 int temp=0;
 if(a<b)
 {
  temp=a;
  a=b;
  b=temp;
 }
 if(a%b==0)
  return b;
 else
  return GCD(a%b,b);
}

vector<DComplex>  CPriURoot(int n)
{
 vector<DComplex> ret;
 vector<DComplex> Cn=CRoot(DComplexObj(1,0),n);
 for(int i=0;i<n;i++)
 {
  if(GCD(i,n)==1)
    ret.push_back(Cn[i]);
 }
 return ret;
}

string signstr(double x)
{
	return x>0.0001?"+":"";
}

string numstr(double x)
{
    char sz[20]={0};
	sprintf(sz,"%f",x);
	return fabs(x)<0.0001?"":sz;
}

void p_print(vector<int>& v,int n,int m)
{        
 cout<<"Φ_"<<n<<"(x)=";
 for(int i = 0; i <m; i++)
 {
	 cout<<"(x-ξ_"<<i+1<<")";
 }
 cout<<"=";
 for (int i = 0; i <v.size(); i++)
 {             
	cout<<v[i]<<"x^"<<i; 
	if(i < v.size()-1) 
	cout<<"+"; 
 }
 cout<<"="; 
 cout<<"[";   
 for (int i = 0; i < v.size(); i++)
 {             
	cout<<v[i]; 
	if(i < v.size()-1) 
	cout<<",";	 
 }
 cout<<"]"<<endl; 
} 

int main(int argc, char* argv[])
{
	if( argc < 2 )
	{
		cout<<"Usage:  CyclotomicPolynomial n"<<endl;
		return 0;
	}
	int n=atoi(argv[1]);	
	vector<DComplex> C1pr=CPriURoot(n);
	int m=C1pr.size();
	cout<<"共有"<<m<<"个"<<n<<"次本原单位根:[";
	for(int i=0;i<m;i++){
		cout<<numstr(C1pr[i].x)<<signstr(C1pr[i].y)<<numstr(C1pr[i].y)<<"i";
        if(i<m-1)
			cout<<",";
        else
            cout<<"]"<<endl;			
	}
	// 根据本原n次单位根计算n次分圆多项式
	vector<DComplex> c=polyCmul(&C1pr[0],m);
	vector<int> v;
	bool bret=CPolyToZPoly(c,v);
	p_print(v,n,m);
	
    return 0;
}	
