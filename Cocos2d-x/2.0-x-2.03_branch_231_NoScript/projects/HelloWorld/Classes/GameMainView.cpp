//
//  GameMainView.cpp
//  XXDDZ
//
//  Created by XXY on 13-11-28.
//
//

#include "GameMainView.h"
#include "GameEngine.h"
//#include "GameBaseController.h"
#include "StaticProperty.h"
//#include "SEN_PlayerEnterGame.h"
//#include "OnLoadView.h"
//#include "OnChangeTableView.h"


//GameMainView *THIS = NULL;

int GameMainLoop_LM = 100;

bool outLineBack;

#pragma mark bool firstEnter;

CCSprite *gameLayer;

CCSprite *gameMenuLayer;

list<GameMessage>* TalkMessgaegList;

list<GameMessage>* GameMainView::getTalkMsgList(void)
{
	if(TalkMessgaegList == NULL)
	{
		TalkMessgaegList = new list<GameMessage>();
	}
	return TalkMessgaegList;
}

list<PlayerEnter>* PlayerEnterMsgList;

list<PlayerEnter>* GameMainView::getPlayerEnterMsgList(void){
    if(PlayerEnterMsgList == NULL)
	{
		PlayerEnterMsgList = new list<PlayerEnter>();
	}
	return PlayerEnterMsgList;
}


bool GameMainView::init(){
    if(TalkMessgaegList == NULL)
	{
		TalkMessgaegList = new list<GameMessage>();
	}
    
    if(PlayerEnterMsgList == NULL)
	{
		PlayerEnterMsgList = new list<PlayerEnter>();
	}
    
    m_myGameType = GameT_NULL;
    
    firstEnterGame = true;
    
    m_TableFull = false;
    
    WillChangeTable = false;
    
	return true;
}


void GameMainView::onEnter(){

    CCNode::onEnter();
    //if (THIS == NULL) {
    //    THIS = this;
    //}
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    ThisLayer = CCSprite::create("gameBack.png");
    ThisLayer->setPosition(ccp(size.width/2, size.height/2));
    ThisLayer->setOpacity(0);
    this->addChild(ThisLayer,10);

    gameMenuLayer = CCSprite::create("gamebg.png");
    gameMenuLayer->setOpacity(0);
    gameMenuLayer->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(gameMenuLayer,10);
    
    LoadGameMainLayer();
    
    
    //PActor->createRacePlayerController();
    
    this->scheduleOnce(schedule_selector(GameMainView::GameMainStartGame), 2.0f);
    
}

void GameMainView::onExit(){
    //if (THIS != NULL) {
    //    THIS = NULL;
    //}
    
    //if (MsgBoard) {
    //    MsgBoard->~DDDGameMessageLayer();
    //    MsgBoard = NULL;
    //}
    
    //PActor->clearPlayerData();
    //this->unschedule(schedule_selector(GameMainView::GameMainLoop));
    while (!PlayerEnterMsgList->empty()) {
        PlayerEnterMsgList->pop_front();
    }
    
    m_myGameType = GameT_NULL;
    
    firstEnterGame = true;
    
    m_TableFull = false;

    CCNode::onExit();
}

bool GameMainView::GameCanSendeReady(){
    return true;//MsgBoard->getOnDisplay();
}

void GameMainView::GameMainStartGame(float dt){
    PlayerOnEnter = true;

    //if (GameEngine::getCurrentGameType() != DGT_HLDDZMATCH) {
    //    if (!outLineBack) {
    //        if (!PActor->UserSitDownToJoinGame()) {
    //            CCLog("为什么坐下不成功");
    //        }
    //        
    //    }else{
    //        
    //        SEN_EnterRace::gameOption();
    //        outLineBack = false;
    //    }
    //}else{
    //    if (!outLineBack) {            
    //    }else{
    //        SEN_EnterRace::gameOption();
    //        outLineBack = false;
    //    }
    //}

//#pragma mark 创建顶部菜单按钮
//    {
//        GamrMainMenuLayer = HLDDZGameMenuLayer::create();
//        this->addChild(GamrMainMenuLayer,100);
//
//        
//        MsgBoard = new DDDGameMessageLayer();
//        MsgBoard->create(this, gameMenuLayer);
//    }
//    this->schedule(schedule_selector(GameMainView::GameMainLoop), 1);
}

