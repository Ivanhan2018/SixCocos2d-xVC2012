// COMPLEX.cpp : 定义 DLL 应用程序的入口点。
//

#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>
#include <math.h>

#ifdef _MANAGED
#pragma managed(push, off)
#endif
extern "C" _declspec(dllexport)void __stdcall occos(double x,double y,double *u,double *v);
extern "C" _declspec(dllexport)void __stdcall ocdiv(double a,double b,double c,double d,double *e,double *f);
extern "C" _declspec(dllexport)void __stdcall ocexp(double x,double y,double *u,double *v);
extern "C" _declspec(dllexport)void __stdcall oclog(double x,double y,double *u,double *v);
extern "C" _declspec(dllexport)void __stdcall ocmul(double a,double b,double c,double d,double *e,double *f);
extern "C" _declspec(dllexport)void __stdcall ocsin(double x,double y,double *u,double *v);
extern "C" _declspec(dllexport)void __stdcall ontrt(double x,double y,int n,double *u,double *v);
extern "C" _declspec(dllexport)void __stdcall opowr(double x,double y,int n,double *u,double *v);
#define pi (double)3.14159265359
/*复数定义*/
typedef struct
{
	double re;
	double im;
}DCOMPLEX;
extern "C" _declspec(dllexport)DCOMPLEX __stdcall CSin(const DCOMPLEX *c1);
extern "C" _declspec(dllexport)DCOMPLEX __stdcall CCos(const DCOMPLEX *c1);
extern "C" _declspec(dllexport)DCOMPLEX __stdcall CTan(const DCOMPLEX *c1);
extern "C" _declspec(dllexport)DCOMPLEX __stdcall CDiv(const DCOMPLEX *c1, const DCOMPLEX *c2);

#include<complex>
#include<limits>
using namespace std;
typedef std::complex<double> dcomplex;


#define M_PI 3.14159265358979323846

extern "C"
{
	//算术几何平均
	_declspec(dllexport)DCOMPLEX __stdcall agm(const DCOMPLEX *a0,const DCOMPLEX *b0,double prec,unsigned int m);
	_declspec(dllexport)DCOMPLEX __stdcall agm1(const DCOMPLEX a0,const DCOMPLEX b0,double prec,unsigned int m);
	//勒让德第一类完全椭圆积分
	_declspec(dllexport)DCOMPLEX __stdcall K(const DCOMPLEX *z);
	//雅可比theta函数
	_declspec(dllexport)DCOMPLEX __stdcall theta(const DCOMPLEX *z,const DCOMPLEX *tau);//
	_declspec(dllexport)DCOMPLEX __stdcall theta_q(const DCOMPLEX *z,const DCOMPLEX *q);//JT3
	_declspec(dllexport)DCOMPLEX __stdcall theta_1(const DCOMPLEX *z,const DCOMPLEX *q);//JT1
	_declspec(dllexport)DCOMPLEX __stdcall theta_2(const DCOMPLEX *z,const DCOMPLEX *q);//
	_declspec(dllexport)DCOMPLEX __stdcall theta_3(const DCOMPLEX *z,const DCOMPLEX *q);//
	_declspec(dllexport)DCOMPLEX __stdcall theta_4(const DCOMPLEX *z,const DCOMPLEX *q);//
	_declspec(dllexport)DCOMPLEX __stdcall theta_00(const DCOMPLEX *z,const DCOMPLEX *tau);//JT3
	_declspec(dllexport)DCOMPLEX __stdcall theta_01(const DCOMPLEX *z,const DCOMPLEX *tau);//JT4
	_declspec(dllexport)DCOMPLEX __stdcall theta_10(const DCOMPLEX *z,const DCOMPLEX *tau);//JT1
	_declspec(dllexport)DCOMPLEX __stdcall theta_11(const DCOMPLEX *z,const DCOMPLEX *tau);//JT2
	_declspec(dllexport)DCOMPLEX __stdcall q_from_k(const DCOMPLEX *k);
	_declspec(dllexport)DCOMPLEX __stdcall setup_period(const DCOMPLEX *k,const DCOMPLEX *g);
	_declspec(dllexport)DCOMPLEX __stdcall sn(const DCOMPLEX *u,const DCOMPLEX *k);
	_declspec(dllexport)DCOMPLEX __stdcall p(const DCOMPLEX *z, const DCOMPLEX *tau);//实周期为1个单位（w1=1）。计算结果同math::detail::weierstrass_e1
	_declspec(dllexport)DCOMPLEX __stdcall P(const DCOMPLEX *z, const DCOMPLEX *tau, const DCOMPLEX *w1);//实周期为w1个单位（w1=w1）。计算结果同math::weierstrass_p2
	_declspec(dllexport)DCOMPLEX __stdcall e1(const DCOMPLEX *tau);//计算结果同math::detail::weierstrass_e1
	_declspec(dllexport)DCOMPLEX __stdcall e2(const DCOMPLEX *tau);//计算结果同math::detail::weierstrass_e2
	_declspec(dllexport)DCOMPLEX __stdcall e3(const DCOMPLEX *tau);//计算结果约同（≈）math::detail::weierstrass_e3
	//平稳值e_1,e_2,e_3的计算
	_declspec(dllexport)DCOMPLEX __stdcall E1(const DCOMPLEX *tau, const DCOMPLEX *w1);
	_declspec(dllexport)DCOMPLEX __stdcall E2(const DCOMPLEX *tau, const DCOMPLEX *w1);
	_declspec(dllexport)DCOMPLEX __stdcall E3(const DCOMPLEX *tau, const DCOMPLEX *w1);
	//不变量g_2,g_3的计算
	_declspec(dllexport)DCOMPLEX __stdcall g2(const DCOMPLEX *tau, const DCOMPLEX *w1);
	_declspec(dllexport)DCOMPLEX __stdcall g3(const DCOMPLEX *tau, const DCOMPLEX *w1);
};



BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	return TRUE;
}

//算术几何平均
namespace detail{
	dcomplex agm(const dcomplex& a0,const dcomplex& b0,double prec,unsigned m);
}

//算术几何平均
namespace detail{
	dcomplex agm(const dcomplex& a0,const dcomplex& b0,double prec,unsigned m)
	{
		dcomplex a=a0;
		dcomplex b=b0;
		dcomplex t;
		for(unsigned n=0;std::abs(0.5*(a-b))>prec && n<m;++n)
		{
			t=0.5*(a+b);
			b=std::sqrt(a*b);
			a=t;
		}
		return a;
	}
}

//勒让德第一类完全椭圆积分
namespace detail{
	dcomplex K(const dcomplex& k,double e,unsigned m);
	dcomplex K(const dcomplex& z)
	{
		return K(z,std::abs(z)*1e-15,500);
	}
}

//勒让德第一类完全椭圆积分
namespace detail{
	dcomplex K(const dcomplex& k,double e,unsigned m)
	{
		dcomplex a=detail::agm(1.0,std::sqrt(1.0-k*k),e,m);
		return M_PI/2.0/a;
	}
}

//雅可比theta函数
namespace detail{
	//computed to pretty high accuracy(a few epsilon)
	dcomplex theta_q(const dcomplex& z,const dcomplex& q);//JT3
	dcomplex theta_1(const dcomplex& z,const dcomplex& q);//JT1
}

//雅可比theta函数
namespace detail{
	dcomplex theta_q(const dcomplex& z,const dcomplex& q)
	{
		if(std::abs(q)>=1)//XXX invalid q
			return 0;
		dcomplex s=0.0;
		dcomplex t=0.0;
		unsigned n=1;
		do
		{
			t=std::pow(q,n*n)*std::cos(static_cast<double>(2*n)*z);
			s+=t;
			++n;
		}while(n<100 && std::abs(t)>5*std::numeric_limits<double>::epsilon());
		//compute to high precision because we implement other function using that
		return 1.0+2.0*s;
	}

	inline dcomplex theta(const dcomplex& z,const dcomplex& tau)
	{
		return theta_q(z*M_PI,std::exp(M_PI*dcomplex(0,1)*tau));
	}

	dcomplex theta_1(const dcomplex& z,const dcomplex& q)
	{
		if(std::abs(q)>=1)//XXX invalid q
			return 0;
		dcomplex s=0.0;
		dcomplex t=0.0;
		unsigned n=0;
		int f=1;
		do
		{
			t=static_cast<double>(f)*std::pow(q,n*(n+1))*std::sin(static_cast<double>(2*n+1)*z);
			s+=t;
			++n;
			f*=-1;
		}while(n<100 && std::abs(t)>5*std::numeric_limits<double>::epsilon());
		//compute to high precision because we implement other function using that
		return 2.0*std::pow(q,1.0/4)*s;
	}

	inline dcomplex theta_2(const dcomplex& z,const dcomplex& q)
	{
		return theta_1(z+M_PI/2,q);
	}

