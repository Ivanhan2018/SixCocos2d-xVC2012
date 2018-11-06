#include "SIX_ClientRoom.h"
#include "SIX_MatchEnd.h"

extern SIX_SceneGate *pSceneGate;
extern SIX_SceneGame *pSceneGame;

SIX_ClientRoom *SIX_ClientRoom::m_gClientRoom = 0;

SIX_ClientRoom::SIX_ClientRoom()
{
	m_tRaiseHandTime=0;
	m_tClientServerTimeInterval=0;
	memset(&m_FishListInfos[0],0,sizeof(m_FishListInfos));
}

SIX_ClientRoom::~SIX_ClientRoom()
{
}

void SIX_ClientRoom::Connect(const char *addr,int port)
{
	m_gClientRoom = SIX_ClientRoom::GetInstance();
#ifdef LOCAL_SERVER
	m_gClientRoom->init("127.0.0.1",port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass());
#else
	m_gClientRoom->init((char*)addr,port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass());
#endif
	m_gClientRoom->start();
}

void SIX_ClientRoom::Disconnect()
{
	SIX_PlayerMgr::GetInstance()->Destory();

	if (!m_gClientRoom)
		return;
	m_gClientRoom->stop();
}

void SIX_ClientRoom::HandlePacketRaw(int m_MainCode,int m_SubCode,unsigned char* m_Data,unsigned int m_DataLen)
{
	// ҵ����
	switch (m_MainCode)
	{
		// OnClose
	case -1:
		{
			switch (m_SubCode)
			{
				// ��ʼ�ǵ���Чֵ
			case CLOSE_TYPE_NO:
				{
					SIXLog("�ͻ�����Ч�ر�");
					break;
				}
				// �ͻ��������ر�
			case CLOSE_TYPE_CLIENT_CLOSE:
				{
					SIXLog("�ͻ��������ر�");
					this->setNeedExit(true);
					// ����ǳ�ʱ��δ�����ӵ����µĶϿ�����Ҫ�л��عؿ�����
					// ����Ҫ���޸�...
					// Cool.Cat
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						// �л����ؿ�����
						SIX_Proxy::GetInstance()->SetChangeScene(true);
					}
					break;
				}
				// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�
			case CLOSE_TYPE_FLASH_CLOSE:
				{
					SIXLog("��������");
					// Ӧ�������UI��ʾ
					// Cool.Cat
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
					{
						pSceneGate->ShowFlashBox(this,true);
						break;
					}
					else if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						pSceneGame->ShowFlashBox(this,true);
						break;
					}
					break;
				}
				// ����������رտͻ���
			case CLOSE_TYPE_SERVER_POWER_CLOSE:
				{
					SIXLog("����������ر�");
					// Ӧ�������UI��ʾ
					// Cool.Cat
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						this->setNeedExit(true);
						// �л����ؿ��������������ɷ���������رտͻ��ˣ�����Ҫ�ų�
						if (3 != PlayerTreasureInfo::Instance().m_lGameType)
							SIX_Proxy::GetInstance()->SetChangeScene(true);
					}
					break;
				}
			}
			break;
		}
	case 0:
		{
			switch (m_SubCode)
			{
				// OnConnect
			case CONNECT_SUCCESSED:
				{
					SIXLog("���ӳɹ������ڵ�¼����[%s:%d][%s][%s]...",
						this->GetRoomInfo()->szIP,
						this->GetRoomInfo()->iPort,
						this->GetRoomInfo()->szName,
						this->GetRoomInfo()->szPassword
					);
					this->login_room();
					break;
				}
				// OnConnect
			case RECONNECT_SUCCESSED:
				{
					SIXLog("���������ɹ�...");
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
					{
						pSceneGate->ShowFlashBox(this,false);
					}
					else if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						pSceneGame->ShowFlashBox(this,false);
					}
					this->setReconnect(true);
					this->login_room();
					//// ���������б�
					//this->query_table_list();
					//// �����û��б�
					//this->query_user_list();
					break;
				}
				// OnConnectFail
			case CONNECT_FAILED:
				{
					SIXLog("����ʧ��");
					break;
				}
				// OnCommError
			case COMM_ERROR:
				{
					SIXLog("����ͨѶ�쳣");
					break;
				}
				// OnSendFailed
			case SEND_ERROR:
				{
					SIXLog("����ʧ��");
					break;
				}
			default:
				{
					SIXLog("HandlePacketRaw.MainCode[%d].SubCode[%d].Unknown!",m_MainCode,m_SubCode);
					break;
				}
			}
			break;
		}
		// ������Ϣ
	case ROOM_MAIN:
		{
			HandlePacketRoom(m_SubCode,m_Data,m_DataLen);
			break;
		}
		// ������Ϣ
	case TABLE_MAIN:
		{
			HandlePacketTable(m_SubCode,m_Data,m_DataLen);
			break;
		}
		// ������Ϣ
	case MATCH_MAIN:
		{
			HandlePacketMatch(m_SubCode,m_Data,m_DataLen);
			break;
		}
	default:
		{
			SIXLog("HandlePacketRaw.MainCode[%d].Unknown!",m_MainCode);
			break;
		}
	}

	this->SendNetGapTime();
}

