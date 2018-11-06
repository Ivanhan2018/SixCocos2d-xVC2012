#include "SIX_ExpandLayer.h"

SIX_ExpandLayer::~SIX_ExpandLayer()
{
	CC_SAFE_RELEASE(pBtnExpandSpriteOn);
	CC_SAFE_RELEASE(pBtnExpandSpriteOff);
}

SIX_ExpandLayer *SIX_ExpandLayer::Create(float x,float y,const ccColor4B& color, float width, float height,int expand_offset,bool WhenTouch,bool IsFollowForward,bool IsHor,bool bRedrawBorder,bool bScissor)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_ExpandLayer *pExpandLayer = new SIX_ExpandLayer();
	if (pExpandLayer && pExpandLayer->init() && expand_offset!=0)
	{
		pExpandLayer->initWithColor(color,width,height);
		pExpandLayer->setPosition(x,y);
		pExpandLayer->setRedrawBorder(bRedrawBorder);
		pExpandLayer->m_bFollowForward = IsFollowForward;
		pExpandLayer->m_iStatusExpand = STATUS_EXPAND_MIN;
		pExpandLayer->m_bHor = IsHor;
		pExpandLayer->m_iOffset = expand_offset;
		pExpandLayer->m_bWhenTouch = WhenTouch;
//#ifdef WIN32
//		pExpandLayer->m_bWhenTouch = false;
//#else
//		pExpandLayer->m_bWhenTouch = true;
//#endif
		pExpandLayer->m_bScissor = bScissor;
		pExpandLayer->setObjName("SIX_ExpandLayer");
	}
	return pExpandLayer;
}

bool SIX_ExpandLayer::init()
{
	if (!SIX_UILayer::init())
		return false;
	pAnimate = 0;
	pBtnExpand = 0;
	pBtnExpandSpriteOn = 0;
	pBtnExpandSpriteOff = 0;
	return true;
}

void SIX_ExpandLayer::onEnterTransitionDidFinish()
{
}

void SIX_ExpandLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,m_nPriority);
}

bool SIX_ExpandLayer::AnimateInit(float width,float height)
{
	if (!pBtnExpand)
		return false;
	pAnimate = SIX_Scissor::create();
	if (pAnimate)
	{
		pAnimate->setDefaultTouchPriority(m_nPriority-1);
		pAnimate->setContentSize(CCSize(width,height));
		pAnimate->ignoreAnchorPointForPosition(true);
		pAnimate->setScissorEnabled(m_bScissor);

		// 微调偏移
		float offset = 0.0f;

		// 横向以pBtnExpand的x轴为基准
		if (m_bHor)
		{
			float y = pBtnExpand->getPositionY()-pAnimate->getContentSize().height/2+pBtnExpand->getPreferredSize().height/2;
			// 左->右
			if (m_iOffset>0)
			{
				offset = m_bFollowForward?pBtnExpand->getPositionX()-pAnimate->getContentSize().width:pBtnExpand->getPositionX()+pBtnExpand->getPreferredSize().width-pAnimate->getContentSize().width;
				// 设置内部裁剪区域
				pAnimate->setScissorOffsetX(pBtnExpand->getPositionX()+pBtnExpand->getContentSize().width);
				pAnimate->setScissorOffsetY(y);
			}
			// 右->左
			else if (m_iOffset<0)
			{
				offset = m_bFollowForward?pBtnExpand->getPositionX()+pBtnExpand->getPreferredSize().width:pBtnExpand->getPositionX();
				// 设置内部裁剪区域
				pAnimate->setScissorOffsetX(pBtnExpand->getPositionX()-pBtnExpand->getContentSize().width);
				pAnimate->setScissorOffsetY(y);
			}
			pAnimate->setPosition(offset,y);
		}
		// 纵向以pBtnExpand的y轴为基准
		else
		{
			float x = pBtnExpand->getPositionX()-pAnimate->getContentSize().width/2+pBtnExpand->getPreferredSize().width/2;
			// 下->上
			if (m_iOffset>0)
			{
				offset = m_bFollowForward?pBtnExpand->getPositionY()-pAnimate->getContentSize().height:pBtnExpand->getPositionY()+pBtnExpand->getPreferredSize().height-pAnimate->getContentSize().height;
				// 设置内部裁剪区域
				pAnimate->setScissorOffsetX(x);
				pAnimate->setScissorOffsetY(pBtnExpand->getPositionY()+pBtnExpand->getContentSize().height);
			}
			// 上->下
			else if (m_iOffset<0)
			{
				offset = m_bFollowForward?pBtnExpand->getPositionY()+pBtnExpand->getContentSize().height:pBtnExpand->getPositionY();
				// 设置内部裁剪区域
				pAnimate->setScissorOffsetX(x);
				pAnimate->setScissorOffsetY(pBtnExpand->getPositionY()-pAnimate->getContentSize().height);
			}
			pAnimate->setPosition(x,offset);
		}
		this->addChild(pAnimate);
	}
	return true;
}

