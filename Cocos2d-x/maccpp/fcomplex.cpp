/*#include<cmath>*/ 
#include<iostream>
#include<complex>
#include<limits>
using namespace std; 
//typedef double real;
#define real double
typedef std::complex<real> fcomplex;

#define M_PI 3.14159265358979323846
#define MYCALL
extern "C" double MYCALL lelp1(double k,double f);
extern "C" double MYCALL lelp2(double k,double f);

//阿贝尔发现：snz的周期是4K及2iK’，cnz的周期是4K及2K+2iK'，dnz的周期是2K+4iK'。
//约定K叫做1/4实周期，K'叫做1/4虚周期,tau=K'/K是个纯虚数
/*
2012.3.11公式P(u)=P(u+2w)=P(u+2w')=P(-u)在代码中是指：
P(z)=P(z+w_1)=P(z+w_2)=P(-z)!=P(z+w_1/2)!=P(z+w_2/2)，这里w_1,w_2是周期，不是半周期，
P可以是math::weierstrass_p2(const complex& z,const complex& w_1, const complex& w_2)
或math::P_theta(const complex& z, const complex& tau, const complex& w1);，
这两个函数完全一致，它们的输入参数w_1,w_2均是指周期，而不是指半周期。
20121225注意：P函数、模形式g_2、g_3等数学函数的c++和jsp实现中，参数w_1,w_2是指最小实周期T，最小虚周期T'，即P(z,w_1,w_2)=P(z,T,T')。
*/

//算术几何平均
namespace detail{
	fcomplex agm(const fcomplex& a0,const fcomplex& b0,real prec,unsigned m);
}

//算术几何平均
namespace detail{
	fcomplex agm(const fcomplex& a0,const fcomplex& b0,real prec,unsigned m)
	{
		fcomplex a=a0;
		fcomplex b=b0;
		fcomplex t;
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
	fcomplex K(const fcomplex& k,real e,unsigned m);
	fcomplex K(const fcomplex& z)
	{
		return K(z,std::abs(z)*1e-15,500);
	}
}

//勒让德第一类完全椭圆积分
namespace detail{
	fcomplex K(const fcomplex& k,real e,unsigned m)
	{
		fcomplex a=detail::agm(1.0,std::sqrt(1.0-k*k),e,m);
		return M_PI/2.0/a;
	}
}

//雅可比theta函数
namespace detail{
	//computed to pretty high accuracy(a few epsilon)
	fcomplex theta_q(const fcomplex& z,const fcomplex& q);//JT3
	fcomplex theta_1(const fcomplex& z,const fcomplex& q);//JT1
}

//雅可比theta函数
namespace detail{
	fcomplex theta_q(const fcomplex& z,const fcomplex& q)
	{
		if(std::abs(q)>=1)//XXX invalid q
			return 0;
		fcomplex s=0.0;
		fcomplex t=0.0;
		unsigned n=1;
		do
		{
			t=std::pow(q,n*n)*std::cos(static_cast<real>(2*n)*z);
			s+=t;
			++n;
		}while(n<100 && std::abs(t)>5*std::numeric_limits<real>::epsilon());
		//compute to high precision because we implement other function using that
	    return 1.0+2.0*s;
	}

	inline fcomplex theta(const fcomplex& z,const fcomplex& tau)
	{
		return theta_q(z*M_PI,std::exp(M_PI*fcomplex(0,1)*tau));
	}

	fcomplex theta_1(const fcomplex& z,const fcomplex& q)
	{
		if(std::abs(q)>=1)//XXX invalid q
			return 0;
		fcomplex s=0.0;
		fcomplex t=0.0;
		unsigned n=0;
		int f=1;
		do
		{
			t=static_cast<real>(f)*std::pow(q,n*(n+1))*std::sin(static_cast<real>(2*n+1)*z);
			s+=t;
			++n;
			f*=-1;
		}while(n<100 && std::abs(t)>5*std::numeric_limits<real>::epsilon());
		//compute to high precision because we implement other function using that
		return 2.0*std::pow(q,1.0/4)*s;
	}

	inline fcomplex theta_2(const fcomplex& z,const fcomplex& q)
	{
		return theta_1(z+M_PI/2,q);
	}

	inline fcomplex theta_3(const fcomplex& z,const fcomplex& q)
	{
		return theta_q(z,q);
	}

	inline fcomplex theta_4(const fcomplex& z,const fcomplex& q)
	{
		return theta_3(z,-q);
	}

