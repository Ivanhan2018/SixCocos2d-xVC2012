
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
	//--- �ص����� -----------------------------------------------

	// �Զ˹ر�֮ǰһɲ�ǵ���Ӧ
	virtual int OnCloseBefore(LONGLONG lUserId);

	// ��Ӧ������Ϣ
	virtual TASK_MSG_RESULT OnRoomMsg(CMemBlock*& pMsgBlock);

	// ��Ӧ����������������Ϣ
	virtual void OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);



public:

};

#endif