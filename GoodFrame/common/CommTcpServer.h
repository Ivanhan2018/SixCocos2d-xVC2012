/********************************************************************
	created:	2013/01/24
	created:	15:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		�����
	
	purpose:	TCP ͨѶģ��
*********************************************************************/

#ifndef COMM_TCP_SERVICE_H
#define COMM_TCP_SERVICE_H

#include "./ChennelNoMgr.h"

#include "./ServerHandle.h"
#include "./TerminateResult.h"
#include "./AcceptResult.h"

#include "./LightweightPool.h"
#include "./CloseType.h"

class __declspec(dllexport) CCoreServer;

// ��Ч���ȶ�
class __declspec(dllexport) CCommTcpServer 
{
public:

	enum{	MAX_THREAD_COUNT = 20,	// ���� thread_work �߳�����
		};

	enum {	COMTIMEOUT_INFINITE				= -1,	// No time out
		 };

	enum{	PULSE_TIME=100,		// һ�������ʱ�䣬��msΪ��λ
		};

	enum{
		INITIATIVE_CLOSE_PEER_OVER_TIME = 10 * 1000,	// �����رնԶ˵ĳ�ʱֵ����msΪ��λ
		};
public:
	friend class CServerHandle;
	friend class CAcceptResult;
	friend class CRecvResult;
	friend class CCoreServer;

public:
	CCommTcpServer(void);
	~CCommTcpServer(void);

public:
	//--- ����Ľӿ� -------------------------------------------------

	// ����������ָ��
	void set_core_server(CCoreServer* pCoreServer);

	// ���ü�����ַ
	void set_listen_addr(const char* szListenAddr);

	// ���ü����˿�
	void set_listen_port(unsigned int nPort);

	// ���ⲿ������Ϣ��
	int set_msg_pool(CMemBlockPool* pMsgPool);

	// ������Ϣ��ĳ���
	void set_msg_block_size(int iMsgBlockSize=2048);

	// ������Ϣ�ص����Ԫ������
	void set_msg_pool_init_count(int iMsgPoolInitCount);

	// ���öԶ˷���ص����Ԫ������
	void set_service_handle_pool_init_count(int iServerHandlePoolInitCount);

	// �������ӽ���ص����Ԫ������
	void set_accept_result_pool_init_count(int iAcceptResultPoolInitCount);

	// ���÷��ͽ���ص����Ԫ������
	void set_send_result_pool_init_count(int iSendResultPoolInitCount);

	// ���ü�������رնԶ˵�ʱ�䣬�� ms Ϊ��λ
	void set_check_power_close_peer(LONGLONG iTime);

	// �����������ֳص�ʱ�䣬iShrinkPoolsTime �� ms Ϊ��λ
	void set_shrink_pools_time(LONGLONG iShrinkPoolsTime);

	// ������������ʱ�䣬�� PULSE_TIME ����Ϊ������λ���� N �� PULSE_TIME ���һ��
	void set_heartbeat_check_time(LONGLONG iHeartbeatCheckTime);

	// ����������������ʱ�䣬�� ms Ϊ��λ���� N ms ֮�ڿͻ���û���κ���Ϣ����������Ϊ�ÿͻ���������
	void set_no_heartbeat_die_time(int iNoHeartbeatDieTime);

	// �Ƿ�������
	BOOL is_heartbeat(CORE_MSG_HEAD* pMsgHead);

	// �Ƿ������ر�ָ���Զ˵�ָ��
	BOOL is_power_close_peer(CORE_MSG_HEAD* pMsgHead);

	/* --------------------------------------------------------------------------
	����˵������ʼ��
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10    ������Ϣ��ʧ��
		20    �����Զ˷����ʧ��
		30    �������ӽ����ʧ��
		40    �������ͽ����ʧ��
		70    CreateIoCompletionPort ʧ��
		80    ���������߳�ʧ��
		90    ������ʱ�����߳�ʧ��
	--------------------------------------------------------------------------*/
	int init();

	// ��������
	int start();

	// ֹͣ����
	int stop();

	// ��ʾ���еĳ���Ϣ
	void display_all_pool();

	// ��ӡ���е���Ч�Զ���Ϣ
	void display_all_valid_peer();

	// ���� IOCP �����̵߳�����
	void set_work_thread_count(int iCount);

	// ����
	int send_data(LONGLONG lChannelNo, CMemBlock*& pSendBlock);

