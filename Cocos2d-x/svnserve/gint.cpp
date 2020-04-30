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

bool is_4n_plus_3( long a )
{ 
	return a%4 == 3 ;
}

bool is_gausian_prime( std::complex<long> z ) // a + bi
{
 const long a = std::abs(z.real());
 const long b = std::abs(z.imag());
 if(a==0) 
	 return is_prime(b) && is_4n_plus_3(b);
 else if(b==0) 
	 return is_prime(a) && is_4n_plus_3(a);
 else 
	 return is_prime(a*a+b*b);
}

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

int main(int argc, char *argv[])
{
	if( argc < 3 )
	{
		cout<<"Usage:  gint arg1 arg2"<<endl;
		return 0;
	}
    int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	cout<<gint(a,b)<<endl;
	return 0;
}	