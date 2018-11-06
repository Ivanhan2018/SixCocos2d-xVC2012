#include "SIX_ScrollBar.h"

SIX_ScrollBar::SIX_ScrollBar()
{
	m_BtnLT = m_BtnRB = 0;
	m_Slider = 0;
	m_bHorizontal = true;
	m_fScrollStep = 10.0f;
}

SIX_ScrollBar::~SIX_ScrollBar()
{
}

SIX_ScrollBar* SIX_ScrollBar::create(
		CCSpriteFrame *bgFrame,CCRect bgFileRect,CCSize bgSize,
		CCSpriteFrame *progressFrame,CCRect progressRect,
		CCSpriteFrame *thumbFrame,CCRect thumbRect,
		CCSpriteFrame *thumbSelectFrame,CCRect thumbSelectRect,
		CCSpriteFrame *btnLTFrame,CCRect btnLTRect,
		CCSpriteFrame *btnRBFrame,CCRect btnRBRect,
		CCSize btnSize,
		bool bHorizontal)
{
	if (!bgFrame || !progressFrame || !thumbFrame /*|| !btnLTFile || !btnRBFile*/)
		return 0;

	CCScale9Sprite *backgroundSprite = 0;
	if (bgFileRect.equals(CCRectZero))
		backgroundSprite = CCScale9Sprite::createWithSpriteFrame(bgFrame);
	else
		backgroundSprite = CCScale9Sprite::createWithSpriteFrame(bgFrame,bgFileRect);

	CCSprite *progressSprite = CCSprite::createWithSpriteFrame(progressFrame);
	if (!progressRect.equals(CCRectZero))
		progressSprite->setTextureRect(progressRect);

	CCScale9Sprite *thumbSprite = CCScale9Sprite::createWithSpriteFrame(thumbFrame);
	//if (!thumbRect.equals(CCRectZero))
	//	thumbSprite->setTextureRect(thumbRect);

	CCScale9Sprite *thumbSelectSprite = 0;
	if (thumbSelectFrame)
	{
		thumbSelectSprite = CCScale9Sprite::createWithSpriteFrame(thumbSelectFrame);
		//if (!thumbRect.equals(CCRectZero))
		//	thumbSprite->setTextureRect(thumbRect);
	}

	CCScale9Sprite *btnLT = 0;
	if (btnLTFrame)
	{
		if (btnLTRect.equals(CCRectZero))
			btnLT = CCScale9Sprite::createWithSpriteFrame(btnLTFrame);
		else
			btnLT = CCScale9Sprite::createWithSpriteFrame(btnLTFrame,btnLTRect);
	}

	CCScale9Sprite *btnRB = 0;
	if (btnRBFrame)
	{
		if (btnRBRect.equals(CCRectZero))
			btnRB = CCScale9Sprite::createWithSpriteFrame(btnRBFrame);
		else
			btnRB = CCScale9Sprite::createWithSpriteFrame(btnRBFrame,btnRBRect);
	}

	return SIX_ScrollBar::create(backgroundSprite,bgSize,progressSprite,thumbSprite,thumbSelectSprite,btnLT,btnRB,btnSize,bHorizontal);
}

