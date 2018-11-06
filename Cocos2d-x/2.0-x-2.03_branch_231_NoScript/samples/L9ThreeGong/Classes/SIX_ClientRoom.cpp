#include "SIX_ClientRoom.h"
#include "SIX_PlayerMgr.h"
#include "SIX_SceneGame.h"
#include "SIX_SceneHall.h"
#include "SIX_RoomMgr.h"
#include <SIX_TMap.h>

extern SIX_SceneHall *pSceneHall;
extern SIX_SceneGame *pSceneGame;

SIX_ClientRoom *SIX_ClientRoom::m_gClientRoom = 0;

SIX_ClientRoom::SIX_ClientRoom()
{
	m_bAutoSitDown = true;
	m_bLogicConnect = false;
}

SIX_ClientRoom::~SIX_ClientRoom()
{
}

void SIX_ClientRoom::Connect(const char *addr,int port,bool bReconnected/*=true*/,int iReconnectDelay/*=MAX_RECONNECT_DELAY*/, bool bAutoSitDown/*=true*/)
{
	m_gClientRoom = SIX_ClientRoom::GetInstance();
	m_gClientRoom->m_bAutoSitDown = bAutoSitDown;
	m_gClientRoom->m_bLogicConnect = true;

//#define LOCAL_SERVER
#ifdef LOCAL_SERVER
	m_gClientRoom->init("192.168.1.167",port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass(),bReconnected,iReconnectDelay);
#else
	m_gClientRoom->init((char*)addr,port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass(),bReconnected,iReconnectDelay);
#endif
	m_gClientRoom->start();
}

void SIX_ClientRoom::Disconnect()
{
	// �������û���Ϣ
	SIX_PlayerMgr::GetInstance()->clearPlayers();
	// ����SIX_PlayerMgr
	SIX_PlayerMgr::GetInstance()->Destory();

	if (!m_gClientRoom)
		return;

	m_gClientRoom->m_bLogicConnect = false;
	m_gClientRoom->stop();
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

		// �����¼���ӳ�1s���ͣ����������MSG���л�һֱ������ֱ���ӳٰ�������ɣ��ż������ͺ������
		// Cool.Cat
		int retv = send_data(ROOM_MAIN, ROOM_SUB_LOGIN, (BYTE*)(&sendData), sizeof(sendData));
		SIXLog("���ڵ�¼����.retv[%d]...",retv);
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

	SIXLog("SIX_ClientRoom::sit_down iTableNo=%d, iSeatNo=%d",iTableNo,iSeatNo)
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
					break;
				}
				// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�
			case CLOSE_TYPE_FLASH_CLOSE:
				{
					SIXLog("��������");
					break;
				}
				// ����������رտͻ���
			case CLOSE_TYPE_SERVER_POWER_CLOSE:
				{
					SIXLog("����������ر�");
					break;
				}
			}
			m_bLogicConnect = false;
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
					this->setReconnect(true);
					this->login_room();
					break;
				}
				// OnConnect
			case RECONNECT_SUCCESSED:
				{
					SIXLog("���������ɹ�...");
					this->setReconnect(true);
					this->login_room();
					break;
				}
				// OnConnectFail
			case CONNECT_FAILED:
				{
					SIXLog("����ʧ��");
					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneHall") &&
						!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
						return;

					if (0 != pSceneHall  &&  0 != pSceneHall->GetPopWndRoomList()  &&  pSceneHall->GetPopWndRoomList()->IsShow())
						pSceneHall->GetPopWndRoomList()->SetReceiveDataComplete(true, true);

#ifdef WIN32
					CCMessageBox(/*����������ʧ�ܣ������ԣ�*/XorStr<0xF8,25,0xFF483E1A>("\x4F\x07\x34\x0A\x3A\x0A\x3F\x53\xBD\xD2\xC8\xA4\xB4\xD9\xA5\xAB\xCF\xE2\xDC\xD3\xC6\xD9\xAD\xAE"+0xFF483E1A).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*����������ʧ�ܣ������ԣ�*/XorStr<0xF8,25,0xFF483E1A>("\x4F\x07\x34\x0A\x3A\x0A\x3F\x53\xBD\xD2\xC8\xA4\xB4\xD9\xA5\xAB\xCF\xE2\xDC\xD3\xC6\xD9\xAD\xAE"+0xFF483E1A).s).c_str(),0);
#endif
					m_bLogicConnect = false;
					break;
				}
				// OnCommError
			case COMM_ERROR:
				{
					SIXLog("����ͨѶ�쳣");
					m_bLogicConnect = false;
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
}

void SIX_ClientRoom::auto_sit_down()
{
	int TableIdx=0;
	int SeatIdx=0;
	char sz[20]={0};
	for(int i=1;i<100;i++)
	{
		sprintf(sz,"T%d",i);
		if(STRCMP(this->GetRoomInfo()->szName,sz)==0)
		{
			TableIdx=i/10;
			SeatIdx=(i%10)%6;
			break;
		} 
	}
	this->sit_down(TableIdx,SeatIdx);
}

