#include "SIX_SocketClient.h"

SIX_SocketClient::SIX_SocketClient(int protocol)
{
	m_bReconnect = m_StopSend = false;
	pConnectT = pHeartBeatT = pRecvT = pSendT = 0;
	m_sendList = 0;
	m_iStatus = 0;
	pPackageMgr = new SIX_PackageMgr();
	this->init(/*127.0.0.1*/XorStr<0xD4,10,0x3287679D>("\xE5\xE7\xE1\xF9\xE8\xF7\xEA\xF5\xED"+0x3287679D).s,2000,"","");
}

SIX_SocketClient::~SIX_SocketClient()
{
	SIXLog("~SIX_SocketClient.Begin");
	stop();
	CC_SAFE_DELETE(pPackageMgr);
	SIXLog("~SIX_SocketClient.Done");
}

int SIX_SocketClient::init(char *ip,int port,char *name,char *pass)
{
	m_addr.clear();
	m_addr.append(ip);

	m_port = port;

	m_name.clear();
	m_name.append(name);

	m_pass.clear();
	m_pass.append(pass);

	// 重置停止发送标志位
	m_StopSend = false;

	// 设置心跳
	this->setHeartBeatDelay(MAX_HEARTBEAT_DELAY);
	this->setHeartBeatLastTime(0);

	// 默认设置断线重连
	this->setReconnect(true);
	// 默认设置断线重连间隔(ms)
	this->setReconnectDelay(MAX_RECONNECT_DELAY);

	return 0;
}

int SIX_SocketClient::start()
{
	this->StartThread();
	return 0;
}

int SIX_SocketClient::stop()
{
	this->StopThread();
	return 0;
}

int SIX_SocketClient::send_data(int iMainCode, int iSubCode, void *pData, int iDataLen)
{
	if (!this->checkStatus(CLIENT_RUNNING))
		return -1;
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->m_MainCode = iMainCode;
	pMsg->m_SubCode = iSubCode;
	pMsg->m_DataLen = iDataLen;
	pMsg->m_Data = new unsigned char[iDataLen+1];
	memcpy(pMsg->m_Data,pData,iDataLen);
	if (!this->PushMsg(pMsg))
	{
		CC_SAFE_DELETE(pMsg);
		return -2;
	}
	return 0;
}

int SIX_SocketClient::send_data(int iMainCode, int iSubCode)
{
	if (!this->checkStatus(CLIENT_RUNNING))
		return -1;
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->m_MainCode = iMainCode;
	pMsg->m_SubCode = iSubCode;
	if (!this->PushMsg(pMsg))
		CC_SAFE_DELETE(pMsg);
	return 0;
}

void SIX_SocketClient::StartThread()
{
	if (this->checkStatus(CLIENT_RUNNING))
		return;

	if (!this->checkStatus(THREAD_CONNECT_RUNNING))
	{
		pConnectT = new SIX_Thread();
		if (BeginThread(pConnectT,(tc_thread_func)ConnectThread/*,PTHREAD_CREATE_DETACHED*/)==0)
			this->setStatus(THREAD_CONNECT_RUNNING);
	}
	if (!this->checkStatus(THREAD_HEARTBEAT_RUNNING))
	{
		pHeartBeatT = new SIX_Thread();
		if (BeginThread(pHeartBeatT,(tc_thread_func)HeartBeatThread/*,PTHREAD_CREATE_DETACHED*/)==0)
			this->setStatus(THREAD_HEARTBEAT_RUNNING);
	}
	if (!this->checkStatus(THREAD_RECV_RUNNING))
	{
		pRecvT = new SIX_Thread();
		if (BeginThread(pRecvT,(tc_thread_func)RecvThread/*,PTHREAD_CREATE_DETACHED*/)==0)
			this->setStatus(THREAD_RECV_RUNNING);
	}
	if (!this->checkStatus(THREAD_SEND_RUNNING))
	{
		pSendT = new SIX_Thread();
		m_sendList = new SIX_TList<MSG_INFO*>;
		if (BeginThread(pSendT,(tc_thread_func)SendThread/*,PTHREAD_CREATE_DETACHED*/)==0)
			this->setStatus(THREAD_SEND_RUNNING);
	}

	this->setStatus(CLIENT_RUNNING);
}

void SIX_SocketClient::setPowerClosePeer()
{
	// 客户端主动断开，底层不进行断线重连
	// Cool.Cat
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Create(0,0,0,0,false,true);
	this->PushMsg(pMsg);
#ifdef WIN32
	Sleep(1000);
#else
	usleep(1000 * 1000);
#endif
}

