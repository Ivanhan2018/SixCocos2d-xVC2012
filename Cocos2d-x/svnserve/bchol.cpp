#include <math.h>
#include <stdio.h>

//对称正定矩阵的乔里斯基分解与行列式的求值
int bchol(double *a,int n,double *det)
  { int i,j,k,u,v,l;
    double d;
    if ((a[0]+1.0==1.0)||(a[0]<0.0))
      { printf("fail\n"); return(-2);}
    a[0]=sqrt(a[0]);
    d=a[0];
    for (i=1; i<=n-1; i++)
      { u=i*n; a[u]=a[u]/a[0];}
    for (j=1; j<=n-1; j++)
      { l=j*n+j;
        for (k=0; k<=j-1; k++)
          { u=j*n+k; a[l]=a[l]-a[u]*a[u];}
        if ((a[l]+1.0==1.0)||(a[l]<0.0))
          { printf("fail\n"); return(-2);}
        a[l]=sqrt(a[l]);
        d=d*a[l];
        for (i=j+1; i<=n-1; i++)
          { u=i*n+j;
            for (k=0; k<=j-1; k++)
              a[u]=a[u]-a[i*n+k]*a[j*n+k];
            a[u]=a[u]/a[l];
          }
      }
    *det=d*d;
    for (i=0; i<=n-2; i++)
    for (j=i+1; j<=n-1; j++)
      a[i*n+j]=0.0;
    return(2);
  }

//复矩阵求逆的全选主元高斯约当法
int bcinv(double *ar,double *ai,int n)
  { int *is,*js,i,j,k,l,u,v,w;
    double p,q,s,t,d,b;
    is=(int *)malloc(n*sizeof(int));
    js=(int *)malloc(n*sizeof(int));
    for (k=0; k<=n-1; k++)
      { d=0.0;
        for (i=k; i<=n-1; i++)
        for (j=k; j<=n-1; j++)
          { u=i*n+j;
            p=ar[u]*ar[u]+ai[u]*ai[u];
            if (p>d) { d=p; is[k]=i; js[k]=j;}
          }
        if (d+1.0==1.0)
          { free(is); free(js); printf("err**not inv\n");
            return(0);
          }
        if (is[k]!=k)
          for (j=0; j<=n-1; j++)
            { u=k*n+j; v=is[k]*n+j;
              t=ar[u]; ar[u]=ar[v]; ar[v]=t;
              t=ai[u]; ai[u]=ai[v]; ai[v]=t;
            }
        if (js[k]!=k)
          for (i=0; i<=n-1; i++)
            { u=i*n+k; v=i*n+js[k];
              t=ar[u]; ar[u]=ar[v]; ar[v]=t;
              t=ai[u]; ai[u]=ai[v]; ai[v]=t;
            }
        l=k*n+k;
        ar[l]=ar[l]/d; ai[l]=-ai[l]/d;
        for (j=0; j<=n-1; j++)
          if (j!=k)
            { u=k*n+j;
              p=ar[u]*ar[l]; q=ai[u]*ai[l];
              s=(ar[u]+ai[u])*(ar[l]+ai[l]);
              ar[u]=p-q; ai[u]=s-p-q;
            }
        for (i=0; i<=n-1; i++)
          if (i!=k)
            { v=i*n+k;
              for (j=0; j<=n-1; j++)
                if (j!=k)
                  { u=k*n+j;  w=i*n+j;
                    p=ar[u]*ar[v]; q=ai[u]*ai[v];
                    s=(ar[u]+ai[u])*(ar[v]+ai[v]);
                    t=p-q; b=s-p-q;
                    ar[w]=ar[w]-t;
                    ai[w]=ai[w]-b;
                  }
            }
        for (i=0; i<=n-1; i++)
          if (i!=k)
            { u=i*n+k;
              p=ar[u]*ar[l]; q=ai[u]*ai[l];
              s=(ar[u]+ai[u])*(ar[l]+ai[l]);
              ar[u]=q-p; ai[u]=p+q-s;
            }
      }
    for (k=n-1; k>=0; k--)
      { if (js[k]!=k)
          for (j=0; j<=n-1; j++)
            { u=k*n+j; v=js[k]*n+j;
              t=ar[u]; ar[u]=ar[v]; ar[v]=t;
              t=ai[u]; ai[u]=ai[v]; ai[v]=t;
            }
        if (is[k]!=k)
          for (i=0; i<=n-1; i++)
            { u=i*n+k; v=i*n+is[k];
              t=ar[u]; ar[u]=ar[v]; ar[v]=t;
              t=ai[u]; ai[u]=ai[v]; ai[v]=t;
            }
      }
    free(is); free(js);
    return(1);
  }

//复矩阵相乘
void bcmul(double *ar,double *ai,double *br,double *bi,int m,int n,int k,double *cr,double *ci)
  { int i,j,l,u,v,w;
    double p,q,s;
    for (i=0; i<=m-1; i++)
    for (j=0; j<=k-1; j++)
      { u=i*k+j;
        cr[u]=0.0; ci[u]=0.0;
        for (l=0; l<=n-1; l++)
          { v=i*n+l; w=l*k+j;
            p=ar[v]*br[w];
            q=ai[v]*bi[w];
            s=(ar[v]+ai[v])*(br[w]+bi[w]);
            cr[u]=cr[u]+p-q;
            ci[u]=ci[u]+s-p-q;
          }
      }
    return;
  }

