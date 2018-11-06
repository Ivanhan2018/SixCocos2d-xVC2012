#include "SIX_Slider.h"

SIX_Slider::SIX_Slider()
: m_value(0.0f)
, m_valueLast(0.0f)
, m_minimumValue(0.0f)
, m_maximumValue(0.0f)
, m_minimumAllowedValue(0.0f)
, m_maximumAllowedValue(0.0f)
, m_thumbSprite(0)
, m_thumbSpriteSelect(0)
, m_progressSprite(0)
, m_backgroundSprite(0)
{
}

SIX_Slider::~SIX_Slider()
{
    CC_SAFE_RELEASE(m_thumbSprite);
	CC_SAFE_RELEASE(m_thumbSpriteSelect);
    CC_SAFE_RELEASE(m_progressSprite);
    CC_SAFE_RELEASE(m_backgroundSprite);
}

SIX_Slider* SIX_Slider::sliderWithFiles(const char* bgFile, CCSize backgroundSize,const char* progressFile, const char* thumbFile)
{
    return SIX_Slider::create(bgFile, backgroundSize,progressFile, thumbFile);
}

SIX_Slider* SIX_Slider::create(const char* bgFile, CCSize backgroundSize,const char* progressFile, const char* thumbFile)
{
    // Prepare background for slider
    CCScale9Sprite *backgroundSprite      = CCScale9Sprite::create(bgFile);
    
    // Prepare progress for slider
    CCSprite *progressSprite        = CCSprite::create(progressFile);
    
    // Prepare thumb (menuItem) for slider
    CCScale9Sprite *thumbSprite           = CCScale9Sprite::create(thumbFile);
    
    return SIX_Slider::create(backgroundSprite, backgroundSize,progressSprite, thumbSprite);
}

SIX_Slider* SIX_Slider::sliderWithSprites(CCScale9Sprite * backgroundSprite, CCSize backgroundSize,CCSprite* pogressSprite, CCScale9Sprite* thumbSprite,CCScale9Sprite *thumbSpriteSelect)
{
    return SIX_Slider::create(backgroundSprite, backgroundSize,pogressSprite, thumbSprite,thumbSpriteSelect);
}

SIX_Slider* SIX_Slider::create(CCScale9Sprite * backgroundSprite, CCSize backgroundSize,CCSprite* pogressSprite, CCScale9Sprite* thumbSprite,CCScale9Sprite *thumbSelectSprite)
{
    SIX_Slider *pRet = new SIX_Slider();
    pRet->initWithSprites(backgroundSprite, backgroundSize,pogressSprite, thumbSprite,thumbSelectSprite);
    pRet->autorelease();
    return pRet;
}

 bool SIX_Slider::initWithSprites(CCScale9Sprite * backgroundSprite, CCSize backgroundSize,CCSprite* progressSprite, CCScale9Sprite* thumbSprite,CCScale9Sprite *thumbSelectSprite)
 {
     if (CCControlButton::init())
     {
        CCAssert(backgroundSprite,  "Background sprite must be not nil");
        CCAssert(progressSprite,    "Progress sprite must be not nil");
        CCAssert(thumbSprite,       "Thumb sprite must be not nil");

        ignoreAnchorPointForPosition(false);
        setTouchEnabled(true);

        this->setBackgroundSprite(backgroundSprite);
		this->m_backgroundSprite->setPreferredSize(backgroundSize);
        this->setProgressSprite(progressSprite);
        this->setThumbSprite(thumbSprite);
		this->setThumbSpriteSelect(thumbSelectSprite);

        // Defines the content size
        CCRect maxRect   = CCControlUtils::CCRectUnion(backgroundSprite->boundingBox(), thumbSprite->boundingBox());

        setContentSize(CCSizeMake(maxRect.size.width, maxRect.size.height));
        
        // Add the slider background
        m_backgroundSprite->setAnchorPoint(ccp(0.5f, 0.5f));
        m_backgroundSprite->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));
        addChild(m_backgroundSprite);

        // Add the progress bar
        m_progressSprite->setAnchorPoint(ccp(0.0f, 0.5f));
        m_progressSprite->setPosition(ccp(0.0f, this->getContentSize().height / 2));
        addChild(m_progressSprite);

        // Add the slider thumb  
        m_thumbSprite->setPosition(ccp(0.0f, this->getContentSize().height / 2));
        addChild(m_thumbSprite);
        
        // Init default values
        m_minimumValue                   = 0.0f;
        m_maximumValue                   = 1.0f;

        setValue(m_minimumValue);
        return true;
     }
     else
     {
         return false;
     }
 }


