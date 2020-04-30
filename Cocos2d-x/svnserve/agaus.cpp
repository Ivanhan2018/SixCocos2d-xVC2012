#include <math.h>
#include <stdio.h>

//全选主元高斯消去法求解实系数线性方程组：
//方程组的阶数n，a存放方程组的系数矩阵，返回时将被破坏，b存放方程组右端的常数向量，返回方程组的解向量，若返回的标志不为0，则正常返回
int agaus(double *a,double *b,int n)
{ 
    int *js,l,k,i,j,is,p,q;
    double d,t;
    js=(int *)malloc(n*sizeof(int));
    l=1;
    for (k=0;k<=n-2;k++)
      { d=0.0;
        for (i=k;i<=n-1;i++)
          for (j=k;j<=n-1;j++)
            { t=fabs(a[i*n+j]);
              if (t>d) { d=t; js[k]=j; is=i;}
            }
        if (d+1.0==1.0) l=0;
        else
          { if (js[k]!=k)
              for (i=0;i<=n-1;i++)
                { p=i*n+k; q=i*n+js[k];
                  t=a[p]; a[p]=a[q]; a[q]=t;
                }
            if (is!=k)
              { for (j=k;j<=n-1;j++)
                  { p=k*n+j; q=is*n+j;
                    t=a[p]; a[p]=a[q]; a[q]=t;
                  }
                t=b[k]; b[k]=b[is]; b[is]=t;
              }
          }
        if (l==0)
          { free(js); printf("fail\n");
            return(0);
          }
        d=a[k*n+k];
        for (j=k+1;j<=n-1;j++)
          { p=k*n+j; a[p]=a[p]/d;}
        b[k]=b[k]/d;
        for (i=k+1;i<=n-1;i++)
          { for (j=k+1;j<=n-1;j++)
              { p=i*n+j;
                a[p]=a[p]-a[i*n+k]*a[k*n+j];
              }
            b[i]=b[i]-a[i*n+k]*b[k];
          }
      }
    d=a[(n-1)*n+n-1];
    if (fabs(d)+1.0==1.0)
      { free(js); printf("fail\n");
        return(0);
      }
    b[n-1]=b[n-1]/d;
    for (i=n-2;i>=0;i--)
      { t=0.0;
        for (j=i+1;j<=n-1;j++)
          t=t+a[i*n+j]*b[j];
        b[i]=b[i]-t;
      }
    js[n-1]=n-1;
    for (k=n-1;k>=0;k--)
      if (js[k]!=k)
        { t=b[k]; b[k]=b[js[k]]; b[js[k]]=t;}
    free(js);
    return(1);
}

//求解大型稀疏方程组的全选主元高斯约当消去法 
int aggje(double *a,double *b,int n)
{   
    int *js,i,j,k,is,u,v;
    double d,t;
    js=(int*)malloc(n*sizeof(int));
    for (k=0; k<=n-1; k++)
      { d=0.0;
        for (i=k; i<=n-1; i++)
        for (j=k; j<=n-1; j++)
          { t=fabs(a[i*n+j]);
            if (t>d) {d=t; js[k]=j; is=i;}
          }
        if (d+1.0==1.0)
          { free(js); printf("fail\n"); return(0);}
        if (is!=k)
          { for (j=k; j<=n-1; j++)
              { u=k*n+j; v=is*n+j;
                t=a[u]; a[u]=a[v]; a[v]=t;
              }
            t=b[k]; b[k]=b[is]; b[is]=t;
          }
        if (js[k]!=k)
          for (i=0; i<=n-1; i++)
            { u=i*n+k; v=i*n+js[k];
              t=a[u]; a[u]=a[v]; a[v]=t;
            }
        t=a[k*n+k];
        for (j=k+1; j<=n-1; j++)
          { u=k*n+j;
            if (a[u]!=0.0) a[u]=a[u]/t;
          }
        b[k]=b[k]/t;
        for (j=k+1; j<=n-1; j++)
          { u=k*n+j;
            if (a[u]!=0.0)
              { for (i=0; i<=n-1; i++)
                  { v=i*n+k;
                    if ((i!=k)&&(a[v]!=0.0))
                      { is=i*n+j;
                        a[is]=a[is]-a[v]*a[u];
                      }
                  }
              }
          }
        for (i=0; i<=n-1; i++)
          { u=i*n+k;
            if ((i!=k)&&(a[u]!=0.0))
              b[i]=b[i]-a[u]*b[k];
          }
      }
    for (k=n-1; k>=0; k--)
      if (k!=js[k])
        { t=b[k]; b[k]=b[js[k]]; b[js[k]]=t;}
    free(js);
    return(1);
}

