#include"E3.h"
#include<iostream>
using namespace std;

//x^3+x+1=0的一实根为：x = -0.68232781
//2000.10.30星期二,x^3-0.75x+0.125=0的三实根为：sin50°=x=0.76604444、sin10°=x2=0.17364815、-sin50°-sin10°=x3=-0.93969262
int main()
{
 std::pair<float,float> PQ[]={ \
	 make_pair(1,1), \
	 make_pair(-0.75,0.125) \
 };
 const char *szEName[]={"x^3+x+1=0","x^3-0.75x+0.125=0"};
 int n=sizeof(PQ)/sizeof(PQ[0]);
 for(int i=0;i<n;i++)
 {
  E3<float> I(PQ[i].first,PQ[i].second);
  float x=I.xOfE3();
  float x2,x3;
  bool ret=I.x2x3OfE3(x2,x3);
  cout<<"ret="<<ret<<","<<"x="<<x<<","<<"x2="<<x2<<","<<"x3="<<x3<<endl;
 }
 
 {
  //j0.DeltOfEC()=-432
  //j0.jOfEC()=0
  //j1728.DeltOfEC()=64
  //j1728.jOfEC()=1728
  EC3<double> j0(0,-1);
  cout<<"j0.DeltOfEC()="<<j0.DeltOfEC()<<endl;
  cout<<"j0.jOfEC()="<<j0.jOfEC()<<endl;
  EC3<double> j1728(-1,0);//y^2=x^3-x
  cout<<"j1728.DeltOfEC()="<<j1728.DeltOfEC()<<endl;
  cout<<"j1728.jOfEC()="<<j1728.jOfEC()<<endl;
 }
 
 {
  //j0.DeltOfEC()=-432
  //j0.jOfEC()=-0
  //j1728.DeltOfEC()=64
  //j1728.jOfEC()=1728
  EC1<double> j0(0,0,0,0,-1);
  cout<<"j0.DeltOfEC()="<<j0.DeltOfEC()<<endl;
  cout<<"j0.jOfEC()="<<j0.jOfEC()<<endl;
  EC1<double> j1728(0,0,0,-1,0);//y^2=x^3-x
  cout<<"j1728.DeltOfEC()="<<j1728.DeltOfEC()<<endl;
  cout<<"j1728.jOfEC()="<<j1728.jOfEC()<<endl;
  //jc.DeltOfEC()=-433
  //jc.jOfEC()=-0.00230947
  //jc2.DeltOfEC()=-3.08659e-009
  //jc2.jOfEC()=-0.00230947
  //j(c=1.3365e-006)=-0.00230947
  EC1<double> jc(-1,0,0,0,1);//y^2-xy=x^3+1
  cout<<"jc.DeltOfEC()="<<jc.DeltOfEC()<<endl;
  cout<<"jc.jOfEC()="<<jc.jOfEC()<<endl;
  double j=-0.00230947;//y^2=x^3-3cx+2c,j=1728*c/(c-1)
  double c=j/(j-1728);
  EC1<double> jc2(0,0,0,-3*c,2*c);
  cout<<"jc2.DeltOfEC()="<<jc2.DeltOfEC()<<endl;
  cout<<"jc2.jOfEC()="<<jc2.jOfEC()<<endl;
  cout<<"j(c="<<c<<")="<<1728*c/(c-1)<<endl;
 } 
 
 return 0;
}