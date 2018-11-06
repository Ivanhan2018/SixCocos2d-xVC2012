
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
	//--- �ص����� -----------------------------------------------

	// �Զ˹ر�֮ǰһɲ�ǵ���Ӧ
	virtual int OnCloseBefore(LONGLONG lUserId);

	// ��Ӧ������Ϣ
	virtual TASK_MSG_RESULT OnRoomMsg(CMemBlock*& pMsgBlock);

	// ��Ӧ����������������Ϣ
	virtual void OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

};

#endif