//矩阵的三角分解
int blluu(double *a,int n,double *l,double *u)
    { int i,j,k,w,v,ll;
    for (k=0; k<=n-2; k++)
      { ll=k*n+k;
	if (fabs(a[ll])+1.0==1.0)
          { printf("fail\n"); return(0);}
        for (i=k+1; i<=n-1; i++)
	  { w=i*n+k; a[w]=a[w]/a[ll];}
        for (i=k+1; i<=n-1; i++)
          { w=i*n+k;
            for (j=k+1; j<=n-1; j++)
              { v=i*n+j;
                a[v]=a[v]-a[w]*a[k*n+j];
              }
          }
      }
    for (i=0; i<=n-1; i++)
      { for (j=0; j<i; j++)
          { w=i*n+j; l[w]=a[w]; u[w]=0.0;}
        w=i*n+i;
        l[w]=1.0; u[w]=a[w];
        for (j=i+1; j<=n-1; j++)
          { w=i*n+j; l[w]=0.0; u[w]=a[w];}
      }
    return(1);
  }

//一般实矩阵的QR分解
int bmaqr(double *a,int m,int n,double *q)
    { int i,j,k,l,nn,p,jj;
    double u,alpha,w,t;
    if (m<n)
      { printf("fail\n"); return(0);}
    for (i=0; i<=m-1; i++)
    for (j=0; j<=m-1; j++)
      { l=i*m+j; q[l]=0.0;
        if (i==j) q[l]=1.0;
      }
    nn=n;
    if (m==n) nn=m-1;
    for (k=0; k<=nn-1; k++)
      { u=0.0; l=k*n+k;
        for (i=k; i<=m-1; i++)
          { w=fabs(a[i*n+k]);
            if (w>u) u=w;
          }
        alpha=0.0;
        for (i=k; i<=m-1; i++)
          { t=a[i*n+k]/u; alpha=alpha+t*t;}
        if (a[l]>0.0) u=-u;
        alpha=u*sqrt(alpha);
        if (fabs(alpha)+1.0==1.0)
          { printf("fail\n"); return(0);}
        u=sqrt(2.0*alpha*(alpha-a[l]));
        if ((u+1.0)!=1.0)
          { a[l]=(a[l]-alpha)/u;
            for (i=k+1; i<=m-1; i++)
              { p=i*n+k; a[p]=a[p]/u;}
            for (j=0; j<=m-1; j++)
              { t=0.0;
                for (jj=k; jj<=m-1; jj++)
                  t=t+a[jj*n+k]*q[jj*m+j];
                for (i=k; i<=m-1; i++)
                  { p=i*m+j; q[p]=q[p]-2.0*t*a[i*n+k];}
              }
            for (j=k+1; j<=n-1; j++)
              { t=0.0;
                for (jj=k; jj<=m-1; jj++)
                  t=t+a[jj*n+k]*a[jj*n+j];
                for (i=k; i<=m-1; i++)
                  { p=i*n+j; a[p]=a[p]-2.0*t*a[i*n+k];}
              }
            a[l]=alpha;
            for (i=k+1; i<=m-1; i++)
              a[i*n+k]=0.0;
          }
      }
    for (i=0; i<=m-2; i++)
    for (j=i+1; j<=m-1;j++)
      { p=i*m+j; l=j*m+i;
        t=q[p]; q[p]=q[l]; q[l]=t;
      }
    return(1);
  }

//求矩阵秩的全选主元高斯消去法 
int brank(double *a,int m,int n)
  { int i,j,k,nn,is,js,l,ll,u,v;
    double q,d;
    nn=m;
    if (m>=n) nn=n;
    k=0;
    for (l=0; l<=nn-1; l++)
      { q=0.0;
        for (i=l; i<=m-1; i++)
        for (j=l; j<=n-1; j++)
          { ll=i*n+j; d=fabs(a[ll]);
	    if (d>q) { q=d; is=i; js=j;}
          }
        if (q+1.0==1.0) return(k);
        k=k+1;
        if (is!=l)
          { for (j=l; j<=n-1; j++)
              { u=l*n+j; v=is*n+j;
                d=a[u]; a[u]=a[v]; a[v]=d;
              }
          }
        if (js!=l)
          { for (i=l; i<=m-1; i++)
              { u=i*n+js; v=i*n+l;
                d=a[u]; a[u]=a[v]; a[v]=d;
              }
          }
        ll=l*n+l;
        for (i=l+1; i<=n-1; i++)
          { d=a[i*n+l]/a[ll];
            for (j=l+1; j<=n-1; j++)
              { u=i*n+j;
                a[u]=a[u]-d*a[l*n+j];
              }
          }
      }
    return(k);
  }  
 
 //实矩阵相乘
 void brmul(double *a,double *b,int m,int n,int k,double *c)
  { int i,j,l,u;
    for (i=0; i<=m-1; i++)
    for (j=0; j<=k-1; j++)
      { u=i*k+j; c[u]=0.0;
        for (l=0; l<=n-1; l++)
          c[u]=c[u]+a[i*n+l]*b[l*k+j];
      }
    return;
  } 

//求行列式值的全选主元高斯消去法
double bsdet(double *a,int n)
  { int i,j,k,is,js,l,u,v;
    double f,det,q,d;
    f=1.0; det=1.0;
    for (k=0; k<=n-2; k++)
      { q=0.0;
        for (i=k; i<=n-1; i++)
        for (j=k; j<=n-1; j++)
          { l=i*n+j; d=fabs(a[l]);
	    if (d>q) { q=d; is=i; js=j;}
          }
        if (q+1.0==1.0)
          { det=0.0; return(det);}
        if (is!=k)
          { f=-f;
            for (j=k; j<=n-1; j++)
              { u=k*n+j; v=is*n+j;
                d=a[u]; a[u]=a[v]; a[v]=d;
              }
          }
        if (js!=k)
          { f=-f;
            for (i=k; i<=n-1; i++)
              { u=i*n+js; v=i*n+k;
                d=a[u]; a[u]=a[v]; a[v]=d;
              }
          }
        l=k*n+k;
        det=det*a[l];
        for (i=k+1; i<=n-1; i++)
          { d=a[i*n+k]/a[l];
            for (j=k+1; j<=n-1; j++)
              { u=i*n+j;
                a[u]=a[u]-d*a[k*n+j];
              }
          }
      }
    det=f*det*a[n*n-1];
    return(det);
  }
 
