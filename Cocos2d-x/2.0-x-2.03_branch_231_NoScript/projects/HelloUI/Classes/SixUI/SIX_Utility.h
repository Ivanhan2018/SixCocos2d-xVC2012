/*********************************************************
Name：多功能类
Desc：各种小玩意
Auth：Cool.Cat@2013-03-15
*********************************************************/
#pragma once

#include <cocos2d.h>
#include "TSingleton.h"
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#include <time.h>
#else
#include <sys/time.h>
typedef unsigned short	WORD;
typedef struct {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

// add by hxh
#define MAKEWORD(a, b)      ((unsigned short)(((unsigned char)(a)) | ((unsigned short)((unsigned char)(b))) << 8))
#define MAKELONG(a, b)      ((long)(((unsigned short)(a)) | ((unsigned int)((unsigned short)(b))) << 16))
#define LOWORD(l)           ((unsigned short)(l))
#define HIWORD(l)           ((unsigned short)(((unsigned int)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((unsigned char)(w))
#define HIBYTE(w)           ((unsigned char)(((unsigned short)(w) >> 8) & 0xFF))

#endif
#include "SIX_Typedef.h"

#include <platform\third_party\win32\iconv\iconv.h>

// 脚本中用MP很麻烦，包装下给脚本用好了
// Cool.Cat
class SIX_MP{
public:
	SIX_MP();
	~SIX_MP();
public:
	int size();
	void push_back(const char *val);
	void pop_back();
	const char *at(int idx);
private:
	MP *mp;
};

class SIX_Utility:public TSingleton<SIX_Utility>{
public:
	SIX_Utility();
	static SIX_Utility* GetInstance();
public:
	unsigned long REVE_DWORD(unsigned long x);
	unsigned long GetCurrentThreadId();
	static int RNDNUM(int min,int max);
	int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen);
	std::string U2G(const char *inbuf);
	std::string G2U(const char *inbuf);
	int Split(char *sp,char *src,MP *ptr,int SplitCount=0);
	int Split(char *sp,char *src,SIX_MP *ptr,int SplitCount=0);
	
	unsigned long GetTickCount();

	//void GetLocalTime(SYSTEMTIME st);

	void TimerStart();
	void TimerEnd();
	double GetMilliseconds();
	double GetGlobalSecond();
	double Fixed(double,int);
private:
	static SIX_Utility* m_pUtility;
#if defined(_WIN32)
	LARGE_INTEGER m_GlobalTimerStart;
	LARGE_INTEGER m_GlobalTimerEnd;
    LARGE_INTEGER m_start;
    LARGE_INTEGER m_end;
	double s_invFrequency;
#elif defined(__linux__) || defined (__APPLE__)
	timeval m_GlobalTimerStart;
	timeval m_GlobalTimerEnd;
    timeval m_start;
    timeval m_end;
#endif
};