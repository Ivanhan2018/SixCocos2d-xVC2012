#include "mathlib52.h"
typedef unsigned char BYTE;

int brinv(double *a,int n)
{ 
    int *is,*js,i,j,k,l,u,v;
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

//有问题已修正
/* 返回值：
      0: delta=0，有3个实根，其中y_2和y_3是重根
      1: delta>0 && delta2>=0||delta<0，有3个相异实根
      2: delta>0 && delta2<0，1实2虚	  	  
*/
int Cardano(double a,double b,double c,double d,double *y)
{
    double p,q,D,u,v,g,delta,fai;
    double delta2;
    p=(3.0*a*c-b*b)/(3*a*a);//p=B-(A^2)/3=c/a-(b^2)/(3a^2)
    q=(2.0*pow(b,3.0)-9*a*b*c+27.0*a*a*d)/(27.0*pow(a,3.0));//q=2A^3/27-AB/3+C=(2b^3)/(27a^3)-(bc)/(3a^2)+(d/a)
    D=b/(3.0*a);
    delta=pow(q/2.0,2.0)+pow(p/3.0,3.0);//取delta=q^2/4+p^3/27=q*q/2+p*p*p/27
    if(delta>=0)
    {
        g=sqrt(delta);//
        
        if(-q/2.0+g<0)//负数a开立方
        u=-pow(fabs(-q/2.0+g),1.0/3.0);
        else//正数a开立方
        u=pow((-q/2.0+g),1.0/3.0);
        
        if(-q/2.0-g<0)//负数b开立方
        v=-pow(fabs(-q/2.0-g),1.0/3.0);
        else//正数b开立方
        v=pow((-q/2.0-g),1.0/3.0);//
    
        if(delta==0)//delta=0是有3个实根的充分不必要条件
        {
           //delta=0=>delta2=0,*real_y1=(-4q)^(1/3)-D=2·(-q/2)^(1/3)-D,*real_y2=*real_y3=(q/2)^(1/3)-D
           y[0]=u+v-D;y[1]=0;//实根y1,x1
           y[2]=-(u+v)/2-D;y[3]=0;//实根y2,x2=-x1/2
           y[4]=-(u+v)/2-D;y[5]=0;//实根y3,x3=-x1/2
           //printf("delta=0，有3个实根，其中y_2和y_3是重根\n");
		   return 1;
        }
        else//delta>0，有3个相异实根或1实2虚
        {
           y[0]=u+v-D;
		   y[1]=0;
           delta2=-3*(u+v)*(u+v)-4*p;
           if(delta2>=0)//4*p<=-3*(u+v)*(u+v)
           {
            y[2]=-(u+v)/2+sqrt(delta2)/2-D;y[3]=0;
            y[4]=-(u+v)/2-sqrt(delta2)/2-D;y[5]=0;
		    return 0;
           }
           else
           {
            y[2]=-(u+v)/2-D;y[3]=sqrt(-delta2)/2;
            y[4]=-(u+v)/2-D;y[5]=-sqrt(-delta2)/2;
			return 2;
           }
           //printf("delta>0，有3个相异实根或1实2虚\n");
            //*real_y1=u+v-D;*imag_y1=0;
            //*real_y2=-(u+v)/2-D;*imag_y2=sqrt(3.0)*(u-v)/2;
            //*real_y3=-(u+v)/2-D;*imag_y3=-sqrt(3.0)*(u-v)/2;
        }
    }
    else//delta<0，三个相异的根
    {
        fai=acos((-q/2)/(sqrt(pow(fabs(p),3)/27)));
        y[0]=2*sqrt(fabs(p)/3.0)*cos(fai/3.0)-D;
        y[2]=-2*sqrt(fabs(p)/3.0)*cos((fai+3.1415926)/3.0)-D;
        y[4]=-2*sqrt(fabs(p)/3.0)*cos((fai-3.1415926)/3.0)-D;
        y[1]=0;
        y[3]=0;
        y[5]=0;
        //printf("delta<0，有三个相异的根\n");
		return 1;
    }
}

int poly3(double *mtx3,double *abcd)
{
    int ret=0;
    for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			double ij=mtx3[3*i+j];
			double ji=mtx3[3*j+i];				
			if(fabs(ij-ji) > 1e-15)
			{
				ret=1;
				break;
			}
		}
    abcd[0]=1;
    abcd[1]=-mtx3[0]-mtx3[4]-mtx3[8];	
    abcd[2]=mtx3[0]*mtx3[4]-mtx3[1]*mtx3[3]+mtx3[4]*mtx3[8]-mtx3[5]*mtx3[7]+mtx3[0]*mtx3[8]-mtx3[2]*mtx3[6];
    abcd[3]=mtx3[0]*mtx3[4]*mtx3[8]+mtx3[1]*mtx3[5]*mtx3[6]+mtx3[2]*mtx3[3]*mtx3[7]-mtx3[6]*mtx3[4]*mtx3[2]-mtx3[1]*mtx3[3]*mtx3[8]-mtx3[0]*mtx3[5]*mtx3[7];		
	return ret;
}

int chhqr(double *a,int n,double *u,double *v,double eps,int jt)
{ 
    int m,it,i,j,k,l,ii,jj,kk,ll;
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

int dqrrt(double a[],int n,double xr[],double xi[],double eps,int jt)
{ 
    int i,j;
    double *q;
    //extern int chhqr();
    q=(double *)malloc(n*n*sizeof(double));
    for (j=0; j<=n-1; j++)
      q[j]=-a[n-j-1]/a[n];
    for (j=n; j<=n*n-1; j++)
      q[j]=0.0;
    for (i=0; i<=n-2; i++)
      q[(i+1)*n+i]=1.0;
    i=chhqr(q,n,xr,xi,eps,jt);
    free(q); 
	return(i);
}