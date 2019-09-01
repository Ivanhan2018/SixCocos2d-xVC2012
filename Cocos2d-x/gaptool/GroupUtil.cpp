//#include "stdafx.h"
#include "GroupUtil.h"

std::vector<string> GroupUtil::split( const std::string& str, const std::string& delims, unsigned int maxSplits /*= 0*/)
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

// S_N中置换乘法m*n
vector<int> GroupUtil::Mul(int N,const vector<int> & m,const vector<int> & n)
{
	vector<int> tArr(N);
	vector<int> aArr(N);
	vector<int> taArr(N);
	memcpy(&tArr[0],&m[0],sizeof(tArr[0])*N);
	memcpy(&aArr[0],&n[0],sizeof(aArr[0])*N);
	for(int i=0;i<N;i++)
		taArr[i]=aArr[tArr[i]-1];
	vector<int> ret(N);
	memcpy(&ret[0],&taArr[0],sizeof(taArr[0])*N);
	return ret;
}

vector<vector<int> > GroupUtil::Order(int N,const vector<int> & m)
{
	vector<vector<int> > ret;
	vector<int> mi=m;
	vector<int> m0(N);
	for(int i=0;i<N;i++)
	{
		m0[i]=i+1;
	}
	while(memcmp(&mi[0],&m0[0],sizeof(int)*N)!=0)
	{
		ret.push_back(mi);
		mi=Mul(N,mi,m);
	}
	ret.push_back(mi);
	return ret;
}

int GroupUtil::IsInFG(int N,const vector<vector<int> > FG,const vector<int> & m)
{
	for(int i=0;i<FG.size();i++)
	{
		if(memcmp(&m[0],&FG[i][0],sizeof(int)*N)==0)
			return i;
	}
	return -1;
}

bool GroupUtil::FG(const char *szFG,const char *szfilename)
{
	vector<vector<int> > FG;
	vector<string> vM=split(szFG,";");
	int M=vM.size();

        // 判断是不是矩阵表示
        if(M>=3)
        {
           size_t loc = vM[0].find_first_of(",", 0 );
           if(loc == string::npos )
	   {
              string strPath=szfilename;
	      //去掉.txt
	      int pos1 = strPath.find_last_of(".");
	      strPath = strPath.substr(0, pos1);

	      char szcmd[100]={0};
	      sprintf(szcmd,"./FGMtx \"%s\" \"%s\"",szFG,strPath.c_str());
	      system(szcmd);
              return true;
	   }
        }


	for(int i=0;i<M;i++)
	{
		vector<string> vM1=split(vM[i],",");
		int N=vM1.size();
		vector<int> viM1(N);
		for(int i=0;i<N;i++)
		{
			viM1[i]=atoi(vM1[i].c_str());
		}
		FG.push_back(viM1);
	}
	int N=FG[0].size();
	vector<int> E;
	for(int i=0;i<N;i++)
	{
		E.push_back(i+1);
	}
	int bIn=IsInFG(N,FG,E);
	if(bIn==-1)
	{
	        FG.insert(FG.begin(),E);
	} 
	int R=FG.size();
	int cnt=R;
	int cnt1=R;
	do{
		cnt=FG.size();
		for(int i=0;i<cnt;i++)
		{
			for(int j=0;j<cnt;j++)
			{
				vector<int> IJ=Mul(N,FG[i],FG[j]);
				int bIn=IsInFG(N,FG,IJ);
				if(bIn==-1)
				{
					FG.push_back(IJ);
				}
			}
		}
		cnt1=FG.size();
	}while(cnt1>cnt);

	ofstream fout(szfilename);
	int n=FG.size();
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			vector<int> IJ=Mul(N,FG[i],FG[j]);
			int bIn=IsInFG(N,FG,IJ);
			fout<<bIn+1<<" ";
		}
		fout<<endl;
	}
	cout<<szfilename<<"生成完毕！"<<endl;

	return true;
}

vector<int> GroupUtil::rank(const vector<vector<int> > &A)
{
        vector<int> vr; 
        vector<vector<int> > vvr;// 遍历过的生成元集
	vector<int> AFlag=IsLegalMtx(A);
	if(AFlag[0]==-1)
		return vr;
	int n=AFlag[1];
        if(n>=6)
        {
	    cout<<"n>=6，计算终止！"<<endl; 
            vr.clear();                   
            return vr;
        } 
	for(int r=1;r<=n-1;r++)
	{
          vector<int> A1(&A[0][1],&A[0][1]+n-1);
          do {
              	vector<int> temp(&A1[0],&A1[0]+r);
                bool bFind=false;
	        for(int t=0;t<vvr.size();t++)
	        {  
		    if(vvr[t].size()==r && memcmp(&temp[0],&vvr[t][0],sizeof(int)*r)==0)
			bFind=true;
	        }
                if(bFind)
                   continue;              
              	vector<int> FG(&A1[0],&A1[0]+r);
                vvr.push_back(FG);
                FG.insert(FG.begin(),1);
	        int R=FG.size();
	        int cnt=R;
	        int cnt1=R;
	        do{
		     cnt=FG.size();
		     for(int i=1;i<cnt;i++)
		     {
			for(int j=1;j<cnt;j++)
			{
				int IJ=A[FG[i]-1][FG[j]-1];
	                        vector<int>::const_iterator it=std::find(FG.begin(),FG.end(),IJ);
				if(it==FG.end())
				{
				   FG.push_back(IJ);
				}
			 }
		       }
		       cnt1=FG.size();
	            }while(cnt1>cnt);
	         if(FG.size()==n)
		    return temp;
             }while( next_permutation(A1.begin(),A1.end()));
	}
        return vr;
}

