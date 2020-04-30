#include <math.h>
#include <stdio.h>
  
// 矩形求积法   
double integalrect(double a,double b,double eps,double(*fun)(double x))   
{   
double sum=0,h,x1,x2;   
int n=static_cast<int>(1.f/eps); 
h=(b-a)/n; /*积分步长*/   
x1=a;
x2=x1+h;   
for(int i=1;i<=n;i++)   
{   
sum+=(*fun)((x2+x1)/2);   
x1+=h;
x2+=h;   
}   
sum*=h;   
return sum;   
}

// 梯形求积法:a是积分下限,b是积分上限,精度eps定义为等分区间数n的倒数,fun是被积函数
double integaltrap(double a,double b,double eps,double(*fun)(double x))   
{
#if 1	
double s,h,y;
s=(fun(a)+fun(b))/2;
int n=static_cast<int>(1.f/eps); 
h=(b-a)/n; /*积分步长*/ 
for(int i=1;i<n;i++) 
s=s+fun(a+i*h); 
y=s*h; 
return y;/*返回积分值*/ 
#else
double s=0,h,x1,x2;   
h=(b-a)/n;   
x1=a;
x2=x1+h;   
for(int i=1;i<=n-1;i++)   
{   
x1+=h;   
s+=(*fun)(x1);   
}   
s=h*(s*2+(*fun)(a)+(*fun)(b))/2;   
return s; 
#endif  
}

// 抛物线求积法   
double integalpara(double a,double b,double eps,double(*fun)(double x))   
{     
double sum=0,h,x1,x2;   
int n=static_cast<int>(1.f/eps); 
h=(b-a)/n; /*积分步长*/   
x1=a;
x2=x1+h;   
for(int i=1;i<=n-1;i++)   
{   
sum+=(*fun)(x1)+4*(*fun)((x1+x2)/2)+(*fun)(x2);   
x1+=h;   
x2+=h;   
}   
sum*=h/6;   
return sum;   
}

double fsimp(double a,double b,double eps,double(*fsimpf)(double)) /*辛普森求积法*/ 
/*a为积分下限，b为积分上限，eps是希望达到的精度*/ 
{ 
int n,k; 
double h,t1,t2,s1,s2,ep,p,x; 
n=1; h=b-a; 
t1=h*(fsimpf(a)+fsimpf(b))/2.0; /*用梯形公式求出一个大概的估值*/ 
s1=t1; 
ep=eps+1.0; 
while (ep>=eps) 
{ 
/*用梯形法则计算*/ 
p=0.0; 
for (k=0;k<=n-1;k++) 
{ 
x=a+(k+0.5)*h; 
p=p+fsimpf(x); 
} 
t2=(t1+h*p)/2.0; 
/*用辛普森公式求精*/ 
s2=(4.0*t2-t1)/3.0; 
ep=fabs(s2-s1); 
t1=t2; s1=s2; n=n+n; h=h/2.0; 
} 
return(s2); 
}

/**********************变步长辛普生法*************/
/***a为积分下限;b为积分上限;eps为精度要求.********/
double bcsimp(double a,double b,double eps,double(*bcsimpf)(double x))
{
	int n,k;
	double h,t1,t2,s1,s2,ep,p,x;
	n=1;h=b-a;
	t1=h*(bcsimpf(a)+bcsimpf(b))/2.0;
	s1=t1;
	ep=eps+1.0;
	while(ep>=eps)
	{
		p=0.0;
		for(k=0;k<=n-1;k++)
		{x=a+(k+0.5)*h;
		p=p+bcsimpf(x);
		}
		t2=(t1+h*p)/2.0;
		s2=(4.0*t2-t1)/3.0;
		ep=fabs(s2-s1);
		t1=t2;s1=s2;n=n+n;h=h/2.0;
	}
	return(s2);
}

double fcbsv(double a,double b,double eps,double(*fcbsvf)(double))//切比雪夫求积法
{
    int m,i,j;
    double h,d,p,ep,g,aa,bb,s,x;
    static double t[5]={-0.8324975,-0.3745414,0.0,
                         0.3745414,0.8324975};
    m=1;
    h=b-a; d=fabs(0.001*h);
    p=1.0e+35; ep=1.0+eps;
    while ((ep>=eps)&&(fabs(h)>d))
      { g=0.0;
        for (i=1;i<=m;i++)
          { aa=a+(i-1.0)*h; bb=a+i*h;
            s=0.0;
            for (j=0;j<=4;j++)
              { x=((bb-aa)*t[j]+(bb+aa))/2.0;
                s=s+fcbsvf(x);
              }
            g=g+s;
          }
        g=g*h/5.0;
        ep=fabs(g-p)/(1.0+fabs(g));
        p=g; m=m+1; h=(b-a)/m;
      }
    return(g);
}

double fromb(double a,double b,double eps,double(*frombf)(double))//龙贝格求积法
/*a为积分下限，b为积分上限，eps是希望达到的精度*/ 
{ 
    int m,n,i,k;
    double y[10],h,ep,p,x,s,q;
    h=b-a;
    y[0]=h*(frombf(a)+frombf(b))/2.0;
    m=1; n=1; ep=eps+1.0;
    while ((ep>=eps)&&(m<=9))
      { p=0.0;
        for (i=0;i<=n-1;i++)
          { x=a+(i+0.5)*h;
            p=p+frombf(x);
          }
        p=(y[0]+h*p)/2.0;
        s=1.0;
        for (k=1;k<=m;k++)
          { s=4.0*s;
            q=(s*p-y[k-1])/(s-1.0);
            y[k-1]=p; p=q;
          }
        ep=fabs(q-y[m-1]);
        m=m+1; y[m-1]=q; n=n+n; h=h/2.0;
      }
    return(q);
}

int main(int argc, char* argv[])
{
	typedef double(*pR)(double a,double b,double eps,double(*frombf)(double));
	pR R[]={integalrect,integaltrap,integalpara,bcsimp,fcbsv,fromb};
	const char *szNameR[]={"矩形求积法","梯形求积法","抛物线求积法","变步长辛普生求积法","切比雪夫求积法","龙贝格求积法"};
	int nR=sizeof(szNameR)/sizeof(szNameR[0]);
	double a,b,eps,t;
	a=2.5; b=8.4; eps=0.000001;
	typedef double(*pF)(double);	
	pF F[]={[](double x)->double{return x*x+sin(x);},[](double x)->double{return x/(4.0+x*x);},[](double x)->double{return exp(x*x);}};	
	const char *szNameF[]={"x*x+sin(x)","y=x/(4.0+x*x)","y=exp(x*x)"};
	int nF=sizeof(szNameF)/sizeof(szNameF[0]);
	for(int i=0;i<nF;i++)
	{
		printf("被积函数:%s,积分区间:[%f,%f]:\n",szNameF[i],a,b);
		for (int j=0;j<nR;j++)
		{
			t=R[j](a,b,eps,F[i]);
			printf("%s定积分值:%f,",szNameR[j],t);
		}
		printf("\n");
	}
	return 0;
}

