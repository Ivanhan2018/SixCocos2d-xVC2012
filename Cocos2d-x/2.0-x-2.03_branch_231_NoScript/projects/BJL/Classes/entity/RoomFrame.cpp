
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

//������Ϸ��������½��
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

//��Ϸ��Ϣ���� add by wangjun 2014-12-15
void RoomFrame::onGameMsg(GBEventConstArg& arg)
{
	tagCmdBuffer& tag = (tagCmdBuffer&)arg;
	CMD_Command* pCommand = &tag.command;
	OnEventTcpGameRead(pCommand,tag.dateBuffer,tag.nDataSize);
}

//ԭ������Ϸ��Ϣ����
/*
bool  RoomFrame::OnEventTcpGameRead(CMD_Command* pCommand,void* pData,WORD wDataSize)
{
switch (pCommand->wMainCmdID)
{
case MDM_GR_LOGON:			//��¼��Ϣ
{
//CCLOG("��½��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameLogin(pCommand,pData,wDataSize);
}
case MDM_GR_USER:			//�û���Ϣ
{
//CCLOG("�û���Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameUser(pCommand,pData,wDataSize);
}
case MDM_GR_INFO:			//������Ϣ
{
//CCLOG("������Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameInfo(pCommand,pData,wDataSize);
}
case MDM_GR_STATUS:			//״̬��Ϣ
{
//CCLOG("״̬��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameStatus(pCommand,pData,wDataSize);
}
case MDM_GR_SYSTEM:			//ϵͳ��Ϣ
{
//CCLOG("ϵͳ��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameSystem(pCommand,pData,wDataSize);
}
case MDM_GR_SERVER_INFO:	//������Ϣ
{
//CCLOG("������Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
return OnSocketGameServerInfo(pCommand,pData,wDataSize);
}
case MDM_GF_GAME:			//��Ϸ��Ϣ
{
//CCLOG("��Ϸ��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);

return OnGameMessage(pCommand->wSubCmdID,pData,wDataSize);
}
case MDM_GF_FRAME:			//�����Ϣ
{
//CCLOG("�����Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
return OnFrameMessage(pCommand->wSubCmdID,pData,wDataSize);
}
}
return  true;
}
*/

//��ԭ������Ϸ��Ϣ�ֳɷ����½��Ϣ����Ϸ��Ϣ			add by wangjun
bool  RoomFrame::OnEventTcpGameRead(CMD_Command* pCommand,void* pData,WORD wDataSize)
{

	switch (pCommand->wMainCmdID)
	{
	case MDM_GR_STATUS:			//״̬��Ϣ
		{
			//CCLOG("״̬��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameStatus(pCommand,pData,wDataSize);
		}
	case MDM_GR_SYSTEM:			//ϵͳ��Ϣ
		{
			//CCLOG("ϵͳ��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameSystem(pCommand,pData,wDataSize);
		}
	case MDM_GR_SERVER_INFO:	//������Ϣ
		{
			//CCLOG("������Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameServerInfo(pCommand,pData,wDataSize);
		}
	case MDM_GF_GAME:			//��Ϸ��Ϣ
		{
			//CCLOG("��Ϸ��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);

			return OnGameMessage(pCommand->wSubCmdID,pData,wDataSize);
		}
	case MDM_GF_FRAME:			//�����Ϣ
		{
			//CCLOG("�����Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnFrameMessage(pCommand->wSubCmdID,pData,wDataSize);
		}
	}
	return  true;
}