void SIX_Slider::setEnabled(bool enabled)
{
    CCControlButton::setEnabled(enabled);
    if (m_thumbSprite != NULL) 
    {
        m_thumbSprite->setOpacity((enabled) ? 255 : 128);
    }
}

bool SIX_Slider::isTouchInside(CCTouch * touch)
{
  CCPoint touchLocation = touch->getLocation();
  touchLocation = this->getParent()->convertToNodeSpace(touchLocation);

  CCRect rect = this->boundingBox();
  // 如果滑块设置了描点，则要加上描点偏移
  // Cool.Cat
  if (!this->getThumbSprite()->isIgnoreAnchorPointForPosition())
  {
	  rect.size.width += m_thumbSprite->getContentSize().width / 2;
	  rect.origin.x -= m_thumbSprite->getContentSize().width / 2;
  }

  return rect.containsPoint(touchLocation);
}

CCPoint SIX_Slider::locationFromTouch(CCTouch* touch)
{
  CCPoint touchLocation   = touch->getLocation();                      // Get the touch position
  touchLocation           = this->convertToNodeSpace(touchLocation);                  // Convert to the node space of this class

  if (touchLocation.x < 0)
  {
      touchLocation.x     = 0;
  } else if (touchLocation.x > m_backgroundSprite->getContentSize().width)
  {
      touchLocation.x     = m_backgroundSprite->getContentSize().width;
  }

  return touchLocation;
}


bool SIX_Slider::ccTouchBegan(CCTouch* touch, CCEvent* pEvent)
{
      if (!isTouchInside(touch) || !isEnabled())
          return false;

    CCPoint location = locationFromTouch(touch);
    sliderBegan(location);
    return true;
}

void SIX_Slider::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location = locationFromTouch(pTouch);
    sliderMoved(location);
}

void SIX_Slider::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    sliderEnded(CCPointZero);
}

void SIX_Slider::needsLayout()
{
    if (NULL == m_thumbSprite || NULL == m_backgroundSprite || NULL == m_progressSprite)
    {
        return;
    }

    // Update thumb position for new value
	float maxWidth = m_backgroundSprite->getContentSize().width;
	// 如果忽略描点的话，要减去thumb的宽度
	// Cool.Cat
	if (m_thumbSprite->isIgnoreAnchorPointForPosition())
		maxWidth = m_backgroundSprite->getContentSize().width-m_thumbSprite->getContentSize().width;
	float offset = (m_value - m_valueLast - m_minimumValue) / (m_maximumValue - m_minimumValue) * maxWidth;

    CCPoint pos = m_thumbSprite->getPosition();
	pos.x = pos.x + offset;

	if (pos.x<0.0f)
		pos.x = 0.0f;
	else
	{
		if (pos.x>maxWidth)
			pos.x = maxWidth;
	}

	m_thumbSprite->setPosition(pos);

    // Stretches content proportional to newLevel
    CCRect textureRect          = m_progressSprite->getTextureRect();
    textureRect                 = CCRectMake(textureRect.origin.x, textureRect.origin.y, pos.x, textureRect.size.height);
    m_progressSprite->setTextureRect(textureRect, m_progressSprite->isTextureRectRotated(), textureRect.size);
}

void SIX_Slider::sliderBegan(CCPoint location)
{
    this->setSelected(true);
    //this->getThumbSprite()->setColor(ccGRAY);
	// 如果点击落在滑块区域，不做处理
	// Cool.Cat
	if (m_thumbSprite->boundingBox().containsPoint(location))
		return;
	setValue(valueForLocation(location));
}

void SIX_Slider::sliderMoved(CCPoint location)
{
    setValue(valueForLocation(location));
}

void SIX_Slider::sliderEnded(CCPoint location)
{
	//if (this->isSelected())
	//{
	//	// 只有点击落在滑块区域外才做处理
	//	// Cool.Cat
	//	if (!m_thumbSprite->boundingBox().containsPoint(location))
	//		setValue(valueForLocation(m_thumbSprite->getPosition()));
	//}
    //this->getThumbSprite()->setColor(ccWHITE);
    this->setSelected(false);
}

