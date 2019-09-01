#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

// 根据群的凯莱表分析其中心、换位子群、射影中心、射影换位子群的小工具ZDOfG.exe

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
	//return (i-1); 
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

bool PrintSaveTable(const char *fn,const vector<vector<int> > &A)
{
	vector<int> AFlag=IsLegalMtx(A);
	if(AFlag[0]==-1)
		return false;
	FILE *fp;
	if((fp=fopen(fn,"ab+"))!=NULL)
	{
		for(int i=0;i<AFlag[1];i++)
		{
			for(int j=0;j<AFlag[2];j++)
			{
		           printf("%d ",A[i][j]);
                           fprintf(fp,"%d ",A[i][j]);
			}
			printf("\r\n");
			fprintf(fp,"\r\n");
		}
		fclose(fp);
	}
	return true;
}

vector<int>  Factors(int n)
{
	vector<int> ret;
	if(n<1)
		return ret;
	for(int i=1;i<=n;i++)
	{
		if(n%i==0)
		{
			ret.push_back(i);
		}
	}
	return ret;
}

// 未知n阶群的群元的阶
int getGnEOrder(const vector<vector<int> > &A,int a)
{
	vector<int> AFlag=IsLegalMtx(A);
	if(AFlag[0]==-1)
		return -1;
	int n=AFlag[1];
	if(a<0||a>=n)
		return -1;
	int t=0;
	for(int i=1;i<=n;i++)
	{
		t=A[t][a]-1;
		if(t==0)
			return i;
	}
	return -1;
}


bool IsInCenterOfG(const vector<vector<int> > &vvG,int j)
{
	int N=vvG.size();
	for(int i=0;i<N;i++)
	{
		int ij=vvG[i][j]-1;
		int ji=vvG[j][i]-1;
		if(ij==ji)
			continue;
		else
			return false;
	}
	return true;
}

vector<int> CenterOfG(const vector<vector<int> > &vvG)
{
	vector<int> ret;
	int N=vvG.size();
	for(int i=0;i<N;i++)
	{
		if(IsInCenterOfG(vvG,i))
			ret.push_back(i);
		else
			continue;
	}
	return ret;
}

int Inv(const vector<vector<int> > &vvG,int j)
{
	int N=vvG.size();
	for(int i=0;i<N;i++)
	{
		int ij=vvG[i][j]-1;
		if(ij==0)
			return i;
	}
	return -1;
}

vector<int> commutatorOfG(const vector<vector<int> > &vvG)
{
	vector<int> ret;
	ret.push_back(0);
	int N=vvG.size();
	for(int i=0;i<N;i++)
	{
		int I=Inv(vvG,i);
		for(int j=i+1;j<N;j++)
		{
			int ij=vvG[i][j]-1;
			int J=Inv(vvG,j);
			int IJ=vvG[I][J]-1;
			int ijIJ=vvG[ij][IJ]-1;
			ret.push_back(ijIJ);
		}
	}
	sort(ret.begin(),ret.end());
	ret.erase(unique(ret.begin(),ret.end()),ret.end());
	return ret;
}

int ToNormal(const vector<int> &v,int a)
{
	for(int i=0;i<v.size();i++)
	{
		if(v[i]==a)
			return i;
	}
	return -1;
}