	// ���ز����ͣ�Ч�ʵͣ����á����ز����ͣ��˺���Ч�ʵͣ����á�ͨ��������ͻ���һ���Դ������������ݣ����緢���û��б��ĳ��ϡ�
	int retrieve_send_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, BYTE* pData=NULL, int iDataLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	int tcp_broadcase(int iMainCode, int iSubCode, BYTE* pData=NULL, int iDataLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	// TCP�㲥�����������ݵ����е���Ч�Զ�
	int tcp_broadcase(CMemBlock*& pSendBlock, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	// ������жԶ˵�����
	int check_all_peer_heartbeat();

	// �����ر�ָ���ĶԶˣ��ͻ��˲�����ִ�ж�������
	int power_close_peer(LONGLONG lChannelNo);

	// �ر�ָ���ĶԶ�
	int close_peer(LONGLONG lChannelNo);

	// �Ͽ����еĶԶ�
	void close_all_peer();

	// ͳ�ƽ��յ����ʣ��Ǹ������Ŀ���
	void statistic_recv_rate();

	// ��������رնԶ˳�ʱ
	int check_power_close_peer();

protected:
	//--- �ص����� -----------------------------------------------B--

	// ��Ӧ�Զ��ѹر���
	int OnClose(LONGLONG lChannelNo, SOCKET socketClose, CLOSE_TYPE iCloseType);

	// ��Ӧ���ͳɹ�
	void OnSend(LONGLONG lChannelNo, const CMemBlock* pSendBlock);

	// ��Ӧ����ʧ��
	void OnSendFailed(LONGLONG lChannelNo, const CMemBlock* pSendBlock);

	// ��Ӧ���ӳɹ�
	void OnConnect(LONGLONG lChannelNo, const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr);	

	// ��Ӧ����ʧ��
	void OnConnectFail(const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr, int iErrorCode);

	/* --------------------------------------------------------------------------
	����˵������Ӧ�հ���Ϣ�����������ϸ��ա������ִ����ԭ����ִ�еģ�������˵������IOCP����Ĺ����߳��ڵ��ñ�����
	���������
		lChannelNo
	����������
		pRecv		��Ϣ�飬�Ѿ���ԭ�Ӱ��ˡ�ע�⣺��ʱ��δ��أ��� CCommTcpServer ֮��Ļ��ƹ��
	--------------------------------------------------------------------------*/
	void OnRecv(LONGLONG lChannelNo, CMemBlock*& pRecv);

	// ��ӦͨѶ�������Ϣ
	void OnCommError(LONGLONG lChannelNo, char* pszError);


private:

	// IOCP �Ĺ����߳�
	static unsigned __stdcall thread_work(LPVOID lpParameter);

	// ��ʱ�����߳�
	static unsigned __stdcall thread_check(LPVOID lpParameter);
	
	// �����߳�
	void start_work_threads();

	// ֹͣ�߳�
	int	stop_work_threads();

	// ��������
	int	start_listen();

	// ֹͣ����
	int	stop_listen();

	// ��������
	int	request_accept();

private:

	BOOL volatile m_bIsExit;		// �˳�״̬

	HANDLE		m_hCompletionPort;
	DWORD		m_dwTmp;

	CChennelNoMgr m_stServerHandleMgr;	// ͨ�����Զ˷��񣩹���

	CMemBlockPool*	m_pMsgPool;				// ��Ϣ�أ��ǿ��Դ��ⲿ�����
	BOOL			m_bMsgPoolFromExternal;	// TRUE ��ʾ��Ϣ���Ǵ��ⲿ��������
	int				m_iMsgPoolInitCount;	// ��Ϣ�ص����Ԫ������
	int				m_iMsgBlockSize;		// ��Ϣ��ĳ���

	CLightweightPool<CServerHandle>*	m_pServerHandlePool;			// �Զ˷����
	int									m_iServerHandlePoolInitCount;	// �Զ˷���ص����Ԫ������

	CLightweightPool<CAcceptResult>*	m_pAcceptResultPool;			// ���ӽ����
	int									m_iAcceptResultPoolInitCount;	// ���ӽ���ص����Ԫ������

	CLightweightPool<CSendResult>*	m_pSendResultPool;			// ���ͽ����
	int								m_iSendResultPoolInitCount;	// ���ͽ���ص����Ԫ������

	LONGLONG	m_iCheckInitiativeClosePeerPulseCount;	// ��������رնԶ˵��������
	LONGLONG	m_iShrinkPoolsiPulseCount;		// �������ֳص��������
	LONGLONG	m_iHeartbeatCheckPulseCount;	// ���������������
	LONGLONG	m_iNoHeartbeatDieTime;	// ������������ʱ�䣬�� ms Ϊ��λ���� N ms ֮�ڿͻ���û���κ���Ϣ����������Ϊ�ÿͻ���������

	
private:
	CCoreServer*	m_pCoreServer;	// ������ָ��

	int			m_nThreadCount;
	sockaddr_in	m_saListenAddr;
	SOCKET		m_sListenSocket;

	CTerminateResult	m_stTerminateResult;

	HANDLE			m_hThread[MAX_THREAD_COUNT];	// �����߳�
	unsigned int	m_uThreadId[MAX_THREAD_COUNT];	// �����߳�ID
	int				m_iThreadCount;					// �����߳�����

	long long	m_iPulseCount;	// ���������

	HANDLE			m_hThreadShrinkPool;		// ��ʱ�����߳�
	unsigned int	m_uThreadShrinkPoolId;		// ��ʱ�����߳�ID

	CCriticalSpection  m_lockClose;	// �� Close �ģ�Ϊ�˰�ȫ������Ƕ�ף�
	
	volatile LONGLONG m_lAtomMsgCount;	// ԭ�Ӱ�������
	LONGLONG m_lStartStatisticTime;		// ��ʼͳ�Ƶ�ʱ��
	BOOL	 m_bStatisticRecvRate;		// �Ƿ�ͳ�ƽ�������
	int		 m_iStatistInterval;		// ͳ�Ƽ������ PULSE_TIME Ϊ��������


		
};

#endif