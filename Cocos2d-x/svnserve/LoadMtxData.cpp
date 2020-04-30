// 计算矩阵群的凯莱表的小工具LoadMtxData.exe
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string>
using namespace std;

string FormatStr(int cnt)
{
	string str="";
	if(cnt<=0)
		return str;
	for(int i=0;i<cnt;i++)
	{
		str+="%d,";
		if(i==cnt-1)
		{
			str=str.substr(0,str.size()-1);
			str+="\\n";
		}
	}
	return str;
}

string Trim(const string& theString)
{
	int aStartPos=0;
	while(aStartPos<(int)theString.length() && isspace(theString[aStartPos]))
		aStartPos++;
	int anEndPos=theString.length()-1;
	while(anEndPos>=0 && isspace(theString[anEndPos]))
		anEndPos--;
	return theString.substr(aStartPos,anEndPos-aStartPos+1);
}

//vector<vector<int>> LoadMtxData(const char * pszFilePath)
vector<string> LoadMtxData(const char * pszFilePath)
{
	//vector<vector<int>> ret;
	vector<string> ret;

	FILE * fp =fopen(pszFilePath, "r");
	if( fp == NULL )
		return ret;

	char sz[2000]={0};
	int n=0;
	n=fscanf(fp,"%s",sz);
	//string strFormat=FormatStr(4);
	ret.push_back(sz);
	while( n > 0 && !feof(fp) )
	{
		//n=fscanf(fp,strFormat.c_str());
		char sz1[2000]={0};
		n=fscanf(fp,"%s",sz1);
		ret.push_back(sz1);
	}
	if(ret.size()>0)
	{
		if(/*Trim*/(ret[ret.size()-1])=="")
			ret.pop_back();
	}
	fclose(fp);
	return ret;//0成功
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

vector<int> atoMtx(const char *str)
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
				return vi;
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
	return vi;
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

vector<vector<int> > StrtoInt(const vector<string>& ElemSet)
{
	vector<vector<int> > ret(ElemSet.size());
	for(int i=0;i<ElemSet.size();i++)
	{
		vector<int> I;
		vector<string> vsi=split(ElemSet[i],",");
		for(int j=0;j<vsi.size();j++)
		{
			I.push_back(atoi(vsi[j].c_str()));
		}
		ret[i]=I;
	}
	return ret;
}

int sqrti(int x)
{
	int ret=(int)(sqrtf(x));
	return ret;
}

int addInF4(int a,int b)
{
	if(a>=4||a<0)
		return -1;
	if(b>=4||b<0)
		return -1;
	static int g_Add[4][4]={
		{0,1,2,3},
		{1,0,3,2},
		{2,3,0,1},
		{3,2,1,0}
	};
	return g_Add[a][b];
}

int mulInF4(int a,int b)
{
	if(a>=4||a<0)
		return -1;
	if(b>=4||b<0)
		return -1;
	static int g_Mul[4][4]={
		{0,0,0,0},
		{0,1,2,3},
		{0,2,3,1},
		{0,3,1,2}
	};
	return g_Mul[a][b];
}

vector<vector<int> > atoTable(vector<vector<int> >& ElemSet,int P=0)
{
	vector<vector<int> > ret(ElemSet.size());
	int n=sqrti(ElemSet[0].size());
	for(int i=0;i<ElemSet.size();i++)
	{
		vector<int> I(ElemSet.size());
		for(int j=0;j<ElemSet.size();j++)
		{
			vector<int> ij(n*n);
			if(P==4 && n==2)
			{
				ij[0]=addInF4(mulInF4(ElemSet[i][0],ElemSet[j][0]),mulInF4(ElemSet[i][1],ElemSet[j][2]));
				ij[1]=addInF4(mulInF4(ElemSet[i][0],ElemSet[j][1]),mulInF4(ElemSet[i][1],ElemSet[j][3]));
				ij[2]=addInF4(mulInF4(ElemSet[i][2],ElemSet[j][0]),mulInF4(ElemSet[i][3],ElemSet[j][2]));
				ij[3]=addInF4(mulInF4(ElemSet[i][2],ElemSet[j][1]),mulInF4(ElemSet[i][3],ElemSet[j][3]));
			}
			else
			{
				Brmul(&(ElemSet[i][0]),&(ElemSet[j][0]),n,n,n,&(ij[0]));
				if(P>0)
				{
					for(int m=0;m<n*n;m++)
					{
						ij[m]=ij[m]%P;
					}
				}
			}
			int ij2=-1;
			for(int k=0;k<ElemSet.size();k++)
			{
				int iRet=memcmp(&ElemSet[k][0],&ij[0],sizeof(int)*n*n);
				if(iRet==0)
				{
					ij2=k;
					break;
				}
			}
			I[j]=ij2+1;
		}
		ret[i]=I;
	}
	return ret;
}

vector<int> IsLegalMtx(const vector<vector<int> > &mtx)
{
	vector<int> ret(3);
	int illegal=-1;
	ret[1]=mtx.size();
	if(ret[1]==0)
	{
		ret[0]=illegal;//不是合法矩阵
		return ret;
	}
	ret[2]=mtx[0].size();
	if(ret[2]==0)
	{
		ret[0]=illegal;//不是合法矩阵
		return ret;
	}
	for(int i=1;i<ret[1];i++)
	{
		if(mtx[i].size()!=ret[2])
		{
			ret[0]=illegal;//不是合法矩阵
			return ret;
		}
	}
	ret[0]=0;//是合法矩阵
	return ret;
}

bool SaveTable(const char *fn,const vector<vector<int> > &A)
{
	vector<int> AFlag=IsLegalMtx(A);
	if(AFlag[0]==-1)
		return false;
	FILE *fp;
	if((fp=fopen(fn,"wb+"))!=NULL)
	{
		for(int i=0;i<AFlag[1];i++)
		{
			for(int j=0;j<AFlag[2];j++)
			{
				fprintf(fp,"%d ",A[i][j]);
			}
			fprintf(fp,"\r\n");
		}
		fclose(fp);
	}
	return true;
}

int main(int argc, char **argv)
{
   //vector<string> S3=LoadMtxData("S4Set.txt");

	char sz[100]={0};
	char sz1[100]={0};
	char sz2[100]={0};
	if(argc<2)
	{
		printf("请输入矩阵群A文件名：");
		scanf("%s",sz);
	}
	else
		strcpy(sz,argv[1]);
	if(argc<3)
	{
		strcpy(sz1,sz);
		strcat(sz1,"Table.txt");
	}
	else
	{
		strcpy(sz1,argv[2]);
		strcat(sz1,"Table.txt");
	}
	if(argc<4)
	{
		printf("请输入特征P或域F_P的阶P：");
		scanf("%s",sz2);
	}
	else
	{
		strcpy(sz2,argv[3]);
	}

	vector<string> Gn=LoadMtxData(sz);
	vector<vector<int> > iGn=StrtoInt(Gn);
	vector<vector<int> > vvGn=atoTable(iGn,atoi(sz2));
	bool bret=SaveTable(sz1,vvGn);
	if(bret)
	{
		printf("计算矩阵群的凯莱表完毕！");
	}
	return 0;
}
