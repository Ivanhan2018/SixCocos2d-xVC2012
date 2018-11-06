#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__



#include <time.h>
#include <pthread.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/platform.h"
#else
#include "platform.h"
#endif

#include <list>
//////////////////////////
#include "Packet.h"
#include "Define.h"
#include "CMD_LogonServer.h"
#include "DataDispath_Base.h"
#include "ODSocket.h"
#include "cocos2d.h"
//#include "REC_LoginOnSquare.h"
//#include "GameServerData.h"
#include "CMD_Commom.h"
#include "CMD_GameServer.h"
//#include "REC_GameController.h"


using namespace std;
using namespace cocos2d;


class GameEngine:public ITCPSocketSink,public CCObject
{
public:
	GameEngine(void);
	~GameEngine(void);
	//窗体指针
    
	//逻辑类
    
public:
    static  bool isNetconnnect(const char *dud_IP);
	//// 获取用户数据
	//static GlobalUserInfo * getGlobalUserInfo(void);
	// 获取游戏的房间列表
    static list<tagGameServer>* getXXDDZRoomList(void);
    // 获取游戏的房间列表
    static list<tagGameServer>* getHLDDZRoomList(void);
    //获取比赛列表
    static map<_WORD_, int> * getXXGameMatchList(void);
	//// 游戏服务器数据
	//static GameServerData* getGameServerData(void);
    
    static list<tagShortMsgInfo>* getshortMSGINFOList(void);
    
private:
	bool Init();
    
public:
	//连接事件
	virtual bool OnEventTCPSocketLink(_WORD_ wSocketID, int nErrorCode)
	{
		return true;
	}
	//关闭事件
	virtual bool  OnEventTCPSocketShut(_WORD_ wSocketID, _BYTE_ cbShutReason);
	//读取事件
	virtual bool  OnEventTCPSocketRead(_WORD_ wSocketID, TCP_Command Command, void * pData, _WORD_ wDataSize);
    
    
    //////////////////////////////////////////////////////////////////////
    //*****************线程的控制********************
private:
	// 接收数据的线程开启
	bool starThread(void);
	// 申明接收数据的线程ID
	pthread_t rec_pidrun;
    // 消息回调函数
	void messageCallBack(CCObject* obj);
    
public:
	// 定义线程的回调函数
	static void* thread_run(void *);
public:
    // 发送数据
	void sendData(CCObject* obj);
public:
    static GameEngine* getGameEngin();
    
public:
	// 获取网络对象
	ODSocket* getODSocket(void);
    static ODSocket * getODSocket(bool &success);
    
	// 链接网络
	static bool connetNet(int currentConnetID,const char* ip,unsigned short port);
    //关闭网络
    static void setCloseNetConnect(void);
    
    //static void setCurrentGameType(DDD_Game_Type type){
    //    REC_GameController::setCurrentGameType(type);
    //}
    
    //static DDD_Game_Type getCurrentGameType(){
    //    return REC_GameController::getCurrentGameType();
    //}

};
#endif //__GAME_ENGINE_H__
