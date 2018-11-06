/***********************************************
Name：SIX_SceneHall
Desc：大厅场景
Auth：Cool.Cat@2013-09-24
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
	// 排行
	BTN_RANK			=	20,
	// 帮助
	BTN_HELP		    =	21,
	// 设置
	BTN_SETTING		    =	22,
	// 首购礼包
	BTN_GIFT		    =	23,
	// 快速游戏
	BTN_QUICKSTART		=	30,
	// 游戏大厅
	BTN_HALL			=	31,
	// 通比竞技
	BTN_ARENA			=	32,
	// 领取奖品
	BTN_REWARD	        =	33,
	// 左下角用户信息区域
	BTN_USER            =   40,
	// 头像
	SPRITE_FACELOGO		=	41,
	// 昵称
	TTF_NICKNAME		=	42,
	// 等级ico
	SPRITE_LEVEL		=	43,
	// 等级ttf
	TTF_LEVEL			=	44,
	// 经验槽
	PROGRESS_EXP		=	45,
	// 获得筹码
	BTN_GETCHIP	        =	50,
	// 筹码ttf
	TTF_CHIP			=	51,
	// 活动
	BTN_ACTIVITY	    =	52,
	// 任务
	BTN_TASK	        =	53,
	// 可领取奖励Sprite
	SPR_REWARD			=	54,
	// 可领取奖励ttf
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
	// 关闭按钮 或 退出进程时触发
	// Cool.Cat
	virtual void onCloseExit();
	virtual void OnNotifyCloseWndClicked(CCObject *pObj);
#ifdef WIN32
	int OnAccelerometerKeyHook( UINT message,WPARAM wParam,LPARAM lParam );
#endif
private:
	void doEvents(CCObject* pSender, CCControlEvent event);
public:
	// 设置头像
	void setFaceLogo(long long llSysLogoID);
	// 设置昵称
	void setNickName(const char*szNickName);
	// 设置等级
	void setLevel(int Lv);
	// 设置筹码
	void setChip(TChip Chip);
	// 设置可领取奖励提示
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

	// 头像
	CCSprite *pSprFaceLogo;
	// 昵称
	CCLabelTTF *pTTFNickName;
	// 等级ico
	CCSprite *pSprLv;
	// 等级ttf
	CCLabelTTF *pTTFLv;
	// 经验槽
	CCProgressTimer *pProgressExp;

	// 筹码ttf
	CCLabelTTF *pTTFChip;

	// 可领取奖励
	CCSprite *pSprReward;
	// 可领取奖励ttf
	CCLabelTTF *pTTFReward;
};