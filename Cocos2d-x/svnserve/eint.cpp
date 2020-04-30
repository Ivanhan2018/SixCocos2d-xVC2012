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

class eint
{
public:
	eint(long a,long b)
	{
		m_a=a;
		m_b=b;
	}

	/*
		艾森斯坦整数a+bω是素数当且仅当：
		An Eisenstein integer z = a + bω is an Eisenstein prime if and only if either of the following (mutually exclusive) conditions hold:
		z is equal to the product of a unit and a natural prime of the form 3n - 1, 
		|z|2 = a2 + ab + b2 is a natural prime (necessarily congruent to 0 or 1 modulo 3). 
		It follows that the absolute value squared of every Eisenstein prime is a natural prime or the square of a natural prime.
		3 = ?(1 + 2ω)2 
		7 = (3 + ω)(2 ? ω). 
		2 + ω, 3 + ω, 4 + ω, 5 + 2ω, 6 + ω, 7 + ω, 7 + 3ω. 
	*/
	static bool IsPrime(eint N)
	{
		// a+bω的6个相伴元：a+bω,-a-bω，-b+(a-b)ω，b+(b-a)ω，(b-a)-aω，(a-b)+aω，范数都是a^-ab+b^2
		int norm=N.m_a*N.m_a+N.m_b*N.m_b-N.m_a*N.m_b;
		// a,-a，aω，-aω，-a-aω，a+aω
		if(N.m_a>0 && (N.m_a+1)%3==0 && N.m_b==0)
			return true;
		if(N.m_a<0 && (-N.m_a+1)%3==0 && N.m_b==0)
			return true;
		if(N.m_b>0 && (N.m_b+1)%3==0 && N.m_a==0)
			return true;
		if(N.m_b<0 && (-N.m_b+1)%3==0 && N.m_a==0)
			return true;
		if(N.m_a>0 && (N.m_a+1)%3==0 && N.m_b==N.m_a)
			return true;
		if(N.m_a<0 && (-N.m_a+1)%3==0 && N.m_b==N.m_a)
			return true;
		if(::IsPrime(norm))
			return true;
		return false;
	}

	// 按范数和辐角主值从小到大排列顺序
	bool operator < (const eint &m)const 
	{
		int norm1=m_a*m_a+m_b*m_b-m_a*m_b;
		int norm2=m.m_a*m.m_a+m.m_b*m.m_b-m.m_a*m.m_b;
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

	friend ostream& operator<< (ostream& os,const eint& N);
public:
	long m_a;
	long m_b;
};

ostream& operator<< (ostream& os,const eint& N)
{
	string strDes=(eint::IsPrime(N)?"是艾森斯坦素数":"不是艾森斯坦素数");
	float pi=atan2f(0,-1);
	complex<float> zeta3=std::exp(complex<float>(0,2*pi/3));
	complex<float> z=complex<float>(N.m_a,0)+zeta3*complex<float>(N.m_b,0);
	cout<<N.m_a<<"+"<<N.m_b<<"ω"<<"="<<z<<strDes<<" ";
	int norm1=N.m_a*N.m_a+N.m_b*N.m_b-N.m_a*N.m_b;
	cout<<"复数模："<<std::abs(z)<<"范数:"<<norm1;
	return os;
}

int main(int argc, char *argv[])
{
	if( argc < 3 )
	{
		cout<<"Usage:  eint arg1 arg2"<<endl;
		return 0;
	}
    int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	cout<<eint(a,b)<<endl;
	return 0;
}	