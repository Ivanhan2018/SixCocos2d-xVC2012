#include "mathlib.h"
typedef unsigned char BYTE;

void conv(float *xin, float *h, int lx, int lh,float *xout)
{
	int i,j; 
	float sum;
	for (i = 0; i < lx + lh - 1; i++)
	{
		sum = 0.0;
		if( i < lh - 1 )
		{
			for(j = 0; j < i+1; j++)
			sum += xin[j] * h[i-j];
			xout[i] = sum;
		}
		else if(i > lx - 1)
		{
			for(j = lh -1; j > i - lx; j--)
			sum += xin[i-j] * h[j];
			xout[i]= sum;
		}
		else
		{
			for(j = 0; j < lh; j++)
			sum += xin[i-j] * h[j];
			xout[i]= sum;
		}
	} 
}

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
  int __stdcall agmqr(double *a,int m,int n,double *b,double *q)
  { int i,j;
    double d,*c;
    c=(double*)malloc(n*sizeof(double));
    i=bmaqr(a,m,n,q);
    if (i==0) { free(c); return(0);}
    for (i=0; i<=n-1; i++)
      { d=0.0;
        for (j=0; j<=m-1; j++)
          d=d+q[j*m+i]*b[j];
        c[i]=d;
      }
    b[n-1]=c[n-1]/a[n*n-1];
    for (i=n-2; i>=0; i--)
      { d=0.0;
        for (j=i+1; j<=n-1; j++)
          d=d+a[i*n+j]*b[j];
        b[i]=(c[i]-d)/a[i*n+i];
      }
    free(c); return(1);
  }

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
  void __stdcall agrad(double *a,int n,double *b,double eps,double *x)
  { int i,k;
    double *p,*r,*s,*q,alpha,beta,d,e;
    p=(double*)malloc(n*sizeof(double));
    r=(double*)malloc(n*sizeof(double));
    s=(double*)malloc(n*sizeof(double));
    q=(double*)malloc(n*sizeof(double));
    for (i=0; i<=n-1; i++)
      { x[i]=0.0; p[i]=b[i]; r[i]=b[i]; }
    i=0;
    while (i<=n-1)
      { brmul(a,p,n,n,1,s);
        d=0.0; e=0.0;
        for (k=0; k<=n-1; k++)
           { d=d+p[k]*b[k]; e=e+p[k]*s[k]; }
        alpha=d/e;
        for (k=0; k<=n-1; k++)
           x[k]=x[k]+alpha*p[k];
        brmul(a,x,n,n,1,q);
        d=0.0;
        for (k=0; k<=n-1; k++)
          { r[k]=b[k]-q[k]; d=d+r[k]*s[k]; }
        beta=d/e; d=0.0;
        for (k=0; k<=n-1; k++) d=d+r[k]*r[k];
        d=sqrt(d);
        if (d<eps) 
          { free(p); free(r); free(s); free(q);return;}
        for (k=0; k<=n-1; k++)
           p[k]=r[k]-beta*p[k];
        i=i+1;
      }
    free(p); free(r); free(s); free(q);
    return;
  } 
  static void ppp(double *a,double *e,double *s,double *v,int m,int n)
  { int i,j,p,q;
    double d;
    if (m>=n) i=n;
    else i=m;
    for (j=1; j<=i-1; j++)
      { a[(j-1)*n+j-1]=s[j-1];
        a[(j-1)*n+j]=e[j-1];
      }
    a[(i-1)*n+i-1]=s[i-1];
    if (m<n) a[(i-1)*n+i]=e[i-1];
    for (i=1; i<=n-1; i++)
    for (j=i+1; j<=n; j++)
      { p=(i-1)*n+j-1; q=(j-1)*n+i-1;
        d=v[p]; v[p]=v[q]; v[q]=d;
      }
    return;
  }

  static void sss(double *fg,double *cs)//cs[2],fg[2];
  { double r,d;
    if ((fabs(fg[0])+fabs(fg[1]))==0.0)
      { cs[0]=1.0; cs[1]=0.0; d=0.0;}
    else 
      { d=sqrt(fg[0]*fg[0]+fg[1]*fg[1]);
        if (fabs(fg[0])>fabs(fg[1]))
          { d=fabs(d);
            if (fg[0]<0.0) d=-d;
          }
        if (fabs(fg[1])>=fabs(fg[0]))
          { d=fabs(d);
            if (fg[1]<0.0) d=-d;
          }
        cs[0]=fg[0]/d; cs[1]=fg[1]/d;
      }
    r=1.0;
    if (fabs(fg[0])>fabs(fg[1])) r=cs[1];
    else
      if (cs[0]!=0.0) r=1.0/cs[0];
    fg[0]=d; fg[1]=r;
    return;
  }

  int __stdcall bmuav(double *a,int m,int n,double *u,double *v,double eps,int ka)
  { int i,j,k,l,it,ll,kk,ix,iy,mm,nn,iz,m1,ks;
    double d,dd,t,sm,sm1,em1,sk,ek,b,c,shh,fg[2],cs[2];
    double *s,*e,*w;
    s=(double*)malloc(ka*sizeof(double));
    e=(double*)malloc(ka*sizeof(double));
    w=(double*)malloc(ka*sizeof(double));
    it=60; k=n;
    if (m-1<n) k=m-1;
    l=m;
    if (n-2<m) l=n-2;
    if (l<0) l=0;
    ll=k;
    if (l>k) ll=l;
    if (ll>=1)
      { for (kk=1; kk<=ll; kk++)
          { if (kk<=k)
              { d=0.0;
                for (i=kk; i<=m; i++)
                  { ix=(i-1)*n+kk-1; d=d+a[ix]*a[ix];}
                s[kk-1]=sqrt(d);
                if (s[kk-1]!=0.0)
                  { ix=(kk-1)*n+kk-1;
                    if (a[ix]!=0.0)
                      { s[kk-1]=fabs(s[kk-1]);
                        if (a[ix]<0.0) s[kk-1]=-s[kk-1];
                      }
                    for (i=kk; i<=m; i++)
                      { iy=(i-1)*n+kk-1;
                        a[iy]=a[iy]/s[kk-1];
                      }
                    a[ix]=1.0+a[ix];
                  }
                s[kk-1]=-s[kk-1];
              }
            if (n>=kk+1)
              { for (j=kk+1; j<=n; j++)
                  { if ((kk<=k)&&(s[kk-1]!=0.0))
                      { d=0.0;
                        for (i=kk; i<=m; i++)
                          { ix=(i-1)*n+kk-1;
                            iy=(i-1)*n+j-1;
                            d=d+a[ix]*a[iy];
                          }
                        d=-d/a[(kk-1)*n+kk-1];
                        for (i=kk; i<=m; i++)
                          { ix=(i-1)*n+j-1;
                            iy=(i-1)*n+kk-1;
                            a[ix]=a[ix]+d*a[iy];
                          }
                      }
                    e[j-1]=a[(kk-1)*n+j-1];
                  }
              }
            if (kk<=k)
              { for (i=kk; i<=m; i++)
                  { ix=(i-1)*m+kk-1; iy=(i-1)*n+kk-1;
                    u[ix]=a[iy];
                  }
              }
            if (kk<=l)
              { d=0.0;
                for (i=kk+1; i<=n; i++)
                  d=d+e[i-1]*e[i-1];
                e[kk-1]=sqrt(d);
                if (e[kk-1]!=0.0)
                  { if (e[kk]!=0.0)
                      { e[kk-1]=fabs(e[kk-1]);
                        if (e[kk]<0.0) e[kk-1]=-e[kk-1];
                      }
                    for (i=kk+1; i<=n; i++)
                      e[i-1]=e[i-1]/e[kk-1];
                    e[kk]=1.0+e[kk];
                  }
                e[kk-1]=-e[kk-1];
                if ((kk+1<=m)&&(e[kk-1]!=0.0))
                  { for (i=kk+1; i<=m; i++) w[i-1]=0.0;
                    for (j=kk+1; j<=n; j++)
                      for (i=kk+1; i<=m; i++)
                        w[i-1]=w[i-1]+e[j-1]*a[(i-1)*n+j-1];
                    for (j=kk+1; j<=n; j++)
                      for (i=kk+1; i<=m; i++)
                        { ix=(i-1)*n+j-1;
                          a[ix]=a[ix]-w[i-1]*e[j-1]/e[kk];
                        }
                  }
                for (i=kk+1; i<=n; i++)
                  v[(i-1)*n+kk-1]=e[i-1];
              }
          }
      }
    mm=n;
    if (m+1<n) mm=m+1;
    if (k<n) s[k]=a[k*n+k];
    if (m<mm) s[mm-1]=0.0;
    if (l+1<mm) e[l]=a[l*n+mm-1];
    e[mm-1]=0.0;
    nn=m;
    if (m>n) nn=n;
    if (nn>=k+1)
      { for (j=k+1; j<=nn; j++)
          { for (i=1; i<=m; i++)
              u[(i-1)*m+j-1]=0.0;
            u[(j-1)*m+j-1]=1.0;
          }
      }
    if (k>=1)
      { for (ll=1; ll<=k; ll++)
          { kk=k-ll+1; iz=(kk-1)*m+kk-1;
            if (s[kk-1]!=0.0)
              { if (nn>=kk+1)
                  for (j=kk+1; j<=nn; j++)
                    { d=0.0;
                      for (i=kk; i<=m; i++)
                        { ix=(i-1)*m+kk-1;
                          iy=(i-1)*m+j-1;
                          d=d+u[ix]*u[iy]/u[iz];
                        }
                      d=-d;
                      for (i=kk; i<=m; i++)
                        { ix=(i-1)*m+j-1;
                          iy=(i-1)*m+kk-1;
                          u[ix]=u[ix]+d*u[iy];
                        }
                    }
                  for (i=kk; i<=m; i++)
                    { ix=(i-1)*m+kk-1; u[ix]=-u[ix];}
                  u[iz]=1.0+u[iz];
                  if (kk-1>=1)
                    for (i=1; i<=kk-1; i++)
                      u[(i-1)*m+kk-1]=0.0;
              }
            else
              { for (i=1; i<=m; i++)
                  u[(i-1)*m+kk-1]=0.0;
                u[(kk-1)*m+kk-1]=1.0;
              }
          }
      }
    for (ll=1; ll<=n; ll++)
      { kk=n-ll+1; iz=kk*n+kk-1;
        if ((kk<=l)&&(e[kk-1]!=0.0))
          { for (j=kk+1; j<=n; j++)
              { d=0.0;
                for (i=kk+1; i<=n; i++)
                  { ix=(i-1)*n+kk-1; iy=(i-1)*n+j-1;
                    d=d+v[ix]*v[iy]/v[iz];
                  }
                d=-d;
                for (i=kk+1; i<=n; i++)
                  { ix=(i-1)*n+j-1; iy=(i-1)*n+kk-1;
                    v[ix]=v[ix]+d*v[iy];
                  }
              }
          }
        for (i=1; i<=n; i++)
          v[(i-1)*n+kk-1]=0.0;
        v[iz-n]=1.0;
      }
    for (i=1; i<=m; i++)
    for (j=1; j<=n; j++)
      a[(i-1)*n+j-1]=0.0;
    m1=mm; it=60;
    while (1==1)
      { if (mm==0)
          { ppp(a,e,s,v,m,n);
            free(s); free(e); free(w); return(1);
          }
        if (it==0)
          { ppp(a,e,s,v,m,n);
            free(s); free(e); free(w); return(-1);
          }
        kk=mm-1;
	while ((kk!=0)&&(fabs(e[kk-1])!=0.0))
          { d=fabs(s[kk-1])+fabs(s[kk]);
            dd=fabs(e[kk-1]);
            if (dd>eps*d) kk=kk-1;
            else e[kk-1]=0.0;
          }
        if (kk==mm-1)
          { kk=kk+1;
            if (s[kk-1]<0.0)
              { s[kk-1]=-s[kk-1];
                for (i=1; i<=n; i++)
                  { ix=(i-1)*n+kk-1; v[ix]=-v[ix];}
              }
            while ((kk!=m1)&&(s[kk-1]<s[kk]))
              { d=s[kk-1]; s[kk-1]=s[kk]; s[kk]=d;
                if (kk<n)
                  for (i=1; i<=n; i++)
                    { ix=(i-1)*n+kk-1; iy=(i-1)*n+kk;
                      d=v[ix]; v[ix]=v[iy]; v[iy]=d;
                    }
                if (kk<m)
                  for (i=1; i<=m; i++)
                    { ix=(i-1)*m+kk-1; iy=(i-1)*m+kk;
                      d=u[ix]; u[ix]=u[iy]; u[iy]=d;
                    }
                kk=kk+1;
              }
            it=60;
            mm=mm-1;
          }
        else
          { ks=mm;
            while ((ks>kk)&&(fabs(s[ks-1])!=0.0))
              { d=0.0;
                if (ks!=mm) d=d+fabs(e[ks-1]);
                if (ks!=kk+1) d=d+fabs(e[ks-2]);
                dd=fabs(s[ks-1]);
                if (dd>eps*d) ks=ks-1;
                else s[ks-1]=0.0;
              }
            if (ks==kk)
              { kk=kk+1;
                d=fabs(s[mm-1]);
                t=fabs(s[mm-2]);
                if (t>d) d=t;
                t=fabs(e[mm-2]);
                if (t>d) d=t;
                t=fabs(s[kk-1]);
                if (t>d) d=t;
                t=fabs(e[kk-1]);
                if (t>d) d=t;
                sm=s[mm-1]/d; sm1=s[mm-2]/d;
                em1=e[mm-2]/d;
                sk=s[kk-1]/d; ek=e[kk-1]/d;
                b=((sm1+sm)*(sm1-sm)+em1*em1)/2.0;
                c=sm*em1; c=c*c; shh=0.0;
                if ((b!=0.0)||(c!=0.0))
                  { shh=sqrt(b*b+c);
                    if (b<0.0) shh=-shh;
                    shh=c/(b+shh);
                  }
                fg[0]=(sk+sm)*(sk-sm)-shh;
                fg[1]=sk*ek;
                for (i=kk; i<=mm-1; i++)
                  { sss(fg,cs);
                    if (i!=kk) e[i-2]=fg[0];
                    fg[0]=cs[0]*s[i-1]+cs[1]*e[i-1];
                    e[i-1]=cs[0]*e[i-1]-cs[1]*s[i-1];
                    fg[1]=cs[1]*s[i];
                    s[i]=cs[0]*s[i];
                    if ((cs[0]!=1.0)||(cs[1]!=0.0))
                      for (j=1; j<=n; j++)
                        { ix=(j-1)*n+i-1;
                          iy=(j-1)*n+i;
                          d=cs[0]*v[ix]+cs[1]*v[iy];
                          v[iy]=-cs[1]*v[ix]+cs[0]*v[iy];
                          v[ix]=d;
                        }
                    sss(fg,cs);
                    s[i-1]=fg[0];
                    fg[0]=cs[0]*e[i-1]+cs[1]*s[i];
                    s[i]=-cs[1]*e[i-1]+cs[0]*s[i];
                    fg[1]=cs[1]*e[i];
                    e[i]=cs[0]*e[i];
                    if (i<m)
                      if ((cs[0]!=1.0)||(cs[1]!=0.0))
                        for (j=1; j<=m; j++)
                          { ix=(j-1)*m+i-1;
                            iy=(j-1)*m+i;
                            d=cs[0]*u[ix]+cs[1]*u[iy];
                            u[iy]=-cs[1]*u[ix]+cs[0]*u[iy];
                            u[ix]=d;
                          }
                  }
                e[mm-2]=fg[0];
                it=it-1;
              }
            else
              { if (ks==mm)
                  { kk=kk+1;
                    fg[1]=e[mm-2]; e[mm-2]=0.0;
                    for (ll=kk; ll<=mm-1; ll++)
                      { i=mm+kk-ll-1;
                        fg[0]=s[i-1];
                        sss(fg,cs);
                        s[i-1]=fg[0];
                        if (i!=kk)
                          { fg[1]=-cs[1]*e[i-2];
                            e[i-2]=cs[0]*e[i-2];
                          }
                        if ((cs[0]!=1.0)||(cs[1]!=0.0))
                          for (j=1; j<=n; j++)
                            { ix=(j-1)*n+i-1;
                              iy=(j-1)*n+mm-1;
                              d=cs[0]*v[ix]+cs[1]*v[iy];
                              v[iy]=-cs[1]*v[ix]+cs[0]*v[iy];
                              v[ix]=d;
                            }
                      }
                  }
                else
                  { kk=ks+1;
                    fg[1]=e[kk-2];
                    e[kk-2]=0.0;
                    for (i=kk; i<=mm; i++)
                      { fg[0]=s[i-1];
                        sss(fg,cs);
                        s[i-1]=fg[0];
                        fg[1]=-cs[1]*e[i-1];
                        e[i-1]=cs[0]*e[i-1];
                        if ((cs[0]!=1.0)||(cs[1]!=0.0))
                          for (j=1; j<=m; j++)
                            { ix=(j-1)*m+i-1;
                              iy=(j-1)*m+kk-2;
                              d=cs[0]*u[ix]+cs[1]*u[iy];
                              u[iy]=-cs[1]*u[ix]+cs[0]*u[iy];
                              u[ix]=d;
                            }
                      }
                  }
              }
          }
      }
    return(1);
  }
 int __stdcall bginv(double *a,int m,int n,double *aa,double eps,double *u,double *v,int ka)
  { int i,j,k,l,t,p,q,f;
    i=bmuav(a,m,n,u,v,eps,ka);
    if (i<0) return(-1);
    j=n;
    if (m<n) j=m;
    j=j-1;
    k=0;
    while ((k<=j)&&(a[k*n+k]!=0.0)) k=k+1;
    k=k-1;
    for (i=0; i<=n-1; i++)
    for (j=0; j<=m-1; j++)
      { t=i*m+j; aa[t]=0.0;
        for (l=0; l<=k; l++)
          { f=l*n+i; p=j*m+l; q=l*n+l;
            aa[t]=aa[t]+v[f]*u[p]/a[q];
          }
      }
    return(1);
  }
