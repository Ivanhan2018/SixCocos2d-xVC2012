#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
//#include <fstream>
#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

// 计算直积群的凯莱表的小工具DP.exe

std::vector<string> split( const std::string& str, const std::string& delims, unsigned int maxSplits = 0)
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


vector<char> lof(const char *fn)
{
	vector<char> ret;
	FILE *fp;
	int i=0;
	char ch=0;
	if((fp=fopen(fn, "rb"))!=NULL)
	{
		fseek(fp, 0, SEEK_SET); 
		while (ch!= EOF) 
		{
			i++; 
			ch = fgetc(fp);
			ret.push_back(ch);
		}; 
		fclose(fp);
	}
	if(ret.size()>0 && ret[ret.size()-1]==EOF)
		ret.pop_back();
	return ret;
}

vector<char> CharArrToNormal(const vector<char>& vec)
{
	vector<char> ret;
	int n=vec.size();
	for(int i=0;i<n;i++)
	{
		if(vec[i]==32||vec[i]==13||vec[i]==10)
		{
			if(ret.size()>0 && ret[ret.size()-1]!=',')
				ret.push_back(',');
		}
		else
		{
			ret.push_back(vec[i]);
		}
	}
	return ret;
}

string CharArrToStr(const vector<char>& vec)
{
	string str;
	int n=vec.size();
	for(int i=0;i<n;i++)
	{
		str.push_back(vec[i]);
	}
	return str;
}

vector<vector<int> > atoTable(const char* strMtx)
{
	vector<vector<int> > vvMtx;
	vector<int> iAll;
	if(strMtx!=0)
	{
		vector<string> All=split(strMtx,",");
		for(int i=0;i<All.size();i++)
		{
			int iElem=atoi(All[i].c_str());
			iAll.push_back(iElem);
		}
	}
	int n=iAll.size();
	int n1=(int)sqrtf(n);
	if(n1*n1==n)
	{
		for(int i=0;i<n1;i++)
		{
			vector<int> iRow;
			for(int j=0;j<n1;j++)
			{
				int iElem=iAll[i*n1+j];
				iRow.push_back(iElem);
			}
			vvMtx.push_back(iRow);
		}
	}
	return vvMtx;
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


vector<vector<int> > ABmul(const vector<vector<int> > &A,const vector<vector<int> > &B)
{
	vector<vector<int> > C;
	vector<int> AFlag=IsLegalMtx(A);
	if(AFlag[0]==-1)
		return C;
	vector<int> BFlag=IsLegalMtx(B);
	if(BFlag[0]==-1)
		return C;
	int nB=BFlag[1];
	int n=AFlag[1]*BFlag[1];

	for(int a=0;a<n;a++)
	{
		vector<int> iRow;
		for(int b=0;b<n;b++)
		{
			int aj=a%nB;
			int ai=a/nB;
			int bj=b%nB;
			int bi=b/nB;
			int i=A[ai][bi]-1;
			int j=B[aj][bj]-1;
			int c=nB*i+j+1;
			iRow.push_back(c);
		}
		C.push_back(iRow);
	}
	return C;
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

int main(int argc, char* argv[])
{
	char sz[100]={0};
	char sz1[100]={0};
	char sz2[100]={0};
	if(argc<2)
	{
		printf("请输入群A凯莱表文件名：");
		scanf("%s",sz);
	}
	else
		strcpy(sz,argv[1]);
	if(argc<3)
	{
		printf("请输入群B凯莱表文件名：");
		scanf("%s",sz1);
	}
	else
		strcpy(sz1,argv[2]);
	if(argc<4)
	{
		printf("请输入直积群A×B凯莱表文件名：");
		scanf("%s",sz2);
	}
	else
		strcpy(sz2,argv[3]);

	vector<char> D3=lof(sz);
	vector<char> C2=lof(sz1);

	string strD3=CharArrToStr(CharArrToNormal(D3));
	string strC2=CharArrToStr(CharArrToNormal(C2));

	vector<vector<int> > vvD3=atoTable(strD3.c_str());
	vector<vector<int> > vvC2=atoTable(strC2.c_str());

	vector<vector<int> > vvD3C2=ABmul(vvD3,vvC2);
	bool bret=SaveTable(sz2,vvD3C2);

	if(bret)
	{
		//MessageBoxA(NULL,"计算直积群的凯莱表完毕！","提示",MB_OK);
                printf("计算直积群的凯莱表完毕！\n");
	}

	//system("pause");
	return 0;
}
