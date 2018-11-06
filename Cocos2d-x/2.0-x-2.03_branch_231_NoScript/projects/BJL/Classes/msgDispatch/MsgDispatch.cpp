//
//  gameFrame.cpp
//  SDH
//
//  Created by zhouwei on 13-6-6.
//
//

#include "MsgDispatch.h"
#include "common/CMD_Game.h"
#include "event/GBEventIDs.h"
#include "globalUnits/GlobalUnits.h"
#include "common/CMD_Plaza.h"
#include "common/IDataArchive.h"
#include "globalUnits/GlobalUnits.h"
#include "common/GlobalField.h"
#include <string>
#include "common/Encrypt.h"
#include "common/GlobalFrame.h"
#include "common/CMD_Plaza.h"
#include "ans/utf-8.h"
#include "configMgr/ConfigMgr.h"
#include "gui/TaskInfo.h"
#include "common/packet.h"
#include "common/CMD_Commom.h"
#include "common/CMD_LogonServer.h"
#include "common/CMD_GameServer.h"
#include "common/platform.h"
#include "net/common.h"
#include "common/MyNSString.h"
#include "common/struct.h"
#include "common/DBHandler.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

#define GAMEKINDDDZ 300

#include "entity/EntityMgr.h"

#ifdef WIN32
#include <Winsock2.h>
#endif

#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))


MsgDispatch::MsgDispatch()
	:m_loginState(enLogin_Server)
{
	GBEVENT_ARG_REGISTER(GBEVENT_NETWORK, MsgDispatch::onEventSocketRecv);
	m_dwRecvPacketCount = 0;
	m_wRecvSize = 0;
	m_bAnonymous = false;
	m_bRegLogin  = false;
	m_bGameStatus = false;

	memset(m_lUserLevel, 0, sizeof(m_lUserLevel));
	//add by wangjun 2014-12-10
	// 消息状态
	m_eDataType = CMD_Logon;
	// 保存游戏ID
	m_dwKindID = 122;
	//m_dwKindID = 27;
	// 启动标识
	m_bStartType = false;
	m_wBehaviorFlags = 0;	

	m_pAccounts = "";
	m_pPassword = "";
	m_pBankWord = "";
	m_pNickname = "";
	m_pPhoneNum = "";

	m_dwUserID		= 0;						
	m_wTableID		= 0;				
	m_wChairID		= 0;	
	m_dwGameID		= 0;
	m_cbStatus		= US_NULL;	
	m_dwGoldScore   = 0;

	m_pClientLoginSock = new ClientSock();
	m_pClientGameSock  = new ClientSock();
	memset(szDescribeString, 0, sizeof(szDescribeString));
	/*CCNotificationCenter::sharedNotificationCenter()->addObserver(
	this, callfuncO_selector(MsgDispatch::onEventSocketRecv), MSG_ANS_NETWORK, NULL);*/
}

MsgDispatch::~MsgDispatch()
{
	GBEVENT_ARG_UNREGISTER(GBEVENT_NETWORK, MsgDispatch::onEventSocketRecv);
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector
		(schedule_selector(MsgDispatch::update), this);

	CC_SAFE_DELETE(m_pClientLoginSock);
	CC_SAFE_DELETE(m_pClientGameSock);

	//CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_ANS_NETWORK);
}

bool MsgDispatch::init()
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector
		(schedule_selector(MsgDispatch::update), this, 0,false);
	return true;
}
void MsgDispatch::update(float dt)
{
	if (m_loginState == enLogin_Server)
	{
		m_pClientLoginSock->update();
	}else
	{
		m_pClientGameSock->update();
	}
}
void MsgDispatch::setGameStatus(bool bStatus)
{ 
	m_bGameStatus = bStatus; 
}

void MsgDispatch::onEventSocketRecv(GBEventConstArg& arg)
{
	tagBuffer& tag = (tagBuffer&)arg;    
	memmove(m_cbRecvBuff + m_wRecvSize, tag.dateBuffer, 81920 - m_wRecvSize);

	m_wRecvSize += tag.nDataSize;

	//变量定义
	WORD wPacketSize=0;
	BYTE cbDataBuffer[SOCKET_PACKET+sizeof(CMD_Head)];
	memset(cbDataBuffer, 0, SOCKET_PACKET+sizeof(CMD_Head));
	CMD_Head * pHead=(CMD_Head*)m_cbRecvBuff;
	while (m_wRecvSize>=sizeof(CMD_Head))
	{
		//效验参数
		wPacketSize = pHead->CmdInfo.wPacketSize;

		if (wPacketSize < sizeof(CMD_Head))
		{
			CCLOG("data error,small than head data");
			return;
		}

		if (pHead->CmdInfo.cbVersion != SOCKET_VER)
		{
			CCLOG("version error");
			return;
		}

		if (m_wRecvSize < wPacketSize)
		{
			return;
		}

		//拷贝数据
		m_dwRecvPacketCount++;

		memcpy(cbDataBuffer,m_cbRecvBuff,wPacketSize);
		m_wRecvSize-=wPacketSize;
		memmove(m_cbRecvBuff,m_cbRecvBuff + wPacketSize,m_wRecvSize);

		WORD wRealySize = wPacketSize;
		if (m_loginState == enLogin_Server)
		{
			//解密数据
			//wRealySize=m_pClientLoginSock->crevasseBuffer(cbDataBuffer,wPacketSize);
			if(!Common_unMappedBuffer(cbDataBuffer,wPacketSize)){
				CCLog("Common_unMappedBuffer FAILED");
			}
		}else
		{
			//解密数据
			//wRealySize=m_pClientGameSock->crevasseBuffer(cbDataBuffer,wPacketSize);
			if(!Common_unMappedBuffer(cbDataBuffer,wPacketSize)){
				CCLog("Common_unMappedBuffer FAILED");
			}
		}

		//解释数据
		WORD wDataSize=wRealySize-sizeof(CMD_Head);
		void * pDataBuffer=cbDataBuffer + sizeof(CMD_Head);
		CMD_Command Command=((CMD_Head*)cbDataBuffer)->CommandInfo;

		if(Command.wMainCmdID == 0 &&Command.wSubCmdID == 1)
		{
			return;
		}

		if (Command.wMainCmdID == MDM_KN_COMMAND)
		{
			switch (Command.wSubCmdID)
			{
			case SUB_KN_DETECT_SOCKET:	//网络检测
				{
					//发送数据

					if (m_loginState == enLogin_Server)
					{
						SendPacketWithCompilatio(0);
					}else
					{
						SendPacketWithCompilatio(1);
					}
					break;
				}
			}
			continue;
		}

		CCLOG("wMainCmdID = %d,wSubCmdID = %d",Command.wMainCmdID,Command.wSubCmdID);

		if (m_eDataType == CMD_Game)
		{
			OnEventTcpGameRead(0, &Command, pDataBuffer, wDataSize);
		}else if(m_eDataType == CMD_Room)
		{
			OnEventTcpRoomRead(0, &Command, pDataBuffer, wDataSize);
		}else{
			onEventTcpLoginRead(0, &Command, pDataBuffer, wDataSize);
		}
	}
}

void MsgDispatch::setTcpSink(BaseObject* obj)
{

}

//设置登陆状态
void MsgDispatch::setLoginState(enLoginState state)
{
	m_loginState = state;
}


bool MsgDispatch::onEventTcpLoginRead(WORD wSocketId,CMD_Command* pCommand,void* pData,WORD wDataSize)
{
	/*switch (pCommand->wMainCmdID)
	{
	case MDM_GP_LOGON:          //登陆消息
	return onSocketMainLogin(pCommand,pData,wDataSize);

	case MDM_GP_SERVER_LIST:    //列表消息
	return onSocketMainServerList(pCommand,pData,wDataSize);

	case MDM_GP_SYSTEM:         //系统消息
	return onSocketMainSystem(pCommand, pData,wDataSize);

	case MDM_GP_USER:           //用户消息
	return onSocketMainUser(pCommand, pData,wDataSize);
	default:
	break;
	}*/


	switch (pCommand->wMainCmdID)
	{
	case MDM_MB_LOGON:          //登陆消息 100
		return OnTCPNetworkMainMBLogon(pCommand->wSubCmdID,pData,wDataSize);
	case MDM_MB_SERVER_LIST:    //列表消息 101
		return OnTCPNetworkMainMBServerList(pCommand->wSubCmdID,pData,wDataSize);
	case MDM_MB_USER_SERVICE:           //用户服务 102
		return OnTCPNetworkMainMBIphoneUserService(pCommand->wSubCmdID, pData,wDataSize);
	case MDM_KN_COMMAND:				// 0
		return true;
	case SUB_KN_DETECT_SOCKET:          // 1
		return false;
	case MDM_GP_USER_SERVICE:          // 3
		return onSocketMainUser(pCommand, pData,wDataSize);
	default:
		//CCAssert(false, "大厅:没有处理的case");
		return false;
	}
	return true;
}

