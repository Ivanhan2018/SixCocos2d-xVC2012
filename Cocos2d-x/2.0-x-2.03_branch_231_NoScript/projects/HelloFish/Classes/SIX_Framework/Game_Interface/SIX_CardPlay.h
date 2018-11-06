/***********************************************
Name：SIX_CardPlay
Desc：扑克玩法逻辑，SIX_TVector模版存储UI结构指针
Auth：Cool.Cat@2013-10-10
***********************************************/
#pragma once
#include "SIX_CardSuit.h"
#include "SIX_TVector.h"

class SIX_CardPlay:public TSingleton<SIX_CardPlay>,public SIX_TVector<void*>
{
public:
	virtual ~SIX_CardPlay();
};