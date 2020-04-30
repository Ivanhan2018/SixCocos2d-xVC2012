// g++ -std=c++11 -o parsePoly parsePoly.cpp
// 解析一个多项式的系数和指数
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class StringUtil
{
public:
	static string stringReplace(const  string&   input,const   string&   find,const   string&   replaceWith);

	// 根据所给字符对字符串进行分割
	static std::vector<string> split( const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0);

	// 去掉所有空格
	static void trimAllSpace(std::string &str);

	// 得到单项式的系数和次数
	static vector<int> CoefAndDeg(const string &str);

	// 解析多项式
	static bool parsePoly(const char* strA,vector<vector<int> >& result);

};

//   原始串
//   替换源串
//   替换目的串
string StringUtil::stringReplace(const  string&   input,const   string&   find,const   string&   replaceWith)   
{   
	string   strOut(input);
	int   curPos   =   0;   

	int   pos;
	while((pos=strOut.find(find,curPos))!=-1)   
	{   
		strOut.replace(pos,find.size(),replaceWith);             //   一次替换   
		curPos=pos+replaceWith.size();                     //   防止循环替换!!   
	}   

	return   strOut;   
}   

/** Returns a std::stringVector that contains all the substd::strings delimited
   by the characters in the passed <code>delims</code> argument.
   @param 
   delims A list of delimiter characters to split by
   @param 
   maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
   parameters is > 0, the splitting process will stop after this many splits, left to right.
   */
std::vector<string> StringUtil::split( const std::string& str, const std::string& delims/* = "\t\n "*/, unsigned int maxSplits/* = 0*/)
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

void StringUtil::trimAllSpace(std::string &str)
{
	std::string::iterator destEnd=std::remove_if(str.begin(),str.end(),[](char ch){return std::isspace(static_cast<unsigned char>(ch));});
	str.resize(destEnd-str.begin());
}

vector<int> StringUtil::CoefAndDeg(const string &str)
{
	string s=str;
	vector<int> ret;
	int Coef=0;
	int Deg=0;
	unsigned int loc = s.find( "x", 0 );
	if(loc != string::npos)
	{
		unsigned int loc1 = s.find( "x^", 0 );
		if(loc1 == string::npos)
		{
			Deg=1;
		}
		else
		{
	        string strR=s.substr(loc1+2,s.length()-loc1-2);
			Deg=atoi(strR.c_str());
		}
		if(loc==0)
		{
			Coef=1;
		}
		else
		{
			if(loc==1 && s[0]=='-')
		    {
			   Coef=-1;
		    }
			else
			{
			   	string strL=s.substr(0,loc1+1);
			    Coef=atoi(strL.c_str());
			}
		}
		ret.push_back(Coef);
		ret.push_back(Deg);
	}
	else
	{
		ret.push_back(atoi(s.c_str()));
		ret.push_back(0);
	}
	return ret;
}

bool StringUtil::parsePoly(const char* strA,vector<vector<int> >& result)
{
	if(strA!=0)
	{
		result.clear();
		string StrA=StringUtil::stringReplace(strA,"-","+-");
		vector<vector<int> > vMonomials;
		vector<string> strArr=StringUtil::split(StrA,"+");
		int nSize=strArr.size();
		for(int i=0;i<nSize;i++)
		{
			StringUtil::trimAllSpace(strArr[i]);
			vector<int> cds=StringUtil::CoefAndDeg(strArr[i]);
			result.push_back(cds);
		}
		return true;
	}
	return false;
}

void PrintArr2(vector<vector<int> >& vv) 
{
	cout << "[" ;
	for (int i = 0; i < vv.size(); i++) {
		cout << "[" ;
		for (int j = 0; j < vv[i].size(); j++) {
			cout << vv[i][j]; 
			if(j<vv[i].size()-1)
			  cout << "," ;  			
		}
	    cout << "]" ;	
        if(i<vv.size()-1)
          cout << "," ;   			
	}
	cout << "]" ;
	cout << endl ;
}

int main(int argc, char* argv[])
{
	const char* strA=" 7x^4   +  x^2";
	vector<vector<int> > vMonomialsA;
	bool bretA=StringUtil::parsePoly(strA,vMonomialsA);
	cout<<strA<<"=";	
    PrintArr2(vMonomialsA);
	
	const char* strB="6x^3 - 3x^2";
	vector<vector<int> > vMonomialsB;
	bool bretB=StringUtil::parsePoly(strB,vMonomialsB);
	cout<<strB<<"=";
    PrintArr2(vMonomialsB);
	
	return 0;
}