//-----------主命令码分类-------------------
//-------------大厅登录--------------
//登录消息		add by wangjun 2014-12-10
bool MsgDispatch::OnTCPNetworkMainMBLogon(int wSubCmdID, void *buffer, WORD size)
{
	//CCLog("OnTCPNetworkMainMBLogon wSubCmdID=%d", wSubCmdID);
	switch (wSubCmdID)
	{
	case SUB_MB_LOGON_SUCCESS:			// 登录成功	100
		{
			return this->OnSocketSubLogonSuccess(buffer, size);
		}
	case SUB_MB_LOGON_FAILURE:			// 登录失败	101
		{
			return this->OnSocketSubLogonFailure(buffer, size);
		}
		//      case SUB_GR_LOGON_NOTIFY:			// 登陆提示TIPS	104
		//		{
		//            return [self OnSocketSubGRLogonNotify:buffer bufferSize:size];
		//		}
	default:
		//CCAssert(false, "登录处理:超出范围");
		return true;
	}
	return true;
}

//列表消息		add by wangjun 2014-12-10
bool MsgDispatch::OnTCPNetworkMainMBServerList(int wSubCmdID, void *buffer, WORD size)
{
	switch (wSubCmdID) 
	{
	case SUB_MB_LIST_KIND:				// 种类列表	100
		{
			return this->OnSocketSubListKind(buffer, size);
		}
	case SUB_MB_LIST_SERVER:			// 房间列表	101
		{
			return this->OnSocketSubListServer(buffer, size);
		}
	case SUB_MB_LIST_FINISH:			// 列表完成	200
		{
			return this->OnSocketSubListFinish(buffer, size);
		}
	}
	return true;
}

//服务消息		add by wangjun 2014-12-10
bool MsgDispatch::OnTCPNetworkMainMBIphoneUserService(int wSubCmdID, void *buffer, WORD size)
{
	return true;
}

//---------------------大厅登录子命令码处理--------------------------
//登录成功      add by wangjun 2014-12-10
bool MsgDispatch::OnSocketSubLogonSuccess(void *buffer, WORD size)
{
	CCLog("OnSocketSubLogonSuccess");

	// 效验大小
	assert(size == sizeof(CMD_MB_LogonSuccess));
	if (size != sizeof(CMD_MB_LogonSuccess)) return false;

	// 变量定义
	BYTE cbBuffer[sizeof(CMD_MB_LogonSuccess)];
	memset(cbBuffer, 0 , sizeof(CMD_MB_LogonSuccess));
	CMD_MB_LogonSuccess *logonSuccess = (CMD_MB_LogonSuccess *)cbBuffer;
	memcpy(logonSuccess, buffer, sizeof(CMD_MB_LogonSuccess));

	// 登录昵称
	char nicknameArray[64]={0};
	MyNSString::wc2mbs(logonSuccess->szNickName, sizeof(logonSuccess->szNickName), nicknameArray);
	m_pNickname = string(nicknameArray);

	// 记录个人信息
	m_cbGender = logonSuccess->cbGender;
	m_wFaceID = logonSuccess->wFaceID;
	m_dwUserID = logonSuccess->dwUserID;
	m_dwGameID = logonSuccess->dwGameID;
	m_dwGoldScore = logonSuccess->dwGoldScore;    // 用户拥有的豆豆
	m_dwExperience = logonSuccess->dwExperience;

	//保存信息
	tagGlobalUserData* pUserData = new tagGlobalUserData;
	MyNSString::wc2mbs(logonSuccess->szNickName, sizeof(logonSuccess->szNickName), pUserData->szNickName);
	pUserData->cbGender=logonSuccess->cbGender;
	pUserData->wFaceID=logonSuccess->wFaceID;
	pUserData->dwUserID=logonSuccess->dwUserID;
	pUserData->dwGameID=logonSuccess->dwGameID;
	pUserData->lScore=logonSuccess->dwGoldScore;    // 用户拥有的豆豆
	pUserData->lExperience=logonSuccess->dwExperience;
	g_GlobalUnits.setGolbalUserData(pUserData);
	CCLOG("wFaceID:%d",pUserData->wFaceID);

	CCLOG("login success2! file(%s) line(%d)",__FILE__, __LINE__);



	//EntityMgr::instance()->getDispatch()->closeLoginSocket();

	cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("NEWZJD_ACCOUNT", m_szAccount);
	cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("NEWZJD_PASSWORD", m_szPassword);
	CCUserDefault::sharedUserDefault()->flush();

	DBHandler *handler = new DBHandler();
	//char sql[800] = {0};
	sqlite3 *DB = handler->getDB();
	sqlite3_stmt *stmt;
	char sql[1024];
	int rv = sqlite3_prepare(DB, "select * from AccountDB", 100, &stmt, NULL);
	rv = sqlite3_step(stmt);
	if(rv == SQLITE_ROW)
	{
		sqlite3_finalize(stmt);
		handler = new DBHandler();
		memset(sql, 0, sizeof(sql));
		sprintf(sql, "update AccountDB set account=\'%s\',password=\'%s\' where id=0",m_szAccount.c_str(),m_szPassword.c_str());
		//sprintf(sql, "update AccountDB set account = \'%s\',password = \'%s\' where id = 0",m_szAccount.c_str(),m_szPassword.c_str());
		handler->execute(sql);
	}else{
		sqlite3_finalize(stmt);
		handler = new DBHandler();
		memset(sql, 0, sizeof(sql));
		//string str = "insert into AccountDB values(\'";
		//str = str+m_szAccount;
		//str = str+"\',\'";
		//str = str+m_szPassword;
		//str = str+"\')";
		//handler->execute(str.c_str());
		sprintf(sql, "insert into AccountDB values(0,\'%s\',\'%s\')",m_szAccount.c_str(),m_szPassword.c_str());
		handler->execute(sql);
	}

	//为注册登陆
	if ( EntityMgr::instance()->getDispatch()->isRegLogin())
	{
		CCLOG("register success! file(%s) line(%d)",__FILE__, __LINE__);

		int count = CCUserDefault::sharedUserDefault()->getIntegerForKey("KEY_ACCOUNT_COUNT") + 1;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("KEY_ACCOUNT_COUNT", count);

		EntityMgr::instance()->getDispatch()->setRegLogin(false);
		//GBEvent::instance()->fire(GBEVENT_UI_REGISTERSUCC);

		CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_REGSUCC);
		this->SendPacketWithQueryBankInfo();
		return true;
	}

	CCLOG("login success! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}

//登录失败      add by wangjun 2014-12-10
bool MsgDispatch::OnSocketSubLogonFailure(void *buffer, WORD size)
{
	CCLog("OnSocketSubLogonFailure");
	EntityMgr::instance()->getDispatch()->closeLoginSocket();

	//效验参数
	CMD_MB_LogonFailure* pLogonError = (CMD_MB_LogonFailure *)buffer;

	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_LOGINFAIL);
	return true;
}

//---------------------列表处理子命令码处理--------------------------
//列表获取      add by wangjun 2014-12-10
bool MsgDispatch::OnSocketSubListKind(void *buffer, WORD size)
{
	CCLog("列表获取");
	return true;
}

