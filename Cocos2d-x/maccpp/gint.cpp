/*
	自然数集与整数集一一对应：当n为偶数时，对应到n/2； n为奇数时对应到1-(n+1)/2
	0,1,-1,……
	有限多个可数集的笛卡尔积是可数的。
	Z[i]可数：按范数升序和幅角主值升序排列
	0,1,i,-1,-i,1+i,-1+i,-1-i,1-i,……

高斯整數和普通整數相像，也是惟一分解 (Unique Factorization) 的。除去因子的次序、單位 + 1、 - 1 、 + i 、 - i 及相伴元以外的分解是惟一的。在高斯整數的世界中，型如 4k-1 的素數 (如 3、7、11、19、23、......) 仍為素數，但其他的則可進一步分解成其他高斯素數：
2 = (1+i) (1-i) 5 = (2+i) (2-i) 13 = (2+3i) (2-3i) 
17 = (4+i) (4-i) 29 = (5+2i) (5-2i) 37 = (6+i) (6-i) 
現在我們知道在實軸 (Real Axis) 及虛軸 (Imaginary Axis) 上存在無限多個高斯素數，因為虛軸上的高斯素數不過是實軸的高斯素數的相伴元。但在複平面 (Complex Plane) 上別的直線又如何呢？例如所有型如 (1 + ki) 的高斯素數是否均存有無限多個呢？仍是存疑。


某些素数并非高斯素数，如2=(1+i)(1-i)及5=(2+i)(2-i)。
4除余3的素数都是高斯素数，4除余1者则否，因为后者能表示成两个平方数之和：
p=a^2+b^2=(a+bi)(a-bi)
若某个高斯整数的范数是素数，该高斯整数是高斯素数。

A complex number a + bj where a and b are integers is a Gaussian prime if the factors are 1, -1, -a - bj and a + bj only.
The following are Gaussian primes: 1 + j, 1 - j, 1 + 2j, 1 - 2j, 3 and 7.
The Gaussian prime factors of 5 are:
    1 + 2j and 1 - 2j, or
    2 + j and 2 - j, or
    -1 - 2j and -1 + 2j, or
    -2 - j and -2 + j.

求证范数小于100，1/4正平面(0<=θ<π/2)上所有“高斯素数”
1+1I   1+2I   2+1I   3   2+3I   3+2I   1+4I   4+1I   2+5I   5+2I   1+6I   6+1I  
4+5I   5+4I   7   2+7I   7+2I   5+6I   6+5I   3+8I   8+3I   5+8I   8+5I   4+9I   9+4I
高斯素数是指除了单位{1,-1,i,-i}及其自身与单位的乘积，不能被其他高斯整数除尽。
找高斯素数我觉得也不很难，只要得出正平面(0<=θ<π/2)上的高斯素数，然后乘上单位
{-1,i,-i}就能得出其他三个平面上的高斯素数。可以看出高斯素数是关于原点对称的。
*/
#include<iostream>
#include<complex>
#include<cstdlib>
using namespace std;

bool is_prime(long p)
{
	if( p<2 ) return false;
	for(int i=2; i*i<=p; i++)
		if ( p%i==0 )
			return false;
	return true;
} 

bool is_4n_plus_3( long a ) { return a%4 == 3 ; }

bool is_gausian_prime( std::complex<long> z ) // a + bi
{
	const long a = std::abs( z.real() ) ;
	const long b = std::abs( z.imag() ) ;

	if( a == 0 ) return is_prime(b) && is_4n_plus_3(b) ;
	else if( b == 0 ) return is_prime(a) && is_4n_plus_3(a) ;
	else return is_prime( a*a + b*b ) ;
}

struct int_max
{
    int operator()(int x,int y){return x>y?x:y; }
};//operator() 重载了()，(int x,int y)是参数列表

class gint
{
public:
	gint(long a,long b)
	{
		m_a=a;
		m_b=b;
	}
	static bool IsPrime(gint N)
	{
		return is_gausian_prime(complex<long>(N.m_a,N.m_b));
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

int main(int argc, const char * argv[]) {
    if(argc>=3)
    {
        int a=atoi(argv[1]);
        int b=atoi(argv[2]);
        cout<<gint(a,b)<<endl;
    }
    else
    {
#if 1
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
	//cout<<int_max()(3,4)<<endl;
#endif
    }
    //cin.get();
    return 0;
}
