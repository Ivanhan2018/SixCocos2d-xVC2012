#include <stdio.h>
#include <dlfcn.h>
#include <math.h>
#include <stdlib.h>

int do_test_so_func(int a,int b)
{
    void* handle;
    typedef int (*FPTR)(int,int);

    handle = dlopen("./test_so.so", 1);
    FPTR fptr = (FPTR)dlsym(handle, "test_so_func");

    int result = (*fptr)(a,b);
    return result;
}

void hi(){
    printf("hello world C!\n");
}

int test_so_func(int a,int b)
{
    return a*b;
}

double lcoss(double x)
{ 
    int m,i,j;
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

double lsinn(double x)
{ 
    int m,i,j;
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

double lexpp(double x)
{ 
    int m,i,j;
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

double bsdet(double *a,int n)
{ 
int i,j,k,is,js,l,u,v;
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

void brmul(double *a,double *b,int m,int n,int k,double *c)
{ 
    int i,j,l,u;
    for (i=0; i<=m-1; i++)
    for (j=0; j<=k-1; j++)
      { u=i*k+j; c[u]=0.0;
        for (l=0; l<=n-1; l++)
          c[u]=c[u]+a[i*n+l]*b[l*k+j];
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

void phbub(char **p,int n,int k,int m)
{ 
    int j,i;
    char *d;
    if (k<0) k=0;
    if (m>n-1) m=n-1;
    while (k<m)
      { j=m-1; m=0;
        for (i=k; i<=j; i++)
          if (strcmp(p[i],p[i+1])>0)
	    { d=p[i]; p[i]=p[i+1]; p[i+1]=d; m=i;}
        j=k+1; k=0;
        for (i=m; i>=j; i--)
          if (strcmp(p[i-1],p[i])>0)
            { d=p[i]; p[i]=p[i-1]; p[i-1]=d; k=i;}
      }
    return;
}

static void hsift(char **p,int k,int i,int l)
{ 
    int m,n;
    char *t;
    t=p[i+k]; m=i; n=2*(i+1)-1;
    while (n<=l-1)
      { if ((n<l-1)&&(strcmp(p[n+k],p[n+1+k])<0)) n=n+1;
        if (strcmp(t,p[n+k])<0)
          { p[m+k]=p[n+k]; m=n; n=2*(m+1)-1;}
        else n=l;
      }
    p[m+k]=t;
    return;
}
  
void phhap(char **p,int n,int k,int m)
{ 
    int i,l;
    char *t;
    if (k<0) k=0;
    if (m>n-1) m=n-1;
    l=m-k+1;
    for (i=l/2-1; i>=0; i--)
      hsift(p,k,i,l);
    for (i=l-1; i>=1; i--)
      { t=p[k]; p[k]=p[i+k]; p[i+k]=t;
        hsift(p,k,0,i);
      }
    return;
  }

static void hsplit(char **p,int k,int m,int *i)
{ 
    int ii,kk,j,l;
    char *t;
    ii=k; j=m;
    kk=(ii+j)/2;
    if ((strcmp(p[ii],p[j])>=0)&&(strcmp(p[j],p[kk])>=0))
        l=j;
    else if ((strcmp(p[ii],p[kk])>=0)&&(strcmp(p[kk],p[j])
          >=0)) l=kk;
    else l=ii;
    t=p[l]; p[l]=p[ii];
    while (ii!=j)
      { while ((ii<j)&&(strcmp(p[j],t)>=0)) j=j-1;
        if (ii<j)
          { p[ii]=p[j]; ii=ii+1;
            while ((ii<j)&&(strcmp(p[ii],t)<=0)) ii=ii+1;
            if (ii<j)
              { p[j]=p[ii]; j=j-1;}
          }
      }
    p[ii]=t; *i=ii;
    return;
}
  
void phqck(char **p,int n,int k,int m)
{ 
    int i0,*i;
    i=&i0;
    if (k<0) k=0;
    if (m>n-1) m=n-1;
    if (m-k>10)
      { hsplit(p,k,m,i);
	phqck(p,n,k,i0-1);
	phqck(p,n,i0+1,m);
      }
    else phbub(p,n,k,m);
    return;
}

int qhbsh(char **p,int n,char *a,char *b,int *m)
{ 
    int i,j,k;
    i=1; j=n;
    while (i<=j)
      { k=(i+j)/2;
        if ((strcmp(p[k-1],a)>=0)&&(strcmp(p[k-1],b)<=0))
          { i=k-1; j=0;
            while ((i>=0)&&(strcmp(p[i],a)>=0)) 
                { i=i-1; j=j+1;}
            i=i+1;
            while ((k<=n-1)&&(strcmp(p[k],b)<=0)) 
                { k=k+1; j=j+1;}
            *m=j; return(i);
          }
        if (strcmp(p[k-1],b)>0) j=k-1;
        else i=k+1;
      }
    while ((i>=0)&&(strcmp(b,p[i])<0)) i=i-1;
    i=i+1; *m=0;
    return(i);
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
  
void pcbub(char *p,int n)
{ 
    int m,k,j,i;
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

void pchap(char *p,int n)
{ 
    int i,mm;
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

  void pcqck(char *p,int n)
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
  
void pcshl(char *p,int n)
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

  void pihap(int *p,int n)
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
  
  void pibub(int *p,int n)
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
  
  void piqck(int *p,int n)
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
  
   void pishl(int *p,int n)
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
  
  void prbub(double *p,int n)
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
  
    void prhap(double *p,int n)
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

  void prqck(double *p,int n)
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
  
void prshl(double *p,int n)
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
  
  void ptopo(int n,int *r,int m,int *p)
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
  
   int qibsh(int *p,int n,int a,int b,int *m)
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
  
  int qrbsh(double *p,int n,double a,double b,int *m)
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
  
  void phshl(char **p,int n,int k,int m)
  { 
    int kk,j,i;
    char *t;
    n=n+0;
    kk=(m-k)/2;
    while (kk>0)
      { for (j=k+kk; j<=m; j++)
          { t=p[j]; i=j-kk;
            while ((i>=0)&&(strcmp(p[i],t)>0))
              { p[i+kk]=p[i]; i=i-kk;}
            p[i+kk]=t;
          }
        kk=kk/2;
      }
    return;
  }
  

  
 