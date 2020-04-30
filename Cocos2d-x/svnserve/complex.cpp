#ifdef USE_STL
#include <complex>
#else
    
#endif
#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;

#ifndef USE_STL

// 模板类友元函数的前置声明，<>的作用是告诉编译器不是普通函数的声明，是友元函数的声明
template<class T> class complex;
template<class T> ostream& operator<<(ostream& os,const complex<T>& c);
//template<class T> complex<T> operator/(complex<T> &, T);
template<class T> complex<T> div(T r, complex<T> & b);
template<class T> complex<T> cos(complex<T> &);
template<class T> complex<T> sin(complex<T> &); 	 
template<class T> T real(complex<T> &);   // the real part
template<class T> T imag(complex<T> &);   // the imaginary part
template<class T> complex<T> conj(complex<T> &);  // the complex conjugate
template<class T> T abs(complex<T> &); //求模	
template<class T> complex<T> log(complex<T> &);
template<class T> complex<T> tan(complex<T> &);
template<class T> complex<T> exp(complex<T> &);
template<class T> complex<T> pow(complex<T> & __base, T __expon);
template<class T> complex<T> pow(complex<T> & cpxz,complex<T> & cpxn,int n);
template<class T> complex<T> pow(complex<T> & cpxz,complex<T> & cpxn);
template<class T> T norm(complex<T> &);   // the square of the magnitude
template<class T> T arg(complex<T> &);    // the angle in the plane
template<class T> complex<T> sqrt(complex<T> &);
template<class T> complex<T> atan(complex<T> &);

template<class T>
class complex
{
private:
	T re;
	T im;
public:
	complex(){re=0.0f;im=0.0f;}; //缺省构造函数
	complex(T r, T i){re=r;im=i;}; //顺便初始化值的构造函数
	complex(T r){re=r;im=0;}; //顺便初始化值的构造函数	
	~complex(){};
	complex operator +(complex<T> x); //计算A+B
	complex operator -(complex<T> x); //计算A-B	
	complex operator *(complex<T> x); //计算A*B
	complex operator /(complex<T> x); //计算A/B	
	complex operator ++(); //计算++A
	complex operator --(); //计算A-
	complex operator =(T x); //把一个double赋给一个complex时
    T real(){return re;};   // the re part
    T imag(){return im;};   // the imaginary part	
	void print(); //输出复数
    // friend complex acos(complex &); 
    // friend complex asin(complex &);
    friend complex<T> atan<>(complex<T> &);
    friend complex<T> cos<>(complex<T> &);
    // friend complex cosh(complex &);
    friend complex<T> exp<>(complex<T> &);
    friend complex<T> log<>(complex<T> &);
    // friend complex log10(complex &);
    friend complex<T> pow<>(complex<T> & __base, T __expon);
    // friend complex pow(double __base, complex & __expon);
	friend complex<T> pow<>(complex<T> & cpxz,complex<T> & cpxn,int n);
	friend complex<T> pow<>(complex<T> & cpxz,complex<T> & cpxn);	
    friend complex<T> sin<>(complex<T> &); 
    // friend complex sinh(complex &);
    friend complex<T> sqrt<>(complex<T> &);
    friend complex<T> tan<>(complex<T> &); 
    // friend complex tanh(complex &); 	
    // Binary Operator Functions
    // friend complex operator+(complex &, complex &);
    // friend complex operator+(double, complex &);
    // friend complex operator+(complex &, double);
    // friend complex operator-(complex &, complex &);
    // friend complex operator-(double, complex &);
    // friend complex operator-(complex &, double);
    // friend complex operator*(complex &, complex &);
    // friend complex operator*(complex &, double);
    // friend complex operator*(double, complex &);
    // friend complex operator/(complex &, complex &);//除法
    friend complex<T> operator/(complex<T> &, T);
    // friend int operator==(complex &, complex &);
    // friend int operator!=(complex &, complex &);
    // complex & operator+=(complex &);
    // complex & operator+=(double);
    // complex & operator-=(complex &);
    // complex & operator-=(double);
    // complex & operator*=(complex &);
    // complex & operator*=(double);
    // complex & operator/=(complex &);
    // complex & operator/=(double);
    // complex operator+();
    // complex operator-();
  // complex manipulations
    friend complex<T> conj<>(complex<T> &);  // the complex conjugate
    friend T norm<>(complex<T> &);   // the square of the magnitude
    friend T arg<>(complex<T> &);    // the angle in the plane
    // // Create a complex object given polar coordinates
    // friend complex polar(double __mag, double __angle=0);