//对称正定矩阵的求逆
int bssgj(double *a,int n)
  { int i,j,k,m;
    double w,g,*b;
    b=(double*)malloc(n*sizeof(double));
    for (k=0; k<=n-1; k++)
      { w=a[0];
        if (fabs(w)+1.0==1.0)
          { free(b); printf("fail\n"); return(-2);}
        m=n-k-1;
        for (i=1; i<=n-1; i++)
          { g=a[i*n]; b[i]=g/w;
            if (i<=m) b[i]=-b[i];
            for (j=1; j<=i; j++)
              a[(i-1)*n+j-1]=a[i*n+j]+g*b[j];
          }
        a[n*n-1]=1.0/w;
        for (i=1; i<=n-1; i++)
          a[(n-1)*n+i-1]=b[i];
      }
    for (i=0; i<=n-2; i++)
    for (j=i+1; j<=n-1; j++)
      a[i*n+j]=a[j*n+i];
    free(b);
    return(2);
  }

//托伯利兹矩阵求逆的特兰持方法 
int btrch(double *t,double *tt,int n,double *b)
  { int i,j,k;
    double a,s,*c,*r,*p;
    c=(double*)malloc(n*sizeof(double));
    r=(double*)malloc(n*sizeof(double));
    p=(double*)malloc(n*sizeof(double));
    if (fabs(t[0])+1.0==1.0)
      { free(c); free(r); free(p);
        printf("fail\n"); return(-1);
      }
    a=t[0]; c[0]=tt[1]/t[0]; r[0]=t[1]/t[0];
    for (k=0; k<=n-3; k++)
      { s=0.0;
        for (j=1; j<=k+1; j++)
          s=s+c[k+1-j]*tt[j];
        s=(s-tt[k+2])/a;
	for (i=0; i<=k; i++)
          p[i]=c[i]+s*r[k-i];
        c[k+1]=-s;
        s=0.0;
        for (j=1; j<=k+1; j++)
          s=s+r[k+1-j]*t[j];
        s=(s-t[k+2])/a;
        for (i=0; i<=k; i++)
          { r[i]=r[i]+s*c[k-i];
            c[k-i]=p[k-i];
          }
        r[k+1]=-s;
	a=0.0;
        for (j=1; j<=k+2; j++)
          a=a+t[j]*c[j-1];
        a=t[0]-a;
        if (fabs(a)+1.0==1.0)
          { free(c); free(r); free(p);
            printf("fail\n"); return(-1);
          }
      }
    b[0]=1.0/a;
    for (i=0; i<=n-2; i++)
      { k=i+1; j=(i+1)*n;
        b[k]=-r[i]/a; b[j]=-c[i]/a;
      }
    for (i=0; i<=n-1; i++)
    for (j=0; j<=n-2; j++)
      { k=(i+1)*n+j+1;
        b[k]=b[i*n+j]-c[i]*b[j+1];
        b[k]=b[k]+c[n-j-2]*b[n-i-1];
      }
    free(c); free(r); free(p);
    return(1);
  }
  
//实矩阵求逆的全选主元高斯约当法
int brinv(double *a,int n)
  { int *is,*js,i,j,k,l,u,v;
    double d,p;
    is=(int*)malloc(n*sizeof(int));
    js=(int*)malloc(n*sizeof(int));
    for (k=0; k<=n-1; k++)
      { d=0.0;
        for (i=k; i<=n-1; i++)
        for (j=k; j<=n-1; j++)
          { l=i*n+j; p=fabs(a[l]);
            if (p>d) { d=p; is[k]=i; js[k]=j;}
          }
        if (d+1.0==1.0)
          { free(is); free(js); printf("err**not inv\n");
            return(0);
          }
        if (is[k]!=k)
          for (j=0; j<=n-1; j++)
            { u=k*n+j; v=is[k]*n+j;
              p=a[u]; a[u]=a[v]; a[v]=p;
            }
        if (js[k]!=k)
          for (i=0; i<=n-1; i++)
            { u=i*n+k; v=i*n+js[k];
              p=a[u]; a[u]=a[v]; a[v]=p;
            }
        l=k*n+k;
        a[l]=1.0/a[l];
        for (j=0; j<=n-1; j++)
          if (j!=k)
            { u=k*n+j; a[u]=a[u]*a[l];}
        for (i=0; i<=n-1; i++)
          if (i!=k)
            for (j=0; j<=n-1; j++)
              if (j!=k)
                { u=i*n+j;
                  a[u]=a[u]-a[i*n+k]*a[k*n+j];
                }
        for (i=0; i<=n-1; i++)
          if (i!=k)
            { u=i*n+k; a[u]=-a[u]*a[l];}
      }
    for (k=n-1; k>=0; k--)
      { if (js[k]!=k)
          for (j=0; j<=n-1; j++)
            { u=k*n+j; v=js[k]*n+j;
              p=a[u]; a[u]=a[v]; a[v]=p;
            }
        if (is[k]!=k)
          for (i=0; i<=n-1; i++)
            { u=i*n+k; v=i*n+is[k];
              p=a[u]; a[u]=a[v]; a[v]=p;
            }
      }
    free(is); free(js);
    return(1);
  }
  