	inline dcomplex theta_3(const dcomplex& z,const dcomplex& q)
	{
		return theta_q(z,q);
	}

	inline dcomplex theta_4(const dcomplex& z,const dcomplex& q)
	{
		return theta_3(z,-q);
	}

	//JT3
	inline dcomplex theta_00(const dcomplex& z,const dcomplex& tau)
	{
		return theta(z,tau);
	}

	//JT4
	inline dcomplex theta_01(const dcomplex& z,const dcomplex& tau)
	{
		return theta(z+0.5,tau);
	}

	//JT2
	inline dcomplex theta_10(const dcomplex& z,const dcomplex& tau)
	{
		return std::exp(M_PI*dcomplex(0,1)*(tau/4.0+z))*theta(z+tau/2.0,tau);
	}

	//JT1
	inline dcomplex theta_11(const dcomplex& z,const dcomplex& tau)
	{
		return std::exp(M_PI*dcomplex(0,1)*(tau/4.0+z+0.5))*theta(z+tau/2.0+0.5,tau);
	}
}

namespace detail{
	dcomplex q_from_k(const dcomplex& k);
	dcomplex setup_period(const dcomplex& k,const dcomplex& g);
}

namespace detail{
	dcomplex q_from_k(const dcomplex& k)
	{
		dcomplex kprimes=std::pow(1.0-k*k,1.0/4);
		dcomplex l=0.5*(1.0-kprimes)/(1.0+kprimes);
		dcomplex l4=l*l*l*l;
		dcomplex q=l;
		l*=l4;q+=2.0*l;
		l*=l4;q+=15.0*l;
		l*=l4;q+=150.0*l;
		l*=l4;q+=1707.0*l;
		l*=l4;q+=20910.0*l;
		l*=l4;q+=268616.0*l;
		//XXX manually truncated series representation,error should be less than 10^(-4) for |k|<500
		//std::cout<<268616*std::pow(l,25)<<std::endl;
		return q;
	}

	dcomplex setup_period(const dcomplex& k,const dcomplex& g)
	{
		dcomplex K;//double quarter period
		dcomplex iK_prime;
		dcomplex P;
		K=detail::K(k,1e-25,5000);
		iK_prime=dcomplex(0,1)*detail::K(std::sqrt(1.0-k*k),1e-25,5000);
		if((K/g).imag()>(iK_prime/g).imag())
			P=K;
		else
			P=iK_prime;
		P*=4.0/g;
		return P;
	}
}

namespace detail{
	dcomplex sn(const dcomplex& u,const dcomplex& k);
	dcomplex P(const dcomplex& z, const dcomplex& tau);//实周期为1个单位（w1=1）。计算结果同math::detail::weierstrass_e1
	dcomplex P(const dcomplex& z, const dcomplex& tau, const dcomplex& w1);//实周期为w1个单位（w1=w1）。计算结果同math::weierstrass_p2

	dcomplex e1(const dcomplex& tau);//计算结果同math::detail::weierstrass_e1
	dcomplex e2(const dcomplex& tau);//计算结果同math::detail::weierstrass_e2
	dcomplex e3(const dcomplex& tau);//计算结果约同（≈）math::detail::weierstrass_e3

	//平稳值e_1,e_2,e_3的计算
	inline dcomplex e1(const dcomplex& tau, const dcomplex& w1)
	{
		return e1(tau)/(w1*w1);
	}
	inline dcomplex e2(const dcomplex& tau, const dcomplex& w1)
	{
		return e2(tau)/(w1*w1);
	}
	inline dcomplex e3(const dcomplex& tau, const dcomplex& w1)
	{
		return e3(tau)/(w1*w1);
	}

	//不变量g_2,g_3的计算
	inline dcomplex g2(const dcomplex& tau, const dcomplex& w1)
	{
		dcomplex e1=detail::e1(tau,w1);
		dcomplex e2=detail::e2(tau,w1);
		dcomplex e3=detail::e3(tau,w1);
		dcomplex retg2=dcomplex(2.0,0)*(e1*e1+e2*e2+e3*e3);
		return retg2;
	}
	inline dcomplex g3(const dcomplex& tau, const dcomplex& w1)
	{
		dcomplex e1=detail::e1(tau,w1);
		dcomplex e2=detail::e2(tau,w1);
		dcomplex e3=detail::e3(tau,w1);
		dcomplex retg3=dcomplex(4.0,0)*e1*e2*e3;
		return retg3;
	}

