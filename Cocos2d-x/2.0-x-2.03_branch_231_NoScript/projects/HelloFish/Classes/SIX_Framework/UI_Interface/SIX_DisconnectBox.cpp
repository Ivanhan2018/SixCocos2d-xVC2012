#include "SIX_DisconnectBox.h"

SIX_DisconnectBox::~SIX_DisconnectBox()
{
}

SIX_DisconnectBox *SIX_DisconnectBox::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	if (0.0001 > x && 0.0001 > y)
	{
		CCSize szWind = CCDirector::sharedDirector()->getWinSize();
		x = (szWind.width - width) / 2;
		y = (szWind.height - height) / 2;
	}

	SIX_DisconnectBox *pDisconnectBox = new SIX_DisconnectBox();
	if (pDisconnectBox && pDisconnectBox->init())
	{
		pDisconnectBox->initWithColor(color,width,height);
		pDisconnectBox->setPosition(x,y);
		pDisconnectBox->setRedrawBorder(bRedrawBorder);
		pDisconnectBox->setTouchEnabled(true);
		pDisconnectBox->m_ForbiddenTouch = true;
		pDisconnectBox->m_bCloseThenCleanup = bCloseThenCleanup;
	}
	return pDisconnectBox;
}

bool SIX_DisconnectBox::init()
{
	if (!SIX_PopWnd::init())
		return false;
	pText = 0;
	pfnCallBack = 0;
	return true;
}

void SIX_DisconnectBox::onEnterTransitionDidFinish()
{
	SIX_PopWnd::onEnterTransitionDidFinish();
}

void SIX_DisconnectBox::setTextAttribute(float x,float y,float w,float h,const char *fontName,int fontSize,CCTextAlignment hAlignment)
{
	if (!fontName || !strlen(fontName))
		return;

	if (fontSize<1)
		fontSize = 12;

	if (!pText)
	{
		pText = CCLabelTTF::create(" ",fontName,fontSize,CCSize(w,h),hAlignment);
		pText->setAnchorPoint(ccp(0,0));
		pText->setPosition(ccp(x,y));
		this->addChild(pText);
	}
	else
	{
		pText->setFontName(fontName);
		pText->setFontSize(fontSize);
	}
}

void SIX_DisconnectBox::setString(const char *text)
{
	if (!text || !strlen(text) || !pText)
		return;

	pText->setVisible(true);
	pText->setString(text);
	SIX_Utility::GetInstance()->FixedTexParameters(pText->getTexture());
}

void SIX_DisconnectBox::setLoadingAttribute(float x,float y,float delay,SIX_UIScene *pScene,SEL_CallFunc pfn)
{
	pfnScene = pScene;
	pfnCallBack = pfn;

	CCSprite *pLoading = CCSprite::createWithSpriteFrameName("loading00.png");
	pLoading->setPosition(ccp(x,y));
	pLoading->ignoreAnchorPointForPosition(true);
	pLoading->setTag(1);
	this->addChild(pLoading);

	CCArray *pArray = CCArray::create();
	for (int i=0;i<21;i++)
	{
		CCString *pName = CCString::createWithFormat("loading%02d.png",i);
		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pName->getCString());
		if (!pFrame)
			break;
		pArray->addObject(pFrame);
	}

	CCAnimation *pAnimation =CCAnimation::createWithSpriteFrames(pArray,0.1f);
	CCRepeatForever *pAct = CCRepeatForever::create(CCAnimate::create(pAnimation));
	pLoading->runAction(pAct);
	CCDelayTime *pDelay = CCDelayTime::create(delay);

	CCCallFuncN *pCallfun = CCCallFuncN::create(this,callfuncN_selector(SIX_DisconnectBox::Hide));
	CCFiniteTimeAction *pSequence = CCSequence::create(pDelay,pCallfun,0);
	pLoading->runAction(pSequence);
}

void SIX_DisconnectBox::Hide(CCNode *node)
{
	CCSprite *pSpr = dynamic_cast<CCSprite*>(node);
	if (!pSpr)
		return;

	pSpr->removeAllChildrenWithCleanup(true);
	pSpr->removeFromParentAndCleanup(true);

	pText->setVisible(false);

	this->Show(false);

	(this->pfnScene->*this->pfnCallBack)();
}

void SIX_DisconnectBox::UnExec()
{
	CCSprite *pSpr = dynamic_cast<CCSprite*>(this->getChildByTag(1));
	if (!pSpr)
		return;

	this->m_ActDone = true;

	this->stopAllActions();
	this->unscheduleAllSelectors();

	pSpr->removeAllChildrenWithCleanup(true);
	pSpr->removeFromParentAndCleanup(true);
}

bool SIX_DisconnectBox::OnSubmit()
{
	SIXLog("OnSubmit");

	if (pfnScene)
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFY_CLOSEWND_CLICKED);
	}

	return true;
}