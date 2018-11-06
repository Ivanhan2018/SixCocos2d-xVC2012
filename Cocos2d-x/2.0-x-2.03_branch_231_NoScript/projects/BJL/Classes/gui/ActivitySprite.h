//
//  SelectButton.h
//  Game
//
//  Created by ?? ???? on 13-6-7.
//
//

#ifndef __Game__ActivitySprite__
#define __Game__ActivitySprite__

#include "cocos2d.h"
#include "common/CocosUnits.h"
USING_NS_CC;

class ActivitySprite : public cocos2d::CCSprite,public cocos2d::CCTouchDelegate
{
public:
    static ActivitySprite * ActivitySpriteWith(int type);
    bool initActivitySprite(int type);
    ActivitySprite();
    ~ActivitySprite();
    void onEnter();
    void onExit();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void setSelect(bool select);
private:
	int m_nType;
};

#endif /* defined(__Game__SelectButton__) */
