#include<iostream>
#include<complex>
#include<vector>
#include<algorithm>
using namespace std;

bool IsPrime(unsigned int N)
{
	if(N==0||N==1)
		return false;
	int up=sqrt((float)N);
	for(int i=2;i<=up;i++)
	{
		if(N%i==0)
			return false;
	}
	return true;
}

class gint
{
public:
	gint(long a,long b)
	{
		m_a=a;
		m_b=b;
	}

	/*
		高斯整数a+bi是素数当且仅当：
		1)a、b中有一个是零，另一个数的绝对值是形如4n+3的素数；
		2)a、b均不为零，而a^2+b^2为素数；
	*/
	static bool IsPrime(gint N)
	{
		//return is_gausian_prime(complex<long>(N.m_a,N.m_b));
		int a=abs(N.m_a);
		int b=abs(N.m_b);		
		if(a==0 && (b+1)%4==0)
			return true;
		if(b==0 && (a+1)%4==0)
			return true;
		if(a*b>0 && ::IsPrime(a*a+b*b))
			return true;
		return false;
	}
	
	// 按范数和辐角主值从小到大排列顺序
	bool operator < (const gint &m)const 
	{
	   int norm1=m_a*m_a+m_b*m_b;
	   int norm2=m.m_a*m.m_a+m.m_b*m.m_b;
	   float arg1=atan2f(m_b,m_a);
	   float arg2=atan2f(m.m_b,m.m_a);
	   float pi=atan2f(0,-1);
	   if(arg1<0)
		   arg1+=2*pi;
	   if(arg2<0)
		   arg2+=2*pi;
	   if(norm1!=norm2)
		   return norm1<norm2;
	   else
           return arg1<arg2;
	}

	friend ostream& operator<< (ostream& os,const gint& N);
public:
	long m_a;
	long m_b;
};
ostream& operator<< (ostream& os,const gint& N)
{
	string strDes=(gint::IsPrime(N)?"是高斯素数":"不是高斯素数");
	if(N.m_a!=0 && N.m_b>0)
		cout<<N.m_a<<"+"<<N.m_b<<"i"<<strDes;
	if(N.m_a!=0 && N.m_b<0)
		cout<<N.m_a<<N.m_b<<"i"<<strDes;
	if(/*N.m_a!=0 && */N.m_b==0)
		cout<<N.m_a<<strDes;
	if(N.m_a==0 && N.m_b!=0)
		cout<<N.m_b<<"i"<<strDes;
	return os;
}

unsigned int Primes[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,
	107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,
	337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,
	593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,
	857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};
int main(void)
{
#if 0
	for(int i=0;i<sizeof(Primes)/sizeof(unsigned int);i++)
		cout<<gint(Primes[i],0)<<endl;
	cout<<gint(1,0)<<endl;
	cout<<gint(-1,0)<<endl;
	cout<<gint(0,1)<<endl;
	cout<<gint(0,-1)<<endl;
	cout<<gint(1,1)<<endl;
	cout<<gint(1,-1)<<endl;
	cout<<gint(4,3)<<endl;
	cout<<gint(5,4)<<endl;
	cout<<gint(0,0)<<endl;
#endif

#if 1
	int Norm=100;//36;
	int n=sqrt((float)Norm);
	vector<gint> vgint;
	for(int i=-n;i<=n;i++)
	 for(int j=-n;j<=n;j++)
	 {
	     gint a(i,j);  
		 vgint.push_back(a);
		 //cout<<a<<endl;
	 }
	 cout<<"范数不超过"<<Norm<<"的高斯整数共有"<<vgint.size()<<"个。"<<endl;
	 sort(vgint.begin(), vgint.end(),less<gint>());
	 for(int j=0;j<vgint.size();j++)
	 {
		 cout<<"第"<<j<<"个高斯整数是"<<vgint[j]<<endl;
		 if(j>0 && j%297==0)
		 {
		     //system("pause");
		 }
	 }
#endif

	//system("pause");
	return 0;
}