void SIX_ClientRoom::HandlePacketRoom(int subCode,unsigned char *pData,int pDataLen)
{
	switch (subCode)
	{
	case ROOM_SUB_LOGIN_FAIL:
		{
			LOGIN_ROOM_FAIL *packet = (LOGIN_ROOM_FAIL*)pData;
			SIXLog("�û���½ʧ��.iErrCode[%d]",packet->iErrCode);
			
			ShowMsgBox("�û���½ʧ��.iErrCode[%d]",packet->iErrCode);
			break;
		}
	case ROOM_SUB_RECOME:
		{
			RECOME_AFTER_CUT *recome = (RECOME_AFTER_CUT*)pData;
			SIXLog("[%s]������������.iTableNo[%d].iSeatNo[%d]",recome->szName,recome->iTableNo,recome->iSeatNo);
			break;
		}
	case ROOM_SUB_LOGIN_SUCC:
		{
			LOGIN_ROOM_SUCC* pReal = (LOGIN_ROOM_SUCC*)pData;

			_snprintf(this->GetLoginInfo().szIP, sizeof(this->GetLoginInfo().szIP), "%s", pReal->szIP);
			this->GetLoginInfo().iPort = pReal->iPort;
			this->GetLoginInfo().bAlreadyInRoom = pReal->bAlreadyInRoom;

			SIXLog("��¼�ɹ�...")
			LOGIN_ROOM_SUCC *packet = (LOGIN_ROOM_SUCC*)pData;
			USER_INFO_SIM pUserInfo = packet->userInfo;
			SIXLog("�Լ�[%lld]��szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]",
				pUserInfo.lUserId,
				SIX_Utility::GetInstance()->G2U(pUserInfo.szName).c_str(),
				SIX_Utility::GetInstance()->G2U(pUserInfo.szNickname).c_str(),
				pUserInfo.iTableNo,
				pUserInfo.iSeatNo,
				pUserInfo.lGoldLogin,
				pUserInfo.stUserState);

			//g_pShipMgr->mMyUserID = pUserInfo.lUserId;
			//g_pShipMgr->mPlayerList.clear();

			PLAYER_LIST *pPlayer = new PLAYER_LIST();
			pPlayer->iTableId = pUserInfo.iTableNo;
			pPlayer->SeatId = pUserInfo.iSeatNo;
			pPlayer->lGoldLogin = pUserInfo.lGoldLogin;
			pPlayer->lPointLogin = pUserInfo.lPointLogin;
			pPlayer->UserIdx = pUserInfo.lUserId;
			memcpy(pPlayer->szName, pUserInfo.szName, sizeof(pPlayer->szName));
			memcpy(pPlayer->szNickname, pUserInfo.szNickname, sizeof(pPlayer->szNickname));
			if (!SIX_PlayerMgr::GetInstance()->Add(pPlayer->UserIdx,pPlayer))
			{
				//// �п��ܿͻ������������Ϻ����������ϣ�����������ܻ����ʧ�ܣ�Ӧ�ò����κδ���
				//// Cool.Cat
				//CCAssert(0,"AddSelfPlayer.Error!");
				//return;
			}

			SIX_PlayerMgr::GetInstance()->setMyUserIdx(pPlayer->UserIdx);

			// Ҫ����Ƿ��ڷ��䳡��
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
			{
				// UI��ʾ
				pSceneGate->getRoomList()->ShowTableLoading(false);
#ifdef WIN32
				CCString *title = CCString::createWithFormat("%s - [%d.%d.%d.%04d] - %s[%s][%lld]",PROJECT_NAME,VER_MAIN,VER_CHILD,VER_STAGE,VER_BUILD,pUserInfo.szName,pUserInfo.szNickname,pUserInfo.lUserId);
				CCEGLView::sharedOpenGLView()->setWindowTitle(title->getCString());
#endif
				//ShowMsgBox("��¼�ɹ���\n+++ ��ĸ������� +++\n�û�ID��%lld\n�û�����%s\n�ǡ��ƣ�%s",pUserInfo.lUserId,pUserInfo.szName,pUserInfo.szNickname);
			}
			break;
		}
	case ROOM_SUB_TABLE_LIST:
		{
			SIXLog("���������б�...");
			SERVER_ROOM_INFO_SIM *packet = (SERVER_ROOM_INFO_SIM*)pData;
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
			{
				// �������ķ��䲻���Զ�������
				if (!pSceneGate->getRoomList()->getAutoSit())
					pSceneGate->getRoomList()->RefreshTableList(packet->iRoomPeopleCount,packet->iTables,packet->iSeatNum);
			}
			//add by Ivan_han 20130716
			PlayerTreasureInfo::Instance().m_lGameType=packet->lGameType;
			PlayerTreasureInfo::Instance().m_iBasePoint=packet->iBasePoint;
			break;
		}
	/*case ROOM_SUB_TABLE_LIST_OVER:
		{
			SIXLog("���������б����...");
			break;
		}*/
	case ROOM_SUB_USER_LIST:
		{
			SIXLog("��������б�...");
			USER_INFO_SIM *pUserInfo = (USER_INFO_SIM*)pData;

			//add by Ivan_han 20130904
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
			{
				if(pSceneGate->getConsoleGM())
				{
					pSceneGate->getConsoleGM()->ON_ROOM_SUB_USER_LIST(pUserInfo->lUserId,SIX_Utility::GetInstance()->G2U(pUserInfo->szName).c_str(),SIX_Utility::GetInstance()->G2U(pUserInfo->szNickname).c_str(),pUserInfo->stUserState,pUserInfo->iTableNo,pUserInfo->iSeatNo,pUserInfo->lGoldLogin,pUserInfo->lPointLogin);
				}
			}

			// �û��Ѿ�����
			if (SIX_PlayerMgr::GetInstance()->Get(pUserInfo->lUserId))
			{
				if (SIX_PlayerMgr::GetInstance()->getMyUserIdx()==pUserInfo->lUserId)
				{
					SIX_PlayerMgr::GetInstance()->setMyTableIdx(pUserInfo->iTableNo);
					SIX_PlayerMgr::GetInstance()->setMySeatIdx(pUserInfo->iSeatNo);
				}
				return;
			}

			SIXLog("���[%lld]��szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]",
				pUserInfo->lUserId,
				SIX_Utility::GetInstance()->G2U(pUserInfo->szName).c_str(),
				SIX_Utility::GetInstance()->G2U(pUserInfo->szNickname).c_str(),
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);

				PLAYER_LIST * pPlayerList = new PLAYER_LIST();
				pPlayerList->iTableId = pUserInfo->iTableNo;
				pPlayerList->SeatId = pUserInfo->iSeatNo;
				pPlayerList->UserIdx = pUserInfo->lUserId;
				//add by Ivan_han 20130713
				pPlayerList->lGoldLogin = pUserInfo->lGoldLogin;
				pPlayerList->lPointLogin = pUserInfo->lPointLogin;
				memcpy(pPlayerList->szName, pUserInfo->szName, sizeof(pPlayerList->szName));
				memcpy(pPlayerList->szNickname, pUserInfo->szNickname, sizeof(pPlayerList->szNickname));

				//g_pShipMgr->mPlayerList.push_back(pPlayerList);
				if (!SIX_PlayerMgr::GetInstance()->Add(pPlayerList->UserIdx,pPlayerList))
				{
					CCAssert(0,"AddPlayer.Error!");
					return;
				}

			// -- ����Ѿ����µģ�����ͷ��
			if (pUserInfo->lUserId!=INVALID_USER_ID && pUserInfo->iTableNo!=INVAL_TABLE_NO && pUserInfo->iSeatNo!=INVAL_SEAT_NO)
			{
				if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
				{
					// �������ķ��䲻���Զ�������
					if (!pSceneGate->getRoomList()->getAutoSit())
						pSceneGate->getRoomList()->SwitchSitDownOrLeaveSeat(pUserInfo->lUserId,pUserInfo->iTableNo,pUserInfo->iSeatNo,true);
				}
			}
			break;
		}
		
	case ROOM_SUB_USER_LIST_OVER:
		{
			SIXLog("��������б����...");
			// Ҫ�жϵ�ǰ����
			// Cool.Cat
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
			{
				pSceneGate->getMatchList()->AutoSqueue();
				pSceneGate->getMatchList()->setLoginRoomSuccess( true );

				// �������ķ������Զ�������
				if (pSceneGate->getRoomList()->getAutoSit())
				{
					// ���ƿ��ٿ�ʼ��ť
					pSceneGate->getRoomList()->ShowQucikStart();
				}

				// ����Լ��Ѿ�����λ��Ϣ��˵���Լ��Ƕ��߽����ģ���ֱ�����Լ�����Ϸ
				if (SIX_PlayerMgr::GetInstance()->getMyTableIdx()!=-1 && SIX_PlayerMgr::GetInstance()->getMySeatIdx()!=-1)
				{
					SIX_Proxy::GetInstance()->SetChangeScene(true);
					SIXLog("��������,�л�����...");
				}
			}
			break;
		}
	case ROOM_SUB_LEAVE_ROOM:
		{
			USER_INFO *pUserInfo = (USER_INFO*)pData;
			SIXLog("[%lld][%d/%d][%s][%s]�뷿�ɹ�",
				pUserInfo->lUserId,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				SIX_Utility::GetInstance()->G2U(pUserInfo->szName).c_str(),
				SIX_Utility::GetInstance()->G2U(pUserInfo->szNickname).c_str());
			// �������������뷿��ͬʱ�Լ����ڷ��䳡������Ҫ���������ҵ���λ
			// Cool.Cat
			if (pUserInfo->lUserId!=INVALID_USER_ID && pUserInfo->iTableNo!=INVAL_TABLE_NO && pUserInfo->iSeatNo!=INVAL_SEAT_NO)
			{
				if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
				{
					pSceneGate->getRoomList()->SwitchSitDownOrLeaveSeat(pUserInfo->lUserId,pUserInfo->iTableNo,pUserInfo->iSeatNo,false);
				}
			}
			SIX_PlayerMgr::GetInstance()->Del(pUserInfo->lUserId);
			break;
		}
	case ROOM_SUB_ROOM_USER_COUNT:
		{
			CMD_RoomUserCount *pRoomUserCount = (CMD_RoomUserCount *)pData;
			SIXLog("����ͳ�ƣ���������[%d]���Ŷ�����[%d]", pRoomUserCount->iRoomUserCount, pRoomUserCount->iArrangeQueueCount);
			break;
		}
	default:
		{
			SIXLog("HandlePacketRoom.subCode[%d].Unknown!",subCode);
			//ShowMsgBox(CCString::createWithFormat("HandlePacketRoom.subCode[%d].Unknown!",subCode)->getCString(),0);
			break;
		}
	}
}

