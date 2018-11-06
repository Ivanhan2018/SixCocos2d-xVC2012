
#ifndef I_ROOM_MGR_H
#define I_ROOM_MGR_H

#include "./MemBlockPool.h"
#include "./EasyDataTime.h"

/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\IRoomMgr.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	IRoomMgr
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#include "./ThreadGuardEx.h"
#include "./LightweightPool.h"

#include "./GameSkeletonMsgCode.h"
#include "./RoomInfo.h"
#include "./SingleUser.h"
#include "./TableInfo.h"
#include "./RoomState.h"
#include "./CloseType.h"
#include "GradeMgr.h"

#include <hash_map>
using std::hash_map;
using std::pair;

#include <vector>
using std::vector;

#include <map>

class CEndlessLoop;
class IBaseTable;
class CCoreServer;
class CClientToRMS;

enum TASK_MSG_RESULT;	// ������Ϣ���

#define ROOM_TIMER_FLAG  0x0001000000000000	// ���䶨ʱ����ʶ����32λ��ǰ16λ��ʾ���������
#define TABLE_TIMER_FLAG 0x0002000000000000	// ���Ӷ�ʱ����ʶ����32λ�ĺ�16λ��ʾ���Ӻ�

// �������
class __declspec(dllexport) IRoomMgr
{
	
public:
	IRoomMgr(void);
	~IRoomMgr(void);


public:
	// ��Ӧ���ӳɹ�
	virtual void OnConnect(LONGLONG lChannelNo);	

	// ��Ӧ����ʧ��
	virtual void OnConnectFail(int iErrorCode);

	// ��Ӧ�Զ��ѹر���
	virtual int OnClose(LONGLONG lChannelNo, CLOSE_TYPE iCloseType);

	// �����߳��û�
	int OnKickOutUser(LONGLONG lChannelNo);

	/* --------------------------------------------------------------------------
	����˵������Ӧ����������
	���������
		lChannelNo	������˶Ͽ���ͨ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int OnNoHeartbeatDie(LONGLONG lChannelNo);

	// ��ӡ���е���ѭ��������
	int display_all_guard();

public:	//--- ����Ҫ�̳еĴ��麯�� -----------------------------------------------

	// ��Ӧ������Ϣ
	virtual TASK_MSG_RESULT OnRoomMsg(CMemBlock*& pMsgBlock) = 0;
	
	// ��Ӧ����������������Ϣ
	virtual void OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;
	
	// �Զ˹ر�֮ǰһɲ�ǵ���Ӧ
	virtual int OnCloseBefore(LONGLONG lUserId) = 0;

public:	//--- �ص����� -----------------------------------------------

	// ���ܷ��������
	TASK_MSG_RESULT OnSkeletonRoomMgrServer(CMemBlock*& pMsgBlock);

	/* --------------------------------------------------------------------------
	����˵������Ӧ������Ϣ
	����������
		pMsgBlock	��Ϣ�飬ע���Զ�����źţ��������أ����Բο� TASK_MSG_RESULT ��ֵ
	����ֵ
		�ο� TASK_MSG_RESULT ö��
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT OnSkeletonRoomMsg(CMemBlock*& pMsgBlock);

	/* --------------------------------------------------------------------------
	����˵������Ӧ������Ϣ
	����������
		pMsgBlock	��Ϣ�飬ע���Զ�����źţ��������أ����Բο� TASK_MSG_RESULT ��ֵ
	����ֵ
		�ο� TASK_MSG_RESULT ö��
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT OnSkeletonTableMsg(CMemBlock*& pMsgBlock);

	/* --------------------------------------------------------------------------
	����˵������Ӧ����Ա��Ϣ
	����������
		pMsgBlock	��Ϣ�飬ע���Զ�����źţ��������أ����Բο� TASK_MSG_RESULT ��ֵ
	����ֵ
		�ο� TASK_MSG_RESULT ö��
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT OnSkeletonMagagerMsg(CMemBlock*& pMsgBlock);

	// ��Ӧ������Ϣ
	TASK_MSG_RESULT OnSkeletonMatchMsg(CMemBlock*& pMsgBlock);

	// ��Ӧ��Ϸ������Ϣ
	TASK_MSG_RESULT OnSkeletonTaskMsg(CMemBlock*& pMsgBlock);

	// ��Ӧ����������������Ϣ
	void OnSkeletonRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// ��Ӧ������Ϣ
	TASK_MSG_RESULT OnSkeletonPropMsg(CMemBlock*& pMsgBlock);

	// ϵͳ��Ϣ
	TASK_MSG_RESULT OnSkeletonSysMsg(CMemBlock*& pMsgBlock);

	// ���䶨ʱ����Ӧ
	int OnRoomTimer(int iIDEvent);

	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);

public:

	// ����
	void start(const CCoreServer* pCCoreServer, const CMemBlockPool* pMsgPool, const SERVER_ROOM_INFO& serverRoomInfo);

	// ���ö�ʱ��
	int set_room_timer(int iIDEvent, int iElapse);

	// ������ʱ��
	int kill_room_timer(int iIDEvent);

	// �������Ӷ�ʱ��
	int set_table_timer(int iTableNo, int iIDEvent, int iElapse);

	// �������Ӷ�ʱ��
	int kill_table_timer(int iTableNo, int iIDEvent);

	// ������Ϸ��Ϣ����Ч��
	int send_game_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// ������Ϸ��Ϣ��// add by cxf
	int send_game_data(LONGLONG lChannelNo, int iMainCode, int iSubCode);

	// �����ڹ㲥
	int broadcast_in_room(int iMainCode, int iSubCode, BYTE* pData=NULL, int iDataLen=0,LONGLONG lChannelNoIngore=INVALID_CHANNEL_NO,int iTableNo=INVAL_TABLE_NO);

	// �رնԶ�
	int close_peer(LONGLONG lChannelNo);

	/* --------------------------------------------------------------------------
	����˵����Ͷ��������Ϣ������ϢͶ��ָ��������ģ��
	���������
		iTaskModuleID	����ģ��ID
	����������
		pMsgBlock		��Ϣ��
	����ֵ��
		���زο� TASK_MSG_RESULT ö��
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT post_work_msg(int iTaskModuleID, CMemBlock*& pMsgBlock);

	// �����Ϣ�ص�ָ��
	CMemBlockPool* get_msg_pool();

	// �����ѭ�����ָ��
	CEndlessLoop* get_endless_loop();

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

	// ��ӡ�����û��б�
	void PrintRoomUser();

	// ��ӡ�����û��б�
	void PrintAllTableUser();

	// ��÷�����Ϣ
	SERVER_ROOM_INFO get_server_room_info();

	// ���÷�����Ϣ
	void set_server_room_info(SERVER_ROOM_INFO info);

public:

	// ���ͨ����
	LONGLONG get_channel(CMemBlock* pMsgBlock);

	/* --------------------------------------------------------------------------
	����˵���������������λ��
	���������
		lChannelNo	ͨ����
	����������
		iTableNo	����
		iSeatNo		����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	������Ч
			20	������Ч
			30	û������
			40  �Ҳ������û�
	--------------------------------------------------------------------------*/
	int get_table_seat_no(LONGLONG lChannelNo, int& iTableNo, int& iSeatNo);

