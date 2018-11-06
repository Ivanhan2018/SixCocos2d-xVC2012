#include "./PublicHead.h"
#include "ClientLogic.h"
#include "Often.h"

// �����ں˿ͻ��˵� Lib
#if _WIN64	// 64λϵ��ϵͳ
	#if _DEBUG	
		#pragma comment(lib, "../../../PUBLIC_LIB/x64/ClientSkeleton64_d.lib") 
	#else
		#pragma comment(lib, "../../../PUBLIC_LIB/x64/ClientSkeleton64.lib") 
	#endif
#else		// 32λϵ��ϵͳ
	#if _DEBUG	
		#pragma comment(lib, "../../../PUBLIC_LIB/x32/ClientSkeleton32_d.lib") 	
	#else
		#pragma comment(lib, "../../../PUBLIC_LIB/x32/ClientSkeleton32.lib") 
	#endif
#endif

CClientLogic::CClientLogic(void)
{
	m_byGameState=E_GAME_FREE;
	m_IsAndroid=true;
}

CClientLogic::~CClientLogic(void)
{
}

void CClientLogic::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	COften::OutputInfo("CClientLogic::OnConnect");
	if(m_IsAndroid)
	{
		login_room();
	}
}

void CClientLogic::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
	COften::OutputInfo("CClientLogic::OnConnectFail");
}

void CClientLogic::OnCommError(char* pszError)
{
	COften::OutputInfo("CClientLogic::OnCommError");
}

void CClientLogic::OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	COften::OutputInfo("CClientLogic::OnSend");
}

void CClientLogic::OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	COften::OutputInfo("CClientLogic::OnSendFailed");
}

void CClientLogic::OnClose(CLOSE_TYPE iCloseType)
{
	COften::OutputInfo("CClientLogic::OnClose");
}

void CClientLogic::OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iMainCode)
	{
	case ROOM_MAIN:	// ������Ϣ
		{
			handle_room_msg(iSubCode, pData, iDataLen);

			break;
		}
	case ROOM_MGR_SERVER:	// ���ܷ��������
		{
			handle_write_db_msg(iSubCode, pData, iDataLen);
			break;
		}
	case TABLE_MAIN:	// ������Ϣ
		{
			handle_table_msg(iSubCode, pData, iDataLen);
			break;
		}
	case MANAGER_MAIN:	// ����Ա��Ϣ
		{
			handle_magager_msg(iSubCode, pData, iDataLen);
			break;
		}
	}
}

