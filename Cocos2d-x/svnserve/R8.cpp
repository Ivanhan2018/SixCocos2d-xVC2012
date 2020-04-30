#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<functional>

struct M4
{
  int m_val[4][4];
};

int g_a1234[][4]={ \
	{1,0,0,0}, \
	{0,1,0,0}, \
	{0,0,1,0}, \
	{0,0,0,1} \
};

M4 PermutationMat4(int a1,int a2,int a3,int a4)
{
 int v[4]={a1,a2,a3,a4};
 M4 ret;
 for(int i=0;i<4;i++)
	memcpy(&ret.m_val[i][0],&g_a1234[v[i]-1][0],sizeof(int)*4);
 return ret;
}

M4 PermutationMat4(int a1a2a3a4)
{
	int v[4]={0};
	int i=0;
	while(a1a2a3a4)
	{
		v[i++]=(a1a2a3a4 % 10);
		a1a2a3a4 /= 10;
	}
	return PermutationMat4(v[3],v[2],v[1],v[0]);
}

template<class T>
void Brmul(T *a,T *b,int m,int n,int k,T *c)
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

M4 M4Mul(const M4 &m,const M4 &n)
{
	M4 mtx;
	Brmul((int *)&(m.m_val[0][0]),(int *)&(n.m_val[0][0]),4,4,4,(int *)&(mtx.m_val[0][0]));
	return mtx;
}

int M4ElemToInt(const M4 &m,M4 M4Elem[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(memcmp(&m.m_val[0][0],&M4Elem[i].m_val[0][0],sizeof(int)*16)==0)
			return i;
	}
	return -1;
}

int M4mul(int a,int b,M4 M4Elem[],int n)
{
	M4 ma=M4Elem[a];
	M4 mb=M4Elem[b];

	M4 mc=M4Mul(ma,mb);
	int c=M4ElemToInt(mc,M4Elem,n);

	return c;
}

M4 g_S4[]={
	PermutationMat4(1234),
	PermutationMat4(1243),
	PermutationMat4(1324),
	PermutationMat4(1342),
	PermutationMat4(1423),
	PermutationMat4(1432),
	PermutationMat4(2134),
	PermutationMat4(2143),
	PermutationMat4(2314),
	PermutationMat4(2341),
	PermutationMat4(2413),
	PermutationMat4(2431),
	PermutationMat4(3124),
	PermutationMat4(3142),
	PermutationMat4(3214),
	PermutationMat4(3241),
	PermutationMat4(3412),
	PermutationMat4(3421),
	PermutationMat4(4123),
	PermutationMat4(4132),
	PermutationMat4(4213),
	PermutationMat4(4231),
	PermutationMat4(4312),
	PermutationMat4(4321)
};
	
struct M2
{
	int a,b,c,d;
};

// 上三角矩阵环T_2(F_2)
M2 g_M2Elem[]={
	{0,0,0,0},
	{1,0,0,0},
	{0,0,0,1},
	{1,0,0,1},
	{0,1,0,0},
	{1,1,0,0},
	{0,1,0,1},
	{1,1,0,1}
};

// 2级全线性群GL(2,2)、2级特殊线性群SL(2,2)、2级正交群GO(-1,2,2)、2级特殊正交群SO(-1,2,2)
M2 g22_M2Elem[]={
	{1,0,0,1},
	{0,1,1,0},
	{0,1,1,1},
	{1,0,1,1},
	{1,1,0,1},
	{1,1,1,0}
};

// O_2(F_7)=D_8
M2 g27_M2Elem[]={
{1,0,0,1},//第5个正交矩阵:
{0,1,1,0},//第1个正交矩阵:
{0,1,6,0},//第2个正交矩阵:
{0,6,1,0},//第3个正交矩阵:
{0,6,6,0},//第4个正交矩阵:
{1,0,0,6},//第6个正交矩阵:
{2,2,2,5},//第7个正交矩阵:
{2,2,5,2},//第8个正交矩阵:
{2,5,2,2},//第9个正交矩阵:
{2,5,5,5},//第10个正交矩阵:
{5,2,2,2},//第11个正交矩阵:
{5,2,5,5},//第12个正交矩阵:
{5,5,2,5},//第13个正交矩阵:
{5,5,5,2},//第14个正交矩阵:
{6,0,0,1},//第15个正交矩阵:
{6,0,0,6},//第16个正交矩阵:
};

M2 g23_M2Elem[]={
 {1,0,0,1},//第5个正交矩阵,det=1
 {0,1,1,0},//第1个正交矩阵,det=2
 {0,1,2,0},//第2个正交矩阵,det=1
 {0,2,1,0},//第3个正交矩阵,det=1
 {0,2,2,0},//第4个正交矩阵,det=2
 {1,0,0,2},//第6个正交矩阵,det=2
 {2,0,0,1},//第7个正交矩阵,det=2
 {2,0,0,2}//第8个正交矩阵,det=1
};

// GO(-1,2,3)=O_2(F_3)=D_4
M2 g23_D4M2Elem[]={
 {1,0,0,1},
 {1,0,1,2},
 {1,1,0,2},
 {1,1,1,2},
 {2,0,0,2},
 {2,0,2,1},
 {2,2,0,1},
 {2,2,2,1}
};

