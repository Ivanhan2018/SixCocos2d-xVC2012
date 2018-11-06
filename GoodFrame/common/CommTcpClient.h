
#ifndef COMM_TCP_CLIENT_H
#define COMM_TCP_CLIENT_H

#include "./SelfModuleID.h"

#include "./MemBlockPool.h"
#include "./LightweightPool.h"

#include "./ClientRecvResult.h"
#include "./ClientSendResult.h"

#include "./TerminateResult.h"

#include "./ThreadGuard.h"
#include "./ThreadGuardEx.h"

#include "./CloseType.h"
#include "./CoreHead.h"

class CCoreClient;

class CCommTcpClient
{
public:
	friend class CCoreClient;

	struct AFTER_CONN_SUCC	// ���ӳɹ���
	{
		AFTER_CONN_SUCC(){	memset(this, 0, sizeof(*this));	}

		bool bIsReconnect;
		sockaddr_in addrConnect;
		CCommTcpClient* pThis;
	};

	

	enum{	PULSE_TIME=100,		// һ�������ʱ�䣬��msΪ��λ
		};

	// ���ͻ��壬ϵͳĬ�ϵ�״̬���ͺͽ���һ��Ϊ8688�ֽ�(ԼΪ8.5K)��
	// ��ʵ�ʵĹ����з������ݺͽ����������Ƚϴ󣬿�������socket����������������send(),recv()���ϵ�ѭ���շ���
	enum{	SEND_BUF_SIZE=128*1024 };

	// ���ջ���
	enum{	RECV_BUF_SIZE=128*1024 };

	
	friend class CClientSendResult;
	friend class CClientRecvResult;
public:
	CCommTcpClient(void);
	~CCommTcpClient(void);

public:

	// �ȴ��������յ����Ӻ��ʼ���������
	static unsigned __stdcall  thread_wait_server_init(void* pParam);

	//--- ����Ľӿ� -------------------------------------------------

	// ����������ָ��
	void set_core_client(CCoreClient* pCoreClient);

	// ������Ϣ��ĳ��ȣ���һ��һ��Ҫ�ӣ�������� ntdll.dll �ı���
	void set_msg_block_size(int iMsgBlockSize=2048);

	// ���÷��ͽ���ص����Ԫ������
	void set_send_result_pool_init_count(int iSendResultPoolInitCount);

	// ������Ϣ�ص����Ԫ������
	void set_msg_pool_init_count(int iMsgPoolInitCount);

	// ���ö��������ļ��ʱ�䣬��λms
	void set_reconnect_interval_time(int iAutoReConnectTime);

	// ��ö�������
	bool get_reconnect();

	// ���ö�������
	void set_reconnect(bool bAutoReConnect);

	// ��ùرշ�ʽ
	CLOSE_TYPE get_close_type();

	// ���ùرշ�ʽ
	void set_close_type(CLOSE_TYPE iCloseType);

	// �����������ֳص�ʱ�䣬iShrinkPoolsTime �� ms Ϊ��λ
	void set_shrink_pools_time(long long iShrinkPoolsTime);

	// ���÷�����������ʱ��
	void set_send_heartbeat_time(long long iSendHeartbeatTime);

	/* --------------------------------------------------------------------------
	����˵������ʼ��
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10  ִ�� WSAStartup ʧ��
		20  ������Ϣ��ʧ��
		40  �������ͷ��ͽ����ʧ��
		50  m_hConnection ִ�� WSASocket ʧ��
		60  CreateIoCompletionPort ʧ��
		70  ���� IOCP �Ĺ����߳�ʧ��
		90  ������ʱ�����߳�ʧ��
	--------------------------------------------------------------------------*/
	int init();

	// ����
	int start();

	// ֹͣ
	int stop();

	// ��������
	int send_data(CMemBlock*& pSendBlock);

	// ��������
	int send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	// ���ʹ������ݣ����ڲ���
	int send_error_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	// �������ӵ�ַ
	void set_connect_addr(const char* szListenAddr);

	// �������Ӷ˿�
	void set_connect_port(unsigned int nPort);

	// ����С�������
	int OnRecvComplete(int iResult, const CMemBlock* pRecv);

	// �����رշ���ˣ�Ŀ�����÷������������ͻ��������ر�������
	int power_close();



	// ��ʾ���еĳ���Ϣ
	void display_all_pool();

	// ����������
	int send_heartbeat_packeg();

private:
	/* --------------------------------------------------------------------------
	����˵�����رշ����
	���������
		bClientClose	TRUE ��ʾ�ͻ��������رգ�FALSE ��ʾ������˹رյ�
	����ֵ��
		�ɹ��򷵻� TRUE�����򷵻� FALSE ��
	--------------------------------------------------------------------------*/
	bool close(CLOSE_TYPE iCloseType);

protected:		
	//--- �ص����� ------------------------

