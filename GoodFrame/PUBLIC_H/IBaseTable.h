
/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\IBaseTable.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	IBaseTable
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef I_BASE_TABLE_H
#define I_BASE_TABLE_H

#include <vector>
using std::vector;

#include "TaskMsgResult.h"
#include "SingleUser.h"
#include "TableInfo.h"
#include "ThreadGuardEx.h"
#include "MemBlockPool.h"
#include "RoomInfo.h"
#include "GameTaskList.h"

#include ".\EndlessLoopGuard.h"

enum TASK_MSG_RESULT;	// ������Ϣ���
class CMemBlock;
class IRoomMgr;

// ����
class __declspec(dllexport) IBaseTable
{
public:
	IBaseTable(void);
	~IBaseTable(void);

public:
	// ������Ϣ
	virtual void OnTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen) = 0;

	// ����֮ǰ
	virtual int OnLeaveSeatBefore(LONGLONG lUserId, int iSeatNo) = 0;

	// ����֮��
	virtual int OnLeaveSeatLast(int iSeatNo) = 0;

	// ����
	virtual int OnCut(LONGLONG lUserId) = 0;

	// ����������Ӧ�����������û����������¼����ʱ�Ż���Ӧ
	virtual int OnRecomeAfterCut(int iSeatNo) = 0;

	//��Ϸ��ʼ
	virtual int OnGameBegin() = 0;

	//��Ϸ����
	virtual int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag)= 0;

	// ���Ӷ�ʱ����Ӧ
	virtual int OnTableTimer(int iTableNo, int iIDEvent) = 0;

	// ����
	virtual int OnRaiseHand(int iSeatNo) = 0;

	// ��ȡ̨�� �������ӵ�
	virtual void TradeFee() = 0;

	// ����
	virtual int OnAccounts(int iSeatNo) = 0;

	// �û�����
	virtual void OnUserSitDown(int iSeatNo) = 0 ;

public:

	/* --------------------------------------------------------------------------
	����˵������ʼ��
	���������
		pRoomMgr		�����������ָ��
		tableInfo		������Ϣ
		iGameBeginType	��Ϸ��ʼ�����ͣ��ο� GAME_BEGIN_TYPE_AUTO ��
	����������
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	void init(IRoomMgr* pRoomMgr, const TABLE_INFO& tableInfo, int iGameBeginType);

	// �ͷ���Դ
	void uninit();

	// ������Ϸ�Ǽ�ʹ�õĶ�ʱ��
	int create_game_skeleton_timer();

	// ������Ϸ�Ǽ�ʹ�õĶ�ʱ��
	int destroy_game_start_timer();

	// �򵥸��û�������Ϸ��Ϣ
	int send_game_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// �򵥸��û�������Ϸ��Ϣ
	int send_game_data(LONGLONG lChannelNo, int iMainCode, int iSubCode);

	// �򵥸��û�������Ϸ��Ϣ
	int send_data(int iSeatNo, int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// �򵥸��û�������Ϸ��Ϣ
	int send_data(int iSeatNo, int iMainCode, int iSubCode);

	// �����ڹ㲥
	int broadcast_in_room(int iMainCode, int iSubCode, BYTE* pData, int iDataLen,LONGLONG lChannelNoIngore=INVALID_CHANNEL_NO, int iTableNo=INVAL_TABLE_NO);
	
	// ���ڹ㲥
	int send_table_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen, LONGLONG lChannelNoIngore=INVALID_CHANNEL_NO);

	// ���ڹ㲥ָ��״̬���û�
	int send_table_state_user(int iMainCode, int iSubCode, BYTE* pData, int iDataLen, int iUserState, LONGLONG lChannelNoIngore=INVALID_CHANNEL_NO);

	// ��ӡ�����û��б�
	void PrintTableUser();

	// �������Ӷ�ʱ��
	int set_table_timer(int iIDEvent, int iElapse);

	// �������Ӷ�ʱ��
	int kill_table_timer(int iIDEvent);

	// ���Ӷ�ʱ��
	int OnBaseTableTimer(int iTableNo, int iIDEvent);

	// ��Ӧ������Ϣ
	void OnBaseTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen);

	// ���ھ����߹㲥
	int broadcast_raise_hand(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);
	
	/* --------------------------------------------------------------------------
	����˵����д����־���
	���������
		bShowInScreen	��ʾ����Ļ��
		iType	���ͣ��ο� LOG_ERR_TYPE ö�٣�
				LOG_TYPE_PROMPT = 0,	// ��ʾ
				LOG_TYPE_WARING = 1,	// ����
				LOG_TYPE_ERR = 2,		// �������쳣

		pszSentence		��־���
		iSentenceLen	��־���ĳ���
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int write_log(BOOL bShowInScreen, int iType, char* pszSentence, int iSentenceLen);

	// �ı���ֵ
	//int change_gold(LONGLONG lChannelNo, LONGLONG lChangeScore);

	// ������ѭ�����ָ��
	void set_endless_loop(CEndlessLoop* pEndlessLoop);

	// ������λ�Ż�ȡ��ǰ������
	CSingleUser *get_SingleUser_by_seatNo(int iSeatNo);

	// �������������������
	int get_sit_down_count();

	// ��������������Ҿ��ֵ�����
	int get_sit_down_raise_count();

	/* --------------------------------------------------------------------------
	����˵�����ж��Ƿ���Կ�ʼ��Ϸ
	����ֵ��
		���Կ�ʼ�򷵻� 0�����ܿ�ʼ���ش��������£�
	--------------------------------------------------------------------------*/
	int can_begin_game();

	/* --------------------------------------------------------------------------
	����˵�����ж��Ƿ���Խ�����Ϸ
	����ֵ��
		���Կ�ʼ�򷵻� 0�����ܿ�ʼ���ش��������£�
	--------------------------------------------------------------------------*/
	int can_finish_game();

	// ��������
	int recome_after_cut(int iSeatNo);

