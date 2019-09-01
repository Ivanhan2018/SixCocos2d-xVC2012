//��C++��д����������
#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#include <stdio.h>
#include <tchar.h>
#include<iostream>
using namespace std;
//һ��ͷ�ļ��������壺

//Rational.h

//#ifndef RATIONAl_CLASS
//#define RATIONAl_CLASS

class Rational
{
private:
 int P,Q;
 void Standardize();                //����������Ϊ��׼��ʽ
 int gcd (int m,int n);             //�������������Լ��
public:
 Rational (int p=0, int q=1);       //��������������������Ĭ��Ϊ0����ĸĬ��Ϊ1
 Rational (Rational &r);            //�������캯��
 Rational (double ra);              //���캯������ʵ��ת��Ϊ��׼��ʽ��������

 virtual ~Rational (void);          //����������

 void Reduce ();                    //��������Ϊ�����ʽ

 int GetNumerator();                //ȡ�����ķ���
 int GetDenominator();              //ȡ�����ķ�ĸ

 Rational& operator= (Rational& r); //��һ������������ֵ����һ������
 Rational& operator= (double ra);   //��һ��ʵ����ֵ��һ������������
 Rational operator- ();            //��һ��������ȡ��
 friend double Float(Rational &r);  //ǿ��ת��һ������������Ϊһ��ʵ��

 //����Ϊ��������������һ�������������һ��ʵ����һ��ʵ����һ������������
 //֮��Ĺ�ϵ�����������
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

 //������������������һ�������������һ��ʵ��
 //֮�����ͨ�������������
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

 //��������������أ����Ϊ�����ʽ
 friend ostream &operator<<(ostream &output,Rational &obj);
    friend istream &operator>>(istream &input,Rational &obj);

 int Iegal(void) const;                                //�ж������������ֵ�Ƿ�Ϸ�
};

//һ��ʵ����һ������������֮���������������
Rational operator+ (double ra, Rational& r);
Rational operator- (double ra, Rational& r);
Rational operator* (double ra, Rational& r);
Rational operator/ (double ra, Rational& r);

void PrintMixedNumber(Rational X);                         //��һ������������ת��Ϊ��������ʽ
Rational SolveEquation(Rational a,Rational b,Rational c);  //���һ��ķ�������

//#endif

//��������ʵ�ֲ��֣�

//Rational.cpp

//#include <iostream>
//using namespace std;
//#include "Rational.h"

void Rational::Standardize ()                    //����������Ϊ��׼��ʽ
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

int Rational::gcd (int m,int n)                  //�������������Լ��
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

Rational::Rational (int p, int q)                //��������������������Ĭ��Ϊ0����ĸĬ��Ϊ1
{
	 P=p;
	 Q=q;
	 Standardize();
}

Rational::Rational (Rational& r)                 //�������캯��
{
	 P=r.P;
	 Q=r.Q;
	 Standardize();
}

Rational::Rational (double ra)                   //���캯������ʵ��ת��Ϊ��׼��ʽ��������
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

Rational::~Rational (void)                       //����������
{}

void Rational::Reduce ()                         //��������Ϊ�����ʽ
{
	 int max=gcd(P,Q);
	 P= P/max;
	 Q= Q/max;
}

int Rational::GetNumerator()                     //ȡ�����ķ���
{
	 return P;
}
int Rational::GetDenominator()                   //ȡ�����ķ�ĸ
{
	 return Q;
}

Rational& Rational::operator= (Rational& r)      //��һ������������ֵ����һ������
{
	 P=r.GetNumerator();
	 Q=r.GetDenominator();
	 return *this;
}

Rational& Rational::operator= (double ra)         //��һ��ʵ����ֵ��һ������������
{
	 Rational temp(ra);
	 *this=temp;
	 return *this;
}

Rational Rational::operator- ()                   //��һ��������ȡ��
{
	 Rational temp(-GetNumerator(),GetDenominator());
	 return temp;
}

double Float(Rational &r)                          //ǿ��ת��һ������������Ϊһ��ʵ��
{
	 return (1.0*r.GetNumerator()/r.GetDenominator());
}

//����Ϊ��������������һ�������������һ��ʵ����һ��ʵ����һ������������
//֮��Ĺ�ϵ�����������
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

//����Ϊ��������������һ�������������һ��ʵ��
//֮�����ͨ�������������
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

//��������������أ����Ϊ�����ʽ
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

int Rational::Iegal(void) const                         //�ж������������ֵ�Ƿ�Ϸ�
{
	 if(Q==0)
	  return 0;
	 else
	  return 1;
}

//һ��ʵ����һ������������֮���������������
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

void PrintMixedNumber(Rational X)                          //��һ������������ת��Ϊ��������ʽ
{
	 int t;
	 X.Reduce();
	 t=X.GetNumerator()/X.GetDenominator();
	 cout<<t<<"("<<(X.GetNumerator()-t*X.GetDenominator())<<"/"<<X.GetDenominator()<<")"<<endl;
}

Rational SolveEquation(Rational a,Rational b,Rational c)   //���һ��ķ�������
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

//���������������Բ��֣�:
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
	 cout<<"E �Ĵ�������ʽΪ: ";
	 PrintMixedNumber(E);
	 Rational X;
	 cout<<"A*X+B=C ���: ";
	 X=SolveEquation(A,C,E);
	 cout<<"X = "<<X<<endl;

#ifdef _MSC_VER
	system("pause");
#endif
	 return 0;
}
