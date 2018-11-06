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
	bool m_voiceIsOpen;		//�����Ƿ��
	bool m_faceIsOpen;		//���鹦���Ƿ��
	float m_musicVol;//��������
	float m_soundEffVol;//��Ч����
	CCSprite * m_voice;		//����״̬
	CCSprite * m_voiceOnOff;	//�������ذ�ťͼƬ
	CCSprite * m_face;		//����״̬
	CCSprite * m_faceOnOff;	//���鿪�ذ�ťͼƬ
	CCSprite * m_bgSprite;	//����
	CCPoint m_bgPoint;		//����λ��
	void setVoiceState(bool voiceState);	//��������״̬
	void setFaceState(bool faceState);		//���ñ��鿪��״̬
	CCSpriteBatchNode * m_batchNode;
	CCProgressTimer * m_soundEffTimer;	//��Ч��
	CCProgressTimer * m_musicTimer;		//����������
	CCSprite * m_soundEffTimerBar;	//��Ч���ϵİ�ť
	bool m_soundBarIsSelected;		//��Ч����ť�Ƿ���
	CCSprite * m_musicTimerBar;		//�����������ϵİ�ť
	bool m_musicBarIsSelected;		//�����������Ƿ���
};

#endif