	// ��Ӧ���ӳɹ�
	void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);

	/* --------------------------------------------------------------------------
	����˵��������ʧ�ܵĻص�
	���������
		bIsReconnect	TRUE ��ʾ��������
		iError			WSAGetLastError() �����Ĵ�����	
		addrConnect		Ҫ���ӵķ����
	--------------------------------------------------------------------------*/
	void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);

	// ��Ӧ���ͳɹ�
	void OnSend(const CMemBlock* pSendBlock);

	// ��Ӧ����ʧ�ܣ�
	void OnSendFailed(const CMemBlock* pSendBlock);

	// ��Ӧ�رշ����
	void OnClose(CLOSE_TYPE iCloseType);

private:

	// ����һЩ���õ� SOCKET ����
	void set_sock_opt(SOCKET s);

	// �жϰ�����Ч��
	int is_packeg_valid(const BYTE* pData, int iDataLen);

	// ������ԭ�Ӱ����� n ���С���ϳ�һ�������İ�
	int make_atom_msg_block_Old(int iResult, const CMemBlock* pRecv);

	// ������ԭ�Ӱ����� n ���С���ϳ�һ�������İ�
	int make_atom_msg_block(int iResult, const CMemBlock* pRecv);

	// �����Ч��
	inline bool is_valid();

	// ������ɣ����۷��ͳɹ���ʧ�ܣ���Ϣ�鶼���ɿ��ϵͳ�Զ����
	void OnSendComplete(CClientSendResult*& pSendResult, int iResult, CMemBlock*& pSendBlock); 

	// IOCP �Ĺ����߳�
	static unsigned __stdcall thread_work(LPVOID lpParameter);

	// ���ӷ�����
	DWORD connect_to_server();

	// �����������Ҫ��Ӧ����Ϣ������Ϣ��Terminate
	DWORD server_operate();

	// ��ʱ�����߳�
	static unsigned __stdcall thread_check(LPVOID lpParameter);

public:
	CMemBlockPool*		m_pMsgPool;				// ��Ϣ��
	int					m_iMsgPoolInitCount;	// ��Ϣ�ص����Ԫ������

private:
	CCoreClient*	m_pCoreClient;	// ������ָ��

	sockaddr_in		m_addrConnect;

	volatile SOCKET	m_hConnection;
	HANDLE			m_hCompletionPort;
	HANDLE			m_hThread;
	unsigned int	m_dwThreadId;

	HANDLE			m_hThreadAfterConn;		// ���ӳɹ�����߳�
	unsigned int	m_dwThreadAfterConn;	// ���ӳɹ�����߳�ID

	volatile LONG	m_iIsConnect;			// 1��ʾ�����У�0��ʾ����
	volatile bool	m_bStop;
	CLOSE_TYPE		m_iCloseType;	// �رշ�ʽ���ο� CLOSE_TYPE ��

	bool			m_bAutoReConnect;		// ���ߺ��Զ�����
	int				m_iAutoReConnectTime;	// ���ߺ��Զ������ļ��ʱ�䣬��λms�������ߺ����ms�����ٴ�����

	int				m_nRecvBufNonius;

	CMemBlock*	m_pStoreBox;	// ��Ϣ�洢�䣬���С���ϳ�һ��ԭ�Ӱ���
								// ���Է����� CRecvResult::recv_data() �����е� wsabuf.len = 3;	

	int		m_iMsgBlockSize;	// ��Ϣ��ĳ���

	CLightweightPool<CClientSendResult>*	m_pSendResultPool;			// ���ͽ����
	int										m_iSendResultPoolInitCount;	// ���ͽ���ص����Ԫ������

	CClientRecvResult	m_stRecvResult;
	CTerminateResult	m_stTerminateResult;

	CSRWLock			m_lockRecvComplete;	// �� OnRecvComplete �ģ�������Ƕ��
	CCriticalSpection  m_lockClose;			// �� Close �ģ�Ϊ�˰�ȫ������Ƕ�ף�

	LONGLONG	m_lConnectSuccedCount;	// ���ӳɹ��Ĵ����������ж��Ƿ��������

	HANDLE			m_hThreadShrinkPool;		// ��ʱ�����߳�
	unsigned int	m_uThreadShrinkPoolId;		// ��ʱ�����߳�ID

	LONGLONG		m_iShrinkPoolsiPulseCount;	// �������ֳص��������
	LONGLONG		m_iSendHeartbeatPulseCount;	// �������������������

	long long	m_iPulseCount;	// ���������

};

// �����Ч��
bool CCommTcpClient::is_valid()
{
	if(m_iIsConnect && INVALID_SOCKET!=m_hConnection)
		return true;
	else
		return false;	
}

#endif