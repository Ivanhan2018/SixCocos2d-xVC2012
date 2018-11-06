
#include "RoomFrame.h"
#include "common/CMD_Game.h"
#include "common/CMD_Plaza.h"
#include "entity/EntityMgr.h"
#include "globalUnits/GlobalUnits.h"
#include "common/GlobalFrame.h"
#include "common/GlobalDef.h"
#include "common/GlobalField.h"
#include "ans/utf-8.h"
#include "common/CMD_GameServer.h"
#include "common/CMD_LogonServer.h"
#include "common/MyNSString.h"
#include "common/DBHandler.h"
#include "ddz/SceneTableInterfaceLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

RoomFrame::RoomFrame()
	:m_pMeUserItem(NULL)
{
	GBEVENT_ARG_REGISTER(GBEVENT_NETWORK_ROOM, RoomFrame::onRoomMsg);
	GBEVENT_ARG_REGISTER(GBEVENT_NETWORK_GAME, RoomFrame::onGameMsg);

	m_nTable = INVALID_CHAIR;
	m_nChair = INVALID_TABLE;
	m_cbStatus = US_NULL;
	gameIsStart = false;
}

RoomFrame::~RoomFrame()
{
	GBEVENT_ARG_UNREGISTER(GBEVENT_NETWORK_ROOM, RoomFrame::onRoomMsg);
	GBEVENT_ARG_UNREGISTER(GBEVENT_NETWORK_GAME, RoomFrame::onGameMsg);
}

void RoomFrame::reset()
{
	UsrDateMap::iterator iter =  m_UserDateList.begin();
	for (; iter != m_UserDateList.end();  iter++)
	{
		delete iter->second;
	}

	m_UserDateList.clear();
	m_pMeUserItem = NULL;
}

//发送游戏服务器登陆包
void RoomFrame::sendLoginPacket()
{
	EntityMgr::instance()->getDispatch()->sendLoginPacket();
}

void RoomFrame::sendQueuePacket(int cbQueueCell)
{
	EntityMgr::instance()->getDispatch()->sendQueuePacket(cbQueueCell);
}

void RoomFrame::onRoomMsg(GBEventConstArg& arg)
{
	tagCmdBuffer& tag = (tagCmdBuffer&)arg;
	CMD_Command* pCommand = &tag.command;
	OnEventTcpRoomRead(pCommand,tag.dateBuffer,tag.nDataSize);
}

//游戏消息处理 add by wangjun 2014-12-15
void RoomFrame::onGameMsg(GBEventConstArg& arg)
{
	tagCmdBuffer& tag = (tagCmdBuffer&)arg;
	CMD_Command* pCommand = &tag.command;
	OnEventTcpGameRead(pCommand,tag.dateBuffer,tag.nDataSize);
}

//原来的游戏信息处理
/*
bool  RoomFrame::OnEventTcpGameRead(CMD_Command* pCommand,void* pData,WORD wDataSize)
{
switch (pCommand->wMainCmdID)
{
case MDM_GR_LOGON:			//登录消息
{
//CCLOG("登陆消息! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameLogin(pCommand,pData,wDataSize);
}
case MDM_GR_USER:			//用户消息
{
//CCLOG("用户消息! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameUser(pCommand,pData,wDataSize);
}
case MDM_GR_INFO:			//配置信息
{
//CCLOG("配置消息! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameInfo(pCommand,pData,wDataSize);
}
case MDM_GR_STATUS:			//状态信息
{
//CCLOG("状态消息! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameStatus(pCommand,pData,wDataSize);
}
case MDM_GR_SYSTEM:			//系统消息
{
//CCLOG("系统消息! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameSystem(pCommand,pData,wDataSize);
}
case MDM_GR_SERVER_INFO:	//房间信息
{
//CCLOG("房间消息! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameServerInfo(pCommand,pData,wDataSize);
}
case MDM_GF_GAME:			//游戏消息
{
//CCLOG("游戏消息! file(%s) line(%d)",__FILE__, __LINE__);

return OnGameMessage(pCommand->wSubCmdID,pData,wDataSize);
}
case MDM_GF_FRAME:			//框架消息
{
//CCLOG("框架消息! file(%s) line(%d)",__FILE__, __LINE__);
return OnFrameMessage(pCommand->wSubCmdID,pData,wDataSize);
}
}
return  true;
}
*/

//把原来的游戏消息分成房间登陆消息和游戏消息			add by wangjun
bool  RoomFrame::OnEventTcpGameRead(CMD_Command* pCommand,void* pData,WORD wDataSize)
{

	switch (pCommand->wMainCmdID)
	{
	case MDM_GR_STATUS:			//状态信息
		{
			//CCLOG("状态消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameStatus(pCommand,pData,wDataSize);
		}
	case MDM_GR_SYSTEM:			//系统消息
		{
			//CCLOG("系统消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameSystem(pCommand,pData,wDataSize);
		}
	case MDM_GR_SERVER_INFO:	//房间信息
		{
			//CCLOG("房间消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameServerInfo(pCommand,pData,wDataSize);
		}
	case MDM_GF_GAME:			//游戏消息
		{
			//CCLOG("游戏消息! file(%s) line(%d)",__FILE__, __LINE__);

			return OnGameMessage(pCommand->wSubCmdID,pData,wDataSize);
		}
	case MDM_GF_FRAME:			//框架消息
		{
			//CCLOG("框架消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnFrameMessage(pCommand->wSubCmdID,pData,wDataSize);
		}
	}
	return  true;
}

bool  RoomFrame::OnEventTcpRoomRead(CMD_Command* pCommand,void* pData,WORD wDataSize)
{
	switch (pCommand->wMainCmdID)
	{
	case MDM_GR_LOGON:			//登录消息				1
		{
			//CCLOG("登陆消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameLogin(pCommand,pData,wDataSize);
		}
	case MDM_GR_CONFIG:			//配置信息				2
		{
			//CCLOG("配置消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameInfo(pCommand,pData,wDataSize);
		}
	case MDM_GR_USER:			//用户消息				3
		{
			//CCLOG("用户消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameUser(pCommand,pData,wDataSize);
		}
	case MDM_GR_STATUS:			//配置信息				4
		{
			//CCLOG("状态消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameStatus(pCommand,pData,wDataSize);
		}
	case MDM_GF_GAME:			//游戏命令				200
		{
			//CCLOG("游戏消息! file(%s) line(%d)",__FILE__, __LINE__);

			return OnGameMessage(pCommand->wSubCmdID,pData,wDataSize);
		}
	case MDM_GF_FRAME:			//框架命令				100
		{
			//CCLOG("框架消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnFrameMessage(pCommand->wSubCmdID,pData,wDataSize);
		}
	case MDM_GR_INSURE:			//保险柜命令			5
		{
			return true;
		}
	case MDM_GR_MANAGE:			//管理命令				6
		{
			//CCLOG("房间消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameServerInfo(pCommand,pData,wDataSize);
			return true;
		}
	case MDM_CM_SYSTEM:			//系统命令				1000
		{
			//CCLOG("系统消息! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameSystem(pCommand,pData,wDataSize);
		}
	case MDM_KN_COMMAND:			//内核命令			0
		{
			return true;
		}
	}
	return  true;
}