static void g60(double *t,double *x,double *y,double *x1,double *y1,double *dx,double *dy,double *p,double *q,int *k,int *it)
  { *it=1;
    while (*it==1)
      { *t=*t/1.67; *it=0;
        *x1=*x-*t*(*dx);
        *y1=*y-*t*(*dy);
        if (*k>=30)
	  { *p=sqrt(*x1*(*x1)+*y1*(*y1));
            *q=exp(75.0/(*k));
            if (*p>=*q) *it=1;
          }
      }
    return;
  }

  static void g90(double *xr,double *xi,double *ar,double *ai,double *x,double *y,double *p,double *w,int *k)
  { int i;
    for (i=1; i<=*k; i++)
      { ar[i]=ar[i]+ar[i-1]*(*x)-ai[i-1]*(*y);
        ai[i]=ai[i]+ar[i-1]*(*y)+ai[i-1]*(*x);
      }
    xr[*k-1]=*x*(*w); xi[*k-1]=*y*(*w);
    *k=*k-1;
    if (*k==1)
      { *p=ar[0]*ar[0]+ai[0]*ai[0];
        xr[0]=-*w*(ar[0]*ar[1]+ai[0]*ai[1])/(*p);
        xi[0]=*w*(ar[1]*ai[0]-ar[0]*ai[1])/(*p);
      }
    return;
  }

  static void g65(double *x,double *y,double *x1,double *y1,double *dx,double *dy,double *dd,double *dc,double *c,int *k,int *is,int *it)
  { if (*it==0)
      { *is=1;
        *dd=sqrt(*dx*(*dx)+*dy*(*dy));
        if (*dd>1.0) *dd=1.0;
        *dc=6.28/(4.5*(*k)); *c=0.0;
      }
    while(1==1)
      { *c=*c+*dc;
        *dx=*dd*cos(*c); *dy=*dd*sin(*c);
        *x1=*x+*dx; *y1=*y+*dy;
        if (*c<=6.29)
          { *it=0; return;}
        *dd=*dd/1.67;
        if (*dd<=1.0e-07)
          { *it=1; return;}
        *c=0.0;
      }
  }
  int __stdcall dcsrt(double *ar,double *ai,int n,double *xr,double *xi)
  { int m,i,jt,k,is,it;
    double t,x,y,x1,y1,dx,dy,p,q,w,dd,dc,c;
    double g,u,v,pq,g1,u1,v1;
    m=n;
    p=sqrt(ar[m]*ar[m]+ai[m]*ai[m]);
    while ((m>0)&&(p+1.0==1.0))
      {  m=m-1;
         p=sqrt(ar[m]*ar[m]+ai[m]*ai[m]);
       }
    if (m<=0)
      { printf("fail\n"); return(-1);}
    for (i=0; i<=m; i++)
      { ar[i]=ar[i]/p; ai[i]=ai[i]/p;}
    for (i=0; i<=m/2; i++)
      { w=ar[i]; ar[i]=ar[m-i]; ar[m-i]=w;
        w=ai[i]; ai[i]=ai[m-i]; ai[m-i]=w;
      }
    k=m; is=0; w=1.0;
    jt=1;
    while (jt==1)
      { pq=sqrt(ar[k]*ar[k]+ai[k]*ai[k]);
	while (pq<1.0e-12)
          { xr[k-1]=0.0; xi[k-1]=0.0; k=k-1;
            if (k==1)
              { p=ar[0]*ar[0]+ai[0]*ai[0];
                xr[0]=-w*(ar[0]*ar[1]+ai[0]*ai[1])/p;
                xi[0]=w*(ar[1]*ai[0]-ar[0]*ai[1])/p;
                return(1);
              }
            pq=sqrt(ar[k]*ar[k]+ai[k]*ai[k]);
          }
	q=log(pq); q=q/(1.0*k); q=exp(q);
        p=q; w=w*p;
        for (i=1; i<=k; i++)
          { ar[i]=ar[i]/q; ai[i]=ai[i]/q; q=q*p;}
        x=0.0001; x1=x; y=0.2; y1=y; dx=1.0;
        g=1.0e+37; 
        l40:
        u=ar[0]; v=ai[0];
        for (i=1; i<=k; i++)
          { p=u*x1; q=v*y1;
            pq=(u+v)*(x1+y1);
            u=p-q+ar[i]; v=pq-p-q+ai[i];
          }
        g1=u*u+v*v;
        if (g1>=g)
          { if (is!=0)
              { it=1;
                g65(&x,&y,&x1,&y1,&dx,&dy,&dd,&dc,
		    &c,&k,&is,&it);
                if (it==0) goto l40;
              }
            else
              { g60(&t,&x,&y,&x1,&y1,&dx,&dy,&p,&q,&k,&it);
                if (t>=1.0e-03) goto l40;
                if (g>1.0e-18)
                  { it=0;
                    g65(&x,&y,&x1,&y1,&dx,&dy,&dd,&dc,
			&c,&k,&is,&it);
                    if (it==0) goto l40;
                  }
              }
            g90(xr,xi,ar,ai,&x,&y,&p,&w,&k);
          }
        else
          { g=g1; x=x1; y=y1; is=0;
            if (g<=1.0e-22)
	      g90(xr,xi,ar,ai,&x,&y,&p,&w,&k);
            else
              { u1=k*ar[0]; v1=ai[0];
                for (i=2; i<=k; i++)
                  { p=u1*x; q=v1*y; pq=(u1+v1)*(x+y);
                    u1=p-q+(k-i+1)*ar[i-1];
                    v1=pq-p-q+(k-i+1)*ai[i-1];
                  }
                p=u1*u1+v1*v1;
                if (p<=1.0e-20)
                  { it=0;
                    g65(&x,&y,&x1,&y1,&dx,&dy,&dd,&dc,
                        &c,&k,&is,&it);
                    if (it==0) goto l40;
                    g90(xr,xi,ar,ai,&x,&y,&p,&w,&k);
                  }
                else
                  { dx=(u*u1+v*v1)/p;
                    dy=(u1*v-v1*u)/p;
                    t=1.0+4.0/k;
                    g60(&t,&x,&y,&x1,&y1,&dx,&dy,&p,&q,
                        &k,&it);
                    if (t>=1.0e-03) goto l40;
                    if (g>1.0e-18)
                      { it=0;
                        g65(&x,&y,&x1,&y1,&dx,&dy,&dd,&dc,
                            &c,&k,&is,&it);
                        if (it==0) goto l40;
                      }
                    g90(xr,xi,ar,ai,&x,&y,&p,&w,&k);
                  }
              }
          }
        if (k==1) jt=0;
        else jt=1;
      }
    return(1);
  }
  void __stdcall isqt1(double *x,double *y,int n,double *a,double *dt)//a[2],dt[6]
  { int i;
    double xx,yy,e,f,q,u,p,umax,umin,s;
    xx=0.0; yy=0.0;
    for (i=0; i<=n-1; i++)
      { xx=xx+x[i]/n; yy=yy+y[i]/n;}
    e=0.0; f=0.0;
    for (i=0; i<=n-1; i++)
      { q=x[i]-xx; e=e+q*q;
        f=f+q*(y[i]-yy);
      }
    a[1]=f/e; a[0]=yy-a[1]*xx;
    q=0.0; u=0.0; p=0.0;
    umax=0.0; umin=1.0e+30;
    for (i=0; i<=n-1; i++)
      { s=a[1]*x[i]+a[0];
        q=q+(y[i]-s)*(y[i]-s);
        p=p+(s-yy)*(s-yy);
        e=fabs(y[i]-s);
        if (e>umax) umax=e;
        if (e<umin) umin=e;
        u=u+e/n;
      }
    dt[1]=sqrt(q/n);
    dt[0]=q; dt[2]=p;
    dt[3]=umax; dt[4]=umin; dt[5]=u;
    return;
  }
 int achol(double *a,int n,int m,double *d)
  { int i,j,k,u,v;
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

  void __stdcall isqt2(double *x,double *y,int m,int n,double *a,double *dt,double *v)
  { int i,j,k,l,mm;
    double q,e,u,p,yy,s,r,pp,*b;
    b=(double*)malloc((m+1)*(m+1)*sizeof(double));
    mm=m+1;
    b[mm*mm-1]=n;
    for (j=0; j<=m-1; j++)
      { p=0.0;
        for (i=0; i<=n-1; i++)
          p=p+x[j*n+i];
        b[m*mm+j]=p;
        b[j*mm+m]=p;
      }
    for (i=0; i<=m-1; i++)
      for (j=i; j<=m-1; j++)
        { p=0.0;
          for (k=0; k<=n-1; k++)
            p=p+x[i*n+k]*x[j*n+k];
          b[j*mm+i]=p;
          b[i*mm+j]=p;
        }
    a[m]=0.0;
    for (i=0; i<=n-1; i++)
      a[m]=a[m]+y[i];
    for (i=0; i<=m-1; i++)
      { a[i]=0.0;
        for (j=0; j<=n-1; j++)
          a[i]=a[i]+x[i*n+j]*y[j];
      }
    achol(b,mm,1,a);
    yy=0.0;
    for (i=0; i<=n-1; i++)
      yy=yy+y[i]/n;
    q=0.0; e=0.0; u=0.0;
    for (i=0; i<=n-1; i++)
      { p=a[m];
        for (j=0; j<=m-1; j++)
          p=p+a[j]*x[j*n+i];
        q=q+(y[i]-p)*(y[i]-p);
        e=e+(y[i]-yy)*(y[i]-yy);
        u=u+(yy-p)*(yy-p);
      }
    s=sqrt(q/n);
    r=sqrt(1.0-q/e);
    for (j=0; j<=m-1; j++)
      { p=0.0;
        for (i=0; i<=n-1; i++)
          { pp=a[m];
            for (k=0; k<=m-1; k++)
              if (k!=j) pp=pp+a[k]*x[k*n+i];
            p=p+(y[i]-pp)*(y[i]-pp);
          }
        v[j]=sqrt(1.0-q/p);
      }
    dt[0]=q; dt[1]=s; dt[2]=r; dt[3]=u;
    free(b); return;
  }
  
    void __stdcall isqt3(int n,int k,double *x,double f1,double f2,double eps,double *xx,double *b,double *v,double *s,double *dt,double *ye,double *yr,double *r)
  { int i,j,ii,m,imi,imx,l,it;
    double z,phi,sd,vmi,vmx,q,fmi,fmx;
    m=n+1; q=0.0;
    for (j=0; j<=n; j++)
      { z=0.0;
        for (i=0; i<=k-1; i++)
          z=z+x[i*m+j]/k;
        xx[j]=z;
      }
    for (i=0; i<=n; i++)
      for (j=0; j<=i; j++)
        { z=0.0;
          for (ii=0; ii<=k-1; ii++)
            z=z+(x[ii*m+i]-xx[i])*(x[ii*m+j]-xx[j]);
          r[i*m+j]=z;
        }
    for (i=0; i<=n; i++)
      ye[i]=sqrt(r[i*m+i]);
    for (i=0; i<=n; i++)
      for (j=0; j<=i; j++)
        { r[i*m+j]=r[i*m+j]/(ye[i]*ye[j]);
          r[j*m+i]=r[i*m+j];
        }
    phi=k-1.0;
    sd=ye[n]/sqrt(k-1.0);
    it=1;
    while (it==1)
      { it=0;
        vmi=1.0e+35; vmx=0.0;
        imi=-1; imx=-1;
        for (i=0; i<=n; i++)
          { v[i]=0.0; b[i]=0.0; s[i]=0.0;}
        for (i=0; i<=n-1; i++)
          if (r[i*m+i]>=eps)
            { v[i]=r[i*m+n]*r[n*m+i]/r[i*m+i];
              if (v[i]>=0.0)
                { if (v[i]>vmx)
                    { vmx=v[i]; imx=i;}
                }
              else
                { b[i]=r[i*m+n]*ye[n]/ye[i];
                  s[i]=sqrt(r[i*m+i])*sd/ye[i];
                  if (fabs(v[i])<vmi)
                    { vmi=fabs(v[i]); imi=i;}
                }
            }
        if (phi!=n-1.0)
          { z=0.0;
            for (i=0; i<=n-1; i++)
              z=z+b[i]*xx[i];
            b[n]=xx[n]-z; s[n]=sd; v[n]=q;
          }
        else
          { b[n]=xx[n]; s[n]=sd;}
        fmi=vmi*phi/r[n*m+n];
        fmx=(phi-1.0)*vmx/(r[n*m+n]-vmx);
        if ((fmi<f2)||(fmx>=f1))
          { if (fmi<f2)
              { phi=phi+1.0; l=imi;}
            else
              { phi=phi-1.0; l=imx;}
            for (i=0; i<=n; i++)
              if (i!=l)
                for (j=0; j<=n; j++)
                  if (j!=l)
                    r[i*m+j]=r[i*m+j]-
                             (r[l*m+j]/r[l*m+l])*r[i*m+l];
            for (j=0; j<=n; j++)
              if (j!=l)
                r[l*m+j]=r[l*m+j]/r[l*m+l];
            for (i=0; i<=n; i++)
              if (i!=l)
                r[i*m+l]=-r[i*m+l]/r[l*m+l];
            r[l*m+l]=1.0/r[l*m+l];
            q=r[n*m+n]*ye[n]*ye[n];
            sd=sqrt(r[n*m+n]/phi)*ye[n];
            dt[0]=sqrt(1.0-r[n*m+n]);
            dt[1]=(phi*(1.0-r[n*m+n]))/
		  ((k-phi-1.0)*r[n*m+n]);
            it=1;
          }
      }
    for (i=0; i<=k-1; i++)
      { z=0.0;
        for (j=0; j<=n-1; j++)
          z=z+b[j]*x[i*m+j];
        ye[i]=b[n]+z; yr[i]=x[i*m+n]-ye[i];
      }
    return;
  }
  void __stdcall kfour(double *f,int n,double *a,double *b)
  { int i,j;
    double t,c,s,c1,s1,u1,u2,u0;
    t=6.283185306/(2.0*n+1.0);
    c=cos(t); s=sin(t);
    t=2.0/(2.0*n+1.0); c1=1.0; s1=0.0;
    for (i=0; i<=n; i++)
      { u1=0.0; u2=0.0;
        for (j=2*n; j>=1; j--)
          { u0=f[j]+2.0*c1*u1-u2;
            u2=u1; u1=u0;
          }
        a[i]=t*(f[0]+u1*c1-u2);
        b[i]=t*u1*s1;
        u0=c*c1-s*s1; s1=c*s1+s*c1; c1=u0;
      }
    return;
  }
  void __stdcall kkabg(int n,double *x,double t,double a,double b,double c,double *y)
  { int i;
    double s1,ss,v1,vv,a1,aa;
    aa=0.0; vv=0.0;ss=0.0;
    for (i=0; i<=n-1; i++)
      { s1=ss+t*vv+t*t*aa/2.0;
        v1=vv+t*aa; a1=aa;
        ss=s1+a*(x[i]-s1); y[i]=ss;
        vv=v1+b*(x[i]-s1);
        aa=a1+2.0*c*(x[i]-s1)/(t*t);
      }
    return;
  }
   void __stdcall kkfft(double *pr,double *pi,int n,int k,double *fr,double *fi,int l,int il)
  { int it,m,is,i,j,nv,l0;
    double p,q,s,vr,vi,poddr,poddi;
    for (it=0; it<=n-1; it++)
      { m=it; is=0;
        for (i=0; i<=k-1; i++)
          { j=m/2; is=2*is+(m-2*j); m=j;}
        fr[it]=pr[is]; fi[it]=pi[is];
      }
    pr[0]=1.0; pi[0]=0.0;
    p=6.283185306/(1.0*n);
    pr[1]=cos(p); pi[1]=-sin(p);
    if (l!=0) pi[1]=-pi[1];
    for (i=2; i<=n-1; i++)
      { p=pr[i-1]*pr[1]; q=pi[i-1]*pi[1];
        s=(pr[i-1]+pi[i-1])*(pr[1]+pi[1]);
        pr[i]=p-q; pi[i]=s-p-q;
      }
    for (it=0; it<=n-2; it=it+2)
      { vr=fr[it]; vi=fi[it];
        fr[it]=vr+fr[it+1]; fi[it]=vi+fi[it+1];
        fr[it+1]=vr-fr[it+1]; fi[it+1]=vi-fi[it+1];
      }
    m=n/2; nv=2;
    for (l0=k-2; l0>=0; l0--)
      { m=m/2; nv=2*nv;
        for (it=0; it<=(m-1)*nv; it=it+nv)
          for (j=0; j<=(nv/2)-1; j++)
            { p=pr[m*j]*fr[it+j+nv/2];
              q=pi[m*j]*fi[it+j+nv/2];
              s=pr[m*j]+pi[m*j];
              s=s*(fr[it+j+nv/2]+fi[it+j+nv/2]);
              poddr=p-q; poddi=s-p-q;
              fr[it+j+nv/2]=fr[it+j]-poddr;
              fi[it+j+nv/2]=fi[it+j]-poddi;
              fr[it+j]=fr[it+j]+poddr;
              fi[it+j]=fi[it+j]+poddi;
            }
      }
    if (l!=0)
      for (i=0; i<=n-1; i++)
        { fr[i]=fr[i]/(1.0*n);
          fi[i]=fi[i]/(1.0*n);
        }
    if (il!=0)
      for (i=0; i<=n-1; i++)
        { pr[i]=sqrt(fr[i]*fr[i]+fi[i]*fi[i]);
          if (fabs(fr[i])<0.000001*fabs(fi[i]))
            { if ((fi[i]*fr[i])>0) pi[i]=90.0;
              else pi[i]=-90.0;
            }
          else
            pi[i]=atan(fi[i]/fr[i])*360.0/6.283185306;
        }
    return;
  }
   void __stdcall kkfwt(double *p,int n,int k,double *x)
  { int m,l,it,ii,i,j,is;
    double q;
    m=1; l=n; it=2;
    x[0]=1; ii=n/2; x[ii]=2;
    for (i=1; i<=k-1; i++)
      { m=m+m; l=l/2; it=it+it;
        for (j=0; j<=m-1; j++)
          x[j*l+l/2]=it+1-x[j*l];
      }
    for (i=0; i<=n-1; i++)
      { ii=x[i]-1; x[i]=p[ii];}
    l=1;
    for (i=1; i<=k; i++)
      { m=n/(2*l)-1;
        for (j=0; j<=m; j++)
          { it=2*l*j;
            for (is=0; is<=l-1; is++)
              { q=x[it+is]+x[it+is+l];
                x[it+is+l]=x[it+is]-x[it+is+l];
                x[it+is]=q;
              }
          }
        l=2*l;
      }
    return;
  }
void __stdcall kkspt(int n,double *y,double *yy)
  { int i;
    if (n<5)
      { for (i=0; i<=n-1; i++) yy[i]=y[i];}
    else
      { yy[0]=69.0*y[0]+4.0*y[1]-6.0*y[2]+4.0*y[3]-y[4];
        yy[0]=yy[0]/70.0;
        yy[1]=2.0*y[0]+27.0*y[1]+12.0*y[2]-8.0*y[3];
        yy[1]=(yy[1]+2.0*y[4])/35.0;
        for (i=2; i<=n-3; i++)
          { yy[i]=-3.0*y[i-2]+12.0*y[i-1]+17.0*y[i];
            yy[i]=(yy[i]+12.0*y[i+1]-3.0*y[i+2])/35.0;
          }
        yy[n-2]=2.0*y[n-5]-8.0*y[n-4]+12.0*y[n-3];
        yy[n-2]=(yy[n-2]+27.0*y[n-2]+2.0*y[n-1])/35.0;
        yy[n-1]=-y[n-5]+4.0*y[n-4]-6.0*y[n-3];
        yy[n-1]=(yy[n-1]+4.0*y[n-2]+69.0*y[n-1])/70.0;
      }
    return;
  }
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

  int __stdcall klman(int n,int m,int k,double *f,double *q,double *r,double *h,double *y,double *x,double *p,double *g)
  { int i,j,kk,ii,l,jj,js;
    double *e,*a,*b;
    e=(double*)malloc(m*m*sizeof(double));
    l=m;
    if (l<n) l=n;
    a=(double*)malloc(l*l*sizeof(double));
    b=(double*)malloc(l*l*sizeof(double));
    for (i=0; i<=n-1; i++)
      for (j=0; j<=n-1; j++)
        { ii=i*l+j; a[ii]=0.0;
          for (kk=0; kk<=n-1; kk++)
            a[ii]=a[ii]+p[i*n+kk]*f[j*n+kk];
        }
    for (i=0; i<=n-1; i++)
      for (j=0; j<=n-1; j++)
        { ii=i*n+j; p[ii]=q[ii];
          for (kk=0; kk<=n-1; kk++)
            p[ii]=p[ii]+f[i*n+kk]*a[kk*l+j];
        }
    for (ii=2; ii<=k; ii++)
      { for (i=0; i<=n-1; i++)
        for (j=0; j<=m-1; j++)
          { jj=i*l+j; a[jj]=0.0;
            for (kk=0; kk<=n-1; kk++)
              a[jj]=a[jj]+p[i*n+kk]*h[j*n+kk];
          }
        for (i=0; i<=m-1; i++)
        for (j=0; j<=m-1; j++)
          { jj=i*m+j; e[jj]=r[jj];
            for (kk=0; kk<=n-1; kk++)
              e[jj]=e[jj]+h[i*n+kk]*a[kk*l+j];
          }
        js=brinv(e,m);
        if (js==0) 
          { free(e); free(a); free(b); return(js);}
        for (i=0; i<=n-1; i++)
        for (j=0; j<=m-1; j++)
          { jj=i*m+j; g[jj]=0.0;
            for (kk=0; kk<=m-1; kk++)
              g[jj]=g[jj]+a[i*l+kk]*e[j*m+kk];
          }
        for (i=0; i<=n-1; i++)
          { jj=(ii-1)*n+i; x[jj]=0.0;
            for (j=0; j<=n-1; j++)
              x[jj]=x[jj]+f[i*n+j]*x[(ii-2)*n+j];
          }
        for (i=0; i<=m-1; i++)
          { jj=i*l; b[jj]=y[(ii-1)*m+i];
            for (j=0; j<=n-1; j++)
              b[jj]=b[jj]-h[i*n+j]*x[(ii-1)*n+j];
          }
        for (i=0; i<=n-1; i++)
          { jj=(ii-1)*n+i;
            for (j=0; j<=m-1; j++)
              x[jj]=x[jj]+g[i*m+j]*b[j*l];
          }
        if (ii<k)
          { for (i=0; i<=n-1; i++)
            for (j=0; j<=n-1; j++)
              { jj=i*l+j; a[jj]=0.0;
                for (kk=0; kk<=m-1; kk++)
                  a[jj]=a[jj]-g[i*m+kk]*h[kk*n+j];
                if (i==j) a[jj]=1.0+a[jj];
              }
            for (i=0; i<=n-1; i++)
            for (j=0; j<=n-1; j++)
              { jj=i*l+j; b[jj]=0.0;
                for (kk=0; kk<=n-1; kk++)
                  b[jj]=b[jj]+a[i*l+kk]*p[kk*n+j];
              }
            for (i=0; i<=n-1; i++)
            for (j=0; j<=n-1; j++)
              { jj=i*l+j; a[jj]=0.0;
                for (kk=0; kk<=n-1; kk++)
                  a[jj]=a[jj]+b[i*l+kk]*f[j*n+kk];
              }
            for (i=0; i<=n-1; i++)
            for (j=0; j<=n-1; j++)
              { jj=i*n+j; p[jj]=q[jj];
                for (kk=0; kk<=n-1; kk++)
                  p[jj]=p[jj]+f[i*n+kk]*a[j*l+kk];
              }
          }
      }
    free(e); free(a); free(b);
    return(js);
  }

double __stdcall lbsl1(int n,double x)
  { int i,m;
    double t,y,z,p,q,s,b0,b1;
    static double a[6]={ 57568490574.0,-13362590354.0,
             651619640.7,-11214424.18,77392.33017,
            -184.9052456};
    static double b[6]={ 57568490411.0,1029532985.0,
             9494680.718,59272.64853,267.8532712,1.0};
    static double c[6]={ 72362614232.0,-7895059235.0,
             242396853.1,-2972611.439,15704.4826,
             -30.16036606};
    static double d[6]={ 144725228443.0,2300535178.0,
             18583304.74,99447.43394,376.9991397,1.0};
    static double e[5]={ 1.0,-0.1098628627e-02,
             0.2734510407e-04,-0.2073370639e-05,
             0.2093887211e-06};
    static double f[5]={ -0.1562499995e-01,
             0.1430488765e-03,-0.6911147651e-05,
             0.7621095161e-06,-0.934935152e-07};
    static double g[5]={ 1.0,0.183105e-02,
             -0.3516396496e-04,0.2457520174e-05,
             -0.240337019e-06};
    static double h[5]={ 0.4687499995e-01,
             -0.2002690873e-03,0.8449199096e-05,
             -0.88228987e-06,0.105787412e-06};
    t=fabs(x);
    if (n<0) n=-n;
    if (n!=1)
      { if (t<8.0)
          { y=t*t; p=a[5]; q=b[5];
	    for (i=4; i>=0; i--)
              { p=p*y+a[i]; q=q*y+b[i];}
            p=p/q;
          }
        else
          { z=8.0/t; y=z*z;
            p=e[4]; q=f[4];
            for (i=3; i>=0; i--)
              { p=p*y+e[i]; q=q*y+f[i];}
            s=t-0.785398164;
            p=p*cos(s)-z*q*sin(s);
            p=p*sqrt(0.636619772/t);
          }
      }
    if (n==0) return(p);
    b0=p;
    if (t<8.0)
      { y=t*t; p=c[5]; q=d[5];
        for (i=4; i>=0; i--)
          { p=p*y+c[i]; q=q*y+d[i];}
        p=x*p/q;
      }
    else
      { z=8.0/t; y=z*z;
        p=g[4]; q=h[4];
        for (i=3; i>=0; i--)
          { p=p*y+g[i]; q=q*y+h[i];}
        s=t-2.356194491;
        p=p*cos(s)-z*q*sin(s);
        p=p*x*sqrt(0.636619772/t)/t;
      }
    if (n==1) return(p);
    b1=p;
    if (x==0.0) return(0.0);
    s=2.0/t;
    if (t>1.0*n)
      { if (x<0.0) b1=-b1;
        for (i=1; i<=n-1; i++)
          { p=s*i*b1-b0; b0=b1; b1=p;}
      }
    else
      { m=(n+(int)sqrt(40.0*n))/2;
        m=2*m;
        p=0.0; q=0.0; b0=1.0; b1=0.0;
        for (i=m-1; i>=0; i--)
          { t=s*(i+1)*b0-b1;
            b1=b0; b0=t;
            if (fabs(b0)>1.0e+10)
              { b0=b0*1.0e-10; b1=b1*1.0e-10;
                p=p*1.0e-10; q=q*1.0e-10;
              }
            if ((i+2)%2==0) q=q+b0;
            if ((i+1)==n) p=b1;
          }
        q=2.0*q-b0; p=p/q;
      }
    if ((x<0.0)&&(n%2==1)) p=-p;
    return(p);
  }
 double __stdcall lbsl2(int n,double x)
  { int i;
    double y,z,p,q,s,b0,b1;
    double __stdcall lbsl1(int n,double x);
    static double a[6]={ -2.957821389e+9,7.062834065e+9,
             -5.123598036e+8,1.087988129e+7,-8.632792757e+4,
             2.284622733e+2};
    static double b[6]={ 4.0076544269e+10,7.452499648e+8,
           7.189466438e+6,4.74472647e+4,2.261030244e+2,1.0};
    static double c[6]={ -4.900604943e+12,1.27527439e+12,
            -5.153438139e+10,7.349264551e+8,-4.237922726e+6,
             8.511937935e+3};
    static double d[7]={ 2.49958057e+13,4.244419664e+11,
            3.733650367e+9,2.245904002e+7,1.02042605e+5,
            3.549632885e+2,1.0};
    static double e[5]={ 1.0,-0.1098628627e-02,
             0.2734510407e-04,-0.2073370639e-05,
             0.2093887211e-06};
    static double f[5]={ -0.1562499995e-01,
             0.1430488765e-03,-0.6911147651e-05,
             0.7621095161e-06,-0.934935152e-07};
    static double g[5]={ 1.0,0.183105e-02,
             -0.3516396496e-04,0.2457520174e-05,
             -0.240337019e-06};
    static double h[5]={ 0.4687499995e-01,
             -0.2002690873e-03,0.8449199096e-05,
             -0.88228987e-06,0.105787412e-06};
    if (n<0) n=-n;
    if (x<0.0) x=-x;
    if (x==0.0) return(-1.0e+70);
    if (n!=1)
      { if (x<8.0)
          { y=x*x; p=a[5]; q=b[5];
	    for (i=4; i>=0; i--)
              { p=p*y+a[i]; q=q*y+b[i];}
            p=p/q+0.636619772*lbsl1(0,x)*log(x);
          }
        else
          { z=8.0/x; y=z*z;
            p=e[4]; q=f[4];
            for (i=3; i>=0; i--)
              { p=p*y+e[i]; q=q*y+f[i];}
            s=x-0.785398164;
            p=p*sin(s)+z*q*cos(s);
            p=p*sqrt(0.636619772/x);
          }
      }
    if (n==0) return(p);
    b0=p;
    if (x<8.0)
      { y=x*x; p=c[5]; q=d[6];
        for (i=4; i>=0; i--)
          { p=p*y+c[i]; q=q*y+d[i+1];}
        q=q*y+d[0];
        p=x*p/q+0.636619772*(lbsl1(1,x)*log(x)-1.0/x);;
      }
    else
      { z=8.0/x; y=z*z;
        p=g[4]; q=h[4];
        for (i=3; i>=0; i--)
          { p=p*y+g[i]; q=q*y+h[i];}
        s=x-2.356194491;
        p=p*sin(s)+z*q*cos(s);
        p=p*sqrt(0.636619772/x);
      }
    if (n==1) return(p);
    b1=p;
    s=2.0/x;
    for (i=1; i<=n-1; i++)
      { p=s*i*b1-b0; b0=b1; b1=p;}
    return(p);
  }
double __stdcall lbsl3(int n,double x)
  { int i,m;
    double t,y,p,b0,b1,q;
    static double a[7]={ 1.0,3.5156229,3.0899424,1.2067492,
                         0.2659732,0.0360768,0.0045813};
    static double b[7]={ 0.5,0.87890594,0.51498869,
              0.15084934,0.02658773,0.00301532,0.00032411};
    static double c[9]={ 0.39894228,0.01328592,0.00225319,
                        -0.00157565,0.00916281,-0.02057706,
                         0.02635537,-0.01647633,0.00392377};
    static double d[9]={ 0.39894228,-0.03988024,-0.00362018,
                        0.00163801,-0.01031555,0.02282967,
                        -0.02895312,0.01787654,-0.00420059};
    if (n<0) n=-n;
    t=fabs(x);
    if (n!=1)
      { if (t<3.75)
          { y=(x/3.75)*(x/3.75); p=a[6];
            for (i=5; i>=0; i--)
              p=p*y+a[i];
          }
        else
          { y=3.75/t; p=c[8];
            for (i=7; i>=0; i--)
              p=p*y+c[i];
            p=p*exp(t)/sqrt(t);
          }
      }
    if (n==0) return(p);
    q=p;
    if (t<3.75)
      { y=(x/3.75)*(x/3.75); p=b[6];
        for (i=5; i>=0; i--) p=p*y+b[i];
        p=p*t;
      }
    else
      { y=3.75/t; p=d[8];
        for (i=7; i>=0; i--) p=p*y+d[i];
        p=p*exp(t)/sqrt(t);
      }
    if (x<0.0) p=-p;
    if (n==1) return(p);
    if (x==0.0) return(0.0);
    y=2.0/t; t=0.0; b1=1.0; b0=0.0;
    m=n+(int)sqrt(40.0*n);
    m=2*m;
    for (i=m; i>0; i--)
      { p=b0+i*y*b1; b0=b1; b1=p;
        if (fabs(b1)>1.0e+10)
          { t=t*1.0e-10; b0=b0*1.0e-10;
            b1=b1*1.0e-10;
          }
        if (i==n) t=b0;
      }
    p=t*q/b1;
    if ((x<0.0)&&(n%2==1)) p=-p;
    return(p);
  }
double __stdcall lbsl4(int n,double x)
  { int i;
    double y,p,b0,b1;
    double __stdcall lbsl3(int n,double x);
    static double a[7]={ -0.57721566,0.4227842,0.23069756,
           0.0348859,0.00262698,0.0001075,0.0000074};
    static double b[7]={ 1.0,0.15443144,-0.67278579,
           -0.18156897,-0.01919402,-0.00110404,-0.00004686};
    static double c[7]={ 1.25331414,-0.07832358,0.02189568,
           -0.01062446,0.00587872,-0.0025154,0.00053208};
    static double d[7]={ 1.25331414,0.23498619,-0.0365562,
           0.01504268,-0.00780353,0.00325614,-0.00068245};
    if (n<0) n=-n;
    if (x<0.0) x=-x;
    if (x==0.0) return(1.0e+70);
    if (n!=1)
      { if (x<=2.0)
          { y=x*x/4.0; p=a[6];
            for (i=5; i>=0; i--) p=p*y+a[i];
            p=p-lbsl3(0,x)*log(x/2.0);
          }
        else
          { y=2.0/x; p=c[6];
            for (i=5; i>=0; i--) p=p*y+c[i];
            p=p*exp(-x)/sqrt(x);
          }
      }
    if (n==0) return(p);
    b0=p;
    if (x<=2.0)
      { y=x*x/4.0; p=b[6];
        for (i=5; i>=0; i--) p=p*y+b[i];
        p=p/x+lbsl3(1,x)*log(x/2.0);
      }
    else
      { y=2.0/x; p=d[6];
        for (i=5; i>=0; i--) p=p*y+d[i];
        p=p*exp(-x)/sqrt(x);
      }
    if (n==1) return(p);
    b1=p;
    y=2.0/x;
    for (i=1; i<n; i++)
      { p=b0+i*y*b1; b0=b1; b1=p;}
    return(p);
  }
  double __stdcall lcoss(double x)
  { int m,i,j;
    double s,p,ep,h,aa,bb,w,xx,g,r,q;
    static double t[5]={-0.9061798459,-0.5384693101,0.0,
                         0.5384693101,0.9061798459};
    static double c[5]={0.2369268851,0.4786286705,0.5688888889,
                        0.4786286705,0.2369268851};
    m=1;
    if (x==0) x=1.0e-35;
    if (x<0.0) x=-x;
    r=0.57721566490153286060651;
    q=r+log(x);
    h=x; s=fabs(0.0001*h);
    p=1.0e+35; ep=0.000001; g=0.0;
    while ((ep>=0.0000001)&&(fabs(h)>s))
      { g=0.0;
        for (i=1;i<=m;i++)
          { aa=(i-1.0)*h; bb=i*h;
            w=0.0;
            for (j=0;j<=4;j++)
              { xx=((bb-aa)*t[j]+(bb+aa))/2.0;
                w=w+(1.0-cos(xx))/xx*c[j];
              }
            g=g+w;
          }
        g=g*h/2.0;
        ep=fabs(g-p)/(1.0+fabs(g));
        p=g; m=m+1; h=x/m;
      }
    g=q-g;
    return(g);
  }
   static double __stdcall fk(double k,double f)
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
  double __stdcall lelp1(double k,double f)
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

static double ek(double k,double f)
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
                w=w+q*c[j];
              }
            g=g+w;
          }
        g=g*h/2.0;
        ep=fabs(g-p)/(1.0+fabs(g));
        p=g; m=m+m; h=0.5*h;
      }
    return(g);
  }

  double __stdcall lelp2(double k,double f)
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
      ff=ek(k,y);
    else
      { ff=ek(k,pi/2.0);
        ff=2.0*n*ff+e*ek(k,y);
      }
    if (f<0.0) ff=-ff;
    return(ff);
  }
 double __stdcall lexpp(double x)
  { int m,i,j;
    double s,p,ep,h,aa,bb,w,xx,g,r,q;
    static double t[5]={-0.9061798459,-0.5384693101,0.0,
                         0.5384693101,0.9061798459};
    static double c[5]={0.2369268851,0.4786286705,0.5688888889,
                        0.4786286705,0.2369268851};
    m=1;
    if (x==0) x=1.0e-10;
    if (x<0.0) x=-x;
    r=0.57721566490153286060651;
    q=r+log(x);
    h=x; s=fabs(0.0001*h);
    p=1.0e+35; ep=0.000001; g=0.0;
    while ((ep>=0.0000001)&&(fabs(h)>s))
      { g=0.0;
        for (i=1;i<=m;i++)
          { aa=(i-1.0)*h; bb=i*h;
            w=0.0;
            for (j=0;j<=4;j++)
              { xx=((bb-aa)*t[j]+(bb+aa))/2.0;
                w=w+(exp(-xx)-1.0)/xx*c[j];
              }
            g=g+w;
          }
        g=g*h/2.0;
        ep=fabs(g-p)/(1.0+fabs(g));
        p=g; m=m+1; h=x/m;
      }
    g=q+g;
    return(g);
  }
  double __stdcall lgam1(double x)
  { int i;
    double y,t,s,u;
    static double a[11]={ 0.0000677106,-0.0003442342,
           0.0015397681,-0.0024467480,0.0109736958,
           -0.0002109075,0.0742379071,0.0815782188,
           0.4118402518,0.4227843370,1.0};
    if (x<=0.0)
      { printf("err**x<=0!\n"); return(-1.0);}
    y=x;
    if (y<=1.0)
      { t=1.0/(y*(y+1.0)); y=y+2.0;}
    else if (y<=2.0)
      { t=1.0/y; y=y+1.0;}
    else if (y<=3.0) t=1.0;
    else
      { t=1.0;
        while (y>3.0)
          { y=y-1.0; t=t*y;}
      }
    s=a[0]; u=y-2.0;
    for (i=1; i<=10; i++)
      s=s*u+a[i];
    s=s*t;
    return(s);
  }
  double __stdcall lgam2(double a,double x)
  { int n;
    double p,q,d,s,s1,p0,q0,p1,q1,qq;
    if ((a<=0.0)||(x<0.0))
      { if (a<=0.0) printf("err**a<=0!\n");
        if (x<0.0) printf("err**x<0!\n");
        return(-1.0);
      }
    if (x+1.0==1.0) return(0.0);
    if (x>1.0e+35) return(1.0);
    q=log(x); q=a*q; qq=exp(q);
    if (x<1.0+a)
      { p=a; d=1.0/a; s=d;
        for (n=1; n<=100; n++)
          { p=1.0+p; d=d*x/p; s=s+d;
	    if (fabs(d)<fabs(s)*1.0e-07)
              { s=s*exp(-x)*qq/lgam1(a);
                return(s);
              }
          }
      }
    else
      { s=1.0/x; p0=0.0; p1=1.0; q0=1.0; q1=x;
        for (n=1; n<=100; n++)
          { p0=p1+(n-a)*p0; q0=q1+(n-a)*q0;
            p=x*p0+n*p1; q=x*q0+n*q1;
            if (fabs(q)+1.0!=1.0)
              { s1=p/q; p1=p; q1=q;
                if (fabs((s1-s)/s1)<1.0e-07)
                  { s=s1*exp(-x)*qq/lgam1(a);
                    return(1.0-s);
                  }
                s=s1;
              }
            p1=p; q1=q;
          }
      }
    printf("a too large !\n");
    s=1.0-s*exp(-x)*qq/lgam1(a);
    return(s);
  }
   double __stdcall lsinn(double x)
  { int m,i,j;
    double s,p,ep,h,aa,bb,w,xx,g;
    static double t[5]={-0.9061798459,-0.5384693101,0.0,
                         0.5384693101,0.9061798459};
    static double c[5]={0.2369268851,0.4786286705,0.5688888889,
                        0.4786286705,0.2369268851};
    m=1;
    if (x==0) return(0.0);
    h=fabs(x);  s=fabs(0.0001*h);
    p=1.0e+35; ep=0.000001; g=0.0;
    while ((ep>=0.0000001)&&(fabs(h)>s))
      { g=0.0;
        for (i=1;i<=m;i++)
          { aa=(i-1.0)*h; bb=i*h;
            w=0.0;
            for (j=0;j<=4;j++)
              { xx=((bb-aa)*t[j]+(bb+aa))/2.0;
                w=w+sin(xx)/xx*c[j];
              }
            g=g+w;
          }
        g=g*h/2.0;
        ep=fabs(g-p)/(1.0+fabs(g));
        p=g; m=m+1; h=fabs(x)/m;
      }
    return(g);
  }
 static double beta(double a,double b,double x)
  { int k;
    double d,p0,q0,p1,q1,s0,s1;
    p0=0.0; q0=1.0; p1=1.0; q1=1.0;
    for (k=1; k<=100; k++)
      { d=(a+k)*(a+b+k)*x;
        d=-d/((a+k+k)*(a+k+k+1.0));
        p0=p1+d*p0; q0=q1+d*q0; s0=p0/q0;
        d=k*(b-k)*x;
        d=d/((a+k+k-1.0)*(a+k+k));
        p1=p0+d*p1; q1=q0+d*q1; s1=p1/q1;
        if (fabs(s1-s0)<fabs(s1)*1.0e-07)
          return(s1);
      }
    printf("a or b too big !");
    return(s1);
  }
  double __stdcall lbeta(double a,double b,double x)
  { double y;
    if (a<=0.0)
      { printf("err**a<=0!"); return(-1.0);}
    if (b<=0.0)
      { printf("err**b<=0!"); return(-1.0);}
    if ((x<0.0)||(x>1.0))
      { printf("err**x<0 or x>1 !");
        return(1.0e+70);
      }
    if ((x==0.0)||(x==1.0)) y=0.0;
    else
      { y=a*log(x)+b*log(1.0-x);
        y=exp(y);
        y=y*lgam1(a+b)/(lgam1(a)*lgam1(b));
      }
    if (x<(a+1.0)/(a+b+2.0))
      y=y*beta(a,b,x)/a;
    else
      y=1.0-y*beta(b,a,1.0-x)/b;
    return(y);
  }
    double __stdcall lchii(double x,int n)
  { double y;
    if (x<0.0) x=-x;
    y=lgam2(n/2.0,x/2.0);
    return(y);
  }
  double __stdcall lerrf(double x)
  { double y;
    if (x>=0.0)
      y=lgam2(0.5,x*x);
    else
      y=-lgam2(0.5,x*x);
    return(y);
  }
    double __stdcall lffff(double f,int n1,int n2)
  { double y;
    if (f<0.0) f=-f;
    y=lbeta(n2/2.0,n1/2.0,n2/(n2+n1*f));
    return(y);
  }
    double __stdcall lgass(double a,double d,double x)
  { double y;
    if (d<=0.0) d=1.0e-10;
    y=0.5+0.5*lerrf((x-a)/(sqrt(2.0)*d));
    return(y);
  }
  double __stdcall lstdt(double t,int n)
  { double y;
    if (t<0.0) t=-t;
    y=1.0-lbeta(n/2.0,0.5,n/(n+t*t));
    return(y);
  }
  double __stdcall mgrn1(double u,double g,double *r)
  { int i,m;
    double s,w,v,t;
    s=65536.0; w=2053.0; v=13849.0;
    t=0.0;
    for (i=1; i<=12; i++)
      { *r=(*r)*w+v; m=(int)(*r/s);
        *r=*r-m*s; t=t+(*r)/s;
      }
    t=u+g*(t-6.0);
    return(t);
  }
    void __stdcall mgrns(double u,double g,double *r,int n,double *a)
  { int i,k,m;
    double s,w,v,t;
    s=65536.0; w=2053.0; v=13849.0;
    for (k=0; k<=n-1; k++)
      { t=0.0;
        for (i=1; i<=12; i++)
          { *r=(*r)*w+v; m=(int)(*r/s);
            *r=*r-m*s; t=t+(*r)/s;
          }
        a[k]=u+g*(t-6.0);
      }
    return;
  }
    int __stdcall mrab1(int a,int b,int *r)
  { int k,l,m,i,p;
    k=b-a+1; l=2;
    while (l<k) l=l+l;
    m=4*l; k=*r; i=1;
    while (i<=1)
      { k=k+k+k+k+k;
	k=k%m; l=k/4+a;
        if (l<=b) { p=l; i=i+1;}
      }
    *r=k;
    return(p);
  }
    void __stdcall mrabs(int a,int b,int *r,int *p,int n)
  { int k,l,m,i;
    k=b-a+1; l=2;
    while (l<k) l=l+l;
    m=4*l; k=*r; i=0;
    while (i<=n-1)
      { k=k+k+k+k+k;
	k=k%m; l=k/4+a;
        if (l<=b) { p[i]=l; i=i+1;}
      }
    *r=k;
    return;
  }
