#pragma once
#include <SIX_UIScene.h>
#include <SIX_Typedef.h>
#include <SIX_ClientRoom.h>
#include <SIX_Console.h>

class SIX_ClientRoom;

class SIX_SceneRoom:public SIX_UIScene
{
public:
	SIX_SceneRoom()
	{
		m_RoomPeopleCount = m_Tables = m_SeatNum;
		pListView = 0;
	}

	virtual ~SIX_SceneRoom();
public:
	static SIX_SceneRoom* scene();
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

#ifdef WIN32
	int OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam);
	virtual void OnProcessCommand(const char *cmd);
#endif
	void ShowConsole();
public:
	void RefreshTableList(int iRoomPeopleCount,int iTables,int iSeatNum);
	void ShowTable(bool IsShow=true);

	void MakeTableAll();
	void MakeRowTable(int rowStart,int rowCount,int tableCount);
	CCControlButton *FindControlFromData(int iTableNo,int iSeatNo);
	void SwitchSitDownOrLeaveSeat(long long lUserId,int iTableNo,int iSeatNo,bool IsSitDown);

	void ShowLoading(bool IsShow);
private:
	void doEvents(CCObject* pSender, CCControlEvent event);
private:
	SIX_ClientRoom *pClientRoom;
	int m_RoomPeopleCount;
	int m_Tables;
	int m_SeatNum;
	int m_rowHaveTableCount;			///< ÁÐÊý

	// UI
	SIX_ListView *pListView;
	SIX_Console *pConsole;
};