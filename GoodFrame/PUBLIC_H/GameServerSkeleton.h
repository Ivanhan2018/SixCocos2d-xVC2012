
/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:43
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\GameServerSkeleton.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	GameServerSkeleton
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef SAMPLE_SERVER_H
#define SAMPLE_SERVER_H

// 解决 <windows.h>中包含了<winsock.h>头文件从而与 #include "Winsock2.h" 相冲突的问题
// 一定要放在 #include <windows.h> 之前
#define WIN32_LEAN_AND_MEAN

#include "./CoreServer.h"	// 内核服务端的头文件
#include "./Singleton.h"

#include "./ClientToRMS.h"
#include "./LogicSkeleton.h"
#include "./DbSkeleton.h"

#include "./IRoomMgr.h"
#include "./IDbAnyGame.h"

class IBaseTable;

// 游戏服务骨架
class __declspec(dllexport) CGameServerSkeleton  : public CCoreServer 
{
public:
	friend class CClientToRMS;
public:
	CGameServerSkeleton(void);
	~CGameServerSkeleton(void);

public:

	// 获得房间配置
	ROOM_CONFIG get_room_config();

	/* --------------------------------------------------------------------------
	函数说明：设置房间配置文件的参数
	输入参数：
		roomConfig	房间配置参数，参考 RoomConfig.ini
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int set_room_config(const char *roomConfig="Config/RoomConfig.ini");

	// 游戏服务骨架的版本号
	int get_skeleton_ver(char* pszVerNo, int iLen);

	// 连接房管服务器 RMS（RoomMgrServer ）
	int create_client_to_rms(const CLIENT_TO_RMS_PARAM& rms);

	// 断开房管服务器 RMS（RoomMgrServer ）
	int destroy_client_to_rms();

	/* --------------------------------------------------------------------------
	函数说明：初始化，必需在 start 函数之前执行本函数
	返回值：
		成功则返回 0，失败返回错误码如下：
			10  建立消息池失败
	--------------------------------------------------------------------------*/
	virtual int init();

	// 释放资源，必需在 stop 函数之后执行本函数
	virtual int uninit();

	// 开始，必需在 init  函数之后执行本函数
	virtual int start();

	// 结束，必需在 uninit 函数之前执行本函数
	virtual int stop();

	// 销毁所有桌子的游戏开始的定时器
	void destroy_game_start_timer();

	// 获得房间管理的指针
	IRoomMgr* CGameServerSkeleton::get_room_mgr();

public:
	//--- 子类要继承的纯虚函数 -----------------------------------

	// 建立房间实例
	virtual IRoomMgr* create_room_mgr(SERVER_ROOM_INFO serverRoomInfo) = 0;

	// 销毁房间实例
	virtual void destroy_room_mgr() = 0;

	// 建立桌子群实例
	virtual int create_table() = 0;

	// 销毁桌子群实例
	virtual void destroy_table() = 0;

	// 建立数据库实例
	virtual IDbAnyGame*	create_db() = 0;

	// 销毁数据库实例
	virtual void destroy_db() = 0;

	// 房管服的信息获取完毕
	virtual int OnRoomMgrServerOk(SERVER_ROOM_INFO serverRoomInfo, ROOM_CONFIG roomConfig) = 0;

public:
	//--- 回调函数 -----------------------------------------------

	// 响应对端已关闭了
	virtual int OnClose(LONGLONG lChannelNo, SOCKET socketClose, CLOSE_TYPE iCloseType);

	// 响应发送成功
	virtual void OnSend(LONGLONG lChannelNo, const CMemBlock* pSendBlock);

	// 响应发送失败
	virtual void OnSendFailed(LONGLONG lChannelNo, const CMemBlock* pSendBlock);

	// 响应连接成功
	virtual void OnConnect(LONGLONG lChannelNo, const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr);	

	// 响应连接失败
	virtual void OnConnectFail(const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr, int iErrorCode);

	// 定时器响应
	virtual int OnTimer(LONGLONG iIDEvent);

	/* --------------------------------------------------------------------------
	函数说明：响应无心跳至死
	传入参数：
		lChannelNo	被服务端断开的通道号
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int OnNoHeartbeatDie(LONGLONG lChannelNo);

	// 心跳消息
	virtual int OnIsHeartbeat(long long lChannelNo);

	/* --------------------------------------------------------------------------
	函数说明：响应收包消息
	传入参数：
		lChannelNo
	传出参数：
		pRecv		消息块，已经是原子包了。注意：要用底层框架的机制归池
	--------------------------------------------------------------------------*/
	virtual void OnRecv(LONGLONG lChannelNo, CMemBlock*& pRecv);

	/* --------------------------------------------------------------------------
	函数说明：响应房间管理服务器的消息
	传入参数：
		pData		收到的数据
		iDataLen	收到的数据的长度
	--------------------------------------------------------------------------*/
	virtual void OnSkeletonRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	


public:
	// 设置游戏开始的类型，iType 参考 GAME_BEGIN_TYPE_AUTO 等
	void game_begin_type(int iType);

	// 获得游戏开始的类型， 返回值参考 GAME_BEGIN_TYPE_AUTO 等
	int game_begin_type();

public:

	CClientToRMS* m_pClientToRMS;
	

	CLogicSkeleton*		m_pLogic;		// 逻辑
	CDbSkeleton*		m_pMyDB;		// 数据库

	IRoomMgr*	m_pRoomMgr;		// 房间管理
	IDbAnyGame*	m_pDbAnyGame;

private:
	ROOM_CONFIG			m_stRoomConfig;		// 房间配置文件

	int	m_iVerNo;	// 版本号
	int	m_iGameBeginType;	// 游戏开始的类型，参考 GAME_BEGIN_TYPE_AUTO 等

	bool m_bStartFinish;	// 启动完成
};

#endif