void SIX_ClientRoom::HandlePacketTable(int subCode,unsigned char *pData,int pDataLen)
{
	switch (subCode)
	{
	case TABLE_SUB_SITDOWN:
		{
			SITDOWN *packet = (SITDOWN*)pData;
			switch (packet->iRes)
			{
				// ok
			case RET_TABLE_OPERATE_SUCCEED:
				{
					//if (!g_pShipMgr->ExistUserPlayer(packet->lUserId))
					//{// �������û��������µ�¼
					//	return ;
					//}
					////�Ƚ�����ҵ�����б�����ҲҪ���£�add by Ivan_han 20130715
					//PLAYER_LIST *pPlayerList = NULL;
					//g_pShipMgr->GetUserPlayer(packet->lUserId, &pPlayerList);
					PLAYER_LIST *pPlayerList = SIX_PlayerMgr::GetInstance()->Get(packet->lUserId);
					if (!pPlayerList)
						return;
					//if (NULL != pPlayerList)
					//{
						pPlayerList->iTableId=packet->iTableNo;	// ����
						pPlayerList->SeatId=packet->iSeatNo;	// ��λ��
						pPlayerList->lGoldLogin = packet->lGoldLogin;
						pPlayerList->lPointLogin = packet->lPointLogin;
					//}

					//if (-1 == g_pShipMgr->mMyTableID)
					if (packet->iTableNo!=-1 && packet->iSeatNo!=-1)
					{
						if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
							pSceneGate->getRoomList()->SwitchSitDownOrLeaveSeat(packet->lUserId,packet->iTableNo,packet->iSeatNo,true);
					}
					//if (packet->lUserId==g_pShipMgr->mMyUserID)
					if (packet->lUserId==SIX_PlayerMgr::GetInstance()->getMyUserIdx())
					{
						// -- ������־λ����update����ȥ�л���������������������Ƚ�����
						SIX_PlayerMgr::GetInstance()->setMySeatIdx(packet->iSeatNo);
						SIX_PlayerMgr::GetInstance()->setMyTableIdx(packet->iTableNo);
						SIX_Proxy::GetInstance()->SetChangeScene(true);
						SIXLog("�л�����...");
					}
					// ���Լ�ͬ�����������
					else if (packet->iTableNo == SIX_PlayerMgr::GetInstance()->getMyTableIdx())
					{
						CCLayerColor *pBG = dynamic_cast<CCLayerColor*>(pSceneGame->getChildren()->objectAtIndex(0));
						g_pShipMgr->Enter(pBG, packet->lUserId, packet->iSeatNo, false);
					}

					break;
				}
			case RET_TABLE_CHAIR_ERROR:
				{
					SIXLog("����ʧ�ܣ�ʧ��ԭ�򣺸���λ�����ڣ�");
					ShowMsgBox("����ʧ�ܣ�ʧ��ԭ�򣺸���λ�����ڣ�");
					break;
				}
			case RET_TABLE_CHAIR_OCCUPY:
				{
					SIXLog("����ʧ�ܣ�ʧ��ԭ�򣺸���λ�Ѿ���������");
					ShowMsgBox("����ʧ�ܣ�ʧ��ԭ�򣺸���λ�Ѿ���������",0);
					break;
				}
			case RET_TABLE_TABLE_START:
				{
					SIXLog("����ʧ�ܣ�ʧ��ԭ�������Ѿ���ʼ����������������ˣ�");
					ShowMsgBox("����ʧ�ܣ�ʧ��ԭ�������Ѿ���ʼ����������������ˣ�",0);
					break;
				}
			case RET_TABLE_ENTER_GOLD_LACK:
				{
					SIXLog("����ʧ�ܣ�ʧ��ԭ�򣺽�Ҳ�����������ӣ�");
					ShowMsgBox("����ʧ�ܣ�ʧ��ԭ�򣺽�Ҳ�����������ӣ�",0);
					break;
				}
			}
			break;
		}
/*	case TABLE_SUB_USER_INFO:		// �����ɹ�����ȡ����������������б�
		{
			SIXLog("������������б�...");
			USER_INFO_SIM *pUserInfo = (USER_INFO_SIM*)pData;
			if (NULL != pUserInfo)
			{
				PLAYER_LIST *pPlayerList = NULL;
				g_pShipMgr->GetUserPlayer(pUserInfo->lUserId, &pPlayerList);
				if (NULL != pPlayerList)
				{
					pPlayerList->lGoldLogin = pUserInfo->lGoldLogin;
					pPlayerList->lPointLogin = pUserInfo->lPointLogin;
				}
			}
			break;
		}
	case TABLE_SUB_SITDOWN_FINISH:				// �û��������
		{
			SIXLog("�������...");
			break;
		}*/
	case TABLE_SUB_LEAVE_SEAT:
		{
			LEAVE_SEAT *packet = (LEAVE_SEAT*)pData;
			switch (packet->iRes)
			{
			case 0:
				{
					// ����ж�Ҫȥ��
					// Cool.Cat
					//if (NULL==g_pShipMgr->getMySelfShip()  ||  packet->lUserId == g_pShipMgr->getMySelfShip()->m_UserID)
					//	return;

					if (-1 == SIX_PlayerMgr::GetInstance()->getMyTableIdx())
					{
						if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
							pSceneGate->getRoomList()->SwitchSitDownOrLeaveSeat(packet->lUserId,packet->iTableNo,packet->iSeatNo,false);
					}

					//vector<PLAYER_LIST*>::const_iterator it = g_pShipMgr->mPlayerList.begin();
					//for (; it != g_pShipMgr->mPlayerList.end(); ++it )
					//{
					//	PLAYER_LIST * pPlayer = *it;
					//	if (pPlayer->SeatId == packet->iSeatNo  &&  pPlayer->iTableId == packet->iTableNo)
					//	{
					//		g_pShipMgr->Leave( packet->lUserId );
					//		g_pShipMgr->mPlayerList.erase( it );
					//		break;
					//	}
					//}

					SIXLog("[%d][%d][%lld]�����ɹ�",packet->iTableNo,packet->iSeatNo,packet->lUserId);
					SIX_PlayerMgr::GetInstance()->LeaveSeat(packet->lUserId,packet->iTableNo,packet->iSeatNo);
					break;
				}
			case 5:
			case 10:
				{
					SIXLog("�뿪��λʧ�ܣ�ʧ��ԭ�򣺸���λ�����ڣ�");
					ShowMsgBox("�뿪��λʧ�ܣ�ʧ��ԭ�򣺸���λ�����ڣ�",0);
					break;
				}
			case 20:
				{
					SIXLog("�뿪��λʧ�ܣ�ʧ��ԭ�򣺸���λ�ϻ�û�������أ�");
					ShowMsgBox("�뿪��λʧ�ܣ�ʧ��ԭ�򣺸���λ�ϻ�û�������أ�",0);
					break;
				}
			}
			break;
		}
	case TABLE_SUB_RECOMEAFTERCUT:
		{
			CMD_SC_RECOMEAFTERCUT *pRecome = (CMD_SC_RECOMEAFTERCUT*)pData;
			break;
		}
	case TABLE_SUB_INIT_GAME:
		{
			INIT_GAME *pInit = (INIT_GAME *)pData;
			if (NULL == pInit  && SCENES_MIN > pInit->iScenesID  &&  SCENES_MAX < pInit->iScenesID)
			{
				CCAssert(0,"");
				break;
			}
			if(NULL == pSceneGame)
			{
				CCAssert(0,"");
				break;
			}
			
			// ��ǰʱ�� - �Ѿ�����ʱ�� = �ͻ��˿���������ʱ�̣�����CK��
			//ULONGLONG ullRunTime = SIX_ClientRoom::GetTickCount64();//c2
			ULONGLONG ullRunTime = SIX_Utility::GetInstance()->GetTickCount();
			//ULONGLONG ullRunTime1 = CEasyDataTime::get_current_time_diff_millitm_from_1970();//�ͻ����հ�������ʱ�̣�����CT��
			ULONGLONG ullRunTime1 = SIX_Utility::GetInstance()->GetTickCount();
			ULONGLONG tStartComputerTime =ullRunTime1 - ullRunTime;//CK
			/*
				add by Ivan_han 20130628
				�Ƿ����ӳ�Ϊ��'�������������������ʱ��Ϊ��S��0���հ��ӳ�Ϊ�š֦�'��ʱ��ͬ����Ϣ����ʱ��Ϊc2�����հ��ӳ٦š�(c2-c1)/2
			*/
			ULONGLONG Epsilon=(ullRunTime-m_tRaiseHandTime)/2;
			long long dT=pInit->tCurrentServerTime-ullRunTime1+Epsilon;//dT=ST-CT+�ţ���>0�������հ��ӳ٣���ʾ��ͬһ��ʵʱ�̣��������˵���CEasyDataTime::get_current_time_diff_millitm_from_1970()��ֵ��ͻ��˶˵���CEasyDataTime::get_current_time_diff_millitm_from_1970()��ֵ��ʱ���
			/*
			    add by Ivan_han 20130612
				m_tClientServerTimeInterval=��t=CK-SK+dT��ʾ��ͬһ��ʵʱ�̣��ͻ��˵���GetTickCount64()��ֵ��������˵���GetTickCount64()��ֵ��ʱ��
				����������ͻ�����ͬһ̨������ʱ����t=0��
				��Ȼ��t��һ���͵��ڿͻ��˿�������ʵʱ����������˿�������ʵʱ�̵�ʱ��
				��Ϊ�ͻ��ˡ�������������ʵʱ����ܲ�һ�£�
				���ǲ��ܿͻ��ˡ����������Ƿ�����ʵʱ���Ƿ�һ�£���t�������õġ�
				һ����˵���ٶ��ͻ��ˡ�������������ʵʱ�䶼һ�µ����������t>0<=>CK>SK��ʾ���������ȿ�����
			*/
			m_tClientServerTimeInterval = (tStartComputerTime - pInit->tServerTime+dT);//��t=CK-SK+dT
			pSceneGame->RefreshScenes( pInit->iScenesID );
			g_pBulletMgr->m_uiMaxBulletCount = pInit->uiBulletMaxCount;
			break;
		}
	case TABLE_SUB_FIRE:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			SHOT_FIRE *pReal = (SHOT_FIRE*)pData;
			switch (pReal->iRes)
			{
			case 0:
				{
					if (pReal->iUserID != g_pShipMgr->getMySelfShip()->m_UserID)
					{
						CCPoint ptDes(pReal->fDesPT.x, pReal->fDesPT.y);
						ptDes = g_pShipMgr->SP2CP( ptDes );
						g_pShipMgr->onShootBullet(pReal->iUserID, pReal->iID, ptDes, pReal->bRepeatShoot,false);
					}
					//add by Ivan_han 20130716
					CShip *pShip=g_pShipMgr->getShip(pReal->iUserID);
					if(pShip)
					{
						pShip->setBulletCount(pReal->iUserBulletCount);
					}
					break;
				}
			case RET_GAME_ERROR_CODE_BULLET_LACK:	// add by cxf
				{
					// �û��ӵ�����
					if (pReal->iUserID == g_pShipMgr->getMySelfShip()->m_UserID)
						ShowMsgBox("�ӵ��������빺���ӵ���",0);
					break;
				}
			default: break;
			}
			break;
		}
	case TABLE_SUB_REFLECTION:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			BULLET_REFLECTION *pReflection = (BULLET_REFLECTION*)pData;
			if ( 0 == pReflection->iRes )
			{
				CCPoint ptCur(pReflection->fCurPos.x, pReflection->fCurPos.y);
				CCPoint ptMove(pReflection->fMovePos.x, pReflection->fMovePos.y);
				ptCur = g_pShipMgr->SP2CP( ptCur );
				//ptMove = g_pShipMgr->SP2CP( ptMove );
				ptMove = g_pShipMgr->SD2CD( ptMove );
				g_pBulletMgr->onReflectionBullect(pReflection->llUserID, pReflection->llID, TPoint(ptCur.x, ptCur.y), pReflection->fCurRotation, TPoint(ptMove.x, ptMove.y), pReflection->fMoveTime, pReflection->iReflectionCount, pReflection->iReflectionMax);
			}
			break;
		}
	case TABLE_SUB_CAPTURE_FISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			CAPTURE_FISH *pReal = (CAPTURE_FISH*)pData;
			if ( 0 == pReal->iRes )
			{
				//g_FishMgr->CaptureOneFish( pReal->llUserID, pReal->llBulletID, pReal->chFishID, pReal->chDeadFishID );
				//add by Ivan_han 20130718
				vector<unsigned int> vFishID(pReal->FishIDs,pReal->FishIDs+pReal->nFishCount);
				vector<unsigned int> vDeadFishID;
				for(unsigned int i=0;i<pReal->nDeadFishCount;i++)
				{
					vDeadFishID.push_back((*pReal)[i]);
				}
				g_FishMgr->CaptureFish( pReal->llUserID, pReal->llBulletID,vFishID,vDeadFishID,pReal->FallIntegral,pReal->GunGrade,pReal->DeadFullScreenBombFishID);
				//add by Ivan_han 20130716
				CShip *pShip=g_pShipMgr->getShip(pReal->llUserID);
				if(pShip)
				{
					if (pReal->FallIntegral>0)
						pShip->setFishCoin(pReal->llUserGameCoinCount);
				}
				//add by Ivan_han 20130724
				if (pReal->llUserID == g_pShipMgr->getMySelfShip()->m_UserID)
				{
					PlayerTreasureInfo::Instance().UpdateFishKindNums(pReal->FishKindNums);
				}
				break;
			}
			break;
		}
	//add by Ivan_han 20130713
	case TABLE_SUB_BUY_BULLET_RET:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			USER_BUY_BULLET_RET *pReal = (USER_BUY_BULLET_RET*)pData;
			switch (pReal->iRes)
			{
			case RET_GAME_OPERATE_SUCCEED:
				{
					CShip *pShip = g_pShipMgr->getShip( pReal->llUserID);
					if (NULL == pShip)
						return;
					unsigned long long llBulletNum=g_pShipMgr->getMySelfShip()->getBulletCount()+pReal->iBulletNum;
					pShip->setBulletCount(llBulletNum);
					pShip->setGoldCoin(pReal->llGold,3,false);
					break;
				}
			case RET_GAME_USER_NOT_EXIST:
				{
					ShowMsgBox("�û�������",0);
					break;
				}
			case RET_GAME_BUY_BULLET_GOLD_LACK:
				{
					ShowMsgBox("��Ҳ��������ӵ�",0);
					break;
				}
			default: break;
			}

			break;
		}
	//add by Ivan_han 20130713
	case TABLE_SUB_WRITE_SCORE_RET:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			WRITE_SCORE_RESULT *pReal = (WRITE_SCORE_RESULT*)pData;
			switch (pReal->iRes)
			{
			case 0:
				{
					CShip *pShip = g_pShipMgr->getShip( pReal->lUserId);
					if (NULL == pShip)
						return;
					pShip->setFishCoin(0);
					pShip->setBulletCount(0);
					if(PlayerTreasureInfo::Instance().m_lGameType==2||pReal->lGold>0)
						pShip->setGoldCoin(pReal->lGold,3,true);
					else
						pShip->setGoldCoin(pReal->lPoint,3,true);
					break;
				}
			default: break;
			}

			// ֻ�д���Ϸ�����л�����ʱ�ſ��ܽ�������
			// Cool.Cat
			if (pSceneGame->IsWaitForChangeScene())
			{
				SIX_Proxy::GetInstance()->SetChangeScene(true);
				return;
			}
			break;
		}
	//add by Ivan_han 20130724
	case RSP_SET_GUNGRADE:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Req_SetGunGrade *pReal = (Req_SetGunGrade*)pData;
			switch (pReal->iRes)
			{
			case RET_GAME_OPERATE_SUCCEED:
				{
					CShip *pShip = g_pShipMgr->getShip( pReal->llUserID);
					if (NULL == pShip)
						return;
					pShip->setGunGrade(pReal->GunGrade);
					if (NULL != pShip->m_gun)
						pShip->m_gun->m_curGunType=pReal->GunGrade;
					break;
				}
			case RET_GAME_USER_NOT_EXIST:
				{
					ShowMsgBox("�û�������",0);
					break;
				}
			default: break;
			}
			break;
	}
	case RSP_USER_SHOOT:
		{
			break;
		}
    //add by Ivan_han 20130902
	case TABLE_SUB_ANTI_ADDICTION:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			CMD_SC_ANTI_ADDICTION *pReal = (CMD_SC_ANTI_ADDICTION*)pData;
			pSceneGame->SetSysTip(pReal->szContent);
			SIX_Utility::GetInstance()->performWithDelay(pSceneGame,callfunc_selector(SIX_SceneGame::ClearSysTip),30);
			break;
		}
	//add by Ivan_han 20130806
	case RSP_CHANGE_SCENE:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			if(g_FishMgr)
				g_FishMgr->SpeedUpAllFish();

			Rsp_ChangeScene *pReal = (Rsp_ChangeScene*)pData;
			if (0 < SIX_PopWnd::GetPopWndCount())
				return;
			pSceneGame->RiseTide(pReal->SeaSceneKind, 4.0f, 0.1f,pReal->bRToL);
			break;
		}
	case RSP_ADD_ONE_FISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish *pReal = (Rsp_AddOneFish*)pData;
			//TBuildTraceTime ClientBuildTime=SIX_ClientRoom::GetTickCount64();
			TBuildTraceTime ClientBuildTime = SIX_Utility::GetInstance()->GetTickCount();
			long long llInitElapsed=ClientBuildTime-pReal->BuildTraceTime+m_tClientServerTimeInterval;
			float InitElapsed =llInitElapsed * 0.001;
			OnAddOneFish(pReal,InitElapsed,pReal->BuildTraceTime);
			break;
		}
	case RSP_ADD_ONE_FISH_ARR:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish_Arr *pReal = (Rsp_AddOneFish_Arr*)pData;
			//TBuildTraceTime ClientBuildTime=SIX_ClientRoom::GetTickCount64();
			TBuildTraceTime ClientBuildTime = SIX_Utility::GetInstance()->GetTickCount();
			for(int i=0;i<(int)(pReal->nFishCount);i++)
			{
				long long llInitElapsed=ClientBuildTime-pReal->Arr[i].BuildTraceTime+m_tClientServerTimeInterval;
				float InitElapsed =llInitElapsed * 0.001;
				OnAddOneFish(&pReal->Arr[i],InitElapsed,pReal->Arr[i].BuildTraceTime);
			}
			break;
		}
	case RSP_ADD_ONE_FISH_LIST:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish_List *pReal = (Rsp_AddOneFish_List*)pData;
			//TBuildTraceTime ClientBuildTime=SIX_ClientRoom::GetTickCount64();
			TBuildTraceTime ClientBuildTime = SIX_Utility::GetInstance()->GetTickCount();
			//SIX_Utility::GetInstance()->TimerStart();
			for(int i=0;i<(int)(pReal->nFishCount);i++)
			{
				long long llInitElapsed=ClientBuildTime-(*pReal)[i].BuildTraceTime+m_tClientServerTimeInterval;
				float InitElapsed =llInitElapsed * 0.001;
				OnAddOneFish(&(*pReal)[i],InitElapsed,(*pReal)[i].BuildTraceTime);
			}
			//SIX_Utility::GetInstance()->TimerEnd();
			//double time = SIX_Utility::GetInstance()->Fixed(SIX_Utility::GetInstance()->GetMilliseconds(),4);
			//SIXLog("RSP_ADD_ONE_FISH_LIST.time[%04f]",time);
			break;
		}
	case RSP_ADD_ONE_FISH_LIST_UNFINISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish_List *pReal = (Rsp_AddOneFish_List*)pData;
			//SIXLog("BusyFishListCount()=%d",BusyFishListCount());
			int ret=IsNeedMalloc(pReal->FishGroupID);
			if(ret)
			{
				FishListInfo *pInfo=GetFishListInfo(pReal->FishGroupID,true);
				if(pInfo==NULL)
					return;
				pInfo->pReal=(Rsp_AddOneFish_List *)malloc(sizeof(Rsp_AddOneFish_List)+sizeof(Rsp_AddOneFish)*pReal->nTotalFishCount);
				pInfo->FishGroupID=pReal->FishGroupID;
				pInfo->RecvCount=pReal->nFishCount;
				memcpy(pInfo->pReal,pReal,sizeof(Rsp_AddOneFish_List)+sizeof(Rsp_AddOneFish)*pReal->nFishCount);
			}
			else
			{
				FishListInfo *pInfo=GetFishListInfo(pReal->FishGroupID,false);
				if(pInfo==NULL)
					return;
				memcpy(&(*(pInfo->pReal))[pInfo->RecvCount],&(*pReal)[0],sizeof(Rsp_AddOneFish)*pReal->nFishCount);
				pInfo->RecvCount+=pReal->nFishCount;
				pInfo->pReal->nFishCount+=pReal->nFishCount;
			}
			//for(int i=0;i<pReal->nFishCount;i++)
			//{
			//	m_vecFish.push_back((*pReal)[i]);
			//}
			break;
		}
	case RSP_ADD_ONE_FISH_LIST_FINISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish_List *pReal = (Rsp_AddOneFish_List*)pData;
			//SIXLog("BusyFishListCount()=%d",BusyFishListCount());
			//for(int i=0;i<pReal->nFishCount;i++)
			//{
			//	m_vecFish.push_back((*pReal)[i]);
			//}
			FishListInfo *pInfo=GetFishListInfo(pReal->FishGroupID,false);
			if(pInfo==NULL)
				return;
			memcpy(&(*(pInfo->pReal))[pInfo->RecvCount],&(*pReal)[0],sizeof(Rsp_AddOneFish)*pReal->nFishCount);
			pInfo->RecvCount+=pReal->nFishCount;
			pInfo->pReal->nFishCount+=pReal->nFishCount;
			Rsp_AddOneFish_List *pReal1 =pInfo->pReal;
			//TBuildTraceTime ClientBuildTime=SIX_ClientRoom::GetTickCount64();
			TBuildTraceTime ClientBuildTime = SIX_Utility::GetInstance()->GetTickCount();
			for(int i=0;i<(int)(pReal1->nTotalFishCount);i++)
			{
				long long llInitElapsed=ClientBuildTime-(*pReal1)[i].BuildTraceTime+m_tClientServerTimeInterval;
				float InitElapsed =llInitElapsed * 0.001;
				OnAddOneFish(&(*pReal1)[i],InitElapsed,(*pReal1)[i].BuildTraceTime);
			}

			//m_vecFish.clear();
			free(pInfo->pReal);
			pInfo->pReal=NULL;
			pInfo->FishGroupID=0;
			pInfo->RecvCount=0;
			break;
		}
	case TABLE_SUB_NET_GAP_TIME:
		{// ƴ�����ӳ�		// add by cxf
			if (NULL == pData)
			{
				break;
			}
			CMD_NET_GAP_TIME *pNetGapTime = (CMD_NET_GAP_TIME*)pData;
			//if (g_pShipMgr->ExistUserPlayer(pNetGapTime->llUserID))
			if (!SIX_PlayerMgr::GetInstance()->Get(pNetGapTime->llUserID))
			{// �û��Ѿ�����
				CShip *pShip = g_pShipMgr->getShip( pNetGapTime->llUserID);
				if (NULL == pShip)
				{
					return;
				}
				//_timeb timebuffer;
				//_ftime( &timebuffer );		// ��ȡ��ǰʱ��
				//long long llTIme = timebuffer.time*1000 + timebuffer.millitm;	// ת������
				//long long delay = CEasyDataTime::get_current_time_diff_millitm_from_1970() - pNetGapTime->llSendTime;
				long long delay = SIX_Utility::GetInstance()->GetTickCount() - pNetGapTime->llSendTime;
				pShip->setNetGapTime(delay);
			}
			break;
		}
	case TABLE_SUB_USER_OVERTIME:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			// ����60��δ�����ӵ���������ʱ��ʾ
			USER_OVERTIME_SURPLUS *packet = (USER_OVERTIME_SURPLUS*)pData;
			pSceneGame->ShowCountDown(packet->iSurplusTime);
			break;
		}
	case TABLE_SUB_USER_DATA_CHANGE:
		{
			CMD_SC_USER_DATA_CHANGE *userDataChange = (CMD_SC_USER_DATA_CHANGE*)pData;
			if (NULL==userDataChange)
			{
				return;
			}
			//PLAYER_LIST *pPlayerList = NULL;
			//g_pShipMgr->GetUserPlayer(userDataChange->lUserId, &pPlayerList);
			PLAYER_LIST *pPlayerList = SIX_PlayerMgr::GetInstance()->Get(userDataChange->lUserId);
			if (NULL != pPlayerList)
			{
				pPlayerList->lGoldLogin += userDataChange->iGold;
				pPlayerList->lPointLogin += userDataChange->iPoint;
			}
			CShip *pShip = g_pShipMgr->getShip( userDataChange->lUserId);
			if (NULL!=pShip)
			{
				pShip->setBulletCount(userDataChange->iPresentBullet);
			}
			SIXLog("�û����ݸı��ˣ�Ŀǰ�����ӿ�ʼ��ʱ����ȡ̨�Ѹı���");
			//ShowMsgBox("�û����ݸı��ˣ�Ŀǰ�����ӿ�ʼ��ʱ����ȡ̨�Ѹı���");
			break;
		}
	case TABLE_SUB_GAME_BEGIN:
		{// ���ӿ�ʼ
			SIXLog("���ӿ�ʼ������Ǳ������Ļ����ѽ����ϵĵȴ�������Ҳμӱ����Ŀ�ȥ��");
			//ShowMsgBox("���ӿ�ʼ������Ǳ������Ļ����ѽ����ϵĵȴ�������Ҳμӱ����Ŀ�ȥ��");
			break;
		}
	default:
		{
			SIXLog("HandlePacketTable.subCode[%d].Unknown!",subCode);
			//ShowMsgBox(CCString::createWithFormat("HandlePacketTable.subCode[%d].Unknown!",subCode)->getCString(),0);
			break;
		}
	}
}