// ��������Ϣ
void CClientLogic::handle_room_msg(int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case ROOM_SUB_LOGIN_FAIL:
		{
			LOGIN_ROOM_FAIL* pReal = (LOGIN_ROOM_FAIL*)pData;
			printf("�û���¼ʧ�ܣ������룺%d  \n", pReal->iErrCode);
			return;
		}
	case ROOM_SUB_LOGIN_SUCC:	// �����ڹ㲥����¼����ɹ�
		{
			assert(sizeof(LOGIN_ROOM_SUCC)==iDataLen);
			if(sizeof(LOGIN_ROOM_SUCC)!=iDataLen)		// ����
				return;

			LOGIN_ROOM_SUCC* pReal = (LOGIN_ROOM_SUCC*)pData;

			_snprintf(m_stLoginSucc.szIP, sizeof(m_stLoginSucc.szIP), "%s", pReal->szIP);
			m_stLoginSucc.iPort = pReal->iPort;
			m_stLoginSucc.bAlreadyInRoom = pReal->bAlreadyInRoom;
			printf("��¼����ɹ���iPort=%d  \n", pReal->iPort);

			USER_INFO_SIM *pUserInfo = &pReal->userInfo;
			printf("�Լ�[%lld]��szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]\n",
				pUserInfo->lUserId,
				pUserInfo->szName,
				pUserInfo->szNickname,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);
		    memcpy(&m_MeUserInfo,pUserInfo,sizeof(USER_INFO_SIM));

			if(m_IsAndroid)
			{
				sit_down(pUserInfo->lUserId%10,-1);
			}

			return;

		}
	case ROOM_SUB_RECOME:	// ��������
		{
			assert(sizeof(RECOME_AFTER_CUT)==iDataLen);
			if(sizeof(RECOME_AFTER_CUT)!=iDataLen)		// ����
				return;

			RECOME_AFTER_CUT* pReal = (RECOME_AFTER_CUT*)pData;
			printf("%s �������룬����%d �� ����%d \n", pReal->szName, pReal->iTableNo, pReal->iSeatNo);

			return;
		}
	case ROOM_SUB_USER_INFO:	// ��¼�ߵ���Ϣ
		{
			assert(sizeof(USER_INFO)==iDataLen);
			if(sizeof(USER_INFO)!=iDataLen)		// ����
				return;

			USER_INFO* pReal = (USER_INFO*)pData;
			printf("�û���Ϣ, ������%s��  �ǳƣ�%s, \n", pReal->szName, pReal->szNickname);

			return;
		}
	case ROOM_SUB_USER_LIST:	// �����û��б�
		{
			//USER_INFO* pUserInfo = (USER_INFO*)pData;
			//vecUserInfo.push_back(*pUserInfo);
			printf("��������б�...\n");
			USER_INFO_SIM *pUserInfo = (USER_INFO_SIM*)pData;

			printf("���[%lld]��szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]\n",
				pUserInfo->lUserId,
				pUserInfo->szName,
				pUserInfo->szNickname,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);

			return;
		}
	case ROOM_SUB_USER_LIST_OVER:	// �����û��б����
		{
			printf("���ڵ��û��б������  \n");

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
			printf("���������б�...\n");
			SERVER_ROOM_INFO_SIM *packet = (SERVER_ROOM_INFO_SIM*)pData;
			printf("����ID[%d]����������[%ld].�������ӵ�����[%d].ÿ������[%d].��Ϸ����[%d].��Ƶ[%d]\n",packet->iRoomId,packet->iRoomPeopleCount,packet->iTables,packet->iSeatNum,packet->iRoomType,packet->iBasePoint);
			
			memcpy(&m_roomInfo,packet,sizeof(SERVER_ROOM_INFO_SIM));

			break;
		}
	case ROOM_SUB_LEAVE_ROOM:	// �뷿�ɹ�
		{
			LEAVE_ROOM_RESULT* pReal = (LEAVE_ROOM_RESULT*)pData;
			int a=0;
			//if(0 == pReal->iErrCode)
			//{
			//	printf("%s �뷿�ɹ� \n", pReal->userInfo.szName);
			//}
			//else
			//{
			//	printf("%s ���ڷ����ڣ� \n", pReal->userInfo.szName);
			//	close(CLOSE_TYPE_CLIENT_CLOSE);	// �ͻ��������رգ������رշ����
			//}
			if(m_IsAndroid)
			{

			}
		}
	}
}

// �������漰д���ݿ����Ϣ
void CClientLogic::handle_write_db_msg(int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case RMS_SUB_WRITE_SCORE_RESULT:
		{
			WRITE_SCORE_RESULT* pReal = (WRITE_SCORE_RESULT*)pData;
			//if(0==pReal->iRes)
			//	printf("д�ַ���, �û�ID=%I64d ��ǰ�ķ�ֵ=%I64d ����=%I64d \n",pReal->lUserId, pReal->lGold, pReal->lPoint);
			//else
			//	printf("д�ַ��أ�������=%d \n", pReal->iRes);
			break;
		}
	}
}