//约化一般实矩阵为赫申伯格矩阵的初等相似变换法
void chhbg(double *a,int n)
  { int i,j,k,u,v;
    double d,t;
    for (k=1; k<=n-2; k++)
      { d=0.0;
        for (j=k; j<=n-1; j++)
          { u=j*n+k-1; t=a[u];
            if (fabs(t)>fabs(d))
              { d=t; i=j;}
          }
        if (fabs(d)+1.0!=1.0)
          { if (i!=k)
              { for (j=k-1; j<=n-1; j++)
                  { u=i*n+j; v=k*n+j;
                    t=a[u]; a[u]=a[v]; a[v]=t;
                  }
                for (j=0; j<=n-1; j++)
                  { u=j*n+i; v=j*n+k;
                    t=a[u]; a[u]=a[v]; a[v]=t;
                  }
              }
            for (i=k+1; i<=n-1; i++)
              { u=i*n+k-1; t=a[u]/d; a[u]=0.0;
                for (j=k; j<=n-1; j++)
                  { v=i*n+j;
                    a[v]=a[v]-t*a[k*n+j];
                  }
                for (j=0; j<=n-1; j++)
                  { v=j*n+k;
                    a[v]=a[v]+t*a[j*n+i];
                  }
              }
          }
      }
    return;
  }
  
//求赫申伯格矩阵全部特征值的QR方法  
int chhqr(double *a,int n,double *u,double *v,double eps,int jt)
  { int m,it,i,j,k,l,ii,jj,kk,ll;
    double b,c,w,g,xy,p,q,r,x,s,e,f,z,y;
    it=0; m=n;
    while (m!=0)
      { l=m-1;
        while ((l>0)&&(fabs(a[l*n+l-1])>eps*
	      (fabs(a[(l-1)*n+l-1])+fabs(a[l*n+l])))) l=l-1;
        ii=(m-1)*n+m-1; jj=(m-1)*n+m-2;
        kk=(m-2)*n+m-1; ll=(m-2)*n+m-2;
        if (l==m-1)
          { u[m-1]=a[(m-1)*n+m-1]; v[m-1]=0.0;
            m=m-1; it=0;
          }
        else if (l==m-2)
          { b=-(a[ii]+a[ll]);
            c=a[ii]*a[ll]-a[jj]*a[kk];
            w=b*b-4.0*c;
            y=sqrt(fabs(w));
            if (w>0.0)
              { xy=1.0;
                if (b<0.0) xy=-1.0;
                u[m-1]=(-b-xy*y)/2.0;
                u[m-2]=c/u[m-1];
                v[m-1]=0.0; v[m-2]=0.0;
              }
            else
              { u[m-1]=-b/2.0; u[m-2]=u[m-1];
                v[m-1]=y/2.0; v[m-2]=-v[m-1];
              }
            m=m-2; it=0;
          }
        else
          { if (it>=jt)
              { printf("fail\n");
                return(-1);
              }
            it=it+1;
            for (j=l+2; j<=m-1; j++)
              a[j*n+j-2]=0.0;
            for (j=l+3; j<=m-1; j++)
              a[j*n+j-3]=0.0;
            for (k=l; k<=m-2; k++)
              { if (k!=l)
                  { p=a[k*n+k-1]; q=a[(k+1)*n+k-1];
                    r=0.0;
                    if (k!=m-2) r=a[(k+2)*n+k-1];
                  }
                else
                  { x=a[ii]+a[ll];
                    y=a[ll]*a[ii]-a[kk]*a[jj];
                    ii=l*n+l; jj=l*n+l+1;
                    kk=(l+1)*n+l; ll=(l+1)*n+l+1;
                    p=a[ii]*(a[ii]-x)+a[jj]*a[kk]+y;
                    q=a[kk]*(a[ii]+a[ll]-x);
                    r=a[kk]*a[(l+2)*n+l+1];
                  }
                if ((fabs(p)+fabs(q)+fabs(r))!=0.0)
                  { xy=1.0;
                    if (p<0.0) xy=-1.0;
                    s=xy*sqrt(p*p+q*q+r*r);
                    if (k!=l) a[k*n+k-1]=-s;
                    e=-q/s; f=-r/s; x=-p/s;
                    y=-x-f*r/(p+s);
                    g=e*r/(p+s);
                    z=-x-e*q/(p+s);
                    for (j=k; j<=m-1; j++)
                      { ii=k*n+j; jj=(k+1)*n+j;
                        p=x*a[ii]+e*a[jj];
                        q=e*a[ii]+y*a[jj];
                        r=f*a[ii]+g*a[jj];
                        if (k!=m-2)
                          { kk=(k+2)*n+j;
                            p=p+f*a[kk];
                            q=q+g*a[kk];
                            r=r+z*a[kk]; a[kk]=r;
                          }
                        a[jj]=q; a[ii]=p;
                      }
                    j=k+3;
                    if (j>=m-1) j=m-1;
                    for (i=l; i<=j; i++)
                      { ii=i*n+k; jj=i*n+k+1;
                        p=x*a[ii]+e*a[jj];
                        q=e*a[ii]+y*a[jj];
                        r=f*a[ii]+g*a[jj];
                        if (k!=m-2)
                          { kk=i*n+k+2;
                            p=p+f*a[kk];
                            q=q+g*a[kk];
                            r=r+z*a[kk]; a[kk]=r;
                          }
                        a[jj]=q; a[ii]=p;
                      }
                  }
              }
          }
      }
    return(1);
  }
  
