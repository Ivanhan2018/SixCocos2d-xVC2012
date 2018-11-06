
#include "./CoreServer.h"
#include "./PublicHead.h"

#include "process.h"

#include "./CommTcpServer.h"	// ����ļ����ܷ��� CoreServer.h �У������ᵼ�� CCoreServer �ļ̳����޷����� CSingleton �������ģʽ��ͨ��
#include "./BasicDB.h"
#include "./GeneralDB.h"

CCoreServer::CCoreServer(void)
{
	m_pTcpService = NULL;	// TCP ͨѶ��
	m_pCoreTimer = NULL;	// �ں˶�ʱ��

	m_lCurrentChannel = INVALID_CHANNEL_NO;

	// ��Ϣ��
	m_pMsgPool = NULL;
	m_iMsgBlockSize = 2048;		// ��Ϣ��ĳ���
	m_iMsgPoolInitCount = 256;	// ��Ϣ�ص����Ԫ������

	m_pTcpService = new CCommTcpServer;
	assert(m_pTcpService);

	m_pLogPrompt = NULL;	// ��ʾ��־��
	m_pLogWaring = NULL;	// ������־��
	m_pLogErr = NULL;		// �������쳣��־

	m_hDbHeartbeatStop = CreateEvent(NULL, FALSE, FALSE, NULL);	// 
	m_iDbHeartbeatTime = 30*1000;	// �������ݿ�������ʱ��

	m_strPath = _T("Server_Log\\");

	
}

CCoreServer::~CCoreServer(void)
{
	// ������Դ

	
}

// ������Ϣ��ĳ���
void CCoreServer::set_msg_block_size(int iMsgBlockSize)
{
	m_iMsgBlockSize = iMsgBlockSize;
}

// ������Ϣ�ص����Ԫ������
void CCoreServer::set_msg_pool_init_count(int iMsgPoolInitCount)
{
	m_iMsgPoolInitCount = iMsgPoolInitCount;	
}

// ���ü�����ַ
void CCoreServer::set_listen_addr(const char* szListenAddr)
{
	assert(m_pTcpService);
	m_pTcpService->set_listen_addr(szListenAddr);
}

// ���ü����˿�
void CCoreServer::set_listen_port(unsigned int nPort)
{
	assert(m_pTcpService);
	m_pTcpService->set_listen_port(nPort);
}

// ���ⲿ������Ϣ��
int CCoreServer::set_msg_pool(CMemBlockPool* pMsgPool)
{
	assert(m_pTcpService);
	return m_pTcpService->set_msg_pool(pMsgPool);
}

// ���öԶ˷���ص����Ԫ������
void CCoreServer::set_service_handle_pool_init_count(int iServerHandlePoolInitCount)
{
	assert(m_pTcpService);
	m_pTcpService->set_service_handle_pool_init_count(iServerHandlePoolInitCount);
}

// �������ӽ���ص����Ԫ������
void CCoreServer::set_accept_result_pool_init_count(int iAcceptResultPoolInitCount)
{
	assert(m_pTcpService);
	m_pTcpService->set_accept_result_pool_init_count(iAcceptResultPoolInitCount);
}

// ���÷��ͽ���ص����Ԫ������
void CCoreServer::set_send_result_pool_init_count(int iSendResultPoolInitCount)
{
	assert(m_pTcpService);
	m_pTcpService->set_send_result_pool_init_count(iSendResultPoolInitCount);
}

// �����������ֳص�ʱ�䣬iShrinkPoolsTime �� ms Ϊ��λ
void CCoreServer::set_shrink_pools_time(LONGLONG iShrinkPoolsTime)
{
	assert(m_pTcpService);
	m_pTcpService->set_shrink_pools_time(iShrinkPoolsTime);
}

// ������������ʱ�䣬�� PULSE_TIME ����Ϊ������λ���� N �� PULSE_TIME ���һ��
void CCoreServer::set_heartbeat_check_time(LONGLONG iHeartbeatCheckTime)
{
	assert(m_pTcpService);
	m_pTcpService->set_heartbeat_check_time(iHeartbeatCheckTime);
}

// ����������������ʱ�䣬�� ms Ϊ��λ���� N ms ֮�ڿͻ���û���κ���Ϣ����������Ϊ�ÿͻ���������
void CCoreServer::set_no_heartbeat_die_time(int iNoHeartbeatDieTime)
{
	assert(m_pTcpService);
	m_pTcpService->set_no_heartbeat_die_time(iNoHeartbeatDieTime);
}