    // // Overloaded ANSI C math functions
    friend T abs<>(complex<T> &); //求模	
	friend ostream& operator<<<>(ostream& os,const complex<T>& c);
};

template<class T>
ostream& operator<<(ostream& os,const complex<T>& c)
{
	os<<"("<<c.re<<","<<c.im<<")";
	return os;
}

template<class T>
T real(complex<T> &a)
{
	return a.real();
}

template<class T>
T imag(complex<T> &a)
{
	return a.imag();
}

template<class T>
complex<T> conj(complex<T> &a)
{
	complex<T> c;
	c.re=a.re;
	c.im=-a.im;
	return c;
}

template<class T>
T arg(complex<T> &a)
{
	T c=atan2(a.im,a.re);
	return c;
}

template<class T>
T norm(complex<T> &a)
{
	T c=a.re*a.re+a.im*a.im;
	return c;
}

template<class T>
T abs(complex<T> &a)
{
	T c=sqrt(a.re*a.re+a.im*a.im);
	return c;
}

template<class T>
void oclog(T x,T y,T *u,T *v)
{ 
	T p;
	p=log(sqrt(x*x+y*y));
	*u=p;
	*v=atan2(y,x);
	return;
}

template<class T>
complex<T> log(complex<T> &a)
{
	complex<T> c;
	oclog(a.re,a.im,&c.re,&c.im);
	return c;
}

template<class T>
void ocexp(T x,T y,T *u,T *v)
{ 
	T p;
	p=exp(x);
	*u=p*cos(y);
	*v=p*sin(y);
	return;
}

template<class T>
complex<T> exp(complex<T> &a)
{
	complex<T> c;
	ocexp(a.re,a.im,&c.re,&c.im);
	return c;
}

template<class T>
complex<T> pow(complex<T> & pz, T w)
{
	complex<T> c;
	T r,q;
	q=atan2(pz.im,pz.re);
	r=sqrt((pz.re)*(pz.re)+(pz.im)*(pz.im));
	if(r+1.0!=1.0)
	{
		r=w*log(r);
		r=exp(r);
	}
	c.re=r*cos(w*q);
	c.im=r*sin(w*q);
	return c;
}

template <class T>
complex<T> pow(complex<T> & cpxz,complex<T> & cpxn,int n)
{
	static const double pi=3.14159265358979;
	T x,y,ar,s;	
	if(cpxz.real() == 0)
	{
		if(cpxz.imag() == 0)
		{
			x = 0;
			y = 0;
			return complex<T>(x,y);
		}
		s = 1.5707963268 * (abs(cpxz.imag()) / cpxz.imag() + 4 * n);
	}
	else
	{
		s = 2 * pi * n + atan(cpxz.imag() / cpxz.real());
		if(cpxz.real() < 0)
		{
			if(cpxz.imag() > 0){
				s = s + pi;
			}
			else
			{
				s = s - pi;
			}
		}
	}
	T r = 0.5 * log(norm(cpxz));
	T v = cpxn.imag() * r + cpxn.real() * s;
	T u = exp(cpxn.real() * r - cpxn.imag() * s);
	x = u * cos(v);
	y = u * sin(v);
	return complex<T>(x,y);
}

template <class T>
complex<T> pow(complex<T> & cpxz,complex<T> & cpxn)
{
	return pow(cpxz,cpxn,0);
}

template<class T>
complex<T> sin(complex<T> &a)
{
	complex<T> c;
	c.re=sin(a.re)*(exp(a.im)+exp(-a.im))/2.0;
	c.im=cos(a.re)*(exp(a.im)-exp(-a.im))/2.0;
	return c;
}

template<class T>
complex<T> cos(complex<T> &a)
{
	complex<T> c;
	c.re=cos(a.re)*(exp(a.im)+exp(-a.im))/2.0;
	c.im=-sin(a.re)*(exp(a.im)-exp(-a.im))/2.0;
	return c;
}

