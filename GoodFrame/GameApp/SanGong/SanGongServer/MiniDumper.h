#pragma once
#ifdef WIN32
#include <windows.h>
#include <string>
using namespace std;

class CMiniDumper
{
public:

    CMiniDumper(bool bPromptUserForMiniDump=true);
    ~CMiniDumper(void);

	void SetUploadURL(char *PostURL);

    void setMiniDumpFileName(void);
    bool getImpersonationToken(HANDLE* phToken);
    BOOL enablePrivilege(LPCTSTR pszPriv, HANDLE hToken, TOKEN_PRIVILEGES* ptpOld);
    BOOL restorePrivilege(HANDLE hToken, TOKEN_PRIVILEGES* ptpOld);

private:

    static LONG WINAPI unhandledExceptionHandler(struct _EXCEPTION_POINTERS *pExceptionInfo);
    LONG writeMiniDump(_EXCEPTION_POINTERS *pExceptionInfo );

    _EXCEPTION_POINTERS *m_pExceptionInfo;
    TCHAR m_szMiniDumpPath[1024];
    TCHAR m_szAppPath[1024];
    TCHAR m_szAppBaseName[1024];
    bool m_bPromptUserForMiniDump;

    static CMiniDumper* s_pMiniDumper;
    static LPCRITICAL_SECTION s_pCriticalSection;

	string UploadUrl;
};
#endif