	//JT3
	inline fcomplex theta_00(const fcomplex& z,const fcomplex& tau)
	{
		return theta(z,tau);
	}

	//JT4
	inline fcomplex theta_01(const fcomplex& z,const fcomplex& tau)
	{
		return theta(z+0.5,tau);
	}

	//JT2
	inline fcomplex theta_10(const fcomplex& z,const fcomplex& tau)
	{
		return std::exp(M_PI*fcomplex(0,1)*(tau/4.0+z))*theta(z+tau/2.0,tau);
	}

	//JT1
	inline fcomplex theta_11(const fcomplex& z,const fcomplex& tau)
	{
		return std::exp(M_PI*fcomplex(0,1)*(tau/4.0+z+0.5))*theta(z+tau/2.0+0.5,tau);
	}
}

namespace detail{
	fcomplex q_from_k(const fcomplex& k);
	fcomplex setup_period(const fcomplex& k,const fcomplex& g);
	/*
		fcomplex retqk=detail::q_from_k(fcomplex(0.985171431,0));
		cout<<retqk<<endl;//(0.20788,0)
		cout<<detail::kq(0.207879576350762)<<endl;//0.985171
		cout<<detail::ckq(0.207879576350762)<<endl;//0.171573
		q=q_from_k(k=0.985171431)=0.20788
		k=kq(q=0.207879576350762)=0.985171431009416
		k'=ckq(q=0.207879576350762)=0.17157287525381
	*/
	//add by Ivan_han
	//计算k(q)
	real kq(real q)
	{
		real s1=0,s2=1;
		for(int i=1;i<=1000;i++)
			s1=s1+2*pow(q,(real)(2*i-1)*(2*i-1)/4.f);
		for(int i=1;i<=1000;i++)
			s2=s2+2*pow(q,(i*i));
		return pow(s1/s2,2);
	}

	int iseven(int n)
	{
	   int ret=1;
	   if(n%2==1)
		   ret=-1;
	   return ret;
	}

	//计算k'(q)
	real ckq(real q)
	{
		real s1=1,s2=1;
		for(int i=1;i<=1000;i++)
			s1=s1+2*pow(q,(i*i))*iseven(i);
		for(int i=1;i<=1000;i++)
			s2=s2+2*pow(q,(i*i));
		return pow(s1/s2,2);
	}

}

namespace detail{
	fcomplex q_from_k(const fcomplex& k)
	{
		fcomplex kprimes=std::pow(1.0-k*k,1.0/4);
		fcomplex l=0.5*(1.0-kprimes)/(1.0+kprimes);
        fcomplex l4=l*l*l*l;
		fcomplex q=l;
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

	fcomplex setup_period(const fcomplex& k,const fcomplex& g)
	{
		fcomplex K;//real quarter period
		fcomplex iK_prime;
		fcomplex P;
		K=detail::K(k,1e-25,5000);
		iK_prime=fcomplex(0,1)*detail::K(std::sqrt(1.0-k*k),1e-25,5000);
		if((K/g).imag()>(iK_prime/g).imag())
			P=K;
		else
			P=iK_prime;
		P*=4.0/g;
		return P;
	}
}

namespace detail{
	fcomplex sn(const fcomplex& u,const fcomplex& k);
	fcomplex P(const fcomplex& z, const fcomplex& tau);//实周期为1个单位（w1=1）。计算结果同math::detail::weierstrass_e1
	fcomplex P(const fcomplex& z, const fcomplex& tau, const fcomplex& w1);//实周期为w1个单位（w1=w1）。计算结果同math::weierstrass_p2

	fcomplex e1(const fcomplex& tau);//计算结果同math::detail::weierstrass_e1
	fcomplex e2(const fcomplex& tau);//计算结果同math::detail::weierstrass_e2
	fcomplex e3(const fcomplex& tau);//计算结果约同（≈）math::detail::weierstrass_e3

	//平稳值e_1,e_2,e_3的计算
	inline fcomplex e1(const fcomplex& tau, const fcomplex& w1)
	{
	  return e1(tau)/(w1*w1);
	}
	inline fcomplex e2(const fcomplex& tau, const fcomplex& w1)
	{
	  return e2(tau)/(w1*w1);
	}
	inline fcomplex e3(const fcomplex& tau, const fcomplex& w1)
	{
	  return e3(tau)/(w1*w1);
	}

