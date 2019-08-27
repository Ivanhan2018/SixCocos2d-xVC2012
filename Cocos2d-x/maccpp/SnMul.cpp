#include<iostream>
#include<vector>
#include<string>
using namespace std;

std::vector<string> split( const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0)
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
vector<int> Mul(int N,const vector<int> & m,const vector<int> & n)
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

vector<int> split2(const string& str)
{
	vector<string> m=split(str,",");
	vector<int> ret(m.size());
	for(int i=0;i<m.size();i++)
	{
		ret[i]=atoi(m[i].c_str());
	}
	return ret;
}


int main(int argc, char **argv)
{
	char sz[100]={0};
	char sz1[100]={0};
	char sz2[100]={0};
	if(argc<2)
	{
		printf("请输入置换次数N：");
		scanf("%s",sz);
	}
	else
		strcpy(sz,argv[1]);
	if(argc<3)
	{
		printf("请输入置换m：");
		scanf("%s",sz1);
	}
	else
		strcpy(sz1,argv[2]);
	if(argc<4)
	{
		printf("请输入置换n：");
		scanf("%s",sz2);
	}
	else
		strcpy(sz2,argv[2]);

	int N=atoi(sz);
	vector<int> m=split2(sz1);
	vector<int> n=split2(sz2);
	vector<int> mn=Mul(N,m,n);
	printf("置换m*n：");
	for(int i=0;i<mn.size();i++)
	{
		printf("%d",mn[i]);
		if(i<mn.size()-1)
			printf(",");
	}
	printf("\n");
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}
