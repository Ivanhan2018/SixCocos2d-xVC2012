#include "CCTouchSprite.h"
USING_NS_CC;

CCTouchSprite* CCTouchSprite::createWithPic(const char *fileName, int row, int cell)
{
	return CCTouchSprite::createWithPic(fileName, row, cell, NULL, NULL);
}

CCTouchSprite* CCTouchSprite::createWithPic(const char *fileName, int row, int cell, CCObject* rec, SEL_CallFuncN selector)
{
	/************************************************************************/
	/* 	const char *fileName ����һ��ָ���ַ�������ָ�루��ʾֵ�����Ա䣩ָ������ָ�� fileName is a point, pointer char const
	    char const *fileName ͬ��
	    char* const fileName ����һ��ָ��ɱ��ַ���ָ�볣������ʾָ���ַ�����Ա� ��ַ���Ա䣩����ָ�� fileName is a point, pointer char const point
        const char* const fileName=&d   char const* const fileName=&d  ָ���ֵ�������Ա���
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

//��ȡϵͳ��������˫��һ��ʱ������250ms��300ms��
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
		//�����¼����ȼ�����tableview
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
	//���ص�ǰ�������opengl����
	CCPoint touchPoint = pTouch->getLocation();

	//����������ת��Ϊ��ǰview��������
	//CCPoint reallyPoint = this->getParent()->convertToNodeSpace(touchPoint);

	CCPoint reallyPoint = this->getParent()->convertTouchToNodeSpace(pTouch);
	//��ȡ��ǰ���ڸ��������ϵ
	CCRect rect = this->boundingBox();
	//CCLog("x = %f,y=%f",touchPoint.x,touchPoint.y);
	//CCnode->convertToNodeSpace ����  convertToWorldSpace �ǻ��ڵ�ǰNode��  �뵱ǰNode���
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