double __stdcall mrnd1(double *r)
  { int m;
    double s,u,v,p;
    s=65536.0; u=2053.0; v=13849.0;
    m=(int)(*r/s); *r=*r-m*s;
    *r=u*(*r)+v; m=(int)(*r/s);
    *r=*r-m*s; p=*r/s;
    return(p);
  }
  void __stdcall mrnds(double *r,double *p,int n)
  { int i,m;
    double s,u,v;
    s=65536.0; u=2053.0; v=13849.0;
    for (i=0; i<=n-1; i++)
      { *r=u*(*r)+v; m=(int)(*r/s);
        *r=*r-m*s; p[i]=*r/s;
      }
    return;
  }
  double __stdcall nbply(double *a,int m,int n,double x,double y)
  { int i,j;
    double u,s,xx;
    u=0.0; xx=1.0;
    for (i=0; i<=m-1; i++)
      { s=a[i*n+n-1]*xx;
        for (j=n-2; j>=0; j--)
          s=s*y+a[i*n+j]*xx;
        u=u+s; xx=xx*x;
      }
    return(u);
  }
  double __stdcall nfpqv(double *x,double *b,int n,double t)
  { int k;
    double u;
    u=b[n-1];
    for (k=n-2; k>=0; k--)
      { if (fabs(u)+1.0==1.0)
           u=1.0e+35*(t-x[k])/fabs(t-x[k]);
        else
           u=b[k]+(t-x[k])/u;
      }
    return(u);
  }
  void __stdcall npdiv(double *p,int m,double *q,int n,double *s,int k,double *r,int l)
    { int i,j,mm,ll;
    for (i=0; i<=k-1; i++) s[i]=0.0;
    if (q[n-1]+1.0==1.0) return;
    ll=m-1;
    for (i=k; i>=1; i--)
      { s[i-1]=p[ll]/q[n-1];
        mm=ll;
        for (j=1; j<=n-1; j++)
          { p[mm-1]=p[mm-1]-s[i-1]*q[n-j-1];
            mm=mm-1;
          }
        ll=ll-1;
      }
    for (i=0; i<=l-1; i++) r[i]=p[i];
    return;
  }
    void __stdcall nplys(double *a,int n,double *x,int m,double *p)
  { int i,j,mm,nn,ll,t,s,kk,k;
    double *b,y,z;
    b=(double*)malloc(2*n*sizeof(double));
    y=a[n-1];
    for (i=0; i<=n-1; i++) b[i]=a[i]/y;
    k=log(n-0.5)/log(2.0)+1;
    nn=1;
    for (i=0; i<=k-1; i++) nn=2*nn;
    for (i=n; i<nn-1; i++) b[i]=0.0;
    b[nn-1]=1.0;
    t=nn; s=1;
    for (i=1; i<=k-1; i++)
      { t=t/2; mm=-t;
        for (j=1; j<=s; j++)
          { mm=mm+t+t; b[mm-1]=b[mm-1]-1.0; 
            for (kk=2; kk<=t; kk++)
              b[mm-kk]=b[mm-kk]-b[mm-1]*b[mm+t-kk];
          }
        s=s+s;
      }
    for (kk=1; kk<=m; kk++)
      { for (i=0; i<=(nn-2)/2; i++)
           a[i]=x[kk-1]+b[2*i];
        mm=1; z=x[kk-1];
        for (i=1; i<=k-1; i++)
          { mm=mm+mm; ll=mm+mm; z=z*z;
            for (j=0; j<=nn-1; j=j+ll)
              a[j/2]=a[j/2]+a[(j+mm)/2]*(z+b[j+mm-1]);
          }
        z=z*z/x[kk-1];
        if (nn!=n) a[0]=a[0]-z;
        p[kk-1]=a[0]*y;
      }
    return;
  }
