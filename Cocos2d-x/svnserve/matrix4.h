#ifndef MATRIX4_H
#define MATRIX4_H

#include<cmath>
#include<iostream>
using namespace std;

#ifndef WIN32
#define __stdcall
#endif

template<class T>
void __stdcall Brmul(T *a,T *b,int m,int n,int k,T *c)
{ 
	int i,j,l,u;
	for (i=0; i<=m-1; i++)
		for (j=0; j<=k-1; j++)
		{ 
			u=i*k+j; 
			c[u]=0.0;
			for(l=0; l<=n-1; l++)
				c[u]=c[u]+a[i*n+l]*b[l*k+j];
		}
		return;
} 


template<class T>
//第一个参数是输入输出参数
T __stdcall Bsdet(T *a,int n)
{ 
	int i,j,k,is,js,l,u,v;
	T f,det,q,d;
	f=1.0; det=1.0;
	for (k=0; k<=n-2; k++)
	{ 
		q=0.0;
		for (i=k; i<=n-1; i++)
			for (j=k; j<=n-1; j++)
			{ 
				l=i*n+j; 
				d=fabs(a[l]);
				if (d>q)
				{ 
					q=d; 
					is=i; 
					js=j;
				}
			}
			if(q+1.0==1.0)
			{ 
				det=0.0; 
				return(det);
			}
			if(is!=k)
			{
				f=-f;
				for (j=k; j<=n-1; j++)
				{ 
					u=k*n+j; 
					v=is*n+j;
					d=a[u]; 
					a[u]=a[v]; 
					a[v]=d;
				}
			}
			if(js!=k)
			{ 
				f=-f;
				for (i=k; i<=n-1; i++)
				{ 
					u=i*n+js; 
					v=i*n+k;
					d=a[u]; 
					a[u]=a[v]; 
					a[v]=d;
				}
			}
			l=k*n+k;
			det=det*a[l];
			for (i=k+1; i<=n-1; i++)
			{ 
				d=a[i*n+k]/a[l];
				for (j=k+1; j<=n-1; j++)
				{ 
					u=i*n+j;
					a[u]=a[u]-d*a[k*n+j];
				}
			}
	}
	det=f*det*a[n*n-1];
	return(det);
}

template<class T>
int __stdcall Brinv(T *a,int n)
{
	int *is,*js,i,j,k,l,u,v;
	T d,p;
	is=(int*)malloc(n*sizeof(int));
	js=(int*)malloc(n*sizeof(int));
	for (k=0; k<=n-1; k++)
	{ 
		d=0.0;
		for (i=k; i<=n-1; i++)
			for (j=k; j<=n-1; j++)
			{ 
				l=i*n+j; 
				p=fabs(a[l]);
				if (p>d) 
				{ 
					d=p; 
					is[k]=i; 
					js[k]=j;
				}
			}
			if (d+1.0==1.0)
			{ 
				free(is); 
				free(js); 
				printf("err**not inv\n");
				return(0);
			}
			if (is[k]!=k)
				for (j=0; j<=n-1; j++)
				{ 
					u=k*n+j; 
					v=is[k]*n+j;
					p=a[u]; 
					a[u]=a[v]; 
					a[v]=p;
				}
				if (js[k]!=k)
					for (i=0; i<=n-1; i++)
					{ 
						u=i*n+k; 
						v=i*n+js[k];
						p=a[u]; 
						a[u]=a[v]; 
						a[v]=p;
					}
					l=k*n+k;
					a[l]=1.0/a[l];
					for (j=0; j<=n-1; j++)
						if (j!=k)
						{ 
							u=k*n+j; 
							a[u]=a[u]*a[l];
						}
						for (i=0; i<=n-1; i++)
							if (i!=k)
								for (j=0; j<=n-1; j++)
									if (j!=k)
									{ 
										u=i*n+j;
										a[u]=a[u]-a[i*n+k]*a[k*n+j];
									}
									for (i=0; i<=n-1; i++)
										if (i!=k)
										{ 
											u=i*n+k; 
											a[u]=-a[u]*a[l];
										}
	}
	for(k=n-1; k>=0; k--)
	{ 
		if (js[k]!=k)
			for (j=0; j<=n-1; j++)
			{ 
				u=k*n+j; 
				v=js[k]*n+j;
				p=a[u];
				a[u]=a[v];
				a[v]=p;
			}
			if (is[k]!=k)
				for (i=0; i<=n-1; i++)
				{ 
					u=i*n+k; 
					v=i*n+is[k];
					p=a[u]; 
					a[u]=a[v]; 
					a[v]=p;
				}
	}
	free(is); 
	free(js);
	return(1);
}



// From gamasutra. This file may follow different licence features.

// A floating point number
//