//全选主元高斯约当消去法
int agjdn(double *a,double *b,int n,int m)
{ 
    int *js,l,k,i,j,is,p,q;
    double d,t;
    js=(int*)malloc(n*sizeof(int));
    l=1;
    for (k=0;k<=n-1;k++)
      { d=0.0;
        for (i=k;i<=n-1;i++)
          for (j=k;j<=n-1;j++)
            { t=fabs(a[i*n+j]);
              if (t>d) { d=t; js[k]=j; is=i;}
            }
        if (d+1.0==1.0) l=0;
        else
          { if (js[k]!=k)
              for (i=0;i<=n-1;i++)
                { p=i*n+k; q=i*n+js[k];
                  t=a[p]; a[p]=a[q]; a[q]=t;
                }
            if (is!=k)
              { for (j=k;j<=n-1;j++)
                  { p=k*n+j; q=is*n+j;
                    t=a[p]; a[p]=a[q]; a[q]=t;
                  }
                for (j=0;j<=m-1;j++)
                  { p=k*m+j; q=is*m+j;
                    t=b[p]; b[p]=b[q]; b[q]=t;
                  }
              }
          }
        if (l==0)
          { free(js); printf("fail\n");
            return(0);
          }
        d=a[k*n+k];
        for (j=k+1;j<=n-1;j++)
          { p=k*n+j; a[p]=a[p]/d;}
        for (j=0;j<=m-1;j++)
          { p=k*m+j; b[p]=b[p]/d;}
        for (j=k+1;j<=n-1;j++)
          for (i=0;i<=n-1;i++)
            { p=i*n+j;
              if (i!=k)
                a[p]=a[p]-a[i*n+k]*a[k*n+j];
            }
        for (j=0;j<=m-1;j++)
        for (i=0;i<=n-1;i++)
          { p=i*m+j;
            if (i!=k)
              b[p]=b[p]-a[i*n+k]*b[k*m+j];
          }
      }
    for (k=n-1;k>=0;k--)
      if (js[k]!=k)
        for (j=0;j<=m-1;j++)
          { p=k*m+j; q=js[k]*m+j;
            t=b[p]; b[p]=b[q]; b[q]=t;
          }
    free(js);
    return(1);
}

//求解对称正定方程组的平方根法Cholesky
int achol(double *a,int n,int m,double *d)
{ 
    int i,j,k,u,v;
    if ((a[0]+1.0==1.0)||(a[0]<0.0))
      { printf("fail\n"); return(-2);}
    a[0]=sqrt(a[0]);
    for (j=1; j<=n-1; j++) a[j]=a[j]/a[0];
    for (i=1; i<=n-1; i++)
      { u=i*n+i;
        for (j=1; j<=i; j++)
          { v=(j-1)*n+i;
            a[u]=a[u]-a[v]*a[v];
          }
        if ((a[u]+1.0==1.0)||(a[u]<0.0))
          { printf("fail\n"); return(-2);}
        a[u]=sqrt(a[u]);
        if (i!=(n-1))
          { for (j=i+1; j<=n-1; j++)
              { v=i*n+j;
                for (k=1; k<=i; k++)
                  a[v]=a[v]-a[(k-1)*n+i]*a[(k-1)*n+j];
                a[v]=a[v]/a[u];
              }
          }
      }
    for (j=0; j<=m-1; j++)
      { d[j]=d[j]/a[0];
        for (i=1; i<=n-1; i++)
          { u=i*n+i; v=i*m+j;
            for (k=1; k<=i; k++)
              d[v]=d[v]-a[(k-1)*n+i]*d[(k-1)*m+j];
            d[v]=d[v]/a[u];
          }
      }
    for (j=0; j<=m-1; j++)
      { u=(n-1)*m+j;
        d[u]=d[u]/a[n*n-1];
        for (k=n-1; k>=1; k--)
          { u=(k-1)*m+j;
            for (i=k; i<=n-1; i++)
              { v=(k-1)*n+i;
                d[u]=d[u]-a[v]*d[i*m+j];
              }
            v=(k-1)*n+k-1;
            d[u]=d[u]/a[v];
          }
      }
    return(2);
}

