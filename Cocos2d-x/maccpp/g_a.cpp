#include<iostream>
#include<complex>
using namespace std;

int Legendre(int t,int p)
{
	if(t%p==0)
		return 0;//t��p�ı���
	int ret=-1;
	for(int i=1;i<p;i++)
	{
		if((i*i-t)%p==0)
		{
			return 1;
		}
	}
	return -1;//t��p�Ķ��η�ʣ��
}

complex<double> Zeta(int p)
{
	const double pi=3.14159265358979323846;//4*atan2((double)1,1);//
	complex<double> z=std::exp(complex<double>(0,2*pi/p));
	return z;
}

complex<double> gauss(int a,int p)
{
	complex<double> z(0,0);
	for(int t=0;t<p;t++)
	{
		complex<double> z1=std::pow(Zeta(p),a*t);
		z+=complex<double>(Legendre(t,p),0)*z1;
	}
	return z;
}

int main(int argc, const char * argv[]) {
    if(argc>=3)
    {
        int a=atoi(argv[1]);
        int p=atoi(argv[2]);
        cout<<"gauss(a="<<a<<",p="<<p<<")="<<gauss(a,p)<<endl;
    }
    else
    {
#if 1
 //   printf("(13/17)=%d\n",Legendre(13,17));
	//printf("(5/17)=%d\n",Legendre(5,17));

	//cout<<"��_3="<<Zeta(3)<<endl;
	//cout<<"��_5="<<Zeta(5)<<endl;
	int primes[12]={2,3,5,7,11,13,17,19,23,29,31,37};
	for(int i=0;i<12;i++)
	{
		int p=primes[i];
                for(int a=0;a<p;a++)
		{
			cout<<"gauss(a="<<a<<",p="<<p<<")="<<gauss(a,p)<<endl;
		}
	}
#endif
    }
#ifdef _MSC_VER
    system("pause");
#endif
    return 0;
}