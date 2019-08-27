#include<iostream>
#include<complex>
#include<vector>
#include<algorithm>
using namespace std;

/*
艾森斯坦整数或欧拉整数是具有以下形式的复数：z=a+bω，其中a和b是整数，且ω=-1/2+sqrt(3)i/2=e^(2pii/3)是本原（非实）的三次单位根。
艾森斯坦整数在复平面上形成了一个三角形点阵。高斯整数则形成了一个正方形点阵。
艾森斯坦整数环中的可逆元群，是复平面中六次单位根所组成的循环群。它们是：{±1,±ω,±ω^2}，它们是范数为1的艾森斯坦整数。
设x和y是艾森斯坦整数，如果存在某个艾森斯坦整数z，使得y=zx，则我们说x能整除y。
它是整数的整除概念的延伸。因此我们也可以延伸素数的概念：一个非可逆元的艾森斯坦整数x是艾森斯坦素数，如果它唯一的因子是ux的形式，其中u是六次单位根的任何一个。
我们可以证明，任何一个被3除余1的素数都具有形式x^2+-xy+y^2，因此可以分解为(x+ωy)(x+ω^2y)。因为这样，它在艾森斯坦整数中不是素数。被3除余2的素数则不能分解为这种形式，因此它们也是艾森斯坦素数。
任何一个艾森斯坦整数a+bω，只要范数a^2-ab+b^2为素数，那么就是一个艾森斯坦素数。实际上，任何一个艾森斯坦整数要么就是这种形式，要么就是一个可逆元和一个被3除余2的素数的乘积。
艾森斯坦整数环形成了一个欧几里德域，其范数N由以下的公式给出：
N(a+bω)=a^2-ab+b^2=|a+bω|^2----注意不要混淆泛函分析中的范数与代数数论中的范数
*/
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
#if 1
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
#endif
#if 0
		//（2,1），（1,2），（-1,1），（-2,-1）都是艾森斯坦素数
		//（2,0），（2,2），（0,2），（-2,0），（-2,-2），（0,-2）都是艾森斯坦素数
		//int a1=abs(N.m_a);
		//int b1=abs(N.m_b);		
		//if(N.m_a==1 && N.m_b==-1)
		//	return true;
		//if(N.m_b==0 && (a1+1)%3==0)
		//	return true;
		int norm=N.m_a*N.m_a+N.m_b*N.m_b-N.m_a*N.m_b;
		if(::IsPrime(norm)/* && (abs(norm)+2)%3==0*/)
			return true;
		return false;
#endif
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
#if 0
	cout<<"    ";
	complex<float> z1=complex<float>(N.m_a,0)+zeta3*zeta3*complex<float>(N.m_b,0);
	cout<<N.m_a<<"+"<<N.m_b<<"ω^2"<<"="<<z1;
#endif
	return os;
}

int main(void)
{
#if 0
	cout<<eint(1,0)<<endl;
	cout<<eint(-1,0)<<endl;
	cout<<eint(0,1)<<endl;
	cout<<eint(0,-1)<<endl;
	cout<<eint(1,1)<<endl;
	cout<<eint(1,-1)<<endl;
	cout<<eint(4,3)<<endl;
	cout<<eint(5,4)<<endl;
	cout<<eint(0,0)<<endl;
#endif

#if 1
	int n=4;
	int Norm=n*n*3;
	float pi=atan2f(0,-1);
	complex<float> zeta3=std::exp(complex<float>(0,2*pi/3));
	complex<float> z=complex<float>(n,0)+zeta3*complex<float>(-n,0);
	float r=std::abs(z);
	vector<eint> veint;
	for(int i=-n;i<=n;i++)
		for(int j=-n;j<=n;j++)
		{
			eint a(i,j);  
			veint.push_back(a);
			//cout<<a<<endl;
		}
		cout<<"复数模不超过"<<r<<"且范数不超过"<<Norm<<"的艾森斯坦整数共有"<<veint.size()<<"个。"<<endl;
		sort(veint.begin(), veint.end(),less<eint>());
		for(int j=0;j<veint.size();j++)
		{
			cout<<"第"<<j<<"个艾森斯坦整数是"<<veint[j]<<endl;
			if(j>0 && j%297==0)
			{
				//system("pause");
			}
		}
#endif

	//system("pause");
	return 0;
}

