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

	// ����ֹͣ���ͱ�־λ
	m_StopSend = false;

	// ��������
	this->setHeartBeatDelay(MAX_HEARTBEAT_DELAY);
	this->setHeartBeatLastTime(0);

	// Ĭ�����ö�������
	this->setReconnect(true);
	// Ĭ�����ö����������(ms)
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
	// �ͻ��������Ͽ����ײ㲻���ж�������
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

	// ����ֹͣ��������
	m_StopSend = true;

	// �ȴ����Ͷ������
	while (GetMsgCount()){}

	// ���RB
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

// �߳�Ĭ���ԷǷ��뷽ʽ���У����̲߳���Sleep
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
		// ֻ�з���״̬�ŵȴ��߳���Ȼ����
		if (!pThread->GetJoinabled())
			while (pThread->GetRunning()){}
	}
}

// �����߳��ԷǷ��뷽ʽ����
void SIX_SocketClient::setJoinable(SIX_Thread *pThread,bool joinable)
{
	if (pThread)
		pThread->SetJoinabled(joinable);
}

// ��ȡ�߳��Ƿ��ԷǷ��뷽ʽ����
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

	// ��ʼ������
	pThis->Connect(pThis->m_addr.c_str(),pThis->m_port);

	while (pThis->checkStatus(THREAD_CONNECT_RUNNING))
	{
		// �����˶�������
		if (pThis->getReconnect())
		{
			// δ����״̬
			if (!pThis->getConnected())
			{
				// ��������
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
		// ֻ�������˲ŷ�����
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

		// ������ǰ���ܳ����Ƿ����
		if (mPckLen+pMsg->m_DataLen>BUFFSIZE)
			break;

		// ���
		if (!pPackageMgr->Pack(pMsg,pPckBuffer,&pLen))
		{
			SIXLog("SIX_SocketClient.Send.PackAMessage.Error[%u]",mPckLen);
			break;
		}

		// ����������ܳ����Ƿ����
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
				// �Ͽ�
				close(CLOSE_TYPE_FLASH_CLOSE);
				return;
			}
		}

		// ���ߵ����ֱ������
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
		// һ��û������ģ���������
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

// ������Ϣ
MSG_INFO *SIX_SocketClient::PopMsg()
{
	if (!m_sendList)
		return 0;
	return m_sendList->Pop();
}

// ������Ϣ
MSG_INFO *SIX_SocketClient::FrontMsg()
{
	if (!m_sendList)
		return 0;
	return m_sendList->Front();
}

// �����Ϣ
void SIX_SocketClient::CleanMsg()
{
	if (!m_sendList)
		return;
	m_sendList->Destory();
}

// ��Ϣ����(���Ͷ���)
unsigned int SIX_SocketClient::GetMsgCount()
{
	if (!m_sendList)
		return 0;
	return m_sendList->GetCount();
}

void SIX_SocketClient::GetStats()
{
#ifdef WIN32
	SIXLog("Stats.Tid[0x%08X]��",pthread_self().p);
#else
	SIXLog("Stats.Tid[0x%08X]��",pthread_self());
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

	// ��д����
	pPackageMgr->WriteBuffer(pData,pLen);

	// ���Դ�RB��ѭ�����
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
	// ֻҪ����RB��Ļ��幻һ�������İ�ͷ�����ǰ�ͷЭ�鲻ƥ��
	if (result==UNPACK_PACKET_INVALID)
	{
		SIXLog("DoUnpack.result[%d].Error!",result);

		// ������������˵���������������ˣ�
		// a) �հ�(��������������)
		// b) ��ͷ����(C/S����Э���ͷ��ƥ�䡢�Ƿ����ݰ���)
		m_uUnpackErrorCount++;
		if (m_uUnpackErrorCount>=MAX_UNPACK_ERROR_COUNT)
		{
			SIXLog("DoUnpack.result[%d].Too many error packet,so kick it!",result);
			// ���RB
			pPackageMgr->ReleaseBuffer();
			// ���ʧ�ܴ����������ƣ��п����ǷǷ�����
			// ��Ҫ�ͻ��������Ͽ����ײ㲻���ж�������
			// Cool.Cat
			this->setPowerClosePeer();
			this->setReconnect(false);
			this->close();
		}
	}
	// ����������رտͻ���
	else if (result==UNPACK_PACKET_CLOSEPEER)
	{
		SIXLog("DoUnpack.result[%d].closeByServer",result);
		m_uUnpackErrorCount = MAX_UNPACK_ERROR_COUNT;
		// ���RB
		pPackageMgr->ReleaseBuffer();
		this->setReconnect(false);
		this->close(CLOSE_TYPE_SERVER_POWER_CLOSE);
	}
	return result;
}