void SIX_ClientRoom::HandlePacketMatch(int subCode,unsigned char *pData,int pDataLen)
{
	switch (subCode)
	{
	case MATCH_SUB_SC_ARRANGE_QUEUE_FINISH:	// �Ŷ����
		{
			break;
		}
	case MATCH_SUB_SC_CANCEL_ARRANGE_QUEUE_FINISH:	// ����ȡ���Ŷ����
		{
			break;
		}
	case MATCH_SUB_SC_GAME_END:	// ��������
		{
			CMD_MatchEnd * pMatchEnd = (CMD_MatchEnd *)pData;

			SIX_MatchEnd *pWndMatchEnd = SIX_MatchEnd::Create(0, 0, ccc4(0,0,0,0), 592, 401, false, true);
			pWndMatchEnd->InitMask(ccc4(0,0,0,128));
			pWndMatchEnd->backgroundWithFile("Common/MatchEnd/matchEndBG.png");
			pWndMatchEnd->SetMatchData( pMatchEnd );
			pWndMatchEnd->SetMyselfID( SIX_PlayerMgr::GetInstance()->getMyUserIdx() );
			pWndMatchEnd->Show( true );
			break;
		}
	case MATCH_SUB_SC_MATCH_COUNTDOWN:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			CMD_SC_MATCH_COUNTDOWN * pCountdown = (CMD_SC_MATCH_COUNTDOWN *)pData;
			pSceneGame->SetMatchCountdown(pCountdown->iMatchCountDown);
			SIXLog("��������ʱ[%d]!",pCountdown->iMatchCountDown);
			break;
		}
	default:
		{
			SIXLog("HandlePacketMatch.subCode[%d].Unknown!",subCode);
			//ShowMsgBox(CCString::createWithFormat("HandlePacketMatch.subCode[%d].Unknown!",subCode)->getCString(),0);
			break;
		}
	}
}

