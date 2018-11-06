#include "SIX_EditBox.h"

static CCPoint absolutePosition(CCNode *pNode)
{
	CCPoint point = pNode->getPosition();
	CCNode *cn = pNode;
	while (cn->getParent()!=0)
	{
		cn = cn->getParent();
		point = ccpAdd(point,cn->getPosition());
	}
	return point;
}

static CCRect getRect(CCNode *pNode)
{
    CCRect rc;
	// 应该取当前节点的绝对偏移，而不是相对偏移
	// Modified by Cool.Cat
    rc.origin = absolutePosition(pNode);
    rc.size = pNode->getContentSize();
    //rc.origin.x -= rc.size.width / 2;
    //rc.origin.y -= rc.size.height / 2;
    return rc;
}

KeyboardNotificationLayer::KeyboardNotificationLayer()
: m_pTrackNode(0)
{
    setTouchEnabled(true);
}

void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void KeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    SIXLog("keyboardWillShow(origin:%f,%f, size:%f,%f)",info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);

    if (! m_pTrackNode)
        return;

    CCRect rectTracked = getRect(m_pTrackNode);
    SIXLog("trackingNodeAt(origin:%f,%f, size:%f,%f)",rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);

    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
        return;

    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = info.end.getMaxY() - rectTracked.getMinY();

    // move all the children node of KeyboardNotificationLayer
    CCArray * children = getChildren();
    CCNode * node = 0;
    int count = children->count();
    CCPoint pos;
    for (int i = 0; i < count; ++i)
    {
        node = (CCNode*)children->objectAtIndex(i);
        pos = node->getPosition();
        pos.y += adjustVert;
        node->setPosition(pos);
    }
}

// CCLayer function

bool KeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_beginPos = pTouch->getLocation();    
    return true;
}

void KeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (! m_pTrackNode)
        return;
    
    CCPoint endPos = pTouch->getLocation();    

    float delta = 1.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
    {
        // not click
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }
	
	//CCRect rect = getRect(this);
	//endPos.x += this->getPositionX();
	//endPos.y += this->getPositionY();
	//this->onClickTrackNode(rect.containsPoint(endPos));

	// 还是用原生方法判断点击范围吧
	// Cool.Cat
	CCRect rect = this->boundingBox();
	CCPoint relativePos = this->getParent()->convertToNodeSpace(endPos);
	this->onClickTrackNode(rect.containsPoint(relativePos));
}

// ----------------------------------------------------
SIX_EditBox::SIX_EditBox()
{
    m_pTextField = CCTextFieldTTF::textFieldWithPlaceHolder("WTF???",FONT_NAME,FONT_SIZE);
    m_pTextField->setDelegate(this);
	m_pTextField->setAnchorPoint(ccp(0,0));
	m_pTextField->setPlaceHolder("");
	m_pTextField->setColor(ccc3(255,255,255));
	m_pTextField->setColorSpaceHolder(ccc3(255,255,255));
	m_pTextField->setOpacity(255);
	addChild(m_pTextField);
	this->setInputTextMaxCount(255);
}

void SIX_EditBox::InitCursor(long long color,int width,int height)
{
	if (!m_pTextField)
		return;

	// 初始化光标
	char *pixels = new char[width*height];
	for (int i=0; i<width;i++) {
		for (int j=0; j<height;j++) {
			pixels[i*width+j] = color;
		}
	}
	CCTexture2D *texture = new CCTexture2D();
	texture->initWithData(pixels, kCCTexture2DPixelFormat_RGB888, 1, 1, CCSizeMake(width,height));
	m_pCursorSprite = CCSprite::createWithTexture(texture);
	m_pCursorSprite->setAnchorPoint(ccp(0,0));
	m_pCursorSprite->setVisible(false);
	m_pTextField->addChild(m_pCursorSprite);
	m_pCursorAction = CCRepeatForever::create((CCActionInterval *)CCSequence::create(CCFadeOut::create(0.5f),CCFadeIn::create(0.5f),0));
	m_pCursorSprite->runAction(m_pCursorAction);
}

std::string SIX_EditBox::subtitle()
{
    return "SIX_EditBox with action and char limit test";
}

void SIX_EditBox::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        SIXLog("附加输入法");
        pTextField->attachWithIME();
    }
    else
    {
        SIXLog("卸载输入法");
        pTextField->detachWithIME();
    }
}

bool SIX_EditBox::attachWithIME()
{
	if (!getTTF())
		return false;
	return getTTF()->attachWithIME();
}

void SIX_EditBox::onEnter()
{
    KeyboardNotificationLayer::onEnter();

    m_pTrackNode = m_pTextField;
}

void SIX_EditBox::onExit()
{
    KeyboardNotificationLayer::onExit();
}

void SIX_EditBox::UpdateCursorPos()
{
	if (m_pCursorSprite)
		m_pCursorSprite->setPositionX(getTTF()->getContentSize().width);
}

// CCTextFieldDelegate protocol
bool SIX_EditBox::onTextFieldAttachWithIME(CCTextFieldTTF * pSender)
{
	if (m_pCursorSprite)
		m_pCursorSprite->setVisible(true);
	UpdateCursorPos();
    return false;
}

bool SIX_EditBox::onTextFieldDetachWithIME(CCTextFieldTTF * pSender)
{
	if (m_pCursorSprite)
		m_pCursorSprite->setVisible(false);
    return false;
}

bool SIX_EditBox::onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen)
{
    // if insert enter, treat as default to detach with ime
    if ('\n' == *text)
    {
		if (!strlen(this->getTTF()->getString()))
			return false;
		// 丢给脚本去处理业务逻辑
		/*CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
		lua_State* m_state = pEngine->getLuaState();
		if (pEngine && m_state)
		{
			lua_pushlightuserdata(m_state,this);
			lua_pushstring(m_state,this->getTTF()->getString());
			pEngine->executeGlobalFunction("OnInputDone",2);
		}*/
        return false;
    }
    
    // if the textfield's char count more than m_nCharLimit, doesn't insert text anymore.
    if (pSender->getCharCount()+nLen >= m_nCharLimit && m_nCharLimit)
    {
        return true;
    }

	//SIXLog("InputText[%d/%d] = %s",this->getTTF()->getCharCount(),this->getInputTextMaxCount(),this->getTTF()->getString());

    return false;
}

bool SIX_EditBox::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen)
{
    return false;
}

void SIX_EditBox::onTextFieldChanged(CCTextFieldTTF * sender)
{
	 UpdateCursorPos();
}

bool SIX_EditBox::onDraw(CCTextFieldTTF * pSender)
{
    return false;
}

void SIX_EditBox::callbackRemoveNodeWhenDidAction(CCNode * pNode)
{
    this->removeChild(pNode, true);
}

// ----------------------------------
int SIX_EditBox::getInputTextMaxCount()
{
	return m_nCharLimit;
}

void SIX_EditBox::setInputTextMaxCount(int max)
{
	m_nCharLimit = max;
}

CCTextFieldTTF *SIX_EditBox::getTTF()
{
	return m_pTextField;
}