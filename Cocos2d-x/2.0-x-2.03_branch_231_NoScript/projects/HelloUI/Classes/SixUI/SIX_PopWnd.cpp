#include "SIX_PopWnd.h"
int SIX_PopWnd::m_WndCount = 0;
int SIX_PopWnd::GLOBAL_PRIORITY	= -1023;
int SIX_PopWnd::GLOBAL_ZORDER = 1023;

SIX_PopWnd::~SIX_PopWnd()
{
	if (!m_bCloseThenCleanup)
	{
		removeAllChildrenWithCleanup( true );
		removeFromParentAndCleanup( true );
	}
}

SIX_PopWnd *SIX_PopWnd::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
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

	SIX_PopWnd *pPopWnd = new SIX_PopWnd();
	if (pPopWnd && pPopWnd->init())
	{
		pPopWnd->initWithColor(color,width,height);
		pPopWnd->setPosition(x,y);
		pPopWnd->setRedrawBorder(bRedrawBorder);
		//pPopWnd->setTouchEnabled(true);
		//pPopWnd->m_ForbiddenTouch = true;
		pPopWnd->m_bCloseThenCleanup = bCloseThenCleanup;
	}
	return pPopWnd;
}

int SIX_PopWnd::GetPopWndCount()
{
	return m_WndCount;
}

void SIX_PopWnd::setPopWndCount(int nCount)
{
	m_WndCount = nCount;
}

bool SIX_PopWnd::init()
{
	if (!SIX_UILayer::init())
		return false;
	//this->m_nPriority = GLOBAL_PRIORITY;
	//GLOBAL_PRIORITY += PRIORITY_STEP;
	m_LastPriority = 0;
	pBackground = 0;
	pSubmit = 0;
	pCancel = 0;
	pClose = 0;
	pBlock = 0;
	m_IsDragged = m_IsShow = false;
	m_bAllowDragged = true;
	m_ActDone = true;
	m_LastHitPos.x = m_LastHitPos.y = 0;
	//this->m_nPriority = GLOBAL_PRIORITY;
	GLOBAL_PRIORITY += PRIORITY_STEP;
	return true;
}

void SIX_PopWnd::onEnterTransitionDidFinish()
{
}

// 需要重新分配子控件优先级
void SIX_PopWnd::Redistribution(CCLayer *pControl,bool IsHide)
{
	if (!pControl)
		return;
	//if (IsHide)
	//{
		//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(pControl);
		//pControl->registerWithTouchDispatcher();
		pControl->setTouchEnabled(!IsHide);
	//}
}

// 只遍历第一层子控件，遍历N层嵌套控件节点效率太低。。。
// Cool.Cat@2013-07-12
void SIX_PopWnd::RedistributionAllChildren(CCNode *pRoot,bool IsHide)
{
	CCObject *pChild = 0;
	CCARRAY_FOREACH(pRoot->getChildren(),pChild)
	{
		CCControl *pControl = dynamic_cast<CCControl*>(pChild);
		if (pControl)
		{
			//pControl->setDefaultTouchPriority(this->m_nPriority-1);
			Redistribution(pControl,IsHide);
		}
		else
		{
			CCLayer *pLayer = dynamic_cast<CCLayer*>(pChild);
			if (pLayer)
			{
				Redistribution(pLayer,IsHide);
			}
		}
		CCNode *pNode = dynamic_cast<CCNode*>(pChild);
		if (pNode)
			RedistributionAllChildren(pNode,IsHide);
	}
}

void SIX_PopWnd::onShow()
{
	//m_LastPriority = this->m_nPriority;
	//this->m_nPriority = GLOBAL_PRIORITY;
	//this->setPriority(this->m_nPriority);
	//GLOBAL_PRIORITY += PRIORITY_STEP;

	RedistributionAllChildren(this,false);

	if (SIX_Cursor::GetInstance()->getInited())
	{
		SIX_Cursor::GetInstance()->setIngore(true);
		SIX_Cursor::GetInstance()->setShowOurCursor(false);
		SIX_Cursor::GetInstance()->setShowSysCursor(TRUE);
	}

	//SIXLog("onShow[%s].m_nPriority[%d]",this->getObjName(),this->m_nPriority);
}

