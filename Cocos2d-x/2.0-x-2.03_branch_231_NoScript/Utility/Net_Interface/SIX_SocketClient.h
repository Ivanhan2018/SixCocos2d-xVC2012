/***********************************************
Name��SIX_SocketClient
Desc��SIX_Socket + PThread + SIX_PackageMgr
Auth��Cool.Cat@2013-04-16
***********************************************/
#pragma once

#include <SIX_Socket.h>
#include <SIX_PackageMgr.h>
#include <SIX_Typedef.h>
#include <SIX_Lock.h>
#include <SIX_Thread.h>
#include <SIX_TList.h>
#include <SIX_Proxy.h>
#include <CCLuaEngine.h>

class SIX_Lock;
class SIX_Thread;
class SIX_SocketClient:public SIX_Socket{
public:
	SIX_SocketClient(int protocol=TCP);
	~SIX_SocketClient();
public:
	// �����߳��ԷǷ��뷽ʽ����
	void setJoinable(SIX_Thread *pThread,bool joinable);
	// ��ȡ�߳��Ƿ��ԷǷ��뷽ʽ����
	bool IsJoinable(SIX_Thread *pThread);

	bool PushMsg(MSG_INFO *pMsg);
	MSG_INFO *PopMsg();
	MSG_INFO *FrontMsg();
	void CleanMsg();
	unsigned int GetMsgCount();

	void GetStats();
private:
	void OnRecv(char *pData,int pLen);
	void OnClose();

	bool GetInited();

	void DoSend();

	void StartRWThread();
	void StopRWThread();

	static int RecvThread(void *);
	static int SendThread(void *);

	// �߳�Ĭ���ԷǷ��뷽ʽ���У����̲߳���Sleep
	void BeginThread(SIX_Thread *pThread,tc_thread_func pFunc,int attr=PTHREAD_CREATE_JOINABLE);
	void EndThread(SIX_Thread *pThread);
private:
	bool m_Inited;
	bool m_NeedExitForSend;
	bool m_NeedExitForRecv;
	bool m_StopSend;

	SIX_Thread *pRecvT;
	SIX_Thread *pSendT;

	SIX_PackageMgr *pPackageMgr;

	// д����
	SIX_TList<MSG_INFO*> *m_sendList;
};