void SIX_ExpandLayer::resetZOrder()
{
	if (!pAnimate || !pBtnExpand)
		return;
	int zOrder = pAnimate->getZOrder();
	pBtnExpand->_setZOrder(zOrder);
	this->reorderChild(pBtnExpand,zOrder);
}

void SIX_ExpandLayer::buttonExpandWithSpriteFrameName(const char *pszSpriteFrameName)
{
	pBtnExpand = CreateButtonWithFrameName(pszSpriteFrameName);
	if (pBtnExpand)
		pBtnExpand->setTag(BTN_EXPAND);
}

void SIX_ExpandLayer::buttonExpandWithFile(const char *file,CCRect rc,const char *text,const char *fontName,int fontSize)
{
	pBtnExpand = CreateButtonWithFile(file,rc,text,fontName,fontSize);
	if (pBtnExpand)
		pBtnExpand->setTag(BTN_EXPAND);
}

void SIX_ExpandLayer::buttonExpandWithFileCell(const char *file,int cell,bool Hor)
{
	pBtnExpand = CreateButtonWithFileCell(file,cell,Hor);
	if (pBtnExpand)
		pBtnExpand->setTag(BTN_EXPAND);
}

CCControlButton *SIX_ExpandLayer::CreateButtonWithFrameName(const char *pszSpriteFrameName)
{
	CCControlButton *pBtn = SIX_Utility::GetInstance()->CreateButtonWithFrameName(pszSpriteFrameName);
	if (!pBtn)
		return 0;
	pBtn->setDefaultTouchPriority(m_nPriority-1);
	if (m_bWhenTouch)
		pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_ExpandLayer::doEvents),32);
	this->addChild(pBtn);
	return pBtn;
}

CCControlButton *SIX_ExpandLayer::CreateButtonWithFile(const char *file,CCRect rc,const char *text,const char *fontName,int fontSize)
{
	CCControlButton *pBtn = SIX_Utility::GetInstance()->CreateButtonWithFile(file,rc,text,fontName,fontSize);
	if (!pBtn)
		return 0;
	pBtn->setDefaultTouchPriority(m_nPriority-1);
	if (m_bWhenTouch)
		pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_ExpandLayer::doEvents),32);
	this->addChild(pBtn);
	return pBtn;
}

CCControlButton *SIX_ExpandLayer::CreateButtonWithFileCell(const char *file,int cell,bool Hor)
{
	CCControlButton *pBtn = SIX_Utility::GetInstance()->CreateButtonWithFileCell(file,cell,Hor);
	if (!pBtn)
		return 0;
	pBtn->setDefaultTouchPriority(m_nPriority-1);
	if (m_bWhenTouch)
		pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_ExpandLayer::doEvents),32);
	this->addChild(pBtn);
	return pBtn;
}