vector<char> GroupUtil::lof(const char *fn)
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

vector<char> GroupUtil::CharArrToNormal(const vector<char>& vec)
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

string GroupUtil::CharArrToStr(const vector<char>& vec)
{
	string str;
	int n=vec.size();
	for(int i=0;i<n;i++)
	{
		str.push_back(vec[i]);
	}
	return str;
}

vector<vector<int> > GroupUtil::atoTable(const char* strMtx)
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

vector<int> GroupUtil::IsLegalMtx(const vector<vector<int> > &mtx)
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


vector<vector<int> > GroupUtil::ABmul(const vector<vector<int> > &A,const vector<vector<int> > &B)
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

bool GroupUtil::SaveTable(const char *fn,const vector<vector<int> > &A)
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

vector<int>  GroupUtil::Factors(int n)
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
int GroupUtil::getGnEOrder(const vector<vector<int> > &A,int a)
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

bool GroupUtil::SaveGnEOrder(const char *srcfn,const char *Desfn,const char *DesGn,int iFlag)
{
	vector<char> A=lof(srcfn);
	string strA=CharArrToStr(CharArrToNormal(A));
	vector<vector<int> > vvA=atoTable(strA.c_str());

	vector<int> AFlag=IsLegalMtx(vvA);
	if(AFlag[0]==-1||AFlag[1]!=AFlag[2])
		return false;

	ofstream fout(Desfn);
	vector<int> vOrders=Factors(AFlag[1]);
	vector<int> vCounts(AFlag[1]+1);
	for(int i=0;i<AFlag[1];i++)
	{
		int ord=getGnEOrder(vvA,i);
		printf("G%dElementToOrder(%d)=%d\n",AFlag[1],i,ord);
		fout<<"G"<<AFlag[1]<<"ElementToOrder("<<i<<")="<<ord<<endl;
		vCounts[ord]=vCounts[ord]+1;
	}
	string strF;
	{
		char sz[200]={0};
		if(DesGn==0)
		{
			sprintf(sz,"G%d有",AFlag[1]);
                        fout<<"G"<<AFlag[1]<<"有"<<AFlag[1];
		}
		else
		{
			sprintf(sz,"%s有",DesGn);
                        fout<<DesGn<<"有";
		}
		strF=sz;
	}
	for(int i=0;i<vOrders.size();i++)
	{
		char sz[200]={0};
		sprintf(sz,"%d个%d阶元，",vCounts[vOrders[i]],vOrders[i]);
		strF+=sz;
                fout<<vCounts[vOrders[i]]<<"个"<<vOrders[i]<<"阶元";
                if(i<vOrders.size()-1)
                fout<<"，";
	}
	if(strF.size()>2)
	{
		strF=strF.substr(0,strF.size()-2);
	}
	printf("%s\n",strF.c_str());
        if(iFlag==1)
        {
	  printf("最小生成元集：\n");
	  fout<<"最小生成元集："<<endl;
	  vector<int> vr=rank(vvA);
          int r=vr.size();
	  for(int i=0;i<r;i++)
	  {
		printf("%d\n",vr[i]);
		fout<<vr[i]<<endl;
	  }
          printf("rank=%d\n",r);
	  fout<<"rank="<<r<<endl;
        }
	fout.close();
	return true;
}

// 从路径名中分离出文件名
char * GroupUtil::find_file_name(char *name)
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
void GroupUtil::filter_ext_name(char *name)
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

string GroupUtil::FormatStr(int cnt)
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

string GroupUtil::Trim(const string& theString)
{
	int aStartPos=0;
	while(aStartPos<(int)theString.length() && isspace(theString[aStartPos]))
		aStartPos++;
	int anEndPos=theString.length()-1;
	while(anEndPos>=0 && isspace(theString[anEndPos]))
		anEndPos--;
	return theString.substr(aStartPos,anEndPos-aStartPos+1);
}

vector<int> GroupUtil::atoMtx(const char *str)
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

vector<vector<int> > GroupUtil::StrtoInt(const vector<string>& ElemSet)
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
