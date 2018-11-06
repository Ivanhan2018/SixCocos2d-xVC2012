
#ifndef CORE_SERVER_H
#define CORE_SERVER_H

#include <WinSock2.h>

#include "./MemBlockPool.h"
#include "./CoreTimer.h"
#include "./Log.h"
#include "./CloseType.h"

class __declspec(dllexport)  CCommTcpServer;
class __declspec(dllexport) CGeneralWork;
class __declspec(dllexport) CGeneralDB;

#include <hash_map>
using std::hash_map;
using std::pair;

#define USE_NEW_WORKER 1	// 1 ��ʾ�������͵� CGeneralWork ��ͨ�����빤���̰߳󶨣��ϸ����ء������ִ����˳�� 
							// 0 ��ʾ�þɵ� CBasicLogic ��ͨ�����빤���̲߳��󶨣�����֡������ꡱ������ 

#define ALLOW_STRONG_CLOSE_PEER 1	// 1 ��ʾ����ǿӲ�رնԶˣ����ڲ���ʱ�ô�ֵ
									// 0 ��ʾ��ֹǿӲ�رնԶˣ�����ʱ�ô�ֵ 

class __declspec(dllexport) CCoreServer
{
public:
	CCoreServer(void);
	~CCoreServer(void);
public:
	enum{
		ERR_CS_exist_work_module = 10,		//  �Ѵ�������ģ��ID��������Ψһ�ģ������ظ�

		};

public:

	//--- ���麯�� ------------------------------------------

	// ��ʼ
	virtual int start() = 0;

	// ����
	virtual int stop();

	// ������Ϣ��ĳ���
	void set_msg_block_size(int iMsgBlockSize=2048);

	// ������Ϣ�ص����Ԫ������
	void set_msg_pool_init_count(int iMsgPoolInitCount);

	//--- TCP ͨѶ������ú��� ------------------------------------------

	// ���ü�����ַ
	void set_listen_addr(const char* szListenAddr);

	// ���ü����˿�
	void set_listen_port(unsigned int nPort);

	// ���ⲿ������Ϣ��
	int set_msg_pool(CMemBlockPool* pMsgPool);

	// ���öԶ˷���ص����Ԫ������
	void set_service_handle_pool_init_count(int iServerHandlePoolInitCount);

	// �������ӽ���ص����Ԫ������
	void set_accept_result_pool_init_count(int iAcceptResultPoolInitCount);

	// ���÷��ͽ���ص����Ԫ������
	void set_send_result_pool_init_count(int iSendResultPoolInitCount);

	// �����������ֳص�ʱ�䣬iShrinkPoolsTime �� ms Ϊ��λ
	void set_shrink_pools_time(LONGLONG iShrinkPoolsTime);

	// ������������ʱ�䣬�� PULSE_TIME ����Ϊ������λ���� N �� PULSE_TIME ���һ��
	void set_heartbeat_check_time(LONGLONG iHeartbeatCheckTime);

	// ����������������ʱ�䣬�� ms Ϊ��λ���� N ms ֮�ڿͻ���û���κ���Ϣ����������Ϊ�ÿͻ���������
	void set_no_heartbeat_die_time(int iNoHeartbeatDieTime);

	// ��ʾ���еĳ���Ϣ
	void display_all_pool();

	// �������ݿ�������ʱ��
	void set_db_heartbeat_time(int iDbHeartbeatTime);

	// ���� IOCP �����̵߳�����
	void set_work_thread_count(int iCount);

	// ������־��·��
	int set_log_path(TCHAR* pszPathName);

	/* --------------------------------------------------------------------------
	����˵�������ͣ����Ƽ���
	���������
		lChannelNo	ͨ����
		pSendBlock	���͵���Ϣ�飬ע�⣺���۷��ͳɹ���ʧ�ܿ��ϵͳ���Ὣ pSendBlock �Զ���أ�                              
	����ֵ��
		�ɹ��򷵻� 0�����һ�ص� OnSend ���������������IO����
		ʧ�ܻ�ص� OnSendFailed ���������ش��������£�
			10  ��Ч��ͨ����
			20  pMemBlock ����ʧ��
			30  pSendResult ����ʧ��
			40  pMemBlock->copy ʧ��
			80  WSASend ʧ��
	--------------------------------------------------------------------------*/
	int send_data(LONGLONG lChannelNo, CMemBlock*& pSendBlock);