// �������ݿ�������ʱ��
void CCoreServer::set_db_heartbeat_time(int iDbHeartbeatTime)
{
	m_iDbHeartbeatTime = iDbHeartbeatTime;
}

// ���� IOCP �����̵߳�����
void CCoreServer::set_work_thread_count(int iCount)
{
	assert(m_pTcpService);
	m_pTcpService->set_work_thread_count(iCount)  ;
}

// ������־��·��
int CCoreServer::set_log_path(TCHAR* pszPathName)
{
	if(!pszPathName)
		return 10;

	m_strPath = pszPathName;

	return 0;
}

// ����
int CCoreServer::send_data(LONGLONG lChannelNo, CMemBlock*& pSendBlock)
{
	assert(m_pTcpService);
	return m_pTcpService->send_data(lChannelNo, pSendBlock)  ; 
}

// ���ز����ͣ�Ч�ʵͣ����á����ز����ͣ��˺���Ч�ʵͣ����á�ͨ��������ͻ���һ���Դ������������ݣ����緢���û��б��ĳ��ϡ�
int CCoreServer::retrieve_send_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, BYTE* pData, int iDataLen, char* pszTextMark, BOOL bIsWait)
{
	assert(m_pTcpService);
	return m_pTcpService->retrieve_send_data(lChannelNo, iMainCode, iSubCode, pData, iDataLen, pszTextMark, bIsWait)  ; 
}

// TCP�㲥�����������ݵ����е���Ч�Զ�
int CCoreServer::tcp_broadcase(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	assert(m_pTcpService);
	return m_pTcpService->tcp_broadcase(iMainCode, iSubCode, pData, iDataLen)  ;
}

// TCP�㲥�����������ݵ����е���Ч�Զ�
int CCoreServer::tcp_broadcase(CMemBlock*& pSendBlock)
{
	assert(m_pTcpService);
	return m_pTcpService->tcp_broadcase(pSendBlock)  ;
}

// ������жԶ˵�����
int CCoreServer::check_all_peer_heartbeat()
{
	assert(m_pTcpService);
	return m_pTcpService->check_all_peer_heartbeat()  ;
}

#if ALLOW_STRONG_CLOSE_PEER
	// �ر�ָ���ĶԶˣ��� power_close_peer ����
	int CCoreServer::close_peer(LONGLONG lChannelNo)
	{
		assert(m_pTcpService);
		return m_pTcpService->close_peer(lChannelNo)  ;
	}
#endif

// �����ر�ָ���ĶԶˣ��ͻ��˲�����ִ�ж�������
int CCoreServer::power_close_peer(LONGLONG lChannelNo)
{
	assert(m_pTcpService);
	return m_pTcpService->power_close_peer(lChannelNo)  ;
}

// �ر����еĶԶ�
void CCoreServer::close_all_peer()
{
	assert(m_pTcpService);
	m_pTcpService->close_all_peer()  ;	
}

// ͳ�ƽ��յ����ʣ��Ǹ������Ŀ���
void CCoreServer::statistic_recv_rate()
{
	assert(m_pTcpService);
	m_pTcpService->statistic_recv_rate()  ;
}

