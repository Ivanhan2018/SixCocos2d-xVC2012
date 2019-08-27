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
	const long a = std::abs( z.real() ) ;
	const long b = std::abs( z.imag() ) ;
	if( a == 0 ) 
		return is_prime(b) && is_4n_plus_3(b) ;
	else if( b == 0 )
		return is_prime(a) && is_4n_plus_3(a) ;
	else
		return is_prime( a*a + b*b ) ;
}

std::complex<long> Div(const std::complex<long> &a,const std::complex<long> &b)
{
	std::complex<float> af(a.real(),a.imag());
	std::complex<float> bf(b.real(),b.imag());
	std::complex<float> cf=af/bf;
	long cr=cf.real()>0?(long)(cf.real()+0.5):(long)(cf.real()-0.5);
	long ci=cf.imag()>0?(long)(cf.imag()+0.5):(long)(cf.imag()-0.5);
	std::complex<long> c(cr,ci);
	return c;
}

int main(void)
{
	int nCount=0;
	int nCount1=0;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
		{
			std::complex<long> z(i,j),z1(i,-j);
			if(is_gausian_prime(z))
			{
                 nCount++;
				 cout<<"第"<<nCount<<"个高斯素数:"<<z<<endl;
			}
			else
			{
				nCount1++;
				cout<<"第"<<nCount1<<"个高斯合数:"<<z<<endl;
			}
			if(j!=0 && is_gausian_prime(z1))
			{
				nCount++;
				cout<<"第"<<nCount<<"个高斯素数:"<<z1<<endl;
			}
			else if(j!=0 && !is_gausian_prime(z1))
			{
					nCount1++;
					cout<<"第"<<nCount1<<"个高斯合数:"<<z1<<endl;
			}
		}

	std::complex<float> af(5,0);
	std::complex<float> bf(2,1);
	std::complex<float> cf=af/bf;

    std::complex<long> a(5,0);
    std::complex<long> b(2,1);
	std::complex<long> c=Div(a,b);//不要写a/b;
	std::complex<long> cb=c*b;
	if(a==cb)
	{
		cout<<b<<"|"<<a<<","<<a<<"="<<b<<"*"<<c<<endl;
	}

	int n=(-7)%3;

	//system("pause");
	return 0;
}