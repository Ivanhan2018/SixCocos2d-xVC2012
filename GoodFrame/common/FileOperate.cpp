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
����˵����
���������
	szPathFile		Ҫ�����ļ���·��������
	iBufLen			pBuf �ĳ���
	iWantReadSize	ϣ�������ĳ��ȣ���Ϊ0��Ĭ��Ϊ���������ļ��ĳ���
����������
	pBuf			����������
	dwRealReadSize	��ʵ�����ĳ���
	iFileSize		�������ļ��ĳ���

����ֵ��
    �ɹ��򷵻� 0�����򷵻ش��������£�
		10	pBuffer		Ϊ��ֵ
		20	szPathFile	Ϊ��ֵ
		50	���ļ�ʧ�ܣ����ļ����ڷ�
		60  ���ļ�ʧ�ܣ�ReadFile �����Ĳ���������ȷ��
		70  �����ĳ��ȳ����� pBuf �ĳ��ȣ��˴��󲻻�����ڴ�й©����Ϊ��û�п�ʼ���ļ�
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

	dwRealReadSize = 0;		// ��ʵ�����ĳ���
	iFileSize = 0;			// �ļ��ĳ���
	memset(pBuf, 0, iBufLen);

	__try	// ���ַ�ʽ��֧�� CString �����������
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

		iFileSize = GetFileSize(hFile, NULL);	// ����ļ��ĳ���

		int iLen = 0;	// Ҫ�����ĳ���
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
����˵����
���������
	szPathFile		Ҫ�����ļ���·��������
	iSeekPos		�ļ�ָ���ƶ���λ��
	iBufLen			pBuf �ĳ���
	dwMoveMethod	FILE_BEGIN��FILE_CURRENT��FILE_END ���� MSDN �е� SetFilePointer ����
	iWantReadSize	ϣ�������ĳ��ȣ���Ϊ0��Ĭ��Ϊ���������ļ��ĳ���
����������
	pBuf			����������
	dwRealReadSize	��ʵ�����ĳ���
	iFileSize		�������ļ��ĳ���

����ֵ��
    �ɹ��򷵻� 0�����򷵻ش��������£�
		10	pBuffer		Ϊ��ֵ
		20	szPathFile	Ϊ��ֵ
		50	���ļ�ʧ�ܣ����ļ����ڷ�
		60  ���ļ�ʧ�ܣ�ReadFile �����Ĳ���������ȷ��
		70  �����ĳ��ȳ����� pBuf �ĳ��ȣ��˴��󲻻�����ڴ�й©����Ϊ��û�п�ʼ���ļ�
		90  iSeekPos ָ��λ�ó������ļ��ĳ���
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

	dwRealReadSize = 0;		// ��ʵ�����ĳ���
	iFileSize = 0;			// �ļ��ĳ���
	memset(pBuf, 0, iBufLen);

	//CAtlString strTmp;	// �д˾��� __try ����ͨ����
	//CString    strTmp;	// �д˾��� __try ����ͨ����

	__try	// ���ַ�ʽ��֧�� CString �����������
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

		iFileSize = GetFileSize(hFile, NULL);	// ����ļ��ĳ���

		int iLen = 0;	// Ҫ�����ĳ���
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

		seek(hFile, iSeekPos, dwMoveMethod);	// �ƶ�ָ��		

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
����˵����
���������
	szPathFile		Ҫд���ļ���·��������
	iBufLen			д��ĵĳ���
����������
	pBuf			д�������
	dwRealWriteSize	��ʵд��ĳ���
����ֵ��
    �ɹ��򷵻� 0�����򷵻ش��������£�
		10	pBuffer		Ϊ��ֵ
		20	szPathFile	Ϊ��ֵ
		50	���ļ�ʧ�ܣ�CreateFile �����Ĳ���������ȷ��
		60  ����ʧ��
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

	dwRealWriteSize = 0;		// ��ʵд��ĳ���

	__try	// ���ַ�ʽ��֧�� CString �����������
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
����˵����
���������
	szPathFile		Ҫд���ļ���·��������
	iBufLen			д��ĵĳ���
