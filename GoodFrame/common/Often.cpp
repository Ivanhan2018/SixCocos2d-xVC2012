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

// ��õ�ǰ���̵�·��
int COften::get_current_path(char* pszPath, int iPathLen)
{
	using namespace std ;
	char buf[256] = {0}; 

	GetModuleFileNameA(NULL,buf,sizeof(buf));

	string strTemp = buf;
	string::size_type  pos = 0;
	pos = strTemp.rfind('\\', strTemp.length());	// �� strTemp ��β����ʼ��ͷ������ָ�����ַ�

	string strPath = strTemp.substr(0, pos+1);	
	_snprintf(pszPath, iPathLen, "%s", strPath.c_str());

	return 0;
}

// ��õ�ǰ���̵�·��
int COften::get_current_path(string& strPath)
{
	using namespace std ;
	char buf[256] = {0}; 

	GetModuleFileNameA(NULL,buf,sizeof(buf));

	string strTemp = buf;
	string::size_type  pos = 0;
	pos = strTemp.rfind('\\', strTemp.length());	// �� strTemp ��β����ʼ��ͷ������ָ�����ַ�
	strPath = strTemp.substr(0, pos+1);	
	
	return 0;
}

// ��õ�ǰ���̵�·��
wstring COften::get_current_path()
{
	wchar_t buf[256] = {0}; 

	GetModuleFileNameW(NULL,buf,sizeof(buf));

	wstring strTemp = buf;
	wstring::size_type  pos;

	pos = strTemp.rfind('\\', strTemp.length());	// �� strTemp ��β����ʼ��ͷ������ָ�����ַ�

	wstring strPath = strTemp.substr(0, pos+1);	

	return strPath;
}

// ����Ŀ¼
int COften::create_dir(wchar_t* pszDirName, int iDirNameLen)
{
	if(!pszDirName || 0==iDirNameLen)
		return 10;	// Ŀ¼���ǿ�ֵ���߳��Ȳ���ȷ

	int iResult = 0;
	int iFlag = 0;
	DWORD dwError = 0;

	// iMode ֵ�ĺ��壺
	//	00 Existence only
	//	02  Write-only
	//	04 Read-only
	//	06 Read and write
	int iMode = 4;

	// �ж�Ŀ¼���ڷ�
	iFlag = _waccess(pszDirName, iMode);

	if(0==iFlag)	// ���ڸ�Ŀ¼
	{
		return 0;
	}	
	else	// û�и�Ŀ¼
	{
		iFlag = _wmkdir(pszDirName);
		if(0==iFlag)	// ������
		{
		}
		else	// ����ʧ��
		{
			dwError = GetLastError();
			iResult = 30;	// ����ʧ��
		}
	}

	return 0;
}

// ���ֽڶ���
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

// ���ֽڶ���
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

// ���ֽ��ִ�ת�ɶ��ֽ��ִ�
int COften::EasyWideCharToMultiByte(const wchar_t* wcsSource, int iSourceLen, string& strDest)
{
	int iReturn = 0;	// ����ֵ
	int iRes = 0;
	int iErr = 0;

	if(!wcsSource)
		return 10;	// ���ֽ��ִ��ǿյ�

	// ����Ҫ���ת���ĳ��ȣ��˳����Ѱ����˽����� \0 
	int iTranLen = WideCharToMultiByte(CP_OEMCP,NULL,wcsSource,-1,NULL,0,NULL,FALSE);
	char *szDest;
	szDest = new char[iTranLen+1];
	memset(szDest, 0, (iTranLen+1) * sizeof(char));
	
	if(!szDest)
		return 20;	// New �ִ�ʧ��

	if(0==iTranLen)	
		return 30;	// ���ֽ��ִ��ĳ���Ϊ 0

	if(iSourceLen > iTranLen)
		return 40;	// ��2��������������ֽ��ִ����ȣ��Ƿ�

	iRes = WideCharToMultiByte (CP_OEMCP, NULL, wcsSource, -1, szDest, iTranLen, NULL, FALSE);
	iErr = GetLastError();

	if(0==iRes)	// ת��ʧ��
		iReturn = 80;
	else
		strDest = szDest;

	delete []szDest;

	return iReturn;
}

