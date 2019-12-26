#include<iostream>
#include<complex>
using namespace std;

int main()
{
   complex<double> x(1,2.1), y;
   cout << "x = " << x << endl;
   cout << "sin(1,2.1)= " << sin(x) << endl;
   cout << "cos(1,2.1)= " << cos(x) << endl;
   cout << "exp(1,2.1)= " << exp(x).real() << "+" << exp(x).imag() << "i" << endl;
   cout << "norm(1,2.1)= " << norm(x) << endl;
   cout << "arg(1,2.1)= " << arg(x) << endl;
   cout << "conj(1,2.1)= " << conj(x) << endl;
   cout << "abs(1,2.1)= " << abs(x) << endl;
   y=sin(x)/cos(x);
   cout << "tan(1,2.1)= " << y.real() << "+" << y.imag() << "i" << endl;
   y=x+1.0;
   cout << "\ny = " << y << endl;
   // if (x < y) not allowed - no standard definition
   //   cout << "x less than y" << endl;
   return 0;
}
