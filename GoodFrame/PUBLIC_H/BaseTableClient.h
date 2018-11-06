
#ifndef BASE_DESK_CLIENT
#define BASE_DESK_CLIENT

#include "./CloseType.h"
#include "./UserInfo.h"
#include "./TableInfo.h"
#include "./RoomInfo.h"
#include "./GameSkeletonMsgCode.h"

class CGameClientTransfer;

#ifdef WIN32
class  __declspec(dllexport) IBaseTableClient
#else
class  IBaseTableClient
#endif
{
public:
	friend class CGameClientTransfer;

public:
	IBaseTableClient(void);
	~IBaseTableClient(void);

public:

	virtual void OnConnect(bool bIsReconnect, sockaddr_in addrConnect)=0;
	virtual void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)=0;
	virtual void OnCommError(char* pszError)=0;
	virtual void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)=0;
	virtual void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)=0;
	virtual void OnClose(CLOSE_TYPE iCloseType)=0;
	/* --------------------------------------------------------------------------
	函数说明：响应收包消息
	传入参数：
		iMainCode	消息主码
		iSubCode	消息辅助码
		pData		包体数据
		iDataLen	包体数据的长度
	--------------------------------------------------------------------------*/
	virtual void OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;

	int init(const CLIENT_ROOM_INFO& vRoomClientInfo, const CLIENT_FRAME_PARAM& vFrameParam);

	int start();
	
	int stop();

	//// 发送数据
	//int send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);
	// Add by Cool.Cat
	int send_data(int iMainCode, int iSubCode, void *pData, int iDataLen);
	int send_data(int iMainCode, int iSubCode);

	/* --------------------------------------------------------------------------
	函数说明：关闭服务端
	传入参数：
		bClientClose	TRUE表示客户端主动关闭，FALSE表示被服务端关闭的
	返回值：
		成功则返回 TRUE，否则返回 FALSE 。
	--------------------------------------------------------------------------*/
	bool close(CLOSE_TYPE iCloseType);

	/* --------------------------------------------------------------------------
	函数说明：登录房间
	传入参数：
		玩家ID
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int login_room();

	// 离开房间
	int leave_room();

	// 入座
	int sit_down(int iTableNo, int iSeatNo);

	/* --------------------------------------------------------------------------
	函数说明：能够开始游戏，坐下后的消息，客户端要等到初始化完毕后，发此消息，服务端才发鱼
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int raise_hand();

	// 离座
	int leave_seat();

	// 申请房间内的用户列表
	int query_user_list();

	// 写分
	int write_score(const CMD_WRITE_SCORE& score);

public:

	// 踢一个玩家离座或离房
	int tick_one_leave_seat(int iTableNo, int iSeatNo);

	// 踢一桌玩家离座
	int tick_table_leave_seat(int iTableNo);

	// 踢所有在座的玩家离座
	int tick_all_leave_seat();

	// 踢玩家离房
	int tick_user_out_room(int iTableNo, int iSeatNo);

	// 踢一桌内所有的玩家离房
	int tick_user_out_room(int iTableNo);

	// 踢所有的玩家离房
	int tick_user_out_room();

	//add by Ivan_han 20130929
	void setUserID(LONGLONG lUserID);

public:
	LOGIN_ROOM_SUCC	m_stLoginSucc;	// 登录成功的一些信息

	CLIENT_ROOM_INFO GetRoomInfo();

private:
	CGameClientTransfer* m_pGameClientTransfer;

	CLIENT_ROOM_INFO	m_stRoomInfo;
	
	LONGLONG m_lUserID;	// 用户ID，在服务端唯一的合法标识，

};

#endif