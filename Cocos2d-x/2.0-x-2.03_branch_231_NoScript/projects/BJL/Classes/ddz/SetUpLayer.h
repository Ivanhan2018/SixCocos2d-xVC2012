//  [4/3/2014 xieyi]
#ifndef __SETUPLAYER__
#define __SETUPLAYER__
#include "cocos2d.h"
#include "DDZRes.h"
#include "SoundControl.h"
#include <limits>
USING_NS_CC;

class SetUpLayer : public CCLayer
{
public:
	SetUpLayer();
	~SetUpLayer();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(SetUpLayer);
private:
	bool m_voiceIsOpen;		//声音是否打开
	bool m_faceIsOpen;		//表情功能是否打开
	float m_musicVol;//背景音量
	float m_soundEffVol;//音效音量
	CCSprite * m_voice;		//声音状态
	CCSprite * m_voiceOnOff;	//声音开关按钮图片
	CCSprite * m_face;		//表情状态
	CCSprite * m_faceOnOff;	//表情开关按钮图片
	CCSprite * m_bgSprite;	//背景
	CCPoint m_bgPoint;		//背景位置
	void setVoiceState(bool voiceState);	//设置声音状态
	void setFaceState(bool faceState);		//设置表情开关状态
	CCSpriteBatchNode * m_batchNode;
	CCProgressTimer * m_soundEffTimer;	//音效条
	CCProgressTimer * m_musicTimer;		//背景音量条
	CCSprite * m_soundEffTimerBar;	//音效条上的按钮
	bool m_soundBarIsSelected;		//音效条按钮是否按下
	CCSprite * m_musicTimerBar;		//背景声音条上的按钮
	bool m_musicBarIsSelected;		//背景音量条是否按下
};

#endif