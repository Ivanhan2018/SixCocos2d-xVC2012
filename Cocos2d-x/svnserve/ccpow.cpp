//g++ -std=c++11 -w -o ccpow ccpow.cpp
#include<complex>//复数类
#include<iostream>
using namespace std;

// C++自定义复数类:对complex的继承与扩展
// 模板类友元函数的前置声明，<>的作用是告诉编译器不是普通函数的声明，是友元函数的声明
template<class T> class mycomplex;
template<class T> ostream& operator<<(ostream& os,const mycomplex<T>& c);

template <class T>
class mycomplex : public complex<T>
{
public:
	mycomplex():complex<T>(){};
	mycomplex(T r):complex<T>(r){};	
	mycomplex(T r, T i):complex<T>(r,i){};
	mycomplex operator +(mycomplex<T> x); //计算A+B
	mycomplex operator -(mycomplex<T> x); //计算A-B	
	mycomplex operator *(mycomplex<T> x); //计算A*B
	mycomplex operator /(mycomplex<T> x); //计算A/B	   
	mycomplex<T> operator ++(); //计算++A,先加1后赋值
	mycomplex<T> operator --(int); //计算A--,先赋值后减1
	friend ostream& operator<<<>(ostream& os,const mycomplex<T>& c);  
};

// 复数加法
template<class T>
mycomplex<T> mycomplex<T>::operator +(mycomplex<T> x)
{
    complex<T> t1((*this).real(),(*this).imag());
    complex<T> x1(x.real(),x.imag());	
    complex<T> ret1=t1+x1;
	*this=mycomplex<T>(ret1.real(),ret1.imag());
    return *this;
}

template<class T>
ostream& operator<<(ostream& os,const mycomplex<T>& c)
{
	cout << c.real() <<(imag(c)>=0?"+":"")<<c.imag()<<"i";
	return os;
}

template <class T>
mycomplex<T>  mycomplex<T>::operator ++()
{
	*this=mycomplex<T>((*this).real()+1,(*this).imag());
    return (*this);
}

template <class T>
mycomplex<T>  mycomplex<T>::operator --(int)
{
	*this=mycomplex<T>((*this).real()-1,(*this).imag());
    return (*this);
}

typedef mycomplex<double> dcomplex; 

void test1()
{
	dcomplex x(1,2.1), y;
	//y=x;
	cout<<"x="<<x<< endl;
	y = x + dcomplex(1.0,0);
	cout<<"y="<<y<< endl;

    dcomplex a(1,2);
    dcomplex b(4,5);
    dcomplex e=++b;// 先加1后赋值
    cout<<"a="<<a<< endl;
	cout<<"b="<<b<< endl;
    cout<<"e="<<e<< endl;
    dcomplex g=e--;// 先赋值后减1
    cout<<"e="<<e<< endl;
    cout<<"g="<<e<< endl;
    dcomplex c=a+b;
    cout<<"c="<<c<< endl;	
    dcomplex d=++a;
    cout<<"d="<<d<< endl;	
	dcomplex f1=0.234; //要写相应的拷贝构造函数
    dcomplex f;
    f=a=0.234; // 链式表达式			
    cout<<"a="<<a<< endl;
    cout<<"f="<<f<< endl;	
}

template <class T>
complex<T> gamma(complex<T> z)
{
	static const int g=7;
	static const T pi =3.1415926535897932384626433832795028841972 ;
	static const T p[g+2] = {0.99999999999980993, 676.5203681218851,-1259.1392167224028, 771.32342877765313, -176.61502916214059,12.507343278686905, -0.13857109526572012, 9.9843695780195716e-6,1.5056327351493116e-7};

	if ( real(z)<0.5 ) {
		return pi / (sin(pi*z)*gamma(1.0-z));
	}
	z -= 1.0;
	complex<T> x=p[0];
	for (int i=1; i<g+2; i++) {
		x += p[i]/(z+complex<T>(i,0));
	}
	complex<T>t = z + (g + 0.5);
	return sqrt(2*pi) * pow(t,z+0.5) * exp(-t) * x;
}

template <class T>
complex<T> ccpow(complex<T> cpxz,complex<T> cpxn,int n)
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

// float、double都可以
void test2()
{
/*
	cpow和ccpow要考虑多值单复变的情况
	复数1+2j的2+3j次幂为：-1.51326724227228E-02+-.179867483913335j
	复数1+2j的2.1次幂为：-3.71047849586439+3.94940791878079j
	复数1+2j的2.1+0j次幂为：-3.71047849586439+3.94940791878079j	
*/
	complex<float> x(1,2),y(2,3);
    //求复幂指数(1,2)^(2,3)=(-0.0151327,-0.179867)
	complex<float> xy=std::pow(x,y);
	std::cout<<x<<"^"<<y<<"="<<xy<<std::endl;	
	xy=ccpow(x,y,0);
	std::cout<<x<<"^"<<y<<"="<<xy<<std::endl;		
	std::cout<<"sin(1,2)="<<std::sin(x)<<std::endl;
	cout << "arg(1,2)= " << arg(x) << endl;
	cout << "abs(1,2)= " << abs(x) << endl;  
	//复数求模abs(55.6,68.2)=87.992
	std::cout<<"abs(55.6,68.2)="<<std::abs(complex<float>(55.6,68.2))<<std::endl;
	//复数相乘(9+11i)(56+3i)=(471,643)
	complex<float> cpxZ1(9,11),cpxZ2(56,3);
	std::cout<<"(9+11i)(56+3i)="<<cpxZ1*cpxZ2<<std::endl;
	//复数相除(471+643i)/(9+11i)=(56,3)
	cpxZ1=complex<float>(471,643);
	cpxZ2=complex<float>(9,11);
	std::cout<<"(471+643i)/(9+11i)="<<cpxZ1/cpxZ2<<std::endl;
	std::cout<<"log(-1.37231,2.34645)="<<log(complex<float>(-1.37231,2.34645))<<std::endl;		
	std::cout<<"exp(1.28247,0.588003)="<<exp(complex<float>(1.28247,0.588003))<<std::endl;		
	std::cout<<"asin(3.48732,2.17302)="<<acos(complex<float>(3.48732,2.17302))<<std::endl;	
	std::cout<<"acos(2.23918,-3.38428)="<<asin(complex<float>(2.23918,-3.38428))<<std::endl;
	std::cout<<"atan(0.0276093,1.01218)="<<atan(complex<float>(0.0276093,1.01218))<<std::endl;	
	float r=2.32594;
	float t=1.12638;
	std::cout<<"re^(it)="<<complex<float>(r*cos(t),r*sin(t))<<"="<<r*exp(complex<float>(0,t))<<std::endl;		
 }

int main()
{
    int f37=(int)(-3.7);
    int f42=(int)(-4.2);
    int z42=(int)(4.2);
    int z37=(int)(3.7);	
	cout<<"f37="<<f37<<endl;
	cout<<"f42="<<f42<<endl;
	cout<<"z37="<<z37<<endl;
	cout<<"z42="<<z42<<endl;	
	
	test2();
	// float不可以、double都可以
	//auto z=complex<float>(5,0);
	auto z=complex<double>(5,0);
	cout << "Γ("<<z<<")="<<gamma(z)<< endl; // should be 4!
	
	return 0;
}
