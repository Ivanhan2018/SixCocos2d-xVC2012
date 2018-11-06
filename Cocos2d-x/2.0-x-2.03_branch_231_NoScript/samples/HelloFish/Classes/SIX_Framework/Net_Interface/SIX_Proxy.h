/***********************************************
Name£ºSIX_Proxy
Desc£ºMultithreading and UI interaction
Auth£ºCool.Cat@2013-04-16
***********************************************/
#pragma once
#include "cocos2d.h"
#include <SIX_Typedef.h>
#include <SIX_TList.h>
#include <SIX_PackageMgr.h>
#include <SIX_MsgBox.h>

USING_NS_CC;

class SIX_Proxy:public CCNode,public TSingleton<SIX_Proxy>
{
public:
	SIX_Proxy();
	~SIX_Proxy();
public:
	static SIX_Proxy *GetInstance();
	void PushEvent(MSG_INFO *pEvent);
	MSG_INFO *PopEvent();
	MSG_INFO *FrontEvent();
	unsigned int GetEventCount();
	void HandlePacketRaw();

	bool IsChangeScene(){return changeScene;}
	void SetChangeScene(bool IsChangeScene){changeScene=IsChangeScene;}

private:
	static SIX_Proxy* m_pProxy;
	virtual void update(float);
private:
	SIX_TList<MSG_INFO*> *m_EventList;
	bool changeScene;
};