//房间列表      add by wangjun 2014-12-10
bool MsgDispatch::OnSocketSubListServer(void *buffer, WORD size)
{
	// loaing进度提示 这里暂时不加


	// 变量定义
	int structSize = sizeof(tagGameServer);

	/*********************************************************************************
	* important 游戏房间数永运等于3，如果server.wSortID相同，则认为在同一个房间有两个入口，
	* 把它保存在数据，快速加入时，搜寻这个数据，保证玩家能登录。
	**********************************************************************************/
	int count = size/structSize;
	int index = 0;

	//这是之前保存数据的地方，先留着
	BYTE cbBuffer[2048];
	memset(cbBuffer, 0 , 2048);
	tagGameServer* pGameServer = (tagGameServer*)cbBuffer;
	memcpy(pGameServer, buffer, size);
	unsigned int nItemCount = count;
	g_GlobalUnits.m_nOnlineCount = nItemCount;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_REFRESHTOTALNUM);
	m_ServerListMgr.clearItem();
	m_ServerListMgr.insertItem(pGameServer,nItemCount);
	m_ServerListMgr.sortItems();
	//ios牛牛中保存数据的方法

	/*
	CCLog("游戏房间数 count=%d, 可使用服务器房间总数=%d", count, size/structSize);

	CCArray *pageRoom = CCArray::create();
	CCArray *roomArray = NULL;
	CFrameOneRoom* pRoomData[3];
	for (int i = 0; i < count; i++)
	pRoomData[i] = NULL;

	// 生成游戏房间列表  顺序为 普通房、初级房、PK房 
	for (int i = 0; i < count; i++)
	{
	if (index%3 == 0)
	{
	roomArray = CCArray::create();
	pageRoom->addObject(roomArray);
	}
	tagGameServer server;
	memset(&server, 0, sizeof(tagGameServer));
	memcpy(&server, ((tagGameServer *)buffer+i), structSize);
	char tempServerName[64];
	MyNSString::wc2mbs(server.szServerName, sizeof(server.szServerName), tempServerName);
	CCLog("lBeginScore=%lld, lMinScore=%lld server.wSortID=%d, roomName=%s", server.lServerScore , server.lMinServerScore, server.wSortID, tempServerName);


	if (count == 3)
	{
	if (server.wSortID == 1)
	{   // 初级房
	pRoomData[1] = COneRoom::ViewWithOneRoomView(&server, 1%m_pFrameDate.m_nRoomCount);
	}
	else if (server.wSortID == 2)
	{
	// 普通房
	pRoomData[0] = COneRoom::ViewWithOneRoomView(&server, 0%m_pFrameDate.m_nRoomCount);
	}
	else if (server.wSortID == 3)
	{
	// PK房
	pRoomData[2] = COneRoom::ViewWithOneRoomView(&server, 2%m_pFrameDate.m_nRoomCount);
	}
	}
	else if (count == 1)
	{
	// 只有一个房间
	pRoomData[0] = COneRoom::ViewWithOneRoomView(&server, 0%m_pFrameDate.m_nRoomCount);
	}
	else if (count == 2)
	{
	if (server.wSortID == 1)
	{   
	pRoomData[1] = COneRoom::ViewWithOneRoomView(&server, 1%m_pFrameDate.m_nRoomCount);
	}
	else
	{
	pRoomData[0] = COneRoom::ViewWithOneRoomView(&server, 2%m_pFrameDate.m_nRoomCount);
	}
	}

	index++;
	}

	for (int i = 0; i < count; i++)
	[roomArray addObject:pRoomData[i]];

	//NSLog(@"pageRoom string=%@", pageRoom);

	// 设置列表key
	[m_pPlazaDic setObject:pageRoom forKey:@"roomlist"];
	*/
	return true;
}

//列表完成      add by wangjun 2014-12-10
bool MsgDispatch::OnSocketSubListFinish(void *buffer, WORD size)
{
	CCLog("OnSocketSubListFinish");

	// 拷贝房间信息，并刷新显示
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_REFRESHTOTALNUM, NULL);
	GBEvent::instance()->fire(GBEVENT_UI_LOGINFINISH);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_LOGINFINISH);
	/*
	// 检测函数
	if([m_pPlaza respondsToSelector:@selector(FrameDateDelegateWithListFinish:size:)])
	[m_pPlaza FrameDateDelegateWithListFinish:buffer size:size];
	else
	NSAssert(FALSE,@"(FrameDateDelegateWithListFinish:size:)");

	// 标识数据状态
	m_eDataType = CMD_Room;

	// 关闭当前连接
	[m_pStream ClosedStream];     // modi by mojunxin   important
	*/
	return true;
}

//登陆房间信息
bool  MsgDispatch::OnEventTcpRoomRead(WORD wSocketId,CMD_Command* pCommand,void* pData,WORD wDataSize)
{
	dispEntityMsg(pCommand,pData,wDataSize,GBEVENT_NETWORK_ROOM);
	return true;
}

//游戏服务消息
bool  MsgDispatch::OnEventTcpGameRead(WORD wSocketId,CMD_Command* pCommand,void* pData,WORD wDataSize)
{
	dispEntityMsg(pCommand,pData,wDataSize,GBEVENT_NETWORK_GAME);
	return true;
}

//登录消息
bool MsgDispatch::onSocketMainLogin(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	dispEntityMsg(pCommand,pBuffer,wDataSize,GBEVENT_NETWORK_LOGIN);

	return true;
}

void MsgDispatch::dispEntityMsg(CMD_Command* pCommand, void * pBuffer, WORD wDataSize,GBEVENT_ID eid)
{
	tagCmdBuffer tag;
	memset(tag.dateBuffer, 0, 40960);

	tag.nDataSize = wDataSize;
	memcpy(tag.dateBuffer, pBuffer,wDataSize);
	memcpy(&tag.command, pCommand,sizeof(CMD_Command));

	GBEvent::instance()->fire(eid,tag);
}
//列表消息
bool MsgDispatch::onSocketMainServerList(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	switch (pCommand->wSubCmdID)
	{
	case SUB_GP_LIST_TYPE:			//类型信息
		{
			CCLOG("get game list type! file(%s) line(%d)",__FILE__, __LINE__);
			return true;
		}
	case SUB_GP_LIST_KIND:			//种类消息
		{
			CCLOG("get game list kind! file(%s) line(%d)",__FILE__, __LINE__);
			return true;
		}
	case SUB_GP_LIST_STATION:		//站点消息
		{
			CCLOG("get game list station! file(%s) line(%d)",__FILE__, __LINE__);
			return true;
		}
	case SUB_GP_LIST_SERVER:		//创建服务器房间列表
		{
			//效验参数
			if (wDataSize % sizeof(tagGameServer) != 0)
			{
				return false;
			}


			//获取服务器列表，添加到服务器管理控制类，同时获取房间在线人数
			//tagGameServer* pGameServer = new tagGameServer;

			tagGameServer* pGameServer = (tagGameServer*)pBuffer;
			unsigned int nItemCount = wDataSize / sizeof(tagGameServer);

			g_GlobalUnits.m_nOnlineCount = nItemCount;

			CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_REFRESHTOTALNUM);

			m_ServerListMgr.clearItem();
			m_ServerListMgr.insertItem(pGameServer,nItemCount);
			CCLOG("get game list server! file(%s) line(%d)",__FILE__, __LINE__);
			return true;
		}
	case SUB_GP_LIST_FINISH:		//登录服务器列表发送完成
		{
			//统计游戏总人数			
			return true;
		}
	case SUB_GP_LIST_CONFIG:		//列表配置
		{
			assert(wDataSize == sizeof(CMD_GP_ListConfig));
			if (wDataSize != sizeof(CMD_GP_ListConfig))
			{
				return false;
			}
			CMD_GP_ListConfig *pListConfig = (CMD_GP_ListConfig *)pBuffer;
			// 破产标准
			ConfigMgr::instance()->m_Config.m_nGolbalBankruptcy = pListConfig->nBankruptcy;
			memcpy(ConfigMgr::instance()->m_Config.szTitle, pListConfig->szTitle, sizeof(ConfigMgr::instance()->m_Config.szTitle));
			memcpy(ConfigMgr::instance()->m_Config.szContent, pListConfig->szContent, sizeof(ConfigMgr::instance()->m_Config.szContent));

			memcpy(TaskInfo::ShareTaskInfo()->m_nTaskConfig, pListConfig->nTaskData, sizeof(pListConfig->nTaskData));

			// 拷贝房间信息，并刷新显示
			memcpy(ConfigMgr::instance()->m_Config.nServerEnter, pListConfig->nRoomEnter, sizeof(pListConfig->nRoomEnter));
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_REFRESHTOTALNUM, NULL);
			return true;
		}

		// 获取游戏服地址
	case SUB_GP_QUICK_GAMESERVER_ADR:
		{
			EntityMgr::instance()->getDispatch()->closeLoginSocket();

			assert(wDataSize == (sizeof(DWORD)<<1));
			if (wDataSize != (sizeof(DWORD)<<1))
			{
				return false;
			}

			long *lpValue = (long *)pBuffer;

			if (0 == lpValue[0] || 0 == lpValue[1])
			{
				// 没有可以连接的服务器
				CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_GAMELINK, CCInteger::create(2));
			}
			else
			{
				bool ret = EntityMgr::instance()->getDispatch()->connectGameServerAdr(lpValue[0], lpValue[1]);			//0为连接失败 1为连接成功  2为没有服务器			
				CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_GAMELINK,CCInteger::create(ret?1:0));
			}

			break;
		}
	}

	return true;
}
//?μ?≥???￠
bool MsgDispatch::onSocketMainSystem(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	return true;
}
//用户消息
bool MsgDispatch::onSocketMainUser(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	switch (pCommand->wSubCmdID)
	{
	case SUB_GP_OPERATE_SUCCESS:
		{
			//closeLoginSocket();
			CMD_GP_OperateSuccess *operateSuccess = (CMD_GP_OperateSuccess *)pBuffer;
			if(userServiceSubCmd == SUB_GP_MODIFY_LOGON_PASS)
			{
				if(operateSuccess->lResultCode == 0)
				{
					int result = 0;
					CCInteger* pPasswordResult = CCInteger::create(result);
					CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_PASSWORDUPDATE,pPasswordResult);
				}
			}
			break;
		}
	case SUB_GP_OPERATE_FAILURE:
		{
			break;
		}
	case SUB_GP_QUERY_INSURE_INFO:
		{
			break;
		}
	case SUB_GP_USER_INSURE_INFO:					// 保险柜资料     403
		return this->OnSocketWithInsureInfo(pBuffer, wDataSize);
	case SUB_GP_USER_INSURE_SUCCESS:				// 操作成功     405
		return this->OnSocketWithBankSucceed(pBuffer, wDataSize);
	case SUB_GP_USER_INSURE_FAILURE:				// 操作失败     406
		return this->OnSocketWithBankFailure(pBuffer, wDataSize);
	default:
		break;
	}

	return true;
}

