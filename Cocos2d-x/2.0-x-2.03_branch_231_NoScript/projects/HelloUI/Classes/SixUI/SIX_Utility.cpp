#include "SIX_Utility.h"

#ifdef WIN32
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
#endif

#include <math.h>

SIX_Utility *SIX_Utility::m_pUtility = 0;

SIX_MP::SIX_MP()
{
	mp = new MP();
}

SIX_MP::~SIX_MP()
{
	mp->clear();
#ifdef WIN32
	mp->swap(MP());
#endif
	CC_SAFE_DELETE(mp);
}

int SIX_MP::size()
{
	if (mp)
		return mp->size();
	return 0;
}

void SIX_MP::push_back(const char *val)
{
	if (mp)
		mp->push_back(val);
}

void SIX_MP::pop_back()
{
	if (mp)
		mp->pop_back();
}

const char *SIX_MP::at(int idx)
{
	if (mp)
		return mp->at(idx).c_str();
	return 0;
}

// ---------------------------------------
SIX_Utility *SIX_Utility::GetInstance()
{
    if (!m_pUtility)
        m_pUtility = new SIX_Utility();

    return m_pUtility;
}

SIX_Utility::SIX_Utility()
{
#if defined(_WIN32)
	srand((unsigned int)time(0));
	// 先取主频
	LARGE_INTEGER largeInteger;
	QueryPerformanceFrequency(&largeInteger);
	s_invFrequency = double(largeInteger.QuadPart);
	if (s_invFrequency > 0.0)
		s_invFrequency = 1000.0 / s_invFrequency;

	QueryPerformanceCounter(&m_GlobalTimerStart);
#elif defined(__linux__) || defined (__APPLE__)
	gettimeofday(&m_GlobalTimerStart,0);
#endif
}

unsigned long SIX_Utility::REVE_DWORD(unsigned long x)
{
	// 0x12345678 => 0x78563412
	return MAKELONG(MAKEWORD(HIBYTE(HIWORD(x)),LOBYTE(HIWORD(x))),MAKEWORD(HIBYTE(LOWORD(x)),LOBYTE(LOWORD(x))));
}

unsigned long SIX_Utility::GetCurrentThreadId()
{
#ifdef _WIN32
	return ::GetCurrentThreadId();
#else
	return pthread_self();
#endif
}

// 生成随机数
int SIX_Utility::RNDNUM(int min,int max)
{
	int rndnum = 0;

	rndnum = rand() % (max-min+1) + min;

	if (rndnum<min)
		rndnum=min;

	return rndnum;
};

int SIX_Utility::code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
    iconv_t cd;

    const char *temp = inbuf;

    const char **pin = &temp;

    char **pout = &outbuf;

    memset(outbuf,0,outlen);

    cd = iconv_open(to_charset,from_charset);

    if(cd==0) 
		return -1;

    if(iconv(cd,pin,&inlen,pout,&outlen)==-1) 
		return -1;

    iconv_close(cd);

    return 0;

}

/*UTF8转GB2312*/
std::string SIX_Utility::U2G(const char *inbuf)
{
	size_t inlen = strlen(inbuf);

	char * outbuf = new char[inlen * 2 + 2];

	std::string strRet;

	if(code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}

	delete [] outbuf;

	return strRet;
}

/*GB2312转UTF8*/
std::string SIX_Utility::G2U(const char *inbuf)
{
	size_t inlen = strlen(inbuf);

	char * outbuf = new char[inlen * 2 + 2];

	std::string strRet;

	if(code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}

	delete [] outbuf;

	return strRet;
}

int SIX_Utility::Split(char *sp,char *src,SIX_MP *ptr,int SplitCount)
{
	if (!ptr)
		return 0;

	MP *mp = new MP();
	int retv = Split(sp,src,mp,SplitCount);
	if (mp->size())
	{
		for (int i=0;i<mp->size();i++)
			ptr->push_back(mp->at(i).c_str());
	}

	mp->clear();
#ifdef WIN32
	mp->swap(MP());
#endif
	CC_SAFE_DELETE(mp);

	return retv;
}