double __stdcall nplyv(double *a,int n,double x)
  { int i;
    double u;
    u=a[n-1];
    for (i=n-2; i>=0; i--)
      u=u*x+a[i];
    return(u);
  }
    void __stdcall npmul(double *p,int m,double *q,int n,double *s,int k)
  { int i,j;
    for (i=0; i<=k-1; i++) s[i]=0.0;
    for (i=0; i<=m-1; i++)
    for (j=0; j<=n-1; j++)
      s[i+j]=s[i+j]+p[i]*q[j];
    return;
  }
void __stdcall occos(double x,double y,double *u,double *v)
  { double p,q;
    p=exp(y); q=exp(-y);
    *u=cos(x)*(p+q)/2.0; *v=-sin(x)*(p-q)/2.0;
    return;
  }
  void __stdcall ocdiv(double a,double b,double c,double d,double *e,double *f)
  { double p,q,s,w;
    p=a*c; q=-b*d; s=(a+b)*(c-d);
    w=c*c+d*d;
    if (w+1.0==1.0) 
      { *e=1.0e+35*a/fabs(a);
        *f=1.0e+35*b/fabs(b);
      }
    else
      { *e=(p-q)/w; *f=(s-p-q)/w; }
    return;
  }
  void __stdcall ocexp(double x,double y,double *u,double *v)
  { double p;
    p=exp(x);
    *u=p*cos(y); *v=p*sin(y);
    return;
  }
   void __stdcall oclog(double x,double y,double *u,double *v)
  { double p;
    p=log(sqrt(x*x+y*y));
    *u=p; *v=atan2(y,x);
    return;
  }
    void __stdcall ocmul(double a,double b,double c,double d,double *e,double *f)
  { double p,q,s;
    p=a*c; q=b*d; s=(a+b)*(c+d);
    *e=p-q; *f=s-p-q;
    return;
  }
  void __stdcall ocsin(double x,double y,double *u,double *v)
  { double p,q;
    p=exp(y); q=exp(-y);
    *u=sin(x)*(p+q)/2.0; *v=cos(x)*(p-q)/2.0;
    return;
  }
    void __stdcall ontrt(double x,double y,int n,double *u,double *v)
  { int k;
    double r,q,t;
    if (n<1) return;
    q=atan2(y,x);
    r=sqrt(x*x+y*y);
    if (r+1.0!=1.0)
      { r=(1.0/n)*log(r); r=exp(r);}
    for (k=0; k<=n-1; k++)
      { t=(2.0*k*3.1415926+q)/n;
        u[k]=r*cos(t); v[k]=r*sin(t);
      }
    return;
  }
  void __stdcall oplot(int n,double *x,double *y,char xc,char yc,char c,double *xd,double *yd)
  { int i,j,k;
    double xx,yy;
    char xy[72][72];
    for (i=0; i<=71; i++)
    for (j=0; j<=71; j++) xy[i][j]=' ';
    xy[0][35]='Y';
    for (i=1; i<=71; i++) xy[i][36]=yc;
    xy[36][71]='X';
    for (j=0; j<=70; j++) xy[36][j]=xc;
    xx=0.0; yy=0.0;
    for (k=0; k<=n-1; k++)
      { if (fabs(x[k])>xx) xx=fabs(x[k]);
        if (fabs(y[k])>yy) yy=fabs(y[k]);
      }
    xx=35.0/xx; yy=35.0/yy;
    for (k=0; k<=n-1; k++)
      { i=37.0-yy*y[k]-0.5;
        j=xx*x[k]+36.0-0.5;
        xy[i][j]=c;
      }
    printf("\n");
    for (i=0; i<=71; i++)
      { for (j=0; j<=71; j++)
          printf("%c",xy[i][j]);
        printf("\n");
      }
    printf("\n");
    printf("X-scale is:%13.7e\n",xx);
    printf("Y-scale is:%13.7e\n",yy);
    printf("\n");
    *xd=xx; *yd=yy;
    return;
  }
  void __stdcall opowr(double x,double y,int n,double *u,double *v)
  { double r,q;
    q=atan2(y,x);
    r=sqrt(x*x+y*y);
    if (r+1.0!=1.0)
      { r=n*log(r); r=exp(r);}
    *u=r*cos(n*q); *v=r*sin(n*q);
    return;
  }
  void __stdcall pcbub(char *p,int n)
    { int m,k,j,i;
    char d;
    k=0; m=n-1;
    while (k<m)
      { j=m-1; m=0;
        for (i=k; i<=j; i++)
          if (p[i]>p[i+1])
            { d=p[i]; p[i]=p[i+1]; p[i+1]=d; m=i;}
        j=k+1; k=0;
        for (i=m; i>=j; i--)
          if (p[i-1]>p[i])
            { d=p[i]; p[i]=p[i-1]; p[i-1]=d; k=i;}
      }
    return;
  }
  static void csift(char *p,int i,int n)
  { int j;
    char t;
    t=p[i]; j=2*(i+1)-1;
    while (j<=n)
      { if ((j<n)&&(p[j]<p[j+1])) j=j+1;
        if (t<p[j])
          { p[i]=p[j]; i=j; j=2*(i+1)-1;}
        else j=n+1;
      }
    p[i]=t;
    return;
  }
  void __stdcall pchap(char *p,int n)
  { int i,mm;
    char t;
    mm=n/2;
    for (i=mm-1; i>=0; i--)
      csift(p,i,n-1);
    for (i=n-1; i>=1; i--)
      { t=p[0]; p[0]=p[i]; p[i]=t;
        csift(p,0,i-1);
      }
    return;
  }
 static void csplit(char *p,int n,int *m)
  { int i,j,k,l;
    char t;
    i=0; j=n-1;
    k=(i+j)/2;
    if ((p[i]>=p[j])&&(p[j]>=p[k])) l=j;
    else if ((p[i]>=p[k])&&(p[k]>=p[j])) l=k;
    else l=i;
    t=p[l]; p[l]=p[i];
    while (i!=j)
      { while ((i<j)&&(p[j]>=t)) j=j-1;
        if (i<j)
          { p[i]=p[j]; i=i+1;
            while ((i<j)&&(p[i]<=t)) i=i+1;
            if (i<j)
              { p[j]=p[i]; j=j-1;}
          }
      }
    p[i]=t; *m=i;
    return;
  }

  void __stdcall pcqck(char *p,int n)
  { int m,i0,*i;
    char *s;
    i=&i0;
    if (n>10)
      { csplit(p,n,i);
        m=i0;
	pcqck(p,m);
	s=p+(i0+1);
        m=n-(i0+1);
	pcqck(s,m);
      }
    else pcbub(p,n);
    return;
  }
