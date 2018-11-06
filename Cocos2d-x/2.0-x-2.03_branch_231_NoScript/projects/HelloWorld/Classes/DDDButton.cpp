
#include "DDDButton.h"
#include "CCScale9Sprite.h"
#include "support/CCPointExtension.h"
#include "label_nodes/CCLabelTTF.h"
#include "label_nodes/CCLabelBMFont.h"
#include "actions/CCAction.h"
#include "actions/CCActionInterval.h"

using namespace std;

NS_CC_EXT_BEGIN

int originalY;

enum
{
    kDDDZoomActionTag = 0xCCCB0001,
};

DDDButton::DDDButton()
: m_currentTitle(NULL)
, m_currentTitleColor(ccWHITE)
, m_doesAdjustBackgroundImage(false)
, m_titleLabel(NULL)
, m_backgroundSprite(NULL)
, m_zoomOnTouchDown(false)
, m_isPushed(false)
, m_bParentInited(false)
, m_titleDispatchTable(NULL)
, m_titleColorDispatchTable(NULL)
, m_titleLabelDispatchTable(NULL)
, m_backgroundSpriteDispatchTable(NULL)
, m_marginH(DDDButtonMarginLR)
, m_marginV(DDDButtonMarginTB)
{

}

DDDButton::~DDDButton()
{
    CC_SAFE_RELEASE(m_backgroundSpriteDispatchTable);
    CC_SAFE_RELEASE(m_titleLabelDispatchTable);
    CC_SAFE_RELEASE(m_titleColorDispatchTable);
    CC_SAFE_RELEASE(m_titleDispatchTable);
    CC_SAFE_RELEASE(m_backgroundSprite);
}

//initialisers

bool DDDButton::init()
{
    return this->initWithLabelAndBackgroundSprite(CCLabelTTF::create("", "Helvetica", 12), CCScale9Sprite::create());
}

bool DDDButton::initWithLabelAndBackgroundSprite(CCNode* node, CCScale9Sprite* backgroundSprite)
{
    if (CCControl::init())
    {
        CCAssert(node != NULL, "Label must not be nil.");
        CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(node);
        CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(node);
        CCAssert(backgroundSprite != NULL, "Background sprite must not be nil.");
        CCAssert(label != NULL || rgbaLabel!=NULL || backgroundSprite != NULL, "");
        
        m_bParentInited = true;

        // Initialize the button state tables
        this->setTitleDispatchTable(CCDictionary::create());
        this->setTitleColorDispatchTable(CCDictionary::create());
        this->setTitleLabelDispatchTable(CCDictionary::create());
        this->setBackgroundSpriteDispatchTable(CCDictionary::create());

        setTouchEnabled(true);
        m_isPushed = false;
        m_zoomOnTouchDown = true;

        m_currentTitle=NULL;

        // Adjust the background image by default
        setAdjustBackgroundImage(true);
        setPreferredSize(CCSizeZero);
        // Zooming button by default
        m_zoomOnTouchDown = true;
        
        // Set the default anchor point
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(ccp(0.5f, 0.5f));
        
        // Set the nodes
        setTitleLabel(node);
        setBackgroundSprite(backgroundSprite);

        // Set the default color and opacity
        setColor(ccc3(255.0f, 255.0f, 255.0f));
        setOpacity(255.0f);
        setOpacityModifyRGB(true);
        
        // Initialize the dispatch table
        
        CCString* tempString = CCString::create(label->getString());
        //tempString->autorelease();
        setTitleForState(tempString, CCControlStateNormal);
        setTitleColorForState(rgbaLabel->getColor(), CCControlStateNormal);
        setTitleLabelForState(node, CCControlStateNormal);
        setBackgroundSpriteForState(backgroundSprite, CCControlStateNormal);
        
        setLabelAnchorPoint(ccp(0.5f, 0.5f));

        // Layout update
        needsLayout();

        return true;
    }
    //couldn't init the CCControl
    else
    {
        return false;
    }
}

