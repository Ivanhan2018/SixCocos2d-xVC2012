#include "SIX_UILayer.h"

//USING_NS_CC_EXT;

SIX_UILayer::SIX_UILayer(bool bTouchThroughForbidden,int nPriority,bool bRedrawBorder,bool bScissor)
{
	m_ForbiddenTouch = bTouchThroughForbidden;
	m_nPriority = nPriority;
	m_bScissor = bScissor;

	setRedrawBorder(bRedrawBorder);
	setBorderColor(ccc4(255,0,0,255));
}

SIX_UILayer::~SIX_UILayer()
{
}

bool SIX_UILayer::getRedrawBorder()
{
	return m_RedrawBorder;
}

void SIX_UILayer::setRedrawBorder(bool bRedrawBorder)
{
	m_RedrawBorder = bRedrawBorder;
}

ccColor4B SIX_UILayer::getBorderColor()
{
	return m_BorderColor;
}

void SIX_UILayer::setBorderColor(const ccColor4B& color)
{
	m_BorderColor = color;
}

void *SIX_UILayer::GetInterface(const char *pstrName)
{
#ifdef WIN32
	if(!_stricmp(pstrName,"UILayer")) 
#else
	if(!strcasecmp(pstrName,"UILayer")) 
#endif
		return static_cast<SIX_UILayer*>(this);
	return 0;
}

/** creates a CCLayer with color, width and height in Points */
SIX_UILayer * SIX_UILayer::create(const ccColor4B& color, float width, float height,bool bTouchThroughForbidden,int nPriority,bool bRedrawBorder,bool bScissor)
{
    SIX_UILayer * pLayer = new SIX_UILayer(bTouchThroughForbidden,nPriority,bRedrawBorder,bScissor);
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

/** creates a CCLayer with color. Width and height are the window size. */
SIX_UILayer * SIX_UILayer::create(const ccColor4B& color,bool bTouchThroughForbidden,int nPriority,bool bRedrawBorder,bool bScissor)
{
    SIX_UILayer * pLayer = new SIX_UILayer(bTouchThroughForbidden,nPriority,bRedrawBorder,bScissor);
    if(pLayer && pLayer->initWithColor(color))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool SIX_UILayer::initWithColor(const ccColor4B& color, float w, float h)
{
    if( SIX_UILayer::init() ) {

        // default blend function
        m_tBlendFunc.src = GL_SRC_ALPHA;
        m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;

        m_tColor.r = color.r;
        m_tColor.g = color.g;
        m_tColor.b = color.b;
        m_cOpacity = color.a;

        for (int i = 0; i<sizeof(m_pSquareVertices) / sizeof( m_pSquareVertices[0]); i++ ) {
            m_pSquareVertices[i].x = 0.0f;
            m_pSquareVertices[i].y = 0.0f;
        }

        updateColor();
        setContentSize(CCSizeMake(w, h));

        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    }
    return true;
}

bool SIX_UILayer::initWithColor(const ccColor4B& color)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    this->initWithColor(color, s.width, s.height);
    return true;
}

bool SIX_UILayer::init()
{
	if (!CCLayer::init())
		return false;
	setTouchEnabled(true);
	return true;
}

// 设置优先级
void SIX_UILayer::setPriority(int Priority)
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->setPriority(Priority,this);
}

// 获取优先级
int SIX_UILayer::getPriority()
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	return pDispatcher->getPriority(this);
}

// 提升优先级
void SIX_UILayer::PriorityPromote()
{
	CCLayer *pFather = dynamic_cast<CCLayer*>(this->getParent());
	if (!pFather)
		return;

	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();

	// 取父节点的触碰handler
	CCTouchHandler *handler = pDispatcher->findHandler(pFather);
	if (!handler)
		return;

	int nPriority = handler->getPriority()-1;

	//pDispatcher->setPriority(nPriority,this);

	//// 取自身触碰handler
	//handler = pDispatcher->findHandler(this);
	//if (!handler)
	//	return;

	//handler->setPriority(nPriority);
}

// 降低优先级
void SIX_UILayer::PriorityReduce()
{
	CCLayer *pFather = dynamic_cast<CCLayer*>(this->getParent());
	if (!pFather)
		return;

	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();

	// 取父节点的触碰handler
	CCTouchHandler *handler = pDispatcher->findHandler(pFather);
	if (!handler)
		return;

	int nPriority = handler->getPriority()+1;

	//pDispatcher->setPriority(nPriority,this);

	//// 取自身触碰handler
	//handler = pDispatcher->findHandler(this);
	//if (!handler)
	//	return;

	//handler->setPriority(nPriority);
}

// 是否拦截触碰事件
void SIX_UILayer::setSwallowsTouches(bool bSwallowsTouches)
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	CCTargetedTouchHandler *handler = dynamic_cast<CCTargetedTouchHandler*>(pDispatcher->findHandler(this));
	if (!handler)
		return;

	handler->setSwallowsTouches(bSwallowsTouches);
}