bool SaveZDOfG(const char *srcfn,const char *Desfn,const char *DesGn=0)
{
	vector<char> A=lof(srcfn);
	string strA=CharArrToStr(CharArrToNormal(A));
	vector<vector<int> > vvA=atoTable(strA.c_str());

	vector<int> AFlag=IsLegalMtx(vvA);
	if(AFlag[0]==-1||AFlag[1]!=AFlag[2])
		return false;

	ofstream fout(Desfn);
	printf("中心：\n");
	fout<<"中心："<<endl;
	vector<int> ZA=CenterOfG(vvA);//0表示Z(D_3)={1}=C_1
	for(int i=0;i<ZA.size();i++)
	{
		printf("%d\n",ZA[i]);
		fout<<ZA[i]<<endl;
	}
	string strF;
	{
		char sz[200]={0};
		if(DesGn==0)
		{
			sprintf(sz,"|Z(G%d)|=%d",AFlag[1],ZA.size());
		}
		else
		{
			sprintf(sz,"|Z(%s)|=%d",DesGn,ZA.size());
		}
		strF=sz;
	}
	printf("%s\n",strF.c_str());
	fout<<strF.c_str()<<endl;

	printf("换位子群：\n");
	fout<<"换位子群："<<endl;
	vector<int> DA=commutatorOfG(vvA);//0表示(D_4)'={1}=C_1
	for(int i=0;i<DA.size();i++)
	{
		printf("%d\n",DA[i]);
		fout<<DA[i]<<endl;
	}
	string strF1;
	{
		char sz[200]={0};
		if(DesGn==0)
		{
			sprintf(sz,"|(G%d)'|=%d",AFlag[1],DA.size());
		}
		else
		{
			sprintf(sz,"|(%s)'|=%d",DesGn,DA.size());
		}
		strF1=sz;
	}
	printf("%s\n",strF1.c_str());
	fout<<strF1.c_str()<<endl;
	bool bArr[]={false,true};
	const char * szArr[2][2]={{"子群形式的中心凯莱表ZTableOfG：","子群形式的换位子群凯莱表DTableOfG："},{"规范形式的中心凯莱表ZTableOfG_N：","规范形式的换位子群凯莱表DTableOfG_N："}};
	for(int b=0;b<2;b++)
	{
		bool IsNormal=bArr[b]; 
		vector<char> A=lof(srcfn);
		string strA=CharArrToStr(CharArrToNormal(A));
		vector<vector<int> > vvA=atoTable(strA.c_str());
		vector<int> AFlag=IsLegalMtx(vvA);
		if(AFlag[0]!=-1 && AFlag[1]==AFlag[2])
		{
			printf("%s\n",szArr[b][0]);
			fout<<szArr[b][0]<<endl;
			vector<int> ZA=CenterOfG(vvA);//0表示Z(D_3)={1}=C_1
			for(int i=0;i<ZA.size();i++)
			{
				for(int j=0;j<ZA.size();j++)
				{
					if(IsNormal)
					{
						int ij=vvA[ZA[i]][ZA[j]]-1;
						int ij2=ToNormal(ZA,ij)+1;
						printf("%d ",ij2);
						fout<<ij2<<" ";
					}
					else
					{
						int ij=vvA[ZA[i]][ZA[j]];
						printf("%d ",ij);
						fout<<ij<<" ";
					}
				}
				printf("\n");
				fout<<endl;
			}
			printf("%s\n",szArr[b][1]);
			fout<<szArr[b][1]<<endl;
			vector<int> DA=commutatorOfG(vvA);//0表示(D_4)'={1}=C_1
			for(int i=0;i<DA.size();i++)
			{
				for(int j=0;j<DA.size();j++)
				{
					if(IsNormal)
					{
						int ij=vvA[DA[i]][DA[j]]-1;
						int ij2=ToNormal(DA,ij)+1;
						printf("%d ",ij2);
						fout<<ij2<<" ";
					}
					else
					{
						int ij=vvA[DA[i]][DA[j]];
						printf("%d ",ij);
						fout<<ij<<" ";
					}

				}
				printf("\n");
				fout<<endl;
			}

		}
	}
	fout.close();
	return true;
}

vector<vector<int> > quotientGN(const vector<vector<int> > &vvG,const vector<int> &vN)
{
	vector<vector<int> > ret;
	int G=vvG.size();
	int N=vN.size();
	for(int i=0;i<G;i++)
	{
		vector<int> I;
		for(int j=0;j<N;j++)
		{
			int ij=vvG[i][vN[j]]-1;
			I.push_back(ij);
		}
		bool bNew=true;
		for(int k=0;k<ret.size();k++)
		{
			//判断I中的元素是否在ret中
			vector<int>::iterator p;
			p=std::find(ret[k].begin(),ret[k].end(),I[0]);
			if(p!=ret[k].end())
			{
				bNew=false;
				break;
			}
		}
		if(bNew)
		{
			ret.push_back(I);
		}
	}
	return ret;
}

