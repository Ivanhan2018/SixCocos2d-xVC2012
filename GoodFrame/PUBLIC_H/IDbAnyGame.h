
/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\IDbAnyGame.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	IDbAnyGame
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef I_DB_ANY_GAME_H
#define I_DB_ANY_GAME_H


#include "./MemBlockPool.h"
#include "./EasyDataTime.h"

#include "./DbSkeleton.h"

// 捕鱼数据库的具体实现
class __declspec(dllexport) IDbAnyGame
{
public:
	IDbAnyGame(void);
	~IDbAnyGame(void);

public:

	// 响应数据库消息
	TASK_MSG_RESULT OnDbRoomMsg(CDB_Connection* pConnect, const CCoreServer* pCoreServer, CMemBlockPool* pMsgPool, CMemBlock*& pMsgBlock);

	// 投递任务消息，将消息投给指定的任务模块
	TASK_MSG_RESULT post_work_msg(const CCoreServer* pCoreServer, int iTaskModuleID, CMemBlock*& pMsgBlock);


private:

};

#endif