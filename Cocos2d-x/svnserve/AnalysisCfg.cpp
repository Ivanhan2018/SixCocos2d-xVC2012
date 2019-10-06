// 精细算法AnalysisCfg.cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<iterator>//linux下编译ostream_iterator需要加入这个头文件
using namespace std;

vector<int> AnalysisCfg(int cfg[5])
{
	int cfg0[5]={0};
	memcpy(cfg0,cfg,sizeof(cfg0));
	int ZeroCount=0;
	for(int i=0;i<5;i++)
	{
		if(cfg0[i]==0)
		{
			ZeroCount--;
			cfg0[i]=ZeroCount;
		}
	}
	int cfg1[5]={0};
	memcpy(cfg1,cfg0,sizeof(cfg0));
	sort(cfg0,cfg0+5,greater<int>());

	vector<int> retV(5);
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(cfg1[i]==cfg0[j])
			{
				retV[i]=j;
				break;
			}
		}
	} 
	return retV;
}

int main()
{
	int cfg[5]={13,3,0,0,1};
	vector<int> ret=AnalysisCfg(cfg);
	
	typedef ostream_iterator<int> ostream_itr;
	copy(ret.begin(), ret.end(), ostream_itr(cout, "\n"));	

#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}
