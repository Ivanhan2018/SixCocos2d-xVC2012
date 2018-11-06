// FishClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"

#include "./PublicHead.h"
#include "ClientLogic.h"

#include "../GameMsg/CMD_SanGong.h"//add by Ivan_han
#define M_PI_4     0.785398163397448309616
#include <iostream>
using std::cin ;	// ��ȾСЩ

#include "resource.h"		// ��Դ

#include "Often.h"
#pragma comment(lib,"ws2_32.lib")

#define STR_LEN 32

string ws2s(const wstring& ws)
{
	string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";

	setlocale(LC_ALL, "chs"); 

	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	string result = _Dest;
	delete []_Dest;

	setlocale(LC_ALL, curLocale.c_str());

	return result;
}

wstring s2ws(const string& s)
{
	setlocale(LC_ALL, "chs"); 

	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	wstring result = _Dest;
	delete []_Dest;

	setlocale(LC_ALL, "C");

	return result;
}

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
	sprintf(szPrompt[5],  "T5 a ������ׯ��0������1���0������Ϣ \n");
	sprintf(szPrompt[6],  "T6 ���� \n");
	sprintf(szPrompt[7],  "T7 ���� \n");

	sprintf(szPrompt[8],  "T8 a ������ע��a��{C1,C2,C3}����Ϣ\n");

	sprintf(szPrompt[9],  "T9 ����ʱд�� \n");
	sprintf(szPrompt[10], "T10 ���뷿�ڵ��û��б� \n");
	sprintf(szPrompt[11], "RTLIST ��ȡ������Ϣ \n");

	sprintf(szPrompt[12], "TKU a b ��a��b�����������  \n");
	sprintf(szPrompt[13], "TKT a   ��a����������� \n");
	sprintf(szPrompt[14], "TKA �������������������  \n");

	sprintf(szPrompt[15], "TR1 a b  ��a��b��������뷿  \n");
	sprintf(szPrompt[16], "TR3 a    ��a�����е�����뷿  \n");
	sprintf(szPrompt[17], "TR4      �����е�����뷿  \n");

	sprintf(szPrompt[18], "SM a     ���ͣ�a ȡֵ 0���� 1��Ϸ���� 2���ߣ� ��Ϣ  \n");

	sprintf(szPrompt[19],  "CR a ���ӷ���a\n");
	sprintf(szPrompt[20],  "SIT a b ����a��b�� \n");

	for(int i=0; i<X; i++)
	{
		printf(szPrompt[i]);
	}

	printf("\n");
}

#define USER_NUMBER 90	// ���ݿ��еĲ����û�����



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



	// ����ͼ��
	set_logo();
	show_prompt_msg();

	CClientLogic* pClientLogic = new CClientLogic;
	assert(pClientLogic);

	string str[6];
	if(argc>6)
	{
		str[0]=ws2s(argv[1]);
		str[1]=ws2s(argv[2]);
		str[2]=ws2s(argv[3]);
		str[3]=ws2s(argv[4]);
		str[4]=ws2s(argv[5]);
		str[5]=ws2s(argv[6]);
	}
	else
	{
		str[0]="19";
		str[1]="T19";
		str[2]="202cb962ac59075b964b07152d234b70";
		str[3]="127.0.0.1";
		str[4]="8000";
		str[5]="1";
	}

	if(str[5]=="1")
		pClientLogic->m_IsAndroid=true;
	else
		pClientLogic->m_IsAndroid=false;
	
	int iRes = pClientLogic->ConnectRoom(str);

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
			//break;
		}
		else if( 0 == strcmp("T5", szMain))	// ��ׯ
		{
			bool bCall=atoi(szParam01)!=0?true:false;
			Req_UserCallBanker req;
			req.llUserID=pClientLogic->m_MeUserInfo.lUserId;
			req.iSeatNo=pClientLogic->m_MeUserInfo.iSeatNo;
			req.bCall=bCall;
			pClientLogic->send_data(TABLE_MAIN,REQ_USER_CALL_BANKER,(BYTE*)(&req), sizeof(req));
		}
		else if( 0 == strcmp("T6", szMain))	// �ܹ���ʼ��Ϸ
		{
			pClientLogic->raise_hand();
		}
		else if( 0 == strcmp("T7", szMain))  // ����
		{
			pClientLogic->leave_seat();
		}
		else if( 0 == strcmp("T8", szMain))	// ��ע
		{
			TChip lScore=_atoi64(szParam01);
			Req_UserChipin req;
			req.llUserID=pClientLogic->m_MeUserInfo.lUserId;
			req.iSeatNo=pClientLogic->m_MeUserInfo.iSeatNo;
			req.lScore=lScore;
			pClientLogic->send_data(TABLE_MAIN, REQ_USER_CHIPIN, (BYTE*)(&req), sizeof(req));			
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
		else if( 0 == strcmp("RTLIST", szMain))	// ��ȡ������Ϣ
		{
			pClientLogic->send_data(ROOM_MAIN, ROOM_SUB_TABLE_LIST);
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
		else if(0 == strcmp("CR", szMain))	// ���ӷ���a
		{
			str[4]=szParam01;
			pClientLogic->leave_room();
			pClientLogic->stop();
			pClientLogic->ConnectRoom(str);
		}

		else if( 0 == strcmp("SIT", szMain))
		{
			int iTableNo = atoi(szParam01);
			int iSeatNo = atoi(szParam02);
			pClientLogic->sit_down(iTableNo,iSeatNo);
		}	

		memset(szInput, 0, sizeof(szInput));
	}
	
	pClientLogic->stop();

	_tprintf_s(_T("�����������....."));
	getchar();

	return 0;
}

