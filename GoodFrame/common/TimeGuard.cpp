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
	m_lEnterTime = ::GetTickCount64();	// ����ʱ��
	m_lLeaveTime = 0;	// �뿪ʱ��

	if(pszFunName)
	{
		_snprintf(m_szFunName, sizeof(m_szFunName), "%s", pszFunName);
	}
}


CTimeGuard::~CTimeGuard(void)
{
	m_lLeaveTime = ::GetTickCount64();	// �뿪ʱ��

	m_lInterval = m_lLeaveTime - m_lEnterTime;

	if(m_bDisplayWhenLeave)
	{
		printf_s("����ʱ��%I64d, ������%s", m_lInterval, m_szFunName);
	}


}