//保险柜命令
bool MsgDispatch::OnTCPNetworkBankInsure(WORD wSubCmdID, void* pBuffer, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case SUB_GP_USER_INSURE_INFO:					// 保险柜资料     403
		return this->OnSocketWithInsureInfo(pBuffer, wDataSize);
	case SUB_GP_USER_INSURE_SUCCESS:				// 操作成功     405
		return this->OnSocketWithBankSucceed(pBuffer, wDataSize);
	case SUB_GP_USER_INSURE_FAILURE:				// 操作失败     406
		return this->OnSocketWithBankFailure(pBuffer, wDataSize);
	default:
		break;
	}
	return true;
}

//保险柜信息      add by wangjun 2014-12-10
bool MsgDispatch::OnSocketWithInsureInfo(void *buffer, WORD size)
{
	BYTE cbBuffer[sizeof(CMD_GP_UserInsureInfo)];
	memset(cbBuffer, 0 , sizeof(CMD_GP_UserInsureInfo));
	CMD_GP_UserInsureInfo *userInsureInfo = (CMD_GP_UserInsureInfo *)cbBuffer;
	memcpy(userInsureInfo, buffer, sizeof(CMD_GP_UserInsureInfo));
	m_wRevenueTake = userInsureInfo->wRevenueTake;				//税收
	m_wRevenueTransfer = userInsureInfo->wRevenueTransfer;			//税收
	m_wServerID = userInsureInfo->wServerID;					//房间标识
	m_dwlUserScore = userInsureInfo->lUserScore;				//用户豆豆
	m_dwGoldScore = userInsureInfo->lUserScore;				//用户豆豆
	m_dwlUserInsure = userInsureInfo->lUserInsure;				//保险柜豆豆
	m_dwlTransferPrerequisite = userInsureInfo->lTransferPrerequisite;		//转账条件
	g_GlobalUnits.getGolbalUserData()->lScore = m_dwlUserScore;
	g_GlobalUnits.getGolbalUserData()->lGoldEggs = 0;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_UPDATESCOREANDGOLDEGG,NULL);  //刷新钱和花费点
	CCNotificationCenter::sharedNotificationCenter()->postNotification("UserInsureInfo");
	return true;
}			

//查询保险柜成功      add by wangjun 2014-12-10
bool MsgDispatch::OnSocketWithBankSucceed(void *buffer, WORD size)
{
	BYTE cbBuffer[sizeof(CMD_GP_UserInsureSuccess)];
	memset(cbBuffer, 0 , sizeof(CMD_GP_UserInsureSuccess));
	CMD_GP_UserInsureSuccess *userInsureInfo = (CMD_GP_UserInsureSuccess *)cbBuffer;
	memcpy(userInsureInfo, buffer, sizeof(CMD_GP_UserInsureSuccess));
	m_dwlUserScore = userInsureInfo->lUserScore;				//用户豆豆
	m_dwlUserInsure = userInsureInfo->lUserInsure;				//保险柜豆豆
	g_GlobalUnits.getGolbalUserData()->lScore = m_dwlUserScore;
	g_GlobalUnits.getGolbalUserData()->lGoldEggs = 0;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_UPDATESCOREANDGOLDEGG,NULL);  //刷新钱和花费点
	MyNSString::wc2mbs(userInsureInfo->szDescribeString, sizeof(userInsureInfo->szDescribeString), szDescribeString);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("UserInsureInfo");
	return true;
}

//查询保险柜失败      add by wangjun 2014-12-10
bool MsgDispatch::OnSocketWithBankFailure(void *buffer, WORD size)
{
	BYTE cbBuffer[sizeof(CMD_GP_UserInsureFailure)];
	memset(cbBuffer, 0 , sizeof(CMD_GP_UserInsureFailure));
	CMD_GP_UserInsureFailure *userInsureInfo = (CMD_GP_UserInsureFailure *)cbBuffer;
	memcpy(userInsureInfo, buffer, sizeof(CMD_GP_UserInsureFailure));
	MyNSString::wc2mbs(userInsureInfo->szDescribeString, sizeof(userInsureInfo->szDescribeString), szDescribeString);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("UserInsureInfo");
	return true;
}	

//登录消息
bool MsgDispatch::OnSocketGameLogin(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	dispEntityMsg(pCommand,pBuffer,wDataSize,GBEVENT_NETWORK_LOGIN);
	return true;
}

//匿名登陆
void MsgDispatch::setAnonymous()
{
	setUserLogin("sys_user01","aaaAAA111get_notice!",true);
	m_bAnonymous = true;
}

//用户登陆
void MsgDispatch::setUserLogin(string account,string password,bool bAnonymous)
{
	string str = "setUserLogin";
	MyNSString::GBKToUTF8(str);
	CCLog("%s", str.c_str());

	//if (!bAnonymous)
	{
		m_szAccount = account;
		m_szPassword = password;
	}

	BYTE cbBuffer[2048];
	memset(cbBuffer, 0 , sizeof(CMD_MB_LogonAccounts));

	m_bAnonymous = bAnonymous;			
	// 登录标识
	m_wBehaviorFlags = (m_bStartType?(BEHAVIOR_LOGON_IMMEDIATELY|VIEW_MODE_PART):BEHAVIOR_LOGON_NORMAL);

	//变量定义
	CMD_MB_LogonAccounts *pLogonByAccounts = (CMD_MB_LogonAccounts *)cbBuffer;
	memset(pLogonByAccounts,0,sizeof(CMD_MB_LogonAccounts));

	pLogonByAccounts->dwPlazaVersion = VERSION_MOBILE;
	pLogonByAccounts->wModuleID = m_dwKindID;
	pLogonByAccounts->cbDeviceType = DEVICE_TYPE_ADNROID;

	memset(pLogonByAccounts->szAccounts, 0, sizeof(TCHART)*NAME_LEN);
	memset(pLogonByAccounts->szPassword, 0, sizeof(TCHART)*PASS_LEN);
	memset(pLogonByAccounts->szMobilePhone, 0, sizeof(TCHART)*LEN_MOBILE_PHONE);
	memset(pLogonByAccounts->szMachineID, 0, sizeof(TCHART)*LEN_MD5);

	char szMD5[33];
	memset(szMD5,0,sizeof(szMD5));
	CMD5Encrypt::EncryptData((unsigned char*)password.c_str(), szMD5);
	MyNSString::mbs2wc(account.c_str(), NAME_LEN, pLogonByAccounts->szAccounts);
	MyNSString::mbs2wc(szMD5, PASS_LEN, pLogonByAccounts->szPassword);
	string macAddr = this->getMacaddress();
	MyNSString::mbs2wc(macAddr.c_str(), macAddr.length(), pLogonByAccounts->szMachineID);

	memset(m_pPassWordMD5, 0, sizeof(TCHART)*LEN_MD5);
	memset(m_pMachineMD5, 0, sizeof(TCHART)*LEN_MD5);
	MyNSString::mbs2wc(szMD5, PASS_LEN, m_pPassWordMD5);
	MyNSString::mbs2wc(macAddr.c_str(), macAddr.length(), m_pMachineMD5);
	//int a = sizeof(ClientSerial);
	//发送数据包
	/*CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LogonByAccounts),sizeof(cbBuffer)-sizeof(CMD_GP_LogonByAccounts));
	DWORD dwGameKindID = GAMEKINDDDZ;
	Packet.AddPacket(&dwGameKindID,sizeof(dwGameKindID),DTP_GAME_KIND);*/

	//// DTP_COMPUTER_ID最后打包进来
	//   Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);

	//m_pClientLoginSock->sendData(MDM_MB_LOGON,SUB_MB_LOGON_ACCOUNTS,cbBuffer,sizeof(CMD_GP_LogonByAccounts)+Packet.GetDataSize());
	m_eDataType = CMD_Logon;
	m_pClientLoginSock->sendData(MDM_MB_LOGON,SUB_MB_LOGON_ACCOUNTS,pLogonByAccounts,sizeof(CMD_MB_LogonAccounts));

}

void MsgDispatch::getVersion()
{
	DWORD dwKindID = GAMEKINDDDZ;
	//m_pClientLoginSock->sendData(MDM_GP_LOGON, SUB_GP_LOGON_VERSION, &dwKindID, sizeof(dwKindID));
}

