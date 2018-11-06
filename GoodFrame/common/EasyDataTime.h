
/********************************************************************
	created:	2013/03/08
	created:	8:3:2013   13:29
	filename: 	E:\SVN_2013\GoodFrame\common\EasyDataTime.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	EasyDataTime
	file ext:	h
	author:		侯国江
	
	purpose:	之所以不用 WINDOWS API 的日期时间函数如 SYSTEM 等，是因为今后在手机上开发就
	            没有 WINDOWS API 函数库啦。这样的纯 C++ 模块可以减少移植到手机上的压力。
*********************************************************************/


#ifndef EASY_DATE_H
#define EASY_DATE_H

#include <assert.h>
#include <time.h>
#include <memory.h>

#include <string>
using std::string;

#ifdef WIN32
	struct __declspec(dllexport) EASY_DATA_TIME
#else
	struct EASY_DATA_TIME
#endif
{
	EASY_DATA_TIME(){ memset(this, 0, sizeof(*this));  }

	int iYear;
	int iMon;
	int iDay;
	int iHour; 
	int iMin; 
	int iSec;
};

// 简易的日期时间
#ifdef WIN32
	class __declspec(dllexport) CEasyDataTime
#else
	class CEasyDataTime
#endif
{
public:
	CEasyDataTime(void);
	~CEasyDataTime(void);

	/* --------------------------------------------------------------------------
	函数说明：前时间至1970年1月1日的秒差值
	返回值：
		差距值，以秒为单位
	--------------------------------------------------------------------------*/
	static long long get_current_time_diff_second_from_1970();

	/* --------------------------------------------------------------------------
	函数说明：当前时间至1970年1月1日的毫秒差值
	返回值：
		差距值，以毫秒为单位
	--------------------------------------------------------------------------*/
	static long long get_current_time_diff_millitm_from_1970();

	/* --------------------------------------------------------------------------
	函数说明：设置时间
	传入参数：
		dt	EASY_DATA_TIME 结构
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pTm 是空值，还未赋值
	--------------------------------------------------------------------------*/
	int set_date_time(const EASY_DATA_TIME& dt);

	/* --------------------------------------------------------------------------
	函数说明：设置时间
	传入参数：
		iYear	年，其值等于实际年份减去1900
		iMon	月，从一月开始，0代表一月，取值区间为[0,11]
		iDay	日，一个月中的日期 - 取值区间为[1,31]
		iHour	时，取值区间为[0,23]
		iMin	分，取值区间为[0,59]
		iSec	秒，取值区间为[0,59]
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int set_date_time(int iYear, int iMon, int iDay, int iHour=0, int iMin=0, int iSec=0);

	/* --------------------------------------------------------------------------
	函数说明：获得日期时间值
	传出参数：
		dt	EASY_DATA_TIME 结构
	返回值：
		成功则返回 0，失败返回错误码如下：
			 10	pTm 是空值，还未赋值
	--------------------------------------------------------------------------*/
	int get_date_time(EASY_DATA_TIME& dt);

	/* --------------------------------------------------------------------------
	函数说明：获得日期时间值
	传出参数：
		iYear	年，其值等于实际年份减去1900
		iMon	月，从一月开始，0代表一月，取值区间为[0,11]
		iDay	日，一个月中的日期 - 取值区间为[1,31]
		iHour	时，取值区间为[0,23]
		iMin	分，取值区间为[0,59]
		iSec	秒，取值区间为[0,59]
	返回值：
		成功则返回 0，失败返回错误码如下：
			 10	pTm 是空值，还未赋值
	--------------------------------------------------------------------------*/
	int get_date_time(int& iYear, int& iMon, int& iDay, int& iHour, int& iMin, int& iSec);

	/* --------------------------------------------------------------------------
	函数说明：获得电脑的当前时间
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	_localtime64_s 执行失败
	--------------------------------------------------------------------------*/
	int get_current_time();

	/* --------------------------------------------------------------------------
	函数说明：日期时间比较
	传入参数：
		dt	日期时间 
		传出参数：
			lDiff 单位是秒。正数表示 dt 的时间靠前（早一些），负数表示 dt 的时间靠后（晚一些），0 表示两个时间相等。
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int compare(const CEasyDataTime& dt, long long& lDiff);

	// 获得电脑的当前日期时间的字串
	string get_datetime_string();

private:
	struct tm	m_Tm;
	__time64_t	TimeT;	// 自1970年1月1日以来失去时间的秒数
};

#endif