//复系数方程组全选主元高斯消去法
int acgas(double *ar,double *ai,int n,double *br,double *bi)
{ 
    int *js,l,k,i,j,is,u,v;
    double p,q,s,d;
    js=(int*)malloc(n*sizeof(int));
    for (k=0;k<=n-2;k++)
      { d=0.0;
        for (i=k;i<=n-1;i++)
        for (j=k;j<=n-1;j++)
          { u=i*n+j;
            p=ar[u]*ar[u]+ai[u]*ai[u];
            if (p>d) {d=p;js[k]=j;is=i;}
          }
        if (d+1.0==1.0)
          { free(js); printf("err**fail\n");
            return(0);
          }
        if (is!=k)
          { for (j=k;j<=n-1;j++)
              { u=k*n+j; v=is*n+j;
                p=ar[u]; ar[u]=ar[v]; ar[v]=p;
                p=ai[u]; ai[u]=ai[v]; ai[v]=p;
              }
            p=br[k]; br[k]=br[is]; br[is]=p;
            p=bi[k]; bi[k]=bi[is]; bi[is]=p;
          }
        if (js[k]!=k)
          for (i=0;i<=n-1;i++)
            { u=i*n+k; v=i*n+js[k];
              p=ar[u]; ar[u]=ar[v]; ar[v]=p;
              p=ai[u]; ai[u]=ai[v]; ai[v]=p;
            }
        v=k*n+k;
        for (j=k+1;j<=n-1;j++)
          { u=k*n+j;
            p=ar[u]*ar[v]; q=-ai[u]*ai[v];
            s=(ar[v]-ai[v])*(ar[u]+ai[u]);
            ar[u]=(p-q)/d; ai[u]=(s-p-q)/d;
          }
        p=br[k]*ar[v]; q=-bi[k]*ai[v];
        s=(ar[v]-ai[v])*(br[k]+bi[k]);
        br[k]=(p-q)/d; bi[k]=(s-p-q)/d;
        for (i=k+1;i<=n-1;i++)
          { u=i*n+k;
            for (j=k+1;j<=n-1;j++)
              { v=k*n+j; l=i*n+j;
                p=ar[u]*ar[v]; q=ai[u]*ai[v];
                s=(ar[u]+ai[u])*(ar[v]+ai[v]);
                ar[l]=ar[l]-p+q;
                ai[l]=ai[l]-s+p+q;
              }
            p=ar[u]*br[k]; q=ai[u]*bi[k];
            s=(ar[u]+ai[u])*(br[k]+bi[k]);
            br[i]=br[i]-p+q; bi[i]=bi[i]-s+p+q;
          }
      }
    u=(n-1)*n+n-1;
    d=ar[u]*ar[u]+ai[u]*ai[u];
    if (d+1.0==1.0)
      { free(js); printf("err**fail\n");
        return(0);
      }
    p=ar[u]*br[n-1]; q=-ai[u]*bi[n-1];
    s=(ar[u]-ai[u])*(br[n-1]+bi[n-1]);
    br[n-1]=(p-q)/d; bi[n-1]=(s-p-q)/d;
    for (i=n-2;i>=0;i--)
    for (j=i+1;j<=n-1;j++)
      { u=i*n+j;
        p=ar[u]*br[j]; q=ai[u]*bi[j];
        s=(ar[u]+ai[u])*(br[j]+bi[j]);
        br[i]=br[i]-p+q;
        bi[i]=bi[i]-s+p+q;
      }
    js[n-1]=n-1;
    for (k=n-1;k>=0;k--)
      if (js[k]!=k)
        { p=br[k]; br[k]=br[js[k]]; br[js[k]]=p;
          p=bi[k]; bi[k]=bi[js[k]]; bi[js[k]]=p;
        }
    free(js);
    return(1);
}  

