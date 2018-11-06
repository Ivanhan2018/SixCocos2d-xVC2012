
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

	// 桌子消息
	virtual void OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

public:

	//--- 游戏逻辑部分 ---------------------------------

	// 处理房间消息
	void handle_room_msg(int iSubCode, const BYTE* pData, int iDataLen);

	// 处理房间涉及写数据库的消息
	void handle_write_db_msg(int iSubCode, const BYTE* pData, int iDataLen);

	// 处理桌子消息
	void handle_table_msg(int iSubCode, const BYTE* pData, int iDataLen);

	// 处理管理员消息
	void handle_magager_msg(int iSubCode, const BYTE* pData, int iDataLen);

public:

	// 测试
	int test();

	// 开火
	int fire();

	//  发送测试消息
	void send_test_msg(int iType);

	// 发射一发炮弹，add by Ivan_han
	//int fire(Req_UserShoot &req);

private:
	vector<USER_INFO> vecUserInfo;	// 用户列表

	

};

#endif
