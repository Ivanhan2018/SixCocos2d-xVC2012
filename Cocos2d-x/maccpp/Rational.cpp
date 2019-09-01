//用C++编写的有理数类
#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
#include <stdio.h>
#include <tchar.h>
#include<iostream>
using namespace std;
//一、头文件函数定义：

//Rational.h

//#ifndef RATIONAl_CLASS
//#define RATIONAl_CLASS

class Rational
{
private:
 int P,Q;
 void Standardize();                //将有理数化为标准形式
 int gcd (int m,int n);             //求两个数的最大公约数
public:
 Rational (int p=0, int q=1);       //构造有理数分数，分子默认为0，分母默认为1
 Rational (Rational &r);            //拷贝构造函数
 Rational (double ra);              //构造函数，将实数转换为标准形式的有理数

 virtual ~Rational (void);          //虚析构函数

 void Reduce ();                    //将分数化为最简形式

 int GetNumerator();                //取分数的分子
 int GetDenominator();              //取分数的分母

 Rational& operator= (Rational& r); //将一个有理数对象赋值给另一个对象
 Rational& operator= (double ra);   //将一个实数赋值给一个有理数对象
 Rational operator- ();            //将一个有理数取反
 friend double Float(Rational &r);  //强制转换一个有理数对象为一个实数

 //以下为两个有理数对象、一个有理数对象和一个实数、一个实数和一个有理数对象
 //之间的关系运算符的重载
 int operator== (Rational& r) const;
 int operator== (double ra) const;
 friend int operator== (double ra, Rational& r);
 
 int operator!= (Rational& r) const;
 int operator!= (double ra) const;
 friend int operator!= (double ra, Rational& r);
 
 int operator< (Rational& r) const;
 int operator< (double ra) const;
 friend int operator< (double ra, Rational& r);
 
 int operator<= (Rational& r) const;
 int operator<= (double ra) const;
 friend int operator<= (double ra, Rational& r);

 int operator> (Rational& r) const;
 int operator> (double ra) const;
 friend int operator> (double ra, Rational& r);
 
 int operator>= (Rational& r) const;
 int operator>= (double ra) const;
 friend int operator>= (double ra, Rational& r);

 //以下两个有理数对象、一个有理数对象和一个实数
 //之间的普通四则运算的重载
 Rational operator+ (Rational& r) const;  
 Rational operator+ (double ra) const;
 void operator+= (Rational& r);
 void operator+= (double ra);

 Rational operator- (Rational& r) const;  
 Rational operator- (double ra) const;
 void operator-= (Rational& r);
 void operator-= (double ra);

 Rational operator* (Rational& r) const;
 Rational operator* (double ra) const;
 void operator*= (Rational& r);
 void operator*= (double ra);

 Rational operator/ (Rational& r) const;
 Rational operator/ (double ra) const;
 void operator/= (Rational& r);
 void operator/= (double ra);

 //输入输出流的重载，输出为最简形式
 friend ostream &operator<<(ostream &output,Rational &obj);
    friend istream &operator>>(istream &input,Rational &obj);

 int Iegal(void) const;                                //判断有理数对象的值是否合法
};

//一个实数和一个有理数对象之间的四则运算重载
Rational operator+ (double ra, Rational& r);
Rational operator- (double ra, Rational& r);
Rational operator* (double ra, Rational& r);
Rational operator/ (double ra, Rational& r);

void PrintMixedNumber(Rational X);                         //将一个有理数对象转换为带分数形式
Rational SolveEquation(Rational a,Rational b,Rational c);  //求解一般的分数方程

//#endif

//二、函数实现部分：

//Rational.cpp

//#include <iostream>
//using namespace std;
//#include "Rational.h"

void Rational::Standardize ()                    //将有理数化为标准形式
{
	 if(Q == 0)
	 {
	  cout<<"Error!"<<endl;
	  exit(1);
	 }
	 else
	  if(Q < 0)
	  {
	   P= -P;
	   Q= -Q;
	  }
}

int Rational::gcd (int m,int n)                  //求两个数的最大公约数
{
	 int i,t;
	 if(m==0 || n==0)
	 {
	  cout<<"Error!"<<endl;
	  exit(1);
	 }
	 if(n>m || n<-m)
	 {
	  t=n;
	  n=m;
	  m=t;
	 }
	 i=m%n;
	 if(i!=0)
	  do
	  {
	   m=n;
	   n=i;
	   i=m%n;
	  }while(m%n!=0);
	 return ((n>0)? n : -n);
}

Rational::Rational (int p, int q)                //构造有理数分数，分子默认为0，分母默认为1
{
	 P=p;
	 Q=q;
	 Standardize();
}

Rational::Rational (Rational& r)                 //拷贝构造函数
{
	 P=r.P;
	 Q=r.Q;
	 Standardize();
}

