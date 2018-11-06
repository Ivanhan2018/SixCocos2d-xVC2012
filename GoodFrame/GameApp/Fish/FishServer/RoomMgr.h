
#ifndef CROOM_MGR_H
#define CROOM_MGR_H

#include "./IRoomMgr.h"
#include "./GameSkeletonID.h"
#include "./TaskMsgResult.h"

class CRoomMgr : public IRoomMgr
{
public:
	CRoomMgr(void);
	~CRoomMgr(void);

public:
	//--- 回调函数 -----------------------------------------------

	// 对端关闭之前一刹那的响应
	virtual int OnCloseBefore(LONGLONG lUserId);

	// 响应房间消息
	virtual TASK_MSG_RESULT OnRoomMsg(CMemBlock*& pMsgBlock);

	// 响应房间管理服务器的消息
	virtual void OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);



public:

};

#endif