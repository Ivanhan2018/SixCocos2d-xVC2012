//基于标准复数库的扩展
#include<iostream>
#include<complex>
using namespace std;

//Declare Function CAbs Lib "VBCOMPLEX.DLL" (cpxZ As Complex) As Double
//Declare Function CCos Lib "VBCOMPLEX.DLL" (cpxZ As Complex) As Complex
//Declare Function CCPow Lib "VBCOMPLEX.DLL" (cpxZ As Complex, cpxN As Complex, n As Integer) As Complex
//Declare Function CDiv Lib "VBCOMPLEX.DLL" (cpxZ1 As Complex, cpxZ2 As Complex) As Complex
//Declare Function CLn Lib "VBCOMPLEX.DLL" (cpxZ As Complex) As Complex
//Declare Function CMul Lib "VBCOMPLEX.DLL" (cpxZ1 As Complex, cpxZ2 As Complex) As Complex
//Declare Function CPow Lib "VBCOMPLEX.DLL" (cpxZ As Complex, w As Double) As Complex
//Declare Function CRoot Lib "VBCOMPLEX.DLL" (cpxZ As Complex, n As Integer, cpxZR() As Complex) As Integer
//Declare Function CSin Lib "VBCOMPLEX.DLL" (cpxZ As Complex) As Complex
//Declare Function CTan Lib "VBCOMPLEX.DLL" (cpxZ As Complex) As Complex

const int PI = 3.14159265358979;
//模板函数，复数乘法
template<typename T>
complex<T>&	CMul(const complex<T>& cpxZ1,const complex<T>& cpxZ2)
{
	return cpxZ1*cpxZ2;
}

//模板函数，复数的N次幂
template<typename T>
complex<T>&	CPowN(const complex<T>& cpxZ1,int N)
{
	return pow(cpxZ1,N);
}

//模板函数，复数除法
template<typename T>
complex<T>&	CDiv(const complex<T>& cpxZ1,const complex<T>& cpxZ2)
{
	return cpxZ1/cpxZ2;
}

//模板函数，复数求模
template<typename T>
T&	CAbs(const complex<T>& cpxZ)
{
	return abs(cpxZ);
}

//模板函数，复自然对数（多值函数）
template<typename T>
complex<T>&	CLn(const complex<T>& cpxZ)
{
	return log(cpxZ);
}

//模板函数，复平方根（多值函数）
template<typename T>
complex<T>&	CSqrt(const complex<T>& cpxZ)
{
	return sqrt(cpxZ);
}

//以下三个圆积分在C++标准库中是没有对应的函数的
//模板函数，复反双曲正切（多值函数）
template<typename T>
complex<T>&	atanh(const complex<T>& cpxZ)
{
	return CLn(CDiv(1+cpxZ,1-cpxZ))/2;
}

//模板函数，复反双曲正弦（多值函数）
template<typename T>
complex<T>&	asinh(const complex<T>& cpxZ)
{
	return CLn(cpxZ+CSqrt(cpxZ*cpxZ+1));
}

//模板函数，复反双曲余弦（多值函数）
template<typename T>
complex<T>&	acosh(const complex<T>& cpxZ)
{
	return CLn(cpxZ+CSqrt(cpxZ*cpxZ-1));
}

int main()
{
   complex<double>  xx,yy(1,2.718);
   xx = log(yy/complex<double>(3,0));
   cout << complex<double>(1,0)+xx<< endl;//(0.96476,1.21825)
   cout << "log(3,2)= " << log(complex<double>(3,2))<< endl;//log(3,2)= (1.28247,0.588003)

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
   y=x+1.0;
   cout << "\ny = " << y << endl;
   // if (x < y) not allowed - no standard definition
   //   cout << "x less than y" << endl;
   //system("pause");
   return 0;
}