//复系数方程组全选主元高斯约当消去法
int acjdn(double *ar,double *ai,double *br,double *bi,int n,int m)
{ 
    int *js,l,k,i,j,is,u,v;
    double p,q,s,d;
    js=(int*)malloc(n*sizeof(int));
    for (k=0;k<=n-1;k++)
      { d=0.0;
        for (i=k;i<=n-1;i++)
        for (j=k;j<=n-1;j++)
          { u=i*n+j;
            p=ar[u]*ar[u]+ai[u]*ai[u];
            if (p>d) {d=p;js[k]=j;is=i;}
          }
        if (d+1.0==1.0)
          { free(js); printf("err**fail\n");
            return(0);
          }
        if (is!=k)
          { for (j=k;j<=n-1;j++)
              { u=k*n+j; v=is*n+j;
                p=ar[u]; ar[u]=ar[v]; ar[v]=p;
                p=ai[u]; ai[u]=ai[v]; ai[v]=p;
              }
            for (j=0;j<=m-1;j++)
              { u=k*m+j; v=is*m+j;
                p=br[u]; br[u]=br[v]; br[v]=p;
                p=bi[u]; bi[u]=bi[v]; bi[v]=p;
              }
          }
        if (js[k]!=k)
          for (i=0;i<=n-1;i++)
            { u=i*n+k; v=i*n+js[k];
              p=ar[u]; ar[u]=ar[v]; ar[v]=p;
              p=ai[u]; ai[u]=ai[v]; ai[v]=p;
            }
        v=k*n+k;
        for (j=k+1;j<=n-1;j++)
          { u=k*n+j;
            p=ar[u]*ar[v]; q=-ai[u]*ai[v];
            s=(ar[v]-ai[v])*(ar[u]+ai[u]);
            ar[u]=(p-q)/d; ai[u]=(s-p-q)/d;
          }
        for (j=0;j<=m-1;j++)
          { u=k*m+j;
            p=br[u]*ar[v]; q=-bi[u]*ai[v];
            s=(ar[v]-ai[v])*(br[u]+bi[u]);
            br[u]=(p-q)/d; bi[u]=(s-p-q)/d;
          }
        for (i=0;i<=n-1;i++)
          if (i!=k)
            { u=i*n+k;
              for (j=k+1;j<=n-1;j++)
                { v=k*n+j; l=i*n+j;
                  p=ar[u]*ar[v]; q=ai[u]*ai[v];
                  s=(ar[u]+ai[u])*(ar[v]+ai[v]);
                  ar[l]=ar[l]-p+q;
                  ai[l]=ai[l]-s+p+q;
                }
              for (j=0;j<=m-1;j++)
                { l=i*m+j; v=k*m+j;
                  p=ar[u]*br[v]; q=ai[u]*bi[v];
                  s=(ar[u]+ai[u])*(br[v]+bi[v]);
                  br[l]=br[l]-p+q; bi[l]=bi[l]-s+p+q;
                }
            }
      }
    for (k=n-1;k>=0;k--)
      if (js[k]!=k)
        for (j=0;j<=m-1;j++)
          { u=k*m+j;v=js[k]*m+j;
            p=br[u]; br[u]=br[v]; br[v]=p;
            p=bi[u]; bi[u]=bi[v]; bi[v]=p;
          }
    free(js);
    return(1);
}

