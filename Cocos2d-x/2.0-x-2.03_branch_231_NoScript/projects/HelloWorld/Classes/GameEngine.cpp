#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include "GameEngine.h"
//#include "REC_GameController.h"
//#include "WaringView.h"

//**************************************************************************
//****************************引擎部分全局数据*******************************

GameEngine *m_gameEngin;

/*
 网络
 */
ODSocket *m_odSocket;
// 服务器是否连接成功
bool isConnet = false;
// 当前连接的服务器
int currentConnet;

list<tagShortMsgInfo> *shortMSGINFO;

//******************************数据部分********************************
/*
 用户信息
 */
//GlobalUserInfo *globalUserInfo;

// 斗地主房间数据
list<tagGameServer> *XXDDZRoomList;
// 欢乐斗地主房间数据
list<tagGameServer> *HLDDZRoomList;

map<_WORD_, int> *XXGameMatchList;

// 游戏服务数据
//GameServerData* m_GameServerData;

//*************************获取数据**************************
// 获取用户数据
//GlobalUserInfo* GameEngine::getGlobalUserInfo()
//{
//	// 用户数据
//	if (globalUserInfo == NULL)
//	{
//		globalUserInfo  = new GlobalUserInfo();
//	}
//	return globalUserInfo;
//}
// 玩家所有数据
//GameServerData* GameEngine::getGameServerData()
//{
//	if(m_GameServerData == NULL)
//	{
//		m_GameServerData = new GameServerData();
//	}
//	return m_GameServerData;
//}

// 获取房间列表
list<tagGameServer>* GameEngine::getXXDDZRoomList(void)
{
	if(XXDDZRoomList == NULL)
	{
		XXDDZRoomList = new list<tagGameServer>();
	}
	return XXDDZRoomList;
}

//获取比赛列表
map<_WORD_, int> * GameEngine::getXXGameMatchList(void){
    
    if(XXGameMatchList == NULL)
	{
		XXGameMatchList = new map<_WORD_, int>;
	}
	return XXGameMatchList;
}

list<tagShortMsgInfo>* GameEngine::getshortMSGINFOList(void){
    
    if(shortMSGINFO == NULL)
	{
		shortMSGINFO = new list<tagShortMsgInfo>();
	}
	return shortMSGINFO;
}

// 获取欢乐斗地主游戏房间列表
list<tagGameServer>* GameEngine::getHLDDZRoomList(void){
    if(HLDDZRoomList == NULL)
	{
		HLDDZRoomList = new list<tagGameServer>();
	}
	return HLDDZRoomList;
}

//*************************获取数据 end**************************
// 构造函数
GameEngine::GameEngine(void)
{
	// 初始化
	Init();
    
    m_gameEngin = this;
}

GameEngine::~GameEngine(void)
{
    
}
// ***************引擎初始化*********************
bool GameEngine::Init()
{
	// ******线程的初始化*********
    // 创建网络链接
	m_odSocket = new ODSocket(this);
    // 监听消息发送
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameEngine::messageCallBack), "MESSAGE", NULL);
    // 开启线程
	starThread();
	return true;
}

// 获取网络对象
ODSocket* GameEngine::getODSocket()
{
	return m_odSocket;
}

ODSocket * GameEngine::getODSocket(bool &success){
    if (!m_odSocket) {
        success = false;
        return NULL;
    }else{
        success = true;
        return m_odSocket;
    }
}

//*************************获取数据 end**************************

GameEngine* GameEngine::getGameEngin(){
    if(!m_gameEngin){
        m_gameEngin = new GameEngine();
    }
    return m_gameEngin;
}

// 消息回调函数
void GameEngine::sendData(CCObject* obj)
{
    //1、得到具体的对象给对象注入当前引擎的指针
	((DataDispath_Base*)obj)->setGameEngine(this);
    
    ((DataDispath_Base*)obj)->run();
}

// 关闭网络连接
void GameEngine::setCloseNetConnect(void){
    // 关闭连接
    isConnet = false;
    // 关闭网络
    m_odSocket->Clean();
    m_odSocket->Close();
    
}

// 连接网络
bool GameEngine::connetNet(int currentConnetID,const char* ip,unsigned short port)
{
    // 如果之前网络没有关闭就关闭网络
    if(isConnet){
        setCloseNetConnect();
    }
    
    // 网络初始化
	m_odSocket->Init();
	// 创建
	m_odSocket->Create(AF_INET,SOCK_STREAM,0);
	// 设置服务器链接的ID
	currentConnet = currentConnetID;
	// 链接
	isConnet = m_odSocket->Connect(ip,port);
    
	return isConnet;
}


//关闭事件
bool  GameEngine::OnEventTCPSocketShut(_WORD_ wSocketID, _BYTE_ cbShutReason){
    if(isConnet){// 服务器主动断开
        // 设置断开标志
        isConnet = false;
        // 弹出提示窗口
        //WaringView::setEORROutLine();
        //CCDirector::sharedDirector()->replaceScene(WaringView::scene());
        
    }
    return true;
}

// 网络数据读取处理
bool  GameEngine::OnEventTCPSocketRead(_WORD_ wSocketID, TCP_Command Command, void * pData, _WORD_ wDataSize)
{
	// 切换服务器连接
	switch(currentConnet)
	{
        case HALLLOGINCONNET:// 大厅连接
		{
			//return REC_LoginOnSquare::MainIdData(Command,pData,wDataSize);
		}
            break;
        case GAMELOGINCONNET:// 游戏连接
		{
			//return REC_GameController::MainIdData(Command,pData,wDataSize);
		}
            break;
	}
    CCLog("空闲中 %d", Command.wMainCmdID);
	return true;
}

//////////////////////////////////////////////////////
//接收线程开始
bool GameEngine::starThread()
{
	// 启动接收数据的线程
	if (pthread_create(&rec_pidrun,NULL,thread_run,NULL) == -1)
	{
		// 线程启动失败
		return false;
	}
	return true;
}

// 接收网络数据的回调函数
void *GameEngine::thread_run(void *m_map)
{
	// while让线程一直循环
	while(true)
	{
        // 判断网络是否连接
        if(isConnet){
            // 调用网络数据接收
			m_odSocket->OnSocketNotifyRead(1,1);
        }
        // 线程休眠
        //sleep(1);
	}
	return NULL;
}
// 消息回调函数
void GameEngine::messageCallBack(CCObject* obj)
{
    //1、得到具体的对象给对象注入当前引擎的指针
	((DataDispath_Base*)obj)->setGameEngine(this);
    
    ((DataDispath_Base*)obj)->run();
}

bool GameEngine::isNetconnnect(const char *dud_IP){
    
    string stringresult = "error";
    char kkk[6] = {0};
    stringresult.copy(kkk, 5);
    
    int isnet =  strcmp(kkk, m_odSocket->jiexiyuming(dud_IP));
    if (isnet == 0) {
        return false;
    }else{
        return  true;
    }
    
}

#endif







