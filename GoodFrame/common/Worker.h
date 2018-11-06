/********************************************************************
	created:	2013/10/07
	created:	7:10:2013   15:46
	filename: 	E:\SixDivisions\GoodFRame\common\Worker.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	Worker
	file ext:	h
	author:		侯国江
	
	purpose:	工人，继承于任务
*********************************************************************/

#ifndef WORKER_H
#define WORKER_H

#include "./BasicLogic.h"
#include "./SelfModuleID.h"
#include "./TaskMsgResult.h"

class CGeneralWork;

class __declspec(dllexport) CWorker : public CBasicLogic
{
public:
	CWorker(void);
	~CWorker(void);

	void set_general_work(CGeneralWork* pGeneralWork);

	// 响应任务消息
	virtual TASK_MSG_RESULT OnTask(CMemBlock*& pMsgBlock);

private:
	CGeneralWork*	m_pGeneralWork;
};

#endif