//一般带型方程的求解--**例子程序有溢出,解的值就为零!** 
int aband(double *b,double *d,int n,int l,int il,int m)
{ 
    int ls,k,i,j,is,u,v;
    double p,t;
    if (il!=(2*l+1))
      { printf("fail\n"); return(-2);}
    ls=l;
    for (k=0;k<=n-2;k++)
      { p=0.0;
        for (i=k;i<=ls;i++)
          { t=fabs(b[i*il]);
            if (t>p) {p=t; is=i;}
          }
        if (p+1.0==1.0)
          { printf("fail\n"); return(0);}
        for (j=0;j<=m-1;j++)
          { u=k*m+j; v=is*m+j;
            t=d[u]; d[u]=d[v]; d[v]=t;
          }
        for (j=0;j<=il-1;j++)
          { u=k*il+j; v=is*il+j;
            t=b[u]; b[u]=b[v]; b[v]=t;
          }
        for (j=0;j<=m-1;j++)
          { u=k*m+j; d[u]=d[u]/b[k*il];}
        for (j=1;j<=il-1;j++)
          { u=k*il+j; b[u]=b[u]/b[k*il];}
        for (i=k+1;i<=ls;i++)
          { t=b[i*il];
            for (j=0;j<=m-1;j++)
              { u=i*m+j; v=k*m+j;
                d[u]=d[u]-t*d[v];
              }
            for (j=1;j<=il-1;j++)
              { u=i*il+j; v=k*il+j;
                b[u-1]=b[u]-t*b[v];
              }
            u=i*il+il-1; b[u]=0.0;
          }
        if (ls!=(n-1)) ls=ls+1;
      }
    p=b[(n-1)*il];
    if (fabs(p)+1.0==1.0)
      { printf("fail\n"); return(0);}
    for (j=0;j<=m-1;j++)
      { u=(n-1)*m+j; d[u]=d[u]/p;}
    ls=1;
    for (i=n-2;i>=0;i--)
      { for (k=0;k<=m-1;k++)
          { u=i*m+k;
            for (j=1;j<=ls;j++)
              { v=i*il+j; is=(i+j)*m+k;
                d[u]=d[u]-b[v]*d[is];
              }
          }
        if (ls!=(il-1)) ls=ls+1;
      }
    return(2);
}

//高斯-赛德尔迭代法
int agsdl(double *a,double *b,int n,double *x,double eps)
{ 
    int i,j,u,v;
    double p,t,s,q;
    for (i=0; i<=n-1; i++)
      { u=i*n+i; p=0.0; x[i]=0.0;
        for (j=0; j<=n-1; j++)
          if (i!=j)
            { v=i*n+j; p=p+fabs(a[v]);}
        if (p>=fabs(a[u]))
          { printf("fail\n"); return(-1);}
      }
    p=eps+1.0;
    while (p>=eps)
      { p=0.0;
        for (i=0; i<=n-1; i++)
          { t=x[i]; s=0.0;
            for (j=0; j<=n-1; j++)
              if (j!=i) s=s+a[i*n+j]*x[j];
            x[i]=(b[i]-s)/a[i*n+i];
            q=fabs(x[i]-t)/(1.0+fabs(x[i]));
            if (q>p) p=q;
          }
      }
    return(1);
}

//求解对称方程组的分解法
int aldle(double *a,int n,int m,double *c)
{ 
    int i,j,l,k,u,v,w,k1,k2,k3;
    double p;
    if (fabs(a[0])+1.0==1.0)
      { printf("fail\n"); return(-2);}
    for (i=1; i<=n-1; i++)
      { u=i*n; a[u]=a[u]/a[0];}
    for (i=1; i<=n-2; i++)
      { u=i*n+i;
        for (j=1; j<=i; j++)
          { v=i*n+j-1; l=(j-1)*n+j-1;
            a[u]=a[u]-a[v]*a[v]*a[l];
          }
        p=a[u];
        if (fabs(p)+1.0==1.0)
          { printf("fail\n"); return(-2);}
        for (k=i+1; k<=n-1; k++)
          { u=k*n+i;
            for (j=1; j<=i; j++)
              { v=k*n+j-1; l=i*n+j-1; w=(j-1)*n+j-1;
		a[u]=a[u]-a[v]*a[l]*a[w];
              }
            a[u]=a[u]/p;
          }
      }
    u=n*n-1;
    for (j=1; j<=n-1; j++)
      { v=(n-1)*n+j-1; w=(j-1)*n+j-1;
        a[u]=a[u]-a[v]*a[v]*a[w];
      }
    p=a[u];
    if (fabs(p)+1.0==1.0)
      { printf("fail\n"); return(-2);}
    for (j=0; j<=m-1; j++)
    for (i=1; i<=n-1; i++)
      { u=i*m+j;
        for (k=1; k<=i; k++)
          { v=i*n+k-1; w=(k-1)*m+j;
            c[u]=c[u]-a[v]*c[w];
          }
      }
    for (i=1; i<=n-1; i++)
      { u=(i-1)*n+i-1;
        for (j=i; j<=n-1; j++)
          { v=(i-1)*n+j; w=j*n+i-1;
            a[v]=a[u]*a[w];
          }
      }
    for (j=0; j<=m-1; j++)
      { u=(n-1)*m+j;
        c[u]=c[u]/p;
        for (k=1; k<=n-1; k++)
          { k1=n-k; k3=k1-1; u=k3*m+j;
            for (k2=k1; k2<=n-1; k2++)
              { v=k3*n+k2; w=k2*m+j;
                c[u]=c[u]-a[v]*c[w];
              }
            c[u]=c[u]/a[k3*n+k3];
          }
      }
    return(2);
}

