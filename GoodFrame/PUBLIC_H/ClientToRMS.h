/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\ClientToRMS.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	ClientToRMS
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef CLIENT_TO_RMS_H
#define CLIENT_TO_RMS_H

#include "./CoreClient.h"
#include "./GameSkeletonID.h"

#include "./EasyDataTime.h"
#include "./RoomInfo.h"

#include <vector>
using std::vector;

class CGameServerSkeleton;

// 客户端，目的是连接房管服务器 RMS（RoomMgrServer ）
class CClientToRMS : public CCoreClient	// 不用单键模式，是因为一个工程中可能有多个客户端。
{
public:
	friend class CGameServerSkeleton;

public:
	CClientToRMS(void);
	~CClientToRMS(void);

protected:		
	//--- 回调函数 ------------------------

	// 响应连接成功
	void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);

	// 响应连接失败
	void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);

	// 响应发送成功
	void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应发送失败，
	void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应关闭服务端
	void OnClose(CLOSE_TYPE iCloseType);

	/* --------------------------------------------------------------------------
	函数说明：响应收包消息
	传入参数：
		pData		收到的数据
		iDataLen	收到的数据的长度
	--------------------------------------------------------------------------*/
	void OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应通讯错误的消息
	void OnCommError(char* pszError);

public:
	// 设置游戏服务骨架的指针
	void set_truck_server(CGameServerSkeleton* pTrunkServer);

	// 设置房间配置文件的参数
	void set_room_config(const ROOM_CONFIG& roomConfig);

public:
	SERVER_ROOM_INFO	m_stServerRoomInfo;	// 房间信息
	ROOM_CONFIG			m_stRoomConfig;		// 房间配置文件
private:
	CGameServerSkeleton* m_pTrunkServer;

	LONGLONG	lConnTime;	// 连上房管的时间
};

#endif