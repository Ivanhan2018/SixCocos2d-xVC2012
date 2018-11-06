/********************************************************************
	created:	2013/01/24
	created:	20:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef SERVICE_HANDLE_H
#define SERVICE_HANDLE_H

#include "./PublicHead.h"

#include "./CoreHead.h"

#include "./RecvResult.h"
#include "./SendResult.h"

#include "./ThreadGuard.h"
#include "./ThreadGuardEx.h"

#include "./MemBlockPool.h"
#include "./CloseType.h"

class CCommTcpServer;

#define CORE_RETRIVE_MSG_TEXT 1 // 1 ��ʾ�ں˳��ؼ��� __FUNCTION__ �ִ������ڼ��δ��ص���Ϣ�顣����Ӫʱ�����1ֵ��
								// 0 ��ʾ�ں˲����δ��ص���Ϣ�飬�����ٶȻ��ܶࡣ����Ӫһ��ʱ��о��ȶ��󣬿��Ըĳ�0ֵ��

#define ERROR_PACKAGER_CUT 0	// 1 ��ʾ��������Ͽ��Զˣ��ŵ㣺���Զ˷��ܴ�Ĵ�������й����������ᱻ����˶Ͽ���������������ǿһЩ
								// 0 ��ʾ������ݶԶˣ����Ͽ����ȴ���һ����ȷ�İ�����ȱ�㣺���Զ˷��ܴ�Ĵ�������й�������ʹ����˵�ѹ��˲�����úܴ�


// һ���Զ˷���
class __declspec(dllexport) CServerHandle
{
public:
	

	friend class CChennelNoMgr;
	friend class CCommTcpServer;
	friend class CRecvResult;

	enum{	ERROR_PACKAGER_UP_LIMIT = 5,	};	// ���������ֵ���������޴����ͶϿ�

	enum { MAX_PENDING_IO = 500,
		 };

	// ���ͻ��壬ϵͳĬ�ϵ�״̬���ͺͽ���һ��Ϊ8688�ֽ�(ԼΪ8.5K)��
	// ��ʵ�ʵĹ����з������ݺͽ����������Ƚϴ󣬿�������socket����������������send(),recv()���ϵ�ѭ���շ���
	enum{	SEND_BUF_SIZE=128*1024 };

	// ���ջ���
	enum{	RECV_BUF_SIZE=128*1024 };

	
	//enum{	IS_CLIENT_POWER_CLOSE = 5,	// ��ʾ�ͻ��������ر�
	//};

public:
	CServerHandle(void);
	~CServerHandle(void);

	void test();

	// ���� CCommTcpServer ָ��
	void set_comm_tcp_server(CCommTcpServer*	pCommTcpServer);

	// ������Ϣ��ĳ���
	void set_msg_block_size(int iMsgBlockSize);

	// ���ùر�����
	inline void set_close_type(CLOSE_TYPE iCloseType);

	// ��ùر�����
	inline CLOSE_TYPE get_close_type();

	// �µ�һ������ʱ��ʼ��һЩֵ
	void init_when_open();

	int	open(sockaddr_in& saLocalAddr, sockaddr_in& saRemoteAddr);

	// ���ͨ����
	inline LONGLONG get_channel_id();

	// ����ͨ����
	inline void	 set_channel_id(LONGLONG lChannelNo);

	int				new_handle();
	inline SOCKET	get_handle();

	// �������
	int OnRecvComplete(int iResult, const CMemBlock* pRecv);

	// �����Ч��
	inline BOOL is_valid();

	// ��������
	int send_data(CMemBlock*& pSendBlock);

	// �������
	void OnSendComplete(CSendResult*& pSendResult, int iResult, CMemBlock*& pSendBlock);

	// �������
	int check_heartbeat();

public:		
	//--- �ص����� ------------------------

	// �жϰ�����Ч��
	int is_packeg_valid(const BYTE* pData, int iDataLen);

	// ������ԭ�Ӱ����� n ���С���ϳ�һ�������İ�
	int make_atom_msg_block(int iResult, const CMemBlock* pRecv);



private:

	// �رնԶ�
	BOOL close(CLOSE_TYPE iCloseType);

	// ����һЩ���õ� SOCKET ����
	void CServerHandle::set_sock_opt(SOCKET s);

public:
	volatile LONGLONG m_lHeartbeatTime;	// ����ʱ��

	LONGLONG	m_lChannelNo;	// ͨ����Զ˷�����йأ������ٿ�����
	SOCKET		m_hSocket;	
	
	LONGLONG	m_iPowerClosePeerTime;	// �����رնԶ˵�ʱ��

private:
	sockaddr_in	m_saLocalAddr;
	sockaddr_in	m_saRemoteAddr;

	BOOL m_bIsOpen;	// ���� open �������ҳɹ�

	volatile int	m_nPendingIo;

	int		m_nRecvBufNonius;

	CMemBlock*	m_pStoreBox;	// ��Ϣ�洢�䣬���С���ϳ�һ��ԭ�Ӱ���
								// ���Է����� CRecvResult::recv_data() �����е� wsabuf.len = 16;	

	int		m_iMsgBlockSize;	// ��Ϣ��ĳ���

	CRecvResult	m_stRecvResult;	// ���ս��

	CSRWLock	m_lockRecvComplete;	// �� OnRecvComplete �ģ�������Ƕ��
	
	CCriticalSpection  m_lockClose;	// �� Close �ģ�Ϊ�˰�ȫ������Ƕ�ף�

	CCommTcpServer*	m_pCommTcpServer;

	CLOSE_TYPE		m_iCloseType;	// �رշ�ʽ���ο� CLOSE_TYPE ��

	int				m_iVerifyFailCount;	// ��Ч��ʧ�ܵĴ���
};

// �����Ч��
BOOL CServerHandle::is_valid()
{
	if(m_bIsOpen && INVALID_SOCKET!=m_hSocket)
		return TRUE;
	else
		return FALSE;
}

LONGLONG CServerHandle::get_channel_id()
{
	return m_lChannelNo;
}

// ����ͨ����
void CServerHandle::set_channel_id(LONGLONG lChannelNo)
{
	m_lChannelNo = lChannelNo;
}

SOCKET CServerHandle::get_handle()
{
	return m_hSocket;
}

#endif