//求实对称矩阵特征值与特征向量的雅可比法 
int cjcbi(double *a,int n,double *v,double eps,int jt)
  { int i,j,p,q,u,w,t,s,l;
    double fm,cn,sn,omega,x,y,d;
    l=1;
    for (i=0; i<=n-1; i++)
      { v[i*n+i]=1.0;
        for (j=0; j<=n-1; j++)
          if (i!=j) v[i*n+j]=0.0;
      }
    while (1==1)
      { fm=0.0;
        for (i=1; i<=n-1; i++)
        for (j=0; j<=i-1; j++)
          { d=fabs(a[i*n+j]);
            if ((i!=j)&&(d>fm))
              { fm=d; p=i; q=j;}
          }
        if (fm<eps)  return(1);
        if (l>jt)  return(-1);
        l=l+1;
        u=p*n+q; w=p*n+p; t=q*n+p; s=q*n+q;
        x=-a[u]; y=(a[s]-a[w])/2.0;
        omega=x/sqrt(x*x+y*y);
        if (y<0.0) omega=-omega;
        sn=1.0+sqrt(1.0-omega*omega);
        sn=omega/sqrt(2.0*sn);
        cn=sqrt(1.0-sn*sn);
        fm=a[w];
        a[w]=fm*cn*cn+a[s]*sn*sn+a[u]*omega;
        a[s]=fm*sn*sn+a[s]*cn*cn-a[u]*omega;
        a[u]=0.0; a[t]=0.0;
        for (j=0; j<=n-1; j++)
        if ((j!=p)&&(j!=q))
          { u=p*n+j; w=q*n+j;
            fm=a[u];
            a[u]=fm*cn+a[w]*sn;
            a[w]=-fm*sn+a[w]*cn;
          }
        for (i=0; i<=n-1; i++)
          if ((i!=p)&&(i!=q))
            { u=i*n+p; w=i*n+q;
              fm=a[u];
              a[u]=fm*cn+a[w]*sn;
              a[w]=-fm*sn+a[w]*cn;
            }
        for (i=0; i<=n-1; i++)
          { u=i*n+p; w=i*n+q;
            fm=v[u];
            v[u]=fm*cn+v[w]*sn;
            v[w]=-fm*sn+v[w]*cn;
          }
      }
    return(1);
  }
  
//求实对称矩阵特征值与特征向量的雅可比过关法 
void cjcbj(double *a,int n,double *v,double eps)
  { int i,j,p,q,u,w,t,s;
    double ff,fm,cn,sn,omega,x,y,d;
    for (i=0; i<=n-1; i++)
      { v[i*n+i]=1.0;
        for (j=0; j<=n-1; j++)
          if (i!=j) v[i*n+j]=0.0;
      }
    ff=0.0;
    for (i=1; i<=n-1; i++)
    for (j=0; j<=i-1; j++)
      { d=a[i*n+j]; ff=ff+d*d; }
    ff=sqrt(2.0*ff);
    loop0:
    ff=ff/(1.0*n);
    loop1:
        for (i=1; i<=n-1; i++)
        for (j=0; j<=i-1; j++)
          { d=fabs(a[i*n+j]);
            if (d>ff)
              { p=i; q=j;
                goto loop;
              }
          }
        if (ff<eps) return;
        goto loop0;
  loop: u=p*n+q; w=p*n+p; t=q*n+p; s=q*n+q;
        x=-a[u]; y=(a[s]-a[w])/2.0;
        omega=x/sqrt(x*x+y*y);
        if (y<0.0) omega=-omega;
        sn=1.0+sqrt(1.0-omega*omega);
        sn=omega/sqrt(2.0*sn);
        cn=sqrt(1.0-sn*sn);
        fm=a[w];
        a[w]=fm*cn*cn+a[s]*sn*sn+a[u]*omega;
        a[s]=fm*sn*sn+a[s]*cn*cn-a[u]*omega;
        a[u]=0.0; a[t]=0.0;
        for (j=0; j<=n-1; j++)
        if ((j!=p)&&(j!=q))
          { u=p*n+j; w=q*n+j;
            fm=a[u];
            a[u]=fm*cn+a[w]*sn;
            a[w]=-fm*sn+a[w]*cn;
          }
        for (i=0; i<=n-1; i++)
          if ((i!=p)&&(i!=q))
            { u=i*n+p; w=i*n+q;
              fm=a[u];
              a[u]=fm*cn+a[w]*sn;
              a[w]=-fm*sn+a[w]*cn;
            }
        for (i=0; i<=n-1; i++)
          { u=i*n+p; w=i*n+q;
            fm=v[u];
            v[u]=fm*cn+v[w]*sn;
            v[w]=-fm*sn+v[w]*cn;
          }
       goto loop1;
  }
    
