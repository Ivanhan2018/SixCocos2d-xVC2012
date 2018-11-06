
#ifndef FISH_CLIENT_H
#define FISH_CLIENT_H

#include "./CloseType.h"
#include "./BaseTableClient.h"
#include "./UserInfo.h"
#include "../GameMsg/CMD_SanGong.h"	//add by Ivan_han

struct SinglePlayer
{
	SinglePlayer()
	{
		Init();
	}
	void Init()
	{
		memset(this, 0, sizeof(*this));
	}
	//TChip	m_lGameScore;				//积分信息
	//TChip	m_lUserChipIn;				//下注信息
	//TPlayStatus	m_cbPlayStatus;
	char m_szAccounts[32];//玩家名字
	//TCardData m_cbUserCardData[3];		//用户扑克
	//unsigned char m_cbUserFinish;//完成标志
	//unsigned char m_cbUserBanker;//换庄标志={0,1}
	//unsigned char m_cbUserContinue;//继续标志
};

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
	int ConnectRoom(string str[5]);
private:
	//vector<USER_INFO> vecUserInfo;	// 用户列表

public:
	//游戏状态
	e_GameState m_byGameState;

	SinglePlayer m_Players[GAME_PLAYER_COUNT];

	//当前客户端的用户信息
	USER_INFO_SIM m_MeUserInfo;

	SERVER_ROOM_INFO_SIM m_roomInfo;

	//庄家用户,S:用户坐下或收到抢庄消息时会写这个变量，C:收到庄家用户信息消息时会写这个变量
	TChairID m_wBankerUser;

	//游戏局数
	unsigned short int	m_wDrawCount;

	//true机器人用户，false普通正常用户
	bool m_IsAndroid;
};

#endif
