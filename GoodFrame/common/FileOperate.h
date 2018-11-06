#ifndef FILE_OPERATE
#define FILE_OPERATE

// ����ǰĿ¼�µ� ��CreateFile��APE��⡷��CAtlFile ֻ�Ƿ�װ��API���ļ�����

/*
	���õĺ���
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