//求解托伯利兹方程组的列文方法 
int atlvs(double *t,int n,double *b,double *x)
{ 
    int i,j,k;
    double a,beta,q,c,h,*y,*s;
    s=(double*)malloc(n*sizeof(double));
    y=(double*)malloc(n*sizeof(double));
    a=t[0];
    if (fabs(a)+1.0==1.0)
      { free(s); free(y); printf("fail\n"); return(-1);}
    y[0]=1.0; x[0]=b[0]/a;
    for (k=1; k<=n-1; k++)
      { beta=0.0; q=0.0;
        for (j=0; j<=k-1; j++)
          { beta=beta+y[j]*t[j+1];
            q=q+x[j]*t[k-j];
          }
        if (fabs(a)+1.0==1.0)
          { free(s); free(y); printf("fail\n"); return(-1);}
        c=-beta/a; s[0]=c*y[k-1]; y[k]=y[k-1];
        if (k!=1)
          for (i=1; i<=k-1; i++)
            s[i]=y[i-1]+c*y[k-i-1];
        a=a+c*beta;
        if (fabs(a)+1.0==1.0)
          { free(s); free(y); printf("fail\n"); return(-1);}
        h=(b[k]-q)/a;
        for (i=0; i<=k-1; i++)
          { x[i]=x[i]+h*s[i]; y[i]=s[i];}
        x[k]=h*y[k];
      }
    free(s); free(y);
    return(1);
}

//三对角线方程的追赶法
int atrde(double *b,int n,int m,double *d)
{   
    int k,j;
    double s;
    if (m!=(3*n-2))
      { printf("err\n"); return(-2);}
    for (k=0;k<=n-2;k++)
      { j=3*k; s=b[j];
        if (fabs(s)+1.0==1.0)
          { printf("fail\n"); return(0);}
        b[j+1]=b[j+1]/s;
        d[k]=d[k]/s;
        b[j+3]=b[j+3]-b[j+2]*b[j+1];
        d[k+1]=d[k+1]-b[j+2]*d[k];
      }
    s=b[3*n-3];
    if (fabs(s)+1.0==1.0)
      { printf("fail\n"); return(0);}
    d[n-1]=d[n-1]/s;
    for (k=n-2;k>=0;k--)
      d[k]=d[k]-b[3*k+1]*d[k+1];
    return(2);
}
  