//实对称三对角阵的全部特征值与特征向量的计算
int csstq(int n,double *b,double *c,double *q,double eps,int l)
  { int i,j,k,m,it,u,v;
    double d,f,h,g,p,r,e,s;
    c[n-1]=0.0; d=0.0; f=0.0;
    for (j=0; j<=n-1; j++)
      { it=0;
        h=eps*(fabs(b[j])+fabs(c[j]));
        if (h>d) d=h;
        m=j;
        while ((m<=n-1)&&(fabs(c[m])>d)) m=m+1;
        if (m!=j)
          { do
              { if (it==l)
                  { printf("fail\n");
                    return(-1);
                  }
                it=it+1;
                g=b[j];
                p=(b[j+1]-g)/(2.0*c[j]);
                r=sqrt(p*p+1.0);
                if (p>=0.0) b[j]=c[j]/(p+r);
                else b[j]=c[j]/(p-r);
                h=g-b[j];
                for (i=j+1; i<=n-1; i++)
                  b[i]=b[i]-h;
                f=f+h; p=b[m]; e=1.0; s=0.0;
                for (i=m-1; i>=j; i--)
                  { g=e*c[i]; h=e*p;
                    if (fabs(p)>=fabs(c[i]))
                      { e=c[i]/p; r=sqrt(e*e+1.0);
                        c[i+1]=s*p*r; s=e/r; e=1.0/r;
                      }
                    else
		      { e=p/c[i]; r=sqrt(e*e+1.0);
                        c[i+1]=s*c[i]*r;
                        s=1.0/r; e=e/r;
                      }
                    p=e*b[i]-s*g;
                    b[i+1]=h+s*(e*g+s*b[i]);
                    for (k=0; k<=n-1; k++)
                      { u=k*n+i+1; v=u-1;
                        h=q[u]; q[u]=s*q[v]+e*h;
                        q[v]=e*q[v]-s*h;
                      }
                  }
                c[j]=s*p; b[j]=e*p;
              }
            while (fabs(c[j])>d);
          }
        b[j]=b[j]+f;
      }
    for (i=0; i<=n-1; i++)
      { k=i; p=b[i];
        if (i+1<=n-1)
          { j=i+1;
            while ((j<=n-1)&&(b[j]<=p))
              { k=j; p=b[j]; j=j+1;}
          }
        if (k!=i)
          { b[k]=b[i]; b[i]=p;
            for (j=0; j<=n-1; j++)
              { u=j*n+i; v=j*n+k;
                p=q[u]; q[u]=q[v]; q[v]=p;
              }
          }
      }
    return(1);
  }

//约化对称矩阵为对称三对角的豪斯荷尔德变换法
void cstrq(double *a,int n,double *q,double *b,double *c)
    { int i,j,k,u,v;
    double h,f,g,h2;
    for (i=0; i<=n-1; i++)
    for (j=0; j<=n-1; j++)
      { u=i*n+j; q[u]=a[u];}
    for (i=n-1; i>=1; i--)
      { h=0.0;
        if (i>1)
          for (k=0; k<=i-1; k++)
            { u=i*n+k; h=h+q[u]*q[u];}
        if (h+1.0==1.0)
          { c[i]=0.0;
            if (i==1) c[i]=q[i*n+i-1];
            b[i]=0.0;
          }
        else
          { c[i]=sqrt(h);
            u=i*n+i-1;
            if (q[u]>0.0) c[i]=-c[i];
            h=h-q[u]*c[i];
            q[u]=q[u]-c[i];
            f=0.0;
            for (j=0; j<=i-1; j++)
              { q[j*n+i]=q[i*n+j]/h;
                g=0.0;
                for (k=0; k<=j; k++)
                  g=g+q[j*n+k]*q[i*n+k];
                if (j+1<=i-1)
                  for (k=j+1; k<=i-1; k++)
                    g=g+q[k*n+j]*q[i*n+k];
                c[j]=g/h;
                f=f+g*q[j*n+i];
              }
            h2=f/(h+h);
            for (j=0; j<=i-1; j++)
              { f=q[i*n+j];
                g=c[j]-h2*f;
                c[j]=g;
                for (k=0; k<=j; k++)
                  { u=j*n+k;
                    q[u]=q[u]-f*c[k]-g*q[i*n+k];
                  }
              }
            b[i]=h;
          }
      }
    for (i=0; i<=n-2; i++) c[i]=c[i+1];
    c[n-1]=0.0;
    b[0]=0.0;
    for (i=0; i<=n-1; i++)
      { if ((b[i]!=0.0)&&(i-1>=0))
          for (j=0; j<=i-1; j++)
            { g=0.0;
              for (k=0; k<=i-1; k++)
                g=g+q[i*n+k]*q[k*n+j];
              for (k=0; k<=i-1; k++)
                { u=k*n+j;
                  q[u]=q[u]-g*q[k*n+i];
                }
            }
        u=i*n+i;
        b[i]=q[u]; q[u]=1.0;
        if (i-1>=0)
          for (j=0; j<=i-1; j++)
            { q[i*n+j]=0.0; q[j*n+i]=0.0;}
      }
    return;
  }
  
