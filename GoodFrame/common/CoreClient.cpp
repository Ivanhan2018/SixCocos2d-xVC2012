
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
	m_pLogPrompt = NULL;	// 提示日志，
	m_pLogWaring = NULL;	// 警告日志，
	m_pLogErr = NULL;		// 错误与异常日志

	
}

CCoreClient::~CCoreClient(void)
{
}

// 设置消息块的长度
void CCoreClient::set_msg_block_size(int iMsgBlockSize)
{
	m_pTcpClient->set_msg_block_size(iMsgBlockSize)  ;
}

// 设置消息池的最初元素数量
void CCoreClient::set_msg_pool_init_count(int iMsgPoolInitCount)
{
	m_pTcpClient->set_msg_pool_init_count(iMsgPoolInitCount)  ;
}

// 设置发送结果池的最初元素数量
void CCoreClient::set_send_result_pool_init_count(int iSendResultPoolInitCount)
{
	m_pTcpClient->set_send_result_pool_init_count(iSendResultPoolInitCount);
}

// 设置断线重连的间隔时间，单位ms
void CCoreClient::set_reconnect_interval_time(int iAutoReConnectTime)
{
	m_pTcpClient->set_reconnect_interval_time(iAutoReConnectTime)  ;
}

// 获得断线重连
bool CCoreClient::get_reconnect()
{
	return m_pTcpClient->get_reconnect();
}

// 设置断线重连
void CCoreClient::set_reconnect(bool bAutoReConnect)
{
	m_pTcpClient->set_reconnect(bAutoReConnect)  ;
}


// 获得关闭方式
CLOSE_TYPE CCoreClient::get_close_type()
{
	return m_pTcpClient->get_close_type();
}

// 设置关闭方式
void CCoreClient::set_close_type(CLOSE_TYPE iCloseType)
{
	m_pTcpClient->set_close_type(iCloseType);
}

// 设置收缩各种池的时间，iShrinkPoolsTime 以 ms 为单位
void CCoreClient::set_shrink_pools_time(LONGLONG iShrinkPoolsTime)
{
	m_pTcpClient->set_shrink_pools_time(iShrinkPoolsTime)  ;
}

// 设置发送心跳包的时间
void CCoreClient::set_send_heartbeat_time(LONGLONG iSendHeartbeatTime)
{
	m_pTcpClient->set_send_heartbeat_time(iSendHeartbeatTime)  ;
}

// 设置日志的路径
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

	// 提示日志
	{
		m_pLogPrompt = NULL;
		m_pLogPrompt = new CLog(_T("Prompt_"));
		assert(m_pLogPrompt);

		m_pLogPrompt->set_path(m_strPath);

		iResult = m_pLogPrompt->start_log();	// 启动任务模块，此句不能省略
		assert(0==iResult);
	}

	// 警告日志
	{
		m_pLogWaring = NULL;
		m_pLogWaring = new CLog(_T("Waring_"));
		assert(m_pLogWaring);

		m_pLogWaring->set_path(m_strPath);

		iResult = m_pLogWaring->start_log();	// 启动任务模块，此句不能省略
		assert(0==iResult);
	}

	// 错误与异常日志
	{
		m_pLogErr = NULL;
		m_pLogErr = new CLog(_T("ErrCatch_"));
		assert(m_pLogErr);

		m_pLogErr->set_path(m_strPath);

		iResult = m_pLogErr->start_log();	// 启动任务模块，此句不能省略
		assert(0==iResult);
	}

	return  m_pTcpClient->init();
}

// 启动
int CCoreClient::start()
{
	return m_pTcpClient->start() ;
}

// 停止
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

// 发送数据
int CCoreClient::send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	return m_pTcpClient->send_data(iMainCode, iSubCode, pData, iDataLen) ;
}

// 发送错误数据，用于测试
int CCoreClient::send_error_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	return m_pTcpClient->send_error_data(iMainCode, iSubCode, pData, iDataLen) ;
}

// 设置连接地址
void CCoreClient::set_connect_addr(const char* szListenAddr)
{
	m_pTcpClient->set_connect_addr(szListenAddr) ;
}

// 设置连接端口
void CCoreClient::set_connect_port(unsigned int nPort)
{
	m_pTcpClient->set_connect_port(nPort) ;
}

// 接收小包已完成
int CCoreClient::OnRecvComplete(int iResult, const CMemBlock* pRecv)
{
	return m_pTcpClient->OnRecvComplete(iResult, pRecv) ;
}

// 主动关闭服务端，目的是让服务端能区别出客户端主动关闭与闪断
int CCoreClient::power_close()
{
	return m_pTcpClient->power_close() ;
}

///* --------------------------------------------------------------------------
//函数说明：关闭服务端，用 power_close_peer 代替
//传入参数：
//	bClientClose	TRUE表示客户端主动关闭，FALSE表示被服务端关闭的
//返回值：
//	成功则返回 TRUE，否则返回 FALSE 。
//--------------------------------------------------------------------------*/
//bool CCoreClient::close(CLOSE_TYPE iCloseType)
//{
//	return m_pTcpClient->close(iCloseType) ;
//}

// 显示所有的池信息
void CCoreClient::display_all_pool()
{
	m_pTcpClient->display_all_pool() ;
}

/* --------------------------------------------------------------------------
函数说明：列印未归池（在池外）的元素
传出参数：
	vecOutPool	未归池（在池外）的元素数组
返回值：
	成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
void CCoreClient::display_out_pool(bool bDisplay, vector<OUT_POOL_ELEMENT>& vecOutPool)
{
	m_pTcpClient->m_pMsgPool->display_out_pool(bDisplay, vecOutPool);
}

// 发送心跳包
int CCoreClient::send_heartbeat_packeg()
{
	return m_pTcpClient->send_heartbeat_packeg() ;
}

// 写入日志语句
int CCoreClient::write_log(int iType, TCHAR* pszSentence, int iSentenceLen)
{
	if(!pszSentence)
		return 10;

	if(0==iSentenceLen)
		return 20;

	if(0==iType)	// 提示
	{
		if(!m_pLogPrompt)
			return 60;

		return m_pLogPrompt->write_log(pszSentence, iSentenceLen);
	}
	else if(1==iType)	// 警告
	{
		if(!m_pLogWaring)
			return 70;

		return m_pLogWaring->write_log(pszSentence, iSentenceLen);
	}
	else if(2==iType)	// 错误与异常
	{
		if(!m_pLogErr)
			return 80;

		return m_pLogErr->write_log(pszSentence, iSentenceLen);
	}

	return  0;
}

// 写入日志语句，仅在 Debug 中生效，Release 中不写的，目的是方便在脚本中调试
int CCoreClient::write_log_debug(int iType, TCHAR* pszSentence, int iSentenceLen)
{
#if _DEBUG
	if(!pszSentence)
		return 10;

	if(0==iSentenceLen)
		return 20;

	if(0==iType)	// 提示
	{
		if(!m_pLogPrompt)
			return 60;

		return m_pLogPrompt->write_log(pszSentence, iSentenceLen);
	}
	else if(1==iType)	// 警告
	{
		if(!m_pLogWaring)
			return 70;

		return m_pLogWaring->write_log(pszSentence, iSentenceLen);
	}
	else if(2==iType)	// 错误与异常
	{
		if(!m_pLogErr)
			return 80;

		return m_pLogErr->write_log(pszSentence, iSentenceLen);
	}
#endif

	return  0;
}