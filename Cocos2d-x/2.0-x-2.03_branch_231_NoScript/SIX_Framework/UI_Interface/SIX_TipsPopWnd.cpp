#include "SIX_TipsPopWnd.h"

SIX_TipsPopWnd::~SIX_TipsPopWnd()
{
}

SIX_TipsPopWnd *SIX_TipsPopWnd::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
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

	SIX_TipsPopWnd *pPopWnd = new SIX_TipsPopWnd();
	if (pPopWnd && pPopWnd->init())
	{
		pPopWnd->initWithColor(color,width,height);
		pPopWnd->setPosition(x,y);
		pPopWnd->setRedrawBorder(bRedrawBorder);
		pPopWnd->setTouchEnabled(true);
		pPopWnd->m_ForbiddenTouch = true;
		pPopWnd->m_bCloseThenCleanup = bCloseThenCleanup;
		pPopWnd->setObjName("SIX_TipsPopWnd");
		//pPopWnd->setRectDirty();
	}
	return pPopWnd;
}

bool SIX_TipsPopWnd::init()
{
	if (!SIX_EffectPopWnd::init())
		return false;
	m_pText = 0;
	setHideWhenTouched();
	return true;
}

bool SIX_TipsPopWnd::ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent)
{
	// 相对GL坐标系
	CCPoint pos = pTouch->getLocation();
	if (getHideWhenTouched())
	{
		this->Show(false);
		return true;
	}
	return SIX_EffectPopWnd::ccTouchBegan(pTouch,pEvent);
}

// 设置文字提示
void SIX_TipsPopWnd::setTips(const char *text,const char *fontName,int fontSize)
{
	if (!m_pText)
	{
		m_pText = CCLabelTTF::create("",fontName,(float)fontSize);
		m_pText->setColor(ccc3(255,255,255));
		m_pText->setHorizontalAlignment(kCCTextAlignmentCenter);
		this->addChild(m_pText);
	}

	m_pText->setString(SIX_Utility::GetInstance()->G2U(text).c_str());
	CCSize size = m_pText->getDimensions();
	CCPoint offset = CCPointZero;
	offset.x = (this->getContentSize().width - size.width)/2;
	offset.y = (this->getContentSize().height - size.height)/2;
	m_pText->setPosition(offset);

	SIX_Utility::GetInstance()->FixedTexParameters(m_pText->getTexture(),true);
}