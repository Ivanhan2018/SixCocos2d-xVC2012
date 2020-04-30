#include <iostream>
using namespace std;

/*
root@iZ14rcmneyrcltZ:~/cpptest# g++ -o Temfunc Temfunc.cpp
root@iZ14rcmneyrcltZ:~/cpptest# ./Temfunc
16
i= 625
l= 1000000000
d= 1e+10
*/
template <class T>
T power(T base, int exponent)
{
    T result = base;
    if (exponent == 0)  return (T)1;
    if (exponent < 0)   return (T)0;
    while (--exponent)  result *= base;
    return result;
}

int main()
{
    int i = power(5, 4);
    long l = power(1000L, 3);
    long double d = power((long double)1e5, 2);
	
	cout<<sizeof(long double)<<endl;//16
    cout << "i= " << i << endl;
    cout << "l= " << l << endl;
    cout << "d= " << d << endl;
    return 0;
}