	/* --------------------------------------------------------------------------
	����˵���������Ƿ���Ч
	���������
		liTableNo	����
	����ֵ��
		��Ч�򷵻ط����ָ�룬ʧ�ܷ���0��
	--------------------------------------------------------------------------*/
	IBaseTable* is_valid_table_no(int iTableNo);

	// ������Ϸ��ʼ�����ͣ�iType �ο� GAME_BEGIN_TYPE_AUTO ��
	void game_begin_type(int iType);

	// �����Ϸ��ʼ�����ͣ� ����ֵ�ο� GAME_BEGIN_TYPE_AUTO ��
	int game_begin_type();

public:
	//--- ������� -----------------------------------------------

	// ��÷��������û���ͨ����
	int find_all_user_channel(vector<LONGLONG>* pVecChannel);


	/* --------------------------------------------------------------------------
	����˵������ͨ���Ż�õ����û�ָ��
	���������
		lChannelNo	ͨ����
		bLock		true��ʾ�������ң�false ��ʾ��������
	����������
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	-------------------------------------------------------------------------- */
	CSingleUser* find_user_by_channel(LONGLONG lChannelNo, BOOL bLock=true);

	// ���û�ID��õ����û�ָ��
	CSingleUser* find_user_by_user_id(LONGLONG lUserId);

	// ��õ������ָ�룬������������λ��
	CSingleUser* find_user_by_table_seat(int iTableNo, int iSeatNo);

	// ��õ������ָ�룬�����û���������
	CSingleUser* find_user_by_name_password(const char* pszName, const char* pszPassword);

	// ����û���ͨ���ţ������û�ID
	int modi_user_by_channel(LONGLONG lUserId, LONGLONG lChannelNo, CSingleUser* singleUser);

	/* --------------------------------------------------------------------------
	����˵��������һ�������û�
	���������
		lChannelNo	ͨ����
		pUserInfo	�û���Ϣ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10 �β��ǿ�ֵ
			20 �Ѵ��ڸ��û����޷�����
	--------------------------------------------------------------------------*/
	int add_user(LONGLONG lChannelNo, const USER_INFO* pUserInfo);

	/* --------------------------------------------------------------------------
	����˵�����Ƴ�һ�������û�������ͨ����
	���������
		lChannelNo	ͨ����
	����������
		userInfo	�뷿�ߵ���Ϣ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10  δ�ҵ�
			20  m_pUserPool ���ʧ��
	--------------------------------------------------------------------------*/
	int remove_one_user(LONGLONG lChannelNo);
	
