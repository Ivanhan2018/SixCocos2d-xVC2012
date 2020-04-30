#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 矩阵的迹Trρ(g)称为表示的特征标
int TraceMat(const vector<vector<int> >&Matrix)
{
	int Tr=0;
    int n=Matrix.size();	
    for(int i=0;i<n;i++){
		Tr+=Matrix[i][i];
    }	
	return Tr;
}

// 返回n阶单位矩阵
vector<vector<int> > IdentityMat(int n)
{
	vector<vector<int> > Matrix(n, vector<int>(n,0));
    for(int i=0;i<n;i++){
		Matrix[i][i]=1;
    }	
	return Matrix;
}

// 求矩阵A的可达矩阵RA
// 根据可达矩阵来判断矩阵的可约性；若可达矩阵中至少有一个元素为0时，则矩阵为可约矩阵；若可达矩阵中每个元素都为1，则矩阵是不可约的。
vector<vector<int> > ReachableMatrix(const vector<vector<int> >&Matrix,bool *pIrr=NULL)
{
    int n=Matrix.size();
    vector<vector<int> > In=IdentityMat(n);
	vector<vector<int> > Matrix1(n, vector<int>(n,0));
    for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			Matrix1[i][j]=In[i][j]||Matrix[i][j];
		}
    }	
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{ 
			for (int k=0;k<n;k++)
			{
				Matrix1[j][k]=Matrix1[j][k]||(Matrix1[j][i]&&Matrix1[i][k]);
			}
		}
	}	
	// 输出参数用来存放矩阵是否可约
	if(pIrr)
	{
		(*pIrr)=true;// 矩阵不可约
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
			{ 
				if (Matrix1[i][j]!=1)
				{
					(*pIrr)=false;// 矩阵可约
					return Matrix1;
				}
			}
		}
	}
	return Matrix1;
}

string itos(int a)
{
	char sz[20]={0};
	sprintf(sz,"%d",a);
	return sz;
}

string MStr(const vector<vector<int> >&Matrix)
{
	string str="[";
    for(int i=0;i<Matrix.size();i++){
		str+="[";
		for(int j=0;j<Matrix[i].size();j++){
			str+=itos(Matrix[i][j])+" ";
			if(j<Matrix[i].size()-1)
				str+=",";
		}	
		str+="]";
		if(i<Matrix.size()-1)
          	str+=",";		
    }	
	str+="]";
	return str;
}

std::vector<string> split( const std::string& str, const std::string& delims/* = "\t\n "*/, unsigned int maxSplits = 0)
{
	std::vector<string> ret;
	unsigned int numSplits = 0;

	// Use STL methods 
	size_t start, pos;
	start = 0;
	do 
	{
		pos = str.find_first_of(delims, start);
		if (pos == start)
		{
			// Do nothing
			start = pos + 1;
		}
		else if (pos == std::string::npos || (maxSplits && numSplits == maxSplits))
		{
			// Copy the rest of the std::string
			ret.push_back( str.substr(start) );
			break;
		}
		else
		{
			// Copy up to delimiter
			ret.push_back( str.substr(start, pos - start) );
			start = pos + 1;
		}
		// parse up to next real data
		start = str.find_first_not_of(delims, start);
		++numSplits;

	} while (pos != std::string::npos);
	return ret;
}

vector<vector<int> > atoMat(const char *str)
{
	vector<string> vs;
	vector<int> vi(2);
	int rows=0;
	int cols=0;
	if(str!=NULL)
	{
		vs=split(str,";");
		rows=vs.size();
		vi[0]=rows;
		for(int i=0;i<vs.size();i++)
		{
			vector<string> vsi=split(vs[i],",");
			if(cols>0 && vsi.size()!=cols)
			{
				vi.clear();
				vector<vector<int> > vv;	
				return vv;
			}
			cols=vsi.size();
			vi[1]=cols;
			for(int j=0;j<vsi.size();j++)
			{
				vi.push_back(atoi(vsi[j].c_str()));
			}
		}
	}
	else
	{
		vi.clear();
	}
	vector<vector<int> > vv(rows, vector<int>(cols,0));	
	for(int k=0;k<vi.size()-2;k++)
	{
		int i=k/cols;
		int j=k%cols;
		vv[i][j]=vi[k+2];
	}	
	return vv;
}

// 矩阵的转置
vector<vector<int> > TransposedMat(const vector<vector<int> >&a)
{
    int n=a.size();	
	vector<vector<int> > c(n, vector<int>(n,0));	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			c[i][j]=a[j][i];
		}
	}
	return c;	
}

// 两个nxn矩阵a和b相乘得到c
vector<vector<int> > MMul(const vector<vector<int> >&a,const vector<vector<int> >&b)
{
    int n=a.size();	
	vector<vector<int> > c(n, vector<int>(n,0));	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			int sum=0;
			for(int k=0;k<n;k++)
				sum+=a[i][k]*b[k][j];
			c[i][j]=sum;
		}
	}
	return c;
}

int main(int argc, char *argv[])
{
	char sz[1024]={0};
	char sz1[1024]={0};
	if(argc<2)
	{
		printf("请输入矩阵A:");
		scanf("%s",&sz);
	}
	else
	{
		strcpy(sz,argv[1]);
	}
// #if 1
    // vector<vector<int> > A=atoMat("4,1,2,3;0,2,3,2;0,3,5,8;0,5,0,8");
// #else
	// int a[4][4]={{4,1,2,3},{0,2,3,2},{0,3,5,8},{0,5,0,8}};
	// vector<vector<int> > A(4, vector<int>(4,0));
	// for(int i=0;i<4;i++)
		// memcpy(&A[i][0],&a[i][0],sizeof(int)*4);
// #endif
    vector<vector<int> > A=atoMat(sz);
    cout<<"A="<<MStr(A)<<endl;	
	
	bool bIrr;
	vector<vector<int> > RA=ReachableMatrix(A,&bIrr);
    cout<<"RA="<<MStr(RA)<<(bIrr?"矩阵不可约":"矩阵可约")<<endl;		
    cout<<"Tr(A)="<<TraceMat(A)<<endl;
	vector<vector<int> > RAtARA=MMul(MMul(TransposedMat(RA),A),RA);
    cout<<"RAtARA="<<MStr(RAtARA)<<endl;
    return EXIT_SUCCESS;
}