SIX_ScrollBar* SIX_ScrollBar::create(
		const char *bgFile,CCRect bgFileRect,CCSize bgSize,
		const char *progressFile,CCRect progressFileRect,
		const char *thumbFile,CCRect thumbFileRect,
		const char *thumbSelectFile,CCRect thumbSelectFileRect,
		const char *btnLTFile,CCRect btnLTRect,
		const char *btnRBFile,CCRect btnRBRect,
		CCSize btnSize,
		bool bHorizontal)
{
	if (!bgFile || !progressFile || !thumbFile /*|| !btnLTFile || !btnRBFile*/)
		return 0;

	CCScale9Sprite *backgroundSprite = 0;
	if (bgFileRect.equals(CCRectZero))
		backgroundSprite = CCScale9Sprite::create(bgFile);
	else
		backgroundSprite = CCScale9Sprite::create(bgFile,bgFileRect);

	CCSprite *progressSprite = 0;
	if (progressFileRect.equals(CCRectZero))
		progressSprite = CCSprite::create(progressFile);
	else
		progressSprite = CCSprite::create(progressFile,progressFileRect);

	CCScale9Sprite *thumbSprite = 0;
	if (thumbFileRect.equals(CCRectZero))
		thumbSprite = CCScale9Sprite::create(thumbFile);
	else
		thumbSprite = CCScale9Sprite::create(thumbFile,thumbFileRect);

	CCScale9Sprite *thumbSelectSprite = 0;
	if (thumbSelectFile)
	{
		if (thumbSelectFileRect.equals(CCRectZero))
			thumbSelectSprite = CCScale9Sprite::create(thumbSelectFile);
		else
			thumbSelectSprite = CCScale9Sprite::create(thumbSelectFile,thumbSelectFileRect);	
	}

	CCScale9Sprite *btnLT = 0;
	if (btnLTFile)
	{
		if (btnLTRect.equals(CCRectZero))
			btnLT = CCScale9Sprite::create(btnLTFile);
		else
			btnLT = CCScale9Sprite::create(btnLTFile,btnLTRect);
	}

	CCScale9Sprite *btnRB = 0;
	if (btnRBFile)
	{
		if (btnRBRect.equals(CCRectZero))
			btnRB = CCScale9Sprite::create(btnRBFile);
		else
			btnRB = CCScale9Sprite::create(btnRBFile,btnRBRect);
	}

	return SIX_ScrollBar::create(backgroundSprite,bgSize,progressSprite,thumbSprite,thumbSelectSprite,btnLT,btnRB,btnSize,bHorizontal);
}

SIX_ScrollBar* SIX_ScrollBar::create(CCScale9Sprite *backgroundSprite,CCSize bgSize,CCSprite *progressSprite,CCScale9Sprite* thumbSprite,CCScale9Sprite *thumbSelectSprite,CCScale9Sprite *btnLT,CCScale9Sprite *btnRB,CCSize btnSize,bool bHorizontal)
{
	if (!backgroundSprite || !progressSprite || !thumbSprite /*|| !btnLT || !btnRB*/)
		return 0;
	SIX_ScrollBar *pRet = new SIX_ScrollBar();
	pRet->setHorizontal(bHorizontal);
	pRet->initWithSprites(backgroundSprite,bgSize,progressSprite,thumbSprite,thumbSelectSprite,btnLT,btnRB,btnSize);
	pRet->autorelease();
	return pRet;
}