template<class T>
complex<T> tan(complex<T> &a)
{
	complex<T> c=sin(a)/cos(a);
	return c;
}

// 复数加法
template<class T>
complex<T> complex<T>::operator +(complex<T> x)
{
    complex<T> c;
    c.re=re+x.re;
    c.im=im+x.im;
    return c;
}

// 复数减法
template<class T>
complex<T> complex<T>::operator -(complex<T> x)
{
    complex<T> c;
    c.re=re-x.re;
    c.im=im-x.im;
    return c;
}

// 复数乘法
template<class T>
complex<T> complex<T>::operator *(complex<T> x)
{
    complex<T> c;
	c.re=re*x.re-im*x.im;
	c.im=re*x.im+im*x.re;
	return c;
}

template<class T>
void ocdiv(T a,T b,T c,T d,T *e,T *f)
{ 
	T p,q,s,w;
	p=a*c;
	q=-b*d;
	s=(a+b)*(c-d);
	w=c*c+d*d;
	if(w+1.0==1.0) 
	{ 
		*e=1.0e+35*a/fabs(a);
		*f=1.0e+35*b/fabs(b);
	}
	else
	{ 
		*e=(p-q)/w; *f=(s-p-q)/w; 
	}
	return;
}

// 复数除法
template<class T>
complex<T> complex<T>::operator /(complex<T> x)
{
    complex<T> c;
	ocdiv(re,im,x.re,x.im,&(c.re),&(c.im));
	return c;
}

template<class T>
complex<T> operator/(complex<T> & __z1, T __re_val2)
{
    return complex<T>(__z1.re/__re_val2, __z1.im/__re_val2);
}

template<class T>
complex<T> div(T r,complex<T> & x)
{
    complex<T> c=complex<T>(r)/x;
	return c;
}

template<class T>
complex<T> complex<T>::operator ++()
{
	complex c;
	++re;
	c.re=re;
	c.im=im;
	return c;
}

template<class T>
complex<T> complex<T>::operator --()
{
	complex c;
	c.re=re;
	c.im=im;
	re--;
	return c;
}

template<class T>
complex<T> complex<T>::operator =(T x)
{
	 re=x;
	 return *this; //按照C++的惯例，返回*this，以便实现链式表达式
}

template<class T>
void complex<T>::print()
{
    cout<<re<<"+"<<im<<"i"<<endl;
}

