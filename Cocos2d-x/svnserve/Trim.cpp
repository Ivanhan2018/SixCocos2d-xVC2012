#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

namespace We
{
	typedef vector<string> StringVector;

	class StringUtil
	{
	public:
		typedef std::stringstream StrStreamType;
		// 去掉空格
		static void Trim(string& str,bool left=true,bool right=true);
	};

    string Trim(const string& theString);
    wstring Trim(const wstring& theString);
}

inline void inlineLTrim(string &theData,const string& theChars="\t\r\n")
{
   theData.erase(0,theData.find_first_not_of(theChars));
}

inline void inlineLTrim(wstring &theData,const wstring& theChars=L"\t\r\n")
{
   theData.erase(0,theData.find_first_not_of(theChars));
}

inline void inlineRTrim(string &theData,const string& theChars="\t\r\n")
{
	theData.resize(theData.find_last_not_of(theChars)+1);
}

inline void inlineTrim(string &theData,const string& theChars="\t\r\n")
{
   inlineRTrim(theData,theChars);
   inlineLTrim(theData,theChars);
}

namespace We
{
	void StringUtil::Trim(string& str,bool left/*=true*/,bool right/*=true*/)
	{
		static const string delims="\t\r";
		if(right)
			str.erase(str.find_last_not_of(delims)+1);//trim right
		if(left)
			str.erase(0,str.find_first_not_of(delims));//trim left
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

     wstring Trim(const wstring& theString)
	 {
	 	int aStartPos=0;
		while(aStartPos<(int)theString.length() && isspace(theString[aStartPos]))
			aStartPos++;
		int anEndPos=theString.length()-1;
		while(anEndPos>=0 && isspace(theString[anEndPos]))
			anEndPos--;
		return theString.substr(aStartPos,anEndPos-aStartPos+1);
	 }
}

int main(int argc, char* argv[])
{
	string strSrc;
    if(argc>1)
	{
		strSrc=argv[1];
	}
    else
	{
		printf("usage: ./Trim strSrc\n例如:\n./Trim \" han shou qing \"\n");
		return 0;
	}
	string ret=We::Trim(strSrc);
	printf("strSrc.length=%d,ret=%s,ret.length=%d\n",strSrc.length(),ret.c_str(),ret.length());
    return 0;
}