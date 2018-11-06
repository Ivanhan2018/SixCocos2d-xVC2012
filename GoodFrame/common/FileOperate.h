#ifndef FILE_OPERATE
#define FILE_OPERATE

// 见当前目录下的 《CreateFile等APE详解》，CAtlFile 只是封装了API的文件操作

/*
	常用的函数
	SetFilePointer
	CeSetFilePointer 
    SetEndOfFile

*/

class __declspec(dllexport) CFileOperate
{
public:
	CFileOperate(void);
	~CFileOperate(void);

	static int read_file(TCHAR* szPathFile, BYTE* pBuf, int iBufLen, DWORD&	dwRealReadSize, int& iFileSize, int iWantReadSize=0);
	static int read_file_ex(TCHAR* szPathFile, int iSeekPos, BYTE* pBuf, int iBufLen, DWORD&	dwRealReadSize, int& iFileSize, DWORD dwMoveMethod=FILE_BEGIN, int iWantReadSize=0);

	static int write_file(TCHAR* szPathFile, BYTE* pBuf, int iBufLen, DWORD& dwRealWriteSize);
	static int insert_file_ex(TCHAR* szPathFile, int iSeekPos, BYTE* pBuf, int iBufLen, DWORD& dwRealWriteSize, DWORD dwMoveMethod=FILE_BEGIN);

	static int is_exist_file(TCHAR* szPathFile, int& iFileSize);

	static int copy_file(TCHAR* szSrcPathFile, TCHAR* szDstPathFile);
	static int rename_file(TCHAR* szSrcPathFile, TCHAR* szDstPathFile);

	static __int64 seek(HANDLE hFile, __int64 distance, DWORD MoveMethod);
};

#endif