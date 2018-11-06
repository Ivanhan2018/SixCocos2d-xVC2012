#include "SIX_SocketClient.h"

SIX_SocketClient::SIX_SocketClient(int protocol)
{
	SIXLog("SIX_SocketClient.Begin");
	m_Inited = m_NeedExitForRecv = m_NeedExitForSend = m_StopSend = false;
	pRecvT = pSendT = 0;
	m_sendList = 0;
	pPackageMgr = new SIX_PackageMgr();
	StartRWThread();
	SIXLog("SIX_SocketClient.Done");
}

SIX_SocketClient::~SIX_SocketClient()
{
	SIXLog("~SIX_SocketClient.Begin");
	StopRWThread();
	CC_SAFE_DELETE(pPackageMgr);
	SIXLog("~SIX_SocketClient.Done");
}

void SIX_SocketClient::StartRWThread()
{
	if (GetInited() || m_StopSend)
		return;

	pSendT = new SIX_Thread();
	pRecvT = new SIX_Thread();
	m_sendList = new SIX_TList<MSG_INFO*>;
	BeginThread(pSendT,(tc_thread_func)SendThread/*,PTHREAD_CREATE_DETACHED*/);
	BeginThread(pRecvT,(tc_thread_func)RecvThread/*,PTHREAD_CREATE_DETACHED*/);
}

void SIX_SocketClient::StopRWThread()
{
	// 设置停止发送数据
	m_StopSend = true;

	// 等待发送队列完成
	while (GetMsgCount()){}

	// 设置退出信号
	m_NeedExitForSend = m_NeedExitForSend = m_NeedExitForRecv = true;

	EndThread(pSendT);
	CC_SAFE_DELETE(pSendT);
	EndThread(pRecvT);
	CC_SAFE_DELETE(pRecvT);

	CC_SAFE_DELETE(m_sendList);
}

bool SIX_SocketClient::GetInited()
{
	return m_Inited;
}

// 线程默认以非分离方式运行，主线程不用Sleep
void SIX_SocketClient::BeginThread(SIX_Thread *pThread,tc_thread_func pFunc,int attr)
{
	if (pThread)
	{
		int retv = pThread->BeginThread(this,pFunc,attr);
		if (retv==0)
			m_Inited = true;
	}
}

void SIX_SocketClient::EndThread(SIX_Thread *pThread)
{
	if (pThread)
	{
		// 只有分离状态才等待线程自然结束
		if (!pThread->GetJoinabled())
			while (pThread->GetRunning()){}
		m_Inited = false;
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

int SIX_SocketClient::RecvThread(void *pointer)
{
	SIX_SocketClient *pThis = static_cast<SIX_SocketClient*>(pointer);
	if (!pThis)
	{
		SIXLog("RecvThread.pThis.Nil");
		return -1;
	}

	while(!pThis->m_NeedExitForRecv)
	{
		pThis->Recv();
	}

	SIXLog("RecvThread[0x%08X].Exit",pThis->pRecvT->GetThreadID());

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

	pThis->CleanMsg();

	while(!pThis->m_NeedExitForSend)
	{
		pThis->DoSend();
	}

	SIXLog("SendThread[0x%08X].Exit",pThis->pSendT->GetThreadID());

	return 1;
}

void SIX_SocketClient::DoSend()
{
	unsigned int mValid = 0;
	unsigned int mTotal = GetMsgCount();

	unsigned int mPckLen = 0;
	char mPckBuffer[BUFFSIZE] = {0};

	unsigned int pLen = 0;
	char pPckBuffer[BUFFSIZE] = {0};
	for (int i=0;i<mTotal;i++)
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

	if (mPckLen>0)
	{
		int retv = Send((const char*)mPckBuffer,mPckLen);
		if (retv>0)
			mValid++;
		else
			SIXLog("SIX_SocketClient.Send.Error[%d][%u]",retv,mPckLen);
	}

	//SIXLog("SIX_SocketClient.Send.Total[%u].Valid[%u]",mTotal,mValid);
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
	SIXLog("OnRecv[%d]",pLen);

	// 拆包
	MSG_INFO *pMsg = new MSG_INFO();
	if (!pPackageMgr->UnPack(pData,pLen,pMsg))
	{
		CC_SAFE_DELETE(pMsg);
		SIXLog("SIX_SocketClient.OnRecv.UnPack.Error[%d]",pLen);
	}
	else
		SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_SocketClient::OnClose()
{
	SIXLog("OnClose");

	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(0,0,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}