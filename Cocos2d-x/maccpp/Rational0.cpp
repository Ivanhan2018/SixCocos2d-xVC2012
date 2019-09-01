//有理数类，第一贝努利数B_n的计算（0<=n<=14，fac函数、gcd函数需要改进）
//#include "stdafx.h"
#include <iostream>
#include <utility>
using namespace std;
//exception for denumerator being 0
class invalid { };

class Rational {
public:
	Rational(): num(1),den(1) {}
	Rational( long n, long d );
	Rational( const Rational& r );
	//void Rational::operator = (const Rational& r );
	pair< long, long > reduction( long n, long d );
	long gcd( long n, long d);
	long get_num() { return num; }
	long get_den() { return den; }
private:
	long num;
	long den;
};
//get the greatest comman divisor
//求最大公约数的gcd函数写的不好，递归层次太深，导致堆栈溢出，用while do改写了后就可以算25个伯努利数了 
long Rational::gcd ( long n, long d){
	n=abs(n);
	d=abs(d);
	if (n > d)
		gcd(n-d,d);
	else if (n < d)
		gcd(n,d-n);
	else
		return n;
}
//the reduction of the fraction
pair<long, long> Rational::reduction ( long n, long d ){
	pair<long, long> p;
	long x;
	if ( n == 0 ){
		p = make_pair( n, 1 );
		return p;
	} else {
		x = gcd(n,d);
		p = make_pair( n/x, d/x );
		return p;
	}
}
//constructing function
Rational::Rational ( long n, long d ){ 
	//if (d == 0) throw new invalid();
	//else {
	pair< long, long> p = reduction(n,d);
	num = p.first;
	den = p.second;
	//}
}
////reload the assign operator =
//void Rational::operator = (const Rational& r ) {
//	num = r.get_num();
//	den = r.get_den();
//	return;
//}
//copying constructing function
Rational::Rational ( const Rational& r ) :
num(r.num),den(r.den) { }
//reload operator +
Rational operator + ( Rational& r1, Rational& r2 ){
	if ( r1.get_num() == 0 )
		return r2;
	if ( r2.get_num() == 0 )
		return r1;
	long n,d;
	n = r1.get_num() * r2.get_den() + r1.get_den() * r2.get_num();
	d = r1.get_den() * r2.get_den();
	Rational r(n,d);
	return r;
}
//reload operator -
Rational operator - ( Rational& r1, Rational& r2 ){
	if ( r2.get_num() == 0 )
		return r1;
	long n,d;
	if ( r1.get_num() == 0 ){
		n = - r2.get_num();
		d = r2.get_den();
	} else {
		n = r1.get_num() * r2.get_den() - r1.get_den() * r2.get_num();
		d = r1.get_den() * r2.get_den();
	}
	Rational r(n,d);
	return r;
}
//reload operator *
Rational operator * ( Rational& r1, Rational& r2 ) {
	long n,d;
	if ( r1.get_num() == 0 || r2.get_num() == 0 ) {
		n = 0;
		d = 1;
	} else {
		n = r1.get_num() * r2.get_num();
		d = r1.get_den() * r2.get_den();
	}
	Rational r(n,d);
	return r;
}
//reload operator /
Rational operator / ( Rational& r1, Rational r2 ) {
	long n,d;
	if ( r2.get_num() == 0 )
		throw new invalid();
	if ( r1.get_num() == 0 ){
		n = 0;
		d = 1;
	} else {
		n = r1.get_num() * r2.get_den();
		d = r1.get_den() * r2.get_num();
	}
	Rational r(n,d);
	return r;
}
//reload operator ==
bool operator == ( Rational& r1, Rational& r2 ) {
	if ( r1.get_num() * r2.get_den() == r1.get_den() * r2.get_num() )
		return 1;
	else
		return 0;
}
//reload operator !=
bool operator != ( Rational& r1, Rational& r2 ) {
	if ( r1.get_num() * r2.get_den() != r1.get_den() * r2.get_num() )
		return 1;
	else
		return 0;
}
//reload operator <
bool operator < ( Rational& r1, Rational& r2 ) {
	if ( r1.get_num() * r2.get_den() < r1.get_den() * r2.get_num() )
		return 1;
	else
		return 0;
}
//reload operator >
bool operator > ( Rational& r1, Rational& r2 ) {
	if ( r1.get_num() * r2.get_den() > r1.get_den() * r2.get_num() )
		return 1;
	else
		return 0;
}
//reload operator <<
ostream& operator << ( ostream& s, Rational& r) {
	if ( r.get_den() == 1 && r.get_num() != 0)
		return s << r.get_num() << " ";
	if ( r.get_num() == 0 )
		return s << 0 << " ";
	return s << r.get_num() << '/' << r.get_den() << " " ;
}

//#include "stdafx.h"
//#include "rational.h"
#include <vector>

struct error {};
//小整数版阶乘(n<=13)calculate the factorial of an integer
long fac(unsigned long n)
{
	if (n == 0||n == 1)
		return 1;
	else
		return (n*fac(n-1));
}
//calculate the coefficient of the formula using combinatorics
Rational coeff_cal(long m, long k)    
{
	long co_num = 1;
	if ( k == 0 ) {
		Rational coeff;
		return coeff;
	}else {
		for ( int i = 0; i != k; ++ i )
			co_num = co_num * (m - i);
		for ( int i = 0; i != k; ++ i )
			co_num = co_num / (k - i);
		Rational coeff(co_num,1);
		return coeff;
	}
}
//create n bernoulli numbers
void create( int n, vector<Rational>& b) {
	Rational temp;
	Rational temp0(0,1);
	Rational coeff;
	for ( int i = 1; i != n; ++ i ) {
		//if ( i == 14)
		//	cout << i;
		int j = 0;
		Rational sum(0,1);
		for ( ; j != i; ++ j ) {                  //这里可以切成两段提高效率（组合数的对称性）
			coeff = coeff_cal(i+1,(j > ((i +1) / 2)) ? (i+1-j):j);
			temp = (coeff * b[j]);
			sum = (sum + temp);
		}
		coeff = coeff_cal(i+1,1);
		temp = sum / coeff;
		temp = temp0 - temp;
		b.push_back(temp);
	}
}

void pause()
{
#ifdef _MSC_VER
	system("pause");
#endif
}

int main()
{
	int n;
	vector<Rational> bernoulli;
	Rational b0;
	bernoulli.push_back(b0);
	try {
		cout << "please enter the number of bernoulli numbers you want to get:" << endl;
		cin >> n;
		if ( n <= 0 )
			throw error();
	} catch (error) {
		cout << "invalid n" << endl;
		pause();
		return 1;
	}
	if ( n ==1 ){
		cout << b0;
		pause();
		return 1;
	}
	else
		create(n, bernoulli);
	for ( vector<Rational>::iterator ib = bernoulli.begin(); ib != bernoulli.end(); ++ ib)
		cout << *ib;
	pause();
	return 1;
}