void SIX_ClientRoom::OnAddOneFish(Rsp_AddOneFish *pReal,float InitElapsed,TBuildTraceTime BuildTraceTime)
{
	if(InitElapsed>pReal->FishMoveSecs)
		return;
	//pathType==4ʱΪCurve��ľ�̬��Ա��������Ĺ켣
	CCPoint startCP=g_pShipMgr->SP2CP(CCP(pReal->startP));//�����
	//FishPathType=1,������
	CCPoint arg1CP=ccpSub(g_pShipMgr->SP2CP(CCP(pReal->arg1)),g_pShipMgr->SP2CP(ccp(0,0)));//�����򣬡�CCP(pReal->arg1),��g_pShipMgr->SP2CP(CCP(pReal->arg1))
	if(pReal->FishPathType==2||pReal->FishPathType==5||pReal->FishPathType==7)
		arg1CP=g_pShipMgr->SP2CP(CCP(pReal->arg1));//�����
	if(pReal->FishPathType==3||pReal->FishPathType==4||pReal->FishPathType==6)
		arg1CP=CCP(pReal->arg1);//�Ȳ�����㣬Ҳ�������򣬽����ڴ洢
	//FishPathType=5,�����
	CCPoint arg2CP=g_pShipMgr->SP2CP(CCP(pReal->arg2));
	if(pReal->FishPathType==3)
	{
		arg2CP=ccp(pReal->arg2.x,g_pShipMgr->SD2CD(pReal->arg2.y));//y����������
	}
	if(pReal->FishPathType==7)
	{
		arg2CP=CCP(pReal->arg2);//�Ȳ�����㣬Ҳ�������򣬽����ڴ洢
	}
	//FishPathType=5,�����
	CCPoint arg3CP=g_pShipMgr->SP2CP(CCP(pReal->arg3));
	if(pReal->FishPathType==3||pReal->FishPathType==6||pReal->FishPathType==7)
	{
		arg3CP=CCP(pReal->arg3);//�Ȳ�����㣬Ҳ�������򣬽����ڴ洢
	}
	g_FishMgr->addOneFish(pReal->FishID, pReal->FishKind, pReal->FishPathType, pReal->FishMoveSecs,pReal->FishMoveStatus, InitElapsed,BuildTraceTime,startCP, arg1CP, arg2CP, arg3CP);
}

