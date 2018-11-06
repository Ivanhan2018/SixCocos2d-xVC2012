#include "SIX_ScrollBar.h"

SIX_ScrollBar::SIX_ScrollBar()
{
	m_BtnLT = m_BtnRB = 0;
	m_Background = m_Thumb = 0;
	m_bHorizontal = true;
	m_ThumbRect = CCRectZero;

	m_value = m_minimumValue = m_maximumValue = m_minimumAllowedValue = m_maximumAllowedValue = 0.0;
}

SIX_ScrollBar::~SIX_ScrollBar()
{
}

SIX_ScrollBar* SIX_ScrollBar::create(
	const char *backgroundFile,CCRect backgroundRect,CCRect backgroundDstRect,
	const char *btnLTFile,CCRect btnLTRect,
	const char *btnRBFile,CCRect btnRBRect,
	const char *thumbFile,CCRect thumbRect,
	bool bHorizontal)
{
	if (!backgroundFile || !btnLTFile || !btnRBFile || !thumbFile)
		return 0;

	CCScale9Sprite *background = 0;
	if (backgroundRect.equals(CCRectZero))
		background = CCScale9Sprite::create(backgroundFile);
	else
		background = CCScale9Sprite::create(backgroundFile,backgroundRect);

	CCSprite *btnLT = 0;
	if (btnLTRect.equals(CCRectZero))
		btnLT = CCSprite::create(btnLTFile);
	else
		btnLT = CCSprite::create(btnLTFile,btnLTRect);

	CCSprite *btnRB = 0;
	if (btnRBRect.equals(CCRectZero))
		btnRB = CCSprite::create(btnRBFile);
	else
		btnRB = CCSprite::create(btnRBFile,btnRBRect);

	CCScale9Sprite *thumb = 0;
	if (thumbRect.equals(CCRectZero))
		thumb = CCScale9Sprite::create(thumbFile);
	else
		thumb = CCScale9Sprite::create(thumbFile,thumbRect);

	return SIX_ScrollBar::create(background,backgroundDstRect,btnLT,btnRB,thumb,bHorizontal);
}

SIX_ScrollBar* SIX_ScrollBar::create(CCScale9Sprite *background,CCRect backgroundDstRect,CCSprite *btnLT,CCSprite *btnRB,CCScale9Sprite* thumb,bool bHorizontal)
{
	if (!background || !btnLT || !btnRB || !thumb)
		return 0;
	SIX_ScrollBar *pRet = new SIX_ScrollBar();
	pRet->setHorizontal(bHorizontal);
	pRet->initWithSprites(background,backgroundDstRect,btnLT,btnRB,thumb);
	pRet->autorelease();
	return pRet;
}

bool SIX_ScrollBar::initWithSprites(CCScale9Sprite * background,CCRect backgroundDstRect,CCSprite *btnLT, CCSprite *btnRB,CCScale9Sprite* thumb)
{
	if (CCControl::init())
	{
		CCAssert(background,"Background.Nil!");
		CCAssert(btnLT,"btnLT.Nil!");
		CCAssert(btnRB,"btnRB.Nil!");
		CCAssert(thumb,"Thumb.Nil!");

		ignoreAnchorPointForPosition(false);
		setTouchEnabled(true);

		// save
		this->setBackground(background);
		this->setBtnLT(btnLT);
		this->setBtnRB(btnRB);
		this->setThumb(thumb);

		// rescale pos and size
		// Cool.Cat
		this->getBtnLT()->setAnchorPoint(ccp(0,0));
		this->getBtnLT()->setPositionX(0.0);
		this->getBtnLT()->setPositionY(0.0);
		addChild(this->getBtnLT());

		// bk stretching
		this->getBackground()->setAnchorPoint(ccp(0,0));
		this->getBackground()->setPositionX(backgroundDstRect.origin.x);
		this->getBackground()->setPositionY(backgroundDstRect.origin.y);
		this->getBackground()->setPreferredSize(backgroundDstRect.size);
		addChild(this->getBackground());

		this->getBtnRB()->setAnchorPoint(ccp(0,0));
		this->getBtnRB()->setPositionX(this->getBackground()->getPositionX() + this->getBackground()->getContentSize().width);
		this->getBtnRB()->setPositionY(0.0);
		addChild(this->getBtnRB());

		// thumb
		this->getThumb()->setAnchorPoint(ccp(0,0));
		addChild(this->getThumb());

		//// 取背景与滑块联合区域作为节点区域
		//CCRect maxRect = CCControlUtils::CCRectUnion(this->getBtnLT()->boundingBox(),this->getBackground()->boundingBox());
		//maxRect = CCControlUtils::CCRectUnion(maxRect,this->getBtnRB()->boundingBox());
		//maxRect = CCControlUtils::CCRectUnion(maxRect,this->getThumb()->boundingBox());
		//setContentSize(CCSizeMake(maxRect.size.width,maxRect.size.height));

		// 默认都按横向来先~
		float width =	this->getBtnLT()->getContentSize().width		+
						this->getBackground()->getContentSize().width	+
						this->getBtnRB()->getContentSize().width;
		float height =	this->getBackground()->getContentSize().height;

		setContentSize(CCSize(width,height));

		if (!this->getHorizontal())
		{
			// 默认是横向的，所以要旋转90度先~
			this->setRotation(90.0);
		}

		this->setMinimumValue(0.0);
		this->setMaximumValue(100.0);

		this->setValue(this->getMinimumValue());
		return true;
	}

	return false;
}