// ���ֽ��ִ�ת�ɿ��ֽ��ִ�
int COften::EasyMultiByteToWideChar(const char* szSource, int iSourceLen, wstring& wcszDest)
{
	/*
	����ԭ�ͣ�
	int MultiByteToWideChar(
							UINT CodePage,
							DWORD dwFlags,        
							LPCSTR lpMultiByteStr,
							int cbMultiByte,      
							LPWSTR lpWideCharStr, 
							int cchWideChar       
							);

	����˵����
	1��CodePage
		ָ��Ҫת���ɵ��ַ�������ҳ�����������κ��Ѿ���װ�Ļ�ϵͳ�Դ����ַ�������ѡ�����´���ҳ��
		CP_ACP         //��ǰϵͳANSI����ҳ
		CP_MACCP       //��ǰϵͳMacintosh����ҳ
		CP_OEMCP       //��ǰϵͳOEM����ҳ��һ��ԭʼ�豸������Ӳ��ɨ����
		CP_SYMBOL      //Symbol����ҳ������Windows 2000���Ժ�汾
		CP_THREAD_ACP  //��ǰ�߳�ANSI����ҳ������Windows 2000���Ժ�汾
		CP_UTF7  //UTF-7�����ô�ֵʱlpDefaultChar��lpUsedDefaultChar������ΪNULL
		CP_UTF8  //UTF-8�����ô�ֵʱlpDefaultChar��lpUsedDefaultChar������ΪNULL

	2��dwFlags
		ָ���Ƿ�ת����Ԥ���ַ���ϳɵĿ��ַ����Կ����ַ��Ƿ�ʹ���������֣��Լ�����������Ч�ַ���
		MB_PRECOMPOSED //����ʹ��Ԥ���ַ������е���Ԥ���ַ�ʱ���Ͳ���ʹ�÷ֽ�Ļ��ַ��Ͳ�ռ�ռ��ַ�����Ϊ������

		Ĭ��ѡ����ܺ�MB_COMPOSITE����
		MB_COMPOSITE   //����ʹ�÷ֽ��ַ���������ʹ�û��ַ�+��ռ�ռ��ַ��ķ�ʽ
		MB_ERR_INVALID_CHARS //���ô�ѡ����������Ƿ��ַ���ʧ�ܲ����ش�����ERROR_NO_UNICODE_TRANSLATION������	�����Ƿ��ַ�
		MB_USEGLYPHCHARS //ʹ�������ַ���������ַ�

		3��lpMultiByteStr //Ҫת�����ַ���
		4��cbMultiByte    //Ҫת���ַ����ĳ��ȣ�-1��ʾת�����ַ�����β
		5��lpWideCharStr //����ת��������Ŀ��ַ����Ļ�����
		6��cchWideChar    //�����������С�����Ϊ0��lpMultiByteStr�������ԣ��������������軺������С����ʹ�� lpWideCharStr

	����ֵ��
		Ϊ0��ʾ����ʧ�ܣ���cchWideCharΪ0ʱ���������������軺������С
	*/

	int iReturn = 0;	// ����ֵ
	int iRes = 0;
	int iErr = 0;
	
	if(!szSource)
		return 10;	// ���ֽ��ִ�Ϊ��

	// ����Ҫ���ת���ĳ��ȣ��˳����Ѱ����˽����� \0 
	int iTranLen = MultiByteToWideChar(CP_ACP, 0, szSource, -1, NULL, 0);

	//if(iSourceLen < iTranLen)
	//	return 20;	// ���ֽ��ִ��ĳ��Ȳ���ȷ

	wchar_t* pWideChar = new wchar_t[iTranLen];	
	memset(pWideChar, 0, iTranLen * sizeof(wchar_t));

	if(!pWideChar)
		return 30;	// New ʧ��

	// ����������ת��
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

		iReturn = 80;	// ת������
	}
	else
	{
		wcszDest = pWideChar;
	}

	delete[] pWideChar;

	return iReturn;
}

