#include "CCTouchSprite.h"
USING_NS_CC;

CCTouchSprite* CCTouchSprite::createWithPic(const char *fileName, int row, int cell)
{
	return CCTouchSprite::createWithPic(fileName, row, cell, NULL, NULL);
}

CCTouchSprite* CCTouchSprite::createWithPic(const char *fileName, int row, int cell, CCObject* rec, SEL_CallFuncN selector)
{
	/************************************************************************/
	/* 	const char *fileName 声明一个指向字符常量的指针（表示值不可以变）指向常量的指针 fileName is a point, pointer char const
	    char const *fileName 同上
	    char* const fileName 声明一个指向可变字符的指针常量（表示指针地址不可以变 地址可以变）常量指针 fileName is a point, pointer char const point
        const char* const fileName=&d   char const* const fileName=&d  指针和值都不可以变了
   */
	/************************************************************************/
	CCTouchSprite* pMySprite = new CCTouchSprite();
	if (pMySprite && pMySprite->initWithFile(fileName))
	{
		pMySprite->setRowIndex(row);
		pMySprite->setCellIndex(cell);
		pMySprite->c_pfnSelector = selector;
		pMySprite->m_pListener = rec;
		pMySprite->autorelease();
		return pMySprite;
	}
	CC_SAFE_DELETE(pMySprite);
	return NULL;
}

CCTouchSprite* CCTouchSprite::createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame,int row, int cell, CCObject* rec, SEL_CallFuncN selector)
{
	CCTouchSprite* pMySprite = new CCTouchSprite();
	if (pMySprite && pMySprite->initWithSpriteFrame(pSpriteFrame))
	{
		pMySprite->setRowIndex(row);
		pMySprite->setCellIndex(cell);
		pMySprite->c_pfnSelector = selector;
		pMySprite->m_pListener = rec;
		pMySprite->autorelease();
		return pMySprite;
	}
	CC_SAFE_DELETE(pMySprite);
	return NULL;
}

//获取系统毫秒数（双击一般时间间隔是250ms～300ms）
static inline long millisecondNow()
{
	struct cc_timeval now;
	cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}


static inline bool isDoubleTouch()
{
	static long lastTouchTime = 0;
	long newTouchTime = millisecondNow();
	if (abs(newTouchTime-lastTouchTime) < 250)
	{
		lastTouchTime = 0;
		return true;
	}
	else
	{
		lastTouchTime = millisecondNow();
		return false;
	}
}

//void CCTouchSprite::myInit(){}

bool CCTouchSprite::ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
	m_bMovedSprite = false;
	if (this->isClickSprite(pTouch))
	{
		if (isDoubleTouch())
		{
			m_bDoubleClick = true;
			return true;
		}
		m_bDoubleClick = false;

		return true;
	}
	return false;
}

void CCTouchSprite::ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
	CCPoint deltaPoint=pTouch->getDelta();

	if(fabs(deltaPoint.x)>1||fabs(deltaPoint.y)>1)
	{
		m_bMovedSprite = true;
	}
}

void CCTouchSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) 
{
	if (!m_bMovedSprite)
	{
		m_bMovedSprite = false;
		if (m_pListener && c_pfnSelector)
		{
			(m_pListener->*c_pfnSelector)(this);
		}
	}
}

void CCTouchSprite::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

void CCTouchSprite::onEnter()
{
	CCSprite::onEnter();

	if (c_pfnSelector)
	{
		//设置事件优先级高于tableview
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	}
}

void CCTouchSprite::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

	CCSprite::onExit();
}

bool CCTouchSprite::isClickSprite(cocos2d::CCTouch* pTouch)
{
	//返回当前触摸点的opengl坐标
	CCPoint touchPoint = pTouch->getLocation();

	//将世界坐标转换为当前view本地坐标
	//CCPoint reallyPoint = this->getParent()->convertToNodeSpace(touchPoint);

	CCPoint reallyPoint = this->getParent()->convertTouchToNodeSpace(pTouch);
	//获取当前基于父类的坐标系
	CCRect rect = this->boundingBox();
	//CCLog("x = %f,y=%f",touchPoint.x,touchPoint.y);
	//CCnode->convertToNodeSpace 或者  convertToWorldSpace 是基于当前Node的  与当前Node相关
	if (rect.containsPoint(reallyPoint))
	{
		return true;
	}
	return false;
}

CCTouchSprite::CCTouchSprite()
{
	setRowIndex(-1);
	setCellIndex(-1);
	m_bMovedSprite = false;
	c_pfnSelector = NULL;
	m_pListener = NULL;
	m_bDoubleClick = false;
}
CCTouchSprite::~CCTouchSprite()
{
	m_pListener = NULL;
	c_pfnSelector = NULL;
}