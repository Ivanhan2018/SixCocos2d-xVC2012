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

// �������(ms)
#define MAX_HEARTBEAT_DELAY		10 * 1000
// �����������(ms)
#define MAX_RECONNECT_DELAY		3 * 100
// ���ʧ������
#define MAX_UNPACK_ERROR_COUNT	10

typedef enum {
	// ʵ��������״̬
	CLIENT_RUNNING				=	1,
	// �����߳�����״̬
	THREAD_CONNECT_RUNNING		=	2,
	// �����߳�����״̬
	THREAD_RECONNECT_RUNNING	=	4,
	// �����߳�����״̬
	THREAD_HEARTBEAT_RUNNING	=	8,
	// �����߳�����״̬
	THREAD_RECV_RUNNING			=	16,
	// �����߳�����״̬
	THREAD_SEND_RUNNING			=	32,
} CLIENTRUNNING_STATUS;

class SIX_Lock;
class SIX_Thread;
class SIX_SocketClient:public SIX_Socket{
public:
	SIX_SocketClient(int protocol=IPPROTO_TCP);
	~SIX_SocketClient();
public:
	int init(char *ip,int port,char *name,char *pass,bool bReconnected=true,int iReconnectDelay=MAX_RECONNECT_DELAY);
	int start();
	int stop();

	int send_data(int iMainCode, int iSubCode, void *pData, int iDataLen);
	int send_data(int iMainCode, int iSubCode);

	// �����߳��ԷǷ��뷽ʽ����
	void setJoinable(SIX_Thread *pThread,bool joinable);
	// ��ȡ�߳��Ƿ��ԷǷ��뷽ʽ����
	bool IsJoinable(SIX_Thread *pThread);

	// �������(ms)
	void setHeartBeatDelay(unsigned int heartbeatDelay);
	unsigned int getHeartBeatDelay();

	// �ϴ�����ʱ��
	void setHeartBeatLastTime(long long heartbeatLastTime);
	long long getHeartBeatLastTime();

	// ��������
	void setReconnect(bool reconnect);
	bool getReconnect();

	// �����������(ms)
	void setReconnectDelay(unsigned int delay);
	unsigned int getReconnectDelay();

	bool PushMsg(MSG_INFO *pMsg);
	MSG_INFO *PopMsg();
	MSG_INFO *FrontMsg();
	void CleanMsg();
	unsigned int GetMsgCount();

	void GetStats();
private:
	virtual void OnConnect(bool bIsReconnect, sockaddr_in addrConnect)=0;
	virtual void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)=0;
	virtual void OnCommError(char* pszError)=0;
	virtual void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)=0;
	virtual void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)=0;
	virtual void OnClose(CLOSE_TYPE iCloseType)=0;
	// ������Ϣ
	virtual void OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)=0;

	void OnRecv(char *pData,int pLen);

	void setStatus(int status);
	int getStatus();
	bool checkStatus(int status);

	void DoHeartBeat();

	void DoSend();
	int DoUnpack();

	void StartThread();
	void StopThread();

	void setPowerClosePeer();

	static int ConnectThread(void *);
	static int ReConnectThread(void *);
	static int HeartBeatThread(void *);
	static int RecvThread(void *);
	static int SendThread(void *);

	// �߳�Ĭ���ԷǷ��뷽ʽ���У����̲߳���Sleep
	int BeginThread(SIX_Thread *pThread,tc_thread_func pFunc,int attr=PTHREAD_CREATE_JOINABLE);
	void EndThread(SIX_Thread *pThread);
private:
	int m_iStatus;
	bool m_bReconnect;
	bool m_StopSend;

	SIX_Thread *pConnectT;
	SIX_Thread *pReConnectT;
	SIX_Thread *pHeartBeatT;
	SIX_Thread *pRecvT;
	SIX_Thread *pSendT;

	SIX_PackageMgr *pPackageMgr;

	// �ϴ�����ʱ��
	long long m_uHeartBeatLastTime;

	// �������
	unsigned int m_uHeartBeatDelay;

	// �����������
	unsigned int m_uReconnectDelay;

	// ���ʧ�ܴ���
	unsigned int m_uUnpackErrorCount;

	// д����
	SIX_TList<MSG_INFO*> *m_sendList;

	string m_addr;
	int m_port;
	string m_name;
	string m_pass;
};