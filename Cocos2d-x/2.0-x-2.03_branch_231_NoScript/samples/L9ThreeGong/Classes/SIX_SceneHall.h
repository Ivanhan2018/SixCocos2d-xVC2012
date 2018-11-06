/***********************************************
Name��SIX_SceneHall
Desc����������
Auth��Cool.Cat@2013-09-24
***********************************************/
#pragma once
#include <SIX_UIScene.h>
#include <SIX_Typedef.h>
#include <SIX_ExpandLayer.h>
#include "SIX_PopWndTask.h"
#include "SIX_PopWndActivity.h"
#include "SIX_PopWndTopList.h"
#include "SIX_PopWndSetting.h"
#include "SIX_PopWndAward.h"
#include "SIX_PopWndShop.h"
#include "SIX_PopWndRoomList.h"
#include "SIX_PopWndPersonalInfomation.h"

enum {
	// ����
	BTN_RANK			=	20,
	// ����
	BTN_HELP		    =	21,
	// ����
	BTN_SETTING		    =	22,
	// �׹����
	BTN_GIFT		    =	23,
	// ������Ϸ
	BTN_QUICKSTART		=	30,
	// ��Ϸ����
	BTN_HALL			=	31,
	// ͨ�Ⱦ���
	BTN_ARENA			=	32,
	// ��ȡ��Ʒ
	BTN_REWARD	        =	33,
	// ���½��û���Ϣ����
	BTN_USER            =   40,
	// ͷ��
	SPRITE_FACELOGO		=	41,
	// �ǳ�
	TTF_NICKNAME		=	42,
	// �ȼ�ico
	SPRITE_LEVEL		=	43,
	// �ȼ�ttf
	TTF_LEVEL			=	44,
	// �����
	PROGRESS_EXP		=	45,
	// ��ó���
	BTN_GETCHIP	        =	50,
	// ����ttf
	TTF_CHIP			=	51,
	// �
	BTN_ACTIVITY	    =	52,
	// ����
	BTN_TASK	        =	53,
	// ����ȡ����Sprite
	SPR_REWARD			=	54,
	// ����ȡ����ttf
	TTF_REWARD			=	55,
};

class SIX_SceneHall:public SIX_UIScene
{
public:
	SIX_SceneHall()
	{
	}

	virtual ~SIX_SceneHall();
public:
	static SIX_SceneHall* scene();
	virtual bool init();
	void update(float dt);

	SIX_PopWndTask * GetPopWndTask() { return m_pWndTask; }
	SIX_PopWndActivity * GetPopWndActivity() { return m_pWndActivity; }
	SIX_PopWndTopList * GetPopWndTopList() { return m_pWndTopList; }
	SIX_PopWndSetting *GetPopWndSetting() { return m_pWndSetting; }
	SIX_PopWndAward * GetPopWndAward() { return m_pWndAward; }
	SIX_PopWndShop * GetPopWndShop() { return m_pWndShop; }
	SIX_PopWndRoomList *GetPopWndRoomList(){ return m_pWndRoomList; }
	SIX_PopWndPersonalInfomation *GetPopWndPersionalInformation(){ return m_pWndPersionalInformation; }

    // default implements are used to call script callback if exist
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType);

    virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
    virtual void onExit();
	// �رհ�ť �� �˳�����ʱ����
	// Cool.Cat
	virtual void onCloseExit();
	virtual void OnNotifyCloseWndClicked(CCObject *pObj);
#ifdef WIN32
	int OnAccelerometerKeyHook( UINT message,WPARAM wParam,LPARAM lParam );
#endif
private:
	void doEvents(CCObject* pSender, CCControlEvent event);
public:
	// ����ͷ��
	void setFaceLogo(long long llSysLogoID);
	// �����ǳ�
	void setNickName(const char*szNickName);
	// ���õȼ�
	void setLevel(int Lv);
	// ���ó���
	void setChip(TChip Chip);
	// ���ÿ���ȡ������ʾ
	void setReward(int);
private:
	SIX_PopWndTask		*m_pWndTask;
	SIX_PopWndActivity *m_pWndActivity;
	SIX_PopWndTopList *m_pWndTopList;
	SIX_PopWndSetting *m_pWndSetting;
	SIX_PopWndAward *m_pWndAward;
	SIX_PopWndShop *m_pWndShop;
	SIX_PopWndRoomList *m_pWndRoomList;
	SIX_PopWndPersonalInfomation *m_pWndPersionalInformation;
	CCLayerColor *pBackground;

	// ͷ��
	CCSprite *pSprFaceLogo;
	// �ǳ�
	CCLabelTTF *pTTFNickName;
	// �ȼ�ico
	CCSprite *pSprLv;
	// �ȼ�ttf
	CCLabelTTF *pTTFLv;
	// �����
	CCProgressTimer *pProgressExp;

	// ����ttf
	CCLabelTTF *pTTFChip;

	// ����ȡ����
	CCSprite *pSprReward;
	// ����ȡ����ttf
	CCLabelTTF *pTTFReward;
};