void SIX_ClientRoom::HandlePacketRoom(int iSubCode,unsigned char *pData,int iDataLen)
{
	switch(iSubCode)
	{
	case ROOM_SUB_LOGIN_FAIL:
		{
			LOGIN_ROOM_FAIL* pReal = (LOGIN_ROOM_FAIL*)pData;
			SIXLog("�û���¼ʧ�ܣ������룺%d  \n", pReal->iErrCode);
			return;
		}
	case ROOM_SUB_LOGIN_SUCC:	// �����ڹ㲥����¼����ɹ�
		{
			assert(sizeof(LOGIN_ROOM_SUCC)==iDataLen);
			if(sizeof(LOGIN_ROOM_SUCC)!=iDataLen)		// ����
				return;

			LOGIN_ROOM_SUCC* pReal = (LOGIN_ROOM_SUCC*)pData;
            SIXLog("��¼����ɹ���iPort=%d  \n", pReal->iPort);

			USER_INFO_SIM *pUserInfo = &pReal->userInfo;
			SIXLog("�Լ�[%lld]��szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]\n",
				pUserInfo->lUserId,
				pUserInfo->szName,
				pUserInfo->szNickname,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);
			//memcpy(&m_MeUserInfo,pUserInfo,sizeof(USER_INFO_SIM));
			SIX_PlayerMgr::GetInstance()->setMyUserIdentity(pUserInfo->lIdentity);
			SIX_PlayerMgr::GetInstance()->setMySeatIdx(pUserInfo->iSeatNo);
			SIX_PlayerMgr::GetInstance()->setMyTableIdx(pUserInfo->iTableNo);

			// ����
			if (pUserInfo->stUserState>US_ONLINE_LEAVE_SIT)
			{
				SIXLog("�����������뷿��...");
			}

			SIX_RoomMgr::GetInstance()->InitRoom();
			return;

		}
	case ROOM_SUB_RECOME:	// ��������
		{
			assert(sizeof(RECOME_AFTER_CUT)==iDataLen);
			if(sizeof(RECOME_AFTER_CUT)!=iDataLen)		// ����
				return;

			RECOME_AFTER_CUT* pReal = (RECOME_AFTER_CUT*)pData;
			SIXLog("%s �������룬����%d �� ����%d \n", pReal->szName, pReal->iTableNo, pReal->iSeatNo);

			return;
		}
	case ROOM_SUB_USER_INFO:	// ��¼�ߵ���Ϣ
		{
			assert(sizeof(USER_INFO)==iDataLen);
			if(sizeof(USER_INFO)!=iDataLen)		// ����
				return;

			USER_INFO* pReal = (USER_INFO*)pData;
			SIXLog("�û���Ϣ, ������%s��  �ǳƣ�%s, \n", pReal->szName, pReal->szNickname);

			return;
		}
	case ROOM_SUB_USER_LIST:	// �����û��б�
		{
			//USER_INFO* pUserInfo = (USER_INFO*)pData;
			//vecUserInfo.push_back(*pUserInfo);
			SIXLog("��������б�...\n");
			USER_INFO_SIM *pUserInfo = (USER_INFO_SIM*)pData;

			SIXLog("���[%lld]��szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]\n",
				pUserInfo->lUserId,
				pUserInfo->szName,
				pUserInfo->szNickname,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);

			// �����û��б�(�����˳�ʱ���Զ��ͷ�)
			// Cool.Cat
			USER_INFO_SIM *pPlayer = new USER_INFO_SIM();
			memcpy(pPlayer,pUserInfo,sizeof(*pUserInfo));
			SIX_PlayerMgr::GetInstance()->Add(pPlayer->lUserId,pPlayer);

			SIX_RoomMgr::GetInstance()->SetTablePlayerCount(pPlayer->iTableNo, 1);
			return;
		}
	case ROOM_SUB_USER_LOGIN_FINISH:	// ��½���
		{
			if (0 != pSceneHall  &&  0 != pSceneHall->GetPopWndRoomList()  &&  pSceneHall->GetPopWndRoomList()->IsShow())
			{
				pSceneHall->GetPopWndRoomList()->SetReceiveDataComplete();
				for (int i=0; i<SIX_RoomMgr::GetInstance()->GetTableCount(); ++i)
				{
					pSceneHall->GetPopWndRoomList()->SetTablePeopleNumber(i, SIX_RoomMgr::GetInstance()->GetTablePlayerCount(i));
				}
			}

			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneHall"))
			{
				if (-1!=SIX_PlayerMgr::GetInstance()->getMyTableIdx()  &&  -1!=SIX_PlayerMgr::GetInstance()->getMySeatIdx())
				{
					SIX_Proxy::GetInstance()->SetChangeScene(true);
					SIX_RoomMgr::GetInstance()->SetCurRoomID(-1);
				}
				else
				{
					if (m_bAutoSitDown)
					{
						this->sit_down(SIX_PlayerMgr::GetInstance()->getMyTableIdx(), SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					}
				}
			}
			return;
		}
	case ROOM_SUB_USER_LIST_OVER:	// �����û��б����
		{
			SIXLog("���ڵ��û��б������  \n");

			//// ��ӡ�û��б�
			//for(int i=0; i<vecUserInfo.size(); i++)
			//{
			//	USER_INFO* pUserInfo = &vecUserInfo[i];
			//	printf("  ������%s��  �ǳƣ�%s, \n", pUserInfo->szName, pUserInfo->szNickname);
			//}

			//vecUserInfo.clear();  // �д˾����´νӵ��������û��б�ʱ�Ͳ��������
			return;
		}
	case ROOM_SUB_TABLE_LIST:
		{
			SIXLog("���������б�...\n");
			SERVER_ROOM_INFO_SIM *packet = (SERVER_ROOM_INFO_SIM*)pData;
			SIXLog("��������[%ld]���������ӵ�����[%d].ÿ������[%d].��Ϸ����[%d].��Ƶ[%d]\n",packet->iRoomPeopleCount,packet->iTables,packet->iSeatNum,packet->iRoomType,packet->iBasePoint);

			break;
		}
	case ROOM_SUB_LEAVE_ROOM:	// �뷿�ɹ�
		{
			LEAVE_ROOM_RESULT* pReal = (LEAVE_ROOM_RESULT*)pData;

			// ���Լ�ͬ�������
			if (pReal->iTableNo==SIX_PlayerMgr::GetInstance()->getMyTableIdx() && pReal->lUserId!=SIX_PlayerMgr::GetInstance()->getMyUserIdx())
			{
				if (pReal->iSeatNo>=0 && pReal->iSeatNo<GAME_PLAYER_COUNT)
				{
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						// ˢ����Ϸ����UI
						int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
						// �û���Ϣ������
						pSceneGame->showPlayerZoneShow(ViewID,false);
						// �ƶ�����
						pSceneGame->showCardSuit(ViewID,false);
						// ����ͳ�����
						pSceneGame->showStatsPanel(ViewID,0,false,false,false);
						// ���س�����
						pSceneGame->SetChipPanelNumber(ViewID,0,false);
						// ����ׯ�ұ�־
						pSceneGame->showPlayerRubBanker(ViewID,false);
					}
				}
			}

			// �����û�����
			for (int j=0;j<GAME_PLAYER_COUNT;j++)
			{
				SinglePlayer *pPlayer = &SIX_PlayerMgr::GetInstance()->m_Players[j];
				if (pPlayer && pPlayer->UserIdx==pReal->lUserId)
				{
					memset(pPlayer,0,sizeof(*pPlayer));
				}
			}

			SIX_PlayerMgr::GetInstance()->Del(pReal->lUserId);

			//if(0 == pReal->iErrCode)
			//{
			//	printf("%s �뷿�ɹ� \n", pReal->userInfo.szName);
			//}
			//else
			//{
			//	printf("%s ���ڷ����ڣ� \n", pReal->userInfo.szName);
			//	close(CLOSE_TYPE_CLIENT_CLOSE);	// �ͻ��������رգ������رշ����
			//}
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
			SIXLog("δ�������Ϣ iSubCode = %d", iSubCode);
			break;
		}
	}
}

