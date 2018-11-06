
/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\DbSkeleton.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	DbSkeleton
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef DB_SKELETON_H
#define DB_SKELETON_H

//#include "./BasicDB.h"
#include "GeneralDb.h"
#include "./GameSkeletonMsgCode.h"

class CGameServerSkeleton;

// ���ݿ����
class __declspec(dllexport)  CDbSkeleton : public CGeneralDB//CBasicDB
{
public:
	CDbSkeleton(void);
	~CDbSkeleton(void);

	int init_after_start_db();
	// ��Ӧ������Ϣ
	virtual TASK_MSG_RESULT OnTask(CMemBlock*& pMsgBlock);

public:
	void set_game_server_skeleton(CGameServerSkeleton* p);

private:
	CGameServerSkeleton* m_pGameServerSkeleton;	// ��Ϸ����Ǽ�
};

#endif