void SIX_SocketClient::StopThread()
{
	if (!this->checkStatus(CLIENT_RUNNING))
		return;

	this->setPowerClosePeer();

	// 设置停止发送数据
	m_StopSend = true;

	// 等待发送队列完成
	while (GetMsgCount()){}

	// 清空RB
	pPackageMgr->ReleaseBuffer();
	this->setReconnect(false);
	this->close();

	if (this->checkStatus(THREAD_CONNECT_RUNNING))
	{
		this->setStatus(-THREAD_CONNECT_RUNNING);
		EndThread(pConnectT);
		CC_SAFE_DELETE(pConnectT);
	}
	if (this->checkStatus(THREAD_HEARTBEAT_RUNNING))
	{
		this->setStatus(-THREAD_HEARTBEAT_RUNNING);
		EndThread(pHeartBeatT);
		CC_SAFE_DELETE(pHeartBeatT);
	}
	if (this->checkStatus(THREAD_SEND_RUNNING))
	{
		this->setStatus(-THREAD_SEND_RUNNING);
		EndThread(pSendT);
		CC_SAFE_DELETE(pSendT);
		CC_SAFE_DELETE(m_sendList);
	}
	if (this->checkStatus(THREAD_RECV_RUNNING))
	{
		this->setStatus(-THREAD_RECV_RUNNING);
		EndThread(pRecvT);
		CC_SAFE_DELETE(pRecvT);
	}

	this->setStatus(-CLIENT_RUNNING);
}

void SIX_SocketClient::setStatus(int status)
{
	if (status>0)
		m_iStatus |= status;
	else
		m_iStatus ^= abs(status);
}

int SIX_SocketClient::getStatus()
{
	return m_iStatus;
}

bool SIX_SocketClient::checkStatus(int status)
{
	return (m_iStatus & status)?true:false;
}

void SIX_SocketClient::setHeartBeatDelay(unsigned int heartbeatDelay)
{
	m_uHeartBeatDelay = heartbeatDelay;
}

unsigned int SIX_SocketClient::getHeartBeatDelay()
{
	return m_uHeartBeatDelay;
}

void SIX_SocketClient::setHeartBeatLastTime(long long heartbeatLastTime)
{
	m_uHeartBeatLastTime = heartbeatLastTime;
}

long long SIX_SocketClient::getHeartBeatLastTime()
{
	return m_uHeartBeatLastTime;
}

void SIX_SocketClient::setReconnect(bool reconnect)
{
	m_bReconnect = reconnect;
}

bool SIX_SocketClient::getReconnect()
{
	return m_bReconnect;
}

void SIX_SocketClient::setReconnectDelay(unsigned int delay)
{
	m_uReconnectDelay = delay;
}

unsigned int SIX_SocketClient::getReconnectDelay()
{
	return m_uReconnectDelay;
}

// 线程默认以非分离方式运行，主线程不用Sleep
int SIX_SocketClient::BeginThread(SIX_Thread *pThread,tc_thread_func pFunc,int attr)
{
	if (pThread)
		return pThread->BeginThread(this,pFunc,attr);
	return -1;
}

void SIX_SocketClient::EndThread(SIX_Thread *pThread)
{
	if (pThread)
	{
		// 只有分离状态才等待线程自然结束
		if (!pThread->GetJoinabled())
			while (pThread->GetRunning()){}
	}
}

// 设置线程以非分离方式运行
void SIX_SocketClient::setJoinable(SIX_Thread *pThread,bool joinable)
{
	if (pThread)
		pThread->SetJoinabled(joinable);
}

// 获取线程是否以非分离方式运行
bool SIX_SocketClient::IsJoinable(SIX_Thread *pThread)
{
	if (!pThread)
		return false;
	return pThread->GetJoinabled();
}

int SIX_SocketClient::ConnectThread(void *pointer)
{
	SIX_SocketClient *pThis = static_cast<SIX_SocketClient*>(pointer);
	if (!pThis)
	{
		SIXLog("ConnectThread.pThis.Nil");
		return -1;
	}

	SIXLog("ConnectThread[0x%08X].Begin...",pThis->pConnectT->GetThreadID());

	// 初始化连接
	pThis->Connect(pThis->m_addr.c_str(),pThis->m_port);

	while (pThis->checkStatus(THREAD_CONNECT_RUNNING))
	{
		// 设置了断线重连
		if (pThis->getReconnect())
		{
			// 未连接状态
			if (!pThis->getConnected())
			{
				// 尝试连接
				SIXLog("Try Reconnect [%s:%d] ...",pThis->m_addr.c_str(),pThis->m_port);
				pThis->Connect(pThis->m_addr.c_str(),pThis->m_port);
			}
		}

#ifdef WIN32
		Sleep(pThis->getReconnectDelay());
#else
		usleep(pThis->getReconnectDelay() * 1000);
#endif
	}

	SIXLog("ConnectThread[0x%08X].Exit!",pThis->pConnectT->GetThreadID());

	return 1;
}