void SIX_ClientRoom::HandlePacketTable(int iSubCode,unsigned char *pData,int iDataLen)
{
	switch(iSubCode)
	{
	//case TABLE_SUB_SITDOWN:
	//	{
	//		SITDOWN* pReal = (SITDOWN*)pData;
	//		if(0==pReal->iRes)
	//		{
	//			SIXLog("�û�ID%I64d ���£�����%d , ����%d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo);
	//		}
	//		else
	//		{
	//			SIXLog("�û�ID%I64d ����ʧ�ܣ�����%d , ����%d , ������ %d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo, pReal->iRes);
	//		}

	//		break;
	//	}
	case TABLE_SUB_SITDOWN:
		{
			SITDOWN *packet=(SITDOWN*)pData;
			switch (packet->iRes)
			{
			case RET_TABLE_OPERATE_SUCCEED:
				{
					bool sameTable = false;
					// �Լ�����
					if (packet->lUserId==SIX_PlayerMgr::GetInstance()->getMyUserIdx())
					{
						sameTable = true;
						SIX_PlayerMgr::GetInstance()->setMySeatIdx(packet->iSeatNo);
						SIX_PlayerMgr::GetInstance()->setMyTableIdx(packet->iTableNo);
					}
					// ���Լ�ͬ�����������
					else if (packet->iTableNo == SIX_PlayerMgr::GetInstance()->getMyTableIdx())
					{
						sameTable = true;
					}

					// �����û��ڷ����û��б��е������κ�
					USER_INFO_SIM *pPlayer = SIX_PlayerMgr::GetInstance()->Get(packet->lUserId);
					if (pPlayer)
					{
						pPlayer->iTableNo = packet->iTableNo;
						pPlayer->iSeatNo = packet->iSeatNo;
						pPlayer->stUserState = US_ONLINE_SITDOWN;
						SIX_RoomMgr::GetInstance()->SetTablePlayerCount(pPlayer->iTableNo, 1);
						if (0!=pSceneHall  &&  0!=pSceneHall->GetPopWndRoomList()  &&  pSceneHall->GetPopWndRoomList()->IsShow())
							pSceneHall->GetPopWndRoomList()->SetTablePeopleNumber(pPlayer->iTableNo, SIX_RoomMgr::GetInstance()->GetTablePlayerCount(pPlayer->iTableNo));
					}

					// �Լ� �� ���Լ�ͬ�����û�����ʱ����
					if (sameTable)
					{
						// ������ǰ�����û��б������Ѿ����Լ�ǰ�����µ�ͬ���û�
						SIX_TMap<long long,USER_INFO_SIM*>::KV_MAP mmap = SIX_PlayerMgr::GetInstance()->GetMap();
						SIX_TMap<long long,USER_INFO_SIM*>::KV_ITER iter = mmap.begin();
						for (;iter!=mmap.end();iter++)
						{
							USER_INFO_SIM *pPlayer = iter->second;
							if (!pPlayer)
								continue;

							// �������Լ�ͬ�����û��������Լ�
							if (SIX_PlayerMgr::GetInstance()->getMyTableIdx()==pPlayer->iTableNo)
							{
								//if (pPlayer->iSeatNo<0 || pPlayer->iSeatNo>=MAX_PLAYER_COUNT)
								//{
								//	CCString *errMsg = CCString::createWithFormat("����.����[%d].�κ�[%d].�û�ID[%lld].�ǳ�[%s].���û��κ������",
								//		pPlayer->iTableNo,pPlayer->iSeatNo,pPlayer->lUserId,pPlayer->szNickname);
								//	SIXLog("%s",SIX_Utility::GetInstance()->G2U(errMsg->getCString()).c_str());
								//	CCMessageBox(SIX_Utility::GetInstance()->G2U(errMsg->getCString()).c_str(),0);
								//	continue;
								//}
								if (pPlayer->iSeatNo<0 || pPlayer->iSeatNo>=GAME_PLAYER_COUNT)
									continue;

								SinglePlayer *pSinglePlayer = &SIX_PlayerMgr::GetInstance()->m_Players[pPlayer->iSeatNo];
								// ����
								pSinglePlayer->iTableId = pPlayer->iTableNo;
								// ����
								pSinglePlayer->SeatId = pPlayer->iSeatNo;
								// �û�ID
								pSinglePlayer->UserIdx = pPlayer->lUserId;
								// ���
								pSinglePlayer->lGoldLogin = pPlayer->lGoldLogin;
								// ����
								pSinglePlayer->lPointLogin = pPlayer->lPointLogin;
								// ͷ��
								pSinglePlayer->lSysLogoID = pPlayer->lSysLogoID;
								// �ʺ�
								memcpy(pSinglePlayer->szName,pPlayer->szNickname,sizeof(pPlayer->szName));
								// �ǳ�
								memcpy(pSinglePlayer->szNickname,pPlayer->szNickname,sizeof(pPlayer->szNickname));
								// ����
								pSinglePlayer->bRaiseHand = (pPlayer->stUserState==US_ONLINE_SITDOWN_RAISE)?true:false;

								// ��������Լ�
								if (SIX_PlayerMgr::GetInstance()->getMyUserIdx()!=packet->lUserId)
								{
									if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
									{
										// ˢ����Ϸ����UI
										int ViewID=SIX_PlayerMgr::getViewID(pPlayer->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
										// �û���Ϣ����ʾ
										pSceneGame->showPlayerZoneShow(ViewID,true);
										// ������ʾ�û��ǳ�
										pSceneGame->setPlayerZoneNickName(ViewID,pPlayer->szNickname);
										// ������ʾ�û�ͷ��
										pSceneGame->setPlayerZoneFaceLogo(ViewID,pPlayer->lSysLogoID);
										// ������ʾ�û�����
										pSceneGame->setPlayerZoneChip(ViewID,pPlayer->lGoldLogin);
										// �����û���Ϣ��͸����
										pSceneGame->setPlayerZoneOpacity(ViewID,pSinglePlayer->bRaiseHand?255:128);
										// �ƶ�����
										pSceneGame->showCardSuit(ViewID,false);
									}
								}
							}
						}
					}

					// for test
					// Cool.Cat
					for (int i=0;i<GAME_PLAYER_COUNT;i++)
					{
						SinglePlayer *pSinglePlayer = &SIX_PlayerMgr::GetInstance()->m_Players[i];
						if (!pSinglePlayer)
							continue;
						SIXLog("pSinglePlayer[%d].iTableId[%d].SeatId[%d].UserIdx[%lld].szName[%s].szNickname[%s]",
							i,
							pSinglePlayer->iTableId,
							pSinglePlayer->SeatId,
							pSinglePlayer->UserIdx,
							pSinglePlayer->szName,
							pSinglePlayer->szNickname);
					}
					SIXLog("---------------------------------");

					// ������Լ����£��л�����Ϸ����
					if (packet->lUserId==SIX_PlayerMgr::GetInstance()->getMyUserIdx())
					{
						SIXLog("SetChangeScene...");
						SIX_Proxy::GetInstance()->SetChangeScene(true);
						SIX_RoomMgr::GetInstance()->SetCurRoomID(-1);
						// ��¼�л�����ǰ�յ����°���ʱ��
						// Cool.Cat
						SIX_PlayerMgr::GetInstance()->setLastRecvSitDownTime(SIX_Utility::GetInstance()->GetTickCount());
					}

					break;
				}
			case RET_TABLE_CHAIR_ERROR:
				{
					SIXLog("����ʧ�ܣ�ʧ��ԭ�򣺸���λ�����ڣ�");
#ifdef WIN32
					CCMessageBox(/*����ʧ�ܣ�ʧ��ԭ�򣺸���λ�����ڣ�*/XorStr<0xA7,35,0x175E755F>("\x70\x50\x66\x68\x61\x0B\x1D\x72\x0C\x11\x7B\x15\x03\x68\x61\x1B\x65\x4A\x1A\x00\x03\x7F\x6A\x47\x71\x7B\x73\x79\x77\x22\x11\x1C\x64\x69"+0x175E755F).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*����ʧ�ܣ�ʧ��ԭ�򣺸���λ�����ڣ�*/XorStr<0xA7,35,0x175E755F>("\x70\x50\x66\x68\x61\x0B\x1D\x72\x0C\x11\x7B\x15\x03\x68\x61\x1B\x65\x4A\x1A\x00\x03\x7F\x6A\x47\x71\x7B\x73\x79\x77\x22\x11\x1C\x64\x69"+0x175E755F).s).c_str(),0);
#endif
					break;
				}
			case RET_TABLE_CHAIR_OCCUPY:
				{
					SIXLog("����ʧ�ܣ�ʧ��ԭ�򣺸���λ�Ѿ���������");
#ifdef WIN32
					CCMessageBox(/*����ʧ�ܣ�ʧ��ԭ�򣺸���λ�Ѿ���������*/XorStr<0x03,39,0xB1C6D99D>("\xD4\xFC\xCA\xC4\xCD\xAF\xB9\xD6\xA8\xAD\xC7\xA9\xBF\xCC\xC5\xBF\xC1\xE6\xB6\xAC\xAF\xDB\xCE\xE3\xD5\xA7\xCF\xCF\xA1\x8D\xF2\xF2\xEB\xEF\xE5\x94\x84\x89"+0xB1C6D99D).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*����ʧ�ܣ�ʧ��ԭ�򣺸���λ�Ѿ���������*/XorStr<0x03,39,0xB1C6D99D>("\xD4\xFC\xCA\xC4\xCD\xAF\xB9\xD6\xA8\xAD\xC7\xA9\xBF\xCC\xC5\xBF\xC1\xE6\xB6\xAC\xAF\xDB\xCE\xE3\xD5\xA7\xCF\xCF\xA1\x8D\xF2\xF2\xEB\xEF\xE5\x94\x84\x89"+0xB1C6D99D).s).c_str(),0);
#endif
					break;
				}
			case RET_TABLE_TABLE_START:
				{
					SIXLog("����ʧ�ܣ�ʧ��ԭ�������Ѿ���ʼ����������������ˣ�");
#ifdef WIN32
					CCMessageBox(/*����ʧ�ܣ�ʧ��ԭ�������Ѿ���ʼ����������������ˣ�*/XorStr<0x8B,53,0x85F86ECB>("\x5C\x74\x42\x4C\x45\x37\x21\x4E\x30\x35\x5F\x31\x27\x44\x4D\x37\x49\x6E\x3E\x24\x48\x60\x76\x71\x71\x75\x1B\x0B\x18\x02\x63\x16\x08\x00\x1F\x15\x7B\x7A\x61\x5F\x0E\x4C\x7D\x5D\x60\x78\x6E\x69\x7A\x77\x1E\x1F"+0x85F86ECB).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*����ʧ�ܣ�ʧ��ԭ�������Ѿ���ʼ����������������ˣ�*/XorStr<0x8B,53,0x85F86ECB>("\x5C\x74\x42\x4C\x45\x37\x21\x4E\x30\x35\x5F\x31\x27\x44\x4D\x37\x49\x6E\x3E\x24\x48\x60\x76\x71\x71\x75\x1B\x0B\x18\x02\x63\x16\x08\x00\x1F\x15\x7B\x7A\x61\x5F\x0E\x4C\x7D\x5D\x60\x78\x6E\x69\x7A\x77\x1E\x1F"+0x85F86ECB).s).c_str(),0);
#endif
					break;
				}
			case RET_TABLE_ENTER_GOLD_LACK:
				{
					SIXLog("����ʧ�ܣ�ʧ��ԭ�򣺽�Ҳ�����������ӣ�");
#ifdef WIN32
					CCMessageBox(/*����ʧ�ܣ�ʧ��ԭ�򣺽�Ҳ�����������ӣ�*/XorStr<0x1F,41,0xDFC7080A>("\xC8\xD8\xEE\xE0\xE9\x83\x95\xFA\x84\x89\xE3\x8D\x9B\xF0\xF9\x83\xFD\xC2\x92\x88\x8E\xC4\x84\xE4\x85\x83\x80\x81\x86\xC4\xF5\xD5\x87\x83\x96\x82\x94\x97\xE6\xE7"+0xDFC7080A).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*����ʧ�ܣ�ʧ��ԭ�򣺽�Ҳ�����������ӣ�*/XorStr<0x1F,41,0xDFC7080A>("\xC8\xD8\xEE\xE0\xE9\x83\x95\xFA\x84\x89\xE3\x8D\x9B\xF0\xF9\x83\xFD\xC2\x92\x88\x8E\xC4\x84\xE4\x85\x83\x80\x81\x86\xC4\xF5\xD5\x87\x83\x96\x82\x94\x97\xE6\xE7"+0xDFC7080A).s).c_str(),0);
#endif
					break;
				}
			case RET_TABLE_NOT_FOUND_FIT:
				{
					SIXLog("����ʧ�ܣ�ʧ��ԭ��δ�ҵ����ʵ����Ӻ����ӣ�������������������");
#ifdef WIN32
					CCMessageBox(/*����ʧ�ܣ�ʧ��ԭ��δ�ҵ����ʵ����Ӻ����ӣ�������������������*/XorStr<0x87,63,0x1BB84B06>("\x50\x70\x46\x48\x41\x2B\x3D\x52\x2C\x31\x5B\x35\x23\x48\x41\x3B\x45\x6A\x3A\x20\x55\x28\x48\x4C\x2A\x1D\x1B\x6D\x69\x6E\x10\x62\x75\x66\x7E\x79\x11\x61\x7A\x6E\x78\x63\x12\x1E\x0C\x7D\x71\x6A\x60\x78\x6E\x69\x73\x77\x77\x43\x6D\x11\x03\x38\x60\x65"+0x1BB84B06).s, 0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*����ʧ�ܣ�ʧ��ԭ��δ�ҵ����ʵ����Ӻ����ӣ�������������������*/XorStr<0x87,63,0x1BB84B06>("\x50\x70\x46\x48\x41\x2B\x3D\x52\x2C\x31\x5B\x35\x23\x48\x41\x3B\x45\x6A\x3A\x20\x55\x28\x48\x4C\x2A\x1D\x1B\x6D\x69\x6E\x10\x62\x75\x66\x7E\x79\x11\x61\x7A\x6E\x78\x63\x12\x1E\x0C\x7D\x71\x6A\x60\x78\x6E\x69\x73\x77\x77\x43\x6D\x11\x03\x38\x60\x65"+0x1BB84B06).s).c_str(), 0);
#endif
				}
			}
			break;
		}

	case TABLE_SUB_LEAVE_SEAT:
		{
			LEAVE_SEAT* pReal = (LEAVE_SEAT*)pData;

			// ������Լ�����
			if (pReal->lUserId==SIX_PlayerMgr::GetInstance()->getMyUserIdx())
			{
				if (pReal->iRes==0)
				{
					SIXLog("��%d��, ��%d�� �������ɹ��� \n", pReal->iTableNo, pReal->iSeatNo);
				}
				else
				{
					SIXLog("��%d��, ��%d�� ������ʧ�ܣ� \n", pReal->iTableNo, pReal->iSeatNo);
				}

				SIX_PlayerMgr::GetInstance()->setMySeatIdx(pReal->iSeatNo);
				SIX_PlayerMgr::GetInstance()->setMyTableIdx(pReal->iTableNo);
				SIX_Proxy::GetInstance()->SetChangeScene(true);
			}
			// ��������Ǹ��Լ�ͬ���������û�����
			else if (pReal->iTableNo==SIX_PlayerMgr::GetInstance()->getMyTableIdx())
			{
				// ���������û��ڷ����б��е�����
				USER_INFO_SIM *pPlayer = SIX_PlayerMgr::GetInstance()->Get(pReal->lUserId);
				if (!pPlayer)
					return;

				//if (pReal->iSeatNo<0 || pReal->iSeatNo>=MAX_PLAYER_COUNT)
				//{
				//	CCString *errMsg = CCString::createWithFormat("����.����[%d].�κ�[%d].�û�ID[%lld].�ǳ�[%s].���û��κ������",
				//		pPlayer->iTableNo,pPlayer->iSeatNo,pPlayer->lUserId,pPlayer->szNickname);
				//	SIXLog("%s",SIX_Utility::GetInstance()->G2U(errMsg->getCString()).c_str());
				//	CCMessageBox(SIX_Utility::GetInstance()->G2U(errMsg->getCString()).c_str(),0);
				//	return;
				//}
				if (pReal->iSeatNo<0 || pReal->iSeatNo>=GAME_PLAYER_COUNT)
					break;

				pPlayer->stUserState = US_ONLINE_LEAVE_SIT;

				if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				{
					// ˢ����Ϸ����UI
					int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					// �û���Ϣ������
					pSceneGame->showPlayerZoneShow(ViewID,false);
					// �ƶ�����
					pSceneGame->showCardSuit(ViewID,false);
					// ����ͳ�����
					pSceneGame->showStatsPanel(ViewID,0,false,false,false);
					// ���س�����
					pSceneGame->SetChipPanelNumber(ViewID,0,false);
					// ����ׯ�ұ�־
					pSceneGame->showPlayerRubBanker(ViewID,false);
				}
			}

			SIX_RoomMgr::GetInstance()->SetTablePlayerCount(pReal->iTableNo, -1);
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneHall"))
			{
				if (0!=pSceneHall  &&  0!=pSceneHall->GetPopWndRoomList()  &&  pSceneHall->GetPopWndRoomList()->IsShow())
					pSceneHall->GetPopWndRoomList()->SetTablePeopleNumber(pReal->iTableNo, SIX_RoomMgr::GetInstance()->GetTablePlayerCount(pReal->iTableNo));
			}
			break;
		}
	case TABLE_SUB_TABLE_SPEAK:
		{
			CMD_ChatContent *pChat = (CMD_ChatContent *)pData;
			if (0==pChat  ||  sizeof(CMD_ChatContent) != iDataLen)
			{
				return;
			}

			SIXLog("%s��%s", pChat->szSpeakNickName, pChat->szCentent);
			if (0 != pSceneGame  &&  SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				pSceneGame->getWndMessage()->ReceiInformation(pChat);
			break;
		}
	case TABLE_SUB_WRITE_SCORE_RET:
		{
			WRITE_SCORE_RESULT* pReal = (WRITE_SCORE_RESULT*)pData;
			//if(0==pReal->iRes)
			//	printf("д�ַ���, �û�ID=%I64d ��ǰ�ķ�ֵ=%I64d ����=%I64d \n",pReal->lUserId, pReal->lGold, pReal->lPoint);
			//else
			//	printf("д�ַ��أ�������=%d \n", pReal->iRes);

			break;
		}
	case TABLE_SUB_RAISE_HAND://�û�����
		{
			RAISE_HAND* pReal = (RAISE_HAND*)pData;
			if(0==pReal->iRes)
			{
				SIXLog("�û�ID%lld ����\n", pReal->lUserId);

				// ���������û��ڷ����б��е�����
				USER_INFO_SIM *pPlayer = SIX_PlayerMgr::GetInstance()->Get(pReal->lUserId);
				if (!pPlayer)
					return;

				pPlayer->stUserState = US_ONLINE_SITDOWN_RAISE;

				SinglePlayer *pSinglePlayer = &SIX_PlayerMgr::GetInstance()->m_Players[pReal->iSeatNo];
				if (pSinglePlayer && pSinglePlayer->UserIdx)
					pSinglePlayer->bRaiseHand = true;

				if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				{
					// ˢ�¸��û���Ϣ��͸����
					int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					// �����û���Ϣ��͸����
					pSceneGame->setPlayerZoneOpacity(ViewID,255);
				}
			}
			else
			{
				CCString *pErr = CCString::createWithFormat("�û�ID%I64d ����ʧ��, ������ %d", pReal->lUserId, pReal->iRes);
				SIXLog("%s",pErr->getCString());
#ifdef WIN32
				CCMessageBox(pErr->getCString(),0);
#else
				CCMessageBox(SIX_Utility::GetInstance()->G2U(pErr->getCString()).c_str(),0);
#endif
			}

			break;
		}
	case RSP_CALL_BANKER_NOTIFY:		//������ׯ
		{
			Rsp_CallBankerNotify* pReal = (Rsp_CallBankerNotify*)pData;
			SIXLog("������ׯ��");
			//m_byGameState=E_GAME_CALL_BANKER;
			// ��ׯ��Ч
			// add by Ivan_han 20131102
			SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(1000,false);

			// ��ʾ��ׯ��ť
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				pSceneGame->showCountDown(true,SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_RUBBANKER"));
				pSceneGame->showBtnRubBanker(true);
				// ��ׯ��ʼ���ֹ�л�����������
				// Cool.Cat
				SIX_PlayerMgr::GetInstance()->setAllowChangeToHall(false);
			}
			break;
		}
	case RSP_USER_CALL_BANKER:		//�û���ׯ
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Req_UserCallBanker* pReal = (Req_UserCallBanker*)pData;
				SIXLog("�û���ׯ���� �û�ID=%lld ��λ��=%d �Ƿ���ׯ=%d TError=%d \n",pReal->llUserID,pReal->iSeatNo,pReal->bCall,pReal->iRes);
				int ViewID = SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
				// ��ʾ��ׯ��ʾ
				pSceneGame->showTipRubBanker(ViewID,pReal->bCall,true);

				// ������Լ���ׯ���أ����ñ�־λ
				if (pReal->iSeatNo==SIX_PlayerMgr::GetInstance()->getMySeatIdx())
				{
					SinglePlayer *pPlayer = &SIX_PlayerMgr::GetInstance()->m_Players[SIX_PlayerMgr::GetInstance()->getMySeatIdx()];
					if (pPlayer && !pPlayer->byCallBanker)
						pPlayer->byCallBanker = 1;
				}
			}
			break;
		}
	case RSP_CALL_BANKER_RESULT://��ׯ���
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Rsp_BankerC3Info* pReal = (Rsp_BankerC3Info*)pData;
				SIXLog("������ע�� wBankerUser=%d C3=%lld C2=%lld C1=%lld �Ƿ񾭹���ׯ����=%d ����ׯ����=%d \n",pReal->wBankerUser,pReal->C3,pReal->C2,pReal->C1,pReal->bNeedCallBanker,pReal->CallBankerNum);
				//m_byGameState=E_GAME_CALL_SCORE;

				// ������ׯ��ť��
				pSceneGame->showBtnRubBanker(false);
				pSceneGame->showCountDown(false);

				// ��ע��ʼ���ֹ�л�����������
				// Cool.Cat
				SIX_PlayerMgr::GetInstance()->setAllowChangeToHall(false);

				SIX_PlayerMgr::GetInstance()->m_wBankerChairID = pReal->wBankerUser;

				// ��ׯ�����Ҫ�������Ӷ���
				if (pReal->bNeedCallBanker && pReal->CallBankerNum!=1)
				{
					// �Ƴ�ׯ�ұ�־
					for (int i=0;i<GAME_PLAYER_COUNT;i++)
					{
						int ViewID=SIX_PlayerMgr::getViewID(i,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
						pSceneGame->showPlayerRubBanker(ViewID,false);
					}

					// ������Ӳ���
					unsigned num[2] = {0,0};
					num[0] = pReal->dice[0];
					num[1] = pReal->dice[1];
					//int ViewID=SIX_PlayerMgr::getViewID(pReal->wBankerUser,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					// Я��������
					long long *pData = new long long[5];
					pData[0] = (long long)pSceneGame;
					pData[1] = (long long)pReal->wBankerUser;
					pData[2] = pReal->C1;
					pData[3] = pReal->C2;
					pData[4] = pReal->C3;
					SIXLog("ViewID[%d/%lld].C1/C2/C3[%lld/%lld/%lld]",pReal->wBankerUser,pData[1],pData[2],pData[3],pData[4]);
					pSceneGame->showAnimateThrowDice(num,sizeof(num)/sizeof(unsigned int),pData);
				}
				// 1������ׯ
				// Cool.Cat
				else if (pReal->CallBankerNum==1)
				{
					// �Ƴ�ׯ�ұ�־
					for (int i=0;i<GAME_PLAYER_COUNT;i++)
					{
						int ViewID=SIX_PlayerMgr::getViewID(i,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
						pSceneGame->showPlayerRubBanker(ViewID,false);
					}

					// �ƶ�ׯ�����ӵ�ϴ����
					pSceneGame->MoveBankerFlagToShuffleArea(pReal->wBankerUser);
					// �ƶ�ׯ�����ӵ�ׯ������
					pSceneGame->MoveBankerFlagToBankerArea(pReal->C1,pReal->C2,pReal->C3);
				}
				else
				{
					// ������ׯ��ʾ
					for (int i=0;i<GAME_PLAYER_COUNT;i++)
					{
						int ViewID = SIX_PlayerMgr::getViewID(i,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
						pSceneGame->showTipRubBanker(ViewID,false,false);
					}

					// ����ׯ�ұ�־
					int ViewID=SIX_PlayerMgr::getViewID(pReal->wBankerUser,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					pSceneGame->showPlayerRubBanker(ViewID,true);

					// �м���ʾ��ע��ť
					if(pReal->wBankerUser!=SIX_PlayerMgr::GetInstance()->getMySeatIdx())
					{
						pSceneGame->showCountDown(true,SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_CHIPIN"));
						pSceneGame->showBtnChipin(true);
						pSceneGame->SetBtnChipPoint(pReal->C1,pReal->C2,pReal->C3);
					}
					else
					{
						// �ȴ��м���ע��ʾ
						pSceneGame->showSprChip(true);
						//ɢ��ׯ����ʾɱ����С��ť
						if(SIX_PlayerMgr::GetInstance()->IsSanXianIdentity())
						{
							pSceneGame->showBtnKill(true);
						}
					}
				}
			}
			break;
		}
	case RSP_DICE_NOTIFY:
		{
			//if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			//{
			//	Rsp_BankerC3Info* pReal = (Rsp_BankerC3Info*)pData;
			//}
			break;
		}
	case RSP_USER_CHIPIN:		//�û���ע
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Req_UserChipin* pReal = (Req_UserChipin*)pData;
				int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
				SIXLog("�û���ע���� �û�ID=%I64d ��λ��=%d ��ע��=%I64d TError=%d ViewID=%d\n",pReal->llUserID,pReal->iSeatNo,pReal->lScore,pReal->iRes,ViewID);

				// ��ע����
				// Cool.Cat
				pSceneGame->showAnimateChip(ViewID,pReal->lScore);

				// ����Լ�����ע��ң�������ע��ť
				if(ViewID==3)
					pSceneGame->showBtnChipin(false);
			}
			break;
		}
		// �����û���ע���
	case RSP_CALL_SCORE_END_NOTIFY:
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				SIXLog("ϴ�ƶ���1");
				// ���صȴ��м���ע
				pSceneGame->showSprChip(false);
			}
			break;
		}
	case RSP_SEND_CARD_LIST://����
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				pSceneGame->showBtnKill(false);
				pSceneGame->showCountDown(false);
				Rsp_SendCard_List *pCardList = (Rsp_SendCard_List*)pData;
				for(int i=0;i<pCardList->nCount;i++) 
				{
					// ��ϴ�Ʒ��ƶ���
					// Cool.Cat
					Rsp_SendCard* pReal = (Rsp_SendCard*)(&pCardList->m_SendCards[i]);
					int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					SIXLog("�˿�����=(%d,%d,%d) �û�ID=%I64d ��λ��=%d ViewID=%d \n",(int)pReal->cbUserCardData[0],(int)pReal->cbUserCardData[1],(int)pReal->cbUserCardData[2],pReal->llUserID,pReal->iSeatNo,ViewID);

					for (int j=0;j<GAME_PLAYER_COUNT;j++)
					{
						SinglePlayer *pPlayer = &SIX_PlayerMgr::GetInstance()->m_Players[j];
						if (!pPlayer || (pPlayer && pPlayer->UserIdx!=pReal->llUserID))
							continue;

						// save it~
						memcpy(pPlayer->UserCardData,pReal->cbUserCardData,sizeof(pPlayer->UserCardData));
					}
				}
				// ϴ�ƶ���
				SIXLog("ϴ�ƶ���2");
				pSceneGame->showAnimateShuffleAndDealCard();
			}
			break;
		}
	case RSP_SEND_FINISH:		//�û��������
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Rsp_SendFinish* pReal = (Rsp_SendFinish*)pData;
				SIXLog("�û�������Ϸ��� �û�ID=%I64d ��λ��=%d TError=%d \n",pReal->llUserID,pReal->iSeatNo,pReal->iRes);
			}
			break;
		}
	case RSP_GAME_END_LIST://һ����Ϸ����
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Rsp_GameEnd_List* pReal = (Rsp_GameEnd_List*)pData;
				SIX_TVector<CUSTOM_INFO*> customVec;
				for(int i=0;i<pReal->nCount;i++)
				{
					Rsp_GameEnd *pGameEnd=&pReal->m_GameEnds[i];//&(*pReal)[i];
					int ViewID=SIX_PlayerMgr::getViewID(pGameEnd->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					//SIXLog("һ����Ϸ���� �û�ID=%I64d ��λ��=%d ��Ϸ˰��=%lld ��������=%lld ����=%d ����=%d \n",pGameEnd->llUserID,pGameEnd->iSeatNo,pGameEnd->lGameTax,pGameEnd->lGameScore,(int)pGameEnd->CardType,(int)pGameEnd->CardPoint);
					//for (int j=0;j<3;j++)
					//	pSceneGame->SetCardFrontShow(ViewID,j,true);
					//// ��ʾÿ���û�ʤ��ͳ�����
					//bool isWin = pGameEnd->lGameScore>0?true:false;
					//pSceneGame->showStatsPanel(ViewID,pGameEnd->CardPoint,isWin,pGameEnd->CardType==1,pGameEnd->CardType==2,pGameEnd->CardType==4);

					//// �Լ��Ĵ���
					//if (ViewID==3)
					//{
					//	// ʤ������
					//	// Cool.Cat
					//	// ʤ
					//	pSceneGame->showStatsMySelfWinOrLose(pGameEnd->lGameScore>0?true:false);
					//	TChip Chip=SIX_PlayerMgr::GetInstance()->getMyChip()+pGameEnd->lGameScore;
					//	SIX_PlayerMgr::GetInstance()->setMyChip(Chip);
					//}
					// ׯ�Ҳ���¼
					int BankerViewID = SIX_PlayerMgr::getViewID(SIX_PlayerMgr::GetInstance()->m_wBankerChairID,SIX_PlayerMgr::GetInstance()->getMySeatIdx());

					//WLOG("llUserID[%lld].iSeatNo[%u].BankerViewID[%d].ViewID[%d].getMySeatIdx[%lld].m_wBankerChairID[%u].lGameScore[%lld]",
					//	pGameEnd->llUserID,
					//	pGameEnd->iSeatNo,
					//	BankerViewID,
					//	ViewID,
					//	SIX_PlayerMgr::GetInstance()->getMySeatIdx(),
					//	SIX_PlayerMgr::GetInstance()->m_wBankerChairID,
					//	pGameEnd->lGameScore);

					//if (BankerViewID==ViewID)
					//	continue;

					// save it~
					CUSTOM_INFO *pCustomInfo = new CUSTOM_INFO();
					pCustomInfo->ViewID = ViewID;
					pCustomInfo->bBanker = (BankerViewID==ViewID)?true:false;
					pCustomInfo->ChipCount = pGameEnd->lGameScore;
					pCustomInfo->UserID = pGameEnd->llUserID;
					pCustomInfo->lGameTax = pGameEnd->lGameTax;
					pCustomInfo->CardType = pGameEnd->CardType;
					pCustomInfo->CardPoint = pGameEnd->CardPoint;
					customVec.Push(pCustomInfo);
					//SIX_PlayerMgr::GetInstance()->mCustomWin.Push(pCustomInfo);
				}
				// �����м�����(Ĭ��˳ʱ��)
				pSceneGame->doSortCustomInfo(&customVec,true);
				// ������㶯��
				// Cool.Cat
				//pSceneGame->showAnimateSettleAccounts();
				pSceneGame->showAnimateSettleAccountsFinal();

				SIXLog("�ƾֽ�����");
			}
			break;
		}
	}
}

void SIX_ClientRoom::HandlePacketMatch(int iSubCode,unsigned char *pData,int iDataLen)
{

}