//用户注册
void MsgDispatch::setUserRegister(string account,string password,int nfaceId,int nGender, int visiter)
{
	m_szAccount = account;
	m_szPassword = password;
	m_bAnonymous = false;
	m_bRegLogin =  true;

	//账号注册
	BYTE cbBuffer[sizeof(CMD_MB_RegisterAccounts)];
	memset(cbBuffer, 0 , sizeof(CMD_MB_RegisterAccounts));
	CMD_MB_RegisterAccounts *accounts = (CMD_MB_RegisterAccounts *)cbBuffer;

	accounts->wModuleID		= m_dwKindID;
	accounts->dwPlazaVersion = VERSION_MOBILE;
	accounts->cbDeviceType	= DEVICE_TYPE_ADNROID;
	accounts->wFaceID  = nfaceId;
	accounts->cbGender = nGender;

	char szMD5[33];
	memset(szMD5,0,sizeof(szMD5));
	CMD5Encrypt::EncryptData((unsigned char*)password.c_str(), szMD5);
	MyNSString::mbs2wc(account.c_str(), NAME_LEN, accounts->szAccounts);
	MyNSString::mbs2wc(szMD5, PASS_LEN, accounts->szLogonPass);
	MyNSString::mbs2wc(account.c_str(), NAME_LEN, accounts->szNickName);
	MyNSString::mbs2wc(szMD5, PASS_LEN, accounts->szInsurePass);
	string macAddr = this->getMacaddress();
	MyNSString::mbs2wc(macAddr.c_str(), macAddr.length(), accounts->szMachineID);
	MyNSString::mbs2wc("12345678901", 12, accounts->szMobilePhone);

	memset(m_pPassWordMD5, 0, sizeof(TCHART)*LEN_MD5);
	memset(m_pMachineMD5, 0, sizeof(TCHART)*LEN_MD5);
	MyNSString::mbs2wc(szMD5, PASS_LEN, m_pPassWordMD5);
	MyNSString::mbs2wc(macAddr.c_str(), macAddr.length(), m_pMachineMD5);

	m_eDataType = CMD_Logon;

	int size = sizeof(CMD_MB_RegisterAccounts);
	CCLog("%d", size);

	m_pClientLoginSock->sendData(MDM_MB_LOGON,SUB_MB_REGISITER_ACCOUNTS,accounts,sizeof(CMD_MB_RegisterAccounts));
}

std::string& MsgDispatch::getMacaddress()
{
	//CCLOG("entitymgr address = %s",EntityMgr::instance()->getMacAddress());
	return EntityMgr::instance()->getMacAddress();
}

//发送登陆包
bool MsgDispatch::sendLoginPacket()
{	
	return true;
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();

	//获取信息
	BYTE cbBuffer[SOCKET_PACKET];
	memset(cbBuffer,0,SOCKET_PACKET);

	//tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();

	char szMD5[33];
	CMD5Encrypt::EncryptData((unsigned char*)m_szPassword.c_str(), szMD5);

	//登录数据包
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID		 = pUserData->dwUserID;
	pLogonByUserID->dwPlazaVersion	 = 0;
	pLogonByUserID->dwProcessVersion = 0;
	std::string plogonByPassWord = cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_PASSWORD");
	memcpy(pLogonByUserID->szPassWord,szMD5 ,PASS_LEN);

	//memcpy(pLogonByUserID->szPassWord,szMD5,PASS_LEN);

	//memcpy(pLogonByUserID->szPassWord,pUserData->szPassWord,PASS_LEN);

	//机器序列号
	//tagClientSerial ClientSerial;
	//g_GlobalUnits.GetClientSerial(ClientSerial);

	//发送数据包
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));

	m_pClientGameSock->sendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());

	return true;
}

//修改昵称
void MsgDispatch::modifyNickName(const char* nickName)
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();

	BYTE cbBuffer[2048];
	CMD_GP_MODIFYNICKNAME* modifyNickName=(CMD_GP_MODIFYNICKNAME *)cbBuffer;

	memset(modifyNickName,0,sizeof(CMD_GP_MODIFYNICKNAME));
	modifyNickName->dwUserID = pUserData->dwUserID;
	const char* pNickName = nickName;
	memcpy(modifyNickName->szNickName,pNickName,sizeof(modifyNickName->szNickName));

	//发送数据包
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_MODIFYNICKNAME),sizeof(cbBuffer)-sizeof(CMD_GP_MODIFYNICKNAME));
	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GP_MODIFY_NICKNAME, cbBuffer,sizeof(CMD_GP_MODIFYNICKNAME)+Packet.GetDataSize());
}

//第三方支付
void MsgDispatch::sendOrderInfo(const char* PayName,int chargeNum)
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();

	BYTE cbBuffer[2048];
	CMD_GP_CZORDER* pOrderInfo=(CMD_GP_CZORDER *)cbBuffer;
	pOrderInfo->dwUserID = pUserData->dwUserID;
	pOrderInfo->dwMoney = (unsigned int)chargeNum;
	memcpy(pOrderInfo->szPayName,PayName,sizeof(pOrderInfo->szPayName));

	//发送数据包
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_CZORDER),sizeof(cbBuffer)-sizeof(CMD_GP_CZORDER));

	if (m_loginState == enLogin_Server)
	{
		m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GF_CZ_ORDER, cbBuffer,sizeof(CMD_GP_CZORDER)+Packet.GetDataSize());
		return;
	}
	m_pClientGameSock->sendData(MDM_GF_USER, SUB_GF_CZ_ORDER, cbBuffer,sizeof(CMD_GP_CZORDER)+Packet.GetDataSize());
}

//修改头像
void MsgDispatch::modifyTouxiang(int nHand,int nSex)
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();
	BYTE cbBuffer[2048];
	CMD_GP_ModifyHead* pModifyTouxiang=(CMD_GP_ModifyHead*)cbBuffer;
	memset(pModifyTouxiang,0,sizeof(CMD_GP_ModifyHead));
	pModifyTouxiang->dwUserID = pUserData->dwUserID;
	pModifyTouxiang->nHead = nHand;
	pModifyTouxiang->nSex = nSex;
	//发送数据包
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_ModifyHead),sizeof(cbBuffer)-sizeof(CMD_GP_ModifyHead));
	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GP_MODIFY_HEAD, cbBuffer,sizeof(CMD_GP_ModifyHead)+Packet.GetDataSize());
}

//紫金岛卡
void MsgDispatch::isLnadCardRecarge(const char* cardNum,const char* cardPass)
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();
	BYTE cbBuffer[2048];
	CMD_GP_ISLANDCARD* pLandCard = (CMD_GP_ISLANDCARD*)cbBuffer;
	memset(pLandCard,0,sizeof(CMD_GP_ISLANDCARD));
	pLandCard->dwGameKindID = GAMEKINDDDZ;
	pLandCard->dwUserID = pUserData->dwUserID;
	memcpy(pLandCard->szCardNo,cardNum,sizeof(pLandCard->szCardNo));
	memcpy(pLandCard->szCardPwd,cardPass,sizeof(pLandCard->szCardPwd));
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_ISLANDCARD),sizeof(cbBuffer)-sizeof(CMD_GP_ISLANDCARD));
	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GF_ISLAND, cbBuffer,sizeof(CMD_GP_ISLANDCARD)+Packet.GetDataSize());
}

void MsgDispatch::phoneCardRechange(const char* cardType,const char* cardFree,const char* cardNum,const char* cardPass)
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();
	BYTE cbBuffer[2048];
	CMD_GP_SZFCARD* pSZcard = (CMD_GP_SZFCARD*)cbBuffer;
	memset(pSZcard,0,sizeof(CMD_GP_SZFCARD));
	pSZcard->dwUserID = pUserData->dwUserID;
	pSZcard->dwCardType = atoi(cardType);
	pSZcard->dwCardFee = atoi(cardFree);
	memcpy(pSZcard->szCardNo,cardNum,sizeof(pSZcard->szCardNo));
	memcpy(pSZcard->szCardPwd,cardPass,sizeof(pSZcard->szCardPwd));
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_SZFCARD),sizeof(cbBuffer)-sizeof(CMD_GP_SZFCARD));
	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GF_SZFCARD, cbBuffer,sizeof(CMD_GP_SZFCARD)+Packet.GetDataSize());
}

//获得登陆奖励
void MsgDispatch::getLoginAward()
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();
	DWORD cbBuffer[2];
	cbBuffer[0] = pUserData->dwUserID;
	cbBuffer[1] = GAMEKINDDDZ;
	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GP_GETLOGONPRIZE, cbBuffer,sizeof(cbBuffer));
}

