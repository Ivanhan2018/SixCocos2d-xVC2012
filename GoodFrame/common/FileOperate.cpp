//#include "stdafx.h"
#include "./PublicHead.h"
#include ".\FileOperate.h"

CFileOperate::CFileOperate(void)
{
}

CFileOperate::~CFileOperate(void)
{
}

/* --------------------------------------------------------------------------
函数说明：
传入参数：
	szPathFile		要读出文件的路径及名称
	iBufLen			pBuf 的长度
	iWantReadSize	希望读出的长度，若为0则默认为读出整个文件的长度
传出参数：
	pBuf			读出的内容
	dwRealReadSize	真实读出的长度
	iFileSize		读出的文件的长度

返回值：
    成功则返回 0，否则返回错误码如下：
		10	pBuffer		为空值
		20	szPathFile	为空值
		50	打开文件失败，该文件存在否？
		60  读文件失败，ReadFile 函数的参数设置正确否？
		70  读出的长度超出了 pBuf 的长度，此错误不会造成内存泄漏，因为还没有开始读文件
--------------------------------------------------------------------------*/
int CFileOperate::read_file(TCHAR* szPathFile, BYTE* pBuf, int iBufLen, DWORD&	dwRealReadSize, int& iFileSize, int iWantReadSize)
{
	if(!pBuf)
		return 10;

	if(!szPathFile)
		return 20;
	
	int		iReturnValue = 0;
	HANDLE	hFile = NULL;	
	BOOL	bFlag = false;

	dwRealReadSize = 0;		// 真实读出的长度
	iFileSize = 0;			// 文件的长度
	memset(pBuf, 0, iBufLen);

	__try	// 这种方式不支持 CString 这样的类对象
	{
		hFile = (HANDLE)CreateFile(
			szPathFile, 
			GENERIC_READ, 
			FILE_SHARE_READ, 
			NULL, 
			OPEN_EXISTING, 
			NULL, 
			NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			hFile = NULL;
			iReturnValue = 50;
			__leave;
		}

		iFileSize = GetFileSize(hFile, NULL);	// 获得文件的长度

		int iLen = 0;	// 要读出的长度
		if(iWantReadSize>0)
			iLen = min(iWantReadSize, iFileSize);	
		else
			iLen = iFileSize;

		if(iLen > iBufLen)
		{
			iReturnValue = 60;
			__leave;
		}

		bFlag = ReadFile(hFile, pBuf, iLen, &dwRealReadSize, NULL);
		if(!bFlag)
		{
			iReturnValue = 70;
			__leave;
		}
	}
	__finally
	{
		if(hFile)
			CloseHandle(hFile);

	}

	return iReturnValue;
}

/* --------------------------------------------------------------------------
函数说明：
传入参数：
	szPathFile		要读出文件的路径及名称
	iSeekPos		文件指针移动的位置
	iBufLen			pBuf 的长度
	dwMoveMethod	FILE_BEGIN、FILE_CURRENT、FILE_END ，见 MSDN 中的 SetFilePointer 函数
	iWantReadSize	希望读出的长度，若为0则默认为读出整个文件的长度
传出参数：
	pBuf			读出的内容
	dwRealReadSize	真实读出的长度
	iFileSize		读出的文件的长度

返回值：
    成功则返回 0，否则返回错误码如下：
		10	pBuffer		为空值
		20	szPathFile	为空值
		50	打开文件失败，该文件存在否？
		60  读文件失败，ReadFile 函数的参数设置正确否？
		70  读出的长度超出了 pBuf 的长度，此错误不会造成内存泄漏，因为还没有开始读文件
		90  iSeekPos 指的位置超出了文件的长度
--------------------------------------------------------------------------*/
int CFileOperate::read_file_ex(TCHAR* szPathFile, int iSeekPos, BYTE* pBuf, int iBufLen, DWORD&	dwRealReadSize, int& iFileSize, DWORD dwMoveMethod, int iWantReadSize)
{
	if(!pBuf)
		return 10;

	if(!szPathFile)
		return 20;
	
	int		iReturnValue = 0;
	HANDLE	hFile = NULL;	
	BOOL	bFlag = false;

	dwRealReadSize = 0;		// 真实读出的长度
	iFileSize = 0;			// 文件的长度
	memset(pBuf, 0, iBufLen);

	//CAtlString strTmp;	// 有此句则 __try 编译通不过
	//CString    strTmp;	// 有此句则 __try 编译通不过

	__try	// 这种方式不支持 CString 这样的类对象
	{
		hFile = (HANDLE)CreateFile(
			szPathFile, 
			GENERIC_READ, 
			FILE_SHARE_READ, 
			NULL, 
			OPEN_EXISTING, 
			NULL, 
			NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			hFile = NULL;
			iReturnValue = 50;
			__leave;
		}

		iFileSize = GetFileSize(hFile, NULL);	// 获得文件的长度

		int iLen = 0;	// 要读出的长度
		if(iWantReadSize>0)
			min(iWantReadSize, iFileSize);	
		else
			iLen = iFileSize;

		if(iLen > iBufLen)
		{
			iReturnValue = 60;
			__leave;
		}

		if(iSeekPos >= iFileSize)
		{
			iReturnValue = 90;
			__leave;
		}

		seek(hFile, iSeekPos, dwMoveMethod);	// 移动指针		

		bFlag = ReadFile(hFile, pBuf, iLen, &dwRealReadSize, NULL);
		if(!bFlag)
		{
			iReturnValue = 70;
			__leave;
		}
	}
	__finally
	{
		if(hFile)
			CloseHandle(hFile);

	}

	return iReturnValue;
}

