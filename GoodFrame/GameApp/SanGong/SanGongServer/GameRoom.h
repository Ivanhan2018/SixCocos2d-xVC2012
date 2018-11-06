
#ifndef CGAME_ROOM_H
#define CGAME_ROOM_H

#include "./IRoomMgr.h"
#include "./GameSkeletonID.h"
#include "./TaskMsgResult.h"

class CGameRoom : public IRoomMgr
{
public:
	CGameRoom(void);
	~CGameRoom(void);

public:
	//--- 回调函数 -----------------------------------------------

	// 对端关闭之前一刹那的响应
	virtual int OnCloseBefore(LONGLONG lUserId);

	// 响应房间消息
	virtual TASK_MSG_RESULT OnRoomMsg(CMemBlock*& pMsgBlock);

	// 响应房间管理服务器的消息
	virtual void OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

};

#endif