	/* --------------------------------------------------------------------------
	����˵�������ز����ͣ�Ч�ʵͣ����á����ز����ͣ��˺���Ч�ʵͣ����á�ͨ��������ͻ���һ���Դ������������ݣ����緢���û��б��ĳ��ϡ�
	���������
		lChannelNo	ͨ����
		iMainCode	��Ϣ����
		iSubCode	��Ϣ������
		pData		��������
		iDataLen	�������ݵĳ���                               
	����ֵ��
		�ɹ��򷵻� 0�����һ�ص� OnSend ���������������IO����
		ʧ�ܻ�ص� OnSendFailed ���������ش��������£�
			10  ��Ч��ͨ����
			20  pMemBlock ����ʧ��
			30  pSendResult ����ʧ��
			40  pMemBlock->copy ʧ��
			80  WSASend ʧ��
	��ע��
		��Ϊ������Ҫ��Ϣ���أ����Ե�Ч��
		��Ч���������� OnRecv ��ʵ������װ�����ݺ�ֱ�ӻط���
	--------------------------------------------------------------------------*/
	int retrieve_send_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, BYTE* pData=NULL, int iDataLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	// TCP�㲥�����������ݵ����е���Ч�Զ�
	int tcp_broadcase(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	// TCP�㲥�����������ݵ����е���Ч�Զ�
	int tcp_broadcase(CMemBlock*& pSendBlock);

	// ������жԶ˵�����
	int check_all_peer_heartbeat();

	#if ALLOW_STRONG_CLOSE_PEER
		// �ر�ָ���ĶԶˣ��� power_close_peer ����
		int close_peer(LONGLONG lChannelNo);
	#endif

	/* --------------------------------------------------------------------------
	����˵���������ر�ָ���ĶԶˣ��ͻ��˲�����ִ�ж�������
	���������
		lChannelNo	ͨ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	��ע��
		�ڿͻ����յ���Ϣ�������ط���������յ���Ϣ��Ҳ�����ط�������£� 
		����˷��� closesocket ָ��ǿ�ƹرտͻ��ˣ��ͻ���ȴ�޷���Ӧ�ر��¼�??? 
	--------------------------------------------------------------------------*/
	int power_close_peer(LONGLONG lChannelNo);

	// �ر����еĶԶ�
	void close_all_peer();

	// ͳ�ƽ��յ����ʣ��Ǹ������Ŀ���
	void statistic_recv_rate();

	//--- TCP ͨѶ��ص����� ------------------------------------------

	// ������Ӧ
	virtual int OnIsHeartbeat(LONGLONG lChannelNo) = 0;

	// ��Ӧ�Զ��ѹر���
	virtual int OnClose(LONGLONG lChannelNo, SOCKET socketClose, CLOSE_TYPE iCloseType) = 0;

	// ��Ӧ���ͳɹ�
	virtual void OnSend(LONGLONG lChannelNo, const CMemBlock* pSendBlock) = 0;

	// ��Ӧ����ʧ��
	virtual void OnSendFailed(LONGLONG lChannelNo, const CMemBlock* pSendBlock) = 0;

	// ��Ӧ���ӳɹ�
	virtual void OnConnect(LONGLONG lChannelNo, const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr) = 0;	

	// ��Ӧ����ʧ��
	virtual void OnConnectFail(const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr, int iErrorCode) = 0;

	// ��ʱ����Ӧ
	virtual int OnTimer(LONGLONG iIDEvent) = 0;

	/* --------------------------------------------------------------------------
	����˵������Ӧ����������
	���������
		lChannelNo	������˶Ͽ���ͨ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	virtual int OnNoHeartbeatDie(LONGLONG lChannelNo) = 0;

	/* --------------------------------------------------------------------------
	����˵������Ӧ�հ���Ϣ�����������ϸ��ա������ִ����ԭ����ִ�еģ�������˵������IOCP����Ĺ����߳��ڵ��ñ�����
	���������
		lChannelNo
	����������
		pRecv		��Ϣ�飬�Ѿ���ԭ�Ӱ��ˡ�ע�⣺Ҫ�õײ��ܵĻ��ƹ�ء�
	--------------------------------------------------------------------------*/
	virtual void OnRecv(LONGLONG lChannelNo, CMemBlock*& pRecv) = 0;

	//--- �ؼ����� ------------------------------------------

	/* --------------------------------------------------------------------------
	����˵������ʼ���������� start ����֮ǰִ�б��������γ� init() start() ... stop() uinit() ��˳��
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10  ������Ϣ��ʧ��
	--------------------------------------------------------------------------*/
	virtual int init();
	
	/* --------------------------------------------------------------------------
	����˵�����ͷ���Դ�������� stop ����֮��ִ�б��������γ� init() start() ... stop() uinit() ��˳��
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10  ������Ϣ��ʧ��
	--------------------------------------------------------------------------*/
	virtual int uninit();

	// ��ӡ��Ϣ��
	void display_msg_pool();

	// ע�Ṥ��ģ�飬���������ݿ⹤��ģ��
	int regist_work_module(int iGeneralWorkID, CGeneralWork* pGeneralWork, CCoreServer* pCoreServer);

	// Ͷ��������Ϣ������ϢͶ��ָ���Ĺ���ģ��
	TASK_MSG_RESULT post_work_msg(int iGeneralWorkID, CMemBlock*& pMsgBlock);

	/* --------------------------------------------------------------------------
	����˵����ע������ģ�飬�������߼����������ݿ�����
	���������
		iTaskModuleID	����ģ��ID
		pTask			����ģ���ָ��
		bIsDB			�Ƿ����ݿ�
	����ֵ��
		�ɹ��򷵻� 0������pTask ���ǿ�ֵ��
		ʧ�ܷ��ش����룬���� pTask Ϊ��ֵ�����������£�
			10  �Ѵ�������ģ��ID��������Ψһ�ģ������ظ�
	--------------------------------------------------------------------------*/
	int regist_task_module(int iTaskModuleID, CBasicLogic* pTask, CCoreServer* pCoreServer);

	/* --------------------------------------------------------------------------
	����˵����Ͷ��������Ϣ������ϢͶ��ָ��������ģ��
	���������
		iTaskModuleID	����ģ��ID
		bIsFront		TRUE ��ʾ�ӵ�˫����е�ͷ����FALSE ��ʾ�ӵ�˫����е�β��
	����������
		pMsgBlock		��Ϣ��
	����ֵ��
		���زο� TASK_MSG_RESULT ö��
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT post_task_msg(int iTaskModuleID, CMemBlock*& pMsgBlock, BOOL bIsFront=FALSE);

	/* --------------------------------------------------------------------------
	����˵�������ö�ʱ��/�޸Ķ�ʱ��
	���������
		iIDEvent	��ʱ��ID������ܲ����ڴ˶�ʱ��ʱ�������ö�ʱ��������ܴ��ڴ˶�ʱ��ʱ�����޸Ĵ˶�ʱ���ļ��
		iElapse		��Ӧʱ�䣬�� ms Ϊ��λ������Ϊ 50 ms
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int set_timer(LONGLONG nIDEvent, int nElapse);

	/* --------------------------------------------------------------------------
	����˵����������ʱ��
	���������
		iIDEvent	��ʱ��ID
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	������ iIDEvent
	--------------------------------------------------------------------------*/
	int kill_timer(LONGLONG iIDEvent);

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

	/* --------------------------------------------------------------------------
	����˵����д����־���
	���������
		iType	���ͣ��ο� LOG_ERR_TYPE ö�٣�
					LOG_TYPE_PROMPT = 0,	// ��ʾ
					LOG_TYPE_WARING = 1,	// ����
					LOG_TYPE_ERR = 2,		// �������쳣

		pszSentence		��־���
		iSentenceLen	��־���ĳ���
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int write_log(int iType, TCHAR* pszSentence, int iSentenceLen);

public:
	//--- ����ר�� ------------------------------------------

private:

	// �������ݿ������߳�
	static unsigned __stdcall  thread_db_heartbeat(void* pParam);

public:
	CMemBlockPool*	m_pMsgPool;		// ��Ϣ��	

private:	

	CCommTcpServer* m_pTcpService;	// TCP ͨѶ�㣬�޷��� CCoreServer ������ֱ��ʹ�ã�����˵��δ����ı�����
									// ֻ��ͨ�� CCoreServer �ĺ�������װ CCommTcpServer �еĹ���

	CCoreTimer*		m_pCoreTimer;	// �ں˶�ʱ��

	wstring		m_strPath;	// ��־��·��
	CLog*		m_pLogPrompt;	// ��ʾ��־��
	CLog*		m_pLogWaring;	// ������־��
	CLog*		m_pLogErr;		// �������쳣��־

private:
	int				m_iMsgPoolInitCount;	// ��Ϣ�ص����Ԫ������
	int				m_iMsgBlockSize;		// ��Ϣ��ĳ���

private:
	
	typedef hash_map<int, CGeneralWork*> MAP_GENERAL_WORK_TYPE;
	typedef pair <int, CGeneralWork*>	 PAIR_GENERAL_WORK_TYPE;	// ��ֵ��
	MAP_GENERAL_WORK_TYPE	m_mapWork;	// ����ģ��Ⱥ

public:
	enum{ DbEventCount = 2,	};	// �¼�������

	HANDLE			m_hDbHeartbeatStop;	// �����������ݿ��������߳�
	HANDLE			m_hDbThread;		// ���ݿ��������߳�
	unsigned int	m_dwDbThreadID;		// ���ݿ��������߳�ID

	int		m_iDbHeartbeatTime;	// �������ݿ�������ʱ��

public:
	long long m_lCurrentChannel;	// ��ǰͨ����
};

#endif