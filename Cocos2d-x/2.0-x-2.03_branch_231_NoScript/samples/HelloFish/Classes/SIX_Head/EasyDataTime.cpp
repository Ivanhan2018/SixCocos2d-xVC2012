
#include "EasyDataTime.h"
#include <sys/timeb.h>  

CEasyDataTime::CEasyDataTime(void)
{
}


CEasyDataTime::~CEasyDataTime(void)
{
}

/* --------------------------------------------------------------------------
函数说明：日期时间比较
传入参数：
	dt	日期时间 
	传出参数：
		lDiff 单位是秒。正数表示 dt 的时间靠前（早一些），负数表示 dt 的时间靠后（晚一些），0 表示两个时间相等。
返回值：
	成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CEasyDataTime::compare(const CEasyDataTime& dt, long long& lDiff)
{
	double dDiff = _difftime64(TimeT, dt.TimeT);

	lDiff = static_cast<long long>(dDiff);

	return 0;
}

// 设置时间
int CEasyDataTime::set_date_time(int iYear, int iMon, int iDay, int iHour, int iMin, int iSec)
{
	m_Tm.tm_year = iYear - 1900;
	m_Tm.tm_mon = iMon-1;
	m_Tm.tm_mday = iDay;
	m_Tm.tm_hour = iHour;
	m_Tm.tm_min = iMin;
	m_Tm.tm_sec = iSec;
	
	// 将时间转换为自1970年1月1日以来失去时间的秒数
	// 发生错误是返回-1.
	long long iRes = TimeT = _mktime64(&m_Tm);
	if(-1==iRes)
		return 10; // _mktime64 错误，看看形参的数据是否非法

	return 0;
}

// 设置时间
int CEasyDataTime::set_date_time(const EASY_DATA_TIME& dt)
{
	m_Tm.tm_year = dt.iYear - 1900;
	m_Tm.tm_mon = dt.iMon-1;
	m_Tm.tm_mday = dt.iDay;
	m_Tm.tm_hour = dt.iHour;
	m_Tm.tm_min = dt.iMin;
	m_Tm.tm_sec = dt.iSec;

	// 将时间转换为自1970年1月1日以来失去时间的秒数
	// 发生错误是返回-1.
	long long  iRes = TimeT = _mktime64(&m_Tm);
	if(-1==iRes)
		return 10; // _mktime64 错误，看看形参的数据是否非法

	return 0;
}

// 获得日期时间值
int CEasyDataTime::get_date_time(EASY_DATA_TIME& dt)
{
	dt.iYear = m_Tm.tm_year + 1900;
	dt.iMon = m_Tm.tm_mon + 1;
	dt.iDay = m_Tm.tm_mday;
	dt.iHour = m_Tm.tm_hour;
	dt.iMin = m_Tm.tm_min;
	dt.iSec = m_Tm.tm_sec;

	return 0;
}

// 获得日期时间值
int CEasyDataTime::get_date_time(int& iYear, int& iMon, int& iDay, int& iHour, int& iMin, int& iSec)
{
	iYear = m_Tm.tm_year + 1900;
	iMon = m_Tm.tm_mon + 1;
	iDay = m_Tm.tm_mday;
	iHour = m_Tm.tm_hour;
	iMin = m_Tm.tm_min;
	iSec = m_Tm.tm_sec;

	return 0;
}

// 
/* --------------------------------------------------------------------------
函数说明：获得电脑的当前日期时间
返回值：
	成功则返回 0，失败返回错误码如下：
		10	_localtime64_s 执行失败
--------------------------------------------------------------------------*/
int CEasyDataTime::get_current_time()
{
	TimeT = _time64(NULL);		// 自1970年1月1日以来失去时间的秒数

	errno_t err = _localtime64_s(&m_Tm, &TimeT);

	assert(0==err);
	if(0!=err)
		return 10;

	struct tm *ptr;
	time_t lt;
	lt =time(NULL);
	ptr=localtime(&lt);

	// 测试用
	int iYear = m_Tm.tm_year + 1900;
	int iMonth = m_Tm.tm_mon + 1;

	return 0;
}

// 当前时间至1970年1月1日的秒差值
long long  CEasyDataTime::get_current_time_diff_second_from_1970()
{
	long long time_last;  
	time_last = _time64(NULL);     // 自1970年1月1日以来失去时间的秒数  

	return time_last;
}

// 当前时间至1970年1月1日的毫秒差值
long long  CEasyDataTime::get_current_time_diff_millitm_from_1970()
{
	struct __timeb64 t1;  
	_ftime64(&t1);  

	long long lMillitmDiffFrom1970 = t1.time * 1000 + t1.millitm;	// 毫秒差值

	return lMillitmDiffFrom1970;
}

// 获得电脑的当前日期时间的字串
string CEasyDataTime::get_datetime_string()
{
	char szTmp[32];
	memset(szTmp, 0, sizeof(szTmp));

	EASY_DATA_TIME dt;
	int iRes = get_date_time(dt);

	if(iRes>0)
		return "";

	_snprintf(szTmp, sizeof(szTmp)-1, "%04d-%02d-%02d %02d:%02d:%02d",
			dt.iYear,
			dt.iMon,
			dt.iDay,
			dt.iHour, 
			dt.iMin, 
			dt.iSec
			);

	return szTmp;
}