DDDButton* DDDButton::buttonWithLabelAndBackgroundSprite(CCNode* label, CCScale9Sprite* backgroundSprite)
{
    return DDDButton::create(label, backgroundSprite);
}

DDDButton* DDDButton::create(CCNode* label, CCScale9Sprite* backgroundSprite)
{
    DDDButton *pRet = new DDDButton();
    pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite);
    pRet->autorelease();
    return pRet;
}

bool DDDButton::initWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize)
{
    CCLabelTTF *label = CCLabelTTF::create(title.c_str(), fontName, fontSize);
    return initWithLabelAndBackgroundSprite(label, CCScale9Sprite::create());
}

DDDButton* DDDButton::buttonWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize)
{
    return DDDButton::create(title, fontName, fontSize);
}

DDDButton* DDDButton::create(string title, const char * fontName, float fontSize)
{
    DDDButton *pRet = new DDDButton();
    pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
    pRet->autorelease();
    return pRet;
}

bool DDDButton::initWithBackgroundSprite(CCScale9Sprite* sprite)
{
    CCLabelTTF *label = CCLabelTTF::create("", "Arial", 30);//
    return initWithLabelAndBackgroundSprite(label, sprite);
}

DDDButton* DDDButton::buttonWithBackgroundSprite(CCScale9Sprite* sprite)
{
    return DDDButton::create(sprite);
}

DDDButton* DDDButton::create(CCScale9Sprite* sprite)
{
    DDDButton *pRet = new DDDButton();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    return pRet;
}


void DDDButton::setMargins(int marginH, int marginV)
{
    m_marginV=marginV;
    m_marginH=marginH;
    needsLayout();
}

void DDDButton::setEnabled(bool enabled)
{
    CCControl::setEnabled(enabled);
    needsLayout();
}

void DDDButton::setSelected(bool enabled)
{
    CCControl::setSelected(enabled);
    needsLayout();
}

void DDDButton::setHighlighted(bool enabled)
{
    CCControl::setHighlighted(enabled);

    CCAction *action =getActionByTag(kDDDZoomActionTag);
    if (action)
    {
        stopAction(action);        
    }
    needsLayout();
    if( m_zoomOnTouchDown )
    {
        float scaleValue = (isHighlighted() && isEnabled() && !isSelected()) ? 0.99f : 1.0f;
        CCAction *zoomAction =CCScaleTo::create(0.05f, scaleValue);
        zoomAction->setTag(kDDDZoomActionTag);
        runAction(zoomAction);
    }
}

void DDDButton::setZoomOnTouchDown(bool zoomOnTouchDown)
{
    m_zoomOnTouchDown = zoomOnTouchDown;
}

bool DDDButton::getZoomOnTouchDown()
{
    return m_zoomOnTouchDown;
}

void DDDButton::setPreferredSize(CCSize size)
{
    if(size.width == 0 && size.height == 0)
    {
        m_doesAdjustBackgroundImage = true;
    }
    else
    {
        m_doesAdjustBackgroundImage = false;
        CCDictElement * item = NULL;
        CCDICT_FOREACH(m_backgroundSpriteDispatchTable, item)
        {
            CCScale9Sprite* sprite = (CCScale9Sprite*)item->getObject();
            sprite->setPreferredSize(size);
        }
    }

    m_preferredSize = size;
    needsLayout();
}

CCSize DDDButton::getPreferredSize()
{
    return m_preferredSize;
}

void DDDButton::setAdjustBackgroundImage(bool adjustBackgroundImage)
{
    m_doesAdjustBackgroundImage=adjustBackgroundImage;
    needsLayout();
}

bool DDDButton::doesAdjustBackgroundImage()
{
    return m_doesAdjustBackgroundImage;
}

CCPoint DDDButton::getLabelAnchorPoint()
{
    return this->m_labelAnchorPoint;
}