// ��ʼ���������� start ����֮ǰִ�б��������γ� init() start() ... stop() uinit() ��˳��
int CCoreServer::init()
{
	int iResult = 0;

	// ��Ϣ��
	{
		m_pMsgPool = new CMemBlockPool(m_iMsgBlockSize, m_iMsgPoolInitCount, 20*m_iMsgPoolInitCount);		
		if(m_pMsgPool)
			m_pMsgPool->init();
		else
			return 10;	// ������Ϣ��ʧ��
	}

	// TCP ͨѶ��
	{
		assert(m_pTcpService);

		// ����������ָ��
		m_pTcpService->set_core_server(this);

		// ���ⲿ������Ϣ��
		m_pTcpService->set_msg_pool(m_pMsgPool);

		iResult = m_pTcpService->init();
		assert(0==iResult);

		iResult = m_pTcpService->start();
		assert(0==iResult);
	}

	// �ں˶�ʱ��
	{
		m_pCoreTimer = new CCoreTimer;
		assert(m_pCoreTimer);

		// ����������ָ��
		m_pCoreTimer->set_core_server(this);

		m_pCoreTimer->set_msg_pool(m_pMsgPool);			
		
		m_pCoreTimer->start_timer();
	}

	// ��ʾ��־
	{
		m_pLogPrompt = NULL;
		m_pLogPrompt = new CLog(_T("Prompt_"));
		assert(m_pLogPrompt);

		m_pLogPrompt->set_path(m_strPath);

		iResult = m_pLogPrompt->start_log();	// ��������ģ�飬�˾䲻��ʡ��
		assert(0==iResult);
	}

	// ������־
	{
		m_pLogWaring = NULL;
		m_pLogWaring = new CLog(_T("Waring_"));
		assert(m_pLogWaring);

		m_pLogWaring->set_path(m_strPath);

		iResult = m_pLogWaring->start_log();	// ��������ģ�飬�˾䲻��ʡ��
		assert(0==iResult);
	}

	// �������쳣��־
	{
		m_pLogErr = NULL;
		m_pLogErr = new CLog(_T("ErrCatch_"));
		assert(m_pLogErr);

		m_pLogErr->set_path(m_strPath);

		iResult = m_pLogErr->start_log();	// ��������ģ�飬�˾䲻��ʡ��
		assert(0==iResult);
	}

	// �������߳�
	m_hDbThread = (HANDLE)_beginthreadex( NULL, 0, &thread_db_heartbeat, (void*)this, 0, &m_dwDbThreadID );

	return 0;
}

// ֹͣ
int CCoreServer::stop()
{
	int iResult = 0;

	iResult = m_pTcpService->stop();
	assert(0==iResult);

	// �ͷ�ͨѶ��
	delete m_pTcpService;
	m_pTcpService = NULL;

	// �ں˶�ʱ��
	iResult = m_pCoreTimer->stop_timer();
	assert(0==iResult);
	delete m_pCoreTimer;

	iResult = m_pLogPrompt->stop_log();
	assert(0==iResult);
	delete 	m_pLogPrompt;

	iResult = m_pLogWaring->stop_log();
	assert(0==iResult);
	delete 	m_pLogWaring;

	iResult = m_pLogErr->stop_log();
	assert(0==iResult);
	delete 	m_pLogErr;

	SetEvent(m_hDbHeartbeatStop);
	DWORD dwResult = WaitForSingleObject(m_hDbThread, 60*1000);	// �ȴ��̳߳��׵Ľ���

	return iResult;
}

// �ͷ���Դ�������� stop ����֮��ִ�б��������γ� init() start() ... stop() uinit() ��˳��
int CCoreServer::uninit()
{
	// �ͷ���Ϣ��
	if(m_pMsgPool)
	{
		m_pMsgPool->uninit();
		delete m_pMsgPool;
	}

	return 0;
}

// �������ݿ������߳�
unsigned __stdcall  CCoreServer::thread_db_heartbeat(void* pParam) 	
{
	CCoreServer* pThis = (CCoreServer*)pParam;	// ��ǰ�̵߳�ID

	DWORD hThreadID = ::GetCurrentThreadId();	// ��õ�ǰ�߳�ID

	while(true)
	{
		DWORD dwResult = WaitForSingleObject(pThis->m_hDbHeartbeatStop, pThis->m_iDbHeartbeatTime);
		switch(dwResult)
		{
		case WAIT_TIMEOUT:	// ����ʱ��Ϊ�������ݿ�������ʱ����
			{
				MAP_GENERAL_WORK_TYPE::iterator iter = pThis->m_mapWork.begin();

				for( ; iter!=pThis->m_mapWork.end(); iter++)	// �������е��߼����������ݿ�����
				{
					CGeneralWork* pWork = (CGeneralWork*)(*iter).second;

					if(pWork->m_bIsDB)	// ���ݿ�����
					{
						CGeneralDB* pDb = (CGeneralDB*)pWork;

						// �����ݿⷢ����������Ϊ���ݿ��ڳ�ʱ��ò������ʾͻ��Զ�����
						pDb->db_heartbeat();
					}
				}
				
				break;
			}
		case WAIT_OBJECT_0:	// �յ���������Ϣ
			{
				return 0;
			}
		}
	}

	return 0;
}