/* --------------------------------------------------------------------------
函数说明：
传入参数：
	szPathFile		要写入文件的路径及名称
	iBufLen			写入的的长度
传出参数：
	pBuf			写入的内容
	dwRealWriteSize	真实写入的长度
返回值：
    成功则返回 0，否则返回错误码如下：
		10	pBuffer		为空值
		20	szPathFile	为空值
		50	打开文件失败，CreateFile 函数的参数设置正确否？
		60  定入失败
--------------------------------------------------------------------------*/
int CFileOperate::write_file(TCHAR* szPathFile, BYTE* pBuf, int iBufLen, DWORD& dwRealWriteSize)
{
	if(!pBuf)
		return 10;

	if(!szPathFile)
		return 20;
	
	int		iReturnValue = 0;
	HANDLE	hFile = NULL;	
	BOOL	bFlag = false;

	dwRealWriteSize = 0;		// 真实写入的长度

	__try	// 这种方式不支持 CString 这样的类对象
	{
		hFile = (HANDLE)CreateFile(
			szPathFile, 
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, 
			NULL, 
			CREATE_ALWAYS, 
			NULL, 
			NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			hFile = NULL;
			iReturnValue = 50;
			__leave;
		}

		bFlag = WriteFile(hFile, pBuf, iBufLen, &dwRealWriteSize, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			hFile = NULL;
			iReturnValue = 60;
			__leave;
		}
	}
	__finally
	{
		if(hFile)
			CloseHandle(hFile);

	}

	return iReturnValue;
}

/* --------------------------------------------------------------------------
函数说明：
传入参数：
	szPathFile		要写入文件的路径及名称
	iBufLen			写入的的长度
传出参数：
	pBuf			写入的内容
	dwRealWriteSize	真实写入的长度
返回值：
    成功则返回 0，否则返回错误码如下：
		10	pBuffer		为空值
		20	szPathFile	为空值
		50	打开文件失败，CreateFile 函数的参数设置正确否？
		60  定入失败
		90  iSeekPos 指的位置超出了文件的长度 
--------------------------------------------------------------------------*/
int CFileOperate::insert_file_ex(TCHAR* szPathFile, int iSeekPos, BYTE* pBuf, int iBufLen, DWORD& dwRealWriteSize, DWORD dwMoveMethod)
{
	if(!pBuf)
		return 10;

	if(!szPathFile)
		return 20;
	
	int		iReturnValue = 0;
	HANDLE	hFile = NULL;	
	BOOL	bFlag = false;

	dwRealWriteSize = 0;		// 真实写入的长度

	//CAtlString strTmp;	// 有此句则 __try 编译通不过
	//CString    strTmp;	// 有此句则 __try 编译通不过

	__try	// 这种方式不支持 CString 这样的类对象
	{
		hFile = (HANDLE)CreateFile(
			szPathFile, 
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, 
			NULL, 
			OPEN_EXISTING, 
			NULL, 
			NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			hFile = NULL;
			iReturnValue = 50;
			__leave;
		}
		
		int iFileSize = GetFileSize(hFile, NULL);	// 获得文件的长度
		
		if(iSeekPos >= iFileSize)
		{
			iReturnValue = 90;
			__leave;
		}
		
		seek(hFile, iSeekPos, dwMoveMethod);
		
		bFlag = WriteFile(hFile, pBuf, iBufLen, &dwRealWriteSize, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			hFile = NULL;
			iReturnValue = 60;
			__leave;
		}
	}
	__finally
	{
		if(hFile)
			CloseHandle(hFile);

	}

	return iReturnValue;
}

