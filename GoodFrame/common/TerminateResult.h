/********************************************************************
	created:	2013/01/24
	created:	23:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		ºî¹ú½­
	
	purpose:	
*********************************************************************/

#ifndef TERMINATE_RESULT_H
#define TERMINATE_RESULT_H

#include "./CompleteResult.h"

class  __declspec(dllexport) CTerminateResult : public CCompleteResult
{
public:
	CTerminateResult(void);
	~CTerminateResult(void);

public:
	virtual int	OnIoComplete(DWORD dwBytesTransfered);
};

#endif