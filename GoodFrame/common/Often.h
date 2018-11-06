/********************************************************************
	created:	2013/01/24
	created:	10:12:2012   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		侯国江
	
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

// 常用的东西
class __declspec(dllexport) COften
{
public:
	COften(void);
	~COften(void);
	
	// 安全删除 New 出来的东西
	static void SafeDelete(BYTE*& p);

	/* --------------------------------------------------------------------------
	函数说明： 获得当前进程的路径，推荐使用
	传入参数：
		iPathLen	iPathLen的最大长度，要减掉结束符0
	传出参数：
		pszPath 路径
	返回值：
		成功则返回 0，失败返回错误码如下：
	使用例程
		char szPath[256] = {0};
		int iRes = COften::get_current_path(szPath, sizeof(szPath)-1);
	--------------------------------------------------------------------------*/
	static int COften::get_current_path(char* pszPath, int iPathLen);

	// 获得当前进程的路径，在客户端有时会崩溃，不如上一个函数稳固
	static int get_current_path(string& strPath);

	// 获得当前进程的路径，尾部的斜杠已经有了
	static wstring get_current_path();

	/* --------------------------------------------------------------------------
	函数说明：创建目录
	传入参数：
		pszDir  目录的全名
		iLen	
	传出参数：
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	目录名是空值或者长度不正确
			30	创建目录失败
	--------------------------------------------------------------------------*/
	static int create_dir(wchar_t* pszDirName, int iDirNameLen);

	/* --------------------------------------------------------------------------
	函数说明：四字节对齐
	传入参数：
		iByteCount  原来的字节数量
		iUpLimit	上限值，上限值应该是4字节对齐后的值
	返回值：
		四字节对齐后的字节数量
	--------------------------------------------------------------------------*/
	static int fn4ByteMade(int iByteCount, int iUpLimit=-1);	

	/* --------------------------------------------------------------------------
	函数说明：八字节对齐
	传入参数：
		iByteCount  原来的字节数量
		iUpLimit	上限值，上限值应该是8字节对齐后的值，若是 -1 则不用判断这个值
	返回值：
		八字节对齐后的字节数量
	--------------------------------------------------------------------------*/
	static int fn8ByteMade(int iByteCount, int iUpLimit=-1);	

	
	/* --------------------------------------------------------------------------
	函数说明：宽字节字串转成多字节字串
	传入参数：
		wcsSource	宽字节字串
		iSourceLen	宽字节字串的长度
	传出参数：
		strDest	多字节字串
	返回值：
		成功则返回 0，否则返回错误码:
			10 宽字节字串是空的
			20 New 字串失败
			30 宽字节字串的长度为 0
			40 第2个传入参数（宽字节字串长度）非法
			80 转换失败
	--------------------------------------------------------------------------*/
	static int EasyWideCharToMultiByte(const wchar_t* wcsSource, int iSourceLen, string& strDest);

	/* --------------------------------------------------------------------------
	函数说明：多字节字串转成宽字节字串
	传入参数：pnt
		szSource	多字节字串
		iSourceLen	多字节字串的长度
	传出参数：
		wcszDest	宽字节字串
	返回值：
		成功则返回 0，否则返回错误码
			10 多字节字串为空
			20 多字节字串的长度不正确
			30 New 失败
			80 转换错误
	--------------------------------------------------------------------------*/
	static int EasyMultiByteToWideChar(const char* szSource, int iSourceLen, wstring& wcszDest);

	/* --------------------------------------------------------------------------
	函数说明：判断是有效的指针，不要过于依赖此函数，这样会掩盖很多本可以解决的问题
	传入参数：
		pPointer	指针
	返回值：
		有效的返回 TRUE，空指针返回 FALSE 。
	--------------------------------------------------------------------------*/
	static BOOL COften::is_valid_point(const VOID* pPointer);

	/* --------------------------------------------------------------------------
	函数说明：将一串字符按分隔符分割成多段字串
	传入参数：
		strIn			要分隔的字串
		strSeparator	分隔符
	传出参数：
		vecStrOut			已分好的多段字串
	返回值：
		成功则返回true，否则返回false
	备注：
		strIn 可以是下列形式：
		_T("Bill Gate,李四,王五,赵六") 
		_T("Bill Gate,李四,王五,赵六,") 
	使用说明：
		string strIn("Bill Gate,李四2,王五,赵六8");
		string strSeparator(",");
		vector<string> vecStrOut;

		COfften strFun;
		strFun.fnDivideStringBySeparator(strIn, strSeparator, vecStrOut);
	--------------------------------------------------------------------------*/
	static BOOL devide_string_to_separator(const string &strIn, const string &strSeparator, vector<string> &vecStrOut);

	// IP数值型地址转成字串型地址
	static int ip_int_to_string(int iIp, char* pszIpAddr, int iIpAddrLen);

	// IP字串型地址转成数值型地址
	static int ip_string_to_int(const char* pszIpAddr, int& iIp);

	// 输出信息
	static void OutputInfo(const char *szInfo);

	/* --------------------------------------------------------------------------
	函数说明：输出数字信息
	传入参数：
		iVal	要输出的数字
		bReturn	是否回车
	-------------------------------------------------------------------------- */
	static void COften::Printf(long long iVal, bool bReturn=true);

	// 输出错误
	static void OutputError(const char *szInfo);

	// 设置输出信息
	static string SetInfo(const string szTitle, const string szInfo);

	// 格式化当前时间
	static string GetCurrentTime_str();
};

#endif