Rational::Rational (double ra)                   //构造函数，将实数转换为标准形式的有理数
{
	 int base=1;
	 while(ra-(int)ra !=0)
	 {
	  ra=ra*10;
	  base=base*10;
	 }
	 P=ra;
	 Q=base;
}

Rational::~Rational (void)                       //虚析构函数
{}

void Rational::Reduce ()                         //将分数化为最简形式
{
	 int max=gcd(P,Q);
	 P= P/max;
	 Q= Q/max;
}

int Rational::GetNumerator()                     //取分数的分子
{
	 return P;
}
int Rational::GetDenominator()                   //取分数的分母
{
	 return Q;
}

Rational& Rational::operator= (Rational& r)      //将一个有理数对象赋值给另一个对象
{
	 P=r.GetNumerator();
	 Q=r.GetDenominator();
	 return *this;
}

Rational& Rational::operator= (double ra)         //将一个实数赋值给一个有理数对象
{
	 Rational temp(ra);
	 *this=temp;
	 return *this;
}

Rational Rational::operator- ()                   //将一个有理数取反
{
	 Rational temp(-GetNumerator(),GetDenominator());
	 return temp;
}

double Float(Rational &r)                          //强制转换一个有理数对象为一个实数
{
	 return (1.0*r.GetNumerator()/r.GetDenominator());
}

//以下为两个有理数对象、一个有理数对象和一个实数、一个实数和一个有理数对象
//之间的关系运算符的重载
int Rational::operator== (Rational& r) const
{
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 return (P*r_q==r_p*Q);
}

int Rational::operator== (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 return (P*temp_q==temp_p*Q);
}

int operator== (double ra, Rational& r)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 r_p=r_p*temp_q;
	 temp_p=temp_p*r_q;
	 return (r_p==temp_p);
}
 
int Rational::operator!= (Rational& r) const
{
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 return !(P*r_q==r_p*Q);
}

int Rational::operator!= (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 return !(P*temp_q==temp_p*Q);
}

int operator!= (double ra, Rational& r)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 r_p=r_p*temp_q;
	 temp_p=temp_p*r_q;
	 return !(r_p==temp_p);
}
 
int Rational::operator< (Rational& r) const
{
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 return (P*r_q<r_p*Q);
}

int Rational::operator< (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 return (P*temp_q<temp_p*Q);
}

int operator< (double ra, Rational& r)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 r_p=r_p*temp_q;
	 temp_p=temp_p*r_q;
	 return (r_p<temp_p);
}
 
int Rational::operator<= (Rational& r) const
{
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 return (P*r_q<=r_p*Q);
}

int Rational::operator<= (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 return (P*temp_q<=temp_p*Q);
}

int operator<= (double ra, Rational& r)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 r_p=r_p*temp_q;
	 temp_p=temp_p*r_q;
	 return (r_p<=temp_p);
}

int Rational::operator> (Rational& r) const
{
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 return (P*r_q>r_p*Q);
}

int Rational::operator> (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 return (P*temp_q>temp_p*Q);
}

int operator> (double ra, Rational& r)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 r_p=r_p*temp_q;
	 temp_p=temp_p*r_q;
	 return (r_p>temp_p);
}
 
int Rational::operator>= (Rational& r) const
{
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 return (P*r_q>=r_p*Q);
}

int Rational::operator>= (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 return (P*temp_q>=temp_p*Q);
}

int operator>= (double ra, Rational& r)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 r_p=r_p*temp_q;
	 temp_p=temp_p*r_q;
	 return (r_p>=temp_p);
}

//以下为两个有理数对象、一个有理数对象和一个实数
//之间的普通四则运算的重载
Rational Rational::operator+ (Rational& r) const
{
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 Rational obj(P*r_q+r_p*Q,Q*r_q);
	 return obj;
}
 
Rational Rational::operator+ (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 Rational obj(P*temp_q+temp_p*Q,Q*temp_q);
	 return obj;
}

void Rational::operator+= (Rational& r)
{
	 P=P+r.GetNumerator();
	 Q=Q+r.GetDenominator();
}

void Rational::operator+= (double ra)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 P=P*temp_q+temp_p*Q;
	 Q=temp_q*Q;
}

Rational Rational::operator- (Rational& r) const
{
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 Rational obj(P*r_q-r_p*Q,Q*r_q);
	 return obj;
}
  
Rational Rational::operator- (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 Rational obj(P*temp_q-temp_p*Q,Q*temp_q);
	 return obj;
}

void Rational::operator-= (Rational& r)
{
	 P=P-r.GetNumerator();
	 Q=Q-r.GetDenominator();
}

void Rational::operator-= (double ra)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 P=P*temp_q-temp_p*Q;
	 Q=temp_q*Q;
}

Rational Rational::operator* (Rational& r) const
{
	 Rational temp(P*r.GetNumerator(), Q*r.GetDenominator());
	 return temp;
}
 