void MsgDispatch::modifyPassWord(string oldPassword,string newPassword)
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();
	BYTE cbBuffer[2048];
	CMD_GP_ModifyLogonPass* modifyPassWord=(CMD_GP_ModifyLogonPass *)cbBuffer;
	memset(modifyPassWord,0,sizeof(CMD_GP_ModifyLogonPass));
	modifyPassWord->dwUserID = pUserData->dwUserID;
	char szOldPasswordMD5[33];
	CMD5Encrypt::EncryptData((unsigned char*)oldPassword.c_str(), szOldPasswordMD5);
	char szNewPasswordMD5[33];
	CMD5Encrypt::EncryptData((unsigned char*)newPassword.c_str(), szNewPasswordMD5);

	MyNSString::mbs2wc(szOldPasswordMD5, sizeof(szOldPasswordMD5), modifyPassWord->szScrPassword);
	MyNSString::mbs2wc(szNewPasswordMD5, sizeof(szNewPasswordMD5), modifyPassWord->szDesPassword);
	//发送数据包
	userServiceSubCmd = SUB_GP_MODIFY_LOGON_PASS;
	m_pClientLoginSock->sendData(MDM_GP_USER_SERVICE, SUB_GP_MODIFY_LOGON_PASS, cbBuffer,sizeof(CMD_GP_ModifyLogonPass));
}

//领取任务奖励
void MsgDispatch::getDarlyAward(int taskID)
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();
	BYTE cbBuffer[2048];
	CMD_GP_GetDailyPrize* getDailyPrize = (CMD_GP_GetDailyPrize*)cbBuffer;
	memset(getDailyPrize,0,sizeof(CMD_GP_GetDailyPrize));
	getDailyPrize->dwUserID = pUserData->dwUserID;
	getDailyPrize->dwGameKindID = GAMEKINDDDZ;
	getDailyPrize->dwPrizeID = (unsigned int)taskID;
	getDailyPrize->nSubCmd = 1;
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_GetDailyPrize),sizeof(cbBuffer)-sizeof(CMD_GP_GetDailyPrize));
	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GP_TASKDAILYDATA, cbBuffer,sizeof(CMD_GP_GetDailyPrize)+Packet.GetDataSize());
}

void MsgDispatch::getDownLoadAward(int gameID,int subcmd)
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();
	if(pUserData==NULL){
		return;
	}
	BYTE cbBuffer[2048];
	SDownloadGamePrize* sDownLoadDate = (SDownloadGamePrize*)cbBuffer;
	memset(sDownLoadDate,0,sizeof(SDownloadGamePrize));
	sDownLoadDate->dwGameKindID = GAMEKINDDDZ;
	sDownLoadDate->dwUserID = pUserData->dwUserID;
	sDownLoadDate->nIndex = gameID;
	sDownLoadDate->nSubCmd = subcmd;
	CSendPacketHelper Packet(cbBuffer+sizeof(SDownloadGamePrize),sizeof(cbBuffer)-sizeof(SDownloadGamePrize));
	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GP_DOWNLOADGAMEGOLD, cbBuffer,sizeof(SDownloadGamePrize)+Packet.GetDataSize());
}

//完善注册
void MsgDispatch::overRegist(string newAccount,string newPassword)
{
	tagGlobalUserData* pUserData = g_GlobalUnits.getGolbalUserData();
	BYTE cbBuffer[2048];
	CMD_GP_Visitor2Player* sVisitor2Player = (CMD_GP_Visitor2Player*)cbBuffer;
	memset(sVisitor2Player,0,sizeof(CMD_GP_Visitor2Player));
	sVisitor2Player->dwUserID = pUserData->dwUserID;

	char szMD5[33];
	std::string plogonByPassWord = cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_PASSWORD");
	CMD5Encrypt::EncryptData((unsigned char*)plogonByPassWord.c_str(), szMD5);
	memcpy(sVisitor2Player->szPassWord,szMD5 ,PASS_LEN);

	char szMD5New[33];
	CMD5Encrypt::EncryptData((unsigned char*)newPassword.c_str(), szMD5New);
	memcpy(sVisitor2Player->szPassWordNew,szMD5New ,PASS_LEN);

	memcpy(sVisitor2Player->szAccounts, newAccount.c_str(), sizeof(sVisitor2Player->szAccounts));
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_Visitor2Player),sizeof(cbBuffer)-sizeof(CMD_GP_Visitor2Player));
	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GP_VISITOR_TO_PALYER, cbBuffer,sizeof(CMD_GP_Visitor2Player)+Packet.GetDataSize());
}

void MsgDispatch::getRelieve(int nUserID)
{
	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GP_GET_RELIEVE, &nUserID,sizeof(nUserID));
}

//发送赠送包
void MsgDispatch::sendScoreGiftPacket(const char* szAccount,long lValue)
{
	CM_GF_SCOREGIFT ScoreGiftUser;
	memset(&ScoreGiftUser,0,sizeof(ScoreGiftUser));
	ScoreGiftUser.dwUserID = g_GlobalUnits.getGolbalUserData()->dwUserID;
	ScoreGiftUser.lValue   = lValue;
	memcpy(ScoreGiftUser.szToUserName, szAccount, sizeof(ScoreGiftUser.szToUserName));

	char szMD5[33];
	CMD5Encrypt::EncryptData((unsigned char*)m_szPassword.c_str(), szMD5);
	memcpy(ScoreGiftUser.szPassword, szMD5,sizeof(ScoreGiftUser.szPassword));

	BYTE szSendBuffer[2048];
	CDataArchive SendBuffer(szSendBuffer,2048);
	SendBuffer.Write(&ScoreGiftUser,sizeof(CM_GF_SCOREGIFT));

	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GF_GIFT, (void*)szSendBuffer,SendBuffer.GetBufferOffset());
}

//发送金币话费领取包
void MsgDispatch::sendChargePacket(int ntype,const char* des)
{
	//发送信息
	CMD_GF_Bank ChargeUser;
	memset(&ChargeUser,0,sizeof(ChargeUser));

	ChargeUser.dwUserID = g_GlobalUnits.getGolbalUserData()->dwUserID;
	ChargeUser.dwGameKindID = GAMEKINDDDZ;
	//通过lValue来区分对话话费还是金币 0话费,1金币
	ChargeUser.lValue = ntype;

	memcpy(ChargeUser.szPassword, des,sizeof(ChargeUser.szPassword));

	CCLog("%s",m_szPassword.c_str());

	char szMD5[33];
	CMD5Encrypt::EncryptData((unsigned char*)m_szPassword.c_str(), szMD5);
	memcpy(ChargeUser.szRealPsd, szMD5,sizeof(ChargeUser.szRealPsd));


	BYTE szSendBuffer[2048];
	CDataArchive SendBuffer(szSendBuffer,2048);
	SendBuffer.Write(&ChargeUser,sizeof(CMD_GF_Bank));

	m_pClientLoginSock->sendData(MDM_GP_USER, SUB_GF_BANK_GET, (void*)szSendBuffer,SendBuffer.GetBufferOffset());
}

//∑￠à?≈≈?”????
void MsgDispatch::sendQueuePacket(int cbQueueCell)
{
	CMD_GR_JoinMatch JoinMatch;
	memset(&JoinMatch,0,sizeof(JoinMatch));

	// 0 第一次排队
	// 1 不允许服务器帮你排队
	// 2 快速排队

	JoinMatch.wJoin = 0;
	JoinMatch.lCellScore = cbQueueCell;

	BYTE szSendBuffer[2048];
	CDataArchive SendBuffer(szSendBuffer,2048);
	SendBuffer.Write(&JoinMatch,sizeof(CMD_GR_JoinMatch));

	CCLOG("Queued requests! file(%s) line(%d)",__FILE__, __LINE__);

	m_pClientGameSock->sendData(MDM_GR_USER, SUB_GR_USER_START_QUEUE_REQ, (void*)szSendBuffer,SendBuffer.GetBufferOffset());
}

//获取服务器配置信息
void MsgDispatch::sendGetConfigPacket(int nVersion)
{
	CMD_GP_GetConfig config;
	config.dwGameKindID = GAMEKINDDDZ;
	config.dwVersion = nVersion;

	m_pClientLoginSock->sendData(MDM_GP_LOGON, SUB_GP_GET_PZINFO, (void*)&config, sizeof(config));
}
//找回密码
void MsgDispatch::findPassword(const char* szAccount)
{
	//char buf[50];
	//memset(buf, 0, 50);
	//utf::utf_gb_convert("utf-8", "gb2312", buf,50, const_cast<char*>(szAccount), strlen(szAccount));

	CMD_GP_GetPassword GetPassword;
	memcpy(GetPassword.szAccounts, szAccount, sizeof(GetPassword.szAccounts));

	std::string str = getMacaddress();
	memcpy(GetPassword.szMobileCode, str.c_str(), str.length());

	BYTE szSendBuffer[2048];
	CDataArchive SendBuffer(szSendBuffer,2048);
	SendBuffer.Write(&GetPassword,sizeof(GetPassword));

	m_pClientLoginSock->sendData(MDM_GP_LOGON, SUB_GP_GET_PASSWORD, (void*)szSendBuffer,SendBuffer.GetBufferOffset());

}

