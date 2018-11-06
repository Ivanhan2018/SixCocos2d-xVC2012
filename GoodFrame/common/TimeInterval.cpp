#include "TimeInterval.h"
#include "PublicHead.h"


CTimeInterval::CTimeInterval(bool bPrint, char* pszFunName)
{
	m_lEnterTime = m_lLeaveTime = ::GetTickCount64();	// 进入的时间

	m_bPrint = bPrint;		// 是否打印

	memset(m_szFunName, 0, sizeof(m_szFunName));
	if(pszFunName)
		_snprintf(m_szFunName, sizeof(m_szFunName), "%s", pszFunName);
}


CTimeInterval::~CTimeInterval(void)
{
	m_lLeaveTime = ::GetTickCount64();
	long long lInterval = m_lLeaveTime - m_lEnterTime;

	if(m_bPrint)
	{
		if(m_szFunName)
			printf("%s 函数，耗时 %I64d \n", m_szFunName, lInterval); 
		else
			printf("耗时 %I64d \n", lInterval); 
	}
}