void __stdcall pcshl(char *p,int n)
  { int k,j,i;
    char t;
    k=n/2;
    while (k>0)
      { for (j=k; j<=n-1; j++)
          { t=p[j]; i=j-k;
            while ((i>=0)&&(p[i]>t))
              { p[i+k]=p[i]; i=i-k;}
            p[i+k]=t;
          }
        k=k/2;
      }
    return;
  }
   
    static void isift(int *p,int i,int n)
  { int j,t;
    t=p[i]; j=2*(i+1)-1;
    while (j<=n)
      { if ((j<n)&&(p[j]<p[j+1])) j=j+1;
        if (t<p[j])
          { p[i]=p[j]; i=j; j=2*(i+1)-1;}
        else j=n+1;
      }
    p[i]=t;
    return;
  }

  void __stdcall pihap(int *p,int n)
  { int i,mm,t;
    mm=n/2;
    for (i=mm-1; i>=0; i--)
      isift(p,i,n-1);
    for (i=n-1; i>=1; i--)
      { t=p[0]; p[0]=p[i]; p[i]=t;
        isift(p,0,i-1);
      }
    return;
  }
   static void isplit(int *p,int n,int *m)
  { int i,j,k,l,t;
    i=0; j=n-1;
    k=(i+j)/2;
    if ((p[i]>=p[j])&&(p[j]>=p[k])) l=j;
    else if ((p[i]>=p[k])&&(p[k]>=p[j])) l=k;
    else l=i;
    t=p[l]; p[l]=p[i];
    while (i!=j)
      { while ((i<j)&&(p[j]>=t)) j=j-1;
        if (i<j)
          { p[i]=p[j]; i=i+1;
            while ((i<j)&&(p[i]<=t)) i=i+1;
            if (i<j)
              { p[j]=p[i]; j=j-1;}
          }
      }
    p[i]=t; *m=i;
    return;
  }