//发送数据
void MsgDispatch::sendSocketDate(WORD wMainCmdID,WORD wSubCmdID)
{
	m_pClientGameSock->sendData(wMainCmdID,wSubCmdID);
}

//发送数据
void MsgDispatch::sendSocketDate(WORD wMainCmdID,WORD wSubCmdID, void* pData, WORD wDataSize)
{
	m_pClientGameSock->sendData(wMainCmdID,wSubCmdID,pData,wDataSize);
}

//网络命令消息发送
// 网络验证
void MsgDispatch::SendPacketWithCompilatio(int tag)
{
	BYTE cbBuffer[sizeof(TCP_Validate)];
	memset(cbBuffer, 0 , sizeof(TCP_Validate));
	TCP_Validate *validate = (TCP_Validate *)cbBuffer;
	Common_Compilation(validate->szValidateKey);
	if(tag == 0){
		m_pClientLoginSock->sendData(MDM_KN_COMMAND, SUB_KN_VALIDATE_SOCKET, (void*)validate, sizeof(TCP_Validate));
	}else{
		m_pClientGameSock->sendData(MDM_KN_COMMAND, SUB_KN_VALIDATE_SOCKET, (void*)validate, sizeof(TCP_Validate));
	}
	CCLog("		发送验证");
}

bool MsgDispatch::connectLoginServer()
{
	CCLog("connectLoginServer");

	if (m_pClientLoginSock->isConectServer())
	{
		m_pClientLoginSock->closeSocket();
	}

	bool ret = m_pClientLoginSock->connectGameServer("120.76.216.167", 8500);
	//bool ret = m_pClientLoginSock->connectGameServer("218.76.35.163", 9001);
	//bool ret = m_pClientLoginSock->connectGameServer("login1.91zjd.com", 9001);
	//bool ret = m_pClientLoginSock->connectGameServer("127.0.0.1", 9001);
	//bool ret = m_pClientLoginSock->connectGameServer(IP_LOGON, PORT_TEMP);
	if (!ret)
	{
		CCLOG("connect login server faild! file(%s) line(%d)",__FILE__, __LINE__);
		return  false;
	}
	SendPacketWithCompilatio(0);
	return true;
}

//进入相应桌子
bool MsgDispatch::connectGameServer(int roomIndex)
{
	if (m_pClientGameSock->isConectServer())
	{
		m_pClientGameSock->closeSocket();
	}
	tagGameServer server = m_ServerListMgr.getGameServerByIndex(roomIndex);
	char ip[64];
	MyNSString::wc2mbs(server.szServerAddr, sizeof(server.szServerAddr), ip);
	unsigned short port = server.wServerPort;
	CCLOG("%d", port);
	bool ret = m_pClientGameSock->connectGameServer(ip, port);
	if (!ret)
	{
		CCLOG("connect game server faild! file(%s) line(%d)",__FILE__, __LINE__);
		return  false;
	}
	SendPacketWithCompilatio(1);
	return true;
}

//快速登陆房间      add by wangjun 2014-12-10
bool MsgDispatch::connectGameServer()
{
	if (m_pClientGameSock->isConectServer())
	{
		m_pClientGameSock->closeSocket();
	}
	tagGameServer server;
	for(int roomIndex = 0 ; roomIndex < g_GlobalUnits.m_nOnlineCount ; roomIndex++)
	{
		server = m_ServerListMgr.getGameServerByIndex(roomIndex);
		if(m_dwGoldScore > server.lMinServerScore)
		{
			break;
		}
	}
	char ip[64] = {0};
	int isie = sizeof(server.szServerAddr);
	MyNSString::wc2mbs(server.szServerAddr, sizeof(server.szServerAddr)/sizeof(TCHART), ip);
	unsigned short port = server.wServerPort;
	bool ret = m_pClientGameSock->connectGameServer(ip, port);
	CCLOG("============================");
	CCLOG("gameserver ip = %s", ip);
	CCLOG("gameserver port = %d", port);
	CCLOG("============================");
	if (!ret)
	{
		CCLOG("connect game server faild! file(%s) line(%d)",__FILE__, __LINE__);
		return  false;
	}
	SendPacketWithCompilatio(1);
	return true;
}

//登陆房间      add by wangjun 2014-12-10
void MsgDispatch::SendPacketWithEnterRoomPageCount(WORD count)
{
	// 房间登录
	BYTE cbBuffer[sizeof(CMD_GR_LogonMobile)];
	memset(cbBuffer, 0 , sizeof(CMD_GR_LogonMobile));
	CMD_GR_LogonMobile *lm = (CMD_GR_LogonMobile *)cbBuffer;

	lm->wGameID			= m_dwKindID;					// 游戏标识
	lm->dwProcessVersion = VERSION_FRAME;                 // 手机版本
	lm->wBehaviorFlags	= m_wBehaviorFlags;				// 行为标识
	lm->wPageTableCount	= count;						// 页数
	lm->dwUserID			= m_dwUserID;					// 用户id
	lm->cbDeviceType		= m_cbDeviceType;				// 设备类型

	//MyNSString::mbs2wc(m_szPassword.c_str(), (int)LEN_PASSWORD, lm.szPassword);
	memcpy(lm->szPassword, m_pPassWordMD5, sizeof(TCHART)*LEN_MD5);
	CCLog("%d", sizeof(CMD_GR_LogonMobile));
	m_pClientGameSock->sendData(MDM_GR_LOGON, SUB_GR_LOGON_MOBILE, (void*)lm, sizeof(CMD_GR_LogonMobile));
	// 消息状态
	m_eDataType = CMD_Room;
	setLoginState(enGame_Server);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_GAMELINK,CCInteger::create(1));
}

//连接游戏服务器
bool MsgDispatch::connectGameServerAdr(DWORD dwAdrIP, WORD wPort)
{
	in_addr addr;
	addr.s_addr = dwAdrIP;
	char* ip = inet_ntoa(addr);

	bool ret = m_pClientGameSock->connectGameServer(ip, wPort);

	setLoginState(enGame_Server);
	m_eDataType = CMD_Room;
	if (!ret)
	{
		CCLOG("connect game server failed! file(%s) line(%d)",__FILE__, __LINE__);
	}
	CCLOG("------------------------------connect game server success!---------------------------------------");

	return ret;
}
//发送数据
void MsgDispatch::sendSocketDate(WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_pClientGameSock->sendData(MDM_GF_GAME,wSubCmdID,pData,wDataSize);
}

//发送表情、文字
void MsgDispatch::sendFrameDate(WORD wSubCmdID, void * pData, WORD wDataSize)
{
	m_pClientGameSock->sendData(MDM_GF_FRAME,wSubCmdID,pData,wDataSize);
}

//发送数据
void MsgDispatch::sendSocketDate(WORD wSubCmdID)
{
	m_pClientGameSock->sendData(MDM_GF_GAME,wSubCmdID);
}


//获取全服总人数
DWORD MsgDispatch::getServerOnLineCount()
{
	return m_ServerListMgr.getServerOnLineCount();
}
void MsgDispatch::closeLoginSocket()
{
	m_pClientLoginSock->closeSocket();

	m_dwRecvPacketCount = 0;
	m_wRecvSize = 0;
	memset(m_cbRecvBuff, 0, 81920);
}

//关闭游戏服务连接
void MsgDispatch::closeGameSocket()
{
	m_pClientGameSock->closeSocket();

	m_dwRecvPacketCount = 0;
	m_wRecvSize = 0;
	memset(m_cbRecvBuff, 0, 81920);

	setLoginState(enLogin_Server);
}

int MsgDispatch::getLevelbyScore(LONG lScore)
{
	int nLevle = 0;
	for (int i = 0; i < CountArray(m_lUserLevel); i++)
	{
		if (lScore >= m_lUserLevel[i])
		{
			nLevle = i + 1;
		}
	}
	return  nLevle;
}

int MsgDispatch::getBaseCell(int type,int nLevel)   //获取倍率
{
	UserLevel::iterator iter = m_UserLevelList.begin();
	for (; iter != m_UserLevelList.end(); iter++)
	{
		if ((*iter).lInfoType == type)
		{
			return  (*iter).tagUserLeve[nLevel].lUserLevel;
		}
	}
	return 0;
}

