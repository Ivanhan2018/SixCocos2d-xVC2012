#include<iostream>
#include<cmath>
#include<complex>
using namespace std;
/*
c++多项式类\求一元三次方程的实根
	x^3+px+q=0：
	x甲=((-q+sqrt(q^2+4p^3/27))/2)^(1/3)+((-q-sqrt(q^2+4p^3/27))/2)^(1/3)
	x乙=(-x甲+sqrt(-3x甲^2-4p))/2
	x丙=(-x甲-sqrt(-3x甲^2-4p))/2
*/

typedef float Real;

struct E3
{
public:
	E3(Real p,Real q):m_p(p),m_q(q){}
	Real DeltOfE3()
	{
		Real ret=m_q*m_q+4*m_p*m_p*m_p/27;
		return ret;
	}
	Real cube(Real a)
	{
		if(a==0)
			return 0;
		if(a>0)
			return expf(1.0*logf(a)/3.0);
		else
			return -expf(1.0*logf(-a)/3.0);
	}
	complex<Real> cube(complex<Real> a)
	{
		return exp(complex<Real>(1.0/3.0,0)*log(a));
	}
	//与牛顿切线法求得的实根值是一致的
	Real xOfE3()
	{
		Real delt=DeltOfE3();
		if(delt>=0)
		{
			Real ret1=cube((-m_q+sqrtf(delt))*0.5);
			Real ret2=cube((-m_q-sqrtf(delt))*0.5);
			return ret1+ret2;
		}
		else
		{
			complex<Real> ret1=cube((-m_q+sqrt(complex<Real>(delt,0)))*complex<Real>(0.5,0));
			complex<Real> ret2=cube((-m_q-sqrt(complex<Real>(delt,0)))*complex<Real>(0.5,0));
			return (ret1+ret2).real();
		}
	}
	//返回true表示有三个实根，返回false表示只有一个实根
	//即初中笔记中的跳板公式
	bool x2x3OfE3(Real &x2,Real &x3)
	{
		Real x1=xOfE3();
		Real delt1=-3*x1*x1-4*m_p;
		if(delt1>=0)
		{
			x2=(-x1+sqrtf(delt1))*0.5;
			x3=(-x1-sqrtf(delt1))*0.5;
			return true;
		}
		else
			return false;//即另外两根为虚根或伪虚根
	}
public:
   Real m_p;
   Real m_q;
};
int main()
{
	{
		E3 E3_1011(1,1);
		Real x=E3_1011.xOfE3();//x^3+x+1=0的一实根为：x = -0.68232781
		Real x2,x3;
		bool ret=E3_1011.x2x3OfE3(x2,x3);
		cout<<"x="<<x<<",x2="<<x2<<",x3="<<x3<<endl;
	}
	{
		//2000.10.30星期二,x^3-0.75x+0.125=0的三实根为：sin50°=x=0.76604444、sin10°=x2=0.17364815、sin50°+sin10°=x3=-0.93969262
		E3 E3_sin10(-0.75,0.125);
		Real x=E3_sin10.xOfE3();
		Real x2,x3;
		bool ret=E3_sin10.x2x3OfE3(x2,x3);
		cout<<"x="<<x<<",x2="<<x2<<",x3="<<x3<<endl;
	}
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}