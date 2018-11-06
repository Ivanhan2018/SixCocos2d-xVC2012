
#include "./PublicHead.h"
#include "./RoomMgr.h"
#include "./FishTable.h"
#include "./EndlessLoopGuard.h"	// ��ѭ���ػ�

CRoomMgr::CRoomMgr(void)
{
}

CRoomMgr::~CRoomMgr(void)
{
}

// �Զ˹ر�֮ǰһɲ�ǵ���Ӧ
int CRoomMgr::OnCloseBefore(LONGLONG lUserId)
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
TASK_MSG_RESULT CRoomMgr::OnRoomMsg(CMemBlock*& pMsgBlock)
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

	switch(iSubCode)
	{
	case ROOM_SUB_MY_TEST:	// ����
		{
			printf("���� OnRoomMsg \n");

			return stTaskMsgResult;	// ��ʱ��ֵӦ���� TMR_CONTINUE_PUT
			break;
		}
	}

	return stTaskMsgResult;
}

// ��Ӧ����������������Ϣ
void CRoomMgr::OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case ROOM_SUB_MY_TEST:	// ����
		{
			printf("���� CRoomMgr::OnRMS \n");
			break;
		}
	}
}