typedef float SCALAR;

//
// A 4D vector
//

class VECTOR4
{
public:
	SCALAR x,y,z,w; //x,y,z,w coordinates
public:
	VECTOR4() : x(0), y(0), z(0),w(0) {}

	VECTOR4( const SCALAR& a, const SCALAR& b, const SCALAR& c , const SCALAR& d) : x(a), y(b), z(c), w(d) {}

	//index a component
	//NOTE: returning a reference allows
	//you to assign the indexed element

	SCALAR& operator [] ( long i )
	{
		return *((&x) + i);
	}

//compare

	const bool operator == ( const VECTOR4& v ) const
	{
		return (v.x==x && v.y==y && v.z==z && v.w==w);
	}

	const bool operator != ( const VECTOR4& v ) const
	{
		return !(v == *this);
	}

//negate

	const VECTOR4 operator - () const
	{
		return VECTOR4( -x, -y, -z ,-w);
	}

//assign

	const VECTOR4& operator = ( const VECTOR4& v )
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

//increment

	const VECTOR4& operator += ( const VECTOR4& v ) 
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		w+=v.w;
		return *this;
	} 

//decrement

	const VECTOR4& operator -= ( const VECTOR4& v ) 
	{
		x-=v.x;
		y-=v.y;
		z-=v.z;
		w-=v.w;
		return *this;
	} 

//self-multiply
	const VECTOR4& operator *= ( const SCALAR& s )
	{
		x*=s;
		y*=s;
		z*=s;
		w*=s;
		return *this;
	}

//self-divide
	const VECTOR4& operator /= ( const SCALAR& s )
	{
		const SCALAR r = 1 / s;
		x *= r;
		y *= r;
		z *= r;
		w *= r;
		return *this;
	}

//add

	const VECTOR4 operator + ( const VECTOR4& v ) const
	{
		return VECTOR4(x + v.x, y + v.y, z + v.z,w+v.w);
	}

//subtract

	const VECTOR4 operator - ( const VECTOR4& v ) const
	{
		return VECTOR4(x - v.x, y - v.y, z - v.z,w-v.w);
	}

//post-multiply by a scalar

	const VECTOR4 operator * ( const SCALAR& s ) const
	{
		return VECTOR4( x*s, y*s, z*s ,w*s);
	}

//pre-multiply by a scalar

	friend inline const VECTOR4 operator * ( const SCALAR& s, const VECTOR4& v )
	{
		return v * s;
	}

//divide

	const VECTOR4 operator / (SCALAR s) const
	{
		s = 1/s;
		return VECTOR4( s*x, s*y, s*z ,s*w);
	}

////cross product，没有4维叉积
//
//	const VECTOR cross( const VECTOR& v ) const
//	{
//		//Davis, Snider, "Introduction to Vector Analysis", p. 44
//		return VECTOR( y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x );
//	}

//scalar dot product

	const SCALAR dot( const VECTOR4& v ) const
	{
		return x*v.x + y*v.y + z*v.z+w*v.w;
	}

//length

	const SCALAR length() const
	{
		return (SCALAR)sqrt( (double)this->dot(*this) );
	}

//unit vector

	const VECTOR4 unit() const
	{
	return (*this) / length();
	}

//make this a unit vector

	void normalize()
	{
		(*this) /= length();
	}

//equal within an error 慹?

	const bool nearlyEquals( const VECTOR4& v, const SCALAR e ) const
	{
		return fabs(x-v.x)<e && fabs(y-v.y)<e && fabs(z-v.z)<e && fabs(w-v.w)<e;
	}
};

//
// A 4D position
//
//typedef VECTOR4 POINT;
// From gamasutra. This file may follow different licence features.

// A 4x4 matrix
//