// ����������Ϣ
void CClientLogic::handle_table_msg(int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case TABLE_SUB_SITDOWN:
		{
			SITDOWN* pReal = (SITDOWN*)pData;
			if(0==pReal->iRes)
			{
				printf("�û�ID%I64d ���£�����%d , ����%d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo);
				if(m_IsAndroid && m_MeUserInfo.lUserId==pReal->lUserId)
				{
					raise_hand();
				}
			}
			else
				printf("�û�ID%I64d ����ʧ�ܣ�����%d , ����%d , ������ %d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo, pReal->iRes);

			break;
		}
	case TABLE_SUB_LEAVE_SEAT:
		{
			LEAVE_SEAT* pReal = (LEAVE_SEAT*)pData;
			if(0==pReal->iRes)
			{
				printf("��%d��, ��%d�� ���Ѿ����� \n", pReal->iTableNo, pReal->iSeatNo);
				if(m_IsAndroid && m_MeUserInfo.lUserId==pReal->lUserId)
				{
					sit_down(pReal->iTableNo, pReal->iSeatNo);
				}
			}
			else
				printf("����ʧ�ܣ��������Ѳ��ڴ���λ�� \n");

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
				printf("�û�ID%lld ����\n", pReal->lUserId);
			}
			else
			{
				printf("�û�ID%I64d ����ʧ��, ������ %d \n", pReal->lUserId, pReal->iRes);
			}

			break;
		}
	case RSP_CALL_BANKER_NOTIFY:		//������ׯ
		{
			Rsp_CallBankerNotify* pReal = (Rsp_CallBankerNotify*)pData;
			printf("������ׯ�� iServerSecs=%d \n",pReal->iServerSecs);
			m_byGameState=E_GAME_CALL_BANKER;

			break;
		}
	case RSP_CALL_BANKER_RESULT://��ׯ���
		{
			Rsp_BankerC3Info* pReal = (Rsp_BankerC3Info*)pData;
			printf("������ע�� wBankerUser=%d C3=%I64d C2=%I64d C1=%I64d \n",pReal->wBankerUser,pReal->C3,pReal->C2,pReal->C1);
			m_byGameState=E_GAME_CALL_SCORE;

			break;
		}
	case RSP_USER_CHIPIN:		//�û���ע
		{
			Req_UserChipin* pReal = (Req_UserChipin*)pData;
			printf("�û���ע���� �û�ID=%I64d ��λ��=%d ��ע��=%I64d \n",pReal->llUserID,pReal->iSeatNo,pReal->lScore);

			break;
		}
	case RSP_SEND_CARD_LIST://����
		{
			Rsp_SendCard_List* pReal = (Rsp_SendCard_List*)pData;
			for(int i=0;i<pReal->nCount;i++)
			{
				Rsp_SendCard *pSendCard=&pReal->m_SendCards[i];
				printf("�˿�����=(%d,%d,%d) �û�ID=%I64d ��λ��=%d \n",(int)pSendCard->cbUserCardData[0],(int)pSendCard->cbUserCardData[1],(int)pSendCard->cbUserCardData[2],pSendCard->llUserID,pSendCard->iSeatNo);
			}
			m_byGameState=E_GAME_SHOW_CARD;

			break;
		}
	case RSP_GAME_END_LIST://һ����Ϸ����
		{
			Rsp_GameEnd_List* pReal = (Rsp_GameEnd_List*)pData;
			for(int i=0;i<pReal->nCount;i++)
			{
				Rsp_GameEnd *pGameEnd=&pReal->m_GameEnds[i];//&(*pReal)[i];
				printf("һ����Ϸ���� �û�ID=%I64d ��λ��=%d ��Ϸ˰��=%I64d ��������=%I64d ����=%d ����=%d \n",pGameEnd->llUserID,pGameEnd->iSeatNo,pGameEnd->lGameTax,pGameEnd->lGameScore,(int)pGameEnd->CardType,(int)pGameEnd->CardPoint);
			}
			m_byGameState=E_GAME_FREE;
			if(m_IsAndroid)
			{
				raise_hand();
			}

			break;
		}

	}
}