vector<vector<int> > quotientGNTable(const vector<vector<int> > &vvG,const vector<int> &vN)
{
	vector<vector<int> > ret1=quotientGN(vvG,vN);
	int G=vvG.size();
	int H=ret1.size();
	vector<vector<int> > ret(H);
	for(int i=0;i<H;i++)
	{
		vector<int> I(H);
		for(int j=0;j<H;j++)
		{
			int ij=vvG[ret1[i][0]][ret1[j][0]]-1;
			int IJ=-1;
			for(int k=0;k<ret1.size();k++)
			{
				vector<int>::iterator p;
				p=std::find(ret1[k].begin(),ret1[k].end(),ij);
				if(p!=ret1[k].end())
				{
					IJ=k+1;
					break;
				}
			}
			I[j]=IJ;
		}
		ret[i]=I;
	}
	return ret;
}

bool SavePZDTableOfG(const char *srcfn,const char *Desfn,const char *DesGn=0)
{
	vector<char> A=lof(srcfn);
	string strA=CharArrToStr(CharArrToNormal(A));
	vector<vector<int> > vvA=atoTable(strA.c_str());
	vector<int> AFlag=IsLegalMtx(vvA);
	if(AFlag[0]==-1||AFlag[1]!=AFlag[2])
		return false;

	vector<int> ZA=CenterOfG(vvA);//0表示Z(D_3)={1}=C_1
	vector<vector<int> > PZA=quotientGNTable(vvA,ZA);
	printf("射影中心PZTableOfG：\n");
	ofstream fout(Desfn,ios::app);
	fout<<"射影中心PZTableOfG："<<endl;
	PrintSaveTable(Desfn,PZA);

	vector<int> DA=commutatorOfG(vvA);//0表示(D_4)'={1}=C_1
	vector<vector<int> > PDA=quotientGNTable(vvA,DA);
	printf("射影换位子群PDTableOfG：\n");
	ofstream foutD(Desfn,ios::app);
	foutD<<"射影换位子群PDTableOfG："<<endl;
	PrintSaveTable(Desfn,PDA);

	return true;
}


// 从路径名中分离出文件名
char * find_file_name(char *name)
{
	char *name_start = NULL;
	int sep = '/';
	if (NULL == name) {
	    printf("the path name is NULL\n");
	    return NULL;
	}
	name_start = strrchr(name, sep);

	return (NULL == name_start)?name:(name_start + 1);
}

// 过滤掉文件名中的扩展名
void filter_ext_name(char *name)
{
	char *name_start = NULL;
	int sep = '.';
	if (NULL == name) {
	    printf("the path name is NULL\n");
	    return;
	}
	name_start = strrchr(name, sep);

        while(NULL != name_start && *name_start!='\0')
        {
            *name_start='\0';
            name_start++;
        }
}

int main(int argc, char **argv)
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
#if defined(_WIN32)||defined(_WIN64)
		_splitpath(sz,0,0,sz1,0);
#else
                char *fn=find_file_name(sz);
                strcpy(sz1,fn);
                filter_ext_name(sz1);
#endif
		string strDes=sz;
		string strFn=sz1;
		strFn.insert(0,"ZD(");
		strFn+=")";
		strcpy(sz2,sz1);
		strDes.replace(strDes.find(sz1,0),strlen(sz1),strFn.c_str());
		strcpy(sz1,strDes.c_str());
	}
	else
		strcpy(sz1,argv[2]);

	bool bret=SaveZDOfG(sz,sz1,sz2);
	if(bret)
	{
		printf("计算群的中心、换位子群完毕！\n");
	}
	bool bret2=SavePZDTableOfG(sz,sz1,sz2);
	if(bret2)
	{
		printf("计算群的射影中心、射影换位子群完毕！\n");
	}

	return 0;
}