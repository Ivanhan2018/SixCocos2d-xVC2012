
#include "ConnectCenterServer.h"

#if _DEBUG	
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/CoreClientShell64_d.lib") 
#else
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/CoreClientShell64.lib") 
#endif

CConnectCenterServer::CConnectCenterServer(void)
{

}

CConnectCenterServer::~CConnectCenterServer(void)
{
	// 清理资源
}

// 响应连接成功
void CConnectCenterServer::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	COften::OutputInfo("连接中心服务器成功");
	CMD_GameServer_Register gameRegister;
	SetRegisterInfo(gameRegister);
	send_data(MAIN_GCG_GAME, SUB_GC_GAME_REGISTER, (BYTE*)(&gameRegister), sizeof(CMD_GameServer_Register));
}

// 响应连接失败
void CConnectCenterServer::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
	COften::OutputError("连接中心服务器失败");
}

// 响应发送成功
void CConnectCenterServer::OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{

}

// 响应发送失败，
void CConnectCenterServer::OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	COften::OutputError("发送消息失败");
}

// 响应关闭服务端
void CConnectCenterServer::OnClose(CLOSE_TYPE iCloseType)
{
	COften::OutputError("中心服务器已经断开");
}

// 响应通讯错误的消息
void CConnectCenterServer::OnCommError(char* pszError)
{

}

/* --------------------------------------------------------------------------
函数说明：响应收包消息
传入参数：
	pData		收到的数据
	iDataLen	收到的数据的长度
--------------------------------------------------------------------------*/
void CConnectCenterServer::OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{

}

// 设置注册信息
void CConnectCenterServer::SetRegisterInfo(CMD_GameServer_Register &gameRegister)
{
	gameRegister.lParentId = m_Config.lParentId;						// 父节点（关卡 1:初级场;2:中级场....）..
	gameRegister.iGameID = m_Config.iGameId;							// 游戏ID(比如：1捕鱼; 2斗地主; 3麻将...)
	gameRegister.iRoomType = m_Config.iRoomType;						// 游戏类型(1=积分房间、2=金币游戏、3=比赛游戏)..
	gameRegister.iRoomId = m_Config.iRoomId;							// 房间ID
	gameRegister.lRoomTeltComIp = m_Config.lRoomTeltComIp;				// 房间的中国电信IP
	gameRegister.lRoomUnicomIp = m_Config.lRoomUnicomIp;				// 房间的中国联通IP
	gameRegister.lRoomMobileIp = m_Config.lRoomMobileIp;				// 房间的中国移动IP
	gameRegister.iRoomPort = m_Config.iRoomPort;						// 房间端口
	memcpy(m_Config.szRoomName, gameRegister.szRoomName, ROOM_NAME_LEN);// 房间名字
	gameRegister.bAutoSit = m_Config.bAutoSit;							// 是否自动入座(0:不自动，需要手动点坐桌和椅子进入; 1:自动入座，不需要点击椅子号)
	gameRegister.iBasePoint = m_Config.iBasePoint;						// 倍率..
	gameRegister.iDoorsill = m_Config.iDoorsill;						// 进入门槛
	gameRegister.iMaxDoorsill = m_Config.iMaxDoorsill;					// 最高进入门槛
	gameRegister.iTables = m_Config.iTables;							// 房内桌子的数量
	gameRegister.iSeatNum = m_Config.iSeatNum;							// 每桌人数，即每桌的座位数量

	gameRegister.iEnterTradeGold = m_Config.iEnterTradeGold;			// 报名费(金币)
	gameRegister.iEnterTradePoint = m_Config.iEnterTradePoint;			// 报名费(积分)
	gameRegister.iRewardGold1 = m_Config.iRewardGold1;					// 第一名奖励
	gameRegister.iRewardGold2 = m_Config.iRewardGold2;					// 第二名奖励
}