// �������Ա��Ϣ
void CClientLogic::handle_magager_msg(int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case MANAGER_SUB_POWER_ERR:	// �޴˹���Ȩ��
		{
			MANAGER_POWER_ERR* pReal = (MANAGER_POWER_ERR*)pData;
			printf("����ԱʩȨʧ�ܣ��㲢�� %d Ȩ�� \n", pReal->iWantPower);
			break;
		}
	case MANAGER_SUB_TICK_ONE_LEAVE_SEAT:	// ��һ���������
		{
			TICK_ONE_LEAVE_SEAT* pReal = (TICK_ONE_LEAVE_SEAT*)pData;
			if(0==pReal->iRes)
				printf("�� ����%d ����%d �����ɹ� \n", pReal->iTableNo, pReal->iSeatNo);
			else
				printf("�� ����%d ����%d ����ʧ�ܣ������� %d \n", pReal->iTableNo, pReal->iSeatNo, pReal->iRes);

			break;
		}
	case MANAGER_SUB_TICK_TABLE_LEAVE_SEAT:	// ��һ���������
		{
			TICK_TABLE_LEAVE_SEAT* pReal = (TICK_TABLE_LEAVE_SEAT*)pData;

			if(0==pReal->iRes)
				printf("�� ����%d ȫ�������ɹ� \n", pReal->iTableNo);
			else
				printf("�� ����%d ȫ������ʧ�ܣ������� %d \n", pReal->iTableNo, pReal->iRes);

			break;
		}
	case MANAGER_SUB_TICK_ALL_LEAVE_SEAT:	// �������������������
		{
			TICK_ALL_LEAVE_SEAT* pReal = (TICK_ALL_LEAVE_SEAT*)pData;

			if(0==pReal->iRes)
				printf("��������������������ɹ� \n");
			else
				printf("�������������������ʧ�ܣ������� %d \n", pReal->iRes);

			break;
		}
	case MANAGER_SUB_TICK_USER_OUT_ROOM:	// ������뷿
		{
			TICK_USER_OUT_ROOM* pReal = (TICK_USER_OUT_ROOM*)pData;

			if(0==pReal->iRes)
			{
				switch(pReal->iTickMode)
				{
				case TICK_USER_OUT_ROOM::TICK_BY_TABLE_SEAT:	// �����š�������
					{
						printf("%s ������%d ����%d�� ������Ա�߳����� \n", 
									pReal->szName, pReal->iTableNo, pReal->iSeatNo);
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_NAME:	// ��������
					{
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_TABLE:	// �������ߣ���һ�������뷿
					{
						printf("��%d��ȫ���˱�����Ա�߳����� \n", 
								pReal->iTableNo);
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_ALL:	// �����е����뷿
					{
						printf("���е��˱�����Ա�߳����� \n");
						break;
					}
				}

				close(CLOSE_TYPE_CLIENT_CLOSE);	// �Ͽ����������ͻ��������ر�
				printf_s("��ʵ����Ҳ���Խ������������� X ����������...... \n ");	// ��ʵ����Ҳ���Խ���������������

			}
			else
			{
				switch(pReal->iTickMode)
				{
				case TICK_USER_OUT_ROOM::TICK_BY_TABLE_SEAT:	// �����š�������
					{
						printf("�� %s ������%d ����%d�� �뷿ʧ�ܣ�������%d \n", 
								pReal->szName, pReal->iTableNo, pReal->iSeatNo, pReal->iRes);
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_NAME:	// ��������
					{
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_TABLE:	// �������ߣ���һ�������뷿
					{
						printf("�� ����%d �뷿ʧ�ܣ�������%d \n", 
								pReal->iTableNo, pReal->iRes);
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_ALL:	// �����е����뷿
					{
						printf("�����е����뷿ʧ�ܣ�������%d \n", pReal->iRes);
						break;
					}
				}
			}

			break;
		}
	}
}


int CClientLogic::ConnectRoom(string str[5])
{
	int iRes = 0;

	// ���ӵĿ�ܲ��������캯������Ĭ��ֵ
	CLIENT_FRAME_PARAM frameParam;	
	frameParam.iSendHeartbeatTime = 30*1000;

	// �ͻ��˵ķ�����Ϣ��Ӧ�ô������д���Ļ����ǹܵ��Ӵ��������д���ģ���δ��???
	CLIENT_ROOM_INFO clientRoomInfo;


	_snprintf(clientRoomInfo.szIP, sizeof(clientRoomInfo.szIP)-1,str[3].c_str());		// ���ط���IP


	clientRoomInfo.iPort=atoi(str[4].c_str());												// ����˿�

	//_snprintf(clientRoomInfo.szName, sizeof(clientRoomInfo.szName)-1, szName);		// �û���
	strcpy(clientRoomInfo.szName,str[1].c_str());
	_snprintf(clientRoomInfo.szPassword, sizeof(clientRoomInfo.szPassword)-1,str[2].c_str());	// ����

	setUserID(atoi(str[0].c_str()));

	iRes = init(clientRoomInfo, frameParam);
	iRes = start();
	return iRes;
}