bool SIX_ScrollBar::isTouchInside(CCTouch * touch)
{
	CCPoint touchLocation = touch->getLocation();
	// 转成节点内部坐标
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);

	CCRect rect = this->boundingBox();
	rect.size.width += m_Thumb->getContentSize().width;
	rect.origin.x -= m_Thumb->getContentSize().width / 2;

	return rect.containsPoint(touchLocation);
}

CCPoint SIX_ScrollBar::locationFromTouch(CCTouch* touch)
{
	CCPoint touchLocation   = touch->getLocation();
	// 转成节点内部坐标
	touchLocation           = this->convertToNodeSpace(touchLocation);

	if (touchLocation.x < 0)
		touchLocation.x = 0;
	else if (touchLocation.x > m_Background->getContentSize().width)
		touchLocation.x = m_Background->getContentSize().width;

	return touchLocation;
}

// ------------------------------------------------
bool SIX_ScrollBar::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if (!isTouchInside(pTouch) || !isEnabled())
		return false;

	CCPoint location = locationFromTouch(pTouch);
	sliderBegan(location);
	return true;
}

void SIX_ScrollBar::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchInside(pTouch) || !isEnabled())
		return;

	CCPoint location = locationFromTouch(pTouch);
	sliderMoved(location);
}

void SIX_ScrollBar::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchInside(pTouch) || !isEnabled())
		return;

	sliderEnded(CCPointZero);
}

// ------------------------------------------------
void SIX_ScrollBar::needsLayout()
{
	if (!this->getBackground() || !this->getBtnLT() || !this->getBtnRB() || !this->getThumb())
		return;

	// Update thumb position for new value
	float percent = (m_value - m_minimumValue) / (m_maximumValue - m_minimumValue);

	CCPoint pos = this->getThumb()->getPosition();
	pos.x = percent * this->getBackground()->getContentSize().width;
	this->getThumb()->setPosition(pos);

	//// Stretches content proportional to newLevel
	//CCRect textureRect          = m_progressSprite->getTextureRect();
	//textureRect                 = CCRectMake(textureRect.origin.x, textureRect.origin.y, pos.x, textureRect.size.height);
	//m_progressSprite->setTextureRect(textureRect, m_progressSprite->isTextureRectRotated(), textureRect.size);
}

void SIX_ScrollBar::sliderBegan(CCPoint location)
{
    this->setSelected(true);
    this->getThumb()->setColor(ccGRAY);
    setValue(valueForLocation(location));
}

void SIX_ScrollBar::sliderMoved(CCPoint location)
{
    setValue(valueForLocation(location));
}

void SIX_ScrollBar::sliderEnded(CCPoint location)
{
    if (this->isSelected())
    {
		setValue(valueForLocation(this->getThumb()->getPosition()));
    }
    this->getThumb()->setColor(ccWHITE);
    this->setSelected(false);
}

