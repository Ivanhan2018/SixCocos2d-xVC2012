/*
问题描述：
求一个整数的高斯素因子。
解题思路：
高斯整数a+bi是素数当且仅当：
1)a、b中有一个是零，另一个数的绝对值是形如4n+3的素数；
2)a、b均不为零，而a^2+b^2为素数；
于是只要将每个分解素因子，对于每个素因子P,如果该素因子形如4n+3，则必定能分解成(a+bj)(a-bj)=a^2+b^2，枚举解决。

a=7+5i，b=18+5i
q=2-i,r=-1+2i
q=2,r=4-5i
q=3-i,r=-8-3i
q=3,r=3-10i

112+i和-57+79i的最大公因数(112+i,-57+79i)=4+7i 
7+5i和18+5i的最大公因数(7+5i,18+5i)=-i 

a=1734+1938i的素因子分解式：a=i(1+i)^3•3•(1+2i)^2•(2+3i)•(1+4i)•(1-4i)
*/

#include <iostream>
#include <cmath>
using namespace std;

int f[65537], p[65537], size;
int pri[1000], top;
int n;

struct point
{
    int a;
    int b;
    char oper;
}s[10000];
int num;

//筛选素数
void init()
{
    f[1] = 1;
    int i, j;
    for(i = 2; i <= 65536; i++)
    {
        if(!f[i])
        {
            p[ size++ ] = i;
            for(j = i+i; j <= 65536; j += i)
                f[j] = 1;
        }
    }
}

//素因子分解
void Flip(int key)
{
    int i;
    top = 0;
    for(i = 0; i < size; i++)
    {
        if(key % p[i] == 0)
        {
            pri[ top++ ] = p[i];
            key /= p[i];

            while(key % p[i] == 0){
                pri[ top++ ] = p[i];
                key /= p[i];
            }
        }
    }

    if(key - 1)
        pri[ top++ ] = key;
}

//高斯素数分解
void Part(int prime)
{
    int i;
    if(prime == 2)
    {
        s[ num ].a = 1; s[ num ].b = 1; s[ num++ ].oper = '+';
        s[ num ].a = 1; s[ num ].b = 1; s[ num++ ].oper = '-';
    }else if( (prime - 1) % 4 == 0)
    {
        for(i = 1; ;i++)
        {
            int u = int(sqrt(prime - i*i*1.0) + 1e-5);
            if(u*u + i*i == prime)
            {
                s[ num ].a = i; s[ num ].b = u; s[ num++ ].oper = '+';
                s[ num ].a = i; s[ num ].b = u; s[ num++ ].oper = '-';
                break;
            }
        }
    }else
    {
        s[ num ].a = prime; s[ num++ ].b = 0;
    }
}

int cmp(const void *a, const void *b)
{
    point *c = (point *)a;
    point *d = (point *)b;
    if(c->a != d->a)
        return c->a - d->a;
    if(c->b != d->b)
        return c->b - d->b;
    return c->oper == '-' ? 1 : -1;
}

void Print(int key)
{
    printf("%d", s[key].a );
    
    if(s[key].b == 0)
        return;

    if(s[key].b == 1)
    {
        printf("%cj", s[key].oper);
    }else
    {
        printf("%c%dj", s[key].oper, s[key].b);
    }

}

int main()
{
    init();
    int i, cas = 1;

    while(scanf("%d", &n) != EOF && n!=0)
    {
        num = 0;
        Flip(n);
        for(i = 0; i < top; i++)
        {
            Part(pri[i]);
        }

        qsort(s, num, sizeof(point), cmp);
        printf("Case #%d: ", cas++);
        Print(0);
        for(i = 1; i < num; i++)
        {
            if(s[i].a == s[i-1].a
                && s[i].b == s[i-1].b
                && s[i].oper == s[i-1].oper)
                continue;
            if(i)
                printf(", ");
            Print(i);
        }
        puts("");
    }
    return 0;
}

