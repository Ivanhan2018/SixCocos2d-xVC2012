/***********************************************
Name��SIX_CardPlay
Desc���˿��淨�߼���SIX_TVectorģ��洢UI�ṹָ��
Auth��Cool.Cat@2013-10-10
***********************************************/
#pragma once
#include "SIX_CardSuit.h"
#include "SIX_TVector.h"

class SIX_CardPlay:public TSingleton<SIX_CardPlay>,public SIX_TVector<void*>
{
public:
	virtual ~SIX_CardPlay();
};