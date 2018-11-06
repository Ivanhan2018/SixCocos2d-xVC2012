#include "SIX_PopWndFirstBuy.h"

enum NodeTag
{
	BUY_BT_ID ,					// 购买按钮
};

SIX_PopWndFirstBuy *SIX_PopWndFirstBuy::Create(float x,float y,const ccColor4B& color, float width, float height)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;
	const CCSize wndSize = CCDirector::sharedDirector()->getWinSize();
	if (0.00001 >= width)
		width = wndSize.width;
	if (0.00001 >= height)
		height = wndSize.height;

	SIX_PopWndFirstBuy *pPopWnd = new SIX_PopWndFirstBuy();
	if (pPopWnd && pPopWnd->init())
	{
		pPopWnd->initWithColor(color,width,height);
		pPopWnd->setPosition(x,y);
		pPopWnd->setShakeOffset(50);
		pPopWnd->m_ForbiddenTouch = true;
		pPopWnd->m_bCloseThenCleanup = true;
		pPopWnd->buttonCloseWithFileCell("btn_close.png", 2);
		pPopWnd->backgroundWithFile("box_bg.png");
		pPopWnd->GetBtnClose()->setPosition(ccp(width-pPopWnd->GetBtnClose()->getContentSize().width/2-15, height-pPopWnd->GetBtnClose()->getContentSize().height/2-15));
	}
	return pPopWnd;
}

SIX_PopWndFirstBuy::~SIX_PopWndFirstBuy(void)
{
}

bool SIX_PopWndFirstBuy::init()
{
	if (!SIX_EffectPopWnd::init())
		return false;

	setAllowDragged(false);
	setShowType(MOVABLE_TOP);
	setHideType(MOVABLE_TOP);
	return true;
}

void SIX_PopWndFirstBuy::onEnterTransitionDidFinish()
{
	CCLabelTTF *pTitle = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U("首购大礼包").c_str(),"微软雅黑",22, \
		CCSize(200,60),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	if (pTitle)
	{
		pTitle->setColor(ccc3(229,181,96));
		pTitle->setOpacity(255);
		pTitle->ignoreAnchorPointForPosition(true);
		pTitle->setPosition(ccp((getContentSize().width-pTitle->getContentSize().width)/2, getContentSize().height-pTitle->getContentSize().height-5));
		SIX_Utility::GetInstance()->FixedTexParameters(pTitle->getTexture(),true);
		addChild(pTitle);
	}

	CCSprite *pSign = CCSprite::create("firstBuy_sign.png");
	if (pSign  &&  pTitle)
	{
		pSign->ignoreAnchorPointForPosition(true);
		pSign->setPosition(ccp(pTitle->getPositionX()-pSign->getContentSize().width+35, pTitle->getPositionY()));
		addChild(pSign);
	}

	CCLabelTTF *pDescription = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U("首次购买任何额度筹码，额外赠送").c_str(),"微软雅黑",16, \
		CCSize(300,60),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	if (pDescription && pSign)
	{
		pDescription->setColor(ccc3(255,255,255));
		pDescription->setOpacity(255);
		pDescription->ignoreAnchorPointForPosition(true);
		pDescription->setPosition(ccp((getContentSize().width-pDescription->getContentSize().width)/2, pSign->getPositionY()-pDescription->getContentSize().height+20));
		SIX_Utility::GetInstance()->FixedTexParameters(pDescription->getTexture(),true);
		addChild(pDescription);
	}

	CCSprite *pChipSign = CCSprite::create("firstBuy_Chip.png");
	if (pChipSign  &&  pDescription)
	{
		pChipSign->ignoreAnchorPointForPosition(true);
		pChipSign->setPosition(ccp((getContentSize().width-pChipSign->getContentSize().width)/2, pDescription->getPositionY()-pChipSign->getContentSize().height));
		addChild(pChipSign);
	}

	CCLabelTTF *pChipNum = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U("100,000筹码").c_str(),"微软雅黑",30, \
		CCSize(300,60),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	if (pChipNum && pChipSign)
	{
		pChipNum->setColor(ccc3(255,255,255));
		pChipNum->setOpacity(255);
		pChipNum->ignoreAnchorPointForPosition(true);
		pChipNum->setPosition(ccp((getContentSize().width-pChipNum->getContentSize().width)/2, pChipSign->getPositionY()-pChipNum->getContentSize().height));
		SIX_Utility::GetInstance()->FixedTexParameters(pChipNum->getTexture(),true);
		addChild(pChipNum);
	}

	CCControlButton *pBuyBT = SIX_Utility::GetInstance()->CreateButtonWithFileCell("firstBuy_BT.png", 2);
	if (pBuyBT  &&  pChipNum)
	{
		pBuyBT->setTag(BUY_BT_ID);
		pBuyBT->setZoomOnTouchDown(false);
		pBuyBT->setDefaultTouchPriority(m_nPriority-1);
		pBuyBT->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndFirstBuy::doEvents),32);
		pBuyBT->setPosition(ccp((getContentSize().width-pBuyBT->getContentSize().width)/2, pChipNum->getPositionY()-pBuyBT->getContentSize().height));
		addChild(pBuyBT);
	}
}

void SIX_PopWndFirstBuy::doEvents(CCObject* pSender, CCControlEvent controlEvent)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	switch (controlEvent)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
			default:
				SIXLog("SIX_PopWndFirstBuy::doEvents 未知按钮事件,  tag=%d", tag);
				break;
			}
		}
	}
	return;
}