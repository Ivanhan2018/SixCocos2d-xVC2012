#include "UINumber.h"


using namespace cocos2d;

UINumber::~UINumber(){
	CC_SAFE_RELEASE_NULL(m_texture);
}

UINumber* UINumber::numberWithStyle(NUM_STYLE style){
	UINumber* n = new UINumber;
	if(n && n->initWithStyle(style)){
		n->autorelease();
		return n;
	}
	CC_SAFE_DELETE(n);
	return NULL;
}

bool UINumber::init(){
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::init());

		m_texture = NULL;
		m_style = NUM_STYLE::NumStyleNormal;
		m_num = 0;
		m_nPosCur = 0;
		m_nPosEnd = 0;

		this->setup();

		bRet = true;
	} while (0);
	return bRet;
}

bool UINumber::initWithStyle(NUM_STYLE style){
	bool bRet = false;
	do 
	{
		init();
		m_style = style;

		bRet = true;
	} while (0);
	return bRet;
}

void UINumber::setup(){
	m_texture = CCTextureCache::sharedTextureCache()->addImage("number.png");
	m_texture->retain();
	CCSpriteFrame* frame = CCSpriteFrame::frameWithTexture(m_texture, CCRectMake(0, 0, NUM_WIDTH, NUM_HEIGHT));
	this->setDisplayFrame(frame);
}

void UINumber::setNumber(int num){
	m_nPosCur = NUM_HEIGHT * m_num;
	m_nPosEnd = NUM_HEIGHT * num;
	if(NUM_STYLE::NumStyleNormal == m_style){
		m_nMoveLen = 4;
	}else if(NUM_STYLE::NumStyleSameTime == m_style){
		m_nMoveLen = (m_nPosEnd-m_nPosCur)/20;
	}
	if(m_num > num){
		this->schedule(schedule_selector(UINumber::onRollUp), 0.03f);
	}else{
	  this->schedule(schedule_selector(UINumber::onRollDown), 0.03f);
	}
	m_num = num;
}

void UINumber::onRollDown(float dt){
	m_nPosCur += m_nMoveLen;
	if(m_nPosCur >= m_nPosEnd){
		m_nPosCur = m_nPosEnd;
	//	this->unschedule(schedule_selector(UINumber::onRollDown));
	}
	CCSpriteFrame* frame = CCSpriteFrame::frameWithTexture(m_texture, CCRectMake(0, m_nPosCur, NUM_WIDTH, NUM_HEIGHT));
	this->setDisplayFrame(frame);
}

void UINumber::onRollUp(float dt){
	m_nPosCur -= m_nMoveLen;
	if(m_nPosCur <= m_nPosEnd){
		m_nPosCur = m_nPosEnd;
		this->unschedule(schedule_selector(UINumber::onRollUp));
	}
	CCSpriteFrame* frame = CCSpriteFrame::frameWithTexture(m_texture, CCRectMake(0, m_nPosCur, NUM_WIDTH, NUM_HEIGHT));
	this->setDisplayFrame(frame);
}