	// ���ͷ���������б�
	int send_table_list(LONGLONG lChannelNo);

	// ���ͷ����ڵ��û��б�
	int send_user_list(LONGLONG lChannelNo);

	// ����д��
	int SendWriteData(int iMainCode, int iSubCode, BYTE* byData, int iDataLen);

public:
	//--- ������� -----------------------------------------------

	// �жϹ����ߵ�Ȩ��
	int is_manager_power(LONGLONG lChannelNo, LONGLONG lManagerPower);

	// �뿪����
	int leave_room(LONGLONG lChannelNo);

	// �����Ӻ�����
	int allot_table_seat(CSingleUser *pSingleUser, SITDOWN* pSeatdown, int iOldDeskNo=INVAL_TABLE_NO);

	// ������
	int allot_seat(CSingleUser *pSingleUser, SITDOWN* pSeatdown);

	// ����
	int user_sit_down(CSingleUser *pSingleUser, SITDOWN* pSeatdown);

	// ����
	int leave_seat(LONGLONG lChannelNo);

	/* --------------------------------------------------------------------------
	����˵������һ��������� 
	���������
		lMgrChannelNo	�����ߵ�ͨ����
		iTableNo		���ߵ�����
		bWriteScore		�ߺ��Ƿ�д��ұ仯ֵ
	����ֵ��
	   �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int tick_table_leave_seat(LONGLONG lMgrChannelNo, int iTableNo, BOOL bWriteScore=FALSE);

	// �����е��������
	int tick_all_leave_seat(LONGLONG lMgrChannelNo, BOOL bWriteScore=FALSE);

	// ��һ������뷿
	int tick_table_out_room(LONGLONG lMgrChannelNo, int iTableNo);

	// ������뷿
	int tick_user_out_room(LONGLONG lMgrChannelNo, const TICK_USER_OUT_ROOM* pTickOutRoom);
private:
	// ���÷�����Ϣ
	void SetRoomInfoSim(SERVER_ROOM_INFO_SIM &serverRoomInfoSim);	// add by cxf 2013-07-06

	// �û��Ŷ�
	void OnArrangeQueue(LONGLONG lChannelNo, BYTE *pData, int iDataLen);

	// ȡ���Ŷ�
	void OnCancelArrangeQueue(CSingleUser* pSingleUser);

	// �Ŷ��û�����
	void OnConstituteTables();

	// Ѱ�ҿ�����
	IBaseTable* Find_Null_Table();

	// �������
	void OnCheckUserHeartbeat();

	// ��ȡ�Ƿ����÷�����
	void OnAntiAddiction();

	// ��ȡ��������
	void get_room_user_count(CMD_RoomUserCount &roomUserCount);

	// ����
	void OnUserChangeDesk(CSingleUser *pSingleUser);

public:
	CCoreServer*		 m_pCoreServer;
	CMemBlockPool*		 m_pMsgPool;
	
	vector<IBaseTable*>	 m_vecTable;
	bool				m_bIsAntiAddiction;		// �Ƿ�����	
	GradeMgr*			m_pGradeMgr;			// �ȼ�����

	

private:

	// ��1����ͨ���ţ���2���ǵ����û���ͨ�� Channel �Ÿ��ٲ�ѯ CSingleUser
    typedef	hash_map<LONGLONG, CSingleUser*>	MAP_SINGLE_USER; 	// 
	typedef pair <LONGLONG, CSingleUser*>		PAIR_SINGLE_USER;	// ��ֵ��
	MAP_SINGLE_USER m_mapChannel;	// ��������û�
	
	// ��1���� UserId����2����ͨ���ţ�Ŀ����ͨ�� UserId �Ÿ��ٲ�ѯͨ����
	typedef hash_map<LONGLONG, LONGLONG> MAP_USERID_CHANNEL;
	typedef pair<LONGLONG, LONGLONG>	 PAIR_USERID_CHANNEL;
	MAP_USERID_CHANNEL m_mapUserid;		// ��������û���
	
	CLightweightPool<CSingleUser>*	m_pUserPool;	// �û��أ�һ�����������е��û������۽����Ļ����뷿�ġ�
	
	CSRWLock	m_lock;		// ��� m_mapChannel �� m_mapUserid ����

	std::map<LONGLONG, CMD_USER_ARRANGE_QUEUE_LIST> m_mapUserQueueList;
	CSRWLock	m_lockQueueList;

private:
	int		 m_iGameBeginType;	// ��Ϸ��ʼ�����ͣ��ο� GAME_BEGIN_TYPE_AUTO ��

	CRoomState	m_stRoomState;	// ����״̬

	SERVER_ROOM_INFO	 m_stServerRoomInfo;	// ������Ϣ

	CLightweightPool<GameTaskList>* m_pGameTaskPool;

protected:
	CEndlessLoop* m_pEndlessLoop;	// ��ѭ����⣬ͬ�����Լ����������ʱ��˯�ߵ�����
};

#endif