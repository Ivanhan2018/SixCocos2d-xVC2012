#pragma once
#include <SIX_UIScene.h>
#include <SIX_Typedef.h>
#include <SIX_ClientLogin.h>
#include <SIX_ClientRoom.h>
#include <SIX_ConsoleGM.h>
#include "SIX_RippleGrid3D.h"
#include "SIX_PopWndSetting.h"
#include <SIX_ExpandLayer.h>
#include <SIX_Cursor.h>
#include <SIX_RoomList.h>
#include "SIX_MatchList.h"
#include "SIX_PopWndRank.h"
#include "SIX_LoginPanel.h"
#include "SIX_LoginPanelSG.h"

class SIX_ClientLogin;
class SIX_ClientRoom;
class SIX_RoomList;
class SIX_MatchList;

class SIX_SceneGate:public SIX_UIScene
{
public:
	SIX_SceneGate()
	{
	}

	virtual ~SIX_SceneGate();
public:
	static SIX_SceneGate* scene();
	//add by Ivan_han 20130904
	SIX_ConsoleGM* getConsoleGM()const{return pConsole;}
	virtual bool init();
	void update(float dt);

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
	int OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam);
	virtual void OnProcessCommand(const char *cmd);
#endif
	void ShowConsole();

	SIX_RoomList *getRoomList(){return pRoomList;}
	SIX_MatchList *getMatchList(){return m_pMatchList;}
	SIX_PopWndRank * getRanking(){return m_pRank;}
	SIX_LoginPanel *getLoginPanel(){return m_pLoginPanel;}
private:
	void doEvents(CCObject* pSender, CCControlEvent event);
	void dropStone(int x, int y, int stoneSize, int stoneWeight);
private:
	// UI
	SIX_ConsoleGM *pConsole;

	SIX_RippleGrid3D *pRipple;  
    int gridWidth;
    int gridHeight;

	int m_ref;

	SIX_PopWndSetting *pSetting;
	SIX_RoomList *pRoomList;
	SIX_MatchList *m_pMatchList;
	SIX_PopWndRank *m_pRank;
	SIX_LoginPanel *m_pLoginPanel;
	//SIX_LoginPanelSG *m_pLoginPanel;
};