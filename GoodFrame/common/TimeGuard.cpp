//#include "StdAfx.h"
#include "TimeGuard.h"

#include "Windows.h"
//#pragma comment(lib, "Kernel32.lib") 
#pragma comment(lib,"ws2_32.lib")

#include <strsafe.h>

CTimeGuard::CTimeGuard(char* pszFunName, bool bDisplayWhenLeave)
{
	memset(m_szFunName, 0, sizeof(m_szFunName)); 

	m_bDisplayWhenLeave = bDisplayWhenLeave;
	m_lEnterTime = ::GetTickCount64();	// 进入时间
	m_lLeaveTime = 0;	// 离开时间

	if(pszFunName)
	{
		_snprintf(m_szFunName, sizeof(m_szFunName), "%s", pszFunName);
	}
}


CTimeGuard::~CTimeGuard(void)
{
	m_lLeaveTime = ::GetTickCount64();	// 离开时间

	m_lInterval = m_lLeaveTime - m_lEnterTime;

	if(m_bDisplayWhenLeave)
	{
		printf_s("消耗时间%I64d, 函数名%s", m_lInterval, m_szFunName);
	}


}
