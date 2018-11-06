
/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:45
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\LogicSkeleton.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	LogicSkeleton
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef LOGIC_SKELETON_H
#define LOGIC_SKELETON_H

//#include "./BasicLogic.h"
#include "./GeneralWork.h"
#include "IRoomMgr.h"

class CGameServerSkeleton;

class CLogicSkeleton : public CGeneralWork // CBasicLogic
{
public:
	CLogicSkeleton(void);
	~CLogicSkeleton(void);
public:

	// ��Ӧ������Ϣ
	virtual TASK_MSG_RESULT OnTask(CMemBlock*& pMsgBlock);

public:
	void set_game_server_skeleton(CGameServerSkeleton* p);

private:
	CGameServerSkeleton* m_pGameServerSkeleton;	// ��Ϸ����Ǽ�
};

#endif