//unsigned long long SIX_ClientRoom::GetTickCount64()
//{
//	////#ifdef WIN32
//	//#if 0
//	//	return ::GetTickCount64();
//	//#else
//	//	//��ʱ�ٶ��ͻ��˵Ŀ���ʱ����1970��
//	//	return CEasyDataTime::get_current_time_diff_millitm_from_1970();
//	//#endif
//	return SIX_Utility::GetInstance()->GetTickCount();
//}

bool SIX_ClientRoom::IsNeedMalloc(TFishGroupID FishGroupID)
{
	for(int i=0;i<20;i++)
	{
		if(m_FishListInfos[i].FishGroupID==FishGroupID)
		{
			return false;
		}
	}
	return true;
}

FishListInfo *SIX_ClientRoom::GetFishListInfo(TFishGroupID FishGroupID,bool isFirst)
{
	if(isFirst)
	{
		for(int i=0;i<20;i++)
		{
			if(m_FishListInfos[i].FishGroupID==0)
			{
				//m_FishListInfos[i].FishGroupID=FishGroupID;
				return &m_FishListInfos[i];
			}
		}
	}
	else
	{
		for(int i=0;i<20;i++)
		{
			if(m_FishListInfos[i].FishGroupID==FishGroupID)
			{
				return &m_FishListInfos[i];
			}
		}
	}
	return NULL;
}

