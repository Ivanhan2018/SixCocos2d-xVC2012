#include "./PublicHead.h"
#include "Often.h"

#include <io.h>

#include "./EasyDataTime.h"


COften::COften(void)
{
}


COften::~COften(void)
{
}


void COften::SafeDelete(BYTE*& p)
{
	if(p)
	{
		delete[] p;
		p = NULL;
	}
}

// 获得当前进程的路径
int COften::get_current_path(char* pszPath, int iPathLen)
{
	using namespace std ;
	char buf[256] = {0}; 

	GetModuleFileNameA(NULL,buf,sizeof(buf));

	string strTemp = buf;
	string::size_type  pos = 0;
	pos = strTemp.rfind('\\', strTemp.length());	// 从 strTemp 的尾部开始向头部查找指定的字符

	string strPath = strTemp.substr(0, pos+1);	
	_snprintf(pszPath, iPathLen, "%s", strPath.c_str());

	return 0;
}

// 获得当前进程的路径
int COften::get_current_path(string& strPath)
{
	using namespace std ;
	char buf[256] = {0}; 

	GetModuleFileNameA(NULL,buf,sizeof(buf));

	string strTemp = buf;
	string::size_type  pos = 0;
	pos = strTemp.rfind('\\', strTemp.length());	// 从 strTemp 的尾部开始向头部查找指定的字符
	strPath = strTemp.substr(0, pos+1);	
	
	return 0;
}

// 获得当前进程的路径
wstring COften::get_current_path()
{
	wchar_t buf[256] = {0}; 

	GetModuleFileNameW(NULL,buf,sizeof(buf));

	wstring strTemp = buf;
	wstring::size_type  pos;

	pos = strTemp.rfind('\\', strTemp.length());	// 从 strTemp 的尾部开始向头部查找指定的字符

	wstring strPath = strTemp.substr(0, pos+1);	

	return strPath;
}

// 创建目录
int COften::create_dir(wchar_t* pszDirName, int iDirNameLen)
{
	if(!pszDirName || 0==iDirNameLen)
		return 10;	// 目录名是空值或者长度不正确

	int iResult = 0;
	int iFlag = 0;
	DWORD dwError = 0;

	// iMode 值的含义：
	//	00 Existence only
	//	02  Write-only
	//	04 Read-only
	//	06 Read and write
	int iMode = 4;

	// 判断目录存在否
	iFlag = _waccess(pszDirName, iMode);

	if(0==iFlag)	// 存在该目录
	{
		return 0;
	}	
	else	// 没有该目录
	{
		iFlag = _wmkdir(pszDirName);
		if(0==iFlag)	// 建好了
		{
		}
		else	// 创建失败
		{
			dwError = GetLastError();
			iResult = 30;	// 创建失败
		}
	}

	return 0;
}

// 四字节对齐
int COften::fn4ByteMade(int iByteCount, int iUpLimit)
{
	if(-1 != iUpLimit)
	{
		if(iByteCount>=iUpLimit)
			return iUpLimit;
	}

	int iResultCount = 0;

	if ((iByteCount%4) !=0)	
		iResultCount = iByteCount/4 + 1;	//if data byte counter is not 4 bytes aligned
	else						
		iResultCount = iByteCount/4;		//if data byte counter is 4 bytes aligned

	iResultCount *= 4; 

	return iResultCount;
}

// 八字节对齐
int COften::fn8ByteMade(int iByteCount, int iUpLimit)
{
	if(-1 != iUpLimit)
	{
		if(iByteCount>=iUpLimit)
			return iUpLimit;
	}

	int iResultCount = 0;

	if ((iByteCount%8) !=0)	
		iResultCount = iByteCount/8 + 1;	//if data byte counter is not 8 bytes aligned
	else						
		iResultCount = iByteCount/8;		//if data byte counter is 8 bytes aligned

	iResultCount *= 8; 

	return iResultCount;
}

// 宽字节字串转成多字节字串
int COften::EasyWideCharToMultiByte(const wchar_t* wcsSource, int iSourceLen, string& strDest)
{
	int iReturn = 0;	// 返回值
	int iRes = 0;
	int iErr = 0;

	if(!wcsSource)
		return 10;	// 宽字节字串是空的

	// 首先要获得转换的长度，此长度已包含了结束符 \0 
	int iTranLen = WideCharToMultiByte(CP_OEMCP,NULL,wcsSource,-1,NULL,0,NULL,FALSE);
	char *szDest;
	szDest = new char[iTranLen+1];
	memset(szDest, 0, (iTranLen+1) * sizeof(char));
	
	if(!szDest)
		return 20;	// New 字串失败

	if(0==iTranLen)	
		return 30;	// 宽字节字串的长度为 0

	if(iSourceLen > iTranLen)
		return 40;	// 第2个传入参数（宽字节字串长度）非法

	iRes = WideCharToMultiByte (CP_OEMCP, NULL, wcsSource, -1, szDest, iTranLen, NULL, FALSE);
	iErr = GetLastError();

	if(0==iRes)	// 转换失败
		iReturn = 80;
	else
		strDest = szDest;

	delete []szDest;

	return iReturn;
}

