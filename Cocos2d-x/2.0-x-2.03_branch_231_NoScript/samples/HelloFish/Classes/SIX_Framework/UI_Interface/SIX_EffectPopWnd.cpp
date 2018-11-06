#include "SIX_EffectPopWnd.h"

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
			pActArr->addObject(CCMoveTo::create(0.1f,beginOffset));
			pActArr->addObject(CCMoveTo::create(0.1f,maxOffset));
			pActArr->addObject(CCMoveTo::create(0.1f,minOffset));
			pActArr->addObject(CCMoveTo::create(0.1f,endOffset));
		}
		else
		{
			pActArr->addObject(CCScaleTo::create(0.2f,1.05f));
			pActArr->addObject(CCScaleTo::create(0.1f,1.0f));
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
			pActArr->addObject(CCMoveTo::create(0.3f,endOffset));
		}
		else
		{
			pActArr->addObject(CCScaleTo::create(0.1f,1.05f));
			pActArr->addObject(CCScaleTo::create(0.2f,0.0f));
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