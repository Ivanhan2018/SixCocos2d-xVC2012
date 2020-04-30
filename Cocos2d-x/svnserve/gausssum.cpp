//g++ -std=c++11 -o gausssum gausssum.cpp
// 计算模素数的不同次数的高斯和
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
using namespace std;

#define maxPrimeSize 10//getprime
//#define pi 3.14159265//gauss
const double pi=3.14159265358979323846;//4*atan2((double)1,1);//atan2((double)0,-1)

int Legendre(int t,int p)
{
 if(t%p==0)
  return 0;//t是p的倍数
 int ret=-1;
 for(int i=1;i<p;i++)
 {
  if((i*i-t)%p==0)
  {
   return 1;
  }
 }
 return -1;//t是p的二次非剩余
}

complex<double> E(int p)
{
 complex<double> z=std::exp(complex<double>(0,2*pi/p));
 return z;
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

string cpx2str(const complex<double> &z)
{
   std::vector<std::pair<complex<double>,string> > r3={ \
	   std::make_pair(complex<double>(0,0),"0"), \   
	   std::make_pair(complex<double>(-1,0),"-1"), \   
	   std::make_pair(complex<double>(0,-1),"-i"), \ 
 	   std::make_pair(complex<double>(0,1),"i"), \ 	   
	   std::make_pair(complex<double>(1,0),"1"), \
	   std::make_pair(complex<double>(-0.5,0.866025),"E(3)"), \
	   std::make_pair(complex<double>(-0.5,-0.866025),"E(3)^2") \
   };

	auto func = std::bind([=](std::pair<complex<double>,string> &obj,complex<double> &a)->bool{
		if (abs(obj.first-a)<0.001)return true;
		return false;
	}, std::placeholders::_1, z);

	auto It1 = std::find_if(r3.begin(), r3.end(),func);
	if (It1 != r3.end()) {
		return It1->second;
	}
	string str=numstr(z.real());
	if(str=="")
		str+=numstr(z.imag())+"i";
	else	
	    str+=signstr(z.imag())+numstr(z.imag())+"i";
	return str;
}

/*
定义：令p是一个奇素数，ζ=e^(2pii/p)。则g_a=∑[t=0->p-1](t|p)ζ^(at)叫做二次高斯和，其中(t|p)是勒让德符号。
g_a=(a|p)g_1。
g^2 =((-1)^((p-1)/2)))p。
g_1=sqrt(p)，p≡1(mod4)；
g_1=isqrt(p)，p≡3(mod4)。
高斯和的定义如下：设F_q是阶为q（q是素数方幂）的有限域，χ,ξ分别是F_q上的乘法和加法特征，则称G(χ,ξ)=∑[n∈F_q]χ(n)ξ(n)为属于特征χ,ξ的高斯和。
高斯和的值对许多问题的计算都有重要意义，而确定这个和并不容易。
在χ为二次特征即为勒让德符号时，高斯和可写成如下形式：设p为素数，n跑遍模p的剩余系，则定义二次高斯和为g(χ)=∑[n]χ(n)e^(2pini/p)。
高斯花了四年的时间才最后决定出以上和式的值。
在χ为三次特征时，高斯和可写成如下形式：
设ω=e^(2pii/3),π≡1(3)是Z[ω]中的素元。若N(π)=p是Z中素数，则三次高斯和定义为g(χ)=∑[j=1->p-1]χ(j)e^(2piij/p)。
确定三次高斯和的值变得更加困难，至今仍没有一个通用的确定方法。利用雅可比和可以给出g(χ)三次方的关系式，即g^3(χ)=-pπ。
*/
complex<double> gausssum(int a,int p)
{
 complex<double> z(0,0);
 for(int t=0;t<p;t++)
 {
  complex<double> z1=std::pow(E(p),a*t);
  z+=complex<double>(Legendre(t,p),0)*z1;
 }
 return z;
}

// determines if the input element, n, is a generator mod the prime.
// does this by verifying that the first (p-1)/2 powers of n are not 1
// mod p. as it works, sets each of these residues to 0 in the checkarray.
bool generates(int n, int prime, int *arr)
{
 int res = 1;
 for(int i = 1; i< (prime+1)/2; i++)
 {
  res = (res*n)%prime;
  arr[res] = 0;
  if(res == 1)
  {
   return false;
  }
 }
 return true;
}

// primitive root sieve. cycles through the residues mod the prime,
// calling generates if the flag for the element is set to 1
// (see generates) in checkarray.
int getprimroot(int prime)
{
 int *checkarray = new int[prime];
 for(int i = 0; i< prime; i++)
 {
  checkarray[i] = 1;
 }
 for(int j = 2; j<prime; j++)
 {
  if(checkarray[j] == 1)
  {
   if(generates(j, prime, checkarray))
   {
    delete[] checkarray;
    return j;
   }
  }
 }
 delete[] checkarray;
 return -1;
}

// takes in a prime, the order of the character, the power of the character,
// a primitive root mod the prime and stores the gauss sum in the
// referenced variables real and imag
void gauss(int prime, int order, int power, int root,double & real, double & imag)
{
 real = imag = 0;
 int prodcount=1;
 for(int count = 1; count<prime; count++)
 {
  prodcount*= root;
  prodcount = prodcount%prime;
  real += cos(2 * pi *(double(count) * power / order +
   double(prodcount) / prime));
  imag += sin(2 * pi *(double(count) * power / order +
   double(prodcount) / prime));
 }
}


// first calls getprimroot to find a primitive root mod the prime.
// then calls gauss for all the powers 1 to p-2. this computes the gauss
// sum of the order p-1 character to the power 1, 2, ..., p-2
int getGaussSums(int prime)
{
 int primroot = getprimroot(prime);
 double real, imag;
 cout<<"Prime "<<prime<<" has Gauss sums:" <<endl; // fout to write to file
 for(int k = 1; k < prime-1; k++)
 {
  gauss(prime, prime-1, k, primroot, real, imag);
  cout<< "g(X^" << k << ") = " << real << " + " << imag << " i" <<endl;
  // fout to write to file
 }
 return primroot;
}

//prime sieve that calls getGaussSums on every prime that it finds
void getprime()
{
 int primearray[maxPrimeSize+1];
 for(int i = 0; i<maxPrimeSize+1; i++)
 {
  primearray[i]=1;
 }
 for(int i = 2; i<maxPrimeSize+1; i++)
 {
  if(primearray[i] == 1)
  {
   getGaussSums(i); // pass fout if writing to file
   for(int j = i*i; j<maxPrimeSize+1; j+=i)
   {
    primearray[j] = 0;
   }
  }
 }
}

int main(int argc, char *argv[])
{
	if( argc < 3 )
	{
		cout<<"Usage:  gausssum a p"<<endl;
		return 0;
	}
    int a=atoi(argv[1]);
	int p=atoi(argv[2]);
	complex<double> z=gausssum(a,p);
	cout<<"g_"<<a<<"(p="<<p<<")="<<cpx2str(z)<<endl;
	/*
	for(int i=1;i<=a;i++)
		cout<<i<<"->"<<getprimroot(a)<<endl;
	cout<<getGaussSums(a)<<endl;	
	getprime();
	*/
	return 0;
}	