public:
	// ����
	int sit_down(int iSeatNo, CSingleUser* pSingleUser, int iOldDeskNo=INVAL_TABLE_NO);

	// ����(�������)
	int leave_seat_external(int iSeatNo);

	// ����(���ӵ���) bIsChangeTable=�Ƿ��ǻ����˳�
	int leave_seat(int iSeatNo, bool bIsChangeTable=false);

	// ��һ��������� 
	int tick_table_leave_seat(LONGLONG lMgrChannelNo, BOOL bWriteScore=TRUE, BOOL bShowInfo=TRUE);

	// ��ȡ����״̬(��ʼ/����״̬...)
	volatile long get_game_sys_state(){return m_iGameSysState;}; 

	// ����Ƿ���Ч���Ӻ�
	SEAT_INFO* is_valid_seat_no(int iSeatNo);

	// ����
	int OnUserAccountsWrite(int iSeatNo, CMD_WRITE_SCORE sendData);

	// ��������
	int OnUserMatchAccounts(int iSeatNo, CMD_MatchAccounts sendData);

private:
	// ��Ϸ��ʼǰ����
	int OnGameStart();

	// ��Ϸ����
	int OnGameEnd();

	// ����
	int OnBaseRaiseHand(int iSeatNo);

	// ���δ����
	void OnCheckAntiAddiction();

	// �������
	void UserTaskFinish(int iSeatNo, int iTaskId);

	// ���������
	void CheckTableRaise();

	// ��ȡ�������������
	int GetUserIdentityCount(UserIdentity eUserIdentity);

public:
	IRoomMgr*		m_pRoomMgr;	// �����������ָ��
	CMemBlockPool*	m_pMsgPool;
	TABLE_INFO	m_stTableInfo;	// ������Ϣ
	vector<SEAT_INFO*>	m_vecSeatInfo;

	CEndlessLoop* m_pEndlessLoop;	// ��ѭ����⣬ͬ�����Լ����������ʱ��˯�ߵ�����

protected:
	CSRWLock	m_lockTable;	// ��������ע�⣺��������Ƕ�ף�һǶ�׾ͻ�����

	int	m_iGameBeginType;				// ��Ϸ��ʼ�����ͣ��ο� GAME_BEGIN_TYPE_AUTO ��
	volatile long m_iGameSysState;		// ��Ϸϵͳ��״̬���ο� GAME_SYS_STATE_NO ��

	int m_iWaitBegintick;		// �ȴ���ʼ�ĵδ�Ŀ����Ϊ���ÿ��ȫ��׼����ϲ���Ӧ�ò㿪ʼ��Ϸ
	int m_iWaitBegintickCount;	// �ȴ���ʼ�ĵδ����

	LONGLONG m_lFinishAfterFreeTable;	// �����೤ʱ�����Խ�����Ϸ���� ms Ϊ��λ
};

#endif