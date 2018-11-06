/*********************************************************
Name：多功能类
Desc：各种小玩意
Auth：Cool.Cat@2013-03-15
*********************************************************/
#pragma once

#include <cocos2d.h>
#include <GUI/CCControlExtension/CCControlExtensions.h>
#include <TSingleton.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#include <time.h>
#include <sys/timeb.h>
#else
#include <arpa/inet.h>
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
#endif
#include <SIX_Typedef.h>
#include <tinyxml/tinyxml.h>
#include <platform\third_party\win32\iconv\iconv.h>
#include <map>
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_XMLParser;

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

typedef map<string,HITBOX_MAP*> FHITBOX_MAP;
typedef FHITBOX_MAP::iterator FHITBOX_ITER;

class SIX_Utility:public TSingleton<SIX_Utility>{
public:
	SIX_Utility();
	~SIX_Utility();
	static SIX_Utility* GetInstance();
public:
	unsigned long REVE_DWORD(unsigned long x);
	unsigned long GetCurrentThreadId();
	int RNDNUM(int min,int max);
	int getIntPart(double x);
	int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen);
	string U2G(const char *inbuf);
	string G2U(const char *inbuf);
	wstring AnsiToUnicode(const char* buf);
	string UnicodeToAnsi(const wchar_t* buf);
	wstring Utf8ToUnicode(const char* buf);
	string UnicodeToUtf8(const wchar_t* buf);
	int Split(char *sp,char *src,MP *ptr,int SplitCount=0);
	int Split(char *sp,char *src,SIX_MP *ptr,int SplitCount=0);
	void replace(string &strBig,const string &strsrc,const string &strdst);

	// 已知一个坐标，一个角度，一个距离求另一个坐标
	CCPoint getAnotherCoordinate(CCPoint pt, float fAngle, int nDistance);

	int s2n(char s);

	static bool addSpriteFramesWithPlistAsync(CCString *pszPlist,CCObject *target,SEL_CallFuncO selector);

	int GetNumberLength(long long number);
	bool AddSpriteBatchNodeByNumber(CCSpriteBatchNode *pBatchNode,const char *file,int cell,float padding,int bitcount,unsigned int num);

	bool LoadHitBoxFromFile(const char *pccPath);
	//void ParseXML(SIX_XMLParser *pXML);
	void ParseXML(TiXmlElement *rootElement);
	HITBOX_MAP *GetHitBoxByFrameName(const char *frameName);
	void AddHitBox();
	void ReleaseHitBox();

	// 2D/3D纹理抗锯齿
	void FixedTexParameters(CCTexture2D *);

	string NTOA(long long);

	bool IsSceneRunning(CCNode *pUIScene,const char *SceneName);

	static CCControlButton *CreateButtonWithFrameName(const char *pszSpriteFrameName);
	static CCControlButton *CreateButtonWithFile(const char *file,CCRect rc,const char *text=0,const char *fontName="微软雅黑",int fontSize=12);
	static CCControlButton *CreateButtonWithFileCell(const char *file,int cell,bool Hor=true);
	static bool SplitSpriteWithCell(const char *file,CCScale9Sprite**,CCScale9Sprite**,CCScale9Sprite**,CCScale9Sprite**,float *cell_width,float *cell_height,int cell=4,bool IsHor=true);

	// action
	static CCAction *schedule(CCNode *node, SEL_CallFunc callback, float delay);
	static CCAction *schedule(CCNode *node, SEL_CallFuncN callback, float delay);

	static CCAction *performWithDelay(CCNode *node, SEL_CallFunc callback, float delay);
	static CCAction *performWithDelay(CCNode *node, SEL_CallFuncN callback, float delay);

	// AppBasePath
	const char *GetAppBasePath(const char *folder=0);
	
	// 获取1970到现在的毫秒
	unsigned long long GetTickCount();

	void GetLocalTime(LPSYSTEMTIME st);

	void TimerStart();
	void TimerEnd();
	double GetMilliseconds();
	double GetGlobalSecond();
	double Fixed(double,int);
	FHITBOX_MAP frameHBox;
private:
	static SIX_Utility* m_pUtility;
	SIX_XMLParser *pXML;
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