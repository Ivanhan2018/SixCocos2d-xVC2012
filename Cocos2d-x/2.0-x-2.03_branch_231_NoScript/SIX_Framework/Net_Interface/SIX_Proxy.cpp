#include "SIX_Proxy.h"
#include <sys/timeb.h>		// add by cxf
#include <SIX_ClientBase.h>

SIX_Proxy *SIX_Proxy::m_pProxy = 0;

SIX_Proxy::SIX_Proxy()
{
	m_EventList = new SIX_TList<MSG_INFO*>;
	this->onEnter();
	this->onEnterTransitionDidFinish();
	//this->scheduleUpdate();
	schedule(schedule_selector(SIX_Proxy::update), 0.01f);

	changeScene = false;
}

SIX_Proxy::~SIX_Proxy()
{
	this->HandlePacketRaw();
	this->unscheduleUpdate();
	CC_SAFE_DELETE(m_EventList);
}

SIX_Proxy *SIX_Proxy::GetInstance()
{
    if (!m_pProxy)
        m_pProxy = new SIX_Proxy();

    return m_pProxy;
}

void SIX_Proxy::update(float dt)
{
	HandlePacketRaw();
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

void SIX_Proxy::HandlePacketRaw()
{
	// 等待事件处理完成
	while (m_EventList->GetCount())
	{
		MSG_INFO *pEvent = PopEvent();
		if (pEvent)
		{
			SIX_ClientBase *pClient = pEvent->m_pClient;
			if (!pClient)
			{
				CC_SAFE_DELETE(pEvent);
				continue;
			}

			pClient->HandlePacketRaw(pEvent->m_MainCode,pEvent->m_SubCode,pEvent->m_Data,pEvent->m_DataLen);
			CC_SAFE_DELETE(pEvent);

			// 先stop断开，再从这里让logic指针释放掉自身单例
			if (pClient->getNeedExit())
			{
				pClient->OnRelease();
			}
		}
	}
}

void SIX_Proxy::SetChangeScene(bool IsChangeScene)
{
	changeScene=IsChangeScene;
}