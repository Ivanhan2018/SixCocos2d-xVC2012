/********************************************************************
	created:	2013/08/31
	created:	31:8:2013   18:52
	filename: 	E:\SixDivisions\GoodFRame\common\TimeInterval.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	TimeInterval
	file ext:	h
	author:		�����
	
	purpose:	ʱ����
*********************************************************************/


#ifndef TIME_INTERVAL_H
#define TIME_INTERVAL_H

// ʱ����
class __declspec(dllexport) CTimeInterval
{
public:
	CTimeInterval(bool bPrint=true, char* pszFunName="");
	~CTimeInterval(void);

private:
	long long m_lEnterTime;	// �����ʱ��
	long long m_lLeaveTime;	// �뿪��ʱ��
	bool	  m_bPrint;		// �Ƿ��ӡ

	char m_szFunName[128];
};

#endif