int main(int argc, char* argv[])
{
	typedef int (*pR)(double *a,double *b,int n);
	pR R[]={agaus,aggje};
	const char *szNameR[]={"全选主元高斯消去法","全选主元高斯-约当消去法"};
	int nR=sizeof(szNameR)/sizeof(szNameR[0]);
	{
		static double a[4][4]={
			{0.2368,0.2471,0.2568,1.2671},
			{0.1968,0.2071,1.2168,0.2271},
			{0.1581,1.1675,0.1768,0.1871},
			{1.1161,0.1254,0.1397,0.1490}
			};
		static double b[4]={1.8471,1.7471,1.6471,1.5471};
		for (int i=0;i<nR;i++)
		{
			int ret=R[i](&a[0][0],&b[0],4);
			const char *szRet=(ret!=0?"成功":"失败");
			printf("%s解实系数线性方程组%s:x=[%e,%e,%e,%e]\n",szNameR[i],szRet,b[0],b[1],b[2],b[3]);
		}
	}
	{
		static double a[8][8]={ 
		                 {0.0,0.0,-1.0,0.0,0.0,0.0,2.0,0.0},
                         {0.0,6.0,0.0,0.0,0.0,-6.0,0.0,0.0},
                         {0.0,0.0,0.0,2.0,0.0,0.0,0.0,-4.0},
                         {3.0,0.0,0.0,0.0,-2.0,0.0,1.0,0.0},
                         {0.0,0.0,6.0,0.0,0.0,0.0,5.0,0.0},
                         {1.0,0.0,0.0,0.0,-3.0,0.0,0.0,2.0},
                         {0.0,4.0,0.0,-1.0,0.0,0.0,0.0,0.0},
                         {0.0,0.0,1.0,0.0,-1.0,0.0,0.0,-2.0}
						 };
		static double b[8]={4.0,6.0,-8.0,-2.0,27.0,-9.0,2.0,-4.0};
		for (int i=0;i<nR;i++)
		{
			int ret=R[i](&a[0][0],&b[0],8);
			const char *szRet=(ret!=0?"成功":"失败");
			printf("%s解实系数线性方程组%s:x=[%e,%e,%e,%e,%e,%e,%e,%e]\n",szNameR[i],szRet,b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7]);
		}
	}	
	{
		static double a[4][4]={ 
		                    {1.0,3.0,2.0,13.0},
                            {7.0,2.0,1.0,-2.0},
                            {9.0,15.0,3.0,-2.0},
                            {-2.0,-2.0,11.0,5.0}
							};
		static double b[4][2]={
			                {9.0,0.0},
							{6.0,4.0},
                            {11.0,7.0},
							{-2.0,-1.0}
							};
    if (agjdn(&a[0][0],&b[0][0],4,2)!=0)
      for (int i=0;i<4;i++)
        printf("x(%d)=%13.7e,  %13.7e\n",i,b[i][0],b[i][1]);		
	}
    { 
		static double a[4][4]={ 
		                  {5.0,7.0,6.0,5.0},
		                  {7.0,10.0,8.0,7.0},
						  {6.0,8.0,10.0,9.0},
						  {5.0,7.0,9.0,10.0}
						};
		static double d[4][2]={
							{23.0,0},
							{32.0,0},
							{33.0,0},
							{31.0,0}
						};
		if (achol(&a[0][0],4,2,&d[0][0])>0)
		  for (int i=0; i<4; i++)
			printf("x(%d)=%13.7e,   %13.7e\n",i,d[i][0],d[i][1]);
    }
	{
	static double ar[4][4]={ 
	                         {1.0,3.0,2.0,13.0},
							 {7.0,2.0,1.0,-2.0},
							 {9.0,15.0,3.0,-2.0},
							 {-2.0,-2.0,11.0,5.0}
						   };
	static double ai[4][4]={ 
	                         {3.0,-2.0,1.0,6.0},
							 {-2.0,7.0,5.0,8.0},
							 {9.0,-3.0,15.0,1.0},
							 {-2.0,-2.0,7.0,6.0}
						   };
	static double br[4]={2.0,7.0,3.0,9.0};
	static double bi[4]={1.0,2.0,-2.0,3.0};
	if (acgas(&ar[0][0],&ai[0][0],4,&br[0],&bi[0])!=0)
	  for (int i=0;i<4;i++)
		printf("b(%d)=%13.7e  +j %13.7e\n",i,br[i],bi[i]);
	}
	{
    static double ar[4][4]={ {1.0,3.0,2.0,13.0},
                             {7.0,2.0,1.0,-2.0},
                             {9.0,15.0,3.0,-2.0},
                             {-2.0,-2.0,11.0,5.0}};
    static double ai[4][4]={ {3.0,-2.0,1.0,6.0},
                             {-2.0,7.0,5.0,8.0},
                             {9.0,-3.0,15.0,1.0},
                             {-2.0,-2.0,7.0,6.0}};
    static double br[4][2]={ {2.0,-2.0},{7.0,3.0},
                             {3.0,2.0},{9.0,1.0}};
    static double bi[4][2]={ {1.0,3.0},{2.0,7.0},
                             {-2.0,9.0},{3.0,2.0}};
    if (acjdn(&ar[0][0],&ai[0][0],&br[0][0],&bi[0][0],4,2)!=0)
      for (int i=0;i<4;i++)
        printf("x(%d)=%13.7e +j %13.7e,   %13.7e +j %13.7e\n",
               i,br[i][0],bi[i][0],br[i][1],bi[i][1]);
	}
	{ 
		static double b[13]={13.0,12.0,11.0,10.0,9.0,8.0,7.0,
							 6.0,5.0,4.0,3.0,2.0,1.0};
		static double d[5]={3.0,0.0,-2.0,6.0,8.0};
		if (atrde(&b[0],5,13,&d[0])>0)
		  for (int i=0;i<5;i++)
			printf("x(%d)=%13.7e\n",i,d[i]);
	}	
	{
		static double x[6];
		static double t[6]={6.0,5.0,4.0,3.0,2.0,1.0};
		static double b[6]={11.0,9.0,9.0,9.0,13.0,17.0};
		if (atlvs(&t[0],6,&b[0],&x[0])>0)
		  for (int i=0; i<6; i++)
			printf("x(%d)=%13.7e\n",i,x[i]);
	}	
	{
		static double a[5][5]={ {5.0,7.0,6.0,5.0,1.0},
			   {7.0,10.0,8.0,7.0,2.0},{6.0,8.0,10.0,9.0,3.0},
			   {5.0,7.0,9.0,10.0,4.0},{1.0,2.0,3.0,4.0,5.0}};
		static double c[5][2]={ {24.0,96.0},{34.0,136.0},
			   {36.0,144.0},{35.0,140.0},{15.0,60.0}};
		if (aldle(&a[0][0],5,2,&c[0][0])>0)
		  for (int i=0; i<5; i++)
			printf("x(%d)=%13.7e,   %13.7e\n",i,c[i][0],c[i][1]);
	}	
	{
		double eps;
		static double a[4][4]={ {7.0,2.0,1.0,-2.0},{9.0,15.0,3.0,-2.0},
							  {-2.0,-2.0,11.0,5.0},{1.0,3.0,2.0,13.0}};
		static double x[5],b[4]={4.0,7.0,-1.0,0.0};
		eps=0.000001;
		if (agsdl(&a[0][0],&b[0],4,&x[0],eps)>0)
		  for (int i=0;i<4; i++)
			printf("x(%d)=%13.7e\n",i,x[i]);
	}	
	{
		static double b[8][5]={ {3.0,-4.0,1.0,0.0,0.0},
		{-2.0,-5.0,6.0,1.0,0.0},{1.0,3.0,-1.0,2.0,-3.0},
		{2.0,5.0,-5.0,6.0,-1.0},{-3.0,1.0,-1.0,2.0,-5.0},
		{6.0,1.0,-3.0,2.0,-9.0},{-4.0,1.0,-1.0,2.0,0.0},
		{5.0,1.0,-7.0,0.0,0.0}};
		static double d[8][3]={ {13.0,29.0,-13.0},
		{-6.0,17.0,-21.0},{-31.0,-6.0,4.0},{64.0,3.0,16.0},
		{-20.0,1.0,-5.0},{-22.0,-41.0,56.0},{-29.0,10.0,-21.0},
		{7.0,-24.0,20.0}};
		if (aband(&b[0][0],&d[0][0],8,2,5,3)>0)
		  for (int i=0;i<8;i++)
		  printf("x(%d)=%13.7e,  %13.7e,  %13.7e\n",
				i,d[i][0],d[i][1],d[i][2]);
	  }	
	return 0;
}

