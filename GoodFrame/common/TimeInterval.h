/********************************************************************
	created:	2013/08/31
	created:	31:8:2013   18:52
	filename: 	E:\SixDivisions\GoodFRame\common\TimeInterval.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	TimeInterval
	file ext:	h
	author:		侯国江
	
	purpose:	时间间隔
*********************************************************************/


#ifndef TIME_INTERVAL_H
#define TIME_INTERVAL_H

// 时间间隔
class __declspec(dllexport) CTimeInterval
{
public:
	CTimeInterval(bool bPrint=true, char* pszFunName="");
	~CTimeInterval(void);

private:
	long long m_lEnterTime;	// 进入的时间
	long long m_lLeaveTime;	// 离开的时间
	bool	  m_bPrint;		// 是否打印

	char m_szFunName[128];
};

#endif