//登录消息
bool RoomFrame::OnSocketGameLogin(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	switch (pCommand->wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS: //登陆成功
		{
			return OnSocketSubGRLogonSuccess(pBuffer, wDataSize);
			 
		}
	case SUB_GR_LOGON_FAILURE:   //登陆失败
		{
			return OnSocketSubGRLogonFailure(pBuffer, wDataSize);
		}
	case SUB_GR_LOGON_FINISH:  //登陆完成
		{
			CCLOG("----------------------gameserver login success!-------------------------- file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketSubGRLogonFinish(pBuffer, wDataSize);
			 
		}
	}
}

// 房间登录子命令码处理       add by wangjun
//登录成功       add by wangjun
bool RoomFrame::OnSocketSubGRLogonSuccess(void *buffer, WORD size)
{
	CCLog("OnSocketSubGRLogonSuccess！！！！！");
	//CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_GAMELINK,CCInteger::create(1));
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_LOGINFAIL,CCInteger::create(2));
	return true;
}

//登录失败       add by wangjun
bool RoomFrame::OnSocketSubGRLogonFailure(void *buffer, WORD size)
{
	EntityMgr::instance()->getDispatch()->closeGameSocket();
	CCLOG("game server login failed! file(%s) line(%d)",__FILE__, __LINE__);
	// 变量定义
	CMD_GR_LogonFailure lf;
	memset(&lf, 0, sizeof(CMD_GR_LogonFailure));
	memcpy(&lf, buffer, sizeof(CMD_GR_LogonFailure));

	//NSLog(@"OnSocketSubGRLogonFailure lErrorCode=%ld", lf.lErrorCode);

	if (lf.lErrorCode == ERROR_CODE_LOGIN)
	{
		//if ([CFrameDate shareFrameDate].m_bChinaPayIsValid)
		if (1)
		{
			//if (alertBuy == nil)
			{
				// 错误提示
				char str[100];
				MyNSString::wc2mbs(lf.szDescribeString, sizeof(lf.szDescribeString), str);
				tagBankruptObj tag;
				tag.bBankrupt = false;
				CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_BANKRUPT,&tag);
				CCLog(str);
			}
		}
		else
		{
			//if (alertBuy == nil)
			{
				char str[100];
				MyNSString::wc2mbs(lf.szDescribeString, sizeof(lf.szDescribeString), str);
				CCLog(str);
			}
		}
	}
	else
	{
		// 错误提示
		char str[100];
		MyNSString::wc2mbs(lf.szDescribeString, sizeof(lf.szDescribeString), str);
		CCLog(str);
	}

	CCLog("登录失败");
	return true;
}

//登录完成       add by wangjun
bool RoomFrame::OnSocketSubGRLogonFinish(void *buffer, WORD size)
{
	CCLog("登录完成");
	bool m_bStartType = EntityMgr::instance()->getDispatch()->getStartType();
	// 空闲状态启动房间
	if ( (EntityMgr::instance()->getDispatch()->m_cbStatus == US_FREE || 
		EntityMgr::instance()->getDispatch()->m_cbStatus == US_NULL || 
		EntityMgr::instance()->getDispatch()->m_cbStatus == US_SIT) && !m_bStartType)
	{
		EntityMgr::instance()->getDispatch()->SendPacketWithChangeTable();
		//if ([m_pPlaza respondsToSelector:@selector(FrameDateDelegateWithOnRoomEnter)])
		//[m_pPlaza FrameDateDelegateWithOnRoomEnter];
		return true;
	}

	//CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_GAMELINK,CCInteger::create(1));

	//CCScene *scene = CCScene::create();
	//SceneTableInterfaceLayer *pHelplayer = SceneTableInterfaceLayer::create();
	//scene->addChild(pHelplayer);
	//CCDirector::sharedDirector()->replaceScene(scene); 


	// 游戏状态启动游戏
	if (EntityMgr::instance()->getDispatch()->m_cbStatus == US_PLAYING || EntityMgr::instance()->getDispatch()->m_cbStatus == US_READY)
	{
		EntityMgr::instance()->getDispatch()->SendPacketWithGameOption();

		m_bStartType = false;

		CCLog("断线重连");
		return true;
	}
}

//提示更新       add by wangjun
bool RoomFrame::OnSocketSubGRUpdateNotify(void *buffer, WORD size)
{
	return true;
}

//大厅登陆成功提示       add by wangjun
bool RoomFrame::OnSocketSubGRLogonNotify(void *buffer, WORD size)
{
	return true;
}

