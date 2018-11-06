
/********************************************************************
	created:	2013/02/19
	created:	20:2:2013   14:03
	filename: 	E:\SVN_2013\GoodFrame\common\CoreTimer.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	CoreTimer
	file ext:	h
	author:		�����
	
	purpose:	�ں˶�ʱ��
				Ͷ�ݵ�����ķ�ʽ������д���ĺô���
				1�������ö��߳�������ʱ���¼���������һ����ʱ iIDEvent ��ʱ����������¾ͻ�������Ķ�ʱ iIDEvent 
				2�������ʱ iIDEvent ͬʱ��Ӧʱ�������Բ���ִ��
*********************************************************************/

#ifndef CORE_TIMER_H
#define CORE_TIMER_H

#include "./ThreadGuard.h"
#include "./BasicLogic.h"

#include <list>
using std::list;

class CCoreTimer :	public CBasicLogic
//class CCoreTimer
{
public:
	friend class CCoreServer;

	struct SET_TIMER_PARAM
	{
		SET_TIMER_PARAM()	{	memset(this, 0, sizeof(*this));	}
		long long iIDEvent;	// ��ʱ��Id
		int iElapse;		// ��Ӧʱ�䣬�� ms Ϊ��λ			
	};

	enum{	
			SET_TIMER = 10,		// ���ö�ʱ��
			KILL_TIMER = 20,	// ɱ��ʱ��
		};

	enum{	
			PULSE_TIME=20,		// һ�������ʱ�䣬��msΪ��λ
		};

	struct TIMER_PARAM		// ��ʱ������
	{
		TIMER_PARAM()	{ memset(this, 0, sizeof(*this)); }

		long long lCount;
		long long iIDEvent;
		int		 iPulseCount;	// ����ı������������ ms �����ỻ��� PULSE_TIME ��������
	};

public:
	CCoreTimer(void);
	~CCoreTimer(void);

private:

	static unsigned __stdcall  thread_spawn_timer(void* pParam);

public:
	
	// ���ⲿ������Ϣ��
	int set_msg_pool(CMemBlockPool* pMsgPool);

	// ����
	int start_timer();

	// ֹͣ
	int stop_timer();

	// ���ö�ʱ��/�޸Ķ�ʱ��������ܲ����ڴ˶�ʱ��ʱ�������ö�ʱ��������ܴ��ڴ˶�ʱ��ʱ�����޸Ĵ˶�ʱ���ļ��
	int set_timer(long long iIDEvent, int iElapse);

	// ������ʱ��
	int kill_timer(long long iIDEvent);

public:
	// ��Ӧ������Ϣ
	virtual TASK_MSG_RESULT OnTask(CMemBlock*& pMsgBlock);

private:
	
	int SetTimer(long long iIDEvent, int iElapse);

	int KillTimer(long long iIDEvent);

	// ��ʱ����Ӧ
	int OnTimer();

public:
	BOOL	m_bIsExit;	// ������

private:
//	CCoreServer*	m_pCoreServer;
	CMemBlockPool*	m_pMsgPool;

	list<TIMER_PARAM>	m_listTimer;	// ��ʱ������
	CCriticalSpection	m_lock;			// �� m_listTimer

	HANDLE			m_hThread;
	unsigned int	m_dwThreadID;
};

#endif