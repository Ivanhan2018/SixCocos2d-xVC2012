#include "SIX_EffectPopWnd.h"
#include "SIX_GlobalMgr.h"//add by Ivan_han 20131102

SIX_EffectPopWnd::SIX_EffectPopWnd()
{
}

SIX_EffectPopWnd::~SIX_EffectPopWnd()
{
}

SIX_EffectPopWnd *SIX_EffectPopWnd::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset,MOVABLE_TYPE showType,MOVABLE_TYPE hideType,bool bSeqExec)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_EffectPopWnd *pPopWnd = new SIX_EffectPopWnd();
	if (pPopWnd && pPopWnd->init())
	{
		pPopWnd->initWithColor(color,width,height);
		pPopWnd->setPosition(x,y);
		pPopWnd->setRedrawBorder(true);
		pPopWnd->m_ForbiddenTouch = true;
		pPopWnd->m_bCloseThenCleanup = false;
		pPopWnd->m_fShakeOffset = shakeOffset;
		pPopWnd->m_tShowType = showType;
		pPopWnd->m_tHideType = hideType;
		pPopWnd->m_bSeqExec = bSeqExec;
	}
	return pPopWnd;
}

bool SIX_EffectPopWnd::init()
{
	if (!SIX_PopWnd::init())
		return false;
	m_fShakeOffset = DEFAULT_SHAKEOFFSET;
	m_tShowType = MOVABLE_NONE;
	m_tHideType = MOVABLE_NONE;
	m_bSeqExec = true;

	// 设置显示/隐藏位移参数
	setParamsShowMovable(0.1f,0.1f,0.1f,0.1f);
	setParamsHideMovable(0.3f);
	// 设置显示/隐藏非位移参数
	setParamsShowUnMovable(0.2f,1.05f,0.1f,1.0f);
	setParamsHideUnMovable(0.1f,1.05f,0.2f,0.0f);
	return true;
}

void SIX_EffectPopWnd::onEnterTransitionDidFinish()
{
}

void SIX_EffectPopWnd::setShowType(MOVABLE_TYPE type)
{
	m_tShowType = type;
}

MOVABLE_TYPE SIX_EffectPopWnd::getShowType()
{
	return m_tShowType;
}

void SIX_EffectPopWnd::setHideType(MOVABLE_TYPE type)
{
	m_tHideType = type;
}

MOVABLE_TYPE SIX_EffectPopWnd::getHideType()
{
	return m_tHideType;
}

void SIX_EffectPopWnd::setShakeOffset(float shakeOffset)
{
	m_fShakeOffset = shakeOffset;
}

float SIX_EffectPopWnd::getShakeOffset()
{
	return m_fShakeOffset;
}

void SIX_EffectPopWnd::setSeqExec(bool bSeqExec)
{
	m_bSeqExec = bSeqExec;
}

bool SIX_EffectPopWnd::getSeqExec()
{
	return m_bSeqExec;
}