void SIX_PopWnd::onHide()
{
	//this->m_nPriority = this->m_LastPriority;
	//this->setPriority(this->m_nPriority);

	RedistributionAllChildren(this,true);

	if (SIX_Cursor::GetInstance()->getInited() && this->GetPopWndCount()==0)
	{
		SIX_Cursor::GetInstance()->setIngore(false);
		SIX_Cursor::GetInstance()->setShowOurCursor(true);
		SIX_Cursor::GetInstance()->setShowSysCursor(FALSE);
	}

	//SIXLog("onHide[%s].m_nPriority[%d]",this->getObjName(),this->m_nPriority);
}

void SIX_PopWnd::backgroundWithSpriteFrameName(const char *pszSpriteFrameName)
{
	if (!pszSpriteFrameName || pBackground)
		return;
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    if (!pFrame)
		return;
	pBackground = CCScale9Sprite::createWithSpriteFrame(pFrame);
	if (!pBackground)
		return;
	pBackground->setAnchorPoint(ccp(0,0));
	pBackground->setPreferredSize(CCSize(this->getContentSize().width,this->getContentSize().height));
	this->addChild(pBackground);
}

void SIX_PopWnd::backgroundWithFile(const char *file)
{
	if (!file || pBackground)
		return;

	pBackground = CCScale9Sprite::create(file);
	if (!pBackground)
		return;
	//pBackground->setAnchorPoint(ccp(0,0));
	pBackground->ignoreAnchorPointForPosition(true);
	pBackground->setPreferredSize(CCSize(this->getContentSize().width,this->getContentSize().height));
	this->addChild(pBackground);
}

CCControlButton *SIX_PopWnd::CreateButtonWithFrameName(const char *pszSpriteFrameName)
{
	CCControlButton *pBtn = 0;//SIX_Utility::GetInstance()->CreateButtonWithFrameName(pszSpriteFrameName);
	if (!pBtn)
		return 0;
	//pBtn->setDefaultTouchPriority(m_nPriority-1);
	pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
	this->addChild(pBtn);
	return pBtn;
}

void SIX_PopWnd::buttonSubmitWithSpriteFrameName(const char *pszSpriteFrameName)
{
	pSubmit = CreateButtonWithFrameName(pszSpriteFrameName);
	if (pSubmit)
		pSubmit->setTag(BTN_SUBMIT);
}

void SIX_PopWnd::buttonCancelWithSpriteFrameName(const char *pszSpriteFrameName)
{
	pCancel = CreateButtonWithFrameName(pszSpriteFrameName);
	if (pCancel)
		pCancel->setTag(BTN_CANCEL);
}

void SIX_PopWnd::buttonCloseWithSpriteFrameName(const char *pszSpriteFrameName)
{
	pClose = CreateButtonWithFrameName(pszSpriteFrameName);
	if (pClose)
		pClose->setTag(BTN_CLOSE);
}

CCControlButton *SIX_PopWnd::CreateButtonWithFile(const char *file,CCRect rc,const char *text,const char *fontName,int fontSize)
{
	CCControlButton *pBtn = 0;//SIX_Utility::GetInstance()->CreateButtonWithFile(file,rc,text,fontName,fontSize);
	if (!pBtn)
		return 0;
	//pBtn->setDefaultTouchPriority(m_nPriority-1);
	pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
	this->addChild(pBtn);
	return pBtn;
}

void SIX_PopWnd::buttonSubmitWithFile(const char *file,const char *text,const char *fontName,int fontSize)
{
	pSubmit = CreateButtonWithFile(file,CCRectZero,text,fontName,fontSize);
	if (pSubmit)
		pSubmit->setTag(BTN_SUBMIT);
}

void SIX_PopWnd::buttonCancelWithFile(const char *file,const char *text,const char *fontName,int fontSize)
{
	pCancel = CreateButtonWithFile(file,CCRectZero,text,fontName,fontSize);
	if (pCancel)
		pCancel->setTag(BTN_CANCEL);
}

void SIX_PopWnd::buttonCloseWithFile(const char *file,const char *text,const char *fontName,int fontSize)
{
	pClose = CreateButtonWithFile(file,CCRectZero,text,fontName,fontSize);
	if (pClose)
		pClose->setTag(BTN_CLOSE);
}

void SIX_PopWnd::AutoCaclBtnPosWidthYesOrNo(float offsetX,float offsetY)
{
	// 支持无缝连接
	if (offsetX<=0.0f)
		offsetX = 0.0f;
	if (offsetY<=0.0f)
		offsetY = 0.0f;

	if (pSubmit && pCancel)
	{
		float total_width = this->getContentSize().width;
		pSubmit->setPosition(offsetX,offsetY);
		pCancel->setPosition(total_width - offsetX - pSubmit->getContentSize().width,offsetY);
	}
}

