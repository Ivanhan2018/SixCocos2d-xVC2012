//
//  Arcsn.cpp
// 
//
//  Created by Hsq on 19/8/23.
//  Copyright © 2019年 Bjoy. All rights reserved.
//
/*
 g++ -o Arcsn Arcsn.cpp
 HsqtekiMac-2:Arcsn Hsq$ ./Arcsn 0.5 0.6
 Arcsn(e=0.500000;x=0.600000)=0.654169
 HsqtekiMac-2:Arcsn Hsq$ ./Arcsn
 计算雅可比分号形式的第一类[不完全]椭圆积分Arcsn(e;x)，请输入e和x,0<=e<=1,-1<=x<=1：
 0.5 0.5
 Arcsn(e=0.500000;x=0.500000)=0.529429
 HsqtekiMac-2:Arcsn Hsq$ Arcsn 0.5 0.5
 -bash: Arcsn: command not found
 HsqtekiMac-2:Arcsn Hsq$ pwd
 /Users/Hsq/SixCocos2d-xVC2012/Cocos2d-x/maccpp/Arcsn/Arcsn
 */
#include <iostream>
#include<math.h>

static double __cdecl fk(double k,double f)
{ int m,i,j;
    double s,p,ep,h,aa,bb,w,xx,g,q;
    static double t[5]={-0.9061798459,-0.5384693101,0.0,
        0.5384693101,0.9061798459};
    static double c[5]={0.2369268851,0.4786286705,0.5688888889,
        0.4786286705,0.2369268851};
    m=1; g=0.0;
    h=fabs(f); s=fabs(0.0001*h);
    p=1.0e+35; ep=0.000001;
    while ((ep>=0.0000001)&&(fabs(h)>s))
    { g=0.0;
        for (i=1;i<=m;i++)
        { aa=(i-1.0)*h; bb=i*h;
            w=0.0;
            for (j=0;j<=4;j++)
            { xx=((bb-aa)*t[j]+(bb+aa))/2.0;
                q=sqrt(1.0-k*k*sin(xx)*sin(xx));
                w=w+c[j]/q;
            }
            g=g+w;
        }
        g=g*h/2.0;
        ep=fabs(g-p)/(1.0+fabs(g));
        p=g; m=m+m; h=0.5*h;
    }
    return(g);
}

double __cdecl lelp1(double k,double f)
{ int n;
    double pi,y,e,ff;
    if (k<0.0) k=-k;
    if (k>1.0) k=1.0/k;
    pi=3.1415926; y=fabs(f);
    n=0;
    while (y>=pi)
    { n=n+1; y=y-pi;}
    e=1.0;
    if (y>=pi/2.0)
    { n=n+1; e=-e; y=pi-y;}
    if (n==0)
        ff=fk(k,y);
    else
    { ff=fk(k,pi/2.0);
        ff=2.0*n*ff+e*fk(k,y);
    }
    if (f<0.0) ff=-ff;
    return(ff);
}

//雅可比分号形式的第一类[不完全]椭圆积分Arcsn(e;x)
double __cdecl lelp1J(double(__cdecl *lelp1)(double e,double x),double e,double x)
{
    return lelp1(e,asin(x));
}

double __cdecl Arcsn(double e,double x)
{
    //return lelp1J(lelp1,e,x);
    return lelp1(e,asin(x));
}

int main(int argc, const char * argv[]) {
    if(argc>=3)
    {
        double e=atof(argv[1]);
        double x=atof(argv[2]);
        double ret=Arcsn(e,x);
        printf("Arcsn(e=%f;x=%f)=%f\n",e,x,ret);
    }
    else
    {
        double e,x;
        printf("计算雅可比分号形式的第一类[不完全]椭圆积分Arcsn(e;x)，请输入e和x,0<=e<=1,-1<=x<=1：\n");
        scanf("%lf%lf",&e,&x);
        printf("Arcsn(e=%f;x=%f)=%f\n",e,x,Arcsn(e,x));
    }
    //getchar();
    return 0;
}