int SIX_ClientRoom::BusyFishListCount()const
{
	int nCount=0;
	for(int i=0;i<20;i++)
	{
		if(m_FishListInfos[i].FishGroupID>0)
		{
			nCount++;
		}
	}
	return nCount;
}

void SIX_ClientRoom::login_room()
{
	if (this->getNeedExit())
		return;

	LOGIN_ROOM sendData;
	memset(&sendData, 0, sizeof(LOGIN_ROOM));
	
	if(this->GetLoginInfo().bAlreadyInRoom)	// �Ѿ��ڷ�������
	{
		if( 0==STRCMP(this->GetRoomInfo()->szIP, this->GetLoginInfo().szIP) && this->GetRoomInfo()->iPort==this->GetLoginInfo().iPort )	// �Ѿ��ڴ˷�������
		{
			SIXLog("ֱ��������ʾ�÷��䣬��Ϊ�Ѿ��ڴ˷������� ");
		}
		else	// ����ĳ�����������������˳�����
		{
			SIXLog("���Ѿ���ĳ�����������������˳����� \n");
		}
	}
	else	// �����¼����
	{
		sendData.lUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
		memcpy(sendData.szName, this->GetRoomInfo()->szName, sizeof(sendData.szName));
		memcpy(sendData.szPassword, this->GetRoomInfo()->szPassword, sizeof(sendData.szPassword));

		send_data(ROOM_MAIN, ROOM_SUB_LOGIN, (BYTE*)(&sendData), sizeof(sendData));
	}
}