float SIX_ScrollBar::valueForLocation(CCPoint location)
{
	float percent = location.x/ this->getBackground()->getContentSize().width;
    return MAX(MIN(m_minimumValue + percent * (m_maximumValue - m_minimumValue), m_maximumAllowedValue), m_minimumAllowedValue);
}

// ------------------------------------------------
void SIX_ScrollBar::setHorizontal(bool bHorizontal)
{
	m_bHorizontal = bHorizontal;
}

bool SIX_ScrollBar::getHorizontal()
{
	return m_bHorizontal;
}

void SIX_ScrollBar::setValue(float value)
{
	// set new value with sentinel
	if (value<m_minimumValue)
		value = m_minimumValue;

	if (value>m_maximumValue) 
		value = m_maximumValue;

	m_value = value;

	this->needsLayout();

	this->sendActionsForControlEvents(CCControlEventValueChanged);
}

float SIX_ScrollBar::getValue()
{
	return m_value;
}

void SIX_ScrollBar::setMinimumValue(float minimumValue)
{
	m_minimumValue=minimumValue;
	m_minimumAllowedValue = minimumValue;
	if (m_minimumValue>=m_maximumValue)
		m_maximumValue = m_minimumValue + 1.0;
	setValue(m_value);
}

float SIX_ScrollBar::getMinimumValue()
{
	return m_minimumValue;
}

void SIX_ScrollBar::setMaximumValue(float maximumValue)
{
	m_maximumValue=maximumValue;
	m_maximumAllowedValue = maximumValue;
	if (m_maximumValue<=m_minimumValue)
		m_minimumValue = m_maximumValue - 1.0;
	setValue(m_value);
}

float SIX_ScrollBar::getMaximumValue()
{
	return m_maximumValue;
}

void SIX_ScrollBar::setMinimumAllowedValue(float minimumAllowedValue)
{
	m_minimumAllowedValue = minimumAllowedValue;
}

float SIX_ScrollBar::getMinimumAllowedValue()
{
	return m_minimumAllowedValue;
}

void SIX_ScrollBar::setMaximumAllowedValue(float maximumAllowedValue)
{
	m_maximumAllowedValue = maximumAllowedValue;
}

float SIX_ScrollBar::getMaximumAllowedValue()
{
	return m_maximumAllowedValue;
}

void SIX_ScrollBar::setThumbRect(CCRect rc)
{
	m_ThumbRect = rc;
}

CCRect SIX_ScrollBar::getThumbRect()
{
	return m_ThumbRect;
}

// ------------------------------------------------
void SIX_ScrollBar::setBackground(CCScale9Sprite *background)
{
	if (m_Background != background)
	{
		CC_SAFE_RETAIN(background);
		CC_SAFE_RELEASE(m_Background);
		m_Background = background;
	}
}

CCScale9Sprite *SIX_ScrollBar::getBackground(void) const 
{ 
	return m_Background;
}

void SIX_ScrollBar::setBtnLT(CCSprite *btnLT)
{
	if (m_BtnLT != btnLT)
	{
		CC_SAFE_RETAIN(btnLT);
		CC_SAFE_RELEASE(m_BtnLT);
		m_BtnLT = btnLT;
	}
}

CCSprite *SIX_ScrollBar::getBtnLT(void) const 
{ 
	return m_BtnLT;
}

void SIX_ScrollBar::setBtnRB(CCSprite *btnRB)
{
	if (m_BtnRB != btnRB)
	{
		CC_SAFE_RETAIN(btnRB);
		CC_SAFE_RELEASE(m_BtnRB);
		m_BtnRB = btnRB;
	}
}

CCSprite *SIX_ScrollBar::getBtnRB(void) const 
{ 
	return m_BtnRB;
}

void SIX_ScrollBar::setThumb(CCScale9Sprite *thumb)
{
	if (m_Thumb != thumb)
	{
		CC_SAFE_RETAIN(thumb);
		CC_SAFE_RELEASE(m_Thumb);
		m_Thumb = thumb;
	}
}

CCScale9Sprite *SIX_ScrollBar::getThumb(void) const 
{ 
	return m_Thumb;
}