void SIX_EffectPopWnd::Show(bool IsShow)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return;

	if (!m_ActDone)
		return;

	// 对话框显示/隐藏音效
	// add by Ivan_han 20131102
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(IsShow?500:400,false);

	setScale(1.0f);

	m_ActDone = false;

	m_IsShow = IsShow;

	CCSize viewSize = CCEGLView::sharedOpenGLView()->getSize();
	CCSize selfSize = this->getContentSize();

	CCPoint beginOffset = CCPointZero;
	CCPoint endOffset = CCPointZero;
	CCPoint maxOffset = CCPointZero;
	CCPoint minOffset = CCPointZero;

	CCArray *pActArr = CCArray::create();
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

		endOffset = ccp((viewSize.width-selfSize.width)/2,(viewSize.height-selfSize.height)/2);

		maxOffset.x = endOffset.x;
		maxOffset.y = endOffset.y;

		minOffset.x = endOffset.x;
		minOffset.y = endOffset.y;

		switch (m_tShowType)
		{
		case MOVABLE_LEFT:
			{
				beginOffset = ccp(-selfSize.width,(viewSize.height-selfSize.height)/2);
				maxOffset.x = endOffset.x + this->getShakeOffset();
				minOffset.x = endOffset.x - this->getShakeOffset();
				break;
			}
		case MOVABLE_RIGHT:
			{
				beginOffset = ccp(viewSize.width+selfSize.width,(viewSize.height-selfSize.height)/2);
				maxOffset.x = endOffset.x + this->getShakeOffset();
				minOffset.x = endOffset.x - this->getShakeOffset();
				break;
			}
		case MOVABLE_TOP:
			{
				beginOffset = ccp((viewSize.width-selfSize.width)/2,viewSize.height+selfSize.height/2);
				maxOffset.y = endOffset.y + this->getShakeOffset();
				minOffset.y = endOffset.y - this->getShakeOffset();
				break;
			}
		case MOVABLE_BOTTOM:
			{
				beginOffset = ccp((viewSize.width-selfSize.width)/2,-selfSize.height/2);
				maxOffset.y = endOffset.y + this->getShakeOffset();
				minOffset.y = endOffset.y - this->getShakeOffset();
				break;
			}
		default:
			{
				beginOffset = ccp((viewSize.width-selfSize.width)/2,(viewSize.height-selfSize.height)/2);
				setScale(0.0f);
				break;
			}
		}

		this->setPosition(beginOffset);

		if (m_tShowType!=MOVABLE_NONE)
		{
			pActArr->addObject(CCMoveTo::create(m_fShowDelayBeginOffset,beginOffset));
			pActArr->addObject(CCMoveTo::create(m_fShowDelayMaxOffset,maxOffset));
			pActArr->addObject(CCMoveTo::create(m_fShowDelayMinOffset,minOffset));
			pActArr->addObject(CCMoveTo::create(m_fShowDelayEndOffset,endOffset));
		}
		else
		{
			pActArr->addObject(CCScaleTo::create(m_fShowDelayScaleMax,m_fShowRatioScaleMax));
			pActArr->addObject(CCScaleTo::create(m_fShowDelayScaleOrigin,m_fShowRatioScaleOrigin));
		}
		//// 视角翻转(x轴)
		//pActArr->addObject(CCOrbitCamera::create(0.3f,1.0f,0.0f,0.0f,360.0f,0.0f,0.0f));
		++m_WndCount;
	}
	else
	{
		setSwallowsTouches(false);
		setTouchEventPause(true);

		CCPoint currentPos = this->getPosition();

		switch (m_tHideType)
		{
		case MOVABLE_LEFT:
			{
				endOffset = ccp(-selfSize.width,currentPos.y);
				break;
			}
		case MOVABLE_RIGHT:
			{
				endOffset = ccp(viewSize.width+selfSize.width,currentPos.y);
				break;
			}
		case MOVABLE_TOP:
			{
				endOffset = ccp(currentPos.x,viewSize.height+selfSize.height);
				break;
			}
		case MOVABLE_BOTTOM:
			{
				endOffset = ccp(currentPos.x,-selfSize.height);
				break;
			}
		default:
			{
				endOffset = ccp(currentPos.x,currentPos.y);
				break;
			}
		}

		if (m_tHideType!=MOVABLE_NONE)
		{
			pActArr->addObject(CCMoveTo::create(m_fHideDelayEndOffset,endOffset));
		}
		else
		{
			pActArr->addObject(CCScaleTo::create(m_fHideDelayScaleMax,m_fHideRatioScaleMax));
			pActArr->addObject(CCScaleTo::create(m_fHideDelayScaleMin,m_fHideRatioScaleMin));
		}
		--m_WndCount;
	}

	if (pActArr->count()>0)
	{
		pActArr->addObject(CCCallFuncN::create(this,callfuncN_selector(SIX_PopWnd::ShowActionCallBack)));
		if (m_bSeqExec)
			runAction(CCSequence::create(pActArr));
		else
			runAction(CCSpawn::create(pActArr));
	}
}

void SIX_EffectPopWnd::onShowFinished()
{
}

void SIX_EffectPopWnd::onHideFinished()
{
}

// 设置显示/隐藏位移参数
void SIX_EffectPopWnd::setParamsShowMovable(float delayBegin,float delayMax,float delayMin,float delayEnd)
{
	m_fShowDelayBeginOffset = delayBegin;
	m_fShowDelayMaxOffset = delayMax;
	m_fShowDelayMinOffset = delayMin;
	m_fShowDelayEndOffset = delayEnd;
}

void SIX_EffectPopWnd::setParamsHideMovable(float delayEnd)
{
	m_fHideDelayEndOffset = delayEnd;
}

// 设置显示/隐藏非位移参数
void SIX_EffectPopWnd::setParamsShowUnMovable(float delayScaleMax,float ratioScaleMax,float delayScaleOrigin,float ratioScaleOrigin)
{
	m_fShowDelayScaleMax = delayScaleMax;
	m_fShowRatioScaleMax = ratioScaleMax;
	m_fShowDelayScaleOrigin = delayScaleOrigin;
	m_fShowRatioScaleOrigin = ratioScaleOrigin;
}

void SIX_EffectPopWnd::setParamsHideUnMovable(float delayScaleMax,float ratioScaleMax,float delayScaleMin,float ratioScaleMin)
{
	m_fHideDelayScaleMax = delayScaleMax;
	m_fHideRatioScaleMax = ratioScaleMax;
	m_fHideDelayScaleMin = delayScaleMin;
	m_fHideRatioScaleMin = ratioScaleMin;
}