bool  RoomFrame::OnEventTcpRoomRead(CMD_Command* pCommand,void* pData,WORD wDataSize)
{
	switch (pCommand->wMainCmdID)
	{
	case MDM_GR_LOGON:			//��¼��Ϣ				1
		{
			//CCLOG("��½��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameLogin(pCommand,pData,wDataSize);
		}
	case MDM_GR_CONFIG:			//������Ϣ				2
		{
			//CCLOG("������Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameInfo(pCommand,pData,wDataSize);
		}
	case MDM_GR_USER:			//�û���Ϣ				3
		{
			//CCLOG("�û���Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameUser(pCommand,pData,wDataSize);
		}
	case MDM_GR_STATUS:			//������Ϣ				4
		{
			//CCLOG("״̬��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameStatus(pCommand,pData,wDataSize);
		}
	case MDM_GF_GAME:			//��Ϸ����				200
		{
			//CCLOG("��Ϸ��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);

			return OnGameMessage(pCommand->wSubCmdID,pData,wDataSize);
		}
	case MDM_GF_FRAME:			//�������				100
		{
			//CCLOG("�����Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnFrameMessage(pCommand->wSubCmdID,pData,wDataSize);
		}
	case MDM_GR_INSURE:			//���չ�����			5
		{
			return true;
		}
	case MDM_GR_MANAGE:			//��������				6
		{
			//CCLOG("������Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameServerInfo(pCommand,pData,wDataSize);
			return true;
		}
	case MDM_CM_SYSTEM:			//ϵͳ����				1000
		{
			//CCLOG("ϵͳ��Ϣ! file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketGameSystem(pCommand,pData,wDataSize);
		}
	case MDM_KN_COMMAND:			//�ں�����			0
		{
			return true;
		}
	}
	return  true;
}


//��¼��Ϣ
bool RoomFrame::OnSocketGameLogin(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	switch (pCommand->wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS: //��½�ɹ�
		{
			return OnSocketSubGRLogonSuccess(pBuffer, wDataSize);
			 
		}
	case SUB_GR_LOGON_FAILURE:   //��½ʧ��
		{
			return OnSocketSubGRLogonFailure(pBuffer, wDataSize);
		}
	case SUB_GR_LOGON_FINISH:  //��½���
		{
			CCLOG("----------------------gameserver login success!-------------------------- file(%s) line(%d)",__FILE__, __LINE__);
			return OnSocketSubGRLogonFinish(pBuffer, wDataSize);
			 
		}
	}
}

// �����¼�������봦��       add by wangjun
//��¼�ɹ�       add by wangjun
bool RoomFrame::OnSocketSubGRLogonSuccess(void *buffer, WORD size)
{
	CCLog("OnSocketSubGRLogonSuccess����������");
	//CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_GAMELINK,CCInteger::create(1));
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_LOGINFAIL,CCInteger::create(2));
	return true;
}

//��¼ʧ��       add by wangjun
bool RoomFrame::OnSocketSubGRLogonFailure(void *buffer, WORD size)
{
	EntityMgr::instance()->getDispatch()->closeGameSocket();
	CCLOG("game server login failed! file(%s) line(%d)",__FILE__, __LINE__);
	// ��������
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
				// ������ʾ
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
		// ������ʾ
		char str[100];
		MyNSString::wc2mbs(lf.szDescribeString, sizeof(lf.szDescribeString), str);
		CCLog(str);
	}

	CCLog("��¼ʧ��");
	return true;
}

//��¼���       add by wangjun
bool RoomFrame::OnSocketSubGRLogonFinish(void *buffer, WORD size)
{
	CCLog("��¼���");
	bool m_bStartType = EntityMgr::instance()->getDispatch()->getStartType();
	// ����״̬��������
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


	// ��Ϸ״̬������Ϸ
	if (EntityMgr::instance()->getDispatch()->m_cbStatus == US_PLAYING || EntityMgr::instance()->getDispatch()->m_cbStatus == US_READY)
	{
		EntityMgr::instance()->getDispatch()->SendPacketWithGameOption();

		m_bStartType = false;

		CCLog("��������");
		return true;
	}
}

//��ʾ����       add by wangjun
bool RoomFrame::OnSocketSubGRUpdateNotify(void *buffer, WORD size)
{
	return true;
}

//������½�ɹ���ʾ       add by wangjun
bool RoomFrame::OnSocketSubGRLogonNotify(void *buffer, WORD size)
{
	return true;
}