void DDDButton::setLabelAnchorPoint(CCPoint labelAnchorPoint)
{
    this->m_labelAnchorPoint = labelAnchorPoint;
    if (m_titleLabel != NULL)
    {
        this->m_titleLabel->setAnchorPoint(labelAnchorPoint);
    }
}

CCString* DDDButton::getTitleForState(CCControlState state)
{
    if (m_titleDispatchTable != NULL)
    {
        CCString* title=(CCString*)m_titleDispatchTable->objectForKey(state);    
        if (title)
        {
            return title;
        }
        return (CCString*)m_titleDispatchTable->objectForKey(CCControlStateNormal);
    }
    return CCString::create("");
}

void DDDButton::setTitleForState(CCString* title, CCControlState state)
{
    m_titleDispatchTable->removeObjectForKey(state);

    if (title)
    {
        m_titleDispatchTable->setObject(title, state);
    }
    
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}


const ccColor3B DDDButton::getTitleColorForState(CCControlState state)
{
    ccColor3B returnColor = ccWHITE;
    do 
    {
        CC_BREAK_IF(NULL == m_titleColorDispatchTable);
        CCColor3bObject* colorObject=(CCColor3bObject*)m_titleColorDispatchTable->objectForKey(state);    
        if (colorObject)
        {
            returnColor= colorObject->value;
            break;
        }

        colorObject=(CCColor3bObject*)m_titleColorDispatchTable->objectForKey(CCControlStateNormal);   
        if (colorObject)
        {
            returnColor=colorObject->value;
        }
    } while (0);

    return returnColor;
}

void DDDButton::setTitleColorForState(ccColor3B color, CCControlState state)
{
    //ccColor3B* colorValue=&color;
    m_titleColorDispatchTable->removeObjectForKey(state); 
    CCColor3bObject* pColor3bObject = new CCColor3bObject(color);
    pColor3bObject->autorelease();
    m_titleColorDispatchTable->setObject(pColor3bObject, state);
      
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

CCNode* DDDButton::getTitleLabelForState(CCControlState state)
{
    CCNode* titleLabel=(CCNode*)m_titleLabelDispatchTable->objectForKey(state);    
    if (titleLabel)
    {
        return titleLabel;
    }
    return (CCNode*)m_titleLabelDispatchTable->objectForKey(CCControlStateNormal);
}

void DDDButton::setTitleLabelForState(CCNode* titleLabel, CCControlState state)
{
    CCNode* previousLabel = (CCNode*)m_titleLabelDispatchTable->objectForKey(state);
    if (previousLabel)
    {
        removeChild(previousLabel, true);
        m_titleLabelDispatchTable->removeObjectForKey(state);        
    }

    m_titleLabelDispatchTable->setObject(titleLabel, state);
    titleLabel->setVisible(false);
    titleLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(titleLabel, 1);

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void DDDButton::setTitleTTFForState(const char * fntFile, CCControlState state)
{
    CCString * title = this->getTitleForState(state);
    if (!title)
    {
        title = CCString::create("");
    }
    this->setTitleLabelForState(CCLabelTTF::create(title->getCString(), fntFile, 12), state);
}

const char * DDDButton::getTitleTTFForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getFontName();
    }
    else
    {
        return "";
    }
}

void DDDButton::setTitleTTFSizeForState(float size, CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    if(label)
    {
        CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
        if(labelTTF != 0)
        {
            return labelTTF->setFontSize(size);
        }
    }
}

float DDDButton::getTitleTTFSizeForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getFontSize();
    }
    else
    {
        return 0;
    }
}

void DDDButton::setTitleBMFontForState(const char * fntFile, CCControlState state)
{
    CCString * title = this->getTitleForState(state);
    if (!title)
    {
        title = CCString::create("");
    }
    this->setTitleLabelForState(CCLabelBMFont::create(title->getCString(), fntFile), state);
}

