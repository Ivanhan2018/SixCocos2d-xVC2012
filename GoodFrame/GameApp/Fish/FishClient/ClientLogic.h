
#ifndef FISH_CLIENT_H
#define FISH_CLIENT_H

#include "./CloseType.h"
#include "./BaseTableClient.h"
#include "./UserInfo.h"
#include "../GameMsg/ProFish.h"	//add by Ivan_han

class CClientLogic : public IBaseTableClient
{
public:
	CClientLogic(void);
	~CClientLogic(void);

public:
	
	virtual void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);
	virtual void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);
	virtual void OnCommError(char* pszError);
	virtual void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	virtual void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	virtual void OnClose(CLOSE_TYPE iCloseType);

	// ������Ϣ
	virtual void OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

public:

	//--- ��Ϸ�߼����� ---------------------------------

	// ��������Ϣ
	void handle_room_msg(int iSubCode, const BYTE* pData, int iDataLen);

	// �������漰д���ݿ����Ϣ
	void handle_write_db_msg(int iSubCode, const BYTE* pData, int iDataLen);

	// ����������Ϣ
	void handle_table_msg(int iSubCode, const BYTE* pData, int iDataLen);

	// �������Ա��Ϣ
	void handle_magager_msg(int iSubCode, const BYTE* pData, int iDataLen);

public:

	// ����
	int test();

	// ����
	int fire();

	//  ���Ͳ�����Ϣ
	void send_test_msg(int iType);

	// ����һ���ڵ���add by Ivan_han
	//int fire(Req_UserShoot &req);

private:
	vector<USER_INFO> vecUserInfo;	// �û��б�

	

};

#endif