bool SIX_PopWnd::IsShow()
{
	return m_IsShow;
}

CCControlButton *SIX_PopWnd::CreateButtonWithFileCell(const char *file,int cell,bool Hor)
{
	CCControlButton *pBtn = 0;//SIX_Utility::GetInstance()->CreateButtonWithFileCell(file,cell,Hor);
	if (!pBtn)
		return 0;
	//pBtn->setDefaultTouchPriority(m_nPriority-1);
	pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
	this->addChild(pBtn);
	return pBtn;
}

// 从文件加载并均分
void SIX_PopWnd::buttonSubmitWithFileCell(const char *file,int cell,bool Hor)
{
	pSubmit = CreateButtonWithFileCell(file,cell,Hor);
	if (pSubmit)
		pSubmit->setTag(BTN_SUBMIT);
}

void SIX_PopWnd::buttonCancelWithFileCell(const char *file,int cell,bool Hor)
{
	pCancel = CreateButtonWithFileCell(file,cell,Hor);
	if (pCancel)
		pCancel->setTag(BTN_CANCEL);
}

void SIX_PopWnd::buttonCloseWithFileCell(const char *file,int cell,bool Hor)
{
	pClose = CreateButtonWithFileCell(file,cell,Hor);
	if (pClose)
		pClose->setTag(BTN_CLOSE);
}

void SIX_PopWnd::InitMask(const ccColor4B& color,int nPriority,bool bRedrawBorder)
{
	//// 默认黑色遮罩
	m_MaskColor = color;
	m_MaskPriority = nPriority;
	m_MaskRedrawBorder = bRedrawBorder;
}

void SIX_PopWnd::CreateMask()
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return;

	pBlock = SIX_UILayer::create(m_MaskColor,true,m_MaskPriority,m_MaskRedrawBorder);
	if (pBlock)
		pScene->addChild(pBlock,99);
}

void SIX_PopWnd::ReleaseMask()
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return;

	if (!pBlock)
		return;

	pScene->removeChild(pBlock,true);
}

void SIX_PopWnd::setContentSize(CCSize size)
{
	SIX_UILayer::setContentSize(size);

	// 需要等比率缩放窗口内部子控件
	// ...
}

void SIX_PopWnd::Show(bool IsShow)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return;

	if (!m_ActDone)
		return;

	m_ActDone = false;

	m_IsShow = IsShow;

	CCScaleTo *ScaleToAction=0;
	CCScaleTo *ScaleToActionReverse=0;
	if (IsShow)
	{
		CreateMask();

		GLOBAL_ZORDER += ZORDER_STEP;

		if (!this->getParent())
			pScene->addChild(this,GLOBAL_ZORDER);
		else
		{
			this->_setZOrder(GLOBAL_ZORDER);
			pScene->reorderChild(this,GLOBAL_ZORDER);
		}

		setSwallowsTouches(true);
		setTouchEventPause(false);
		setScale(0.0f);
		ScaleToAction = CCScaleTo::create(0.2f,1.05f);
		ScaleToActionReverse = CCScaleTo::create(0.1f,1.0f);
		++m_WndCount;
	}
	else
	{
		setSwallowsTouches(false);
		setTouchEventPause(true);
		setScale(1.0f);
		ScaleToAction = CCScaleTo::create(0.1f,1.05f);
		ScaleToActionReverse = CCScaleTo::create(0.2f,0.0f);
		--m_WndCount;
	}

	if (ScaleToAction && ScaleToActionReverse)
	{
		runAction(CCSequence::create(ScaleToAction,ScaleToActionReverse,CCCallFuncN::create(this, callfuncN_selector(SIX_PopWnd::ShowActionCallBack )),0));
	}
}

void SIX_PopWnd::ShowActionCallBack(CCNode *node)
{
	SIX_PopWnd *pPopWnd = (SIX_PopWnd*)(node);
	if (!pPopWnd)
		return;

	if (!pPopWnd->m_IsShow)
	{
		// 移除遮罩
		pPopWnd->ReleaseMask();

		// 在关闭的时候销毁UI子控件
		if (pPopWnd->m_bCloseThenCleanup)
		{
			pPopWnd->removeAllChildrenWithCleanup( true );
			pPopWnd->removeFromParentAndCleanup( true );
		}
		else
		{
			// 否则还原到上一次的优先级
			// Cool.Cat@2013-07-12
			onHide();
		}
	}
	else
	{
		onShow();
	}
	if (!pPopWnd->m_ActDone)
		pPopWnd->m_ActDone = true;

	if (!pPopWnd->m_IsShow)
		onHideFinished();
	else
		onShowFinished();
}