// SO(-1,2,3)=C_4
M2 g23_C4M2Elem[]={
 {1,0,0,1},
 {1,1,1,2},
 {2,0,0,2},
 {2,2,2,1}	
 //{1,0,0,1},//第5个正交矩阵,det=1
 //{0,1,2,0},//第2个正交矩阵,det=1
 //{0,2,1,0},//第3个正交矩阵,det=1
 //{2,0,0,2}//第8个正交矩阵,det=1
};

int M2ElemToInt(const M2 &m,M2 M2Elem[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(M2Elem[i].a==m.a && M2Elem[i].b==m.b && M2Elem[i].c==m.c && M2Elem[i].d==m.d)
			return i;
	}
	return -1;
}

M2 Add(const M2 &m,const M2 &n,int p)
{
	M2 ret;
	ret.a=(m.a+n.a)%p;
	ret.b=(m.b+n.b)%p;
	ret.c=(m.c+n.c)%p;
	ret.d=(m.d+n.d)%p;
	return ret;
}

M2 Mul(const M2 &m,const M2 &n,int p)
{
	M2 ret;
	ret.a=(m.a*n.a+m.b*n.c)%p;
	ret.b=(m.a*n.b+m.b*n.d)%p;
	ret.c=(m.c*n.a+m.d*n.c)%p;
	ret.d=(m.c*n.b+m.d*n.d)%p;
	return ret;
}

int Mod(int ret,unsigned int n)
{
 if(ret<0)
 {
  int ret1=ret+(-ret+1)*n;
  return ret1%n;
 }
 return ret%n;
}

int DeterminantMatMod(const M2 &m,int p)
{
	int ret=Mod(m.a*m.d-m.b*m.c,p);
	return ret;
}

// 求逆的前提条件是可逆(Det≠0)
M2 InverseMatMod(const M2 &m,int p)
{
	M2 ret;	
	int det=Mod(m.a*m.d-m.b*m.c,p);
	for(int i=1;i<p;i++)
	{
		if((det*i)%p==1)
		{
			ret.a=Mod(i*m.d,p);
			ret.b=Mod(-i*m.b,p);
			ret.c=Mod(-i*m.c,p);
			ret.d=Mod(i*m.a,p);
			return ret;
		}
	}
	return ret;
}

int M2mul(int a,int b,M2 M2Elem[],int n,int p,M2(*pMul)(const M2 &m,const M2 &n,int p))
{
	M2 ma=M2Elem[a];
	M2 mb=M2Elem[b];

	M2 mc=pMul(ma,mb,p);
	int c=M2ElemToInt(mc,M2Elem,n);

	return c;
}

void Printf(int n,std::function<int(int,int)> pmul)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%d ",pmul(i,j)+1);
		}	
		printf("\n");
	}	
}

int main()
{
    {
		int n=sizeof(g23_M2Elem)/sizeof(g23_M2Elem[0]);
		for(int i=0;i<n;i++)
		{	
			M2 mat=g23_M2Elem[i];
			int det=DeterminantMatMod(mat, 3);
			M2 inv=InverseMatMod( mat, 3 );
			printf("det=%d\n",det);
			if(det!=0)
			{
				printf("矩阵非奇异\n");
				M2 inv=InverseMatMod( mat, 3 );
				printf("inv=[[%d,%d],[%d,%d]]\n",inv.a,inv.b,inv.c,inv.d);
				M2 I=Mul(mat,inv,3);
				printf("mat*inv=[[%d,%d],[%d,%d]]\n",I.a,I.b,I.c,I.d);
			}
			else
			{
				printf("矩阵奇异\n");
			}
		}
	}

    // 8阶非交换幺环R8_49
	{
		int n=sizeof(g_M2Elem)/sizeof(g_M2Elem[0]);
		auto add=std::bind(M2mul,std::placeholders::_1,std::placeholders::_2,g_M2Elem,n,2,Add);
		printf("[R8Add]\n");
		Printf(n,add);
		auto mul=std::bind(M2mul,std::placeholders::_1,std::placeholders::_2,g_M2Elem,n,2,Mul);
		printf("[R8Mul]\n");
		Printf(n,mul);
	}
	{
		const char *szName[]={"D_3=GAP4[6,1]","D_8=GAP4[16,7]","D_4=GAP4[8,3]","D_4=GAP4[8,3]","C_4=GAP4[4,1]"};
		M2 *vvM2Elem[]={g22_M2Elem,g27_M2Elem,g23_M2Elem,g23_D4M2Elem,g23_C4M2Elem};
		int nArr[]={6,16,8,8,4};
		int pArr[]={2,7,3,3,3};	
		int iNum=sizeof(szName)/sizeof(szName[0]);
		for(int i=0;i<iNum;i++)
		{
			auto mul=std::bind(M2mul,std::placeholders::_1,std::placeholders::_2,vvM2Elem[i],nArr[i],pArr[i],Mul);
			printf("%s:\n",szName[i]);
			Printf(nArr[i],mul);
		}
	}
	{
		const char *szName[]={"S_4=GAP4[24,12]"};
		M4 *vvM4Elem[]={g_S4};
		int nArr[]={24};
		int iNum=sizeof(szName)/sizeof(szName[0]);
		for(int i=0;i<iNum;i++)
		{
			auto mul=std::bind(M4mul,std::placeholders::_1,std::placeholders::_2,vvM4Elem[i],nArr[i]);
			printf("%s:\n",szName[i]);
			Printf(nArr[i],mul);
		}
	}	
	return 0;
}