	//void Test1()
	//{
	//	std::cout<<"g_2(实周期w_1=8.626062，虚周期w_2=7.416195i)="<<g2(dcomplex(0,7.416195/8.626062),dcomplex(8.626062,0))<<std::endl;
	//	std::cout<<"g_3(实周期w_1=8.626062，虚周期w_2=7.416195i)="<<g3(dcomplex(0,7.416195/8.626062),dcomplex(8.626062,0))<<std::endl;
	//}

	//void Test2()
	//{
	//	std::cout<<"sn(u=1.26604138177897;k=0.985171431009416)="<<sn(dcomplex(1.26604138177897,0),dcomplex(0.985171431009416,0))<<std::endl;
	//}
}

namespace detail{
	dcomplex sn(const dcomplex& u,const dcomplex& k)
	{
		if(k==0.0)
			return std::sin(u);
		static dcomplex last_k=std::numeric_limits<double>::quiet_NaN();
		static dcomplex f;
		static dcomplex g;
		static dcomplex q;
		static dcomplex P;//period to use for reduction
		if(k!=last_k)
		{
			q=q_from_k(k);
			f=theta_3(0,q)/theta_2(0,q);
			g=theta_3(0,q);
			g*=g;
			P=setup_period(k,g);
			last_k=k;
		}
		dcomplex z=u/g;

		//reduce imaginary part
		int a=static_cast<int>(z.imag()/P.imag());
		z-=static_cast<double>(a)*P;

		return f*theta_1(z,q)/theta_4(z,q);
	}

	dcomplex P(const dcomplex& z, const dcomplex& tau)
	{
		dcomplex z1=dcomplex(M_PI*M_PI,0);
		dcomplex z2=z1*std::pow(theta_00(dcomplex(0,0),tau),2);
		z2=z2*std::pow(theta_10(dcomplex(0,0),tau),2);
		z2=z2*std::pow(theta_01(z,tau),2);
		z2=z2/std::pow(theta_11(z,tau),2);
		dcomplex z3=(z1/dcomplex(3.0,0))*(std::pow(theta_00(dcomplex(0,0),tau),4)+std::pow(theta_10(dcomplex(0,0),tau),4));
		return z2-z3;
	}

	dcomplex P(const dcomplex& z, const dcomplex& tau, const dcomplex& w1)
	{
		dcomplex retP=P(z/w1,tau)/(w1*w1);
		return retP;
	}

	dcomplex e1(const dcomplex& tau)
	{
		dcomplex z1=dcomplex(M_PI*M_PI,0);
		dcomplex e1=(z1/dcomplex(3.0,0))*(std::pow(theta_00(dcomplex(0,0),tau),4)+std::pow(theta_01(dcomplex(0,0),tau),4));
		return e1;
	}

	dcomplex e2(const dcomplex& tau)
	{
		dcomplex z1=dcomplex(M_PI*M_PI,0);
		dcomplex e2=-(z1/dcomplex(3.0,0))*(std::pow(theta_00(dcomplex(0,0),tau),4)+std::pow(theta_10(dcomplex(0,0),tau),4));
		return e2;
	}

	dcomplex e3(const dcomplex& tau)
	{
		dcomplex z1=dcomplex(M_PI*M_PI,0);
		dcomplex e3=(z1/dcomplex(3.0,0))*(std::pow(theta_10(dcomplex(0,0),tau),4)-std::pow(theta_01(dcomplex(0,0),tau),4));
		return e3;
	}

}

