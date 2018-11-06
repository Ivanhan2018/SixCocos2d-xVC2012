
/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\IDbAnyGame.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	IDbAnyGame
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef I_DB_ANY_GAME_H
#define I_DB_ANY_GAME_H


#include "./MemBlockPool.h"
#include "./EasyDataTime.h"

#include "./DbSkeleton.h"

// �������ݿ�ľ���ʵ��
class __declspec(dllexport) IDbAnyGame
{
public:
	IDbAnyGame(void);
	~IDbAnyGame(void);

public:

	// ��Ӧ���ݿ���Ϣ
	TASK_MSG_RESULT OnDbRoomMsg(CDB_Connection* pConnect, const CCoreServer* pCoreServer, CMemBlockPool* pMsgPool, CMemBlock*& pMsgBlock);

	// Ͷ��������Ϣ������ϢͶ��ָ��������ģ��
	TASK_MSG_RESULT post_work_msg(const CCoreServer* pCoreServer, int iTaskModuleID, CMemBlock*& pMsgBlock);


private:

};

#endif