/* --------------------------------------------------------------------------
函数说明：拷贝文件，很稳定、健壮，这种方式即使 szDstPathFile 被别人打开占用时也能成功
传入参数：
	szSrcPathFile		源文件的路径及名称
	szDstPathFile		目标文件的路径及名称
返回值：
    成功则返回 0，否则返回错误码如下：
		10	源文件的路径及名称为空
		20	目标文件的路径及名称为空
		30	源文件不存在
		40  源文件长度为零
		50  读源文件失败
		60  写目标文件失败
--------------------------------------------------------------------------*/
int CFileOperate::copy_file(TCHAR* szSrcPathFile, TCHAR* szDstPathFile)
{
	if(!szSrcPathFile)
		return 10;

	if(!szDstPathFile)
		return 20;

	int		iReturnValue = 0;

	BYTE*	pBuf = NULL;	
	int		iBufLen = 0;

	DWORD	dwRealReadSize = 0;		// 真实读出的长度
	DWORD	dwRealWriteSize = 0;	// 真实写入的长度
	int		iFileSize = 0;			// 文件的长度
	int iRes = 0;


	//CAtlString strTmp;	// 有此句则 __try 编译通不过
	//CString    strTmp;	// 有此句则 __try 编译通不过

	__try	// 这种方式不支持 CString 这样的类对象
	{
		iRes = is_exist_file(szSrcPathFile, iFileSize);

		if(0 == iRes)
		{
			if(0==iFileSize)
			{
				iReturnValue = 40;
				__leave;
			}

			pBuf = new BYTE[iFileSize];
			memset(pBuf, 0, iFileSize);
			iBufLen = iFileSize;

			iRes = CFileOperate::read_file(szSrcPathFile, pBuf, iBufLen, dwRealReadSize, iFileSize);

			if(0 == iRes)
			{
				iRes = CFileOperate::write_file(szDstPathFile, pBuf, dwRealReadSize, dwRealWriteSize);
				if(iRes>0)
				{
					iReturnValue = 60;
					__leave;
				}
			}
			else
			{
				iReturnValue = 50;
				__leave;
			}
		}
		else	// 源文件不存在
		{
			iReturnValue = 30;
			__leave;
		}

	}
	__finally
	{
		if(pBuf)
			delete[] pBuf;
	}

	return iReturnValue;
}

/* --------------------------------------------------------------------------
函数说明：文件改名
传入参数：
	szSrcPathFile		源文件的路径及名称
	szDstPathFile		目标文件的路径及名称
返回值：
    成功则返回 0，否则返回错误码如下：
		10	源文件的路径及名称为空
		20	目标文件的路径及名称为空
		30	源文件不存在
		40  源文件长度为零
		50  读源文件失败
		60  写目标文件失败
		90  删除源文件失败，源文件很可能被某个进程打开着
--------------------------------------------------------------------------*/
int CFileOperate::rename_file(TCHAR* szSrcPathFile, TCHAR* szDstPathFile)
{
	int		iReturnValue = 0;
	int		iFlag = 0;

	iReturnValue = copy_file(szSrcPathFile, szDstPathFile);
	if(0 == iReturnValue)
	{
		if(!DeleteFile(szSrcPathFile))	// 删除源文件，但并不知道删除的结果
		{
			iReturnValue = 90;	// 删除源文件失败
		}
	}

	return iReturnValue;
}

/* --------------------------------------------------------------------------
函数说明：文件存在否
传入参数：
	szPathFile		文件的路径及名称
	iFileSize		文件的长度
返回值：
    存在则返回 0，否则返回错误码如下：
		10	文件名为空
		50	文件不存在
--------------------------------------------------------------------------*/
int CFileOperate::is_exist_file(TCHAR* szPathFile, int& iFileSize)
{
	int	iReturnValue = 0;
	
	if(!szPathFile)
		return 10;
	
	HANDLE	hFile = NULL;	
	BOOL	bFlag = false;
	iFileSize = 0;
	
	hFile = (HANDLE)CreateFile(
		szPathFile, 
		GENERIC_READ, 
		FILE_SHARE_READ, 
		NULL, 
		OPEN_EXISTING, 
		NULL, 
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		hFile = NULL;
		iReturnValue = 50;
	}
	
	if(hFile)
	{
		iFileSize = GetFileSize(hFile, NULL);	// 获得文件的长度

		CloseHandle(hFile);
	}
	
	return iReturnValue;
}

__int64 CFileOperate::seek(HANDLE hFile, __int64 distance, DWORD MoveMethod)
{
	LARGE_INTEGER   li;

	li.QuadPart = distance;

	li.LowPart = SetFilePointer(hFile, li.LowPart, &li.HighPart, MoveMethod);

	if   (li.LowPart == INVALID_SET_FILE_POINTER   &&   GetLastError() != NO_ERROR)
	{
		li.QuadPart   =   -1;
	}

	return   li.QuadPart;
} 