  //不变量g_2,g_3的计算
  inline fcomplex g2(const fcomplex& tau, const fcomplex& w1)
  {
	  fcomplex e1=detail::e1(tau,w1);
	  fcomplex e2=detail::e2(tau,w1);
	  fcomplex e3=detail::e3(tau,w1);
	  fcomplex retg2=fcomplex(2.0,0)*(e1*e1+e2*e2+e3*e3);
	  return retg2;
  }
  inline fcomplex g3(const fcomplex& tau, const fcomplex& w1)
  {
	  fcomplex e1=detail::e1(tau,w1);
	  fcomplex e2=detail::e2(tau,w1);
	  fcomplex e3=detail::e3(tau,w1);
	  fcomplex retg3=fcomplex(4.0,0)*e1*e2*e3;
	  return retg3;
  }

  //Klein's absolute invariant
  inline fcomplex KleinInvariantJ(const fcomplex& tau, const fcomplex& w1=fcomplex(1.0,0))
  {
   fcomplex g2g2g2=std::pow(g2(tau,w1),3);
   fcomplex g3g3=std::pow(g3(tau,w1),2);
   fcomplex ret=g2g2g2/(g2g2g2-g3g3*fcomplex(27.0,0));
   return ret;
  }

  void Test1()
  {
      std::cout<<"g_2(实周期w_1=8.626062，虚周期w_2=7.416195i)="<<g2(fcomplex(0,7.416195/8.626062),fcomplex(8.626062,0))<<std::endl;
	  std::cout<<"g_3(实周期w_1=8.626062，虚周期w_2=7.416195i)="<<g3(fcomplex(0,7.416195/8.626062),fcomplex(8.626062,0))<<std::endl;
  }

  void Test2()
  {
      std::cout<<"sn(u=1.26604138177897;k=0.985171431009416)="<<sn(fcomplex(1.26604138177897,0),fcomplex(0.985171431009416,0))<<std::endl;
  }
}

namespace detail{
	fcomplex sn(const fcomplex& u,const fcomplex& k)
	{
		if(k==0.0)
		  return std::sin(u);
		static fcomplex last_k=std::numeric_limits<real>::quiet_NaN();
		static fcomplex f;
		static fcomplex g;
		static fcomplex q;
		static fcomplex P;//period to use for reduction
		if(k!=last_k)
		{
			q=q_from_k(k);
			f=theta_3(0,q)/theta_2(0,q);
			g=theta_3(0,q);
			g*=g;
			P=setup_period(k,g);
			last_k=k;
		}
		fcomplex z=u/g;

		//reduce imaginary part
		int a=static_cast<int>(z.imag()/P.imag());
		z-=static_cast<real>(a)*P;

		return f*theta_1(z,q)/theta_4(z,q);
	}

	fcomplex P(const fcomplex& z, const fcomplex& tau)
	{
	   fcomplex z1=fcomplex(M_PI*M_PI,0);
	   fcomplex z2=z1*std::pow(theta_00(fcomplex(0,0),tau),2);
	   z2=z2*std::pow(theta_10(fcomplex(0,0),tau),2);
	   z2=z2*std::pow(theta_01(z,tau),2);
	   z2=z2/std::pow(theta_11(z,tau),2);
	   fcomplex z3=(z1/fcomplex(3.0,0))*(std::pow(theta_00(fcomplex(0,0),tau),4)+std::pow(theta_10(fcomplex(0,0),tau),4));
	   return z2-z3;
	}

	fcomplex P(const fcomplex& z, const fcomplex& tau, const fcomplex& w1)
	{
	   fcomplex retP=P(z/w1,tau)/(w1*w1);
	   return retP;
	}

	fcomplex e1(const fcomplex& tau)
	{
	   fcomplex z1=fcomplex(M_PI*M_PI,0);
	   fcomplex e1=(z1/fcomplex(3.0,0))*(std::pow(theta_00(fcomplex(0,0),tau),4)+std::pow(theta_01(fcomplex(0,0),tau),4));
	   return e1;
	}

	fcomplex e2(const fcomplex& tau)
	{
	   fcomplex z1=fcomplex(M_PI*M_PI,0);
	   fcomplex e2=-(z1/fcomplex(3.0,0))*(std::pow(theta_00(fcomplex(0,0),tau),4)+std::pow(theta_10(fcomplex(0,0),tau),4));
	   return e2;
	}

