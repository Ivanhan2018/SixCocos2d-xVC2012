/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include <Windows.h>
#include "platform/CCCommon.h"
#include "CCStdC.h"

NS_CC_BEGIN

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

void CCLog(const char * pszFormat, ...)
{
    char szBuf[MAX_LEN];
	sprintf(szBuf, "[cocos2d]");
	char *p = szBuf;
	int iLen = strlen(szBuf);
	p= p + iLen;

	// add timestamp
	// Cool.Cat
SYSTEMTIME st;
#ifdef _WIN32
	::GetLocalTime(&st);
#else
	struct timeval tv;
	gettimeofday (&tv , NULL);

	tm tm_now ;
	localtime_r(&tv.tv_sec,&tm_now);

	st.wYear = tm_now.tm_year+1900;
	st.wMonth = tm_now.tm_mon+1;
	st.wDay = tm_now.tm_mday;
	st.wDayOfWeek = (tm_now.tm_wday+1)%7;
	st.wHour =tm_now.tm_hour;
	st.wMinute = tm_now.tm_min;
	st.wSecond = tm_now.tm_sec;
	st.wMilliseconds = tv.tv_usec/1000;
#endif

	char timestamp[MAX_LEN] = {0};
	sprintf(timestamp,"[%02d-%02d %02d:%02d:%02d:%04d]",
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds);
	::strcat(p,timestamp);
	p = p + strlen(timestamp);

	iLen += strlen(timestamp);
	//memcpy(p,timestamp,strlen(timestamp));

    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(p, MAX_LEN-iLen, pszFormat, ap);
    va_end(ap);

    WCHAR wszBuf[MAX_LEN] = {0};
    MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
    OutputDebugStringW(wszBuf);
    OutputDebugStringA("\n");

    WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
    printf("%s\n", szBuf);
}

void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
    MessageBoxA(NULL, pszMsg, pszTitle, MB_OK);
}

void CCLuaLog(const char *pszMsg)
{
    //int bufflen = MultiByteToWideChar(CP_UTF8, 0, pszMsg, -1, NULL, 0);
    //++bufflen;
    //WCHAR* buff = new WCHAR[bufflen];
    //memset(buff, 0, sizeof(WCHAR) * bufflen);
    //MultiByteToWideChar(CP_UTF8, 0, pszMsg, -1, buff, bufflen - 1);

    //OutputDebugStringW(buff);
    //OutputDebugStringA("\n");

    //puts(pszMsg);

	CCLog("[%s](%d) ==> %s",__FUNCTION__,__LINE__,pszMsg);
}

NS_CC_END

