#include<iostream>
#include<complex>
#include<cstdlib>
using namespace std;

//http://www.metu.edu.tr/~e132713/programs/jacobi.cpp
int Jacobi(int a,int n)
{ 
	int t,j=1; 
	if(a==1) 
		return j; 
	cout<<"a="<<a<<" n="<<n<<endl;
	a%=n; 
	while((a%2)==0)
	{ 
		j*=t;
		a/=2; 
	} 
	//cout<<"a="<<a<<" n="<<n<<endl; 
	if(a!=1)
	{ 
		t=a; 
		a=n; 
		n=t; 
		if(((a%4)==3) && ((n%4)==3)) 
			j*=-1; 
	} 
	return j; 
} 


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

bool is_old_primitive( std::complex<long> z )
{ 
	long a = z.real();
    long b = z.imag();
	return ((b%2==0) && ((a+b-1)%4==0));
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

bool divide(const std::complex<long>& a, const std::complex<long>& b,std::complex<long>& q, std::complex<long>& r)
{
  //long qr = floor((a/b).real() + 0.5);
  //long qi = floor((a/b).imag() + 0.5);
  //q = std::complex<long>(qr,qi);
  q=Div(a,b);
  r = a - q*b;
  bool bret=(r==std::complex<long>(0,0));
  return bret;
}

long Norm(const std::complex<long>& a)
{
	return (a.real()*a.real()+a.imag()*a.imag());
}

std::complex<long> gcd(const std::complex<long>& a, const std::complex<long>& b)
{
	std::complex<long> x = a, y = b;
	//if(abs(x)<abs(y) )
	if(Norm(x)<Norm(y) )
	{
		std::swap(x,y);
	}
	while ( y != std::complex<long>(0,0) ) {
		std::complex<long> q,r;
		bool ret=divide(x,y,q,r);
		x = y;
		y = r;
	}
	return x;
}

std::complex<long> simple_gcd(const std::complex<long>& a, const std::complex<long>& b)
{

  std::complex<long> aa = a, bb = b;

  //if ( abs(aa) < abs(bb) )
  if(Norm(aa)<Norm(bb) )
  {
      std::swap(aa,bb);
   }

  //while ( abs(bb) != 0)
  while(bb != std::complex<long>(0,0))
   {
      std::complex<long> qq, rr;
      bool bret=divide (aa, bb, qq, rr);
      aa = bb;
      bb = rr;
   }

  return aa;
}

std::complex<long> extended_gcd(const std::complex<long>& a, const std::complex<long>& b,std::complex<long>& x, std::complex<long>& y)
{
	std::complex<long> aa = a, bb = b;
	bool swapped = false;
	//if( abs(aa) < abs(bb) )
	if(Norm(aa)<Norm(bb) )
	{
		std::swap(aa,bb);
		swapped = true;
	}
	std::complex<long> xx = 0, lx = 1, yy = 1, ly = 0;
	do
	{
		std::complex<long> qq, rr;
		bool bret=divide (aa, bb, qq, rr);
		aa = bb; bb = rr;

		std::complex<long> tx = lx - qq*xx;
		lx = xx; xx = tx;

		std::complex<long> ty = ly - qq*yy;
		ly = yy; yy = ty;
	}while (bb != std::complex<long>(0,0));

	x = lx;
	y = ly;
	if (swapped)
	{
		std::swap(x,y);
	}

	return aa;
}

int main(void)
{
#if 0
	int nCount3=0;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
		{
			std::complex<long> z(i,j),z1(i,-j),z2(-i,j),z3(-i,-j);
			if(is_gausian_prime(z) && is_old_primitive(z))
			{
                 nCount3++;
				 cout<<"第"<<nCount3<<"个本原奇素数:"<<z<<endl;
			}
			if(j!=0 && is_gausian_prime(z1) && is_old_primitive(z1))
			{
				nCount3++;
				cout<<"第"<<nCount3<<"个本原奇素数:"<<z1<<endl;
			}
			if(i!=0 && is_gausian_prime(z2) && is_old_primitive(z2))
			{
					nCount3++;
					cout<<"第"<<nCount3<<"个本原奇素数:"<<z2<<endl;
			}
			if(j!=0 && is_gausian_prime(z3) && is_old_primitive(z3))
			{
					nCount3++;
					cout<<"第"<<nCount3<<"个本原奇素数:"<<z3<<endl;
			}
		}
#endif

#if 0
	int nCount=0;
	int nCount1=0;
	int nCount2=0;
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
			if(is_old_primitive(z))
			{
			     nCount2++;
				 cout<<"第"<<nCount2<<"个奇本原数:"<<z<<endl;
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
			if(j!=0 && is_old_primitive(z1))
			{
			     nCount2++;
				 cout<<"第"<<nCount2<<"个奇本原数:"<<z1<<endl;
			}
		}
#endif

#if 0
	bool bret1=is_4n_plus_3(-7);
	bool bret2=is_4n_plus_3(-5);

	static std::complex<long> k[4]={std::complex<long>(1,0),std::complex<long>(0,1),std::complex<long>(-1,0),std::complex<long>(0,-1)};
	std::complex<long> evenP(1,1);
	for(int i=0;i<4;i++)
	{
	   std::complex<long> kP=k[i]*evenP;
	   cout<<"第"<<(i+1)<<"个偶素数:"<<kP<<endl;
	}
#endif

#if 1
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
	std::complex<long> q,r;
	bool bret=divide(a,b,q,r);

	{
		std::complex<long> a[]={std::complex<long>(5,0),std::complex<long>(7,5),std::complex<long>(112,1)};
		std::complex<long> b[]={std::complex<long>(2,1),std::complex<long>(18,5),std::complex<long>(-57,79)};
		for(int i=0;i<3;i++)
		{
			//cout<<"abs:"<<abs(a[i])<<","<<abs(b[i])<<endl;
			//cout<<"Norm:"<<Norm(a[i])<<","<<Norm(b[i])<<endl;
			std::complex<long> ret=gcd(a[i],b[i]);
			cout<<"gcd("<<a[i]<<","<<b[i]<<")="<<ret<<endl;
			std::complex<long> ret1=simple_gcd(a[i],b[i]);
			cout<<"simple_gcd("<<a[i]<<","<<b[i]<<")="<<ret1<<endl;
			std::complex<long> x,y;
			std::complex<long> ret2=extended_gcd(a[i],b[i],x,y);
			cout<<"extended_gcd("<<a[i]<<","<<b[i]<<")="<<ret2<<",x="<<x<<",y="<<y<<endl;
		}
	}

	long i1=floor(-2.7+0.5);
	long i2=floor(-2.3+0.5);
	long i3=floor(2.7+0.5);
	long i4=floor(2.3+0.5);
	long i5=floor(2.0+0.5);
	long i6=floor(-2.0+0.5);
	int m=(-4)%4;
	int n=(-7)%3;

#endif

#if 0
	{ 
		int n,a,qr; 
		a=7411; 
		n=9283; 
		if((n%2)==0)
		{ 
			cout<<n<<" is not an odd integer. Can not calculate Jacobi symbol..\n"; 
			return 0; 
		} 
		else
			qr=Jacobi(a,n); 
		cout<<qr<<endl;
		return 0; 
	} 
#endif
	//system("pause");
	return 0;
}