template<class T>
void ontrt(T x,T y,int n,T *u,T *v)
{ 
	int k;
	T r,q,t;
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

template<class T>
complex<T> sqrt(complex<T> &a)
{
	complex<T> c;
	T u[2];
	T v[2];
	ontrt(a.re,a.im,2,&u[0],&v[0]);
	c.re=u[0];
	c.im=v[0];
	return c;
}

#endif

#ifdef USE_STL
//复反正切atan(x+yi)=-0.5*i*ln((1+iz)/(1-iz))=0.5*i*ln((1-iz)/(1+iz))
template<class T>
complex<T> atan(complex<T> &a)
{
	T re=0.5 * atan2(2 * a.real(), 1 - a.imag()*a.imag() - a.real()*a.real());
	T im=-0.5 * log(sqrt((a.real()*a.real()+a.imag()*a.imag() - 1)*(a.real()*a.real()+a.imag()*a.imag() - 1) + 4 * a.real()*a.real()) / ((a.imag() + 1) *(a.imag() + 1) + a.real()*a.real()));
	return complex<T>(re,im);
}	
#else
//复反正切atan(x+yi)=-0.5*i*ln((1+iz)/(1-iz))=0.5*i*ln((1-iz)/(1+iz))
template<class T>
complex<T> atan(complex<T> &a)
{
	complex<T> c;
	c.re=0.5 * atan2(2 * a.re, 1 - a.im*a.im - a.re*a.re);
	c.im=-0.5 * log(sqrt((a.re*a.re+a.im*a.im - 1)*(a.re*a.re+a.im*a.im - 1) + 4 * a.re*a.re) / ((a.im + 1) *(a.im + 1) + a.re*a.re));
	return c;
}	
#endif

/* Define complex double data type */
typedef complex<double> dcomp; 

void test1()
{
	complex<double> a(1,2);
	complex<double> b(4,5);
	cout << "a+b = " << a+b << endl;
	cout << "a-b = " << a-b << endl;
	cout << "a*b = " << a*b << endl;
	cout << "a/b = " << a/b << endl;
	
	complex<double> xx,yy(1,2.718);
	complex<double> zz=complex<double>(3,0);
	complex<double> ww=yy/zz;
	xx = log(ww);
	//cout << complex<double>(1,0)+xx<< endl;//(0.96476,1.21825)
	complex<double> aa=complex<double>(3,2);
	cout << "log(3,2)= " << log(aa)<< endl;//log(3,2)= (1.28247,0.588003)
	complex<double> x(1,2.1), y;
	cout << "sin(1,2.1)= " << sin(x) << endl;
	cout << "cos(1,2.1)= " << cos(x) << endl;
	cout << "exp(1,2.1)= " << exp(x).real() << "+" << exp(x).imag() << "i" << endl;
	cout << "norm(1,2.1)= " << norm(x) << endl;
	cout << "arg(1,2.1)= " << arg(x) << endl;
	cout << "conj(1,2.1)= " << conj(x) << endl;
	cout << "abs(1,2.1)= " << abs(x) << endl;
	y=sin(x)/cos(x);
	cout << "tan(1,2.1)= " << y.real() << "+" << y.imag() << "i" << endl;
	cout << "tan(1,2.1)= " << tan(x) << endl;
	cout << "atan"<<y<<"= " << atan(y) << endl;   
	y=x+1.0;
	cout << "y = " << y << endl;
	// if (x < y) not allowed - no standard definition
	//   cout << "x less than y" << endl;
#ifdef USE_STL
#endif   
}

void test2()
{
  dcomp i, a, b, c, d, e, p, q, r; // Declare complex double variables
  double x, y;

  /* Set complex double variable equal to complex double constant */
  i = dcomp (0., 1.); 
  cout<<"i="<<i<<endl;

  /* Test arithmetic operations with complex double variables */
  a = i * i;
#ifdef USE_STL
  b = 1. / i;  
#else
  b = div(1.,i); 	
#endif
  cout<<"a="<<a<<endl;
  cout<<"b="<<b<<endl;
  
  dcomp z=dcomp(5,7);
  dcomp w=sin(z);
  cout<<"z="<<z<<endl;  
  cout<<"w=sin(z)="<<w<<endl;    

  z=dcomp(0.75,0.25);
  w=cos(z);
  cout<<"z="<<z<<endl;  
  cout<<"w=cos(z)="<<w<<endl; 
  
  z=dcomp(0.25,0.25);
  w=tan(z);
  cout<<"z="<<z<<endl;  
  cout<<"w=tan(z)="<<w<<endl;  
  
  /* Test complex operations */
  p = conj(i);
  q = real(i);
  r = imag(i);
  cout<<"p=conj(i)="<<p<<endl; 
  cout<<"q=real(i)="<<q<<endl;    
  cout<<"r=imag(i)="<<r<<endl; 

  //初等多值函数
  z=dcomp(3,2);
  w=log(z);
  cout<<"z="<<z<<endl;  
  cout<<"w=ln(z)="<<w<<endl;  

  z=dcomp(55.6,68.2);
  double zabs=abs(z);
  cout<<"z="<<z<<endl;  
  cout<<"zabs=abs(z)="<<zabs<<endl; 
  
  z=dcomp(16,81);
  double r1=4;
  w=pow(z,r1);
  cout<<"z="<<z<<endl;  
  cout<<"r1="<<r1<<endl; 
  cout<<"w=z^r1="<<w<<endl;  

   /* Test mathematical functions using complex double variables */
  c = sqrt(i);//初等多值函数
  d = sin(i);
  e = pow(i, 0.25);//初等多值函数
  cout<<"c=sqrt(i)="<<c<<endl;
  cout<<"d=sin(i)="<<d<<endl; 
  cout<<"e=i^0.25="<<e<<endl;   

  z=dcomp(1,1);
  dcomp z1=dcomp(1,1);
  w=pow(z,z1);	
  cout<<"z="<<z<<endl;  
  cout<<"z1="<<z1<<endl; 
  cout<<"w=z^z1="<<w<<endl;   
}

int main()
{
  test1();
  test2();
  return 0;
}