int SIX_Utility::Split(char *sp,char *src,MP *ptr,int SplitCount)
{
	if (!ptr)
		return 0;

	int splen = strlen(sp);
	char *ss=src;
	char *p = ss;
	char *last = ss;

	int index =0;
	int pos = 0;

	string tmpbuff("");

	p=strstr(p,sp);

	while (p)
	{
		// 本轮找到sp的位置
		pos = p - last;

		tmpbuff.resize(pos,0);

		memcpy((void*)tmpbuff.c_str(),last,pos);

		ptr->push_back(tmpbuff.c_str());

		p+=splen;
		last = p;

		if (SplitCount>0 && index==SplitCount-1)
		{
			int lastlen = strlen(src) - (last - ss);
			tmpbuff.resize(lastlen,0);
			memcpy((void*)tmpbuff.c_str(),last,lastlen);
			ptr->push_back(tmpbuff.c_str());
			break;
		}

		p=strstr(p,sp);

		if (!p)
		{
			int lastlen = strlen(src) - (last - ss);
			tmpbuff.resize(lastlen,0);
			memcpy((void*)tmpbuff.c_str(),last,lastlen);
			ptr->push_back(tmpbuff.c_str());
		}
		index++;
	}

	index = ptr->size();

	return index;
}

unsigned long SIX_Utility::GetTickCount()
{
#ifdef WIN32
	return ::timeGetTime();
#else
	struct timeval tv; 
	gettimeofday(&tv,NULL);
	return tv.tv_usec / 1000;
#endif
}
/*
void SIX_Utility::GetLocalTime(SYSTEMTIME st)
{
#ifdef WIN32
	::GetLocalTime(&st);
#else
	struct timeval tv;
	gettimeofday (&tv , NULL);

	tm tm_now ;
	localtime_r(&tv.tv_sec,&tm_now);

	lpSystemTime->wYear = tm_now.tm_year+1900;
	lpSystemTime->wMonth = tm_now.tm_mon+1;
	lpSystemTime->wDay = tm_now.tm_mday;
	lpSystemTime->wDayOfWeek = (tm_now.tm_wday+1)%7;
	lpSystemTime->wHour =tm_now.tm_hour;
	lpSystemTime->wMinute = tm_now.tm_min;
	lpSystemTime->wSecond = tm_now.tm_sec;
	lpSystemTime->wMilliseconds = tv.tv_usec/1000;
#endif
}
*/

double SIX_Utility::Fixed(double n,int p)
{
	double x = pow(10.0,p);
#ifdef WIN32
	return ((_int64)(n*x+0.5))/x;
#else
	return ((long long)(n*x+0.5))/x;
#endif
}

// 定时器部分
#if defined(_WIN32) && !defined(SHP)

void SIX_Utility::TimerStart()
{
	QueryPerformanceCounter(&m_start);
}

void SIX_Utility::TimerEnd()
{
	QueryPerformanceCounter(&m_end);
}

double SIX_Utility::GetMilliseconds()
{
	return Fixed((s_invFrequency*(m_end.QuadPart-m_start.QuadPart)),4);
}

double SIX_Utility::GetGlobalSecond()
{
	QueryPerformanceCounter(&m_GlobalTimerEnd);
	// 保留小数点后4位
	return Fixed((s_invFrequency*(m_GlobalTimerEnd.QuadPart-m_GlobalTimerStart.QuadPart))/1000.0,4);
}

#elif defined(__linux__) || defined (__APPLE__)

#include <sys/time.h>

void SIX_Utility::TimerStart()
{
	gettimeofday(&m_start,0);
}

void SIX_Utility::TimerEnd()
{
	gettimeofday(&m_end,0);
}

double SIX_Utility::GetMilliseconds()
{
	return (m_end.tv_sec - m_start.tv_sec) * 1000 + m_end.tv_usec * 0.001f - m_start.tv_usec * 0.001f;
}

double SIX_Utility::GetGlobalSecond()
{
	return ((m_GlobalTimerEnd.tv_sec - m_GlobalTimerStart.tv_sec) * 1000 + m_GlobalTimerEnd.tv_usec * 0.001f - m_GlobalTimerStart.tv_usec * 0.001f) * 1000.0f;
}

#else

void SIX_Utility::TimerStart()
{
}

void SIX_Utility::TimerEnd()
{
}

double SIX_Utility::GetMilliseconds()
{
	return 0.0f;
}

double SIX_Utility::GetGlobalSecond()
{
	return 0.0f;
}

#endif