bool SIX_UILayer::getSwallowsTouches()
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	CCTargetedTouchHandler *handler = dynamic_cast<CCTargetedTouchHandler*>(pDispatcher->findHandler(this));
	if (!handler)
		return false;

	return handler->isSwallowsTouches();
}

static void setTouchEventPauseLoop(CCLayer *pRoot,bool bPause)
{
	if (!pRoot)
		return;

	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();

	// 处理子节点
	CCTouchDelegate *pDelegate = 0;
	CCTouchHandler *pHandler = 0;
	CCNode *pChild = 0;
	CCARRAY_FOREACH_T(pRoot->getChildren(),pChild,CCNode*)
	{
		if (!pChild)
			continue;

		pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
		if (!pDelegate)
			continue;

		pHandler = pDispatcher->findHandler(pDelegate);
		if (!pHandler)
			continue;

		pHandler->setTouchEventPause(bPause);

		// 遍历所有节点
		CCLayer *pLayer = dynamic_cast<CCLayer*>(pDelegate);

		setTouchEventPauseLoop(pLayer,bPause);
	}

	// 处理自身
	CCTouchHandler *handler = dynamic_cast<CCTouchHandler*>(pDispatcher->findHandler(pRoot));
	if (!handler)
		return;

	pHandler = dynamic_cast<CCTargetedTouchHandler*>(pDispatcher->findHandler(pRoot));

	handler->setTouchEventPause(bPause);
}

// 是否响应触碰事件，需要遍历设置所有子节点
void SIX_UILayer::setTouchEventPause(bool bPause)
{
	setTouchEventPauseLoop(this,bPause);
}

bool SIX_UILayer::getTouchEventPause()
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	CCTouchHandler *handler = dynamic_cast<CCTouchHandler*>(pDispatcher->findHandler(this));
	if (!handler)
		return false;

	return handler->getTouchEventPause();
}

// -----------------------

void SIX_UILayer::draw()
{
	CCLayerColor::draw();

	// 画边框
	if (getRedrawBorder())
	{
		// OGL顶点顺序：左上-左下-右下-右上
		CCPoint vertices[4]={
			ccp(0,m_tContentSize.height),
			ccp(0,0),
			ccp(m_tContentSize.width,0),
			ccp(m_tContentSize.width,m_tContentSize.height),
		};
		ccDrawColor4F(m_BorderColor.r,m_BorderColor.g,m_BorderColor.b,m_BorderColor.a);
		for (int i=0;i<3;i++)
			ccDrawLine(vertices[i],vertices[i+1]);
		ccDrawLine(vertices[3],vertices[0]);
	}
}

void SIX_UILayer::beforeDraw()
{
	CCPoint screenPos = this->convertToWorldSpace(this->getPosition());

    glEnable(GL_SCISSOR_TEST);
    float s = this->getScale();
	CCEGLView::sharedOpenGLView()->setScissorInPoints(screenPos.x*s, screenPos.y*s, getContentSize().width*s, getContentSize().height*s);
}

void SIX_UILayer::visit()
{
	if (!m_bScissor)
	{
		CCLayerColor::visit();
		return;
	}

	if (!isVisible())
    {
		return;
    }

	kmGLPushMatrix();

    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        this->transformAncestors();
    }

	this->transform();
    this->beforeDraw();

	if(m_pChildren)
    {
		ccArray *arrayData = m_pChildren->data;
		unsigned int i=0;
		
		// draw children zOrder < 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode *child =  (CCNode*)arrayData->arr[i];
			if ( child->getZOrder() < 0 )
            {
				child->visit();
			}
            else
            {
				break;
            }
		}
		
		// this draw
		this->draw();
		
		// draw children zOrder >= 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode* child = (CCNode*)arrayData->arr[i];
			child->visit();
		}
	}
    else
    {
		this->draw();
    }

    this->afterDraw();
	if ( m_pGrid && m_pGrid->isActive())
    {
		m_pGrid->afterDraw(this);
    }

	kmGLPopMatrix();
}

void SIX_UILayer::afterDraw()
{
	glDisable(GL_SCISSOR_TEST);
}

void SIX_UILayer::registerWithTouchDispatcher()
{
	// 如果不吞噬touch的话，其他层也会响应touch事件，所以必须得吞噬！
	if (m_ForbiddenTouch)
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_nPriority,true);
	else
		CCLayerColor::registerWithTouchDispatcher();
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_nPriority,m_ForbiddenTouch);
}