����������
	pBuf			д�������
	dwRealWriteSize	��ʵд��ĳ���
����ֵ��
    �ɹ��򷵻� 0�����򷵻ش��������£�
		10	pBuffer		Ϊ��ֵ
		20	szPathFile	Ϊ��ֵ
		50	���ļ�ʧ�ܣ�CreateFile �����Ĳ���������ȷ��
		60  ����ʧ��
		90  iSeekPos ָ��λ�ó������ļ��ĳ��� 
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

	dwRealWriteSize = 0;		// ��ʵд��ĳ���

	//CAtlString strTmp;	// �д˾��� __try ����ͨ����
	//CString    strTmp;	// �д˾��� __try ����ͨ����

	__try	// ���ַ�ʽ��֧�� CString �����������
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
		
		int iFileSize = GetFileSize(hFile, NULL);	// ����ļ��ĳ���
		
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
����˵���������ļ������ȶ�����׳�����ַ�ʽ��ʹ szDstPathFile �����˴�ռ��ʱҲ�ܳɹ�
���������
	szSrcPathFile		Դ�ļ���·��������
	szDstPathFile		Ŀ���ļ���·��������
����ֵ��
    �ɹ��򷵻� 0�����򷵻ش��������£�
		10	Դ�ļ���·��������Ϊ��
		20	Ŀ���ļ���·��������Ϊ��
		30	Դ�ļ�������
		40  Դ�ļ�����Ϊ��
		50  ��Դ�ļ�ʧ��
		60  дĿ���ļ�ʧ��
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

	DWORD	dwRealReadSize = 0;		// ��ʵ�����ĳ���
	DWORD	dwRealWriteSize = 0;	// ��ʵд��ĳ���
	int		iFileSize = 0;			// �ļ��ĳ���
	int iRes = 0;


	//CAtlString strTmp;	// �д˾��� __try ����ͨ����
	//CString    strTmp;	// �д˾��� __try ����ͨ����

	__try	// ���ַ�ʽ��֧�� CString �����������
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
		else	// Դ�ļ�������
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
����˵�����ļ�����
���������
	szSrcPathFile		Դ�ļ���·��������
	szDstPathFile		Ŀ���ļ���·��������
����ֵ��
    �ɹ��򷵻� 0�����򷵻ش��������£�
		10	Դ�ļ���·��������Ϊ��
		20	Ŀ���ļ���·��������Ϊ��
		30	Դ�ļ�������
		40  Դ�ļ�����Ϊ��
		50  ��Դ�ļ�ʧ��
		60  дĿ���ļ�ʧ��
		90  ɾ��Դ�ļ�ʧ�ܣ�Դ�ļ��ܿ��ܱ�ĳ�����̴���
--------------------------------------------------------------------------*/
int CFileOperate::rename_file(TCHAR* szSrcPathFile, TCHAR* szDstPathFile)
{
	int		iReturnValue = 0;
	int		iFlag = 0;

	iReturnValue = copy_file(szSrcPathFile, szDstPathFile);
	if(0 == iReturnValue)
	{
		if(!DeleteFile(szSrcPathFile))	// ɾ��Դ�ļ���������֪��ɾ���Ľ��
		{
			iReturnValue = 90;	// ɾ��Դ�ļ�ʧ��
		}
	}

	return iReturnValue;
}

/* --------------------------------------------------------------------------
����˵�����ļ����ڷ�
���������
	szPathFile		�ļ���·��������
	iFileSize		�ļ��ĳ���
����ֵ��
    �����򷵻� 0�����򷵻ش��������£�
		10	�ļ���Ϊ��
		50	�ļ�������
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
		iFileSize = GetFileSize(hFile, NULL);	// ����ļ��ĳ���

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
