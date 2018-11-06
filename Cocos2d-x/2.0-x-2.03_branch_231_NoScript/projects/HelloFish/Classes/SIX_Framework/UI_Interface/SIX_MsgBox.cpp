#include "SIX_MsgBox.h"

SIX_MsgBox::~SIX_MsgBox()
{
}

SIX_MsgBox *SIX_MsgBox::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
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

	SIX_MsgBox *pMsgBox = new SIX_MsgBox();
	if (pMsgBox && pMsgBox->init())
	{
		pMsgBox->initWithColor(color,width,height);
		pMsgBox->setPosition(x,y);
		pMsgBox->setRedrawBorder(bRedrawBorder);
		pMsgBox->setTouchEnabled(true);
		pMsgBox->m_ForbiddenTouch = true;
		pMsgBox->m_bCloseThenCleanup = bCloseThenCleanup;
	}
	return pMsgBox;
}

bool SIX_MsgBox::init()
{
	if (!SIX_PopWnd::init())
		return false;
	pText = 0;
	return true;
}

void SIX_MsgBox::onEnterTransitionDidFinish()
{
	SIX_PopWnd::onEnterTransitionDidFinish();
}

void SIX_MsgBox::setTextAttribute(float x,float y,float w,float h,const char *fontName,int fontSize,CCTextAlignment hAlignment)
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

void SIX_MsgBox::setString(const char *text)
{
	if (!text || !strlen(text) || !pText)
		return;

	pText->setString(text);
	SIX_Utility::GetInstance()->FixedTexParameters(pText->getTexture());
}