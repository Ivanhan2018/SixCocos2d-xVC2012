
#include "./PublicHead.h"
#include "./RoomMgr.h"
#include "./FishTable.h"
#include "./EndlessLoopGuard.h"	// 死循环守护

CRoomMgr::CRoomMgr(void)
{
}

CRoomMgr::~CRoomMgr(void)
{
}

// 对端关闭之前一刹那的响应
int CRoomMgr::OnCloseBefore(LONGLONG lUserId)
{
	printf("lUserId=%I64d 关闭之前一刹那的响应 \n", lUserId);

	return 0;
}
/* --------------------------------------------------------------------------
函数说明：响应房间消息
传出参数：
	pMsgBlock	消息块，注意自动归池信号，若不想归池，可以参考 TASK_MSG_RESULT 的值
返回值
    参考 TASK_MSG_RESULT 枚举
--------------------------------------------------------------------------*/
TASK_MSG_RESULT CRoomMgr::OnRoomMsg(CMemBlock*& pMsgBlock)
{
	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// 自动归池信号
	int iRes = 0;

	LONGLONG lChannelNo;
	int iMainCode = 0;
	int iSubCode = 0;
	BYTE* pData = NULL;
	int iDataLen = 0;

	// 获得内核消息的真实数据
	iRes = m_pMsgPool->get_core_msg_data(pMsgBlock, &lChannelNo, &iMainCode, &iSubCode, pData, &iDataLen);
	assert(0==iRes);
	if(0!=iRes)
		return stTaskMsgResult;

	switch(iSubCode)
	{
	case ROOM_SUB_MY_TEST:	// 测试
		{
			printf("测试 OnRoomMsg \n");

			return stTaskMsgResult;	// 此时的值应该是 TMR_CONTINUE_PUT
			break;
		}
	}

	return stTaskMsgResult;
}

// 响应房间管理服务器的消息
void CRoomMgr::OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case ROOM_SUB_MY_TEST:	// 测试
		{
			printf("测试 CRoomMgr::OnRMS \n");
			break;
		}
	}
}