//发送游戏规则      add by wangjun 2014-12-10
void MsgDispatch::SendPacketWithGameOption()
{
	BYTE cbBuffer[sizeof(CMD_GF_GameOption)];
	memset(cbBuffer, 0 , sizeof(CMD_GF_GameOption));
	CMD_GF_GameOption *gameOption = (CMD_GF_GameOption *)cbBuffer;
	gameOption->cbAllowLookon=false;
	gameOption->dwFrameVersion=INVALID_DWORD;
	gameOption->dwClientVersion=INVALID_DWORD;

	m_pClientGameSock->sendData(MDM_GF_FRAME, SUB_GF_GAME_OPTION, gameOption, sizeof(CMD_GF_GameOption));
	CCLog("		发送游戏规则");
}

//获取用户 或申请用户信息
void MsgDispatch::SendPacketWithRequestUserInfo(DWORD dwUserID, WORD wTableID)
{
	BYTE cbBuffer[sizeof(CMD_GR_UserInfoReq)];
	memset(cbBuffer, 0 , sizeof(CMD_GR_UserInfoReq));
	CMD_GR_UserInfoReq *info = (CMD_GR_UserInfoReq *)cbBuffer;

	info->dwUserIDReq=dwUserID;
	info->wTablePos=wTableID;

	m_pClientGameSock->sendData(MDM_GR_USER, SUB_GR_USER_INFO_REQ, info, sizeof(CMD_GR_UserInfoReq));

	CCLog("		发送ID请求");
}

void MsgDispatch::SendPacketWithRequestChairUserInfo(WORD wTableID, WORD wChairID)
{
	BYTE cbBuffer[sizeof(CMD_GR_ChairUserInfoReq)];
	memset(cbBuffer, 0 , sizeof(CMD_GR_ChairUserInfoReq));
	CMD_GR_ChairUserInfoReq *info = (CMD_GR_ChairUserInfoReq *)cbBuffer;

	info->wTableID=wTableID;
	info->wChairID=wChairID;

	m_pClientGameSock->sendData(MDM_GR_USER, SUB_GR_USER_CHAIR_INFO_REQ, info, sizeof(CMD_GR_ChairUserInfoReq));

	CCLog("		发送ID请求");
}

//请求发送自己桌子的用户信息
void MsgDispatch::SendPacketWithRequestMyTableUserInfo(int playerNum)
{
	for(WORD chairID = 0 ; chairID < playerNum ; chairID++)
	{
		this->SendPacketWithRequestChairUserInfo(m_wTableID, chairID);
	}
}

//申请换桌
void MsgDispatch::SendPacketWithChangeTable()
{
	m_pClientGameSock->sendData(MDM_GR_USER, SUB_GR_USER_CHAIR_REQ);
}

void MsgDispatch::SendPacketWithUserStatus(BYTE status)
{
	BYTE cbBuffer[sizeof(CMD_GR_UserStatus)];
	memset(cbBuffer, 0 , sizeof(CMD_GR_UserStatus));
	CMD_GR_UserStatus *ready = (CMD_GR_UserStatus *)cbBuffer;

	ready->dwUserID = m_dwUserID;
	ready->UserStatus.wChairID = m_wChairID;
	ready->UserStatus.wTableID = m_wTableID;
	ready->UserStatus.cbUserStatus = status;

	m_pClientGameSock->sendData(MDM_GF_FRAME, SUB_GF_USER_READY, ready, sizeof(CMD_GR_UserStatus));
	EntityMgr::instance()->roomFrame()->setGameIsStart(true);
}

//大厅保险柜操作
void MsgDispatch::SendPacketWithQueryBankInfo()
{
	BYTE cbBuffer[sizeof(CMD_GP_QueryInsureInfo)];
	memset(cbBuffer, 0 , sizeof(CMD_GP_QueryInsureInfo));
	CMD_GP_QueryInsureInfo *info = (CMD_GP_QueryInsureInfo *)cbBuffer;

	info->dwUserID=m_dwUserID;
	memcpy(info->szPassword, m_pPassWordMD5, sizeof(CMD_GP_QueryInsureInfo)-sizeof(info->dwUserID));

	if (!m_pClientLoginSock->isConectServer())
	{
		this->connectLoginServer();
		//m_pClientLoginSock->connectGameServer(IP_LOGON, PORT_TEMP);
	}
	m_pClientLoginSock->sendData(MDM_GP_USER_SERVICE, SUB_GP_QUERY_INSURE_INFO, info, sizeof(CMD_GP_QueryInsureInfo));
}

void MsgDispatch::SendPacketWithDeposit(SCORE score)
{
	BYTE cbBuffer[sizeof(CMD_GP_UserSaveScore)];
	memset(cbBuffer, 0 , sizeof(CMD_GP_UserSaveScore));
	CMD_GP_UserSaveScore *info = (CMD_GP_UserSaveScore *)cbBuffer;

	info->dwUserID=m_dwUserID;
	info->lSaveScore = score;
	memcpy(info->szMachineID, m_pMachineMD5, sizeof(CMD_GP_UserSaveScore)-sizeof(info->dwUserID)-sizeof(info->lSaveScore));

	if (!m_pClientLoginSock->isConectServer())
	{
		this->connectLoginServer();
		//m_pClientLoginSock->connectGameServer(IP_LOGON, PORT_TEMP);
	}
	m_pClientLoginSock->sendData(MDM_GP_USER_SERVICE, SUB_GP_USER_SAVE_SCORE, info, sizeof(CMD_GP_UserSaveScore));
}

void MsgDispatch::SendPacketWithWithdraw(SCORE score, string password)
{
	BYTE cbBuffer[sizeof(CMD_GP_UserTakeScore)];
	memset(cbBuffer, 0 , sizeof(CMD_GP_UserTakeScore));
	CMD_GP_UserTakeScore *info = (CMD_GP_UserTakeScore *)cbBuffer;

	info->dwUserID=m_dwUserID;
	info->lTakeScore = score;
	memcpy(info->szMachineID, m_pMachineMD5, sizeof(TCHART)*LEN_MACHINE_ID);

	char szMD5[33];
	memset(szMD5,0,sizeof(szMD5));
	CMD5Encrypt::EncryptData((unsigned char*)password.c_str(), szMD5);
	MyNSString::mbs2wc(szMD5, PASS_LEN, info->szPassword);

	if (!m_pClientLoginSock->isConectServer())
	{
		this->connectLoginServer();
		//m_pClientLoginSock->connectGameServer(IP_LOGON, PORT_TEMP);
	}
	m_pClientLoginSock->sendData(MDM_GP_USER_SERVICE, SUB_GP_USER_TAKE_SCORE, info, sizeof(CMD_GP_UserTakeScore));
}

void MsgDispatch::SendPacketWithSendScore(string nickname, SCORE score, string password, BYTE byNickName)
{

	BYTE cbBuffer[sizeof(CMD_GP_UserTransferScore)];
	memset(cbBuffer, 0 , sizeof(CMD_GP_UserTransferScore));
	CMD_GP_UserTransferScore *info = (CMD_GP_UserTransferScore *)cbBuffer;

	info->dwUserID=m_dwUserID;
	info->cbByNickName = byNickName;
	info->lTransferScore = score;
	MyNSString::mbs2wc(nickname.c_str(), LEN_NICENAME, info->szNickName);

	char szMD5[33];
	memset(szMD5,0,sizeof(szMD5));
	CMD5Encrypt::EncryptData((unsigned char*)password.c_str(), szMD5);
	MyNSString::mbs2wc(szMD5, PASS_LEN, info->szPassword);

	memcpy(info->szMachineID, m_pMachineMD5, sizeof(TCHART)*LEN_MACHINE_ID);

	if (!m_pClientLoginSock->isConectServer())
	{
		this->connectLoginServer();
		//m_pClientLoginSock->connectGameServer(IP_LOGON, PORT_TEMP);
	}
	m_pClientLoginSock->sendData(MDM_GP_USER_SERVICE, SUB_GP_USER_TRANSFER_SCORE, info, sizeof(CMD_GP_UserTransferScore));
}

/*********用户请求**********/
//请求起立
void MsgDispatch::SendPacketWithPerformStandup(WORD wTableID, WORD wChairID, BYTE cbForceLeave)
{
	if(wTableID == INVALID_TABLE)
	{
		wTableID = m_wTableID;
	}
	if(wChairID == INVALID_CHAIR)
	{
		wChairID = m_wChairID;
	}
	if(wTableID == INVALID_TABLE || wChairID == INVALID_CHAIR)
	{
		return;
	}

	//if(m_cbStatus != US_SIT)
	//{
	//	return;
	//}

	BYTE cbBuffer[sizeof(CMD_GR_UserStandUp)];
	memset(cbBuffer, 0 , sizeof(CMD_GR_UserStandUp));
	CMD_GR_UserStandUp *info = (CMD_GR_UserStandUp *)cbBuffer;

	info->wTableID=wTableID;
	info->wChairID = wChairID;
	info->cbForceLeave = cbForceLeave;

	m_pClientGameSock->sendData(MDM_GR_USER, SUB_GR_USER_STANDUP, info, sizeof(CMD_GR_UserStandUp));
}