//�û���Ϣ
bool RoomFrame::OnSocketGameUser(CMD_Command* pCommand, void* pBuffer, WORD wDataSize)
{
	switch (pCommand->wSubCmdID)
	{
	case SUB_GR_USER_RULE:				// �û�����	1
		{
			CCLog("δ�����case");
			return true;
		}
	case SUB_GR_USER_LOOKON:			// �û��Թ�	2
		{
			CCLog("δ�����case");
			return true; 
		}
	case SUB_GR_USER_SITDOWN:			// �û�����	3	
		{
			CCLog("δ�����case");
			return true;
		}
	case SUB_GR_USER_STANDUP:			// �û�����	4
		{
			CCLog("δ�����case");
			return true;
		}
	case SUB_GR_USER_INVITE:			// �û�����	5
		{
			CCLog("�û�����δ����");
			return true;
		}
	case SUB_GR_USER_INVITE_REQ:		// ��������	6
		{
			CCLog("��������δ�����");
			return true;
		}
	case SUB_GR_USER_REPULSE_SIT:		// �ܾ�����	7
		{
			CCLog("�ܾ�����δ����7");
			return true;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
	case SUB_GR_USER_ENTER:				// �û�����	100
		{
			return OnSocketSubUserCome(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_USER_SCORE:				// �û�����	101
		{
			return OnSocketSubScore(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_USER_STATUS:			// �û�״̬	102
		{
			return OnSocketSubStatus(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_REQUEST_FAILURE:		// ����ʧ��	103
		{
			return OnSocketSubSitFailed(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_USER_CHAT:				// �û�����	201
		{
			return OnSocketSubChat(pCommand,pBuffer,wDataSize);
		}
	case SUB_GR_USER_EXPRESSION:		// �û�����	202
		{
			CCLog("δ�����case");
			return true;
		}
	case SUB_GR_WISPER_CHAT:			// �û�˽��	203
		{
			CCLog("δ�����case");
			return true;
		}
	case SUB_GR_WISPER_EXPRESSION:		// ˽�ı���	204
		{
			CCLog("δ�����case");
			return true;
		}
	case SUB_GR_COLLOQUY_CHAT:			//�Ự��Ϣ	205
		{
			CCLog("δ�����case");
			return true;
		}
	case SUB_GR_COLLOQUY_ERPRESSION:	// �Ự����	206
		{
			CCLog("δ�����case");
			return true;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
	case SUB_GR_PROPERTY_BUY:			// �������	300
		{
			CCLog("���߹���δ����");
			return true;
		}
	case SUB_GR_PROPERTY_SUCCESS:		// ���߳ɹ�	301
		{
			//return [self OnSocketPropBuySuccess:wSubCmdID buffer:buffer bufferSize:size];
		}
	case SUB_GR_PROPERTY_FAILURE:		// ����ʧ��	302		
		{
			//return [self OnSocketPropBuyFailure:wSubCmdID buffer:buffer bufferSize:size];
		}
	case SUB_GR_PROPERTY_MESSAGE:		// ������Ϣ	303 ������Ϣ������ʱû��ʲô��;
		{
			return true;
		}

		//case SUB_GP_USER_INSURE_INFO:           // ���չ����� 403
		//case SUB_GP_USER_INSURE_SUCCESS:        // ���չ�ɹ� 405
		//case SUB_GP_USER_INSURE_FAILURE:        // ���չ�ʧ�� 406
		{
			//return [self OnSocketRecvBankInfo:wSubCmdID buffer:buffer bufferSize:size];
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
	case SUB_GR_GET_BONUS:              // �������˷��ؽ�����Լ�������� 405      // add by mojunxin
		{
			//return [self OnSocketRecvSilverBonus:buffer bufferSize:size];
		}
	case SUB_GR_GET_ERROR:                  // ������䷵�ش�����Ϣ���� 1405
		{
			//return [self OnSocketRecvSilverBonusError:buffer bufferSize:size];
		}


		//////////////////////////////////////////////////////////////////////////////////////////////
	case SUB_GP_PAY_REVE_IP:             // appleӦ���ڹ�����ɣ�������������ֵ�����������صĽ��  601      // add by mojunxin
		{
			//return [self OnSocketGetIapResult:buffer bufferSize:size];
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
	default:
		{
			CCLog("δ�����case OnTCPNetworkMainGRUser wSubCmdID=%d", pCommand->wSubCmdID);
			return true;
		}
	}
	return true;
}
//������Ϣ
bool RoomFrame::OnSocketGameInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	switch (pCommand->wSubCmdID)
	{
	case SUB_GR_CONFIG_COLUMN:			// �б�����
		{
			return this->OnSocketSubGRConfigColumn(pBuffer, wDataSize);
		}
	case SUB_GR_CONFIG_SERVER:			// ��������
		{
			return this->OnSocketSubGRConfigServer(pBuffer, wDataSize);
		}
	case SUB_GR_CONFIG_PROPERTY:		// ��������
		{
			return this->OnSocketSubGRConfigPropepty(pBuffer, wDataSize);
		}
	case SUB_GR_CONFIG_FINISH:			// �������
		{
			return this->OnSocketSubGRConfigFinish(pBuffer, wDataSize);
		}
	default:
		//CCAssert(false, "δ�����case");
		return true;
	}
	return true;
}

// ������Ϣ�������봦��       add by wangjun
//�б�����       add by wangjun
bool RoomFrame::OnSocketSubGRConfigColumn(void *buffer, WORD size)
{
	CCLog("�б�����");
	return true;
}

//��������       add by wangjun
bool RoomFrame::OnSocketSubGRConfigServer(void *buffer, WORD size)
{
	CCLog("��������");
	// Ч���С
	if (size != sizeof(CMD_GR_ConfigServer)) return false;

	return true;
}

//��������       add by wangjun
bool RoomFrame::OnSocketSubGRConfigPropepty(void *buffer, WORD size)
{
	CCLog("��������");
	return true;
}

//�������       add by wangjun
bool RoomFrame::OnSocketSubGRConfigFinish(void *buffer, WORD size)
{
	CCLog("�������");
	return true;
}


//�����û�����
bool RoomFrame::OnSocketSubMatchUserCome(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	return true;
}
//״̬��Ϣ
bool RoomFrame::OnSocketGameStatus(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLog("��ȡ�û�״̬");
	return true;
}
//ϵͳ��Ϣ
bool RoomFrame::OnSocketGameSystem(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	//Ч�����
	CMD_GF_Message* pMessage=(CMD_GF_Message *)pBuffer;
	if (wDataSize<=(sizeof(CMD_GF_Message)-sizeof(pMessage->szContent)))
	{
		return false;
	}
	//��Ϣ����
	WORD wHeadSize= sizeof(CMD_GF_Message) - sizeof(pMessage->szContent);
	if (wDataSize != (wHeadSize + pMessage->wMessageLength * sizeof(char)))
	{
		return false;
	}
	pMessage->szContent[pMessage->wMessageLength-1]=0;
	 
	//    
	//    //�ж��ж�
	//    if (pMessage->wMessageType&SMT_CLOSE_GAME)
	//    {
	//        //        KillGameTimer(m_nTimerID);
	//        //        m_ChannelServiceHelper->CloseChannel(true,true); //���ܹر��ĵ���CloserFrame��Ҫ���÷�����Ϣ������
	//    }
	//    
	//    //ϵͳ��Ϣ
	//    if(pMessage->wMessageType&SMT_INFO)
	//    {
	//        //        m_pIClientKernelSink->InsertSystemString(pMessage->szContent);
	//    }
	//    
	//    //������Ϣ
	//    if (pMessage->wMessageType&SMT_EJECT)
	//    {
	//        //ShowMessageBox(pMessage->szContent,MB_ICONINFORMATION);
	//    }

	if (pMessage->wMessageType & SMT_GLOBAL)
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_MATCH);
		//        if(IDNO ==ShowInformationCellYesNo(pMessage->szContent,0,MB_ICONINFORMATION|MB_YESNO,TEXT("��λ��Ϣ�Ի���")))
		//            //IDNO ==ShowInformation(pMessage->szContent,10,MB_ICONINFORMATION|MB_YESNO))
		//        {
		//            //AfxMessageBox("�㲻ͬ��ѽ������ѡ��ͬ��ƥ������");
		//            SendQueuePacket(US_QUEUE_CELL_SAME);
		//sendQueuePacket(1);
		//        }
		//        else
		//        {
		//            //AfxMessageBox("��ͬ����ѽ������ѡ������ƥ������");
		//sendQueuePacket(2);
		//        }
	}

	//������Ϣ�͹̶���ʾ��Ϣ��Ӯ����Ϣ
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
	//        case SMT_TABLE_WINTIP:          //��Ӯ��
	//        {
	//            CCLOG("��Ӯ��");
	//            break;
	//        }
	//        case SMT_GLOBAL:                //������
	//        {
	//             CCLOG("������");
	//            break;
	//        }
	//        case SMT_TABLE_ANI:             //���ѵ�
	//        {
	//             CCLOG("���ѵ�");
	//            break;
	//        }
	//        case SMT_CLOSE_GAME:           //�رշ���
	//        {
	//             CCLOG("�رշ���");
	//            break;
	//        }
	//        default:
	//            break;
	//    }
	//
	//    //�رշ���
	//    if (pMessage->wMessageType&SMT_CLOSE_GAME)
	//    {
	//        m_bInquire=false;
	//        m_pIClientKernelSink->CloseGameFrame(true);
	//    }

	return true;
}
//������Ϣ
bool RoomFrame::OnSocketGameServerInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	return true;
}

//�û���Ϣ �û�����

bool RoomFrame::OnSocketSubUserCome(CMD_Command* pCommand, void* pBuffer, WORD wDataSize)
{
	string str = "�û�����";
	MyNSString::GBKToUTF8(str);
	CCLog(str.c_str());
	// ��������
	BYTE cbBuffer[sizeof(tagGameInUserInfo)];
	memset(cbBuffer, 0 , sizeof(tagGameInUserInfo));
	tagGameInUserInfo *pUserInfoHead = (tagGameInUserInfo *)cbBuffer;
	memcpy(pUserInfoHead, pBuffer, sizeof(tagGameInUserInfo));
	//CCLOG("�û�����! file(%s) line(%d)",__FILE__, __LINE__);
	BYTE bBuffer[sizeof(tagDataDescribe)];
	memset(bBuffer, 0 , sizeof(tagDataDescribe));
	tagDataDescribe *describe= (tagDataDescribe *)bBuffer;
	memcpy(describe, (BYTE *)pBuffer+sizeof(tagGameInUserInfo), sizeof(tagDataDescribe));

	//��ȡ������Ϣ
	tagUserData* pUserData = new tagUserData;
	memset(pUserData, 0, sizeof(tagUserData));
	memset(pUserData, 0, sizeof(tagUserData));
	// �û�����
	if (describe->wDataDecribe == DTP_GR_NICK_NAME){
		//memcpy(pUserData->szNickName, ((BYTE *)pBuffer+sizeof(tagGameInUserInfo)+sizeof(tagDataDescribe)), describe->wDataSize);
		MyNSString::wc2mbs((TCHART *)(((BYTE *)pBuffer+sizeof(tagGameInUserInfo)+sizeof(tagDataDescribe))), describe->wDataSize, pUserData->szNickName);
	}
	pUserData->dwGameID=pUserInfoHead->dwGameID;
	pUserData->dwUserID=pUserInfoHead->dwUserID;
	// ͷ����Ϣ
	pUserData->wFaceID=pUserInfoHead->wFaceID;
	// �û�����
	pUserData->cbGender=pUserInfoHead->cbGender;
	pUserData->cbMemberOrder=pUserInfoHead->cbMemberOrder;
	// �û�״̬
	pUserData->wTableID=pUserInfoHead->wTableID;
	pUserData->wChairID=pUserInfoHead->wChairID;
	pUserData->cbUserStatus=pUserInfoHead->cbUserStatus;
	// ������Ϣ
	pUserData->lScore=pUserInfoHead->lScore;
	// ��Ϸ��Ϣ
	pUserData->lWinCount=pUserInfoHead->dwWinCount;
	pUserData->lLostCount=pUserInfoHead->dwLostCount;
	pUserData->lDrawCount=pUserInfoHead->dwDrawCount;
	pUserData->lFleeCount=pUserInfoHead->dwFleeCount;
	pUserData->lExperience=pUserInfoHead->dwExperience;
	pUserData->lGoldEggs = 0;
	string dwellPlace = "�㶫ʡ������";
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

	// ����������ͼ
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

//1�����б����û�ԭ��״̬

//�û�״̬
bool RoomFrame::OnSocketSubStatus(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	//CCLOG("�����������������������������������������û�״̬!��������������������������������������������������");

	if (wDataSize!=sizeof(CMD_GR_UserStatus))
	{
		return false;
	}

	//��������
	BYTE cbBuffer[sizeof(CMD_GR_UserStatus)];
	memset(cbBuffer, 0 , sizeof(CMD_GR_UserStatus));
	CMD_GR_UserStatus *pUserStatus = (CMD_GR_UserStatus *)cbBuffer;
	memcpy(pUserStatus, pBuffer, sizeof(CMD_GR_UserStatus));

	CUserItem* pIUserItem = (CUserItem*)getUserItem(pUserStatus->dwUserID);
	if(pIUserItem == NULL && pUserStatus->UserStatus.cbUserStatus != US_NULL)
	{
		//��ȡ������Ϣ
		tagUserData* pUserData = new tagUserData;
		memset(pUserData, 0, sizeof(tagUserData));
		memset(pUserData, 0, sizeof(tagUserData));
		string nicknameString = "��ȡ�û���ʧ��";
		MyNSString::GBKToUTF8(nicknameString);
		memcpy(pUserData->szNickName, nicknameString.c_str(), sizeof(pUserData->szNickName));
		string dwellPlace = "�㶫ʡ������";
		MyNSString::GBKToUTF8(dwellPlace);
		memcpy(pUserData->szDwellingPlace, dwellPlace.c_str(), sizeof(pUserData->szDwellingPlace));
		pUserData->dwUserID=pUserStatus->dwUserID;
		pUserData->cbUserStatus = pUserStatus->UserStatus.cbUserStatus;
		pUserData->wTableID = pUserStatus->UserStatus.wTableID;
		pUserData->wChairID = pUserStatus->UserStatus.wChairID;
		// ������Ϣ
		pUserData->lScore=0;
		pUserData->lExperience=0;
		pUserData->lGoldEggs = 0;
		pIUserItem = (CUserItem*)insertItem(pUserData);
		EntityMgr::instance()->getDispatch()->SendPacketWithRequestChairUserInfo(pUserStatus->UserStatus.wTableID, pUserStatus->UserStatus.wChairID);
	}

	if (pIUserItem != NULL) 
	{
		//����״̬
		WORD wNowTableID=pUserStatus->UserStatus.wTableID;
		WORD wNowChairID=pUserStatus->UserStatus.wChairID;
		BYTE cbNowStatus=pUserStatus->UserStatus.cbUserStatus;

		//ԭ��״̬
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
				// ɾ���û�
				removeItem(pUserStatus->dwUserID);
				// ������Լ� �˳���Ϸ  -------�˳�������-------
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
				// �����û�
				updateUserStatus(pUserStatus->dwUserID,&status);
				// ������Լ��ж��Ƿ�����ʾ����
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
			// �����û�
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
				//���������û���Ϣ
				EntityMgr::instance()->getDispatch()->SendPacketWithRequestChairUserInfo(pUserStatus->UserStatus.wTableID, pUserStatus->UserStatus.wChairID);

				// �����ж�
				if (cbLastStatus < US_SIT)
				{
					EntityMgr::instance()->getDispatch()->SendPacketWithGameOption();
					// ������ MDM_GF_FRAME �� MDM_MB_LOGON ��ͻ��������ȡ�����
					CCNotificationCenter::sharedNotificationCenter()->postNotification("GameStart", NULL);
				}
			} else
			{ 
				//���������û���Ϣ
				EntityMgr::instance()->getDispatch()->SendPacketWithRequestChairUserInfo(pUserStatus->UserStatus.wTableID, pUserStatus->UserStatus.wChairID);
				if (pUserStatus->UserStatus.cbUserStatus == US_SIT) 
				{
					if (pMeUserData->wTableID != INVALID_TABLE && wNowTableID == pMeUserData->wTableID && wLastTableID != pMeUserData->wTableID) 
					{
						//String szStr;
						//if(useritem.GetMemberOrder() > 0){
						//	szStr = "VIP " + useritem.GetNickName() + " �����ǳ���";
						//	CGameClientView.onSubSystemMessage(szStr, false,true);
						//	HornRecord.addHornInfo(0,szStr);
						//}
					}
				}
			}

			// ����������ͼ
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


//�û�����
bool RoomFrame::OnSocketSubScore(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	//��������
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

		//С��500 ��ʾ�Ʋ�
		if (userScore.lScore < 500)
		{

		}
	}

	pIUserItem->setUserScore(&userScore);

	//CCLOG("======================%d",pUserScore->UserScore.lScore);			�����ı�--ˢ������
	tagUserBuffer tag;
	tag.dwUserID = pUserScore->dwUserID;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_PLAYERUPDATE,&tag);
	return true;
}
//�û�����
bool RoomFrame::OnSocketSubSort(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	return true;
	CCLOG("user sort! file(%s) line(%d)",__FILE__, __LINE__);
}
//�û�Ȩ��
bool RoomFrame::OnSocketSubRight(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user right! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//��Ա�ȼ�
bool RoomFrame::OnSocketSubMemberOrder(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user member order! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//����ʧ��
bool RoomFrame::OnSocketSubSitFailed(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user sit failed! file(%s) line(%d)",__FILE__, __LINE__);
	tagBankruptObj tag;
	tag.bBankrupt = true;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_BANKRUPT,&tag);
	return true;
}
//�û�����
bool RoomFrame::OnSocketSubChat(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user chat! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//�û�˽��
bool RoomFrame::OnSocketSubWisper(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user wisper! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//�������
bool RoomFrame::OnSocketSubUserInvite(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user invite! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//�μӱ���
bool RoomFrame::OnSocketJoinMatch(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("user join match! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//�޸��û����
bool RoomFrame::OnSocketSubGold(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("change user gold! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//��Ϸ������Ϣ
bool RoomFrame::OnSocketGameMatchInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("get match info! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//VIP����������Ϣ
bool RoomFrame::OnSocketVIPRoomPassWord(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("VIP room password! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}
//vip�����������
bool RoomFrame::OnSocketVIPErrorPassWord(CMD_Command* pCommand, void * pBuffer, WORD wDataSize)
{
	CCLOG("vip error password! file(%s) line(%d)",__FILE__, __LINE__);
	return true;
}

//�û������ɼ�
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

//������Ϣ(�����Ϣ������д�ĺ�����)
bool RoomFrame::OnFrameMessage(WORD wSubCmdID, const void* pBuffer, WORD wDataSize)
{
	CCLog("OnFrameMessage");
	switch (wSubCmdID)
	{
	case SUB_GF_GAME_OPTION:			// ��Ϸ����     1
		{
			CCLog("��Ϸ����");
			break;
		}
	case SUB_GF_USER_READY:				// �û�׼��     2
		{
			CCLog("�û�׼��");
			return true;
		}
	case SUB_GF_LOOKON_CONFIG:			//�Թ�����      3
		{
			CCLog("�Թ�����");
			return true;
		}
	case SUB_GF_USER_CHAT:				//�û�����      10
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
	case SUB_GF_USER_EXPRESSION:		//�û�����      11
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
	case SUB_GF_GAME_STATUS:			//��Ϸ״̬      100
		{
			//Ч�����
			//assert(wDataSize==sizeof(CMD_GF_Option));
			if (wDataSize!=sizeof(CMD_GF_Option))
			{
				return false;
			}

			//��Ϣ����
			CMD_GF_Option * pOption=(CMD_GF_Option *)pBuffer;
			m_cbGameStatus = pOption->bGameStatus;
			m_cbAllowLookon = pOption->bAllowLookon;

			CCLOG("gamestatus!");
			return true;
		}
	case SUB_GF_GAME_SCENE:				//��Ϸ����      101
		{
			//��Ϸ������Ϣ
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
	case SUB_GF_SYSTEM_MESSAGE:			//ϵͳ��Ϣ      200
		{

			//Ч�����
			CMD_CM_SystemMessage* pMessage=(CMD_CM_SystemMessage *)pBuffer;
			if (wDataSize<=(sizeof(CMD_CM_SystemMessage)-sizeof(pMessage->szString)))
			{
				return false;
			}
			//��Ϣ����
			//WORD wHeadSize= sizeof(CMD_GF_Message) - sizeof(pMessage->szContent);
			//if (wDataSize != (wHeadSize + pMessage->wMessageLength * sizeof(char)))
			//{
			//	return false;
			//}
			pMessage->szString[pMessage->wLength-1]=0;
			char message[1224];
			time_t tt = time(NULL);//��䷵�ص�ֻ��һ��ʱ��cuo
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
			//                case SMT_TABLE_WINTIP:          //��Ӯ��
			//                {
			//                    CCLOG("��Ӯ��");
			//                    break;
			//                }
			//                case SMT_GLOBAL:                //������
			//                {
			//                    CCLOG("������");
			//                    break;
			//                }
			//                case SMT_TABLE_ANI:             //���ѵ�
			//                {
			//                    CCLOG("���ѵ�");
			//                    break;
			//                }
			//                case SMT_CLOSE_GAME:           //�رշ���
			//                {
			//                    CCLOG("�رշ���");
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
	//case SUB_GR_CLIENT_START_GAME: //�ͻ���������ɣ�֪ͨ����
	//	{
	//		CCLOG("client lauch over,raise hand");
	//		EntityMgr::instance()->getDispatch()->sendSocketDate(MDM_GF_FRAME,SUB_GF_USER_READY);

	//		OnClientStartGame();
	//		return true;
	//	}

	//case SUB_GF_BANK_GET:				//�컰�ѷ�����Ϣ����
	//	{
	//		//Ч�����
	//		assert(wDataSize==sizeof(CM_GF_CHARGE));
	//		if (wDataSize!=sizeof(CM_GF_CHARGE)) return false;

	//		CM_GF_CHARGE *lpCharge = (CM_GF_CHARGE *)pBuffer;

	//		return true;
	//	}
	//case SUB_GF_CELL:				//��k��������������
	//	{

	//		CMD_GF_CELL_MESSAGE *pMessage = (CMD_GF_CELL_MESSAGE *)pBuffer;
	//		if (wDataSize<=(sizeof(CMD_GF_CELL_MESSAGE) - sizeof(pMessage->szContent))) return false;

	//		if (pMessage->wMessageType==SMT_CELL_USER_H)  //�û�����
	//		{
	//			//CCLOG("���������������û������ˣ�����������");
	//			g_GlobalUnits.m_nGabalUserLevel = SMT_CELL_USER_H;
	//		}
	//		if (pMessage->wMessageType==SMT_CELL_USER_L)  //�û�����
	//		{
	//			if(pMessage->lCellScoreL < 1 )//�Ʋ�
	//			{

	//			}else
	//			{
	//				//CCLOG("���������������û������ˣ�����������");
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

//�ͻ��˿�ʼ��Ϸ
void RoomFrame::OnClientStartGame()
{
	EntityMgr::instance()->getDispatch()->sendSocketDate(MDM_GF_GAME,SUB_C_ALL_READY);
}

//��ʼ�ͻ�����Ϸ
void RoomFrame::startClientGame()
{
	CCLOG("start game!");

	//��ȡ������������Ϣ
	BYTE cbBuffer[sizeof(CMD_GF_Info)];
	memset(cbBuffer, 0 , sizeof(CMD_GF_Info));
	CMD_GF_Info *Info = (CMD_GF_Info *)cbBuffer;
	Info->bAllowLookon= false;

	//������Ϣ
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
	//        CCLOG("�û����ݲ���ʧ�ܣ� file(%s) line(%d)",__FILE__, __LINE__);
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
	//CCLOG("�û�����%d,�Լ�����%d",nTableID,m_pMeUserItem->getTableID());
}

//�����Լ�����
void RoomFrame::updateMeTable(DWORD dwUserID)
{
	if (!EntityMgr::instance()->getDispatch()->isGameStatuc())
	{
		return;
	}

	//����״̬���id
	tagUserBuffer tag;
	tag.dwUserID = dwUserID;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_PLAYERUPDATE,&tag);
}
