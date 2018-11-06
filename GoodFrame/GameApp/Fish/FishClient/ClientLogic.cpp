
#include "./PublicHead.h"
#include "ClientLogic.h"

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
	
}

CClientLogic::~CClientLogic(void)
{
}

void CClientLogic::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
}

void CClientLogic::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
}

void CClientLogic::OnCommError(char* pszError)
{
}

void CClientLogic::OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
}

void CClientLogic::OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
}

void CClientLogic::OnClose(CLOSE_TYPE iCloseType)
{
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
			printf("��������[%ld]���������ӵ�����[%d].ÿ������[%d].��Ϸ����[%d].��Ƶ[%d]\n",packet->iRoomPeopleCount,packet->iTables,packet->iSeatNum,packet->iRoomType,packet->iBasePoint);
			break;
		}
	case ROOM_SUB_LEAVE_ROOM:	// �뷿�ɹ�
		{
			LEAVE_ROOM_RESULT* pReal = (LEAVE_ROOM_RESULT*)pData;
			//if(0 == pReal->iErrCode)
			//{
			//	printf("%s �뷿�ɹ� \n", pReal->userInfo.szName);
			//}
			//else
			//{
			//	printf("%s ���ڷ����ڣ� \n", pReal->userInfo.szName);
			//	close(CLOSE_TYPE_CLIENT_CLOSE);	// �ͻ��������رգ������رշ����
			//}
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
			//printf("д�ֽ��������ֵ%d����ǰ��ֵ%d \n", pReal->iRes, pReal->lScore);
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
				printf("�û�ID%I64d ���£�����%d , ����%d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo);
			else
				printf("�û�ID%I64d ��������ʧ�ܣ�����%d , ����%d , ������ %d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo, pReal->iRes);

			break;
		}
	case TABLE_SUB_LEAVE_SEAT:
		{
			LEAVE_SEAT* pReal = (LEAVE_SEAT*)pData;
			if(0==pReal->iRes)
				printf("��%d��, ��%d�� ���Ѿ����� \n", pReal->iTableNo, pReal->iSeatNo);
			else
				printf("����ʧ�ܣ��������Ѳ��ڴ���λ�� \n");

			break;
		}
	case TABLE_SUB_WRITE_SCORE_RET:
		{
			WRITE_SCORE_RESULT* pReal = (WRITE_SCORE_RESULT*)pData;
			if(0==pReal->iRes)
				printf("д�ַ���, �û�ID=%I64d ��ǰ�ķ�ֵ=%I64d ����=%I64d \n",pReal->lUserId, pReal->lGold, pReal->lPoint);
			else
				printf("д�ַ��أ�������=%d \n", pReal->iRes);

			break;
		}
	case RSP_ADD_ONE_FISH:
		{
				//printf("����...\n");

			break;
		}
	case TABLE_SUB_FIRE:
		{
			//SHOT_FIRE_RESULT* pReal = (SHOT_FIRE_RESULT*)pData;
			//if(0==pReal->iRes)
			//	printf("%s ����, ����%d ����%d �ӵ���%d \n", 
			//	pReal->szName, pReal->iTableNo, pReal->iSeatNo, pReal->iBulletNum);
			//else
			//	printf("����ʧ�ܣ������� %d \n", pReal->iRes);

			break;
		}
		//add by Ivan_han
	case RSP_ADD_ONE_FISH_ARR:
		{
#if 0
			Rsp_AddOneFish_Arr* pReal = (Rsp_AddOneFish_Arr*)pData;
			printf("��켣��, ����%d ��켣������%d������Ŀ%d \n", 
				pReal->TableID, pReal->FishGroupType,pReal->nFishCount);
#endif
			break;
		}
		//add by Ivan_han
	case RSP_ADD_ONE_FISH_LIST:
		{
#if 0
			Rsp_AddOneFish_List* pReal = (Rsp_AddOneFish_List*)pData;
			printf("��켣��, ����%d ��켣������%d������Ŀ%d \n", 
				pReal->TableID, pReal->FishGroupType,pReal->nFishCount);
			for(int i=0;i<pReal->nFishCount;i++)
			{
				Rsp_AddOneFish *pRecord=&(*pReal)[i];
				int a=0;
			}
#endif
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

// ����
int CClientLogic::test()
{
#if 0
	MY_TEST sendData;
	sendData.a = 1001;
	sendData.b = 1002;

	int iType = 1;
	if(0 == iType)	// ������Ϣ����Ӧ�ò�
	{
		send_data(ROOM_MAIN, ROOM_SUB_MY_TEST, (BYTE*)(&sendData), sizeof(sendData));
	}
	else if(1 == iType)	// ������Ϣ����Ӧ�ò�
	{
		send_data(TABLE_MAIN, ROOM_SUB_MY_TEST, (BYTE*)(&sendData), sizeof(sendData));
	}
#endif
	return 0;
}

// ����
int CClientLogic::fire()
{
	static int iTestNo = 0;

	//SHOT_FIRE sendData(0,0,0,0,0,0,0,0,0,false);
	//send_data(TABLE_MAIN, TABLE_SUB_FIRE, (BYTE*)(&sendData), sizeof(sendData));

	return 0;
}

//  ���Ͳ�����Ϣ
void CClientLogic::send_test_msg(int iType)
{
#if 0
	MY_TEST myTest;
	myTest.a = 1001;
	myTest.b = 3399;

	switch(iType)
	{
	case 0:	// ����
		{
			send_data(MATCH_MAIN, MATCH_SUB_CS_ARRANGE_QUEUE, (BYTE*)(&myTest), sizeof(myTest));
			break;
		}
	case 1:	// ��Ϸ����
		{
			send_data(TASK_MAIN, TASK_SUB_TEST, (BYTE*)(&myTest), sizeof(myTest));
			break;
		}
	case 2:	// ����
		{
			send_data(PROP_MAIN, PROP_SUB_TEST, (BYTE*)(&myTest), sizeof(myTest));
			break;
		}
	}
#endif
}

//// ����һ���ڵ���add by Ivan_han
//int CClientLogic::fire(Req_UserShoot &req)
//{
//	//send_data(TABLE_MAIN, REQ_USER_SHOOT, (BYTE*)(&req), sizeof(req));
//
//	return 0;
//}