bool GameMainView::GameNeedReset(){
    //DDD_Game_Type type = GameEngine::getCurrentGameType();
    return true;//type == DGT_HLDDZMATCH;
}

void GameMainView::GameNeedSendConfigMessage(_BYTE_ wChairStatus){
    //DDD_Game_Type type = GameEngine::getCurrentGameType();
    //if (type == DGT_HLDDZMATCH && wChairStatus == US_READY) {
    //    SEN_EnterRace::gameOption();
    //}else if(wChairStatus == US_SIT){
    //    SEN_EnterRace::gameOption();
    //}
}

void GameMainView::GameMainOverGame(){
//    if (WillChangeTable) {
//        #pragma mark (未实�? 更换桌子
//        CCDirector::sharedDirector()->replaceScene(OnChangeTableView::scene());
//        
//        return;
//    }
//    // 关闭数据接收
//    GameEngine::setCloseNetConnect();
//#pragma mark 重新登陆到大�?    
//	REC_LoginOnSquare::loginHall();
//#pragma mark 返回到大厅场�?    
//	OnLoadView::setNextViewType(SVCT_GAMESQUARE, SVCT_GAMESQUARE);
//    CCDirector::sharedDirector()->replaceScene(OnLoadView::scene());
}

void GameMainView::clearPlayerOnTable(){
    //PActor->clearPlayerForMatch();
}

void GameMainView::SetGameOutLineLoadback(){
    
    //firstEnterGame = false;
    //
    //_BYTE_ ChiIdx;
    //GameEngine::getGameServerData()->getCurrentChair(ChiIdx);
    //_BYTE_ tabIdx;
    //GameEngine::getGameServerData()->getCurrentTable(tabIdx);
    //
    //GameBaseController::setUserCurrentTableIndexAndChairIndex(tabIdx, ChiIdx);
    //PActor->controllerSetGameStart(ChiIdx);
}

void GameMainView::InitGameController(_WORD_ wTableId, _WORD_ wChairID){
    //if (!this) {
    //    if (THIS) {
    //        THIS->InitGameController(wTableId, wChairID);
    //    }
    //        return;
    //}else{
    //    PlayerOnEnter = false;
    //    GameBaseController::setUserCurrentTableIndexAndChairIndex(wTableId, wChairID);
    //    PActor->controllerSetGameStart(wChairID);
    //    int flg = PlayerEnterMsgList->size();
    //    while (flg-- > 0) {
    //        PlayerEnter EnterMsg= PlayerEnterMsgList->front();
    //        if (EnterMsg.isEnter == EnterMsg.isLeave || EnterMsg.isEnter) {
    //            PActor->LoadPlayerStateforIndex(EnterMsg.index, EnterMsg.wChairStatusPrev, EnterMsg.wChairStatus, EnterMsg.wPlayerId);
    //        }else{
    //            PActor->setPlayerLeaveGame(EnterMsg.index, EnterMsg.wChairStatusPrev, EnterMsg.wChairStatus, EnterMsg.wPlayerId);
    //        }
    //        PlayerEnterMsgList->push_back(EnterMsg);
    //        PlayerEnterMsgList->pop_front();
    //    }
    //    PlayerOnEnter = true;
    //}
    
}

//断线虫练 �?�?
void GameMainView::GameOutLineConnect(bool flag){
    if (flag) {
        CCNotificationCenter::sharedNotificationCenter()->postNotification("ONLOADVIEWPASS",(CCObject *)100);
        CCLog("断线虫练  完成 登陆");
    }
    outLineBack = flag;
}


void GameMainView::setTableFull(bool flg){
    m_TableFull = flg;
}

bool GameMainView::getTableFull(){
    return m_TableFull;
}