bool SIX_ScrollBar::initWithSprites(CCScale9Sprite * backgroundSprite,CCSize bgSize,CCSprite *progressSprite,CCScale9Sprite* thumbSprite,CCScale9Sprite *thumbSelectSprite,CCScale9Sprite *btnLT,CCScale9Sprite *btnRB,CCSize btnSize)
{
	if (CCControl::init())
	{
		CCAssert(backgroundSprite,"backgroundSprite.Nil!");
		CCAssert(progressSprite,"progressSprite.Nil!");
		CCAssert(thumbSprite,"thumbSprite.Nil!");
		//CCAssert(btnLT,"btnLT.Nil!");
		//CCAssert(btnRB,"btnRB.Nil!");

		ignoreAnchorPointForPosition(false);
		setTouchEnabled(true);

		m_Slider = SIX_Slider::create(backgroundSprite,bgSize,progressSprite,thumbSprite,thumbSelectSprite);

		if (btnLT)
			m_BtnLT = CCControlButton::create(btnLT);
		if (btnRB)
			m_BtnRB = CCControlButton::create(btnRB);

		// save
		this->setSlider(m_Slider);
		this->setBtnLT(m_BtnLT);
		this->setBtnRB(m_BtnRB);

		// rescale pos and size
		// Cool.Cat
		if (this->getBtnLT())
		{
			this->getBtnLT()->setAnchorPoint(ccp(0,0));
			this->getBtnLT()->setPositionX(0.0);
			this->getBtnLT()->setPositionY(0.0);
			this->getBtnLT()->setPreferredSize(btnSize);
			addChild(this->getBtnLT());
		}

		// bk stretching
		this->getSlider()->setAnchorPoint(ccp(0,0));
		if (this->getBtnLT())
			this->getSlider()->setPositionX(this->getBtnLT()->getContentSize().width);
		else
			this->getSlider()->setPositionX(0.0);
		this->getSlider()->setPositionY(0.0);
		addChild(this->getSlider());

		if (this->getBtnRB())
		{
			this->getBtnRB()->setAnchorPoint(ccp(0,0));
			this->getBtnRB()->setPositionX(this->getSlider()->getPositionX() + this->getSlider()->getContentSize().width);
			this->getBtnRB()->setPositionY(0.0);
			this->getBtnRB()->setPreferredSize(btnSize);
			addChild(this->getBtnRB());
		}

		//// 取背景与滑块联合区域作为节点区域
		//CCRect maxRect = CCControlUtils::CCRectUnion(this->getBtnLT()->boundingBox(),this->getBackground()->boundingBox());
		//maxRect = CCControlUtils::CCRectUnion(maxRect,this->getBtnRB()->boundingBox());
		//maxRect = CCControlUtils::CCRectUnion(maxRect,this->getThumb()->boundingBox());
		//setContentSize(CCSizeMake(maxRect.size.width,maxRect.size.height));

		// 默认都按横向来先~
		float width = this->getSlider()->getContentSize().width;
		if (this->getBtnLT())
			width += this->getBtnLT()->getContentSize().width;
		if (this->getBtnRB())
			width += this->getBtnRB()->getContentSize().width;

		float height =	this->getSlider()->getContentSize().height;

		setContentSize(CCSize(width,height));

		if (!this->getHorizontal())
		{
			// 默认是横向的，所以要旋转90度先~
			this->setRotation(90.0);
		}

		this->setMinimumValue(0.0);
		this->setMaximumValue(100.0);

		this->setValue(this->getMinimumValue());

		// 设置回调
		this->getSlider()->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_ScrollBar::ScrollBarChanged),CCControlEventValueChanged);
		return true;
	}

	return false;
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
	m_Slider->setValue(value);
}

float SIX_ScrollBar::getValue()
{
	return m_Slider->getValue();
}

void SIX_ScrollBar::setMinimumValue(float minimumValue)
{
	m_Slider->setMinimumValue(minimumValue);
}

float SIX_ScrollBar::getMinimumValue()
{
	return m_Slider->getMinimumValue();
}

void SIX_ScrollBar::setMaximumValue(float maximumValue)
{
	m_Slider->setMaximumValue(maximumValue);
}

float SIX_ScrollBar::getMaximumValue()
{
	return m_Slider->getMaximumValue();
}

void SIX_ScrollBar::setMinimumAllowedValue(float minimumAllowedValue)
{
	m_Slider->setMinimumAllowedValue(minimumAllowedValue);
}

float SIX_ScrollBar::getMinimumAllowedValue()
{
	return m_Slider->getMinimumAllowedValue();
}

void SIX_ScrollBar::setMaximumAllowedValue(float maximumAllowedValue)
{
	m_Slider->setMaximumAllowedValue(maximumAllowedValue);
}

float SIX_ScrollBar::getMaximumAllowedValue()
{
	return m_Slider->getMaximumAllowedValue();
}

// ------------------------------------------------
void SIX_ScrollBar::setSlider(SIX_Slider *slider)
{
	if (m_Slider != slider)
	{
		CC_SAFE_RETAIN(slider);
		CC_SAFE_RELEASE(m_Slider);
		m_Slider = slider;
	}
}

