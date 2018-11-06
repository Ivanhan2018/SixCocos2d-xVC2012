#include "SIX_Proxy.h"

SIX_Proxy *SIX_Proxy::m_pProxy = 0;

SIX_Proxy::SIX_Proxy()
{
	m_EventList = new SIX_TList<MSG_INFO*>;
	this->onEnter();
	this->onEnterTransitionDidFinish();
	this->scheduleUpdate();
}

SIX_Proxy::~SIX_Proxy()
{
	this->WaitForExit();

	CC_SAFE_DELETE(m_EventList);
	this->unscheduleUpdate();
}

SIX_Proxy *SIX_Proxy::GetInstance()
{
    if (!m_pProxy)
        m_pProxy = new SIX_Proxy();

    return m_pProxy;
}

void SIX_Proxy::update(float dt)
{
	MSG_INFO *pEvent = PopEvent();
	if (pEvent)
	{
		// 丢给脚本去处理业务逻辑
		CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
		lua_State* m_state = pEngine->getLuaState();
		if (pEngine && m_state)
		{
			lua_pushlightuserdata(m_state,this);
			lua_pushinteger(m_state,pEvent->m_MainCode);
			lua_pushinteger(m_state,pEvent->m_SubCode);
			lua_pushlightuserdata(m_state,pEvent->m_Data);
			lua_pushinteger(m_state,pEvent->m_DataLen);
			pEngine->executeGlobalFunction("OnSocketRecv",5);
		}
		CC_SAFE_DELETE(pEvent);
	}
}

void SIX_Proxy::PushEvent(MSG_INFO *pEvent)
{
	if (pEvent)
	{
		m_EventList->Push(pEvent);
	}
}

MSG_INFO *SIX_Proxy::PopEvent()
{
	return m_EventList->Pop();
}

MSG_INFO *SIX_Proxy::FrontEvent()
{
	return m_EventList->Front();
}

unsigned int SIX_Proxy::GetEventCount()
{
	return m_EventList->GetCount();
}

void SIX_Proxy::WaitForExit()
{
	// 等待事件处理完成
	while (m_EventList->GetCount()){}
}