// 多字节字串转成宽字节字串
int COften::EasyMultiByteToWideChar(const char* szSource, int iSourceLen, wstring& wcszDest)
{
	/*
	函数原型：
	int MultiByteToWideChar(
							UINT CodePage,
							DWORD dwFlags,        
							LPCSTR lpMultiByteStr,
							int cbMultiByte,      
							LPWSTR lpWideCharStr, 
							int cchWideChar       
							);

	参数说明：
	1、CodePage
		指定要转换成的字符集代码页，它可以是任何已经安装的或系统自带的字符集，可选择以下代码页：
		CP_ACP         //当前系统ANSI代码页
		CP_MACCP       //当前系统Macintosh代码页
		CP_OEMCP       //当前系统OEM代码页，一种原始设备制造商硬件扫描码
		CP_SYMBOL      //Symbol代码页，用于Windows 2000及以后版本
		CP_THREAD_ACP  //当前线程ANSI代码页，用于Windows 2000及以后版本
		CP_UTF7  //UTF-7，设置此值时lpDefaultChar和lpUsedDefaultChar都必须为NULL
		CP_UTF8  //UTF-8，设置此值时lpDefaultChar和lpUsedDefaultChar都必须为NULL

	2、dwFlags
		指定是否转换成预制字符或合成的宽字符，对控制字符是否使用像形文字，以及怎样处理无效字符：
		MB_PRECOMPOSED //总是使用预制字符，即有单个预制字符时，就不会使用分解的基字符和不占空间字符。此为函数的

		默认选项，不能和MB_COMPOSITE合用
		MB_COMPOSITE   //总是使用分解字符，即总是使用基字符+不占空间字符的方式
		MB_ERR_INVALID_CHARS //设置此选项，函数遇到非法字符就失败并返回错误码ERROR_NO_UNICODE_TRANSLATION，否则	丢弃非法字符
		MB_USEGLYPHCHARS //使用像形字符代替控制字符

		3、lpMultiByteStr //要转换的字符串
		4、cbMultiByte    //要转换字符串的长度，-1表示转换到字符串结尾
		5、lpWideCharStr //接收转换后输出的宽字符串的缓冲区
		6、cchWideChar    //输出缓冲区大小，如果为0，lpMultiByteStr将被忽略，函数将返回所需缓冲区大小而不使用 lpWideCharStr

	返回值：
		为0表示调用失败；当cchWideChar为0时，函数将返回所需缓冲区大小
	*/

	int iReturn = 0;	// 返回值
	int iRes = 0;
	int iErr = 0;
	
	if(!szSource)
		return 10;	// 多字节字串为空

	// 首先要获得转换的长度，此长度已包含了结束符 \0 
	int iTranLen = MultiByteToWideChar(CP_ACP, 0, szSource, -1, NULL, 0);

	//if(iSourceLen < iTranLen)
	//	return 20;	// 多字节字串的长度不正确

	wchar_t* pWideChar = new wchar_t[iTranLen];	
	memset(pWideChar, 0, iTranLen * sizeof(wchar_t));

	if(!pWideChar)
		return 30;	// New 失败

	// 进行真正的转换
	iRes = MultiByteToWideChar(
								CP_ACP,
								0,
								szSource,
								-1,
								pWideChar,
								iTranLen
								);
	iErr = GetLastError();

	if(iRes<=0)
	{
		switch(iErr)
		{
		case ERROR_INSUFFICIENT_BUFFER:		// A supplied buffer size was not large enough, or it was incorrectly set to NULL.
			break;
		case ERROR_INVALID_FLAGS:			// The values supplied for flags were not valid.
			break;
		case ERROR_INVALID_PARAMETER:		// Any of the parameter values was invalid.
			break;
		case ERROR_NO_UNICODE_TRANSLATION:	// Invalid Unicode was found in a string.
			break;
		}

		iReturn = 80;	// 转换错误
	}
	else
	{
		wcszDest = pWideChar;
	}

	delete[] pWideChar;

	return iReturn;
}

// 判断是有效的指针，不要过于依赖此函数，这样会掩盖很多本可以解决的问题
BOOL COften::is_valid_point(const VOID* pPointer)
{
    if( NULL == pPointer )
        return FALSE;	// 空指针

    ULONG_PTR nPozition = (ULONG_PTR)pPointer;

	#if defined(_WIN64)

		if( (0xcdcdcdcdcdcdcdcd == nPozition) ||
			(0xcccccccccccccccc == nPozition) ||
			(0xfdfdfdfdfdfdfdfd == nPozition) ||
			(0xfeeefeeefeeefeee == nPozition) ||
			(0xdddddddddddddddd == nPozition) ||
			(0xabababababababab == nPozition) ||
			(0xfefefefefefefefe == nPozition) )
		{
			return FALSE;	// 空指针
		}

	#else
		if( (0xcdcdcdcd == nPozition) ||
			(0xcccccccc == nPozition) ||
			(0xfdfdfdfd == nPozition) ||
			(0xfeeefeee == nPozition) ||
			(0xdddddddd == nPozition) ||
			(0xabababab == nPozition) ||
			(0xfefefefe == nPozition) )
		{
			return FALSE;	// 空指针
		}

	#endif

    return TRUE;	// 有值
}