	fcomplex e3(const fcomplex& tau)
	{
	   fcomplex z1=fcomplex(M_PI*M_PI,0);
	   fcomplex e3=(z1/fcomplex(3.0,0))*(std::pow(theta_10(fcomplex(0,0),tau),4)-std::pow(theta_01(fcomplex(0,0),tau),4));
	   return e3;
	}

}


static double MYCALL fk(double k,double f)
{ 
	int m,i,j;
	double s,p,ep,h,aa,bb,w,xx,g,q;
	static double t[5]={-0.9061798459,-0.5384693101,0.0,0.5384693101,0.9061798459};
	static double c[5]={0.2369268851,0.4786286705,0.5688888889,0.4786286705,0.2369268851};
	m=1; g=0.0;
	h=fabs(f); s=fabs(0.0001*h);
	p=1.0e+35; ep=0.000001;
	while ((ep>=0.0000001)&&(fabs(h)>s))
	{ 
		g=0.0;
		for(i=1;i<=m;i++)
		{ 
			aa=(i-1.0)*h;
			bb=i*h;
			w=0.0;
			for(j=0;j<=4;j++)
			{ 
				xx=((bb-aa)*t[j]+(bb+aa))/2.0;
				q=sqrt(1.0-k*k*sin(xx)*sin(xx));
				w=w+c[j]/q;
			}
			g=g+w;
		}
		g=g*h/2.0;
		ep=fabs(g-p)/(1.0+fabs(g));
		p=g; 
		m=m+m; 
		h=0.5*h;
	}
	return(g);
}



static double ek(double k,double f)
{ 
	int m,i,j;
	double s,p,ep,h,aa,bb,w,xx,g,q;
	static double t[5]={-0.9061798459,-0.5384693101,0.0,0.5384693101,0.9061798459};
	static double c[5]={0.2369268851,0.4786286705,0.5688888889,0.4786286705,0.2369268851};
	m=1;
	g=0.0;
	h=fabs(f);
	s=fabs(0.0001*h);
	p=1.0e+35;
	ep=0.000001;
	while((ep>=0.0000001)&&(fabs(h)>s))
	{ 
		g=0.0;
		for(i=1;i<=m;i++)
		{ 
			aa=(i-1.0)*h; bb=i*h;
			w=0.0;
			for(j=0;j<=4;j++)
			{ 
				xx=((bb-aa)*t[j]+(bb+aa))/2.0;
				q=sqrt(1.0-k*k*sin(xx)*sin(xx));
				w=w+q*c[j];
			}
			g=g+w;
		}
		g=g*h/2.0;
		ep=fabs(g-p)/(1.0+fabs(g));
		p=g;
		m=m+m;
		h=0.5*h;
	}
	return(g);
}

double MYCALL lelp1(double k,double f)
{ 
		int n;
		double pi,y,e,ff;
		if(k<0.0)
			k=-k;
		if (k>1.0)
			k=1.0/k;
		pi=3.1415926;
		y=fabs(f);
		n=0;
		while (y>=pi)
		{ 
			n=n+1;
			y=y-pi;
		}
		e=1.0;
		if(y>=pi/2.0)
		{ 
			n=n+1; 
			e=-e; 
			y=pi-y;
		}
		if(n==0)
			ff=fk(k,y);
		else
		{ 
			ff=fk(k,pi/2.0);
			ff=2.0*n*ff+e*fk(k,y);
		}
		if(f<0.0)
			ff=-ff;
		return(ff);
}

double MYCALL lelp2(double k,double f)
{ 
		int n;
		double pi,y,e,ff;
		if(k<0.0) k=-k;
		if(k>1.0) k=1.0/k;
		pi=3.1415926; 
		y=fabs(f);
		n=0;
		while(y>=pi)
		{ 
			n=n+1;
			y=y-pi;
		}
		e=1.0;
		if(y>=pi/2.0)
		{ 
			n=n+1;
			e=-e;
			y=pi-y;
		}
		if(n==0)
			ff=ek(k,y);
		else
		{ 
			ff=ek(k,pi/2.0);
			ff=2.0*n*ff+e*ek(k,y);
		}
		if(f<0.0)ff=-ff;
		return(ff);
}
namespace Han 
{ 
	//雅可比分号形式的第一类[不完全]椭圆积分Arcsn(e;x)
	double MYCALL lelp1J(double(MYCALL *plelp1)(double e,double x),double e,double x)
	{
	  return plelp1(e,asin(x));
	}
} 

namespace math 
{ 
	double K(double e)
	{
	  return lelp1(e,asin(1.0f));
	}

