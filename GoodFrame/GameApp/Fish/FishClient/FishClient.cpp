// FishClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"

#include "./PublicHead.h"
#include "ClientLogic.h"

#include "../GameMsg/ProFish.h"//add by Ivan_han
#define M_PI_4     0.785398163397448309616
#include <iostream>
using std::cin ;	// ��ȾСЩ

#include "resource.h"		// ��Դ

#include "Often.h"
#pragma comment(lib,"ws2_32.lib")

#define STR_LEN 32

// ����ͼ��
void set_logo()
{
	HWND   hwnd=GetConsoleWindow();   
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
}

// ��ʾ��ʾ��Ϣ
void show_prompt_msg()
{
	const int X = 21;
	const int Y = 64;

	char szPrompt[X][Y];

	sprintf(szPrompt[0],  "?   ��ʾ \n");
	sprintf(szPrompt[1], "CLS ���� \n");
	sprintf(szPrompt[2], "X   �˳� \n");

	sprintf(szPrompt[3],  "T3 ��¼����    \n");
	sprintf(szPrompt[4],  "T4 �뿪����  \n");
	sprintf(szPrompt[5],  "T5 ���� \n");
	sprintf(szPrompt[6],  "T6 ���� \n");
	sprintf(szPrompt[7],  "T7 ���� \n");

	sprintf(szPrompt[8],  "T8 ���� \n");

	sprintf(szPrompt[9],  "T9 ����ʱд�� \n");
	sprintf(szPrompt[10], "T10 ���뷿�ڵ��û��б� \n");
	sprintf(szPrompt[11], "T11 �ܼ�������Ҫ���û��� \n");

	sprintf(szPrompt[12], "TKU a b ��a��b�����������  \n");
	sprintf(szPrompt[13], "TKT a   ��a����������� \n");
	sprintf(szPrompt[14], "TKA �������������������  \n");

	sprintf(szPrompt[15], "TR1 a b  ��a��b��������뷿  \n");
	sprintf(szPrompt[16], "TR3 a    ��a�����е�����뷿  \n");
	sprintf(szPrompt[17], "TR4      �����е�����뷿  \n");

	sprintf(szPrompt[18], "SM a     ���ͣ�a ȡֵ 0���� 1��Ϸ���� 2���ߣ� ��Ϣ  \n");

	sprintf(szPrompt[19],  "FIRE ���� \n");//add by Ivan_han
	sprintf(szPrompt[20],  "SIT a b ����a��b�� \n");//add by Ivan_han

	for(int i=0; i<X; i++)
	{
		printf(szPrompt[i]);
	}

	printf("\n");
}

#define USER_NUMBER 90	// ���ݿ��еĲ����û�����

// ��ÿͻ���������Ϣ����Ҫ���ڵ��ԣ�Ŀ���ǵ���ʱ�Զ����ò�ͬ���û���
void get_client_config(char* pszName, int& iSeatNo)
{
	char szTmp[32];
	string strPath, strPathFile;
	COften::get_current_path(strPath);

	strPathFile = strPath + "FishClientConfig.ini";

	UINT iChangeNameNo = GetPrivateProfileIntA("NAME_NO", "ChangeNameNo", 1, strPathFile.c_str());	// �������ļ��ж�ȡ

	UINT iNameNo = GetPrivateProfileIntA("NAME_NO", "NameNo", 0, strPathFile.c_str());	// �������ļ��ж�ȡ
	printf("iNameNo=%d \n",iNameNo);

	int iUserNo = iNameNo%USER_NUMBER;
	iSeatNo = iUserNo%4;

	switch(iUserNo)
	{
	case 0:
		sprintf(pszName, "��ë");
		break;
	case 1:
		sprintf(pszName, "��һ");
		break;
	case 2:
		sprintf(pszName, "���");
		break;
	case 3:
		sprintf(pszName, "����");
		break;
	case 4:
		sprintf(pszName, "����");
		break;
	case 5:
		sprintf(pszName, "����");
		break;
	case 6:
		sprintf(pszName, "����");
		break;
	case 7:
		sprintf(pszName, "����");
		break;
	case 8:
		sprintf(pszName, "���");
		break;
	case 9:
		sprintf(pszName, "Ǯ��");
		break;
	default:
		sprintf(pszName, "T%2d", iUserNo);
		break;
	}

	if(iChangeNameNo>0)
	{
		_snprintf(szTmp, sizeof(szTmp)-1, "%d", iNameNo+1);
		WritePrivateProfileStringA("NAME_NO", "NameNo", szTmp, strPathFile.c_str());	// д�������ļ�
	}

	int iTmp = 0;
}

