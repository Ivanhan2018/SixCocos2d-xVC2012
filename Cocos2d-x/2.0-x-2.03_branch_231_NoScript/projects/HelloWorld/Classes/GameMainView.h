//
//  GameMainView.h
//  XXDDZ
//
//  Created by XXY on 13-11-28.
//
//

#ifndef __XXDDZ__GameMainView__
#define __XXDDZ__GameMainView__

#include "cocos-ext.h"
#include "Packet.h"

#include "DDDMessageBox.h"
//#include "GamePlayerController.h"
//#include "HLDDZGameMenuLayer.h"
//#include "DDDGameMessageLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

enum GameMainType {
    GameT_Race = 10,
    GameT_Race_Back = 11,
    GameT_Normal = 20,
    GameT_Normal_Back = 21,
    GameT_NULL = 100
};

enum GameMsgType {
    GMsgT_SYS = 1,
    GMsgT_CHART = 2,
    GMsgT_FACE = 3
};

struct GameMessage {
    _WORD_ wChatLength; //信息长度
	_WORD_ wType; //聊天类型
    _D_WORD_ dwSendUserID;						//发送用�?    
	_D_WORD_ dwTargetUserID;						//目标用户
    _WORD_ wChairID;							//发送用户椅�?	
	_TCHAR_ szChatString[1024]; //聊天信息
};

struct PlayerEnter {
    bool isEnter;
    bool isLeave;
    _BYTE_ wChairStatusPrev;
    _BYTE_ wChairStatus;
    _D_WORD_ index;                             //玩家位子
    _D_WORD_ wPlayerId;                         //玩家ID索引
};

//时钟显示
struct TimerTip {
    CCSprite *timeTipLayer;
    CCLabelAtlas *timeMin;
    CCLabelTTF *timeDot;
    CCLabelAtlas *timeHour;
    bool onShow;
};

class GameMainView;

//extern GameMainView *THIS;

extern list<GameMessage>* TalkMessgaegList;

extern CCSprite *gameLayer;

class GameMainView: public DDDLayer, public WaittingOtherPlayer
{
    /*
     游戏场景基础类实现，主要为基类对应接口实�?     */
public:
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    void GameMainStartGame(float dt);
    
    void GameMainOverGame();
    
    void clearPlayerOnTable();
    
    void GameNeedSendConfigMessage(_BYTE_ wChairStatus);
  
    bool GameNeedReset();
    
    //加载用户信息，用户进入游�?    
	void InitGameController(_WORD_ wTableId,_WORD_ wChairID);
    
    void SetGameOutLineLoadback();
    
    list<GameMessage>* getTalkMsgList(void);
    
    list<PlayerEnter>* getPlayerEnterMsgList(void);
    
protected:
    
    virtual void GameMainLoop() = 0;
    
    virtual void LoadGameMainLayer() = 0;
    
    virtual void WaitOtherPlayerEnterStatusOff() = 0;
    
    bool firstEnterGame;
    
    virtual void GameNeedPrepare() = 0;
    
    CC_PROPERTY(bool , m_TableFull, TableFull);
    
    virtual void LoadTimeForCurrentMoment(bool onShow) = 0;
    
    //需要现实用户等待动�?    
	virtual void GameNeedWaittingAnimation() = 0;
    
private:
    
    CCSprite *ThisLayer;
    
    bool WillChangeTable;
    
public:
        bool GameCanSendeReady();
    
    // 主菜�?    
		//HLDDZGameMenuLayer *GamrMainMenuLayer;
    
        //DDDGameMessageLayer *MsgBoard;
    
    void setWillChangeTable(bool flag){
        WillChangeTable = flag;
    }
    
    //短线重连 �?�?    
	void GameOutLineConnect(bool flag);
    
    bool PlayerOnEnter;
    
    TimerTip *TM;
    
    GameMainType m_myGameType;
    
    //GamePlayerController *PActor;

};

#endif /* defined(__XXDDZ__GameMainView__) */
