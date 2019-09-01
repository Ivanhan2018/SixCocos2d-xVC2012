#include<vector>
#include<string>
#include<algorithm>
using namespace std;

/** Returns a std::stringVector that contains all the substd::strings delimited
   by the characters in the passed <code>delims</code> argument.
   @param 
   delims A list of delimiter characters to split by
   @param 
   maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
   parameters is > 0, the splitting process will stop after this many splits, left to right.
   */
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

vector<vector<double>> atomtx(const char* strMtx)
{
	vector<vector<double>> vvMtx;
	if(strMtx!=0)
	{
		vector<string> AllRows=split(strMtx,";");
		for(int i=0;i<AllRows.size();i++)
		{
			vector<double> fRow;
			vector<string> sRow=split(AllRows[i],",");
			for(int j=0;j<sRow.size();j++)
			{
				double f=atof(sRow[j].c_str());
				fRow.push_back(f);
			}
			vvMtx.push_back(fRow);
		}
	}
	return vvMtx;
}

vector<int> IsLegalMtx(const vector<vector<double>> &mtx)
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

int main(int argc, char* argv[])
{
	// 3行2列矩阵
	const char* strMtx="256,160;196,100;150,255";
	vector<vector<double>> vvMtx=atomtx(strMtx);

	vector<int> mtxFlag=IsLegalMtx(vvMtx);
	if(mtxFlag[0]==0)
	{
		double *pArr=(double *)malloc(mtxFlag[1]*mtxFlag[2]*sizeof(double));

		for(int i=0;i<mtxFlag[1];i++)
			memcpy(&pArr[mtxFlag[2]*i],&vvMtx[i][0],sizeof(double)*mtxFlag[2]);

		free(pArr);
		pArr=0;
	}

	double Arr32[3][2]={0};
	//memcpy(Arr32,&vvMtx[0][0],sizeof(Arr32));//不要这样写
	for(int i=0;i<3;i++)
		memcpy(Arr32[i],&vvMtx[i][0],sizeof(Arr32[i]));


#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}