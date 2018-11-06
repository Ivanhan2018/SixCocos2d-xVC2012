
/********************************************************************
	created:	2013/07/03
	created:	3:7:2013   20:14
	filename: 	E:\SixDivisions\GoodFRame\common\TimeGuard.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	TimeGuard
	file ext:	h
	author:		侯国江
	
	purpose:	用于进入指定函数时记住进入时间，离开函数时记住离开时间，并打印时间差，以观察此函数的耗时。
	            此类依赖 Windows 系统的 Windows.h 与 ws2_32.lib ，不能跨平台

*********************************************************************/

#ifndef TIME_GUARD_H
#define TIME_GUARD_H

class CTimeGuard
{
public:
	enum{ FUN_NAME_LEN=128,	};
public:

	/* --------------------------------------------------------------------------
	函数说明：
	传入参数：
		bDisplayWhenLeave	离开函数时是否列印
		pszFunName			进入函数的函数名
	--------------------------------------------------------------------------*/
	CTimeGuard(char* pszFunName, bool bDisplayWhenLeave=true);
	~CTimeGuard(void);

private:
	char m_szFunName[FUN_NAME_LEN];
	bool m_bDisplayWhenLeave;

	long long m_lEnterTime;	// 进入时间
	long long m_lLeaveTime;	// 离开时间
	long long m_lInterval;	// 时间差

};

#endif