// ����������
void parse_cmd(char* szSource, int iSourceLen, char* pszMain, char* pszParam01, char* pszParam02, char* pszParam03)
{
	char szUpper[STR_LEN] = {0};	// ת�ɴ�д���ִ�

	int iNo = 0;
	char* p = szSource;

	// ת�ɴ�д���ִ�
	for( p = szSource; p <szSource+iSourceLen ; p++, iNo++ )
	{
		if( islower(*p) )
			szUpper[iNo] = _toupper(*p);
		else
			szUpper[iNo] = *p;
	}

	string strIn(szUpper);
	string strSeparator(" ");
	vector<string> vecStrOut;
	COften::devide_string_to_separator(strIn, strSeparator, vecStrOut);
	size_t iSize = vecStrOut.size();

	for(int i=0; i<vecStrOut.size(); i++)
	{
		if(0==i)
			sprintf(pszMain, "%s", vecStrOut.at(i).c_str()  );
		else if(1==i)
			sprintf(pszParam01, "%s", vecStrOut.at(i).c_str() );
		else if(2==i)
			sprintf(pszParam02, "%s", vecStrOut.at(i).c_str() );
		else if(3==i)
			sprintf(pszParam03, "%s", vecStrOut.at(i).c_str() );
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	::setlocale(LC_ALL,"");     // �ÿ���̨��� Unicode ������

	char szName[32];
	int iTable = 0;	// ���ţ�������
	int iSeatNo;	// ���ţ�������

	// ��ÿͻ���������Ϣ����Ҫ���ڵ��ԣ�Ŀ���ǵ���ʱ�Զ����ò�ͬ���û���
	get_client_config(szName, iSeatNo);

	// ����ͼ��
	set_logo();
	show_prompt_msg();

	CClientLogic* pClientLogic = new CClientLogic;
	assert(pClientLogic);

	int iRes = 0;
	

	// ���ӵĿ�ܲ��������캯������Ĭ��ֵ
	CLIENT_FRAME_PARAM frameParam;	
	frameParam.iSendHeartbeatTime = 5*60*1000;	// �����ã�������Ƶ���ĳ��ָ��ŵ���

	// �ͻ��˵ķ�����Ϣ��Ӧ�ô������д���Ļ����ǹܵ��Ӵ��������д���ģ���δ��???
	CLIENT_ROOM_INFO clientRoomInfo;

	int iType = 0;
	if(0==iType)
		_snprintf(clientRoomInfo.szIP, sizeof(clientRoomInfo.szIP)-1, "127.0.0.1");		// ���ط���IP
	else if(1==iType)
		_snprintf(clientRoomInfo.szIP, sizeof(clientRoomInfo.szIP)-1, "192.168.1.99");		// ����99������IP
	else if(2==iType)
		_snprintf(clientRoomInfo.szIP, sizeof(clientRoomInfo.szIP)-1, "112.124.39.86");		// �����ķ���IP

	clientRoomInfo.iPort = 7000;													// ����˿�

	//_snprintf(clientRoomInfo.szName, sizeof(clientRoomInfo.szName)-1, szName);		// �û���
	strcpy(clientRoomInfo.szName,"T9");
	#if 1
		_snprintf(clientRoomInfo.szPassword, sizeof(clientRoomInfo.szPassword)-1, "202cb962ac59075b964b07152d234b70");	// ����
	#else
		_snprintf(clientRoomInfo.szPassword, sizeof(clientRoomInfo.szPassword)-1, "123ttt");	// ���룬������󣬲�����
	#endif

    pClientLogic->setUserID(9);
	
	iRes = pClientLogic->init(clientRoomInfo, frameParam);
	iRes = pClientLogic->start();

	char szMain[STR_LEN], szParam01[STR_LEN], szParam02[STR_LEN], szParam03[STR_LEN];
	char szInput[STR_LEN] = {0};	// ������ִ�

	while(cin.getline(szInput, STR_LEN))
	{
		memset(szMain , 0, sizeof(szMain));
		memset(szParam01 , 0, sizeof(szParam01));
		memset(szParam02 , 0, sizeof(szParam02));
		memset(szParam03 , 0, sizeof(szParam03));

		parse_cmd(szInput, lstrlenA(szInput), szMain, szParam01, szParam02, szParam03);
	
		if( 0 == strcmp("CLS", szMain ))	// ����
		{
			system("cls");
		}
		else if( 0 == strcmp("?", szMain))	// ��ݼ���ʾ
		{
			show_prompt_msg();
		}
		else if( 0 == strcmp("X", szMain))	// �����˳�
		{
			break;
		}
		else if( 0 == strcmp("T3", szMain))	// ��¼����
		{
			pClientLogic->login_room();
		}
		else if( 0 == strcmp("T4", szMain))	// �뿪���䣬�൱���˳�ȥ��
		{
			pClientLogic->leave_room();
			break;
		}
		else if( 0 == strcmp("T5", szMain))	// ����
		{
			int iTableNumInRoom = 2;	// �����е���������
			srand( (unsigned)time( NULL ) );
			iTable = rand()%iTableNumInRoom;
			pClientLogic->sit_down(iTable, iSeatNo);
		}
		else if( 0 == strcmp("T6", szMain))	// �ܹ���ʼ��Ϸ
		{
			pClientLogic->raise_hand();
		}
		else if( 0 == strcmp("T7", szMain))  // ����
		{
			pClientLogic->leave_seat();
		}
		else if( 0 == strcmp("T8", szMain))	// ����
		{
			pClientLogic->fire();
		}
		else if( 0 == strcmp("T9", szMain))	// ����ʱд��
		{
			CMD_WRITE_SCORE score;
			score.lGold = 0;

			pClientLogic->write_score(score);
		}
		else if( 0 == strcmp("T10", szMain))	// ���뷿�ڵ��û��б�
		{
			pClientLogic->query_user_list();
		}
		else if( 0 == strcmp("T11", szMain))	// �ܼ�������Ҫ���û���
		{
			// �ܼ�����
			for(int i=0; i<20; i++)
			{
				pClientLogic->fire();
				//Sleep(100);
			}
		}
		else if( 0 == strcmp("TKU", szMain))	// ��һ������������뷿
		{
			pClientLogic->tick_one_leave_seat(atoi(szParam01), atoi(szParam02));
		}
		else if( 0 == strcmp("TKT", szMain))	// ��һ���������
		{
			pClientLogic->tick_table_leave_seat(atoi(szParam01));
		}
		else if( 0 == strcmp("TKA", szMain))	// ��һ���������
		{
			pClientLogic->tick_all_leave_seat();
		}
		else if( 0 == strcmp("TR1", szMain))	// 
		{
			int iTableNo = atoi(szParam01);
			int iSeatNo = atoi(szParam02);
			pClientLogic->tick_user_out_room(iTableNo, iSeatNo);
		}
		else if(0 == strcmp("TR3", szMain))	// ��a�����е�����뷿
		{
			int iTableNo = atoi(szParam01);
			pClientLogic->tick_user_out_room(iTableNo);
		}
		else if(0 == strcmp("TR4", szMain))	// �����е�����뷿
		{
			pClientLogic->tick_user_out_room();
		}
		else if(0 == strcmp("SM", szMain))	// ���Ͳ�����Ϣ
		{
			int iType = atoi(szParam01);
			pClientLogic->send_test_msg(iType);	
		}

		////add by Ivan_han
		//else if( 0 == strcmp("FIRE", szMain))	// ����
		//{
		//	//static TBulletID BulletID=0;
		//	Req_UserShoot sendData;
		//	//sendData.BulletID++;
		//	sendData.Angle=M_PI_4;
		//	sendData.GunGrade=3;
		//	pClientLogic->fire(sendData);
		//}
		//add by Ivan_han
		else if( 0 == strcmp("SIT", szMain))
		{
			
			int iTableNo = atoi(szParam01);
			int iSeatNo = atoi(szParam02);
			pClientLogic->sit_down(iTableNo, iSeatNo);
		}		

		memset(szInput, 0, sizeof(szInput));
	}
	
	pClientLogic->stop();

	_tprintf_s(_T("�����������....."));
	getchar();

	return 0;
}

