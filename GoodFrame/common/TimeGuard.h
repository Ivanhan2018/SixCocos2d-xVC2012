
/********************************************************************
	created:	2013/07/03
	created:	3:7:2013   20:14
	filename: 	E:\SixDivisions\GoodFRame\common\TimeGuard.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	TimeGuard
	file ext:	h
	author:		�����
	
	purpose:	���ڽ���ָ������ʱ��ס����ʱ�䣬�뿪����ʱ��ס�뿪ʱ�䣬����ӡʱ���Թ۲�˺����ĺ�ʱ��
	            �������� Windows ϵͳ�� Windows.h �� ws2_32.lib �����ܿ�ƽ̨

*********************************************************************/

#ifndef TIME_GUARD_H
#define TIME_GUARD_H

class CTimeGuard
{
public:
	enum{ FUN_NAME_LEN=128,	};
public:

	/* --------------------------------------------------------------------------
	����˵����
	���������
		bDisplayWhenLeave	�뿪����ʱ�Ƿ���ӡ
		pszFunName			���뺯���ĺ�����
	--------------------------------------------------------------------------*/
	CTimeGuard(char* pszFunName, bool bDisplayWhenLeave=true);
	~CTimeGuard(void);

private:
	char m_szFunName[FUN_NAME_LEN];
	bool m_bDisplayWhenLeave;

	long long m_lEnterTime;	// ����ʱ��
	long long m_lLeaveTime;	// �뿪ʱ��
	long long m_lInterval;	// ʱ���

};

#endif