void __stdcall pibub(int *p,int n)
{ int m,k,j,i,d;
k=0; m=n-1;
while (k<m)
{ j=m-1; m=0;
for (i=k; i<=j; i++)
if (p[i]>p[i+1])
{ d=p[i]; p[i]=p[i+1]; p[i+1]=d; m=i;}
j=k+1; k=0;
for (i=m; i>=j; i--)
if (p[i-1]>p[i])
{ d=p[i]; p[i]=p[i-1]; p[i-1]=d; k=i;}
}
return;
}

void __stdcall mysort1(int *p,int n,int ascending)
{
	int temp,i,j;
	if(ascending)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<i;j++)
			{
				if(p[j]>p[i])//选择升序排序
				{
					temp=p[i];
					//插入
					for(int k=i;k>=j;k--)p[k]=p[k-1];
					p[j]=temp;
				}
			}
			printf("A[i=%d]=",i);
			for(int k=0;k<n;k++) 
				printf("%d",p[k]);
			printf("\n");
		}
	}
	else
	{
		for(i=0;i<n-1;i++)
		{
			for(j=0;j<n-1;j++)
				if(p[j]<p[j+1])//选择降序
				{
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
				}
		}
	}
}

void __stdcall mysort2(int *p,int n,int ascending)
{ 
	int m,k,j,i,d;
	k=0; m=n-1;
	while (k<m)
	{ 
		j=m-1; m=0;
		for (i=k; i<=j; i++)
{
		if (p[i]>p[i+1])
		{ 
			d=p[i]; 
			p[i]=p[i+1]; 
			p[i+1]=d; 
			m=i;
		}
			printf("A[i=%d]=",i);
			for(int k=0;k<n;k++) 
				printf("%d",p[k]);
			printf("\n");
}
		j=k+1; 
		k=0;
		for (i=m; i>=j; i--)
{
		if (p[i-1]>p[i])
		{ 
			d=p[i]; 
			p[i]=p[i-1]; 
			p[i-1]=d; 
			k=i;
		}
			printf("A[i=%d]=",i);
			for(int k=0;k<n;k++) 
				printf("%d",p[k]);
			printf("\n");
}
	}
       if(ascending==0)
           reversed(p,n);
	return;
}

void __stdcall reversed(int* arr, int n)
{   
   for(int i=0;i<n/2;i++)
   {
      int k=n-1-i;
      int temp=arr[k];
      arr[k]=arr[i];
      arr[i]=temp;
   }
} 

  void __stdcall piqck(int *p,int n)
  { int m,i0,*i,s0,*s;
    i=&i0;
    if (n>10)
      { isplit(p,n,i);
        m=i0;
        piqck(p,m);
	s=p+(i0+1);
        m=n-(i0+1);
        piqck(s,m);
      }
    else pibub(p,n);
    return;
  }
   void __stdcall pishl(int *p,int n)
  { int k,j,i,t;
    k=n/2;
    while (k>0)
      { for (j=k; j<=n-1; j++)
          { t=p[j]; i=j-k;
            while ((i>=0)&&(p[i]>t))
              { p[i+k]=p[i]; i=i-k;}
            p[i+k]=t;
          }
        k=k/2;
      }
    return;
  }
  void __stdcall prbub(double *p,int n)
  { int m,k,j,i;
    double d;
    k=0; m=n-1;
    while (k<m)
      { j=m-1; m=0;
        for (i=k; i<=j; i++)
          if (p[i]>p[i+1])
            { d=p[i]; p[i]=p[i+1]; p[i+1]=d; m=i;}
        j=k+1; k=0;
        for (i=m; i>=j; i--)
          if (p[i-1]>p[i])
            { d=p[i]; p[i]=p[i-1]; p[i-1]=d; k=i;}
      }
    return;
  }
  static void rsift(double *p,int i,int n)
  { int j;
    double t;
    t=p[i]; j=2*(i+1)-1;
    while (j<=n)
      { if ((j<n)&&(p[j]<p[j+1])) j=j+1;
        if (t<p[j])
          { p[i]=p[j]; i=j; j=2*(i+1)-1;}
        else j=n+1;
      }
    p[i]=t;
    return;
  }

  void __stdcall prhap(double *p,int n)
  { int i,mm;
    double t;
    mm=n/2;
    for (i=mm-1; i>=0; i--)
      rsift(p,i,n-1);
    for (i=n-1; i>=1; i--)
      { t=p[0]; p[0]=p[i]; p[i]=t;
        rsift(p,0,i-1);
      }
    return;
  }
    static void rsplit(double *p,int n,int *m)
  { int i,j,k,l;
    double t;
    i=0; j=n-1;
    k=(i+j)/2;
    if ((p[i]>=p[j])&&(p[j]>=p[k])) l=j;
    else if ((p[i]>=p[k])&&(p[k]>=p[j])) l=k;
    else l=i;
    t=p[l]; p[l]=p[i];
    while (i!=j)
      { while ((i<j)&&(p[j]>=t)) j=j-1;
        if (i<j)
          { p[i]=p[j]; i=i+1;
            while ((i<j)&&(p[i]<=t)) i=i+1;
            if (i<j)
              { p[j]=p[i]; j=j-1;}
          }
      }
    p[i]=t; *m=i;
    return;
  }

  void __stdcall prqck(double *p,int n)
  { int m,i0,*i;
    double *s;
    i=&i0;
    if (n>10)
      { rsplit(p,n,i);
        m=i0;
        prqck(p,m);
	s=p+(i0+1);
        m=n-(i0+1);
        prqck(s,m);
      }
    else prbub(p,n);
    return;
  }