class MATRIX4
{
public:
	VECTOR4 C[4]; //column vectors，应该是行向量或列向量，对象占用4*16=64字节的内存空间，内存顺序与真数组的内存顺序是一致的
public:
	MATRIX4()
	{
		//identity matrix
		C[0].x = 1;
		C[1].y = 1;
		C[2].z = 1;
		C[3].w = 1;
	}
	MATRIX4( const VECTOR4& c0, const VECTOR4& c1, const VECTOR4& c2, const VECTOR4& c3 )
	{
		C[0] = c0;
		C[1] = c1;
		C[2] = c2;
		C[3] = c3;
	}
	//index a column, allow assignment
	//NOTE: using this index operator along with the vector index
	//gives you M[column][row], not the standard M[row][column]
	VECTOR4& operator [] ( long i )
	{
		return C[i];
	}
	//compare
	const bool operator == ( const MATRIX4& m ) const
	{
		return C[0]==m.C[0] && C[1]==m.C[1] && C[2]==m.C[2] && C[3]==m.C[3];
	}
	const bool operator != ( const MATRIX4& m ) const
	{
		return !(m == *this);
	}
	//assign
	const MATRIX4& operator = ( const MATRIX4& m )
	{
		C[0] = m.C[0];
		C[1] = m.C[1];
		C[2] = m.C[2];
		C[3] = m.C[3];
		return *this;
	}
	//increment
	const MATRIX4& operator +=( const MATRIX4& m )
	{
		C[0] += m.C[0];
		C[1] += m.C[1];
		C[2] += m.C[2];
		C[3] += m.C[3];
		return *this;
	}
	//decrement
	const MATRIX4& operator -=( const MATRIX4& m ) 
	{
		C[0] -= m.C[0];
		C[1] -= m.C[1];
		C[2] -= m.C[2];
		C[3] -= m.C[3];
		return *this;
	}
	//self-multiply by a scalar
	const MATRIX4& operator *= ( const SCALAR& s )
	{
		C[0] *= s;
		C[1] *= s;
		C[2] *= s;
		C[3] *= s;
		return *this;
	}
	//self-multiply by a matrix
	const MATRIX4& operator *= ( const MATRIX4& m )
	{
		//NOTE: don抰 change the columns
		//in the middle of the operation
		MATRIX4 temp = (*this);
		C[0] = temp * m.C[0];
		C[1] = temp * m.C[1];
		C[2] = temp * m.C[2];
		C[3] = temp * m.C[3];
		return *this;
	}
	//add
	const MATRIX4 operator + ( const MATRIX4& m ) const
	{
		return MATRIX4( C[0] + m.C[0], C[1] + m.C[1], C[2] + m.C[2], C[3] + m.C[3] );
	}
	//subtract
	const MATRIX4 operator - ( const MATRIX4& m ) const
	{
		return MATRIX4( C[0] - m.C[0], C[1] - m.C[1], C[2] - m.C[2], C[3] - m.C[3]);
	}
	//post-multiply by a scalar
	const MATRIX4 operator * ( const SCALAR& s ) const
	{
		return MATRIX4( C[0]*s, C[1]*s, C[2]*s, C[3]*s );
	}
	//pre-multiply by a scalar
	friend inline const MATRIX4 operator * ( const SCALAR& s, const MATRIX4& m )
	{
		return m * s;
	}
	//post-multiply by a vector
	const VECTOR4 operator * ( const VECTOR4& v ) const
	{
		return( C[0]*v.x + C[1]*v.y + C[2]*v.z+ C[3]*v.w );
	}
	//pre-multiply by a vector
	inline friend const VECTOR4 operator * ( const VECTOR4& v, const MATRIX4& m )
	{
		return VECTOR4( m.C[0].dot(v), m.C[1].dot(v), m.C[2].dot(v), m.C[3].dot(v) );
	}
	//post-multiply by a matrix
	const MATRIX4 operator * ( const MATRIX4& m ) const
	{
		return MATRIX4( (*this) * m.C[0], (*this) * m.C[1], (*this) * m.C[2], (*this) * m.C[3] );
	}
	//transpose
	MATRIX4 transpose() const
	{
		//turn columns on their side
		return MATRIX4( VECTOR4( C[0].x, C[1].x, C[2].x , C[3].x ), //column 0
			VECTOR4( C[0].y, C[1].y, C[2].y, C[3].y ), //column 1
			VECTOR4( C[0].z, C[1].z, C[2].z ,C[3].z), //column 2
			VECTOR4( C[0].w, C[1].w, C[2].w, C[3].w ) //column 3
			);
	}
	////scalar determinant，没有4维叉积
	//const SCALAR determinant() const
	//{
	//	//Lang, "Linear Algebra", p. 143
	//	return C[0].dot( C[1].cross(C[2]) );
	//}

	const SCALAR det() const
	{
		MATRIX4 mtx=*this;
		SCALAR ret=Bsdet(&mtx[0][0],4);//第一个参数是输入输出参数
		return ret;
	}

	//matrix inverse，去掉返回值类型中的const
	MATRIX4 inverse() const
	{
	   MATRIX4 mtx=*this;
	   int i=Brinv((SCALAR *)&mtx[0][0],4);
	   if(i!=0)
		   return mtx;
	   return MATRIX4();
	}

	friend ostream& operator<< (ostream& os,const MATRIX4& mtx);
};

ostream& operator<< (ostream& os,const MATRIX4& mtx)
{
    MATRIX4& mtx1=const_cast<MATRIX4&>(mtx);
	for(int i=0;i<=3;i++)
	{
		for(int j=0;j<=3;j++)
		{
			cout<<mtx1[i][j]<<",";
		}
		os<<endl;
	}
	return os;
}

#endif