float SIX_Slider::valueForLocation(CCPoint location)
{
	float percent = 0.0f;
	if (this->getThumbSprite()->isIgnoreAnchorPointForPosition())
		percent = location.x/ (m_backgroundSprite->getContentSize().width - this->getThumbSprite()->getContentSize().width);
	else
		percent = location.x/ m_backgroundSprite->getContentSize().width;
    return MAX(MIN(m_minimumValue + percent * (m_maximumValue - m_minimumValue), m_maximumAllowedValue), m_minimumAllowedValue);
}

void SIX_Slider::setValue(float value,bool NeedNotify)
{
	// set new value with sentinel
	if (value < m_minimumValue)
		value = m_minimumValue;

	if (value > m_maximumValue) 
		value = m_maximumValue;

	m_valueLast = m_value;
	m_value = value;

	this->needsLayout();

	if (NeedNotify)
		this->sendActionsForControlEvents(CCControlEventValueChanged);
}

float SIX_Slider::getValue()
{
	return m_value;
}

void SIX_Slider::setMinimumValue(float minimumValue)
{
	m_minimumValue=minimumValue;
	m_minimumAllowedValue = minimumValue;
	if (m_minimumValue >= m_maximumValue)    
		m_maximumValue = m_minimumValue + 1.0f;
	setValue(m_value);
}

float SIX_Slider::getMinimumValue()
{
	return m_minimumValue;
}

void SIX_Slider::setMaximumValue(float maximumValue)
{
	m_maximumValue=maximumValue;
	m_maximumAllowedValue = maximumValue;
	if (m_maximumValue <= m_minimumValue)   
		m_minimumValue = m_maximumValue - 1.0f;
	setValue(m_value);
}

float SIX_Slider::getMaximumValue()
{
	return m_maximumValue;
}

void SIX_Slider::setMinimumAllowedValue(float MinimumAllowedValue)
{
	m_minimumAllowedValue = MinimumAllowedValue;
}

float SIX_Slider::getMinimumAllowedValue()
{
	return m_minimumAllowedValue;
}

void SIX_Slider::setMaximumAllowedValue(float MaximumAllowedValue)
{
	m_maximumAllowedValue = MaximumAllowedValue;
}

float SIX_Slider::getMaximumAllowedValue()
{
	return m_maximumAllowedValue;
}

void SIX_Slider::setThumbSprite(CCScale9Sprite *ThumbSprite)
{
	if (m_thumbSprite!=ThumbSprite)
	{
		CC_SAFE_RETAIN(ThumbSprite);
		CC_SAFE_RELEASE(m_thumbSprite);
		m_thumbSprite = ThumbSprite;
	}
}

CCScale9Sprite *SIX_Slider::getThumbSprite()
{
	return m_thumbSprite;
}

void SIX_Slider::setThumbSpriteSelect(CCScale9Sprite *ThumbSpriteSelect)
{
	if (m_thumbSpriteSelect!=ThumbSpriteSelect)
	{
		CC_SAFE_RETAIN(ThumbSpriteSelect);
		CC_SAFE_RELEASE(m_thumbSpriteSelect);
		m_thumbSpriteSelect = ThumbSpriteSelect;
		this->setBackgroundSpriteForState(m_thumbSpriteSelect,CCControlStateSelected);
	}
}

CCScale9Sprite *SIX_Slider::getThumbSpriteSelect()
{
	return m_thumbSpriteSelect;
}

void SIX_Slider::setProgressSprite(CCSprite *ProgressSprite)
{
	if (m_progressSprite!=ProgressSprite)
	{
		CC_SAFE_RETAIN(ProgressSprite);
		CC_SAFE_RELEASE(m_progressSprite);
		m_progressSprite = ProgressSprite;
	}
}

CCSprite *SIX_Slider::getProgressSprite()
{
	return m_progressSprite;
}

void SIX_Slider::setBackgroundSprite(CCScale9Sprite *BackgroundSprite)
{
	if (m_backgroundSprite!=BackgroundSprite)
	{
		CC_SAFE_RETAIN(BackgroundSprite);
		CC_SAFE_RELEASE(m_backgroundSprite);
		m_backgroundSprite = BackgroundSprite;
	}
}

CCScale9Sprite *SIX_Slider::getBackgroundSprite()
{
	return m_backgroundSprite;
}