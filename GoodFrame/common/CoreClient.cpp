
#include "./CoreClient.h"
#include "./CommTcpClient.h"
#include "./assert.h"

CCoreClient::CCoreClient(void)
{
	//m_pMsgPool = NULL;
	m_pTcpClient = NULL;
	m_pTcpClient = new CCommTcpClient;
	if(m_pTcpClient)
		m_pTcpClient->set_core_client(this);

	m_strPath = _T("Client_Log\\");
	m_pLogPrompt = NULL;	// ��ʾ��־��
	m_pLogWaring = NULL;	// ������־��
	m_pLogErr = NULL;		// �������쳣��־

	
}

CCoreClient::~CCoreClient(void)
{
}

// ������Ϣ��ĳ���
void CCoreClient::set_msg_block_size(int iMsgBlockSize)
{
	m_pTcpClient->set_msg_block_size(iMsgBlockSize)  ;
}

// ������Ϣ�ص����Ԫ������
void CCoreClient::set_msg_pool_init_count(int iMsgPoolInitCount)
{
	m_pTcpClient->set_msg_pool_init_count(iMsgPoolInitCount)  ;
}

// ���÷��ͽ���ص����Ԫ������
void CCoreClient::set_send_result_pool_init_count(int iSendResultPoolInitCount)
{
	m_pTcpClient->set_send_result_pool_init_count(iSendResultPoolInitCount);
}

// ���ö��������ļ��ʱ�䣬��λms
void CCoreClient::set_reconnect_interval_time(int iAutoReConnectTime)
{
	m_pTcpClient->set_reconnect_interval_time(iAutoReConnectTime)  ;
}

// ��ö�������
bool CCoreClient::get_reconnect()
{
	return m_pTcpClient->get_reconnect();
}

// ���ö�������
void CCoreClient::set_reconnect(bool bAutoReConnect)
{
	m_pTcpClient->set_reconnect(bAutoReConnect)  ;
}


// ��ùرշ�ʽ
CLOSE_TYPE CCoreClient::get_close_type()
{
	return m_pTcpClient->get_close_type();
}

// ���ùرշ�ʽ
void CCoreClient::set_close_type(CLOSE_TYPE iCloseType)
{
	m_pTcpClient->set_close_type(iCloseType);
}

// �����������ֳص�ʱ�䣬iShrinkPoolsTime �� ms Ϊ��λ
void CCoreClient::set_shrink_pools_time(LONGLONG iShrinkPoolsTime)
{
	m_pTcpClient->set_shrink_pools_time(iShrinkPoolsTime)  ;
}

// ���÷�����������ʱ��
void CCoreClient::set_send_heartbeat_time(LONGLONG iSendHeartbeatTime)
{
	m_pTcpClient->set_send_heartbeat_time(iSendHeartbeatTime)  ;
}

// ������־��·��
int CCoreClient::set_log_path(TCHAR* pszPathName)
{
	if(!pszPathName)
		return 10;

	m_strPath = pszPathName;

	return 0;
}

int CCoreClient::init()
{
	int iResult = 0;

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

	return  m_pTcpClient->init();
}

// ����
int CCoreClient::start()
{
	return m_pTcpClient->start() ;
}

// ֹͣ
int CCoreClient::stop()
{
	int iResult = 0;

	if (m_pLogPrompt)
	{
		iResult = m_pLogPrompt->stop_log();
		assert(0==iResult);
		delete 	m_pLogPrompt;
	}

	if (m_pLogWaring)
	{
		iResult = m_pLogWaring->stop_log();
		assert(0==iResult);
		delete 	m_pLogWaring;
	}

	if (m_pLogErr)
	{
		iResult = m_pLogErr->stop_log();
		assert(0==iResult);
		delete 	m_pLogErr;
	}

	return m_pTcpClient->stop();
}

// ��������
int CCoreClient::send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	return m_pTcpClient->send_data(iMainCode, iSubCode, pData, iDataLen) ;
}

// ���ʹ������ݣ����ڲ���
int CCoreClient::send_error_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	return m_pTcpClient->send_error_data(iMainCode, iSubCode, pData, iDataLen) ;
}

// �������ӵ�ַ
void CCoreClient::set_connect_addr(const char* szListenAddr)
{
	m_pTcpClient->set_connect_addr(szListenAddr) ;
}

// �������Ӷ˿�
void CCoreClient::set_connect_port(unsigned int nPort)
{
	m_pTcpClient->set_connect_port(nPort) ;
}

// ����С�������
int CCoreClient::OnRecvComplete(int iResult, const CMemBlock* pRecv)
{
	return m_pTcpClient->OnRecvComplete(iResult, pRecv) ;
}

// �����رշ���ˣ�Ŀ�����÷������������ͻ��������ر�������
int CCoreClient::power_close()
{
	return m_pTcpClient->power_close() ;
}

///* --------------------------------------------------------------------------
//����˵�����رշ���ˣ��� power_close_peer ����
//���������
//	bClientClose	TRUE��ʾ�ͻ��������رգ�FALSE��ʾ������˹رյ�
//����ֵ��
//	�ɹ��򷵻� TRUE�����򷵻� FALSE ��
//--------------------------------------------------------------------------*/
//bool CCoreClient::close(CLOSE_TYPE iCloseType)
//{
//	return m_pTcpClient->close(iCloseType) ;
//}

// ��ʾ���еĳ���Ϣ
void CCoreClient::display_all_pool()
{
	m_pTcpClient->display_all_pool() ;
}

/* --------------------------------------------------------------------------
����˵������ӡδ��أ��ڳ��⣩��Ԫ��
����������
	vecOutPool	δ��أ��ڳ��⣩��Ԫ������
����ֵ��
	�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
void CCoreClient::display_out_pool(bool bDisplay, vector<OUT_POOL_ELEMENT>& vecOutPool)
{
	m_pTcpClient->m_pMsgPool->display_out_pool(bDisplay, vecOutPool);
}

// ����������
int CCoreClient::send_heartbeat_packeg()
{
	return m_pTcpClient->send_heartbeat_packeg() ;
}

// д����־���
int CCoreClient::write_log(int iType, TCHAR* pszSentence, int iSentenceLen)
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

// д����־��䣬���� Debug ����Ч��Release �в�д�ģ�Ŀ���Ƿ����ڽű��е���
int CCoreClient::write_log_debug(int iType, TCHAR* pszSentence, int iSentenceLen)
{
#if _DEBUG
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
#endif

	return  0;
}