	double cK(double e)
	{
	  return lelp1(sqrt(1-e*e),asin(1.0f));
	}

	double P(double x,double e)
	{
	  fcomplex ret=detail::P(fcomplex(x,0),fcomplex(0,cK(e)/K(e)),fcomplex(K(e),0));
#undef real
	  return ret.real();
#define real double
	}

	//tau=it
	double g2(double t,double w1)
	{
	  fcomplex ret=detail::g2(fcomplex(0,t),fcomplex(w1,0));
#undef real
	  return ret.real();
#define real double
	}

	//tau=it
	double g3(double t,double w1)
	{
	  fcomplex ret=detail::g3(fcomplex(0,t),fcomplex(w1,0));
#undef real
	  return ret.real();
#define real double
	}
}

int main(void) 
{ 
	double ret=Han::lelp1J(lelp1,0.866025,0.466428);//测试命名空间Han，::是作用域解析运算符 
    printf("arcsn(e=0.866025;x=0.466428)=%f\n",ret);//arcsn(e=0.866025;x=0.466428)=0.499999,//sn(u=0.500000+0.000000i;k=0.866025+0.000000i)=0.466428+0.000000i
	
	
	/*
		根据e计算1/4实、虚周期
		real retw1=math::K(complex(0.8660254,0),prec,m).real();
		real retw2=math::K(complex(std::sqrt((real)0.25),0),prec,m).real();
		complex w_1=complex(retw1,0);
		complex w_2=complex(0,retw2);

		tau=w_2/w_1=1.685750i/2.156516=0.781701i
		P(z=0.5,w_1=2.156516,w_2=1.685750i)=4.197128=P(0.5,k=0.8660254)!=4.013195
		P(z=0.5,w_1=1,w_2=tau)=P(z=0.5,tau=0.781701i)=7.750935
		错误的结果：
		g_2(tau=0.781701i)=413.330047
		g_3(tau=0.781701i)=-2086.126608
		正确的结果：
		g2(tau=0.781701i,w1=2.156516)=(17.3333,0)
		g3(tau=0.781701i,w1=2.156516)=(-10.3704,0)
		g2(tau=0.781701i,w1=1)=(374.88,0)
		g3(tau=0.781701i,w1=1)=(-1043.06,0)
		http://functions.wolfram.com/webMathematica/FunctionEvaluation.jsp
		jsp计算结果：
		P(0.5;17.3333,-10.3704)=4.19713

		问：已知w_1,w_2，求e,g_2,g_3？
		P(z=0.5,w_1=2.156516,w_2=1.854049i)=4.151395
		P(z=0.5,w_1=1,tau=0.859743i)=7.294863
		tau=w_2/w_1=0.859743i
		g2(tau=0.859743i,w1=1)=276.176
		g3(tau=0.859743i,w1=1)=-461.88
		g2(tau=0.859743i,w1=2.156516)=12.7695
		g3(tau=0.859743i,w1=2.156516)=-4.59211
		jsp计算结果：
		P(z=0.5,g_2=12.7695,g_3=-4.59211)=4.151395
		P(z=0.231855,g_2=12.7695,g_3=-4.59211)=18.6362
		c++计算结果：
		P(z=0.5,w_1=1,w_2=tau=0.859743i)=7.294862=(7.29486,-7.87764e-031)
		P(z_=z/w_1=0.231855,w_1=1,tau=0.859743i)=19.306386=(19.3064,9.34084e-015)
		P(z=0.5,w_1=2.156516,w_2=w_1*0.859743i)=(4.15139,1.00427e-015)
		P(z_=z/w_1=0.231855,w_1=2.156516,w_2=w_1*0.859743i)=(18.6362,1.02781e-014)

		tau=0.5i=>q=exp(i*pi*tau)=0.207879576350762
		cout<<detail::theta_00(fcomplex(0.2,0),fcomplex(0,0.5))<<endl;//(1.12545,0)
		cout<<detail::theta_00(fcomplex(0.2,0.2),fcomplex(0,0.5))<<endl;//(1.22519,-0.651829)
		cout<<detail::theta_00(fcomplex(0,0),fcomplex(0,0.5))<<endl;//(1.4195,0)=JT3(z=0,tau=0.5i)=1.41949548808377
		cout<<detail::theta_00(fcomplex(3.3416,0),fcomplex(0,0.5))<<endl;//(0.772187,0)
		cout<<detail::theta_00(fcomplex(1.2,0),fcomplex(0,0.5))<<endl;//(1.12545,0)
		cout<<detail::theta_01(fcomplex(0.2,0),fcomplex(0,0.5))<<endl;//(0.868503,0)
		cout<<detail::theta_01(fcomplex(0,0),fcomplex(0,0.5))<<endl;//(0.587974,0)=JT4(z=0,tau=0.5i)=0.587974282891712
		cout<<detail::theta_01(fcomplex(1.5708,0),fcomplex(0,0.5))<<endl;//(1.37765,0)
		cout<<detail::theta_01(fcomplex(1.6708,0),fcomplex(0,0.5))<<endl;//(1.19643,0)
		cout<<detail::theta_01(fcomplex(1.7708,0),fcomplex(0,0.5))<<endl;//(0.942211,0)
		cout<<detail::theta_01(fcomplex(1.8708,0),fcomplex(0,0.5))<<endl;//(0.713678,0)
		cout<<detail::theta_01(fcomplex(1,0),fcomplex(0,0.5))<<endl;//(0.587974,0)
		cout<<detail::theta_01(fcomplex(1.1,0),fcomplex(0,0.5))<<endl;//(0.664798,0)
		cout<<detail::theta_01(fcomplex(1.2,0),fcomplex(0,0.5))<<endl;//(0.868503,0)
		cout<<detail::theta_01(fcomplex(1.3,0),fcomplex(0,0.5))<<endl;//(1.12545,0)
		cout<<detail::theta_01(fcomplex(0.5,0),fcomplex(0,0.5))<<endl;//(1.4195,0)
		cout<<detail::theta_01(fcomplex(0.6,0),fcomplex(0,0.5))<<endl;//(1.33751,0)
		cout<<detail::theta_01(fcomplex(0.7,0),fcomplex(0,0.5))<<endl;//(1.12545,0)
		cout<<detail::theta_01(fcomplex(0.8,0),fcomplex(0,0.5))<<endl;//(0.868503,0)
		JT3(z=0.2,tau=0.5i)=1.12545388495798
		JT3(z=0.2+0.2i,tau=0.5i)=1.22519068532128-0.651828923108493i
		JT3(z=0,tau=0.5i)=1.41949548808377
		验证了公式：JT4(z,tau)=JT3(z+1/2,tau)，JT3(z+1,tau)=JT3(z,tau)
		而不是公式：JT4(z,tau)=JT3(z+pi/2,tau)，JT3(z+pi,tau)=JT3(z,tau)
		cout<<detail::theta_3(fcomplex(0.2,0)*M_PI,fcomplex(0.207879576350762,0))<<endl;//(1.12545,0)
		=JT3(z=0.2,tau=0.5i)=1.12545388495798
		cout<<detail::theta_3(fcomplex(0.2,0),fcomplex(0.207879576350762,0))<<endl;//(1.38554,0)
		cout<<detail::theta_3(fcomplex(0,0),fcomplex(0.207879576350762,0))<<endl;//(1.4195,0)，
		JT3(z=0,tau=0.5i)=1.41949548808377
		cout<<detail::theta_4(fcomplex(0.2,0),fcomplex(0.207879576350762,0))<<endl;//(0.619662,0)
		cout<<detail::theta_4(fcomplex(0,0),fcomplex(0.207879576350762,0))<<endl;//(0.587974,0)，
		JT4(z=0,tau=0.5i)=0.587974282891712

		cout<<detail::theta_2(fcomplex(0.2,0)*M_PI,fcomplex(0.207879576350762,0))<<endl;//(1.07441,0)
		cout<<detail::theta_10(fcomplex(0.2,0)/M_PI,fcomplex(0,0.5))<<endl;//(1.37177,0)
		cout<<detail::theta_10(fcomplex(0.2,0),fcomplex(0,0.5))<<endl;//(1.07441,-1.11022e-016)
		cout<<detail::theta_10(fcomplex(0,0),fcomplex(0,0.5))<<endl;//(1.40893,0)，某处计算结果：JT2(z=0,tau=0.5i)=0.70446581836561

		cout<<detail::theta_2(fcomplex(0.2,0),fcomplex(0.207879576350762,0))<<endl;//(1.37177,0)
		cout<<detail::theta_2(fcomplex(0,0),fcomplex(0.207879576350762,0))<<endl;//(1.40893,0)

		cout<<detail::theta_11(fcomplex(0.2,0),fcomplex(0,0.5))<<endl;//(-0.73828,-5.55112e-017)，某处计算结果：
		JT1(z=0.2,tau=0.5i)=0.369140086660667，JT1无负号，对应的sn的Theta函数表达式中也无负号
		cout<<detail::theta_11(fcomplex(0,0),fcomplex(0,0.5))<<endl;//(7.20051e-017,-4.40904e-033)=JT1(z=0,tau=0.5i)=0
		cout<<detail::theta_1(fcomplex(0.2,0),fcomplex(0.207879576350762,0))<<endl;//(0.235436,0)
		cout<<detail::theta_1(fcomplex(0,0),fcomplex(0.207879576350762,0))<<endl;//(0,0)


		sn(u;k)=JT3(0;tau)*JT1(z;tau)/(JT2(0;tau)*JT4(z;tau))=1.41949548808377*0.369140086660667/
		(0.70446581836561*0.868502943433161)=0.856434209027962
		cn(u;k)=JT4(0;tau)*JT2(z;tau)/(JT2(0;tau)*JT4(z;tau))=0.587974282891712*0.537202659820004/
		(0.70446581836561*0.868502943433161)=0.516256182148607
		dn(u;k)=JT4(0;tau)*JT3(z;tau)/(JT3(0;tau)*JT4(z;tau))=0.587974282891712*1.12545388495798/
		(1.41949548808377*0.868502943433161)=0.516256182148607=0.536760717392963

	*/
	cout<<detail::K(fcomplex(0,1))<<endl;//(1.31103,0)
	double retK=math::K(0.8660254);
	printf("K(e=0.8660254)=%f\n",retK);//K(e=0.8660254)=2.156516
	double retcK=math::cK(0.8660254);
	printf("K'(e=0.8660254)=%f\n",retcK);//K'(e=0.8660254)=1.685750
	cout<<"P(z=0.5,e=0.8660254)="<<math::P(0.5,0.8660254)<<endl;//P(z=0.5,e=0.8660254)=4.19713
	cout<<"P(z=0.5,tau=0.781701i)="<<detail::P(fcomplex(0.5,0),fcomplex(0,0.781701))<<endl;//P(z=0.5,tau=0.781701i)=(7.75093,0)
	cout<<"P(z=0.5,tau=0.781701i,w1=2.156516)="<<detail::P(fcomplex(0.5,0),fcomplex(0,0.781701),fcomplex(2.156516,0))<<endl;//P(z=0.5,tau=0.781701i,w1=2.156516)=(4.19713,-1.0154e-015)
	cout<<"g2(tau=0.781701i,w1=2.156516)="<<detail::g2(fcomplex(0,0.781701),fcomplex(2.156516,0))<<endl;//g2(tau=0.781701i,w1=2.156516)=(17.3333,0)
	cout<<"g3(tau=0.781701i,w1=2.156516)="<<detail::g3(fcomplex(0,0.781701),fcomplex(2.156516,0))<<endl;//g3(tau=0.781701i,w1=2.156516)=(-10.3704,0)
	cout<<"g2(tau=0.781701i,w1=1)="<<detail::g2(fcomplex(0,0.781701),fcomplex(1,0))<<endl;//g2(tau=0.781701i,w1=1)=(374.88,0)
	cout<<"g3(tau=0.781701i,w1=1)="<<detail::g3(fcomplex(0,0.781701),fcomplex(1,0))<<endl;//g3(tau=0.781701i,w1=1)=(-1043.06,0)

   	cout<<"g2(tau=0.859743i,w1=1)="<<math::g2(0.859743,1)<<endl;//g2(tau=0.859743i,w1=1)=
   	cout<<"g3(tau=0.859743i,w1=1)="<<math::g3(0.859743,1)<<endl;//g3(tau=0.859743i,w1=1)=
   	cout<<"g2(tau=0.859743i,w1=2.156516)="<<math::g2(0.859743,2.156516)<<endl;//g2(tau=0.859743i,w1=2.156516)=
   	cout<<"g3(tau=0.859743i,w1=2.156516)="<<math::g3(0.859743,2.156516)<<endl;//g3(tau=0.859743i,w1=2.156516)=

	cout<<detail::P(fcomplex(0.5,0),fcomplex(0,0.859743))<<endl;
	cout<<detail::P(fcomplex(0.231855,0),fcomplex(0,0.859743))<<endl;

	cout<<detail::P(fcomplex(0.5,0),fcomplex(0,0.859743),fcomplex(2.156516,0))<<endl;
	cout<<detail::P(fcomplex(0.231855,0),fcomplex(0,0.859743),fcomplex(2.156516,0))<<endl;

	fcomplex x(1,2.1),y;
   std::cout<<"sin(1,2.1)="<<std::sin(x)<<std::endl;
   //复数求模abs(55.6,68.2)=87.992
   std::cout<<"abs(55.6,68.2)="<<std::abs(fcomplex(55.6,68.2))<<std::endl;
   //求实幂指数(16+81i)^3=(-310832,-469233)
   fcomplex cpxZ(16,81);
   fcomplex cpxPow=std::pow(cpxZ,3);
   std::cout<<"(16+81i)^3="<<cpxPow<<std::endl;
   //复数相乘(9+11i)(56+3i)=(471,643)
   fcomplex cpxZ1(9,11),cpxZ2(56,3);
   std::cout<<"(9+11i)(56+3i)="<<cpxZ1*cpxZ2<<std::endl;
   //复数相除(471+643i)/(9+11i)=(56,3)
   cpxZ1=fcomplex(471,643);
   cpxZ2=fcomplex(9,11);
   std::cout<<"(471+643i)/(9+11i)="<<cpxZ1/cpxZ2<<std::endl;

   detail::Test2();

   fcomplex retqk=detail::q_from_k(fcomplex(0.985171431,0));
   cout<<retqk<<endl;

   cout<<detail::kq(0.207879576350762)<<endl;
   cout<<detail::ckq(0.207879576350762)<<endl;

   cout<<detail::theta_00(fcomplex(0.2,0),fcomplex(0,0.5))<<endl;
   cout<<detail::theta_00(fcomplex(0.2,0.2),fcomplex(0,0.5))<<endl;
   cout<<detail::theta_00(fcomplex(0,0),fcomplex(0,0.5))<<endl;
   cout<<detail::theta_00(fcomplex(3.3416,0),fcomplex(0,0.5))<<endl;
   cout<<detail::theta_00(fcomplex(1.2,0),fcomplex(0,0.5))<<endl;

   cout<<detail::theta_01(fcomplex(0.2,0),fcomplex(0,0.5))<<endl;
   cout<<detail::theta_01(fcomplex(0,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(1.5708,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(1.6708,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(1.7708,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(1.8708,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(1,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(1.1,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(1.2,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(1.3,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(0.5,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(0.6,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(0.7,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_01(fcomplex(0.8,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_3(fcomplex(0.2,0)*M_PI,fcomplex(0.207879576350762,0))<<endl;
   //cout<<detail::theta_3(fcomplex(0.2,0),fcomplex(0.207879576350762,0))<<endl;
   //cout<<detail::theta_3(fcomplex(0,0),fcomplex(0.207879576350762,0))<<endl;
   //cout<<detail::theta_4(fcomplex(0.2,0),fcomplex(0.207879576350762,0))<<endl;
   //cout<<detail::theta_4(fcomplex(0,0),fcomplex(0.207879576350762,0))<<endl;

   //cout<<detail::theta_2(fcomplex(0.2,0)*M_PI,fcomplex(0.207879576350762,0))<<endl;
   //cout<<detail::theta_10(fcomplex(0.2,0)/M_PI,fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_10(fcomplex(0.2,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_10(fcomplex(0,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_2(fcomplex(0.2,0),fcomplex(0.207879576350762,0))<<endl;
   //cout<<detail::theta_2(fcomplex(0,0),fcomplex(0.207879576350762,0))<<endl;

   //cout<<detail::theta_11(fcomplex(0.2,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_11(fcomplex(0,0),fcomplex(0,0.5))<<endl;
   //cout<<detail::theta_1(fcomplex(0.2,0),fcomplex(0.207879576350762,0))<<endl;
   //cout<<detail::theta_1(fcomplex(0,0),fcomplex(0.207879576350762,0))<<endl;

  //fcomplex tau=fcomplex(0,0.859743);
  fcomplex tau=fcomplex(0,0.5);
  fcomplex retJ=detail::KleinInvariantJ(tau,fcomplex(1.0,0));
  cout<<retJ<<endl;//

  cout<<detail::g2(fcomplex(0,2),fcomplex(1,0))<<endl;
  cout<<detail::g3(fcomplex(0,2),fcomplex(1,0))<<endl;

  cout<<detail::g2(fcomplex(0,2),fcomplex(2,0))<<endl;
  cout<<detail::g3(fcomplex(0,2),fcomplex(2,0))<<endl;

	//system("pause");
	return 0;

} 