/*********************************************************
Name��SIX_ClientLogic
Desc��SOCKET�����ӿڣ�����������Ϣ����SIX_Proxy�����У�
      ��UI�̴߳���
Auth��Cool.Cat@2013-05-08
*********************************************************/
#pragma once

#include <SIX_Typedef.h>
#include <SIX_PackageMgr.h>
#include <SIX_Proxy.h>
#include <EasyDataTime.h>
#include <BaseTableClient.h>
#include <UserInfo.h>

class SIX_ClientLogic : public IBaseTableClient
{
public:
	SIX_ClientLogic(void);
	~SIX_ClientLogic(void);

public:
	virtual void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);
	virtual void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);
	virtual void OnCommError(char* pszError);
	virtual void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	virtual void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	virtual void OnClose(bool bClientClose);
	// ������Ϣ
	virtual void OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	bool IsNeedExit();
	int stop();

	//--- ��Ϸ�߼����� ---------------------------------

	// ����
	int test();

	// ����
	int fire();

	int RandomUser(char* pszName);
private:
	vector<USER_INFO> vecUserInfo;	// �û��б�
	bool m_NeedExit;
};