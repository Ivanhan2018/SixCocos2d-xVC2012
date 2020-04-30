//g++ -std=c++11 -o CharacterTable CharacterTable.cpp
#include<iostream>
#include<complex>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
using namespace std;

complex<double> E(int n)
{
	const double pi=atan2((double)0,-1);
    complex<double>  Wn=exp(complex<double>(0,2*pi/n));
	return Wn;
}

string cpx2str(const complex<double> &z)
{
   std::vector<std::pair<complex<double>,string> > r3={ \
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
	return "";
}

void PrintCharacterTable(const vector<vector<complex<double>>> &vv) 
{
 vector<complex<double>>::const_iterator vi;
 vector<vector<complex<double>>>::const_iterator vvi;
 for(vvi=vv.begin(); vvi!=vv.end(); vvi++)
 {
  for(vi=(*vvi).begin(); vi!=(*vvi).end(); vi++)
  {
   cout << cpx2str(*vi)<<" ";
  }
  cout << endl;
 } 
 return;
}

int main()
{
 int n=3;
 const double pi=atan2((double)0,-1);
 complex<double>  Wn=exp(complex<double>(0,2*pi/n));
 vector<vector<complex<double>>> vv(n);
 vector<complex<double>> v(n);

 for(int i=0;i<n;i++)
 { 
  for(int j=0;j<n;j++)
  { 
   v[j]=pow(Wn,i*j);
  }
   vv[i]=v;
 }

 // 1维平凡表示χ_0
 for(int i=0;i<n;i++)
 { 
  v[i]=complex<double>(1,0);
 }
 vv[0]=v;
 // 1维忠实表示χ_1
 for(int i=0;i<n;i++)
 { 
  v[i]=pow(Wn,i);
 }
 vv[1]=v;
 // 1维忠实表示χ_2=χ_1·χ_1
 for(int i=0;i<n;i++)
 { 
  v[i]=v[i]*v[i];
 }
 vv[2]=v;

 PrintCharacterTable(vv);
 return 0;
}
