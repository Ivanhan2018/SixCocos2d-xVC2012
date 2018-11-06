//
//  RegistScene.h
//  Game
//
//  Created by 兰 天乐 on 13-6-7.
//
//

#ifndef __Game__RoomOption__
#define __Game__RoomOption__

#include "cocos2d.h"
#include "event/GBEvent.h"
USING_NS_CC;

class RoomOption : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(RoomOption);
    virtual bool init();
    
    RoomOption();
    ~RoomOption();

	void back(CCObject* obj);
	void changeAccount(CCObject* obj);
	void openSilentMode(CCObject* obj);
	void checkVesion(CCObject* obj);
	void onCheckVersion(CCObject* obj);
	void onEnter();
	void onExit();

	void toFreeLayer(CCObject* obj);

	virtual void keyBackClicked(void);					//手机返回按钮

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
    CCMenuItemSprite* m_pSilentItemSprite;
	bool m_bOpenSlientMode;

	CCSprite* m_pMusicControlSprite;
	CCSprite* m_pMusicControlBlackBack;
	CCProgressTimer* m_pMusicControlWhiteTimer;

	CCSprite* m_pSoundControlSprite;
	CCSprite* m_pSoundControlBlackBack;
	CCProgressTimer* m_pSoundControlWhiteTimer;

	int m_nChangeVoice;				//1为音乐，2为音效
};

#endif /* defined(__Game__RegistScene__) */