// 移动设备上用触碰方式
void SIX_ExpandLayer::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControlButton *pButton = (CCControlButton*)pSender;
	int tag = pButton->getTag();
	SIXLog("SIX_ExpandLayer.doEvents.pSender[0x%08X].event[%d].tag[%d].onCCControlEventTouchUpInside",pSender,event,tag);

	if (!pBtnExpand || !pAnimate || !m_bWhenTouch)
		return;

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
			case BTN_EXPAND:
				{
					if (this->OnExpand())
					{
						if (this->m_iStatusExpand==STATUS_EXPAND_MIN)
							this->doExpandAnimation(true);
						else if (this->m_iStatusExpand==STATUS_EXPAND_MAX)
							this->doExpandAnimation(false);
					}
					break;
				}
			}
			break;
		}
	}
}

// PC上用这种方式
void SIX_ExpandLayer::ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType)
{
	if (nType==CCNCMOUSEMOVE)
		return;
	OnTouchLogic(pTouches,nType);
}

void SIX_ExpandLayer::OnTouchLogic(CCSet *pTouches,int pEvent)
{
	if (!pBtnExpand || !pAnimate || m_bWhenTouch)
		return;

	CCSetIterator it;
	for( it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *pTouch = (CCTouch *)(*it);
		// 相对GL坐标系
		CCPoint pos = pTouch->getLocation();
		//// 相对屏幕坐标系
		//CCPoint posInView = pTouch->getLocationInView();
		//// 转换后：location==pos
		//CCPoint location = CCDirector::sharedDirector()->convertToGL(posInView);

		bool insideExpand = pBtnExpand->isTouchInside(pTouch);
		bool insideAnimate = pAnimate->isTouchInside(pTouch);
		if (!insideExpand && !insideAnimate)
		{
			if (this->m_iStatusExpand==STATUS_EXPAND_MAX)
				doExpandAnimation(false);
		}
		else if (insideExpand)
		{
			if (this->m_iStatusExpand==STATUS_EXPAND_MIN)
				doExpandAnimation(true);
		}
	}
}

void SIX_ExpandLayer::doExpandAnimation(bool IsExpand)
{
	if (!pBtnExpand || !pAnimate)
		return;

	CCMoveTo *pMove = 0;
	CCCallFuncN *pCall = 0;
	CCAction *pAction = 0;

	float offset = 0.0f;

	// 已收拢
	if (m_iStatusExpand==STATUS_EXPAND_MIN && IsExpand)
	{
		//pBtnExpand->setTouchEnabled(false);
		m_iStatusExpand = STATUS_EXPAND_INC;
		// 横向
		if (m_bHor)
		{
			// 跟随
			if (m_bFollowForward)
			{
				offset = this->getPositionX() + m_iOffset;
				pMove = CCMoveTo::create(EXPAND_DELAY,CCPoint(offset,this->getPositionY()));
			}
			else
			{
				offset = pAnimate->getPositionX() + m_iOffset;
				pMove = CCMoveTo::create(EXPAND_DELAY,CCPoint(offset,pAnimate->getPositionY()));
			}
		}
		// 纵向
		else
		{
			// 跟随
			if (m_bFollowForward)
			{
				offset = this->getPositionY() + m_iOffset;
				pMove = CCMoveTo::create(EXPAND_DELAY,CCPoint(this->getPositionX(),offset));
			}
			else
			{
				offset = pAnimate->getPositionY() + m_iOffset;
				pMove = CCMoveTo::create(EXPAND_DELAY,CCPoint(pAnimate->getPositionX(),offset));
			}
		}
		pCall = CCCallFuncN::create(this,callfuncN_selector(SIX_ExpandLayer::ExpandOn));
		pAction = CCSequence::create(pMove,pCall,0);
		if (m_bFollowForward)
			this->runAction(pAction);
		else
			pAnimate->runAction(pAction);
	}
	// 已展开
	else if (m_iStatusExpand==STATUS_EXPAND_MAX && !IsExpand)
	{
		//pBtnExpand->setTouchEnabled(false);
		m_iStatusExpand = STATUS_EXPAND_DEC;
		// 横向
		if (m_bHor)
		{
			// 跟随
			if (m_bFollowForward)
			{
				offset = this->getPositionX() - m_iOffset;
				pMove = CCMoveTo::create(EXPAND_DELAY,CCPoint(offset,this->getPositionY()));
			}
			else
			{
				offset = pAnimate->getPositionX() - m_iOffset;
				pMove = CCMoveTo::create(EXPAND_DELAY,CCPoint(offset,pAnimate->getPositionY()));
			}
		}
		// 纵向
		else
		{
			// 跟随
			if (m_bFollowForward)
			{
				offset = this->getPositionY() - m_iOffset;
				pMove = CCMoveTo::create(EXPAND_DELAY,CCPoint(this->getPositionX(),offset));
			}
			else
			{
				offset = pAnimate->getPositionY() - m_iOffset;
				pMove = CCMoveTo::create(EXPAND_DELAY,CCPoint(pAnimate->getPositionX(),offset));
			}
		}
		pCall = CCCallFuncN::create(this,callfuncN_selector(SIX_ExpandLayer::ExpandOff));
		pAction = CCSequence::create(pMove,pCall,0);
		if (m_bFollowForward)
			this->runAction(pAction);
		else
			pAnimate->runAction(pAction);
	}
}