void SIX_PopWnd::setAllowDragged(bool bAllowDragged)
{
	m_bAllowDragged = bAllowDragged;
}

bool SIX_PopWnd::getAllowDragged()
{
	return m_bAllowDragged;
}

// default implements are used to call script callback if exist
bool SIX_PopWnd::ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent)
{
	OnTouchLogic(pTouch,CCTOUCHBEGAN);
	return SIX_UILayer::ccTouchBegan(pTouch,pEvent);
}

void SIX_PopWnd::ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent)
{
	OnTouchLogic(pTouch,CCTOUCHMOVED);
	SIX_UILayer::ccTouchMoved(pTouch,pEvent);
}

void SIX_PopWnd::ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent)
{
	OnTouchLogic(pTouch,CCTOUCHENDED);
	SIX_UILayer::ccTouchEnded(pTouch,pEvent);
}

void SIX_PopWnd::ccTouchCancelled(CCTouch *pTouch,CCEvent *pEvent)
{
	OnTouchLogic(pTouch,CCTOUCHCANCELLED);
	SIX_UILayer::ccTouchCancelled(pTouch,pEvent);
}

void SIX_PopWnd::ccWindowMSG(CCTouch *pTouch,CCEvent *pEvent, int nType)
{
	/*if (nType==CCNCMOUSEMOVE)
		return;*/
	OnTouchLogic(pTouch,nType);
}

void SIX_PopWnd::OnTouchLogic(CCTouch *pTouch,int pEvent)
{
	// 相对GL坐标系
	CCPoint pos = pTouch->getLocation();
	//// 相对屏幕坐标系
	//CCPoint posInView = pTouch->getLocationInView();
	//// 转换后：location==pos
	//CCPoint location = CCDirector::sharedDirector()->convertToGL(posInView);

	//SIXLog("SIX_PopWnd.OnTouchLogic.pTouch[0x%08X].pEvent[%d]",pTouch,pEvent);

	switch (pEvent)
	{
	case CCTOUCHBEGAN:
		{
			if (!m_bAllowDragged)
				return;

			CCRect rcPopWnd = CCRect(this->getPositionX(),this->getPositionY(),this->getContentSize().width,this->getContentSize().height);
			if (!rcPopWnd.containsPoint(pos))
				break;

			m_LastHitPos = pos;

			m_IsDragged = true;
			break;
		}
	case CCTOUCHMOVED:
		{
			// PopWnd拖拽
			// Cool.Cat
			if (!m_IsDragged)
				break;

			CCRect rcPopWnd = CCRect(this->getPositionX(),this->getPositionY(),this->getContentSize().width,this->getContentSize().height);
			if (!rcPopWnd.containsPoint(pos))
				break;

			CCPoint HitPos = CCPoint(pos.x - m_LastHitPos.x,pos.y - m_LastHitPos.y);

			float absPosX = this->getPositionX()+HitPos.x;
			float absPosY = this->getPositionY()+HitPos.y;

			float maxWidth = CCDirector::sharedDirector()->getWinSize().width;
			float maxHeight = CCDirector::sharedDirector()->getWinSize().height;

			if (absPosX<0.0)
				absPosX = 0.0;
			else if (absPosX+this->getContentSize().width>maxWidth)
				absPosX = maxWidth - this->getContentSize().width;

			if (absPosY<0.0)
				absPosY = 0.0;
			else if (absPosY+this->getContentSize().height>maxHeight)
				absPosY = maxHeight - this->getContentSize().height;

			// save it~
			m_LastHitPos = pos;

			this->setPosition(ccp(absPosX,absPosY));
			break;
		}
	default:
		{
			m_IsDragged = false;
			break;
		}
	}
}

void SIX_PopWnd::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControlButton *pButton = (CCControlButton*)pSender;
	int tag = pButton->getTag();
	SIXLog("SIX_PopWnd.doEvents.pSender[0x%08X].event[%d].tag[%d].onCCControlEventTouchUpInside",pSender,event,tag);

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
			case BTN_SUBMIT:
				{
					if (this->OnSubmit())
						this->Show(false);
					break;
				}
			case BTN_CANCEL:
				{
					if (this->OnCancel())
						this->Show(false);
					break;
				}
			case BTN_CLOSE:
				{
					if (this->OnClose())
						this->Show(false);
					break;
				}
			default:
				{
					this->OnBtn(pSender,tag);
					break;
				}
			}
			break;
		}
	}
}