const char * DDDButton::getTitleBMFontForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelBMFont* labelBMFont = dynamic_cast<CCLabelBMFont*>(label);
    if(labelBMFont != 0)
    {
        return labelBMFont->getFntFile();
    }
    else
    {
        return "";
    }
}


CCScale9Sprite* DDDButton::getBackgroundSpriteForState(CCControlState state)
{
    CCScale9Sprite* backgroundSprite=(CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(state);    
    if (backgroundSprite)
    {
        return backgroundSprite;
    }
    return (CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(CCControlStateNormal);
}


void DDDButton::setBackgroundSpriteForState(CCScale9Sprite* sprite, CCControlState state)
{
    CCSize oldPreferredSize = m_preferredSize;

    CCScale9Sprite* previousBackgroundSprite = (CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(state);
    if (previousBackgroundSprite)
    {
        removeChild(previousBackgroundSprite, true);
        m_backgroundSpriteDispatchTable->removeObjectForKey(state);
    }

    m_backgroundSpriteDispatchTable->setObject(sprite, state);
    sprite->setVisible(false);
    sprite->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(sprite);

    if (this->m_preferredSize.width != 0 || this->m_preferredSize.height != 0)
    {
        if (oldPreferredSize.equals(m_preferredSize))
        {
            // Force update of preferred size
            sprite->setPreferredSize(CCSizeMake(oldPreferredSize.width+1, oldPreferredSize.height+1));
        }
        
        sprite->setPreferredSize(this->m_preferredSize);
    }

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void DDDButton::setBackgroundSpriteFrameForState(CCSpriteFrame * spriteFrame, CCControlState state)
{
    CCScale9Sprite * sprite = CCScale9Sprite::createWithSpriteFrame(spriteFrame);
    this->setBackgroundSpriteForState(sprite, state);
}


void DDDButton::needsLayout()
{
    if (!m_bParentInited) {
        return;
    }
    // Hide the background and the label
    if (m_titleLabel != NULL) {
        m_titleLabel->setVisible(false);
    }
    if (m_backgroundSprite) {
        m_backgroundSprite->setVisible(false);
    }
    // Update anchor of all labels
    this->setLabelAnchorPoint(this->m_labelAnchorPoint);
    
    // Update the label to match with the current state
    CC_SAFE_RELEASE(m_currentTitle);
    m_currentTitle = getTitleForState(m_eState);
    CC_SAFE_RETAIN(m_currentTitle);

    m_currentTitleColor=getTitleColorForState(m_eState);

    this->setTitleLabel(getTitleLabelForState(m_eState));

    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(m_titleLabel);
    if (label && m_currentTitle)
    {
        label->setString(m_currentTitle->getCString());
    }

    CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(m_titleLabel);
    if (rgbaLabel)
    {
        rgbaLabel->setColor(m_currentTitleColor);
    }
    if (m_titleLabel != NULL)
    {
        m_titleLabel->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
    
    // Update the background sprite
    this->setBackgroundSprite(this->getBackgroundSpriteForState(m_eState));
    if (m_backgroundSprite != NULL)
    {
        m_backgroundSprite->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
   
    // Get the title label size
    CCSize titleLabelSize;
    if (m_titleLabel != NULL)
    {
        titleLabelSize = m_titleLabel->boundingBox().size;
    }
    
    // Adjust the background image if necessary
    if (m_doesAdjustBackgroundImage)
    {
        // Add the margins
        if (m_backgroundSprite != NULL)
        {
            m_backgroundSprite->setContentSize(CCSizeMake(titleLabelSize.width + m_marginH * 2, titleLabelSize.height + m_marginV * 2));
        }
    } 
    else
    {        
        //TODO: should this also have margins if one of the preferred sizes is relaxed?
        if (m_backgroundSprite != NULL)
        {
            CCSize preferredSize = m_backgroundSprite->getPreferredSize();
            if (preferredSize.width <= 0)
            {
                preferredSize.width = titleLabelSize.width;
            }
            if (preferredSize.height <= 0)
            {
                preferredSize.height = titleLabelSize.height;
            }

            m_backgroundSprite->setContentSize(preferredSize);
        }
    }
    
    // Set the content size
    CCRect rectTitle;
    if (m_titleLabel != NULL)
    {
        rectTitle = m_titleLabel->boundingBox();
    }
    CCRect rectBackground;
    if (m_backgroundSprite != NULL)
    {
        rectBackground = m_backgroundSprite->boundingBox();
    }

    CCRect maxRect = CCControlUtils::CCRectUnion(rectTitle, rectBackground);
    setContentSize(CCSizeMake(maxRect.size.width, maxRect.size.height));        
    
    if (m_titleLabel != NULL)
    {
        m_titleLabel->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        // Make visible the background and the label
        m_titleLabel->setVisible(true);
    }
  
    if (m_backgroundSprite != NULL)
    {
        m_backgroundSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        m_backgroundSprite->setVisible(true);   
    }   
}



bool DDDButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
    {
        return false;
    }
    originalY = pTouch->getLocation().y;
    m_eState=CCControlStateHighlighted;
    m_isPushed=true;
    this->setHighlighted(true);
    sendActionsForControlEvents(CCControlEventTouchDown);
    return true;
}

void DDDButton::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{    
    if (!isEnabled() || !isPushed() || isSelected())
    {
        if (isHighlighted())
        {
            setHighlighted(false);
        }
        return;
    }
    
    bool isTouchMoveInside = isTouchInside(pTouch);
    if (isTouchMoveInside && !isHighlighted())
    {
        m_eState = CCControlStateHighlighted;
        setHighlighted(true);
        sendActionsForControlEvents(CCControlEventTouchDragEnter);
    }
    else if (isTouchMoveInside && isHighlighted())
    {
        sendActionsForControlEvents(CCControlEventTouchDragInside);
    }
    else if (!isTouchMoveInside && isHighlighted())
    {
        m_eState = CCControlStateNormal;
        setHighlighted(false);
        
        sendActionsForControlEvents(CCControlEventTouchDragExit);        
    }
    else if (!isTouchMoveInside && !isHighlighted())
    {
        sendActionsForControlEvents(CCControlEventTouchDragOutside);        
    }
}
void DDDButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    m_eState = CCControlStateNormal;
    m_isPushed = false;
    setHighlighted(false);
    
    
    if (isTouchInside(pTouch))
    {
        if (pTouch->getLocation().y > originalY+5 || pTouch->getLocation().y < originalY-5) {
            return;
        }
        sendActionsForControlEvents(CCControlEventTouchUpInside);        
    }
    else
    {
        sendActionsForControlEvents(CCControlEventTouchUpOutside);        
    }
}

void DDDButton::setOpacity(GLubyte opacity)
{
    m_cOpacity = opacity;
    
    CCObject* child;
    CCArray* children=getChildren();
    CCARRAY_FOREACH(children, child)
    {
        CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
        if (pNode)
        {
            pNode->setOpacity(opacity);
        }
    }
    CCDictElement * item = NULL;
    CCDICT_FOREACH(m_backgroundSpriteDispatchTable, item)
    {
        CCScale9Sprite* sprite = (CCScale9Sprite*)item->getObject();
        sprite->setOpacity(opacity);
    }
}

GLubyte DDDButton::getOpacity()
{
    return m_cOpacity;
}

void DDDButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    m_eState = CCControlStateNormal;
    m_isPushed = false;
    setHighlighted(false);
    sendActionsForControlEvents(CCControlEventTouchCancel);
}

DDDButton* DDDButton::create()
{
    DDDButton *pControlButton = new DDDButton();
    if (pControlButton && pControlButton->init())
    {
        pControlButton->autorelease();
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return NULL;
}

DDDButton* DDDButton::node()
{
    return DDDButton::create();
}

NS_CC_EXT_END
