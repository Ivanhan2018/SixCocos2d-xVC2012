/********************************************************************
	created:	2013/01/24
	created:	10:12:2012   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef OFTEN_H
#define OFTEN_H

#include  <iostream>
#include <string.h>

#include <vector>
using std::vector;

using std::string;
using std::wstring;

// ���õĶ���
class __declspec(dllexport) COften
{
public:
	COften(void);
	~COften(void);
	
	// ��ȫɾ�� New �����Ķ���
	static void SafeDelete(BYTE*& p);

	/* --------------------------------------------------------------------------
	����˵���� ��õ�ǰ���̵�·�����Ƽ�ʹ��
	���������
		iPathLen	iPathLen����󳤶ȣ�Ҫ����������0
	����������
		pszPath ·��
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	ʹ������
		char szPath[256] = {0};
		int iRes = COften::get_current_path(szPath, sizeof(szPath)-1);
	--------------------------------------------------------------------------*/
	static int COften::get_current_path(char* pszPath, int iPathLen);

	// ��õ�ǰ���̵�·�����ڿͻ�����ʱ�������������һ�������ȹ�
	static int get_current_path(string& strPath);

	// ��õ�ǰ���̵�·����β����б���Ѿ�����
	static wstring get_current_path();

	/* --------------------------------------------------------------------------
	����˵��������Ŀ¼
	���������
		pszDir  Ŀ¼��ȫ��
		iLen	
	����������
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	Ŀ¼���ǿ�ֵ���߳��Ȳ���ȷ
			30	����Ŀ¼ʧ��
	--------------------------------------------------------------------------*/
	static int create_dir(wchar_t* pszDirName, int iDirNameLen);

	/* --------------------------------------------------------------------------
	����˵�������ֽڶ���
	���������
		iByteCount  ԭ�����ֽ�����
		iUpLimit	����ֵ������ֵӦ����4�ֽڶ�����ֵ
	����ֵ��
		���ֽڶ������ֽ�����
	--------------------------------------------------------------------------*/
	static int fn4ByteMade(int iByteCount, int iUpLimit=-1);	

	/* --------------------------------------------------------------------------
	����˵�������ֽڶ���
	���������
		iByteCount  ԭ�����ֽ�����
		iUpLimit	����ֵ������ֵӦ����8�ֽڶ�����ֵ������ -1 �����ж����ֵ
	����ֵ��
		���ֽڶ������ֽ�����
	--------------------------------------------------------------------------*/
	static int fn8ByteMade(int iByteCount, int iUpLimit=-1);	

	
	/* --------------------------------------------------------------------------
	����˵�������ֽ��ִ�ת�ɶ��ֽ��ִ�
	���������
		wcsSource	���ֽ��ִ�
		iSourceLen	���ֽ��ִ��ĳ���
	����������
		strDest	���ֽ��ִ�
	����ֵ��
		�ɹ��򷵻� 0�����򷵻ش�����:
			10 ���ֽ��ִ��ǿյ�
			20 New �ִ�ʧ��
			30 ���ֽ��ִ��ĳ���Ϊ 0
			40 ��2��������������ֽ��ִ����ȣ��Ƿ�
			80 ת��ʧ��
	--------------------------------------------------------------------------*/
	static int EasyWideCharToMultiByte(const wchar_t* wcsSource, int iSourceLen, string& strDest);

	/* --------------------------------------------------------------------------
	����˵�������ֽ��ִ�ת�ɿ��ֽ��ִ�
	���������pnt
		szSource	���ֽ��ִ�
		iSourceLen	���ֽ��ִ��ĳ���
	����������
		wcszDest	���ֽ��ִ�
	����ֵ��
		�ɹ��򷵻� 0�����򷵻ش�����
			10 ���ֽ��ִ�Ϊ��
			20 ���ֽ��ִ��ĳ��Ȳ���ȷ
			30 New ʧ��
			80 ת������
	--------------------------------------------------------------------------*/
	static int EasyMultiByteToWideChar(const char* szSource, int iSourceLen, wstring& wcszDest);

	/* --------------------------------------------------------------------------
	����˵�����ж�����Ч��ָ�룬��Ҫ���������˺������������ڸǺܶ౾���Խ��������
	���������
		pPointer	ָ��
	����ֵ��
		��Ч�ķ��� TRUE����ָ�뷵�� FALSE ��
	--------------------------------------------------------------------------*/
	static BOOL COften::is_valid_point(const VOID* pPointer);

	/* --------------------------------------------------------------------------
	����˵������һ���ַ����ָ����ָ�ɶ���ִ�
	���������
		strIn			Ҫ�ָ����ִ�
		strSeparator	�ָ���
	����������
		vecStrOut			�ѷֺõĶ���ִ�
	����ֵ��
		�ɹ��򷵻�true�����򷵻�false
	��ע��
		strIn ������������ʽ��
		_T("Bill Gate,����,����,����") 
		_T("Bill Gate,����,����,����,") 
	ʹ��˵����
		string strIn("Bill Gate,����2,����,����8");
		string strSeparator(",");
		vector<string> vecStrOut;

		COfften strFun;
		strFun.fnDivideStringBySeparator(strIn, strSeparator, vecStrOut);
	--------------------------------------------------------------------------*/
	static BOOL devide_string_to_separator(const string &strIn, const string &strSeparator, vector<string> &vecStrOut);

	// IP��ֵ�͵�ַת���ִ��͵�ַ
	static int ip_int_to_string(int iIp, char* pszIpAddr, int iIpAddrLen);

	// IP�ִ��͵�ַת����ֵ�͵�ַ
	static int ip_string_to_int(const char* pszIpAddr, int& iIp);

	// �����Ϣ
	static void OutputInfo(const char *szInfo);

	/* --------------------------------------------------------------------------
	����˵�������������Ϣ
	���������
		iVal	Ҫ���������
		bReturn	�Ƿ�س�
	-------------------------------------------------------------------------- */
	static void COften::Printf(long long iVal, bool bReturn=true);

	// �������
	static void OutputError(const char *szInfo);

	// ���������Ϣ
	static string SetInfo(const string szTitle, const string szInfo);

	// ��ʽ����ǰʱ��
	static string GetCurrentTime_str();
};

#endif