void __stdcall prshl(double *p,int n)
  { int k,j,i;
    double t;
    k=n/2;
    while (k>0)
      { for (j=k; j<=n-1; j++)
          { t=p[j]; i=j-k;
            while ((i>=0)&&(p[i]>t))
              { p[i+k]=p[i]; i=i-k;}
            p[i+k]=t;
          }
        k=k/2;
      }
    return;
  }
  void __stdcall ptopo(int n,int *r,int m,int *p)
  { int top,i,j,k,t,*s,*g,*f;
    struct node
      { int suc;
        int next;
      } *q;
    q=(struct node *)malloc(m*sizeof(struct node));
    f=(int*)malloc(n*sizeof(int));
    s=(int*)malloc(n*sizeof(int));
    g=(int*)malloc(n*sizeof(int));
    top=-1; t=0;
    for (k=0; k<=n-1; k++) { f[k]=0; g[k]=-1;}
    for (k=0; k<=m-1; k++)
      { i=r[k+k]; j=r[k+k+1];
        f[j-1]=f[j-1]+1;
        q[k].next=g[i-1]; q[k].suc=j; g[i-1]=k;
      }
    for (k=0; k<=n-1; k++)
      if (f[k]==0) { top=top+1; s[top]=k+1;}
    while (top!=-1)
      { i=s[top]; top=top-1; p[t]=i; t=t+1;
        k=g[i-1];
        while (k!=-1)
        { j=q[k].suc; f[j-1]=f[j-1]-1;
          if (f[j-1]==0) { top=top+1; s[top]=j;}
          k=q[k].next;
        }
      }
    for (k=0; k<=n-1; k++)
      if (f[k]!=0) { p[t]=-(k+1); t=t+1;}
    free(f); free(g); free(s); free(q);
    return;
  }
   int __stdcall qibsh(int *p,int n,int a,int b,int *m)
  { int i,j,k;
    i=1; j=n;
    while (i<=j)
      { k=(i+j)/2;
        if ((p[k-1]>=a)&&(p[k-1]<=b))
          { i=k-1; j=0;
            while ((i>=0)&&(p[i]>=a)) 
                { i=i-1; j=j+1;}
            i=i+1;
            while ((k<=n-1)&&(p[k]<=b)) 
                { k=k+1; j=j+1;}
            *m=j; return(i);
          }
        if (p[k-1]>b) j=k-1;
        else i=k+1;
      }
    while ((i>=0)&&(b<p[i])) i=i-1;
    i=i+1; *m=0;
    return(i);
  }
  int __stdcall qrbsh(double *p,int n,double a,double b,int *m)
  { int i,j,k;
    i=1; j=n;
    while (i<=j)
      { k=(i+j)/2;
        if ((p[k-1]>=a)&&(p[k-1]<=b))
          { i=k-1; j=0;
            while ((i>=0)&&(p[i]>=a)) 
                { i=i-1; j=j+1;}
            i=i+1;
            while ((k<=n-1)&&(p[k]<=b)) 
                { k=k+1; j=j+1;}
            *m=j; return(i);
          }
        if (p[k-1]>b) j=k-1;
        else i=k+1;
      }
    while ((i>=0)&&(b<p[i])) i=i-1;
    i=i+1; *m=0;
    return(i);
  }
void __stdcall ncdiv(double *pr,double *pi,int m,double *qr,double *qi,int n,double *sr,double *si,int k,double *rr,double *ri,int l)
  { int i,j,mm,ll;
    double a,b,c,d,u,v;
    for (i=0; i<=k-1; i++) 
      { sr[i]=0.0; si[i]=0.0; }
    d=qr[n-1]*qr[n-1]+qi[n-1]*qi[n-1];
    if (d+1.0==1.0) return;
    ll=m-1;
    for (i=k; i>=1; i--)
      { a=pr[ll]; b=pi[ll]; c=qr[n-1]; d=qi[n-1];
        ocdiv(a,b,c,d,&u,&v);
        sr[i-1]=u; si[i-1]=v;
        mm=ll;
        for (j=1; j<=n-1; j++)
          { a=sr[i-1]; b=si[i-1]; 
            c=qr[n-j-1]; d=qi[n-j-1];
            ocmul(a,b,c,d,&u,&v);
            pr[mm-1]=pr[mm-1]-u;
            pi[mm-1]=pi[mm-1]-v;
            mm=mm-1;
          }
        ll=ll-1;
      }
    for (i=0; i<=l-1; i++) 
      { rr[i]=pr[i]; ri[i]=pi[i]; }
    return;
  }
void __stdcall ncmul(double *pr,double *pi,int m,double *qr,double *qi,int n,double *sr,double *si,int k)
  { int i,j;
    double a,b,c,d,u,v;
    for (i=0; i<=k-1; i++)
      { sr[i]=0.0; si[i]=0.0; }
    for (i=0; i<=m-1; i++)
    for (j=0; j<=n-1; j++)
      { a=pr[i]; b=pi[i]; c=qr[j]; d=qi[j];
        ocmul(a,b,c,d,&u,&v);
        sr[i+j]=sr[i+j]+u;
        si[i+j]=si[i+j]+v;
      }
    return;
  }
  void __stdcall ncply(double *ar,double *ai,int n,double x,double y,double *u,double *v)
  { int i;
    double p,q,s,t;
    s=ar[n-1]; t=ai[n-1];
    for (i=n-2; i>=0; i--)
      { ocmul(s,t,x,y,&p,&q);
        s=p+ar[i]; t=q+ai[i];
      }
    *u=s; *v=t;
    return;
  }
  int __stdcall agmiv(double *a,int m,int n,double *b,double *x,double *aa,double eps,double *u,double *v,int ka)
  { int i,j;
    i=bginv(a,m,n,aa,eps,u,v,ka);
    if (i<0) return(-1);
    for (i=0; i<=n-1; i++)
      { x[i]=0.0;
        for (j=0; j<=m-1; j++)
          x[i]=x[i]+aa[i*m+j]*b[j];
      }
    return(1);
  }
 int agaus(double *a,double *b,int n)
  { int *js,l,k,i,j,is,p,q;
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
   int __stdcall abint(double *a,int n,double *b,double eps,double *x)
  { int i,j,k,kk;
    double *p,*r,*e,q,qq;
    p=(double*)malloc(n*n*sizeof(double));
    r=(double*)malloc(n*sizeof(double));
    e=(double*)malloc(n*sizeof(double));
    i=60;
    for (k=0; k<=n-1; k++)
    for (j=0; j<=n-1; j++)
      p[k*n+j]=a[k*n+j];
    for (k=0; k<=n-1; k++) x[k]=b[k];
    kk=agaus(p,x,n);
    if (kk==0)
      { free(p); free(r); free(e); return(kk); }
    q=1.0+eps;
    while (q>=eps)
      { if (i==0)
          { free(p); free(r); free(e); return(i); }
        i=i-1;
        brmul(a,x,n,n,1,e);
        for ( k=0; k<=n-1; k++) r[k]=b[k]-e[k];
        for ( k=0; k<=n-1; k++)
        for ( j=0; j<=n-1; j++)
           p[k*n+j]=a[k*n+j];
        kk=agaus(p,r,n);
        if (kk==0)
          { free(p); free(r); free(e); return(kk); }
        q=0.0;
        for ( k=0; k<=n-1; k++)
          { qq=fabs(r[k])/(1.0+fabs(x[k]+r[k]));
            if (qq>q) q=qq;
          }
        for ( k=0; k<=n-1; k++) x[k]=x[k]+r[k];
      }
    free(p); free(r); free(e); return(1);
  } 

//f(x)=(x+k)mod26,f^(-1)(x)=(x-k)mod26
int __stdcall fkmod26(int x,int k)
{
  int ret=(x+k)%26;
  while(ret<0){ret=ret+26;}//if(ret<0)ret=ret+26;
  while(ret>25){ret=ret-26;}//if(ret>25)ret=ret-26;
  return ret;
}

void  __stdcall ECode(char *str,int k)
{
 int nsize=strlen(str);
 for(int i=0;i<nsize;i++)
 {
    if(str[i]<='z'&&str[i]>='a')
  str[i]=fkmod26(str[i]-97,k)+97;
    if(str[i]<='Z'&&str[i]>='A')
         str[i]=fkmod26(str[i]-65,k)+65;
        }
}


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
float __stdcall dfridr(float(__stdcall *func)(float),float x,float h,float *err)
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

double __stdcall fcbsv(double a,double b,double eps,double(__stdcall *fcbsvf)(double))//切比雪夫求积法
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

double __stdcall fromb(double a,double b,double eps,double(__stdcall *frombf)(double))//龙贝格求积法
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

/*
static double __stdcall fk(double k,double f)
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

double __stdcall lelp1(double k,double f)
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
*/

//雅可比分号形式的第一类[不完全]椭圆积分Arcsn(e;x)
double __stdcall lelp1J(double(__stdcall *lelp1)(double e,double x),double e,double x)
{
  return lelp1(e,asin(x));
}

double __stdcall Arcsn(double e,double x)
{ 
    //return lelp1J(lelp1,e,x);
    return lelp1(e,asin(x));
}

/*
RK4（比Solver1D要一般）计算泛函：输入：初值X=t,y，函数f(x,y)；输出一阶常微分方程y'=f(x,y)的特解y(x)在x处的值（这里步长h=1e-2）
Solver1D计算泛函：输入：初值X=t,y，函数f(x)；输出一阶常微分方程y'=f(y)的特解y(x)的采样值（这里步长dt=0.1）
*/
double __stdcall RK4(double(__stdcall *f)(double x, double y), double x0, double y0, double xn, double h)
{
 double k1 = 0.0, k2 = 0.0, k3 = 0.0, k4 = 0.0;
 double x = 0.0, y = y0, ns;
 int nsteps, i;
 
 // Calculate nsteps
 ns = (xn - x0)/h;
 ns = ceil(ns);
 nsteps = (int) ns;  // number of steps
 h = (xn - x0)/ns;

 for(i = 0; i < nsteps; i++)
 {
     x = x0 + i * h;
     k1 = h * f(x, y);
     k2 = h * f(x + h / 2, y + k1 / 2);
     k3 = h * f(x + h / 2, y + k2 / 2);
     k4 = h * f(x + h, y + k3);
     y += k1 / 6 + k2 / 3 + k3 / 3 + k4 / 6;
}
return y;
}

double __stdcall fsimp(double a,double b,double eps,double(__stdcall *fsimpf)(double)) /*辛普森算法*/ 
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

double __stdcall Zeta(double s)
{
 int i;
 double sum=0;
 for (i=1;i<=100;i++)
  sum+=1.0/pow((double)i,s);
 return sum;
}

int __stdcall DFT1(double *pr,double *pi,double *fr,double *fi,int N,int inv)
{
    double sr,si;
    if(inv==1)
    {
      for(int j=0;j<N;j++)
      { sr=0.0;si=0.0;
        for(int k=0;k<N;k++)
        {
          sr+=pr[k]*cos(-6.2831853068*j*k/N);
          si+=pr[k]*sin(-6.2831853068*j*k/N);
         }
         fr[j]=sr;fi[j]=si;
      }
    }
    if(inv==-1)
    {
      for(int k=0;k<N;k++)
      {
         sr=0.0;si=0.0;
         for(int j=0;j<N;j++)
         {
          sr+=fr[j]*cos(6.2831853068*j*k/N)-fi[j]*sin(6.2831853068*j*k/N);
          si+=fr[k]*sin(6.2831853068*j*k/N)+fi[j]*cos(6.2831853068*j*k/N);
         }
          pr[k]=sr/N;
          pi[k]=si/N;
        }
    }
    return 0;
}

#define	PI (float)3.14159265 
// 一维FFT
#define OPT  1 // OPT = 1 光学DFT(直流成分在中间)
// OPT = 0 一般DFT(直流成分在左端)

void fft1core(float a_rl[], float a_im[], int length,int ex, float sin_tbl[], float cos_tbl[], float buf[]);
void cstb(int length, int inv, float sin_tbl[], float cos_tbl[]);
void birv(float a[], int length, int ex, float b[]);

int __stdcall FFT1(float a_rl[], float a_im[], int ex, int inv)
{
int i, length = 1;
float *sin_tbl;//Sin 数据配列
float *cos_tbl; //Cos 数据配列
float *buf; //工作用数列
for (i=0; i<ex; i++) length*=2; //计算数据个数
sin_tbl=(float *)malloc((size_t)length*sizeof(float));
cos_tbl = (float *)malloc((size_t)length*sizeof(float));
buf = (float *)malloc((size_t)length*sizeof(float));
if ((sin_tbl == NULL) || (cos_tbl == NULL) || (buf == NULL)) {
return -1;
}
cstb(length, inv, sin_tbl, cos_tbl);      //计算Sin、Cos数据
fft1core(a_rl, a_im, length, ex, sin_tbl, cos_tbl, buf);
free(sin_tbl);
free(cos_tbl);
return 0;
}

void fft1core(float a_rl[], float a_im[], int length, int ex, float sin_tbl[], float cos_tbl[], float buf[])
{
int i, j, k, w, j1, j2;
int numb, lenb, timb;
float xr, xi, yr, yi, nrml;
if (OPT==1) {
for (i = 1; i < length; i+=2) {
a_rl[i] = -a_rl[i];
a_im[i] = -a_im[i];
}
}
numb=1;
lenb=length;
for(i=0; i<ex;i++){
lenb/=2;
timb=0;
for(j=0;j<numb;j++) {
w = 0;
for (k=0; k<lenb;k++) {
j1=timb+k;
j2=j1+lenb;
xr=a_rl[j1];
xi=a_im[j1];
yr=a_rl[j2];
yi=a_im[j2];
a_rl[j1]=xr+yr;
a_im[j1]=xi+yi;
xr=xr-yr;
xi=xi-yi;
a_rl[j2] = xr*cos_tbl[w] - xi*sin_tbl[w];
a_im[j2] = xr*sin_tbl[w] + xi*cos_tbl[w];
w += numb;
}
timb += (2*lenb);
}
numb *= 2;
}
birv(a_rl, length, ex, buf); //实数数据的排列
birv(a_im, length, ex, buf); //虚数数据的排列
if(OPT==1) {
for (i = 1; i < length; i+=2) {
a_rl[i] = -a_rl[i];
a_im[i] = -a_im[i];
}
}
nrml = (float)(1.0 / sqrt((float)length));
for (i = 0; i < length; i++) {
a_rl[i] *= nrml;
a_im[i] *= nrml;
}
}

void cstb(int length, int inv, float sin_tbl[], float cos_tbl[])
{int i;
float xx, arg;
xx = (float)(((-PI) * 2.0) / (float)length);
if (inv < 0) xx = -xx;
for (i = 0; i < length; i++) {
arg = (float)i * xx;
sin_tbl[i] = (float)sin(arg);
cos_tbl[i] = (float)cos(arg);
}
}

void birv(float a[], int length, int ex, float b[])
{int i, ii, k, bit;
 for (i = 0; i < length; i++) {
for (k = 0, ii=i, bit=0; ; bit<<=1, ii>>=1) {
bit = (ii & 1) | bit;
if (++k == ex) break;
}
b[i] = a[bit];
}
for (i = 0; i < length; i++) 
a[i] = b[i];
}

// 二维FFT
void cstb(int length, int inv, float sin_tbl[], float cos_tbl[]);
void rvmtx1(float *a, float *b,      int xsize, int ysize);
void rvmtx2(float *a, float *b,      int xsize, int ysize);
int __stdcall FFT2(float *a_rl, float *a_im, int inv, int xsize, int ysize)
{
float *b_rl;            //数据转置作业用配列（实数部）
float *b_im;            //数据转置作业用配列（虚数部）
float *hsin_tbl;         //计算水平SIN用配列
float *hcos_tbl;         //计算水平COS用配列
float *vsin_tbl;         //计算垂直SIN用配列
float *vcos_tbl;         //计算垂直COS用配列
float *buf_x;            //水平方向作业用配列
float *buf_y;            //垂直方向作业用配列
int i;
           b_rl = (float *)calloc((size_t)xsize*ysize, sizeof(float));
           b_im = (float *)calloc((size_t)xsize*ysize, sizeof(float));
           hsin_tbl = (float *)calloc((size_t)xsize, sizeof(float));
           hcos_tbl = (float *)calloc((size_t)xsize, sizeof(float));
           vsin_tbl = (float *)calloc((size_t)ysize, sizeof(float));
           vcos_tbl = (float *)calloc((size_t)ysize, sizeof(float));
           buf_x = (float *)malloc((size_t)xsize*sizeof(float));
           buf_y = (float *)malloc((size_t)ysize*sizeof(float));
           if ((b_rl == NULL) || (b_im == NULL)
                 || (hsin_tbl == NULL) || (hcos_tbl == NULL)
                 || (vsin_tbl == NULL) || (vcos_tbl == NULL)
                 || (buf_x == NULL) || (buf_y == NULL)) {
                 return -1;
           }
           cstb(xsize, inv, hsin_tbl, hcos_tbl);   //计算水平用SIN,COS配列
           cstb(ysize, inv, vsin_tbl, vcos_tbl);   //计算垂直用SIN,COS配列
           
           int x_exp = (int)(log((double)xsize)/log((double)2));
           //水平方向的傅里叶变换
           for (i = 0; i < ysize; i++) {
                 fft1core(&(*(a_rl + (long)i*xsize)), &(*(a_im + (long)i*xsize)),xsize, x_exp, hsin_tbl, hcos_tbl, buf_x);
           }
           //2维数据的倒置
           rvmtx1(a_rl, b_rl, xsize, ysize);
           rvmtx1(a_im, b_im, xsize, ysize);

           //垂直方向的傅里叶变换
           int y_exp = (int)(log((double)ysize)/log((double)2));
           for (i = 0; i < xsize; i++) {
                 fft1core(&(*(b_rl + ysize*i)), &(*(b_im + ysize*i)), ysize, y_exp, vsin_tbl, vcos_tbl, buf_y);
           }
           //2维数据的倒置
           rvmtx2(b_rl, a_rl, xsize, ysize);
           rvmtx2(b_im, a_im, xsize, ysize);

           free(b_rl);
           free(b_im);
           free(hsin_tbl);
           free(hcos_tbl);
           free(vsin_tbl);
           free(vcos_tbl);
           return 0;
      }
      void rvmtx1(float *a, float *b, 
           int xsize, int ysize)
      {
           int i, j;

           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++)
                 *(b + i*ysize + j) = *(a + j*xsize + i);
           }
      }
      void rvmtx2(float *a, float *b, 
           int xsize, int ysize)
      {
           int i, j;

           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++)
                       *(b + j*xsize + i) = *(a + i*ysize + j);
           }
      }