Rational Rational::operator* (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 Rational obj(P*temp_p,Q*temp_q);
	 return obj;
}

void Rational::operator*= (Rational& r)
{
	 P=P*r.GetNumerator();
	 Q=Q*r.GetDenominator();
}

void Rational::operator*= (double ra)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 P=P*temp_p;
	 Q=temp_q*Q;
}

Rational Rational::operator/ (Rational& r) const
{
	 Rational temp(P*r.GetDenominator(),Q*r.GetNumerator());
	 return temp;
}
  
Rational Rational::operator/ (double ra) const
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 Rational obj(P*temp_q,Q*temp_p);
	 return obj;
}

void Rational::operator/= (Rational& r)
{
	 P=P*r.GetDenominator();
	 Q=Q*r.GetNumerator();
}

void Rational::operator/= (double ra)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 P=P*temp_q;
	 Q=temp_p*Q;
}

//输入输出流的重载，输出为最简形式
ostream& operator<<(ostream &output,Rational &obj)
{
	obj.Reduce();
	output<<obj.GetNumerator();
	output<<"/"<<obj.GetDenominator();
	return output;
}

istream& operator>>(istream &input,Rational &obj)
{
	int num,den;
	char oper;
	input>>num;
	input>>oper;
	input>>den;
	Rational temp(num,den);
	obj=temp;
	return input;
}

int Rational::Iegal(void) const                         //判断有理数对象的值是否合法
{
	 if(Q==0)
	  return 0;
	 else
	  return 1;
}

//一个实数和一个有理数对象之间的四则运算重载
Rational operator+ (double ra, Rational& r)
{
	 Rational temp(ra);
	 temp=temp+r;
	 return temp;
}

Rational operator- (double ra, Rational& r)
{
	 Rational temp(ra);
	 temp=temp-r;
	 return temp;
}

Rational operator* (double ra, Rational& r)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 Rational obj(temp_p*r_p,r_q*temp_q);
	 return obj;
}

Rational operator/ (double ra, Rational& r)
{
	 Rational temp(ra);
	 int temp_p=temp.GetNumerator(), temp_q=temp.GetDenominator();
	 int r_p=r.GetNumerator(), r_q=r.GetDenominator();
	 Rational obj(temp_p*r_q,r_p*temp_q);
	 return obj;
}

void PrintMixedNumber(Rational X)                          //将一个有理数对象转换为带分数形式
{
	 int t;
	 X.Reduce();
	 t=X.GetNumerator()/X.GetDenominator();
	 cout<<t<<"("<<(X.GetNumerator()-t*X.GetDenominator())<<"/"<<X.GetDenominator()<<")"<<endl;
}

Rational SolveEquation(Rational a,Rational b,Rational c)   //求解一般的分数方程
{
	 Rational temp;
	 if(a.GetNumerator()==0)
	 {
		  cout<<"Error!"<<endl;
		  exit(1);
	 }
	 temp=(c-b)/a;
	 temp.Reduce();
	 return temp;
}

//三、主函数（测试部分）:
//#include<iostream>
//using namespace std;
//#include "Rational.h"

int main()
{
	 Rational A(-4,-8),C,D;
	 Rational B(10.05);
	 Rational E(B);
	 cout<<"Please input C: ";
	 cin>>C;
	 D=43.9;
	 cout<<"A = "<<A<<endl;
	 cout<<"B = "<<B<<endl;
	 cout<<"E = "<<E<<endl;
	 cout<<"B = E ? "<<(B==E)<<endl;
	 cout<<"A != B ? "<<(A!=B)<<endl;
	 cout<<"-B = "<<(-B)<<endl;
	 cout<<"D(43.9) = "<<D<<endl;
	 cout<<"A+B = "<<(A+B)<<endl;
	 cout<<"A-B = "<<(A-B)<<endl;
	 cout<<"A+1.5 = "<<(A+1.5)<<endl;
	 cout<<"1.5+A = "<<(1.5+A)<<endl;
	 cout<<"A*1.5 = "<<(A*1.5)<<endl;
	 cout<<"1.5*A = "<<(1.5*A)<<endl;
	 cout<<"A/B = "<<(A/B)<<endl;
	 cout<<"A/1.5 = "<<(A/1.5)<<endl;
	 cout<<"1.5/A = "<<(1.5/A)<<endl;
	 A*=1.5;
	 cout<<"A*=1.5 = "<<A<<endl;
	 cout<<"float(A) = "<<Float(A)<<endl;
	 cout<<"E 的带分数形式为: ";
	 PrintMixedNumber(E);
	 Rational X;
	 cout<<"A*X+B=C 解得: ";
	 X=SolveEquation(A,C,E);
	 cout<<"X = "<<X<<endl;

#ifdef _MSC_VER
	system("pause");
#endif
	 return 0;
}