// 将一串字符按分隔符分割成多段字串
BOOL COften::devide_string_to_separator(const string &strIn, const string &strSeparator, vector<string> &vecStrOut)
{
	if(strIn.empty() || strSeparator.empty())
		return false;

	string::size_type posSeparator = strIn.find(strSeparator);

	if( string::npos == posSeparator)	// 未找到分隔符
	{
		vecStrOut.push_back(strIn);
		return true;
	}
	else	// 找到分隔符
	{
		int iCount = (int)posSeparator;
		vecStrOut.push_back(strIn.substr(0, iCount));

		posSeparator++;	// 越过分隔符
		iCount = (int)strIn.size() - (int)posSeparator;
		string strOther = strIn.substr(posSeparator, iCount);

		if(!strOther.empty())
		{
			devide_string_to_separator(strOther, strSeparator, vecStrOut);
		}
	}

	return true;
}

/* --------------------------------------------------------------------------
函数说明：Ip地址转换，数值型地址转成字串地址
传入参数：
	iIp			要转换的数值型Ip地址
	iIpAddrLen	pszIpAddr的长度
传出参数：
	pszIpAddr	转成后的字串
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int COften::ip_int_to_string(int iIp, char* pszIpAddr, int iIpAddrLen)
{
	if(!pszIpAddr)
		return 10;

	if(iIpAddrLen<=0)
		return 20;

	in_addr	addr;
	addr.S_un.S_addr = iIp;

	_snprintf(pszIpAddr, iIpAddrLen-1, "%s", inet_ntoa(addr));

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：Ip地址转换，字串地址转成数值型地址
传入参数：
	pszIpAddr	要转换的字串地址
	iIpAddrLen	pszIpAddr的长度
传出参数：
	iIp			转换后的数值型Ip地址
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int COften::ip_string_to_int(const char* pszIpAddr, int& iIp)
{
	if(!pszIpAddr)
		return 10;

	in_addr ipAddr;
	ipAddr.S_un.S_addr = inet_addr(pszIpAddr); //将字符串形式的IP地址转换为按网络字节顺序的整形值
	iIp = ipAddr.S_un.S_addr;

	return 0;
}

// 输出信息
void COften::OutputInfo(const char *szInfo)
{
	string strOutputInfo(SetInfo("Info", szInfo));
	printf(strOutputInfo.c_str());
}

// 输出信息
void COften::Printf(long long iVal, bool bReturn)
{
	char szTmp[16];
	memset(szTmp, 0, sizeof(szTmp));

	if(bReturn)
		sprintf(szTmp, "%I64d\n", iVal);
	else
		sprintf(szTmp, "%I64d", iVal);

	printf(szTmp);
}

// 输出错误
void COften::OutputError(const char *szInfo)
{
	string strOutputInfo(SetInfo("Erro", szInfo));
	printf(strOutputInfo.c_str());
}

// 组合输出信息
string COften::SetInfo(const string szTitle, const string szInfo)
{
	string strOutputInfo = GetCurrentTime_str();
	strOutputInfo+="  ";
	strOutputInfo+=szTitle;
	strOutputInfo+="  ";
	strOutputInfo+=szInfo;
	strOutputInfo+="\n";

	return strOutputInfo;
}

// 格式化当前时间
string COften::GetCurrentTime_str()
{
#if 0	// 这种方式“月份”值是错的
	time_t t;
	time(&t);
	struct tm* pTm = localtime(&t);

	char szTime[32]={0};
	sprintf(szTime,"%02d月%02d日 %02d:%02d:%02d", pTm->tm_mon, pTm->tm_mday,pTm->tm_hour,pTm->tm_min,pTm->tm_sec);
	string strTimeFormat(szTime);
#else
	// 时间尽量用这个类，是跨平台的

	CEasyDataTime easy;
	easy.get_current_time();	// 获得电脑的当前时间

	#if 0	// 这样更简单，只是多了年份，字串长了一些
		string strTimeFormat = easy.get_datetime_string();
	#else	// 这样更灵活，可以取任意想要的元素，字串也短
		int iYear, iMon, iDay, iHour, iMin, iSec;
		easy.get_date_time(iYear, iMon, iDay, iHour, iMin, iSec);	// 获得日期时间值

		char szTime[32]={0};
		sprintf(szTime,"%02d月%02d日 %02d:%02d:%02d", iMon, iDay, iHour, iMin, iSec);

		string strTimeFormat(szTime);
	#endif

#endif

	return strTimeFormat;
}