//算术几何平均
DCOMPLEX __stdcall agm(const DCOMPLEX *a0,const DCOMPLEX *b0,double prec,unsigned int m)
{
	dcomplex ret=detail::agm(dcomplex(a0->re,a0->im),dcomplex(b0->re,b0->im),prec,m);
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

//算术几何平均
DCOMPLEX __stdcall agm1(const DCOMPLEX a0,const DCOMPLEX b0,double prec,unsigned int m)
{
	dcomplex ret=detail::agm(dcomplex(a0.re,a0.im),dcomplex(b0.re,b0.im),prec,m);
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

//勒让德第一类完全椭圆积分
DCOMPLEX __stdcall K(const DCOMPLEX *z)
{
	dcomplex ret=detail::K(dcomplex(z->re,z->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

//雅可比theta函数
DCOMPLEX __stdcall theta(const DCOMPLEX *z,const DCOMPLEX *tau)
{
	dcomplex ret=detail::theta(dcomplex(z->re,z->im),dcomplex(tau->re,tau->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall theta_q(const DCOMPLEX *z,const DCOMPLEX *q)
{
	dcomplex ret=detail::theta_q(dcomplex(z->re,z->im),dcomplex(q->re,q->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall theta_1(const DCOMPLEX *z,const DCOMPLEX *q)
{
	dcomplex ret=detail::theta_1(dcomplex(z->re,z->im),dcomplex(q->re,q->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall theta_2(const DCOMPLEX *z,const DCOMPLEX *q)
{
	dcomplex ret=detail::theta_2(dcomplex(z->re,z->im),dcomplex(q->re,q->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall theta_3(const DCOMPLEX *z,const DCOMPLEX *q)
{
	dcomplex ret=detail::theta_3(dcomplex(z->re,z->im),dcomplex(q->re,q->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall theta_4(const DCOMPLEX *z,const DCOMPLEX *q)
{
	dcomplex ret=detail::theta_4(dcomplex(z->re,z->im),dcomplex(q->re,q->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall theta_00(const DCOMPLEX *z,const DCOMPLEX *tau)
{
	dcomplex ret=detail::theta_00(dcomplex(z->re,z->im),dcomplex(tau->re,tau->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall theta_01(const DCOMPLEX *z,const DCOMPLEX *tau)
{
	dcomplex ret=detail::theta_01(dcomplex(z->re,z->im),dcomplex(tau->re,tau->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall theta_10(const DCOMPLEX *z,const DCOMPLEX *tau)
{
	dcomplex ret=detail::theta_10(dcomplex(z->re,z->im),dcomplex(tau->re,tau->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall theta_11(const DCOMPLEX *z,const DCOMPLEX *tau)
{
	dcomplex ret=detail::theta_11(dcomplex(z->re,z->im),dcomplex(tau->re,tau->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}


DCOMPLEX __stdcall q_from_k(const DCOMPLEX *k)
{
	dcomplex ret=detail::q_from_k(dcomplex(k->re,k->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall setup_period(const DCOMPLEX *k,const DCOMPLEX *g)
{
	dcomplex ret=detail::setup_period(dcomplex(k->re,k->im),dcomplex(g->re,g->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall sn(const DCOMPLEX *u,const DCOMPLEX *k)
{
	dcomplex ret=detail::sn(dcomplex(u->re,u->im),dcomplex(k->re,k->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall p(const DCOMPLEX *z, const DCOMPLEX *tau)
{
	dcomplex ret=detail::P(dcomplex(z->re,z->im),dcomplex(tau->re,tau->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall P(const DCOMPLEX *z, const DCOMPLEX *tau, const DCOMPLEX *w1)
{
	dcomplex ret=detail::P(dcomplex(z->re,z->im),dcomplex(tau->re,tau->im),dcomplex(w1->re,w1->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}


DCOMPLEX __stdcall e1(const DCOMPLEX *tau)
{
	dcomplex ret=detail::e1(dcomplex(tau->re,tau->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall e2(const DCOMPLEX *tau)
{
	dcomplex ret=detail::e2(dcomplex(tau->re,tau->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall e3(const DCOMPLEX *tau)
{
	dcomplex ret=detail::e3(dcomplex(tau->re,tau->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}
//平稳值e_1,e_2,e_3的计算
DCOMPLEX __stdcall E1(const DCOMPLEX *tau, const DCOMPLEX *w1)
{
	dcomplex ret=detail::e1(dcomplex(tau->re,tau->im),dcomplex(w1->re,w1->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall E2(const DCOMPLEX *tau, const DCOMPLEX *w1)
{
	dcomplex ret=detail::e2(dcomplex(tau->re,tau->im),dcomplex(w1->re,w1->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall E3(const DCOMPLEX *tau, const DCOMPLEX *w1)
{
	dcomplex ret=detail::e3(dcomplex(tau->re,tau->im),dcomplex(w1->re,w1->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

//不变量g_2,g_3的计算
DCOMPLEX __stdcall g2(const DCOMPLEX *tau, const DCOMPLEX *w1)
{
	dcomplex ret=detail::g2(dcomplex(tau->re,tau->im),dcomplex(w1->re,w1->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

DCOMPLEX __stdcall g3(const DCOMPLEX *tau, const DCOMPLEX *w1)
{
	dcomplex ret=detail::g3(dcomplex(tau->re,tau->im),dcomplex(w1->re,w1->im));
	DCOMPLEX ret1;
	ret1.re=ret.real();
	ret1.im=ret.imag();
	return ret1;
}

/*
void main (void)
 {
   DCOMPLEX x(1,2.1),y;
   std::cout<<"sin(1,2.1)="<<std::sin(x)<<std::endl;
   //复数求模abs(55.6,68.2)=87.992
   std::cout<<"abs(55.6,68.2)="<<std::abs(DCOMPLEX(55.6,68.2))<<std::endl;
   //求实幂指数(16+81i)^3=(-310832,-469233)
   DCOMPLEX cpxZ(16,81);
   DCOMPLEX cpxPow=std::pow(cpxZ,3);
   std::cout<<"(16+81i)^3="<<cpxPow<<std::endl;
   //复数相乘(9+11i)(56+3i)=(471,643)
   DCOMPLEX cpxZ1(9,11),cpxZ2(56,3);
   std::cout<<"(9+11i)(56+3i)="<<cpxZ1*cpxZ2<<std::endl;
   //复数相除(471+643i)/(9+11i)=(56,3)
   cpxZ1=DCOMPLEX(471,643);
   cpxZ2=DCOMPLEX(9,11);
   std::cout<<"(471+643i)/(9+11i)="<<cpxZ1/cpxZ2<<std::endl;

   detail::Test2();

   getchar();
 }
*/
DCOMPLEX __stdcall CDiv(const DCOMPLEX *c1, const DCOMPLEX *c2)
{
	DCOMPLEX ret;
	ocdiv(c1->re,c1->im,c2->re,c2->im,&(ret.re),&(ret.im));
	return ret;
}

DCOMPLEX __stdcall CSin(const DCOMPLEX *c1)
{
	DCOMPLEX ret;
	ocsin(c1->re,c1->im,&(ret.re),&(ret.im));
	return ret;
}

DCOMPLEX __stdcall CCos(const DCOMPLEX *c1)
{
	DCOMPLEX ret;
	occos(c1->re,c1->im,&(ret.re),&(ret.im));
	return ret;
}

DCOMPLEX __stdcall CTan(const DCOMPLEX *c1)
{
	DCOMPLEX ret1=CSin(c1);
	DCOMPLEX ret2=CCos(c1);
	DCOMPLEX ret=CDiv(&ret1,&ret2);
	return ret;
}

void __stdcall occos(double x,double y,double *u,double *v)
{ 
	double p,q;
	p=exp(y); q=exp(-y);
	*u=cos(x)*(p+q)/2.0; *v=-sin(x)*(p-q)/2.0;
	return;
}

void __stdcall ocdiv(double a,double b,double c,double d,double *e,double *f)
{ 
	double p,q,s,w;
	p=a*c; q=-b*d; s=(a+b)*(c-d);
	w=c*c+d*d;
	if(w+1.0==1.0) 
	{ *e=1.0e+35*a/fabs(a);
	*f=1.0e+35*b/fabs(b);
	}
	else
	{ *e=(p-q)/w; *f=(s-p-q)/w; }
	return;
}

void __stdcall ocexp(double x,double y,double *u,double *v)
{ 
	double p;
	p=exp(x);
	*u=p*cos(y); *v=p*sin(y);
	return;
}

void __stdcall oclog(double x,double y,double *u,double *v)
{ 
	double p;
	p=log(sqrt(x*x+y*y));
	*u=p; *v=atan2(y,x);
	return;
}

void __stdcall ocmul(double a,double b,double c,double d,double *e,double *f)
{ 
	double p,q,s;
	p=a*c; q=b*d; s=(a+b)*(c+d);
	*e=p-q; *f=s-p-q;
	return;
}

void __stdcall ocsin(double x,double y,double *u,double *v)
{ 
	double p,q;
	p=exp(y); q=exp(-y);
	*u=sin(x)*(p+q)/2.0; *v=cos(x)*(p-q)/2.0;
	return;
}

void __stdcall ontrt(double x,double y,int n,double *u,double *v)
{ 
	int k;
	double r,q,t;
	if (n<1) return;
	q=atan2(y,x);
	r=sqrt(x*x+y*y);
	if (r+1.0!=1.0)
	{ r=(1.0/n)*log(r); r=exp(r);}
	for (k=0; k<=n-1; k++)
	{ 
		t=(2.0*k*3.1415926+q)/n;
		u[k]=r*cos(t); v[k]=r*sin(t);
	}
	return;
}

void __stdcall opowr(double x,double y,int n,double *u,double *v)
{ 
	double r,q;
	q=atan2(y,x);
	r=sqrt(x*x+y*y);
	if (r+1.0!=1.0)
	{ 
		r=n*log(r); r=exp(r);}
	*u=r*cos(n*q); *v=r*sin(n*q);
	return;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

