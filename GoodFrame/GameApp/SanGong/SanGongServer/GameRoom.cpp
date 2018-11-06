
#include "PublicHead.h"
#include "GameRoom.h"
#include "GameTable.h"

CGameRoom::CGameRoom(void)
{
}

CGameRoom::~CGameRoom(void)
{
}

// 对端关闭之前一刹那的响应
int CGameRoom::OnCloseBefore(LONGLONG lUserId)
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
TASK_MSG_RESULT CGameRoom::OnRoomMsg(CMemBlock*& pMsgBlock)
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

	return stTaskMsgResult;
}

// 响应房间管理服务器的消息
void CGameRoom::OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{

}