// ��ӡ��Ϣ��
void CCoreServer::display_msg_pool()
{
	printf(" MsgPool��       ������=%9d �����=%9d ���ڵ�ǰԪ��=%9d \n",
		m_pMsgPool->get_retrieve_count(),
		m_pMsgPool->get_recycle_count(),
		m_pMsgPool->get_current_element_count()
		);
}

// ��ʾ���еĳ���Ϣ
void CCoreServer::display_all_pool()
{
	m_pTcpService->display_all_pool();
}

// ע�Ṥ��ģ�飬���������ݿ⹤��ģ��
int CCoreServer::regist_work_module(int iGeneralWorkID, CGeneralWork* pGeneralWork, CCoreServer* pCoreServer)
{
	assert(pCoreServer);
	assert(pGeneralWork);

	MAP_GENERAL_WORK_TYPE::iterator iter;

	iter = m_mapWork.find(iGeneralWorkID);

	if( iter != m_mapWork.end())	// �ҵ���
	{
		return ERR_CS_exist_work_module;	// �Ѵ�������ģ��ID��������Ψһ�ģ������ظ�
	}

	if(pGeneralWork)
	{
		pGeneralWork->set_core_server(pCoreServer);
		m_mapWork.insert(PAIR_GENERAL_WORK_TYPE(iGeneralWorkID, pGeneralWork));
	}

	return 0;
}

// Ͷ��������Ϣ������ϢͶ��ָ���Ĺ���ģ��
TASK_MSG_RESULT CCoreServer::post_work_msg(int iGeneralWorkID, CMemBlock*& pMsgBlock)
{
	// ��Ϊ�� regist_task_module ֮�󣬲��������ӻ��Ƴ�����ģ�����������Բ��ü���

	TASK_MSG_RESULT stRes = TMR_ERROR;

	if (NULL==pMsgBlock)
	{
		return stRes;
	}

	MAP_GENERAL_WORK_TYPE::iterator iter;

	iter = m_mapWork.find(iGeneralWorkID);

	if( iter != m_mapWork.end())	// �ҵ���
	{
		CGeneralWork* p = (CGeneralWork*)(*iter).second;
		if(0==p->handle_msg(pMsgBlock))
		{
			stRes = TMR_CONTINUE_PUT;
		}
		else
		{
			m_pMsgPool->recycle(pMsgBlock);
		}
	}

	return stRes;
}

// ���ö�ʱ��/�޸Ķ�ʱ��������ܲ����ڴ˶�ʱ��ʱ�������ö�ʱ��������ܴ��ڴ˶�ʱ��ʱ�����޸Ĵ˶�ʱ���ļ��
int CCoreServer::set_timer(LONGLONG iIDEvent, int iElapse)
{
	assert(m_pCoreTimer);
	if(!m_pCoreTimer)
		return 10;

	m_pCoreTimer->set_timer(iIDEvent, iElapse);

	return 0;
}

int CCoreServer::kill_timer(LONGLONG iIDEvent)
{
	assert(m_pCoreTimer);
	if(!m_pCoreTimer)
		return 10;

	m_pCoreTimer->kill_timer(iIDEvent);

	return 0;
}

// д����־���
int CCoreServer::write_log(BOOL bShowInScreen, int iType, char* pszSentence, int iSentenceLen)
{
	int iRes = 0;
	wstring wstrRes;

	// ���ֽ��ִ�ת�ɿ��ֽ��ִ�
	iRes = COften::EasyMultiByteToWideChar(pszSentence , iSentenceLen, wstrRes);
	if(0==iRes)
	{
		return write_log(iType, (TCHAR*)wstrRes.c_str(), (int)wstrRes.length());
	}

	return 0;
}

// д����־���
int CCoreServer::write_log(int iType, TCHAR* pszSentence, int iSentenceLen)
{
	if(!pszSentence)
		return 10;

	if(0==iSentenceLen)
		return 20;

	if(0==iType)	// ��ʾ
	{
		if(!m_pLogPrompt)
			return 60;

		return m_pLogPrompt->write_log(pszSentence, iSentenceLen);
	}
	else if(1==iType)	// ����
	{
		if(!m_pLogWaring)
			return 70;

		return m_pLogWaring->write_log(pszSentence, iSentenceLen);
	}
	else if(2==iType)	// �������쳣
	{
		if(!m_pLogErr)
			return 80;

		return m_pLogErr->write_log(pszSentence, iSentenceLen);
	}

	return  0;
}
