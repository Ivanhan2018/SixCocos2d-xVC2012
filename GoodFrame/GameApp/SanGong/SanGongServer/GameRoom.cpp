
#include "PublicHead.h"
#include "GameRoom.h"
#include "GameTable.h"

CGameRoom::CGameRoom(void)
{
}

CGameRoom::~CGameRoom(void)
{
}

// �Զ˹ر�֮ǰһɲ�ǵ���Ӧ
int CGameRoom::OnCloseBefore(LONGLONG lUserId)
{
	printf("lUserId=%I64d �ر�֮ǰһɲ�ǵ���Ӧ \n", lUserId);

	return 0;
}
/* --------------------------------------------------------------------------
����˵������Ӧ������Ϣ
����������
	pMsgBlock	��Ϣ�飬ע���Զ�����źţ��������أ����Բο� TASK_MSG_RESULT ��ֵ
����ֵ
    �ο� TASK_MSG_RESULT ö��
--------------------------------------------------------------------------*/
TASK_MSG_RESULT CGameRoom::OnRoomMsg(CMemBlock*& pMsgBlock)
{
	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// �Զ�����ź�
	int iRes = 0;

	LONGLONG lChannelNo;
	int iMainCode = 0;
	int iSubCode = 0;
	BYTE* pData = NULL;
	int iDataLen = 0;

	// ����ں���Ϣ����ʵ����
	iRes = m_pMsgPool->get_core_msg_data(pMsgBlock, &lChannelNo, &iMainCode, &iSubCode, pData, &iDataLen);
	assert(0==iRes);
	if(0!=iRes)
		return stTaskMsgResult;

	return stTaskMsgResult;
}

// ��Ӧ����������������Ϣ
void CGameRoom::OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{

}