// �ж�����Ч��ָ�룬��Ҫ���������˺������������ڸǺܶ౾���Խ��������
BOOL COften::is_valid_point(const VOID* pPointer)
{
    if( NULL == pPointer )
        return FALSE;	// ��ָ��

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
			return FALSE;	// ��ָ��
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
			return FALSE;	// ��ָ��
		}

	#endif

    return TRUE;	// ��ֵ
}

// ��һ���ַ����ָ����ָ�ɶ���ִ�
BOOL COften::devide_string_to_separator(const string &strIn, const string &strSeparator, vector<string> &vecStrOut)
{
	if(strIn.empty() || strSeparator.empty())
		return false;

	string::size_type posSeparator = strIn.find(strSeparator);

	if( string::npos == posSeparator)	// δ�ҵ��ָ���
	{
		vecStrOut.push_back(strIn);
		return true;
	}
	else	// �ҵ��ָ���
	{
		int iCount = (int)posSeparator;
		vecStrOut.push_back(strIn.substr(0, iCount));

		posSeparator++;	// Խ���ָ���
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
����˵����Ip��ַת������ֵ�͵�ַת���ִ���ַ
���������
	iIp			Ҫת������ֵ��Ip��ַ
	iIpAddrLen	pszIpAddr�ĳ���
����������
	pszIpAddr	ת�ɺ���ִ�
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
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
����˵����Ip��ַת�����ִ���ַת����ֵ�͵�ַ
���������
	pszIpAddr	Ҫת�����ִ���ַ
	iIpAddrLen	pszIpAddr�ĳ���
����������
	iIp			ת�������ֵ��Ip��ַ
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int COften::ip_string_to_int(const char* pszIpAddr, int& iIp)
{
	if(!pszIpAddr)
		return 10;

	in_addr ipAddr;
	ipAddr.S_un.S_addr = inet_addr(pszIpAddr); //���ַ�����ʽ��IP��ַת��Ϊ�������ֽ�˳�������ֵ
	iIp = ipAddr.S_un.S_addr;

	return 0;
}

// �����Ϣ
void COften::OutputInfo(const char *szInfo)
{
	string strOutputInfo(SetInfo("Info", szInfo));
	printf(strOutputInfo.c_str());
}

// �����Ϣ
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

// �������
void COften::OutputError(const char *szInfo)
{
	string strOutputInfo(SetInfo("Erro", szInfo));
	printf(strOutputInfo.c_str());
}

// ��������Ϣ
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

// ��ʽ����ǰʱ��
string COften::GetCurrentTime_str()
{
#if 0	// ���ַ�ʽ���·ݡ�ֵ�Ǵ��
	time_t t;
	time(&t);
	struct tm* pTm = localtime(&t);

	char szTime[32]={0};
	sprintf(szTime,"%02d��%02d�� %02d:%02d:%02d", pTm->tm_mon, pTm->tm_mday,pTm->tm_hour,pTm->tm_min,pTm->tm_sec);
	string strTimeFormat(szTime);
#else
	// ʱ�価��������࣬�ǿ�ƽ̨��

	CEasyDataTime easy;
	easy.get_current_time();	// ��õ��Եĵ�ǰʱ��

	#if 0	// �������򵥣�ֻ�Ƕ�����ݣ��ִ�����һЩ
		string strTimeFormat = easy.get_datetime_string();
	#else	// ������������ȡ������Ҫ��Ԫ�أ��ִ�Ҳ��
		int iYear, iMon, iDay, iHour, iMin, iSec;
		easy.get_date_time(iYear, iMon, iDay, iHour, iMin, iSec);	// �������ʱ��ֵ

		char szTime[32]={0};
		sprintf(szTime,"%02d��%02d�� %02d:%02d:%02d", iMon, iDay, iHour, iMin, iSec);

		string strTimeFormat(szTime);
	#endif

#endif

	return strTimeFormat;
}