void SIX_ExpandLayer::ExpandOn(CCNode *pNode)
{
	if (!pNode)
		return;
	SIX_ExpandLayer *pExpandLayer = dynamic_cast<SIX_ExpandLayer*>(pNode);
	if (!pExpandLayer)
	{
		CCControl *pAnimate = dynamic_cast<CCControl*>(pNode);
		if (!pAnimate)
			return;
		pExpandLayer = dynamic_cast<SIX_ExpandLayer*>(pAnimate->getParent());
		if (!pExpandLayer)
			return;
	}
	pExpandLayer->m_iStatusExpand = STATUS_EXPAND_MAX;
	//pExpandLayer->pBtnExpand->setTouchEnabled(true);
	pExpandLayer->pBtnExpand->setBackgroundSpriteForState(pExpandLayer->pBtnExpandSpriteOff,CCControlStateNormal);
}

void SIX_ExpandLayer::ExpandOff(CCNode *pNode)
{
	if (!pNode)
		return;
	SIX_ExpandLayer *pExpandLayer = dynamic_cast<SIX_ExpandLayer*>(pNode);
	if (!pExpandLayer)
	{
		CCControl *pAnimate = dynamic_cast<CCControl*>(pNode);
		if (!pAnimate)
			return;
		pExpandLayer = dynamic_cast<SIX_ExpandLayer*>(pAnimate->getParent());
		if (!pExpandLayer)
			return;
	}
	pExpandLayer->m_iStatusExpand = STATUS_EXPAND_MIN;
	//pExpandLayer->pBtnExpand->setTouchEnabled(true);
	pExpandLayer->pBtnExpand->setBackgroundSpriteForState(pExpandLayer->pBtnExpandSpriteOn,CCControlStateNormal);
}

void SIX_ExpandLayer::setExpandButtonSprite(CCScale9Sprite *btnOn,CCScale9Sprite *btnOff,CCSize size)
{
	if (btnOn)
	{
		pBtnExpandSpriteOn = btnOn;
		pBtnExpandSpriteOn->retain();
	}
	if (btnOff)
	{
		pBtnExpandSpriteOff = btnOff;
		pBtnExpandSpriteOff->retain();
	}

	if (!pBtnExpandSpriteOn)
		return;

	pBtnExpand = CCControlButton::create(pBtnExpandSpriteOn);
	if (!pBtnExpand)
		return;

	pBtnExpand->ignoreAnchorPointForPosition(true);
	pBtnExpand->setZoomFactor(1.05f);
	pBtnExpand->setPreferredSize(size);

	pBtnExpand->setDefaultTouchPriority(m_nPriority-1);
	if (m_bWhenTouch)
		pBtnExpand->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_ExpandLayer::doEvents),32);
	this->addChild(pBtnExpand);
}