SIX_Slider *SIX_ScrollBar::getSlider(void) const 
{ 
	return m_Slider;
}

void SIX_ScrollBar::setBtnLT(CCControlButton *btnLT)
{
	if (m_BtnLT != btnLT)
	{
		CC_SAFE_RETAIN(btnLT);
		CC_SAFE_RELEASE(m_BtnLT);
		m_BtnLT = btnLT;
	}
}

CCControlButton *SIX_ScrollBar::getBtnLT(void) const 
{ 
	return m_BtnLT;
}

void SIX_ScrollBar::setBtnRB(CCControlButton *btnRB)
{
	if (m_BtnRB != btnRB)
	{
		CC_SAFE_RETAIN(btnRB);
		CC_SAFE_RELEASE(m_BtnRB);
		m_BtnRB = btnRB;
	}
}

CCControlButton *SIX_ScrollBar::getBtnRB(void) const 
{ 
	return m_BtnRB;
}

bool SIX_ScrollBar::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if (!isEnabled())
		return false;

	if (!this->isTouchInside(pTouch))
		return false;

	// 如果在button区域内
	if (m_BtnLT && m_BtnLT->isTouchInside(pTouch) && m_BtnLT->isEnabled())
	{
		float value = m_Slider->getValue() - m_fScrollStep;
		if (value<m_Slider->getMinimumAllowedValue())
			value = m_Slider->getMinimumAllowedValue();
		m_Slider->setValue(value);
		return true;
	}
	else if (m_BtnRB && m_BtnRB->isTouchInside(pTouch) && m_BtnRB->isEnabled())
	{
		float value = m_Slider->getValue() + m_fScrollStep;
		if (value>m_Slider->getMaximumAllowedValue())
			value = m_Slider->getMaximumAllowedValue();
		m_Slider->setValue(value);
		return true;
	}

	// 如果在slider区域内
	if (m_Slider->isTouchInside(pTouch) && m_Slider->isEnabled())
	{
		CCPoint location = m_Slider->locationFromTouch(pTouch);
		m_Slider->sliderBegan(location);
		return true;
	}
	
	return false;
}

void SIX_ScrollBar::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isEnabled())
		return;

	if (!this->isTouchInside(pTouch))
		return;

	// 如果在button区域内
	if (m_BtnLT && m_BtnLT->isTouchInside(pTouch) && m_BtnLT->isEnabled())
	{
		float value = m_Slider->getValue() - m_fScrollStep;
		if (value<m_Slider->getMinimumAllowedValue())
			value = m_Slider->getMinimumAllowedValue();
		m_Slider->setValue(value);
		return;
	}
	else if (m_BtnRB && m_BtnRB->isTouchInside(pTouch) && m_BtnRB->isEnabled())
	{
		float value = m_Slider->getValue() + m_fScrollStep;
		if (value>m_Slider->getMaximumAllowedValue())
			value = m_Slider->getMaximumAllowedValue();
		m_Slider->setValue(value);
		return;
	}

	// 有可能拖动时鼠标不一定在滑块区域内，so应该只要down在滑块区域内
	// 就可以直接移动，去掉下面的区域判断，这样比较人性化，具体效果参
	// 考QQ2013滑块~
	// Cool.Cat
	//if (m_Slider->isTouchInside(pTouch))
	//{
		CCPoint location = m_Slider->locationFromTouch(pTouch);
		m_Slider->sliderMoved(location);
	//}
}

void SIX_ScrollBar::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isEnabled())
		return;

	if (!this->isTouchInside(pTouch))
		return;

	m_Slider->sliderEnded(CCPointZero);
}

// 滚动条回调
void SIX_ScrollBar::ScrollBarChanged(CCObject *pSender,CCControlEvent controlEvent)
{
	this->sendActionsForControlEvents(CCControlEventValueChanged);
}