void SIX_ClientRoom::leave_room()
{
	if (this->getNeedExit())
		return;
	send_data(ROOM_MAIN, ROOM_SUB_LEAVE_ROOM, 0, 0);
}

void SIX_ClientRoom::sit_down(int iTableNo, int iSeatNo)
{
	if (this->getNeedExit())
		return;

	SITDOWN sendData;
	sendData.iTableNo = iTableNo;
	sendData.iSeatNo = iSeatNo;

	send_data(TABLE_MAIN, TABLE_SUB_SITDOWN, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::raise_hand()
{
	if (this->getNeedExit())
		return;

	RAISE_HAND sendData;

	// �ܹ���ʼ��Ϸ�����º����Ϣ���ͻ���Ҫ�ȵ���ʼ����Ϻ󣬷�����Ϣ������˲ŷ���
	send_data(TABLE_MAIN, TABLE_SUB_RAISE_HAND, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::leave_seat()
{
	if (this->getNeedExit())
		return;

	send_data(TABLE_MAIN, TABLE_SUB_LEAVE_SEAT, 0, 0);
}

void SIX_ClientRoom::query_table_list()
{
	if (this->getNeedExit())
		return;

	send_data(ROOM_MAIN, ROOM_SUB_TABLE_LIST);
}

void SIX_ClientRoom::query_user_list()
{
	if (this->getNeedExit())
		return;

	send_data(ROOM_MAIN, ROOM_SUB_USER_LIST);
}

void SIX_ClientRoom::write_score(const CMD_WRITE_SCORE& score)
{
	if (this->getNeedExit())
		return;

	send_data(TABLE_MAIN, TABLE_SUB_WRITE_SCORE, (BYTE*)(&score), sizeof(score));
}

void SIX_ClientRoom::tick_one_leave_seat(int iTableNo, int iSeatNo)
{
	if (this->getNeedExit())
		return;

	// ��һ���������
	TICK_ONE_LEAVE_SEAT sendData;
	sendData.iTableNo = iTableNo;
	sendData.iSeatNo = iSeatNo;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_ONE_LEAVE_SEAT, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_table_leave_seat(int iTableNo)
{
	if (this->getNeedExit())
		return;

	// ��һ���������
	TICK_TABLE_LEAVE_SEAT sendData;
	sendData.iTableNo = iTableNo;
	sendData.bWriteScore = true;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_TABLE_LEAVE_SEAT, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_all_leave_seat()
{
	if (this->getNeedExit())
		return;

	TICK_ALL_LEAVE_SEAT sendData;
	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_ALL_LEAVE_SEAT, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_user_out_room(int iTableNo, int iSeatNo)
{
	if (this->getNeedExit())
		return;

	TICK_USER_OUT_ROOM sendData;
	sendData.iTickMode = TICK_USER_OUT_ROOM::TICK_BY_TABLE_SEAT;	// �����š�������
	sendData.bWriteScore = true;
	sendData.iTableNo = iTableNo;
	sendData.iSeatNo = iSeatNo;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_USER_OUT_ROOM, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_user_out_room(int iTableNo)
{
	if (this->getNeedExit())
		return;

	TICK_USER_OUT_ROOM sendData;
	sendData.iTickMode = TICK_USER_OUT_ROOM::TICK_BY_TABLE;	// 
	sendData.bWriteScore = true;
	sendData.iTableNo = iTableNo;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_USER_OUT_ROOM, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_user_out_room()
{
	if (this->getNeedExit())
		return;

	TICK_USER_OUT_ROOM sendData;
	sendData.iTickMode = TICK_USER_OUT_ROOM::TICK_BY_ALL;	// 
	sendData.bWriteScore = true;
	sendData.iTableNo = INVAL_TABLE_NO;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_USER_OUT_ROOM, (BYTE*)(&sendData), sizeof(sendData));
}

// add by cxf
// ����ʱ�䣨������ȡ�����ӳ���Ϣ��
void SIX_ClientRoom::SendNetGapTime()
{
	if (!g_pShipMgr)
	{
		return;
	}
	if (SIX_PlayerMgr::GetInstance()->getMyUserIdx() > 0)
	{// �û��Ѿ�����
		CShip *pShip = g_pShipMgr->getMySelfShip();
		if (NULL == pShip)
		{// 
			return;
		}
		//static unsigned int iSend = 0;

		//// SendNetGapTime()����ʱ�䲻ȷ�������Բ�������İ취
		//// Cool.Cat
		//if (iSend < 3600 && iSend >0)
		//{// 60 �뷢��һ��
		//	iSend ++;
		//	return;
		//}
		//iSend = 1;

		//_timeb timebuffer;
		//_ftime( &timebuffer );												// ��ȡϵͳʱ��
		//long long llTIme = timebuffer.time*1000 + timebuffer.millitm;		// ��ǰ��ʱ��

		//long long llTIme = CEasyDataTime::get_current_time_diff_millitm_from_1970();
		long long llTIme = SIX_Utility::GetInstance()->GetTickCount();

		// 10��һ��ping��
		//if (pShip->getLastPingTime()!=0 && pShip->getLastPingTime()+1000*10<llTIme)
		if (pShip->getLastPingTime()!=0 && pShip->getLastPingTime()+1000*10>llTIme)
			return;

		pShip->setLastPingTime(llTIme);

		CMD_NET_GAP_TIME pNetGapTime;
		pNetGapTime.llUserID =SIX_PlayerMgr::GetInstance()->getMyUserIdx();
		pNetGapTime.llSendTime = llTIme;
		this->send_data(TABLE_MAIN, TABLE_SUB_NET_GAP_TIME, &pNetGapTime, sizeof(pNetGapTime));
	}
}
void SIX_ClientRoom::ShowMsgBox(const char *fmt,...)
{
	SIX_MsgBox *pMsgBox = SIX_MsgBox::Create(0.0,0.0,ccc4(0,0,0,0),409.0,254.0,false,true);
	if (!pMsgBox)
		return;
	pMsgBox->InitMask(ccc4(0,0,0,128));
	pMsgBox->backgroundWithFile("tipbox.png");
	pMsgBox->buttonSubmitWithFileCell("Common/Button/return.png",3);
	pMsgBox->GetBtnSubmit()->setPosition(ccp(270,35));
	pMsgBox->setTextAttribute(20,80,369,140,"����",12);
	//pMsgBox->setRectDirty();

	char szBuf[1024] = {0};

    va_list ap;
    va_start(ap,fmt);
	vsnprintf(szBuf,1023,fmt,ap);
    va_end(ap);

	pMsgBox->setString(SIX_Utility::GetInstance()->G2U(szBuf).c_str());
	pMsgBox->Show();
}