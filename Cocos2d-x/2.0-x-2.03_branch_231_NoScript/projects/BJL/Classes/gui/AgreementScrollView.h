#ifndef __Game__AgreementScrollView__
#define __Game__AgreementScrollView__
#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
class AgreementScrollView : public cocos2d::CCLayer
{

public:
	AgreementScrollView();
	~AgreementScrollView();
	virtual bool init();
	static cocos2d::CCScene* scene();
	virtual void visit();
	CREATE_FUNC(AgreementScrollView);
public:
	void onEnter();
	void onExit();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
	CCLabelTTF *str1;
	float m_start;
	float m_end;

};
#endif  //__Game__AgreementScrollView__