int SIX_SocketClient::HeartBeatThread(void *pointer)
{
	SIX_SocketClient *pThis = static_cast<SIX_SocketClient*>(pointer);
	if (!pThis)
	{
		SIXLog("HeartBeat.pThis.Nil");
		return -1;
	}

	SIXLog("HeartBeatThread[0x%08X].Begin...",pThis->pHeartBeatT->GetThreadID());

	while (pThis->checkStatus(THREAD_HEARTBEAT_RUNNING))
	{
		// 只有连上了才发心跳
		// Cool.Cat
		if (pThis->getConnected())
			pThis->DoHeartBeat();
#ifdef WIN32
		Sleep(100);
#else
		usleep(100*1000);
#endif
	}

	SIXLog("HeartBeatThread[0x%08X].Exit!",pThis->pHeartBeatT->GetThreadID());

	return 1;
}

int SIX_SocketClient::RecvThread(void *pointer)
{
	SIX_SocketClient *pThis = static_cast<SIX_SocketClient*>(pointer);
	if (!pThis)
	{
		SIXLog("RecvThread.pThis.Nil");
		return -1;
	}

	SIXLog("RecvThread[0x%08X].Begin...",pThis->pRecvT->GetThreadID());

	while(pThis->checkStatus(THREAD_RECV_RUNNING))
	{
		pThis->Recv();
#ifdef WIN32
		Sleep(1);
#else
		usleep(1000);
#endif
	}

	SIXLog("RecvThread[0x%08X].Exit!",pThis->pRecvT->GetThreadID());

	return 1;
}

int SIX_SocketClient::SendThread(void *pointer)
{
	SIX_SocketClient *pThis = static_cast<SIX_SocketClient*>(pointer);
	if (!pThis)
	{
		SIXLog("SendThread.pThis.Nil");
		return -1;
	}

	SIXLog("SendThread[0x%08X].Begin...",pThis->pSendT->GetThreadID());

	pThis->CleanMsg();

	while(pThis->checkStatus(THREAD_SEND_RUNNING))
	{
		pThis->DoSend();
#ifdef WIN32
		Sleep(1);
#else
		usleep(1000);
#endif
	}

	SIXLog("SendThread[0x%08X].Exit!",pThis->pSendT->GetThreadID());

	return 1;
}

void SIX_SocketClient::DoHeartBeat()
{
	//long long now = CEasyDataTime::get_current_time_diff_millitm_from_1970();
	long long now = SIX_Utility::GetInstance()->GetTickCount();

	if (this->getHeartBeatLastTime()!=0 && (this->getHeartBeatLastTime() + this->getHeartBeatDelay() > now))
		return;

	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Create(0,0,0,0,true);
	if (!this->PushMsg(pMsg))
		CC_SAFE_DELETE(pMsg);
	else
		m_uHeartBeatLastTime = now;
}

void SIX_SocketClient::DoSend()
{
	unsigned int mValid = 0;
	unsigned int mTotal = GetMsgCount();

	unsigned int mPckLen = 0;
	char mPckBuffer[BUFFSIZE] = {0};

	unsigned int pLen = 0;
	char pPckBuffer[BUFFSIZE] = {0};
	for (unsigned int i=0;i<mTotal;i++)
	{
		MSG_INFO *pMsg = FrontMsg();
		if (!pMsg)
			continue;

		// 检查组包前的总长度是否溢出
		if (mPckLen+pMsg->m_DataLen>BUFFSIZE)
			break;

		// 组包
		if (!pPackageMgr->Pack(pMsg,pPckBuffer,&pLen))
		{
			SIXLog("SIX_SocketClient.Send.PackAMessage.Error[%u]",mPckLen);
			break;
		}

		// 检查组包后的总长度是否溢出
		if (mPckLen+pLen>BUFFSIZE)
			break;

		memmove(mPckBuffer+mPckLen,pPckBuffer,pLen);

		mPckLen += pLen;

		CC_SAFE_DELETE(pMsg);

		PopMsg();
	}

	int nPos = 0;
	while (mPckLen>0)
	{
		int sendSize = Send((const char*)mPckBuffer+nPos,mPckLen);
		if (sendSize==SOCKET_ERROR)
		{
			int errIdx = GetErrorNumber();
#ifdef WIN32
			if (errIdx!=WSAEWOULDBLOCK)
#else
			if (errIdx!=EINPROGRESS)
#endif
			{
				const char *errMsg = GetErrorMsg(errIdx);
				SIXLog("SIX_SocketClient.Send.close[%s]",errMsg);
				CC_SAFE_DELETE(errMsg);
				// 断开
				close(CLOSE_TYPE_FLASH_CLOSE);
				return;
			}
		}

		// 断线的情况直接跳出
		if (sendSize==-2)
			return;

		if (sendSize<=0)
		{
			int errIdx = GetErrorNumber();
			const char *errMsg = GetErrorMsg(errIdx);
			SIXLog("SIX_SocketClient.Send.Error[%d][%u][%s]",sendSize,mPckLen,errMsg);
			CC_SAFE_DELETE(errMsg);
			return;
		}
		// 一次没拷贝完的，继续拷贝
		mPckLen -= sendSize;
		nPos = sendSize;

		mValid++;
		//SIXLog("SIX_SocketClient.Send.Total[%u].Valid[%u]",mTotal,mValid);
	}
}

