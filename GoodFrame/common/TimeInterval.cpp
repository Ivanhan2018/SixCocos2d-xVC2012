#include "TimeInterval.h"
#include "PublicHead.h"


CTimeInterval::CTimeInterval(bool bPrint, char* pszFunName)
{
	m_lEnterTime = m_lLeaveTime = ::GetTickCount64();	// �����ʱ��

	m_bPrint = bPrint;		// �Ƿ��ӡ

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
			printf("%s ��������ʱ %I64d \n", m_szFunName, lInterval); 
		else
			printf("��ʱ %I64d \n", lInterval); 
	}
}
