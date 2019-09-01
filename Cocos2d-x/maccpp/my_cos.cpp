#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;

double factorial(const int k)
{
    //int prod = 1;//会导致my_exp(1)=1.#INF00
	double prod = 1;
    for(int i=1; i<=k; i++)
        prod = i * prod;
    return prod;
}

double power(const double base, const int exponent)
{
    double result = 1;
    for(int i=1; i<=exponent; i++)
        result = result * base;
    return result;
}

double _my_exp(double x)
{
    double sum = 1 + x;
    for(int k=2; k<50; k++)
        sum = sum + power(x,k) / factorial(k);
    return sum;
}

/*
Instead of completely evaluating the power and the factorial terms for each term in your expansion, 
you should consider how the k'th term is related to the k-1'th term and just update each term based on this relationship. 
That will avoid the nasty overflows in your power and factorial functions (which you will no longer need). 
E.g.
*/
//下面的指数函数实现版本同上，但没有用阶乘函数和整数次幂函数
template<typename T>
T  my_exp(T x)
{
    T sum = 1.0 + x;
    T term = x;                 // term for k = 1 is just x
    for (int k = 2; k < 50; k++)//换成171，结果是一样的
    {
        term = term * x / (T)k; // term[k] = term[k-1] * x / k
        sum = sum + term;
    }
    return sum;
}

//Taylor series for cos(x): 
//cos(x)  = 1 - x^2/2! + x^4/4! - x^6/6! +x^8/8! - x^10/10! + ... 
#define MACH_EPS  1E-16 
template<typename T>
T my_cos(T x) 
{ 
	int k= 0; 
	T term = 1.0; 
	T sum = term; 
	T zeta = fabs((double)x); 
	T rem = zeta; 
	k=2; 

	while(fabs((double)rem/sum) > MACH_EPS)   { 
		term = - term * x * x / ((k-1)*k); 
		sum = sum + term; 
		k +=2; 
		rem = ((rem * zeta) / k) / (k-1); 
	} 
	return sum; 
}

// Ask the user to enter a float value
float ask_for_float(char *msg){
    printf(msg);
    float input = 0;
    if ( ! scanf("%f", &input) ){
        printf("You didn't enter a float value\n");
        exit(1);
    }
    return input;
}


// calculate a fourth order approximation of the cosine of x
float my_cos(float x){
    return (   1.0 - ( (x*x) / 2.0 ) + ( (x*x*x*x) / 24.0 )  - ( (x*x*x*x*x*x) / 720.0 )   );
}

// calculate the difference between the result of my_cos for x
// and the result from the library function.
float difference(float x){
    return my_cos(x) - cos(x);
}
//Enter float: 70.6858
//Approx Cos  : -172207216.000000
//Accurate Cos: 0.000036
//Difference  : -172207216.000000

template<typename T>
T my_sin(T x)
{
	T sum;
	T term;
	int n=1,i;
	term = x;
	sum = term;
	for(i=3;i<20;i=i+2)//循环 次数 估计足够了
	{
		n = n + 2;
		term = term * x * x /(T) n / (T) (n-1); 
		term = term * (-1.0);
		sum = sum + term;
	}
	return sum;
}

template<typename T>
T diff_sin(T x){
    return my_sin(x) - sin(x);
}

//根据arcsin(x)展开的级数，输入x，计算反正弦函数的值。结束条件为|u|<ε=MACH_EPS，u为通项。
template<typename T>
T my_arcsin(T x)
{ 
	T sum=0.0;
	int n=1;
	T index=x;//通项  
	while(fabs(index)>=MACH_EPS)
	{ 
		sum+=index; 
		index=factorial(2*n)*pow(x*1.0,2*n+1)/(factorial(n)*factorial(n)*pow(2,n*2.0)*(2*n+1)*1.0); 
		n++;
	} 
	return sum; 
}

//自然对数log(x)当0<x<2.0时，可以利用下式计算其近似值，log(x)=∑[n=1->∞](-1)^(n+1)(x-1)^n/n,0<x<2.0。
template<typename T>
T my_log(T x, int n)	//定義my_log、浮點數x、整數n
{
  T j(0.0), a;
  int i(1), b(1);
  while ( i <= n )
  {
    a = static_cast<T>(b * pow(x-1 , i)/ i);	//a=(x-1)的i次方除以i
    b = (-1) * b;									//b值用於變號
    i++;											//i值由1遞增到n
    j += a;											//累加a值
  }
  return j;											//傳回累加的a值
}

template<typename T>
T diff_log(T x, int n){
    return my_log(x,n) - log(x);
}

/*
Here is one of the most genius sqrt implementations which can be found on wikipedia. 
It is not the most accurate, but extremely fast.
*/
float fast_sqrt(float number) {
   long i;
   float x2, y;
   const float threehalfs = 1.5F;

   x2 = number * 0.5F;
   y  = number;
   i  = * ( long * ) &y;                     // floating point bit level hacking [sic]
   i  = 0x5f3759df - ( i >> 1 );             // Newton's approximation
   y  = * ( float * ) &i;
   y  = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
   y  = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
   y  = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration

   return 1/y;
}


int main()
{
	double ret1,ret2,ret3,ret4;
	printf("%lf\n",ret1=my_exp(1));
	printf("%lf\n",ret2=exp((double)1));
	printf("%lf\n",ret1=my_exp(10));
	printf("%lf\n",ret2=exp((double)10));
	printf("----my_cos测试结果\n----");
	printf("%lf\n",ret1=my_cos(0));
	printf("%lf\n",ret2=my_cos(3.14158265/2));
	printf("%lf\n",ret3=my_cos(2*3.14158265/3));
	printf("%lf\n",ret4=my_cos(3.14158265/3));
	printf("%lf\n",ret2=my_cos(5*3.14158265/2));
	printf("%lf\n",ret2=my_cos(45*3.14158265/2));
	printf("----cos测试结果\n----");
	printf("%lf\n",ret1=cos((double)0));
	printf("%lf\n",ret2=cos((double)3.14158265/2));
	printf("%lf\n",ret3=cos((double)2*3.14158265/3));
	printf("%lf\n",ret4=cos((double)3.14158265/3));
	printf("%lf\n",ret2=cos((double)5*3.14158265/2));
	printf("%lf\n",ret2=cos((double)45*3.14158265/2));

    //float input;
    //input = ask_for_float("Enter float: ");
    //printf( "Approx Cos  : %f\n", my_cos(input) );
    //printf( "Accurate Cos: %f\n", cos(input) );
    //printf( "Difference  : %f\n", difference(input) );
    //printf( "\nIn the range [0,1], the theoretical maximum error for the used approximation as calculated by Taylor's formula is 1/7! ~= 2e-4. The actual maximum error which is reached for x=1, is in fact smaller by one order of magnitude.\n");
  float p;			//浮點數p
	for (p = static_cast< float >(0.1) ;	//p=0.1、0.2、0.3.....1.9、2.0
	   p <= 1.5 ;
	   p += static_cast< float >(0.1) )
	{
		printf("my_log(%f,20)=%f,diff_log=%f\n",p,my_log(p,20),diff_log(p,20));
	}

#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}