bool SIX_SocketClient::PushMsg(MSG_INFO *pMsg)
{
	if (m_StopSend || !m_sendList)
		return false;
	m_sendList->Push(pMsg);
	return true;
}

// 弹出消息
MSG_INFO *SIX_SocketClient::PopMsg()
{
	if (!m_sendList)
		return 0;
	return m_sendList->Pop();
}

// 弹出消息
MSG_INFO *SIX_SocketClient::FrontMsg()
{
	if (!m_sendList)
		return 0;
	return m_sendList->Front();
}

// 清空消息
void SIX_SocketClient::CleanMsg()
{
	if (!m_sendList)
		return;
	m_sendList->Destory();
}

// 消息总数(发送队列)
unsigned int SIX_SocketClient::GetMsgCount()
{
	if (!m_sendList)
		return 0;
	return m_sendList->GetCount();
}

void SIX_SocketClient::GetStats()
{
#ifdef WIN32
	SIXLog("Stats.Tid[0x%08X]：",pthread_self().p);
#else
	SIXLog("Stats.Tid[0x%08X]：",pthread_self());
#endif
	SIXLog("-----------------------");
	if (pRecvT)
		SIXLog("RecvT.Tid[0x%08X].Running[%d].Joinabled[%d]",pRecvT->GetThreadID(),pRecvT->GetRunning(),pRecvT->GetJoinabled());
	if (pSendT)
		SIXLog("SendT.Tid[0x%08X].Running[%d].Joinabled[%d]",pSendT->GetThreadID(),pSendT->GetRunning(),pSendT->GetJoinabled());
	SIXLog("-----------------------");
	SIXLog("RecvList.Count[%u]",SIX_Proxy::GetInstance()->GetEventCount());
	SIXLog("SendList.Count[%u]",GetMsgCount());
	SIXLog("-----------------------");
}

void SIX_SocketClient::OnRecv(char *pData,int pLen)
{
	//SIXLog("OnRecv[%d]",pLen);

	// 先写缓冲
	pPackageMgr->WriteBuffer(pData,pLen);

	// 尝试从RB里循环拆包
	DoUnpack();
}

int SIX_SocketClient::DoUnpack()
{
	MSG_INFO *pMsg = new MSG_INFO();
	int result = 1;
	while (result>0)
	{
		CC_SAFE_DELETE(pMsg->m_Data);
		result = pPackageMgr->TryUnPack(pMsg);
		if (result<=UNPACK_PACKET_SUCCESSED)
			goto clean;

		m_uUnpackErrorCount = 0;
		OnTableMsg(pMsg->m_MainCode,pMsg->m_SubCode,pMsg->m_Data,pMsg->m_DataLen);
	}
clean:
	CC_SAFE_DELETE(pMsg);
	// 只要满足RB里的缓冲够一个完整的包头，但是包头协议不匹配
	if (result==UNPACK_PACKET_INVALID)
	{
		SIXLog("DoUnpack.result[%d].Error!",result);

		// 进到这里来就说明存在以下问题了！
		// a) 空包(正常情况不会出现)
		// b) 包头错误(C/S两端协议包头不匹配、非法数据包等)
		m_uUnpackErrorCount++;
		if (m_uUnpackErrorCount>=MAX_UNPACK_ERROR_COUNT)
		{
			SIXLog("DoUnpack.result[%d].Too many error packet,so kick it!",result);
			// 清空RB
			pPackageMgr->ReleaseBuffer();
			// 拆包失败次数超过限制，有可能是非法包，
			// 需要客户端主动断开，底层不进行断线重连
			// Cool.Cat
			this->setPowerClosePeer();
			this->setReconnect(false);
			this->close();
		}
	}
	// 服务端主动关闭客户端
	else if (result==UNPACK_PACKET_CLOSEPEER)
	{
		SIXLog("DoUnpack.result[%d].closeByServer",result);
		m_uUnpackErrorCount = MAX_UNPACK_ERROR_COUNT;
		// 清空RB
		pPackageMgr->ReleaseBuffer();
		this->setReconnect(false);
		this->close(CLOSE_TYPE_SERVER_POWER_CLOSE);
	}
	return result;
}