#ifndef __Game__HelpScrollView__
#define __Game__HelpScrollView__
#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
class HelpScrollView : public cocos2d::CCLayer
{

public:
	HelpScrollView();
	~HelpScrollView();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CCRect addString(CCPoint pt,const char* buff,CCSize size);

	CREATE_FUNC(HelpScrollView);
public:
	void onEnter();
	void onExit();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
	CCNode *m_node;
	float m_start;
	float m_end;
	CCPoint m_endPos;

};
#endif  //__Game__HelpScrollView__