int main(int argc, char* argv[])
{
   { 
    double det;
    static double a[4][4]={ {5.0,7.0,6.0,5.0},
                            {7.0,10.0,8.0,7.0},
                            {6.0,8.0,10.0,9.0},
                            {5.0,7.0,9.0,10.0}};
    int ret=bchol(&a[0][0],4,&det);
    if (ret>0)
      { printf("MAT L IS:\n");
        for (int i=0; i<4; i++)
          { for (int j=0; j<4; j++)
              printf("%13.7e ",a[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("det(A)=%13.7e\n",det);
      } 
    }	
  { int i,j;
    static double br[4][4],bi[4][4],cr[4][4],ci[4][4];
    static double ar[4][4]={ {0.2368,0.2471,0.2568,1.2671},
                             {1.1161,0.1254,0.1397,0.1490},
                             {0.1582,1.1675,0.1768,0.1871},
                             {0.1968,0.2071,1.2168,0.2271}};
    static double ai[4][4]={ {0.1345,0.1678,0.1875,1.1161},
                             {1.2671,0.2017,0.7024,0.2721},
                             {-0.2836,-1.1967,0.3558,-0.2078},
                             {0.3576,-1.2345,2.1185,0.4773}};
    for (i=0; i<4; i++)
    for (j=0; j<4; j++)
      { br[i][j]=ar[i][j]; bi[i][j]=ai[i][j];}
    i=bcinv(&ar[0][0],&ai[0][0],4);
    if (i!=0)
      { printf("MAT AR IS:\n");
    for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",br[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("MAT AI IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",bi[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("MAT AR- IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",ar[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("MAT AI- IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",ai[i][j]);
            printf("\n");
          }
        bcmul(&br[0][0],&bi[0][0],&ar[0][0],&ai[0][0],4,4,4,&cr[0][0],&ci[0][0]);
        printf("\n");
        printf("MAT CR=AA- IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",cr[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("MAT CI=AA- IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",ci[i][j]);
            printf("\n");
          }
      }
  }	
  { int i,j;
    static double l[4][4],u[4][4];
    static double a[4][4]={ {2.0,4.0,4.0,2.0},
                            {3.0,3.0,12.0,6.0},
                            {2.0,4.0,-1.0,2.0},
                            {4.0,2.0,1.0,1.0}};
    i=blluu(&a[0][0],4,&l[0][0],&u[0][0]);
    if (i!=0)
      { printf("MAT L IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",l[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("MAT U IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",u[i][j]);
            printf("\n");
          }
        printf("\n");
      }
  } 
 { int i,j;
    static double q[4][4],a[4][3]={ {1.0,1.0,-1.0},
       {2.0,1.0,0.0},{1.0,-1.0,0.0},{-1.0,2.0,1.0}};
    i=bmaqr(&a[0][0],4,3,&q[0][0]);
    if (i!=0)
      { printf("MAT Q IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",q[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("MAT R IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<3; j++)
              printf("%13.7e ",a[i][j]);
            printf("\n");
          }
        printf("\n");
      } 
  }  
{ static double a[5][4]={ {1.0,2.0,3.0,4.0},
                            {5.0,6.0,7.0,8.0},
                            {9.0,10.0,11.0,12.0},
                            {13.0,14.0,15.0,16.0},
                            {-17.0,18.0,19.0,20.0}};
static double a1[5][4]={ {1,2,3,4},
                            {5,6,7,8},
                            {9,10,11,12},
                            {13,14,15,16},
                            {-17,18,19,20}};
    printf("\n");
    printf("秩RANK=%d\n",brank(&a1[0][0],5,4));
    printf("\n");
  }  
{ static double a[4][4]={ {1.0,2.0,3.0,4.0},
                            {5.0,6.0,7.0,8.0},
                            {9.0,10.0,11.0,12.0},
                            {13.0,14.0,15.0,16.0}};
    static double b[4][4]={ {3.0,-3.0,-2.0,4.0},
                            {5.0,-5.0,1.0,8.0},
                            {11.0,8.0,5.0,-7.0},
                            {5.0,-1.0,-3.0,-1.0}};
    double det;
    det=bsdet(&a[0][0],4);
    printf("det(A)=%13.7e\n",det);
    printf("\n");
    det=bsdet(&b[0][0],4);
    printf("det(B)=%13.7e\n",det);
    printf("\n");
  }  
   { int i,j;
    static double a[4][4]={ {5.0,7.0,6.0,5.0},
                            {7.0,10.0,8.0,7.0},
                            {6.0,8.0,10.0,9.0},
                            {5.0,7.0,9.0,10.0}};
    static double b[4][4],c[4][4];
    for (i=0; i<4; i++)
    for (j=0; j<4; j++)
      b[i][j]=a[i][j];
    i=bssgj(&a[0][0],4);
    if (i>0)
      { printf("MAT A IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",b[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("MAT A- IS:\n");
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",a[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("MAT AA- IS:\n");
        brmul(&b[0][0],&a[0][0],4,4,4,&c[0][0]);
        for (i=0; i<4; i++)
          { for (j=0; j<4; j++)
              printf("%13.7e ",c[i][j]);
            printf("\n");
          }
        printf("\n");
      }
  } 
{ int n,i,j,k;
    static double t[6]={10.0,5.0,4.0,3.0,2.0,1.0};
    static double tt[6]={0.0,-1.0,-2.0,-3.0,-4.0,-5.0};
    static double b[6][6],a[6][6];
    n=6;
    i=btrch(&t[0],&tt[0],n,&b[0][0]);
    if (i>0)
      { printf("B=inv(T):\n");
        for (i=0; i<6; i++)
          { for (j=0; j<6; j++)
              printf("%12.6e ",b[i][j]);
            printf("\n");
          }
        printf("\n");
        printf("A=T*B:\n");
        for (i=1; i<=6; i++)
        for (j=1; j<=6; j++)
          { a[i-1][j-1]=0.0;
            for (k=1; k<=j-1; k++)
              a[i-1][j-1]=a[i-1][j-1]+b[i-1][k-1]*t[j-k];
            a[i-1][j-1]=a[i-1][j-1]+b[i-1][j-1]*t[0];
            for (k=j+1; k<=6; k++)
              a[i-1][j-1]=a[i-1][j-1]+b[i-1][k-1]*tt[k-j];
          }
        for (i=0; i<6; i++)
          { for (j=0; j<6; j++)
              printf("%12.6e ",a[i][j]);
            printf("\n");
          }
      }
  }  
 { int i,j;
    static double a[5][5]={ {1.0,6.0,-3.0,-1.0,7.0},
      {8.0,-15.0,18.0,5.0,4.0},{-2.0,11.0,9.0,15.0,20.0},
      {-13.0,2.0,21.0,30.0,-6.0},{17.0,22.0,-5.0,3.0,6.0}};
    chhbg(&a[0][0],5);
    printf("MAT A IS:\n");
    for (i=0; i<5; i++)
      { for (j=0; j<5; j++)
          printf("%13.7e ",a[i][j]);
        printf("\n");
      }
    printf("\n");
  }
 { int i,j,jt=60;
    double eps=0.000001;
    static double u[5],v[5];
    static double a[5][5]={ {1.0,6.0,-3.0,-1.0,7.0},
       {8.0,-15.0,18.0,5.0,4.0},{-2.0,11.0,9.0,15.0,20.0},
       {-13.0,2.0,21.0,30.0,-6.0},{17.0,22.0,-5.0,3.0,6.0}};
    chhbg(&a[0][0],5);
    printf("MAT H IS:\n");
    for (i=0; i<5; i++)
      { for (j=0; j<5; j++)
          printf("%13.7e ",a[i][j]);
        printf("\n");
      }
    printf("\n");
    i=chhqr(&a[0][0],5,&u[0],&v[0],eps,jt);
    if (i>0)
      for (i=0; i<5; i++)
        printf("%13.7e +J %13.7e\n",u[i],v[i]);
    printf("\n");
  }
{ int i,j;
    double eps;
    static double v[3][3];
    static double a[3][3]={ {2.0,-1.0,0.0},{-1.0,2.0,-1.0},
                            {0.0,-1.0,2.0}};
    eps=0.000001;
    i=cjcbi(&a[0][0],3,&v[0][0],eps,100);
    if (i>0)
      { for (i=0; i<3; i++)
          printf("%13.7e  ",a[i][i]);
        printf("\n\n");
        for (i=0; i<3; i++)
          { for (j=0; j<3; j++)
              printf("%13.7e  ",v[i][j]);
            printf("\n");
          }
        printf("\n");
      }
  }
 { int i,j;
    double eps;
    static double v[5][5];
    static double a[5][5]={ {10.0,1.0,2.0,3.0,4.0},
                            {1.0,9.0,-1.0,2.0,-3.0},
                            {2.0,-1.0,7.0,3.0,-5.0},
                            {3.0,2.0,3.0,12.0,-1.0},
                            {4.0,-3.0,-5.0,-1.0,15.0}};
    eps=0.000001;
    cjcbj(&a[0][0],5,&v[0][0],eps);
    for (i=0; i<5; i++)
      printf("%13.7e\n",a[i][i]);
    printf("\n\n");
    for (i=0; i<5; i++)
      { for (j=0; j<5; j++)
          printf("%12.6e ",v[i][j]);
        printf("\n");
      }
    printf("\n");
  }
 { int i,j,k,l=60;
    static double q[5][5],b[5],c[5];
    static double a[5][5]={ {10.0,1.0,2.0,3.0,4.0},
       {1.0,9.0,-1.0,2.0,-3.0},{2.0,-1.0,7.0,3.0,-5.0},
       {3.0,2.0,3.0,12.0,-1.0},{4.0,-3.0,-5.0,-1.0,15.0}};
    double eps=0.000001;
    cstrq(&a[0][0],5,&q[0][0],&b[0],&c[0]);
    k=csstq(5,&b[0],&c[0],&q[0][0],eps,l);
    printf("MAT A IS:\n");
    for (i=0; i<5; i++)
      { for (j=0; j<5; j++)
          printf("%13.7e ",a[i][j]);
        printf("\n");
      }
    printf("\n");
    if (k>0)
      { printf("MAT B IS:\n");
        for (i=0; i<5; i++)
          printf("%13.7e ",b[i]);
        printf("\n\n");
        printf("MAT Q IS:\n");
        for (i=0; i<5; i++)
          { for (j=0; j<5; j++)
              printf("%13.7e ",q[i][j]);
            printf("\n");
          }
        printf("\n");
      }
  }
 { int i,j;
    static double b[5],c[5],q[5][5];
    static double a[5][5]={ {10.0,1.0,2.0,3.0,4.0},
        {1.0,9.0,-1.0,2.0,-3.0},{2.0,-1.0,7.0,3.0,-5.0},
        {3.0,2.0,3.0,12.0,-1.0},{4.0,-3.0,-5.0,-1.0,15.0}};
    cstrq(&a[0][0],5,&q[0][0],&b[0],&c[0]);
    printf("MAT A IS:\n");
    for (i=0; i<5; i++)
      { for (j=0; j<5; j++)
          printf("%13.7e ",a[i][j]);
        printf("\n");
      }
    printf("\n");
    printf("MAT Q IS:\n");
    for (i=0; i<5; i++)
      { for (j=0; j<5; j++)
          printf("%13.7e ",q[i][j]);
        printf("\n");
      }
    printf("\n");
    printf("MAT B IS:\n");
    for (i=0; i<5; i++)
      printf("%13.7e ",b[i]);
    printf("\n\n");
    printf("MAT C IS:\n");
    for (i=0; i<5; i++)
      printf("%13.7e ",c[i]);
    printf("\n\n");
  }
{ int i,j;
    static double a[4][5]={ {1.0,3.0,-2.0,0.0,4.0},
                            {-2.0,-1.0,5.0,-7.0,2.0},
                            {0.0,8.0,4.0,1.0,-5.0},
                            {3.0,-3.0,2.0,-4.0,1.0}};
    static double c[4][3],b[5][3]={ {4.0,5.0,-1.0},
                      {2.0,-2.0,6.0},{7.0,8.0,1.0},
                      {0.0,3.0,-5.0},{9.0,8.0,-6.0}};
    brmul(&a[0][0],&b[0][0],4,5,3,&c[0][0]);
    for (i=0; i<4; i++)
      { for (j=0; j<3; j++)
          printf("%13.7e  ",c[i][j]);
        printf("\n");
      }
    printf("\n");
  }
	return 0;
}

