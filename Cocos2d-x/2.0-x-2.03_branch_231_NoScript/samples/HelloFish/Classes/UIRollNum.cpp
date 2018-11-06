#include "UIRollNum.h"

using namespace cocos2d;

UIRollNum::~UIRollNum(){
	CC_SAFE_RELEASE_NULL(numArray);
}

UIRollNum* UIRollNum::getOne(){
	UIRollNum* one = new UIRollNum;
	if(one && one->init()){
		one->autorelease();
		return one;
	}
	CC_SAFE_DELETE(one);
	return NULL;
}

bool UIRollNum::init(){
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::init());

		m_nNumber = 0;
		m_maxCol = 6;
		numArray = CCArray::array();
		numArray->retain();
		zeroFill = true;
		style = NUM_STYLE::NumStyleNormal;
		this->clearEffect();

		bRet = true;
	} while (0);
	return bRet;
}

int UIRollNum::getNumber(){
	return m_nNumber;
}

void UIRollNum::setNumber(int num){
	if(m_nNumber != num){
		m_nNumber = num;
		this->rebuildEffect();
	}
}

void UIRollNum::rebuildEffect(){
	int i = 0;
	int num = m_nNumber;
	while(1){
		if(num <= 0){
			if(m_maxCol <= i && zeroFill){
				break;
			}
		}
		int showNum = num % 10;
		UINumber* pNumber = (UINumber*)numArray->objectAtIndex(i);
		pNumber->setNumber(showNum);
		i++;
		num = num / 10;
	}

}

void UIRollNum::clearEffect(){
	for(unsigned int i = 0; i < numArray->count(); i++){
		UINumber* pNumber = (UINumber*)numArray->objectAtIndex(i);
		this->removeChild(pNumber, true);
	}

	numArray->removeAllObjects();

	for(int i = 0; i < m_maxCol; i++){
		UINumber* pNumber = UINumber::numberWithStyle(style);
		numArray->addObject(pNumber);
		pNumber->setNumber(0);
		pNumber->setPosition(ccp(m_point.x - i * NUM_WIDTH, m_point.y));
		pNumber->setAnchorPoint(ccp(1.0f, 0.5f));
		this->addChild(pNumber, 100);
	}
}