//
//  dfridr.cpp
// 
//
//  Created by Hsq on 19/8/23.
//  Copyright © 2019年 Bjoy. All rights reserved.
//
/*
 g++ -o dfridr dfridr.cpp
 HsqtekiMac-2:maccpp Hsq$ ./dfridr 1
dsin(x)/dx|_(x=1)=0.540301,cos(1)=0.540302
err=0.000001HsqtekiMac-2:maccpp Hsq$ ./dfridr
计算一阶导数dfridr(sin,x,h=0.1)，请输入x：
1
dsin(x)/dx|_(x=1)=0.540301,cos(1)=0.540302
 */
#include <iostream>
#include<math.h>
extern "C" float __cdecl dfridr(float(__cdecl *func)(float),float x,float h,float *err);

static float maxarg1,maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1)>(maxarg2)?(maxarg1):(maxarg2))

void nrerror(char error_text[])
{
    fprintf(stderr,"%s\n",error_text);
    exit(1);
}

float **matrix(long nrl,long nrh,long ncl,long nch)
{
    long i,nrow=nrh=nrh-nrl+1,ncol=nch-ncl+1;
    float **m;
    m=(float **)malloc((size_t)((nrow+1)*sizeof(float *)));
    if(!m)nrerror("malloc失败1");
    m+=1;
    m-=nrl;
    m[nrl]=(float *)malloc((size_t)((nrow*ncol+1)*sizeof(float)));
    if(!m[nrl])nrerror("malloc失败2");
    m[nrl]+=1;
    m[nrl]-=ncl;
    for(i=nrl+1;i<=nrh;i++)m[i]=m[i-1]+ncol;
    return m;
}

void free_matrix(float **m,long nrl,long nrh,long ncl,long nch)
{
    free((char *)(m[nrl]+ncl-1));
    free((char *)(m+nrl-1));
}

//Ridders多项式外推法求导func'(x)
//h!==0.0
float __cdecl dfridr(float(__cdecl *func)(float),float x,float h,float *err)
{
    int i,j;
    float errt,fac,hh,**a,ans;
    if(h==0.0)nrerror("h不能为0");
    a=matrix(1,10,1,10);
    hh=h;
    a[1][1]=((*func)(x+hh)-(*func)(x-hh))/(2.0*hh);
    *err=1.0e30;
    for(i=2;i<=10;i++)
    {
        hh/=1.4;
        a[1][i]=((*func)(x+hh)-(*func)(x-hh))/(2.0*hh);
        fac=1.96;
        for(j=2;j<=i;j++)
        {
            a[j][i]=(a[j-1][i]*fac-a[j-1][i-1])/(fac-1.0);
            fac=1.96*fac;
            errt=FMAX(fabs(a[j][i]-a[j-1][i]),fabs(a[j][i]-a[j-1][i-1]));
            if(errt<=*err)
            {
                *err=errt;
                ans=a[j][i];
            }
        }
        if(fabs(a[i][i]-a[i-1][i-1])>=2.0*(*err))break;
    }
    free_matrix(a,1,10,1,10);
    return ans;
}

float __cdecl Myfunc(float x)
{
    return sin(x);
}

int main(int argc, const char * argv[]) {
    if(argc>=2)
    {
        float x=atof(argv[1]);
        float err,ret;
        ret=dfridr(sinf,x,0.1,&err);
        printf("dsin(x)/dx|_(x=1)=%f,cos(1)=%lf\n",ret,cos(x));
        printf("err=%lf",err);
    }
    else
    {
        float x,err,ret;
        printf("计算一阶导数dfridr(sin,x,h=0.1)，请输入x：\n");
        scanf("%f",&x);
        ret=dfridr(sinf,x,0.1,&err);
        printf("dsin(x)/dx|_(x=1)=%f,cos(1)=%lf\n",ret,cos(1));
        printf("err=%lf",err);
    }
    //getchar();
    return 0;
}