// 吞噬掉touch的同时，分发给当前层所有子节点去响应
// 参考CCTouchDispatcher::touches
// Cool.Cat
bool SIX_UILayer::ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent)
{
	if (m_ForbiddenTouch)
	{
		CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		
		CCTouchHandler *pBaseHandler = 0;
		CCTouchHandler *pHandler = 0;
		CCTouchDelegate *pDelegate = 0;
		CCNode *pChild = 0;

		CCARRAY_FOREACH_T(this->getChildren(),pChild,CCNode*)
		{
			if (!pChild)
				continue;

			pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
			if (!pDelegate)
				continue;

			pBaseHandler = pDispatcher->findHandler(pDelegate);

			pHandler = dynamic_cast<CCTargetedTouchHandler*>(pBaseHandler);
			if (!pHandler)
				pHandler = dynamic_cast<CCStandardTouchHandler*>(pBaseHandler);

			if (pHandler)
				pHandler->getDelegate()->ccTouchBegan(pTouch, pEvent);
		}
		//return true;
	}
	//return CCLayerColor::ccTouchBegan(pTouch,pEvent);
	return true;
}

void SIX_UILayer::ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent)
{
	if (m_ForbiddenTouch)
	{
		CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		
		CCTouchHandler *pBaseHandler = 0;
		CCTouchHandler *pHandler = 0;
		CCTouchDelegate *pDelegate = 0;
		CCNode *pChild = 0;

		CCARRAY_FOREACH_T(this->getChildren(),pChild,CCNode*)
		{
			if (!pChild)
				continue;

			pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
			if (!pDelegate)
				continue;

			pBaseHandler = pDispatcher->findHandler(pDelegate);

			pHandler = dynamic_cast<CCTargetedTouchHandler*>(pBaseHandler);
			if (!pHandler)
				pHandler = dynamic_cast<CCStandardTouchHandler*>(pBaseHandler);

			if (pHandler)
				pHandler->getDelegate()->ccTouchMoved(pTouch, pEvent);
		}
		return;
	}
	//CCLayerColor::ccTouchMoved(pTouch,pEvent);
}

void SIX_UILayer::ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent)
{
	if (m_ForbiddenTouch)
	{
		CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		
		CCTouchHandler *pBaseHandler = 0;
		CCTouchHandler *pHandler = 0;
		CCTouchDelegate *pDelegate = 0;
		CCNode *pChild = 0;

		CCARRAY_FOREACH_T(this->getChildren(),pChild,CCNode*)
		{
			if (!pChild)
				continue;

			pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
			if (!pDelegate)
				continue;

			pBaseHandler = pDispatcher->findHandler(pDelegate);

			pHandler = dynamic_cast<CCTargetedTouchHandler*>(pBaseHandler);
			if (!pHandler)
				pHandler = dynamic_cast<CCStandardTouchHandler*>(pBaseHandler);

			if (pHandler)
				pHandler->getDelegate()->ccTouchEnded(pTouch, pEvent);
		}
		return;
	}
	//CCLayerColor::ccTouchEnded(pTouch,pEvent);
}

void SIX_UILayer::ccTouchCancelled(CCTouch *pTouch,CCEvent *pEvent)
{
	if (m_ForbiddenTouch)
	{
		CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		
		CCTouchHandler *pBaseHandler = 0;
		CCTouchHandler *pHandler = 0;
		CCTouchDelegate *pDelegate = 0;
		CCNode *pChild = 0;

		CCARRAY_FOREACH_T(this->getChildren(),pChild,CCNode*)
		{
			if (!pChild)
				continue;

			pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
			if (!pDelegate)
				continue;

			pBaseHandler = pDispatcher->findHandler(pDelegate);

			pHandler = dynamic_cast<CCTargetedTouchHandler*>(pBaseHandler);
			if (!pHandler)
				pHandler = dynamic_cast<CCStandardTouchHandler*>(pBaseHandler);

			if (pHandler)
				pHandler->getDelegate()->ccTouchCancelled(pTouch, pEvent);
		}
		return;
	}
	//CCLayerColor::ccTouchCancelled(pTouch,pEvent);
}

void SIX_UILayer::ccWindowMSG(CCTouch *pTouch,CCEvent *pEvent, int nType)
{
	if (nType==CCNCMOUSEMOVE)
		return;
	if (m_ForbiddenTouch)
	{
		CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		
		CCTouchHandler *pBaseHandler = 0;
		CCTouchHandler *pHandler = 0;
		CCTouchDelegate *pDelegate = 0;
		CCNode *pChild = 0;

		CCARRAY_FOREACH_T(this->getChildren(),pChild,CCNode*)
		{
			if (!pChild)
				continue;

			pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
			if (!pDelegate)
				continue;

			pBaseHandler = pDispatcher->findHandler(pDelegate);

			pHandler = dynamic_cast<CCTargetedTouchHandler*>(pBaseHandler);
			if (!pHandler)
				pHandler = dynamic_cast<CCStandardTouchHandler*>(pBaseHandler);

			if (pHandler)
				pHandler->getDelegate()->ccWindowMSG(pTouch, pEvent, nType);
		}
		return;
	}
	//CCLayerColor::ccWindowMSG(pTouch,pEvent, nType);
}

int SIX_UILayer::OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam)
{
	return 0;
}