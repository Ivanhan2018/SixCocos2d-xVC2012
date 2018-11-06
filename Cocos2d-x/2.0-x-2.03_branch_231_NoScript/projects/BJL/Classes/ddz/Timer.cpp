#include "Timer.h"
#include "MyTools.h"
using namespace std;
using namespace texture_name;

Timer::Timer()
{

}

Timer::~Timer()
{
	RemoveObject();
}

bool Timer::init()
{
	//if (!CCNode::init())
	//{
	//	return false;
	//}
	g_timerNode = CCNode::create();
	//时钟
	CCSprite * timer = CCSprite::createWithSpriteFrameName(s_timer);
	g_timerNode->addChild(timer);
	//时间数字
	m_number = CCLabelAtlas::create("0",texture_name::s_timerNumber,14,23,'0');
	m_number->setAnchorPoint(ccp(0.5f,0.5f));
	m_number->setPosition(CCPointZero);
	m_number->setPositionY(-2.0f);
	g_timerNode->addChild(m_number);
	m_timeKey= 0;
	m_gameState =Game_null;
	this->addChild(g_timerNode);

	m_nikeSprite = CCSprite::create("BJL/BJL_15.png");
	m_nikeSprite->setPosition(ccp(timer->getPositionX()+80,timer->getPositionY()-15));
	m_nikeSprite->setScale(0.6);
	this->addChild(m_nikeSprite);
	AddObject();
	return true;
}
void Timer::AddObject()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(Timer::setCCteefTag),"MI_setCCteefTag",NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(Timer::setPlaceScore),"MI_setPlaceScore",NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(Timer::setCardTalayer),"MI_setCardTalayer",NULL);

}
void Timer::RemoveObject()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "MI_setCCteefTag");
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "MI_setPlaceScore");
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "MI_setCardTalayer");
}
void Timer::start(int userId, int t,Game_State gameState,int key)
{
	this->unscheduleAllSelectors();
	g_timerNode->stopAllActions();
	m_time = t;
	m_gameState = gameState;
	m_UserID =userId;
	m_timeKey= key;
	CCString str;
	str.initWithFormat("%d",m_time--);
	m_number->setString(str.getCString());
	this->schedule(schedule_selector(Timer::time_schedule),1.0f);
}

void Timer::time_schedule(float t)
{
	if (m_time>0)
	{
		CCString str;
		str.initWithFormat("%d",m_time--);
		m_number->setString(str.getCString());
		if (m_time<5)
		{
			m_number->runAction(CCSequence::create(CCScaleTo::create(0.2f,1.2f),CCScaleTo::create(0.2f,1.0f),NULL));
			if (g_timerNode->numberOfRunningActions()<=0)
			{
				g_timerNode->runAction(CCShake::create(10.0f,1));
			}
		}
	}else{
		this->unschedule(schedule_selector(Timer::time_schedule));
		g_timerNode->stopAllActions();
		this->setVisible(false);
		m_nikeSprite->setVisible(false);
		if (m_UserID ==1)
		{
			CCtimeCallBack* _callBackData=CCtimeCallBack::create(msgToview_TimeCallBack);
			_callBackData->m_gameState =m_gameState;
			_callBackData->m_timeKey =m_timeKey;
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,_callBackData);
		}
	}
}
void Timer::setCCteefTag(CCObject *obj)
{
	m_nikeSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_15.png"));
	m_nikeSprite->setVisible(true);

}
void Timer::setCardTalayer( CCObject *obj )
{
	m_nikeSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_16.png"));
	m_nikeSprite->setVisible(true);

}

void Timer::setPlaceScore( CCObject *obj )
{
	m_nikeSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_14.png"));
	m_nikeSprite->setVisible(true);
}