//二维FFT结果图像化
int __stdcall FFTImage(char *image_in, char *image_out, int xsize, int ysize)
      {
           float      *ar;            //数据实数部（输入输出）
           float      *ai;            //数据虚数部（输入输出）
           double      norm, max;
           float      data;
           long      i, j;

           ar = (float *)malloc((size_t)ysize*xsize*sizeof(float));
           ai = (float *)malloc((size_t)ysize*xsize*sizeof(float));
           if ((ar == NULL) || (ai == NULL)) return -1;
           //读入原图像，变换2维FFT输入数据
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       ar[xsize*j + i] = (float)(*(image_in + j*xsize + i));
                       ai[xsize*j + i] = 0.0;
                 }
           }
           //2维FFT变换
           if (FFT2(ar, ai, 1, xsize, ysize) == -1) 
                 return -1;
           //FFT结果图像化
           max = 0;
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       norm = ar[xsize*j + i]*ar[xsize*j + i] 
                          + ai[xsize*j + i]*ai[xsize*j + i];       //计算幅度成分
                       if (norm != 0.0) norm = log(norm) / 2.0;
                       else norm = 0.0;
                       ar[xsize*j + i] = (float)norm;
                       if (norm > max) max = norm;
                 }
           }
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       ar[xsize*j + i] = (float)(ar[xsize*j + i]*255 / max);
                 }
           }
           //FFT结果变图像
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       data = ar[xsize*j + i];
                       if (data > 255) data = 255;
                       if (data <   0) data = 0;
                       *(image_out + j*xsize + i) = (unsigned char)data;
                 }
           }
           free(ar);
           free(ai);
           return 0;
      }


//基于二维FFT的滤波处理
int __stdcall FFTFilter(char *image_in, char *image_out, int xsize, int ysize, int a, int b)
      {
           float      *ar;   //数据实数部（输入输出）
           float      *ai;   //数据虚数部（输入输出）
           float      *ff;   //滤波子的空间频率特性
           double      norm, max;
           float      data;
           long      i, j, circ;

           ar = (float *)malloc((size_t)ysize*xsize*sizeof(float));
           ai = (float *)malloc((size_t)ysize*xsize*sizeof(float));
           ff = (float *)malloc((size_t)ysize*xsize*sizeof(float));
           if ((ar == NULL) || (ai == NULL) || (ff == NULL)) {
                 return -1;
           }
           //读入原图像，变换2维FFT输入数据
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       ar[xsize*j + i] = (float)(*(image_in + j*xsize + i));
                       ai[xsize*j + i] = 0.0;
                 }
           }
           //2维FFT变换 
           if (FFT2(ar, ai, 1, xsize, ysize) == -1) 
                 return -1;

           //FFT结果图像化
           max = 0;
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       norm = ar[xsize*j + i]*ar[xsize*j + i] 
                          + ai[xsize*j + i]*ai[xsize*j + i];       //计算幅度成分
                       if (norm != 0.0) norm = log(norm) / 2.0;
                       else norm = 0.0;
                       ar[xsize*j + i] = (float)norm;
                       if (norm > max) max = norm;
                 }
           }
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       ar[xsize*j + i] = (float)(ar[xsize*j + i]*255 / max);
                 }
           }


           //做成只通过a以上b以下成分的滤波子
           for (j = 0; j < ysize; j++) {
                 for(i = 0; i < xsize; i++) {
                       data = (float)((i-xsize/2)*(i-xsize/2)
                             + (j-ysize/2)*(j-ysize/2));
                       circ = (long)sqrt(data);
                       if ((circ >= a) && (circ <= b))
                             ff[xsize*j + i] = 1.0;
                       else
                             ff[xsize*j + i] = 0.0;
                 }
           }

           //对原图像的频率成分实施滤波
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       ar[xsize*j + i] *= ff[xsize*j + i];
                       ai[xsize*j + i] *= ff[xsize*j + i];
                 }
           }

           //将结果变为图像数据
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       data = ar[xsize*j + i];
                       if (data > 255) data = 255;
                       if (data <   0) data = 0;
                       *(image_out + j*xsize + i) = (BYTE)data;
                 }
           }
           free(ar);
           free(ai);
           free(ff);
           return 0;
      }


// 基于二维FFT的滤波处理、逆傅里叶变换
int __stdcall FFTFilterImage(char *image_in, char *image_out, int xsize, int ysize, int a, int b)
{
           float *ar;   //数据实数部（输入输出）
           float *ai;   //数据虚数部（输入输出）
           float *ff;   //滤波子的空间频率特性
           float data;
           long i,j, circ;

           ar = (float *)malloc((size_t)ysize*xsize*sizeof(float));
           ai = (float *)malloc((size_t)ysize*xsize*sizeof(float));
           ff = (float *)malloc((size_t)ysize*xsize*sizeof(float));
           if ((ar == NULL) || (ai == NULL) || (ff == NULL)) {
                 return -1;
           }
           //读入原图像，变换2维FFT输入数据
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       ar[xsize*j + i] = (float)(*(image_in + j*xsize + i));
                       ai[xsize*j + i] = 0.0;
                 }
           }
           //2维FFT变换 
           if (FFT2(ar, ai, 1, xsize, ysize) == -1) 
                 return -1;
           //做成只通过a以上b以下成分的滤波子
           for (j = 0; j < ysize; j++) {
                 for(i = 0; i < xsize; i++) {
                       data = (float)((i-xsize/2)*(i-xsize/2)
                             + (j-ysize/2)*(j-ysize/2));
                       circ = (long)sqrt(data);
                       if ((circ >= a) && (circ <= b))
                             ff[xsize*j + i] = 1.0;
                       else
                             ff[xsize*j + i] = 0.0;
                 }
           }
           //对原图像的频率成分实施滤波
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       ar[xsize*j + i] *= ff[xsize*j + i];
                       ai[xsize*j + i] *= ff[xsize*j + i];
                 }
           }
           //实施逆FFT变换，将滤波后的频率成分变回为图像
           if (FFT2(ar, ai, -1, xsize, ysize) == -1) 
                 return -1;
           //将结果变为图像数据
           for (j = 0; j < ysize; j++) {
                 for (i = 0; i < xsize; i++) {
                       data = ar[xsize*j + i];
                       if (data > 255) data = 255;
                       if (data <   0) data = 0;
                       *(image_out + j*xsize + i) = (BYTE)data;
                 }
           }
           free(ar);
           free(ai);
           free(ff);
           return 0;
}