//用户消息
bool RoomFrame::OnSocketGameUser(CMD_Command* pCommand, void* pBuffer, WORD wDataSize)
{
	switch (pCommand->wSubCmdID)
	{
	case SUB_GR_USER_RULE:				// 用户规则	1
		{
			CCLog("未处理的case");
			return true;
		}
	case SUB_GR_USER_LOOKON:			// 用户旁观	2
		{
			CCLog("未处理的case");
			return true; 
		}
	case SUB_GR_USER_SITDOWN:			// 用户坐下	3	
		{
			CCLog("未处理的case");
			return true;
		}
	case SUB_GR_USER_STANDUP:			// 用户起立	4
		{
			CCLog("未处理的case");
			return true;
		}
	case SUB_GR_USER_INVITE:			// 用户邀请	5
		{
			CCLog("用户邀请未处理");
			return true;
		}
	case SUB_GR_USER_INVITE_REQ:		// 邀请请求	6
		{
			CCLog("邀请请求未处理的");
			return true;
		}
	case SUB_GR_USER_REPULSE_SIT:		// 拒绝坐下	7
		{
			CCLog("拒绝坐下未处理7");
			return true;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
	case SUB_GR_USER_ENTER:				// 用户进入	100
		{
			return OnSocketSubUserCome(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_USER_SCORE:				// 用户分数	101
		{
			return OnSocketSubScore(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_USER_STATUS:			// 用户状态	102
		{
			return OnSocketSubStatus(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_REQUEST_FAILURE:		// 请求失败	103
		{
			return OnSocketSubSitFailed(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_USER_CHAT:				// 用户聊天	201
		{
			return OnSocketSubChat(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_USER_EXPRESSION:		// 用户表情	202
		{
			CCLog("未处理的case");
			return true;
		}
	case SUB_GR_WISPER_CHAT:			// 用户私聊	203
		{
			CCLog("未处理的case");
			return true;
		}
	case SUB_GR_WISPER_EXPRESSION:		// 私聊表情	204
		{
			CCLog("未处理的case");
			return true;
		}
	case SUB_GR_COLLOQUY_CHAT:			//会话消息	205
		{
			CCLog("未处理的case");
			return true;
		}
	case SUB_GR_COLLOQUY_ERPRESSION:	// 会话表情	206
		{
			CCLog("未处理的case");
			return true;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
	case SUB_GR_PROPERTY_BUY:			// 购买道具	300
		{
			CCLog("道具购买未处理");
			return true;
		}
	case SUB_GR_PROPERTY_SUCCESS:		// 道具成功	301
		{
			//return [self OnSocketPropBuySuccess:wSubCmdID buffer:buffer bufferSize:size];
		}
	case SUB_GR_PROPERTY_FAILURE:		// 道具失败	302		
		{
			//return [self OnSocketPropBuyFailure:wSubCmdID buffer:buffer bufferSize:size];
		}
	case SUB_GR_PROPERTY_MESSAGE:		// 道具消息	303 道具消息好象暂时没有什么用途
		{
			return true;
		}

		//case SUB_GP_USER_INSURE_INFO:           // 保险柜资料 403
		//case SUB_GP_USER_INSURE_SUCCESS:        // 保险柜成功 405
		//case SUB_GP_USER_INSURE_FAILURE:        // 保险柜失败 406
		{
			//return [self OnSocketRecvBankInfo:wSubCmdID buffer:buffer bufferSize:size];
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
	case SUB_GR_GET_BONUS:              // 服务器端返回结果，以及豆豆金额 405      // add by mojunxin
		{
			//return [self OnSocketRecvSilverBonus:buffer bufferSize:size];
		}
	case SUB_GR_GET_ERROR:                  // 点击宝箱返回错误消息描述 1405
		{
			//return [self OnSocketRecvSilverBonusError:buffer bufferSize:size];
		}


		//////////////////////////////////////////////////////////////////////////////////////////////
	case SUB_GP_PAY_REVE_IP:             // apple应用内购买完成，向服务器申请充值，服务器返回的结果  601      // add by mojunxin
		{
			//return [self OnSocketGetIapResult:buffer bufferSize:size];
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
	default:
		{
			CCLog("未处理的case OnTCPNetworkMainGRUser wSubCmdID=%d", pCommand->wSubCmdID);
			return true;
		}
	}
	return true;
}
//配置信息
bool RoomFrame::OnSocketGameInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	switch (pCommand->wSubCmdID)
	{
	case SUB_GR_CONFIG_COLUMN:			// 列表配置
		{
			return this->OnSocketSubGRConfigColumn(pBuffer, wDataSize);
		}
	case SUB_GR_CONFIG_SERVER:			// 房间配置
		{
			return this->OnSocketSubGRConfigServer(pBuffer, wDataSize);
		}
	case SUB_GR_CONFIG_PROPERTY:		// 道具配置
		{
			return this->OnSocketSubGRConfigPropepty(pBuffer, wDataSize);
		}
	case SUB_GR_CONFIG_FINISH:			// 配置完成
		{
			return this->OnSocketSubGRConfigFinish(pBuffer, wDataSize);
		}
	default:
		//CCAssert(false, "未处理的case");
		return true;
	}
	return true;
}

// 配置信息子命令码处理       add by wangjun
//列表配置       add by wangjun
bool RoomFrame::OnSocketSubGRConfigColumn(void *buffer, WORD size)
{
	CCLog("列表配置");
	return true;
}

//房间配置       add by wangjun
bool RoomFrame::OnSocketSubGRConfigServer(void *buffer, WORD size)
{
	CCLog("房间配置");
	// 效验大小
	if (size != sizeof(CMD_GR_ConfigServer)) return false;

	return true;
}

//道具配置       add by wangjun
bool RoomFrame::OnSocketSubGRConfigPropepty(void *buffer, WORD size)
{
	CCLog("道具配置");
	return true;
}

//配置完成       add by wangjun
bool RoomFrame::OnSocketSubGRConfigFinish(void *buffer, WORD size)
{
	CCLog("配置完成");
	return true;
}


//参赛用户进入
bool RoomFrame::OnSocketSubMatchUserCome(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	return true;
}
//状态信息
bool RoomFrame::OnSocketGameStatus(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLog("获取用户状态");
	return true;
}
//系统消息
bool RoomFrame::OnSocketGameSystem(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	//效验参数
	CMD_GF_Message* pMessage=(CMD_GF_Message *)pBuffer;
	if (wDataSize<=(sizeof(CMD_GF_Message)-sizeof(pMessage->szContent)))
	{
		return false;
	}
	//消息处理
	WORD wHeadSize= sizeof(CMD_GF_Message) - sizeof(pMessage->szContent);
	if (wDataSize != (wHeadSize + pMessage->wMessageLength * sizeof(char)))
	{
		return false;
	}
	pMessage->szContent[pMessage->wMessageLength-1]=0;
	 
	//    
	//    //中断判断
	//    if (pMessage->wMessageType&SMT_CLOSE_GAME)
	//    {
	//        //        KillGameTimer(m_nTimerID);
	//        //        m_ChannelServiceHelper->CloseChannel(true,true); //不能关闭心道，CloserFrame需要利用发送消息给大厅
	//    }
	//    
	//    //系统消息
	//    if(pMessage->wMessageType&SMT_INFO)
	//    {
	//        //        m_pIClientKernelSink->InsertSystemString(pMessage->szContent);
	//    }
	//    
	//    //弹出消息
	//    if (pMessage->wMessageType&SMT_EJECT)
	//    {
	//        //ShowMessageBox(pMessage->szContent,MB_ICONINFORMATION);
	//    }

	if (pMessage->wMessageType & SMT_GLOBAL)
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_MATCH);
		//        if(IDNO ==ShowInformationCellYesNo(pMessage->szContent,0,MB_ICONINFORMATION|MB_YESNO,TEXT("档位消息对话框")))
		//            //IDNO ==ShowInformation(pMessage->szContent,10,MB_ICONINFORMATION|MB_YESNO))
		//        {
		//            //AfxMessageBox("你不同意呀，发送选择同档匹配请求");
		//            SendQueuePacket(US_QUEUE_CELL_SAME);
		//sendQueuePacket(1);
		//        }
		//        else
		//        {
		//            //AfxMessageBox("你同意了呀，发送选择自由匹配请求");
		//sendQueuePacket(2);
		//        }
	}

	//滚动消息和固定显示消息大赢家消息
	//    if ((pMessage->wMessageType & SMT_TABLE_ROLL) || (pMessage->wMessageType & SMT_TABLE_FIX)
	//        ||(pMessage->wMessageType & SMT_TABLE_WINTIP) || (pMessage->wMessageType & SMT_TABLE_ANI))
	//    {
	//        tagSystemBuffer tag;
	//        tag.wMessageType = pMessage->wMessageType;
	//        tag.wMessageLength = pMessage->wMessageLength;
	//        memcpy(tag.szContent, pMessage->szContent, sizeof(tag.szContent));
	//        GBEvent::instance()->fire(GBEVENT_UI_SYSTEM,tag);
	//    }

	//    switch (pMessage->wMessageType)
	//    {
	//        case SMT_TABLE_ROLL:
	//        case SMT_TABLE_FIX:
	//        {
	//            break;
	//        }
	//        case SMT_TABLE_WINTIP:          //大赢家
	//        {
	//            CCLOG("大赢家");
	//            break;
	//        }
	//        case SMT_GLOBAL:                //升降档
	//        {
	//             CCLOG("升降档");
	//            break;
	//        }
	//        case SMT_TABLE_ANI:             //话费点
	//        {
	//             CCLOG("话费点");
	//            break;
	//        }
	//        case SMT_CLOSE_GAME:           //关闭房间
	//        {
	//             CCLOG("关闭房间");
	//            break;
	//        }
	//        default:
	//            break;
	//    }
	//
	//    //关闭房间
	//    if (pMessage->wMessageType&SMT_CLOSE_GAME)
	//    {
	//        m_bInquire=false;
	//        m_pIClientKernelSink->CloseGameFrame(true);
	//    }

	return true;
}
//房间信息
bool RoomFrame::OnSocketGameServerInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	return true;
}

//用户信息 用户进入

bool RoomFrame::OnSocketSubUserCome(CMD_Command* pCommand, void* pBuffer, WORD wDataSize)
{
	string str = "用户进入";
	MyNSString::GBKToUTF8(str);
	CCLog(str.c_str());
	// 变量定义
	BYTE cbBuffer[sizeof(tagGameInUserInfo)];
	memset(cbBuffer, 0 , sizeof(tagGameInUserInfo));
	tagGameInUserInfo *pUserInfoHead = (tagGameInUserInfo *)cbBuffer;
	memcpy(pUserInfoHead, pBuffer, sizeof(tagGameInUserInfo));
	//CCLOG("用户进入! file(%s) line(%d)",__FILE__, __LINE__);
	BYTE bBuffer[sizeof(tagDataDescribe)];
	memset(bBuffer, 0 , sizeof(tagDataDescribe));
	tagDataDescribe *describe= (tagDataDescribe *)bBuffer;
	memcpy(describe, (BYTE *)pBuffer+sizeof(tagGameInUserInfo), sizeof(tagDataDescribe));

	//读取基本信息
	tagUserData* pUserData = new tagUserData;
	memset(pUserData, 0, sizeof(tagUserData));
	memset(pUserData, 0, sizeof(tagUserData));
	// 用户属性
	if (describe->wDataDecribe == DTP_GR_NICK_NAME){
		//memcpy(pUserData->szNickName, ((BYTE *)pBuffer+sizeof(tagGameInUserInfo)+sizeof(tagDataDescribe)), describe->wDataSize);
		MyNSString::wc2mbs((TCHART *)(((BYTE *)pBuffer+sizeof(tagGameInUserInfo)+sizeof(tagDataDescribe))), describe->wDataSize, pUserData->szNickName);
	}
	pUserData->dwGameID=pUserInfoHead->dwGameID;
	pUserData->dwUserID=pUserInfoHead->dwUserID;
	// 头像信息
	pUserData->wFaceID=pUserInfoHead->wFaceID;
	// 用户属性
	pUserData->cbGender=pUserInfoHead->cbGender;
	pUserData->cbMemberOrder=pUserInfoHead->cbMemberOrder;
	// 用户状态
	pUserData->wTableID=pUserInfoHead->wTableID;
	pUserData->wChairID=pUserInfoHead->wChairID;
	pUserData->cbUserStatus=pUserInfoHead->cbUserStatus;
	// 积分信息
	pUserData->lScore=pUserInfoHead->lScore;
	// 游戏信息
	pUserData->lWinCount=pUserInfoHead->dwWinCount;
	pUserData->lLostCount=pUserInfoHead->dwLostCount;
	pUserData->lDrawCount=pUserInfoHead->dwDrawCount;
	pUserData->lFleeCount=pUserInfoHead->dwFleeCount;
	pUserData->lExperience=pUserInfoHead->dwExperience;
	pUserData->lGoldEggs = 0;
	string dwellPlace = "广东省深圳市";
	MyNSString::GBKToUTF8(dwellPlace);
	memcpy(pUserData->szDwellingPlace, dwellPlace.c_str(), sizeof(pUserData->szDwellingPlace));

	if (pUserInfoHead->cbUserStatus == US_NULL)
	{
		removeItem(pUserInfoHead->dwUserID);
	}else{
		CUserItem* pUserItem = (CUserItem*)insertItem(pUserData);
	}

	if (pUserInfoHead->dwUserID == EntityMgr::instance()->getDispatch()->m_dwUserID)
	{
		EntityMgr::instance()->getDispatch()->m_cbStatus = pUserInfoHead->cbUserStatus;
		//m_cbStatus = pUserInfoHead->cbUserStatus;
		EntityMgr::instance()->getDispatch()->m_wChairID = pUserInfoHead->wChairID;
		EntityMgr::instance()->getDispatch()->m_wTableID = pUserInfoHead->wTableID;
		m_pMeUserItem = new CUserItem(pUserData);
	}

	// 更新桌子视图
	if (pUserInfoHead->wTableID != INVALID_TABLE && pUserInfoHead->wChairID != INVALID_CHAIR && 
		EntityMgr::instance()->getDispatch()->m_wTableID == pUserInfoHead->wTableID) 
	{
		if(pUserInfoHead->cbUserStatus>=US_SIT)
		{
			updateMeTable(pUserInfoHead->dwUserID);
		}
	}
	return true;
}

//1房间列表保存用户原来状态

//用户状态
bool RoomFrame::OnSocketSubStatus(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	//CCLOG("－－－－－－－－－－－－－－－－－－－－用户状态!－－－－－－－－－－－－－－－－－－－－－－－－－");

	if (wDataSize!=sizeof(CMD_GR_UserStatus))
	{
		return false;
	}

	//处理数据
	BYTE cbBuffer[sizeof(CMD_GR_UserStatus)];
	memset(cbBuffer, 0 , sizeof(CMD_GR_UserStatus));
	CMD_GR_UserStatus *pUserStatus = (CMD_GR_UserStatus *)cbBuffer;
	memcpy(pUserStatus, pBuffer, sizeof(CMD_GR_UserStatus));

	CUserItem* pIUserItem = (CUserItem*)getUserItem(pUserStatus->dwUserID);
	if(pIUserItem == NULL && pUserStatus->UserStatus.cbUserStatus != US_NULL)
	{
		//读取基本信息
		tagUserData* pUserData = new tagUserData;
		memset(pUserData, 0, sizeof(tagUserData));
		memset(pUserData, 0, sizeof(tagUserData));
		string nicknameString = "获取用户名失败";
		MyNSString::GBKToUTF8(nicknameString);
		memcpy(pUserData->szNickName, nicknameString.c_str(), sizeof(pUserData->szNickName));
		string dwellPlace = "广东省深圳市";
		MyNSString::GBKToUTF8(dwellPlace);
		memcpy(pUserData->szDwellingPlace, dwellPlace.c_str(), sizeof(pUserData->szDwellingPlace));
		pUserData->dwUserID=pUserStatus->dwUserID;
		pUserData->cbUserStatus = pUserStatus->UserStatus.cbUserStatus;
		pUserData->wTableID = pUserStatus->UserStatus.wTableID;
		pUserData->wChairID = pUserStatus->UserStatus.wChairID;
		// 积分信息
		pUserData->lScore=0;
		pUserData->lExperience=0;
		pUserData->lGoldEggs = 0;
		pIUserItem = (CUserItem*)insertItem(pUserData);
		EntityMgr::instance()->getDispatch()->SendPacketWithRequestChairUserInfo(pUserStatus->UserStatus.wTableID, pUserStatus->UserStatus.wChairID);
	}

	if (pIUserItem != NULL) 
	{
		//现在状态
		WORD wNowTableID=pUserStatus->UserStatus.wTableID;
		WORD wNowChairID=pUserStatus->UserStatus.wChairID;
		BYTE cbNowStatus=pUserStatus->UserStatus.cbUserStatus;

		//原来状态
		tagUserData* pUserData=pIUserItem->getUserData();
		WORD wLastTableID=pUserData->wTableID;
		WORD wLastChairID=pUserData->wChairID;
		BYTE cbLastStatus=pUserData->cbUserStatus;


		tagUserStatus status;
		status.wTableID = pUserStatus->UserStatus.wTableID;
		status.wChairID = pUserStatus->UserStatus.wChairID;
		status.cbUserStatus = pUserStatus->UserStatus.cbUserStatus;

		tagUserData* pMeUserData =  m_pMeUserItem->getUserData();

		switch (pUserStatus->UserStatus.cbUserStatus) 
		{
		case US_NULL : 
			{
				// 删除用户
				removeItem(pUserStatus->dwUserID);
				// 如果是自己 退出游戏  -------退出到大厅-------
				if (pMeUserData->dwUserID == pUserStatus->dwUserID)
				{
					EntityMgr::instance()->getDispatch()->m_cbStatus = pUserStatus->UserStatus.cbUserStatus;
					m_cbStatus = pUserStatus->UserStatus.cbUserStatus;
					EntityMgr::instance()->getDispatch()->m_wChairID = pUserStatus->UserStatus.wChairID;
					EntityMgr::instance()->getDispatch()->m_wTableID = pUserStatus->UserStatus.wTableID;
					pUserData->wTableID = wNowTableID;
					pUserData->wChairID = wNowChairID;
					pUserData->cbUserStatus = cbNowStatus;
					m_pMeUserItem->setUserDate(pUserData);
				} 
				break;
			}
		case US_FREE : 
			{
				// 更新用户
				updateUserStatus(pUserStatus->dwUserID,&status);
				// 如果是自己判断是否需显示房间
				if (pMeUserData->dwUserID == pUserStatus->dwUserID) {
					EntityMgr::instance()->getDispatch()->m_cbStatus = pUserStatus->UserStatus.cbUserStatus;
					m_cbStatus = pUserStatus->UserStatus.cbUserStatus;
					EntityMgr::instance()->getDispatch()->m_wChairID = pUserStatus->UserStatus.wChairID;
					EntityMgr::instance()->getDispatch()->m_wTableID = pUserStatus->UserStatus.wTableID;
					pUserData->wTableID = wNowTableID;
					pUserData->wChairID = wNowChairID;
					pUserData->cbUserStatus = cbNowStatus;
					m_pMeUserItem->setUserDate(pUserData);
				}
				break;
			}
		case US_LOOKON :
		case US_OFFLINE :
		case US_PLAYING :
		case US_READY :
		case US_SIT : {
			// 更新用户
			updateUserStatus(pUserStatus->dwUserID,&status);

			if (pMeUserData->dwUserID == pUserStatus->dwUserID) 
			{
				EntityMgr::instance()->getDispatch()->m_cbStatus = pUserStatus->UserStatus.cbUserStatus;
				m_cbStatus = pUserStatus->UserStatus.cbUserStatus;
				EntityMgr::instance()->getDispatch()->m_wChairID = pUserStatus->UserStatus.wChairID;
				EntityMgr::instance()->getDispatch()->m_wTableID = pUserStatus->UserStatus.wTableID;
				pUserData->wTableID = wNowTableID;
				pUserData->wChairID = wNowChairID;
				pUserData->cbUserStatus = cbNowStatus;
				m_pMeUserItem->setUserDate(pUserData);
				//发送椅子用户信息
				EntityMgr::instance()->getDispatch()->SendPacketWithRequestChairUserInfo(pUserStatus->UserStatus.wTableID, pUserStatus->UserStatus.wChairID);

				// 坐下判断
				if (cbLastStatus < US_SIT)
				{
					EntityMgr::instance()->getDispatch()->SendPacketWithGameOption();
					// 命令码 MDM_GF_FRAME 与 MDM_MB_LOGON 冲突，这里先取负解决
					CCNotificationCenter::sharedNotificationCenter()->postNotification("GameStart", NULL);
				}
			} else
			{ 
				//发送椅子用户信息
				EntityMgr::instance()->getDispatch()->SendPacketWithRequestChairUserInfo(pUserStatus->UserStatus.wTableID, pUserStatus->UserStatus.wChairID);
				if (pUserStatus->UserStatus.cbUserStatus == US_SIT) 
				{
					if (pMeUserData->wTableID != INVALID_TABLE && wNowTableID == pMeUserData->wTableID && wLastTableID != pMeUserData->wTableID) 
					{
						//String szStr;
						//if(useritem.GetMemberOrder() > 0){
						//	szStr = "VIP " + useritem.GetNickName() + " 闪亮登场！";
						//	CGameClientView.onSubSystemMessage(szStr, false,true);
						//	HornRecord.addHornInfo(0,szStr);
						//}
					}
				}
			}

			// 更新桌子视图
			if (wNowTableID != INVALID_TABLE && wNowChairID != INVALID_CHAIR && pMeUserData->wTableID == wNowTableID) 
			{
				updateMeTable(pUserStatus->dwUserID);
			}
			break;
					  }
		default :
			return true;
		}
	}
	return true;
}
UsrIdList RoomFrame::searchUser(WORD wTableID)
{
	UsrIdList userList;
	UsrDateMap::iterator iter =  m_UserDateList.begin();
	for (; iter != m_UserDateList.end(); iter++)
	{
		CUserItem* pUserItem = (CUserItem*)iter->second;
		if (!pUserItem)
		{
			continue;
		}
		tagUserData* pUserDate = pUserItem->getUserData();
		if (!pUserDate)
		{
			continue;
		}
		if (pUserDate->wTableID == wTableID)
		{
			userList.push_back(pUserDate->dwUserID);
		}
	}
	return userList;
}


UsrDateList RoomFrame::searchUserDate(WORD wTableID)
{
	UsrDateList userList;
	UsrDateMap::iterator iter =  m_UserDateList.begin();
	for (; iter != m_UserDateList.end(); iter++)
	{
		CUserItem* pUserItem = (CUserItem*)iter->second;
		if (!pUserItem)
		{
			continue;
		}
		tagUserData* pUserDate = pUserItem->getUserData();
		if (!pUserDate)
		{
			continue;
		}
		if (pUserDate->wTableID == wTableID)
		{
			userList.push_back(pUserDate);
		}
	}
	return userList;
}


//用户分数
bool RoomFrame::OnSocketSubScore(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	//处理数据
	CMD_GR_MobileUserScore* pUserScore=(CMD_GR_MobileUserScore *)pBuffer;

	CUserItem* pIUserItem = (CUserItem*)getUserItem(pUserScore->dwUserID);
	if (pIUserItem==NULL)
	{
		return true;
	}

	tagUserData* pUserData = pIUserItem->getUserData();
	if (pUserData == NULL)
	{
		return  true;
	}

	tagMobileUserScore userScore = pUserScore->UserScore;
	if (pUserData->dwUserID ==  m_pMeUserItem->getUserData()->dwUserID)
	{
		m_pMeUserItem->setUserScore(&userScore);
		g_GlobalUnits.getGolbalUserData()->lScore    = userScore.lScore;
		//g_GlobalUnits.getGolbalUserData()->lGoldEggs = userScore.lGoldEggs;
		CCLOG("score=%d",userScore.lScore);

		//小于500 提示破产
		if (userScore.lScore < 500)
		{

		}
	}

	pIUserItem->setUserScore(&userScore);

	//CCLOG("======================%d",pUserScore->UserScore.lScore);			分数改变--刷新桌子
	tagUserBuffer tag;
	tag.dwUserID = pUserScore->dwUserID;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_PLAYERUPDATE,&tag);
	return true;
}
//用户名次
bool RoomFrame::OnSocketSubSort(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	return true;
	CCLOG("user sort! file(%s) line(%d)",__FILE__, __LINE__);
}
//用户权限
bool RoomFrame::OnSocketSubRight(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user right! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//会员等级
bool RoomFrame::OnSocketSubMemberOrder(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user member order! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//坐下失败
bool RoomFrame::OnSocketSubSitFailed(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user sit failed! file(%s) line(%d)",__FILE__, __LINE__);
	tagBankruptObj tag;
	tag.bBankrupt = true;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_BANKRUPT,&tag);
	return true;
}
//用户聊天
bool RoomFrame::OnSocketSubChat(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user chat! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//用户私语
bool RoomFrame::OnSocketSubWisper(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user wisper! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//邀请玩家
bool RoomFrame::OnSocketSubUserInvite(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user invite! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//参加比赛
bool RoomFrame::OnSocketJoinMatch(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user join match! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//修改用户金币
bool RoomFrame::OnSocketSubGold(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("change user gold! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//游戏比赛信息
bool RoomFrame::OnSocketGameMatchInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("get match info! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//VIP房间密码信息
bool RoomFrame::OnSocketVIPRoomPassWord(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("VIP room password! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//vip房间密码错误
bool RoomFrame::OnSocketVIPErrorPassWord(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("vip error password! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}

//用户比赛成绩
bool RoomFrame::OnSocketSubMatchScore(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user match score result! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}

bool RoomFrame::OnSocketSubModifyNickName(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("Modyfu nickname result! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}

bool RoomFrame::OnSocketGameOrder(void * pBuffer, WORD wDataSize)
{
	assert(wDataSize==sizeof(CMD_GP_ScoreGiftResult));
	if(wDataSize!=sizeof(CMD_GP_ScoreGiftResult)) return false;
	CMD_GP_ScoreGiftResult *pGiftResult = (CMD_GP_ScoreGiftResult *)pBuffer;
	CCLOG("ordwe ID = %d, errCode = %d",pGiftResult->lScore,pGiftResult->lErrCode);
	if(pGiftResult->lErrCode == 0)
	{
		int orderID = pGiftResult->lScore;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		toSendAndroidOrder(orderID);
#endif
	}
	else
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		toSendAndroidOrder(0);
#endif
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//网络消息(这个消息服务器写的很奇葩)
bool RoomFrame::OnFrameMessage(WORD wSubCmdID, const void* pBuffer, WORD wDataSize)
{
	CCLog("OnFrameMessage");
	switch (wSubCmdID)
	{
	case SUB_GF_GAME_OPTION:			// 游戏配置     1
		{
			CCLog("游戏配置");
			break;
		}
	case SUB_GF_USER_READY:				// 用户准备     2
		{
			CCLog("用户准备");
			return true;
		}
	case SUB_GF_LOOKON_CONFIG:			//旁观配置      3
		{
			CCLog("旁观配置");
			return true;
		}
	case SUB_GF_USER_CHAT:				//用户聊天      10
		{
			
			//BYTE cbBuffer[sizeof(CMD_GR_S_UserChat)];
			//memset(cbBuffer, 0 , sizeof(CMD_GR_S_UserChat));
			//CMD_GR_S_UserChat *UserChat = (CMD_GR_S_UserChat *)cbBuffer; 
			//memcpy(UserChat, pBuffer,wDataSize);

			BYTE cbBuffer1[sizeof(tagGameBuffer)];
			memset(cbBuffer1, 0 , sizeof(tagGameBuffer));
			tagGameBuffer *tag = (tagGameBuffer *)cbBuffer1;
			
			tag->nDataSize = wDataSize;
			tag->wSubCmdID = wSubCmdID;
			memcpy(tag->dateBuffer, pBuffer,wDataSize);
			CCNotificationCenter::sharedNotificationCenter()->postNotification(GBEVENT_UI_GAMEMESSAGE, tag);

			break;
		}
	case SUB_GF_USER_EXPRESSION:		//用户表情      11
		{
			BYTE cbBuffer[sizeof(tagGameBuffer)];
			memset(cbBuffer, 0 , sizeof(tagGameBuffer));
			tagGameBuffer *tag = (tagGameBuffer *)cbBuffer;

			tag->nDataSize = wDataSize;
			tag->wSubCmdID = wSubCmdID;
			memcpy(tag->dateBuffer, pBuffer,wDataSize);
			CCNotificationCenter::sharedNotificationCenter()->postNotification(GBEVENT_UI_GAMEMESSAGE, tag);
			break;
		}
	case SUB_GF_GAME_STATUS:			//游戏状态      100
		{
			//效验参数
			//assert(wDataSize==sizeof(CMD_GF_Option));
			if (wDataSize!=sizeof(CMD_GF_Option))
			{
				return false;
			}

			//消息处理
			CMD_GF_Option * pOption=(CMD_GF_Option *)pBuffer;
			m_cbGameStatus = pOption->bGameStatus;
			m_cbAllowLookon = pOption->bAllowLookon;

			CCLOG("gamestatus!");
			return true;
		}
	case SUB_GF_GAME_SCENE:				//游戏场景      101
		{
			//游戏场景消息
			//EntityMgr::instance()->getDispatch()->sendSocketDate(MDM_GF_GAME,SUB_GR_CLIENT_READY);

			BYTE cbBuffer[sizeof(tagSceneBuffer)];
			memset(cbBuffer, 0 , sizeof(tagSceneBuffer));
			tagSceneBuffer *tag = (tagSceneBuffer *)cbBuffer;

			tag->nDataSize = wDataSize;
			tag->cbState = m_cbGameStatus;
			memcpy(tag->dateBuffer, pBuffer,wDataSize);
			CCNotificationCenter::sharedNotificationCenter()->postNotification(GBEVENT_UI_SCENEMESSAGE, tag);
			if(gameIsStart == false){
				//CCNotificationCenter::sharedNotificationCenter()->postNotification("GameStart", NULL);
			}
			break;
		}
	case SUB_GF_SYSTEM_MESSAGE:			//系统消息      200
		{

			//效验参数
			CMD_CM_SystemMessage* pMessage=(CMD_CM_SystemMessage *)pBuffer;
			if (wDataSize<=(sizeof(CMD_CM_SystemMessage)-sizeof(pMessage->szString)))
			{
				return false;
			}
			//消息处理
			//WORD wHeadSize= sizeof(CMD_GF_Message) - sizeof(pMessage->szContent);
			//if (wDataSize != (wHeadSize + pMessage->wMessageLength * sizeof(char)))
			//{
			//	return false;
			//}
			pMessage->szString[pMessage->wLength-1]=0;
			char message[1224];
			time_t tt = time(NULL);//这句返回的只是一个时间cuo
			tm* t= localtime(&tt);
			char msg[1024] = {0};
			MyNSString::wc2mbs(pMessage->szString, pMessage->wLength, msg);
			sprintf(message, "insert into SystemMsg(msg) values(\'%s     %d-%02d-%02d %02d:%02d:%02d\')", msg,
				t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
			DBHandler::sharedDBHandler()->execute(message);

			tagGameBuffer tag;
			memset(tag.dateBuffer, 0, 4096);

			tag.nDataSize = wDataSize;
			tag.wSubCmdID = wSubCmdID;
			memcpy(tag.dateBuffer, pBuffer,wDataSize);
			CCNotificationCenter::sharedNotificationCenter()->postNotification(GBEVENT_UI_GAMEMESSAGE,&tag);
			//            switch (pMessage->wMessageType)
			//            {
			//                case SMT_TABLE_ROLL:
			//                case SMT_TABLE_FIX:
			//                {
			//                    break;
			//                }
			//                case SMT_TABLE_WINTIP:          //大赢家
			//                {
			//                    CCLOG("大赢家");
			//                    break;
			//                }
			//                case SMT_GLOBAL:                //升降档
			//                {
			//                    CCLOG("升降档");
			//                    break;
			//                }
			//                case SMT_TABLE_ANI:             //话费点
			//                {
			//                    CCLOG("话费点");
			//                    break;
			//                }
			//                case SMT_CLOSE_GAME:           //关闭房间
			//                {
			//                    CCLOG("关闭房间");
			//                    break;
			//                }
			//                default:
			//                    break;
			//            }
		}
	}
	return true;
}


bool RoomFrame::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	//CCLog("OnGameMessage");
	//switch (wSubCmdID)
	//{
	//case SUB_GR_CLIENT_START_GAME: //客户端启动完成，通知举手
	//	{
	//		CCLOG("client lauch over,raise hand");
	//		EntityMgr::instance()->getDispatch()->sendSocketDate(MDM_GF_FRAME,SUB_GF_USER_READY);

	//		OnClientStartGame();
	//		return true;
	//	}

	//case SUB_GF_BANK_GET:				//领话费返回消息处理
	//	{
	//		//效验参数
	//		assert(wDataSize==sizeof(CM_GF_CHARGE));
	//		if (wDataSize!=sizeof(CM_GF_CHARGE)) return false;

	//		CM_GF_CHARGE *lpCharge = (CM_GF_CHARGE *)pBuffer;

	//		return true;
	//	}
	//case SUB_GF_CELL:				//设k置升级降级变量
	//	{

	//		CMD_GF_CELL_MESSAGE *pMessage = (CMD_GF_CELL_MESSAGE *)pBuffer;
	//		if (wDataSize<=(sizeof(CMD_GF_CELL_MESSAGE) - sizeof(pMessage->szContent))) return false;

	//		if (pMessage->wMessageType==SMT_CELL_USER_H)  //用户升级
	//		{
	//			//CCLOG("－－－－－－－用户升级了－－－－－－");
	//			g_GlobalUnits.m_nGabalUserLevel = SMT_CELL_USER_H;
	//		}
	//		if (pMessage->wMessageType==SMT_CELL_USER_L)  //用户降级
	//		{
	//			if(pMessage->lCellScoreL < 1 )//破产
	//			{

	//			}else
	//			{
	//				//CCLOG("－－－－－－－用户降级了－－－－－－");
	//				g_GlobalUnits.m_nGabalUserLevel = SMT_CELL_USER_L;
	//			}
	//		}
	//		return true;
	//	}
	//}

	BYTE cbBuffer[sizeof(tagGameBuffer)];
	memset(cbBuffer, 0 , sizeof(tagGameBuffer));
	tagGameBuffer *tag = (tagGameBuffer *)cbBuffer;

	tag->nDataSize = wDataSize;
	tag->wSubCmdID = wSubCmdID;
	memcpy(tag->dateBuffer, pBuffer,wDataSize);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(GBEVENT_UI_GAMEMESSAGE, tag);

	return true;
}

//客户端开始游戏
void RoomFrame::OnClientStartGame()
{
	EntityMgr::instance()->getDispatch()->sendSocketDate(MDM_GF_GAME,SUB_C_ALL_READY);
}

//开始客户端游戏
void RoomFrame::startClientGame()
{
	CCLOG("start game!");

	//获取服务器场景消息
	BYTE cbBuffer[sizeof(CMD_GF_Info)];
	memset(cbBuffer, 0 , sizeof(CMD_GF_Info));
	CMD_GF_Info *Info = (CMD_GF_Info *)cbBuffer;
	Info->bAllowLookon= false;

	//发送消息
	EntityMgr::instance()->getDispatch()->sendSocketDate(MDM_GF_FRAME, SUB_GF_INFO,Info,sizeof(Info));

	CCLOG("-----------------------------------------------------get game scene message!---------------------------------------------------");
}
IUserItem* RoomFrame::insertItem(tagUserData* tag)
{
	if (!tag)
	{
		assert(false);
		return NULL;
	}
	CUserItem* pUserItem = new CUserItem(tag);

	DBHandler *handler = new DBHandler();
	char sql[400];
	sprintf(sql, "insert into UserInfo(dwUserID,wFaceID,cbGender,cbMemberOrder,lScore,dwWinCount,dwLostCount,dwDrawCount,dwFleeCount,dwExperience,nickname) select %lu,0,0,0,0,0,0,0,0,0,'' where not exists(select * from UserInfo where dwUserID=%lu)", tag->dwUserID, tag->dwUserID);
	handler->execute(sql);
	memset(sql, 0, sizeof(sql));
	sprintf(sql, "update UserInfo set dwUserID = %lu,wFaceID = %d,cbGender=%d,cbMemberOrder=%d,lScore=%ld,dwWinCount=%ld,dwLostCount=%ld,dwDrawCount=%ld,dwFleeCount=%ld,dwExperience=%ld,nickname=\'%s\' where dwUserID=%lu",
		tag->dwUserID, tag->wFaceID, tag->cbGender, tag->cbMemberOrder, tag->lScore, tag->lWinCount, tag->lLostCount, tag->lDrawCount, tag->lFleeCount, tag->lExperience, tag->szNickName, tag->dwUserID);
	handler->execute(sql);
	//handler->execute("insert into UserInfo(dwUserID,wFaceID,cbGender,cbMemberOrder,lScore,dwWinCount,dwLostCount,dwDrawCount,dwFleeCount,dwExperience,nickname) values(10010,0,0,0,0,0,0,0,0,0, 'test009') where not exists(select * from UserInfo where dwUserID=10010)");
	//handler->execute("update UserInfo set nickname='test008' where dwUserID=10010 where exists(select * from UserInfo where dwUserID=10010)");
	UsrDateMap::iterator iter =  m_UserDateList.find(pUserItem->getUserID());
	if (iter != m_UserDateList.end())
	{
		CCLOG("user data insert failed! file(%s) line(%d)",__FILE__, __LINE__);
		m_UserDateList.erase(iter);
		//m_UserDateList[tag->dwUserID] = pUserItem;
		//return NULL;
	}
	m_UserDateList[tag->dwUserID] = pUserItem;
	return pUserItem;
}

IUserItem* RoomFrame::insertItem(IUserItem* item)
{
	//    UsrDateMap::iterator iter =  m_UserDateMap.find(item->getUserID());
	//    if (iter != m_UserDateMap.end())
	//    {
	//        CCLOG("用户数据插入失败！ file(%s) line(%d)",__FILE__, __LINE__);
	//        return NULL;
	//    }
	//    m_UserDateMap[item->getUserID()] = item;
	return item;
}

void RoomFrame::removeItem(DWORD dwUserID)
{
	UsrDateMap::iterator iter =  m_UserDateList.find(dwUserID);
	if (iter != m_UserDateList.end())
	{
		m_UserDateList.erase(iter);
	}
}

IUserItem* RoomFrame::getUserItem(DWORD dwUserID)
{
	UsrDateMap::iterator iter =  m_UserDateList.find(dwUserID);
	if (iter != m_UserDateList.end())
	{
		return iter->second;
	}
	return NULL;
}

void RoomFrame::removeItemByTable(unsigned int nTableID,unsigned int nChairID)
{
	//m_TableFrame.removeUserItem(nTableID,nChairID);

	if (nTableID == m_nTable)
	{
		//updateMeTable();
	}
}

void RoomFrame::updateUserStatus(DWORD dwUserID, const tagUserStatus* pUserStatus)
{
	CUserItem* pUserItem = NULL;
	UsrDateMap::iterator iter =  m_UserDateList.find(dwUserID);
	if (iter != m_UserDateList.end())
	{
		((CUserItem*)iter->second)->setUserStatus(pUserStatus);
	}

}

void RoomFrame::updateTableUserStatus(unsigned int nTableID, unsigned int nChairID,IUserItem* pUserItem)
{
	//m_TableFrame.setUserItem(nTableID,nChairID,pUserItem);

	if (nTableID == m_nTable)
	{
		//updateMeTable();
	}
	//CCLOG("用户桌子%d,自己桌子%d",nTableID,m_pMeUserItem->getTableID());
}

//更新自己桌子
void RoomFrame::updateMeTable(DWORD dwUserID)
{
	if (!EntityMgr::instance()->getDispatch()->isGameStatuc())
	{
		return;
	}

	//发送状态玩家id
	tagUserBuffer tag;
	tag.dwUserID = dwUserID;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_PLAYERUPDATE,&tag);
}
