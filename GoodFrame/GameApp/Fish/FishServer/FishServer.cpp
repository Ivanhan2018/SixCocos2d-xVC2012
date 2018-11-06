// FishServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <stdio.h>
#include <locale.h>      // setlocale ����ͷ�ļ����ÿ���̨��� Unicode ������

#include <iostream>
using std::cin ;	// ��ȾСЩ

#include "resource.h"

//#include <strsafe.h>
//#pragma comment(lib, "strsafe.lib") 

#include "FishTrunk.h"
#include "MiniDumper.h"

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
void set_my_logo()
{
	HWND   hwnd=GetConsoleWindow();   
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
}

// ��ʾ��ʾ��Ϣ
void show_prompt_msg()
{
	const int X =  10;
	const int Y = 64;

	char szPrompt[X][Y];

	sprintf(szPrompt[0], "?   ��ʾ \n");
	sprintf(szPrompt[1], "CLS ���� \n");
	sprintf(szPrompt[2], "X   �˳� \n");
	sprintf(szPrompt[3],  "T3 ��ӡ��Ϣ \n");
	sprintf(szPrompt[4],  "T4 �ر����еĶԶ� \n");

	sprintf(szPrompt[5], "T5 ���÷��䣨�����ӣ���ʱ�� \n");
	sprintf(szPrompt[6], "T6 ɱ�����䣨�����ӣ���ʱ�� \n");

	sprintf(szPrompt[7],  "T7 ��ӡ�����û��б���Ϣ \n");
	sprintf(szPrompt[8],  "T8 ��ӡ���������û��б���Ϣ \n");

	sprintf(szPrompt[9], "  \n");

	for(int i=0; i<X; i++)
	{
		printf(szPrompt[i]);
	}

	printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])

{
	CMiniDumper *pMiniDumper = new CMiniDumper();

	::setlocale(LC_ALL,"");     // �ÿ���̨��� Unicode ������

	// ����ͼ��
	set_my_logo();	

	// ��ʾ��ʾ��Ϣ
	show_prompt_msg();

	int iRes = 0;
	const int INPUT_STRING_LEN = 32;
	char szInput[INPUT_STRING_LEN] = {0};	// ������ִ�
	char szUpper[INPUT_STRING_LEN] = {0};	// ת�ɴ�д���ִ�
	char szTemp[INPUT_STRING_LEN] = {0};
	char* p = NULL;
	int iNo = 0;

	string str;
	if(argc>1)
	{
		str=ws2s(argv[1]);
	}
	CFishTrunk::spawn(str.c_str());	// ����
	CFishTrunk* pService =  CFishTrunk::get_singleton_ptr();
	assert(pService);

	while(cin.getline(szInput, INPUT_STRING_LEN))
	{
		iNo = 0;

		// ת�ɴ�д���ִ�
		for( p = szInput; p < szInput + lstrlenA(szInput); p++, iNo++ )
		{
			if( islower(*p) )
			{
				szUpper[iNo] = _toupper(*p);
			}
			else
			{
				szUpper[iNo] = *p;
			}
		}

		if( 0 == strcmp("CLS", szUpper))	// ����
		{
			system("cls");
		}
		else if( 0 == strcmp("?", szUpper))	// ��ݼ���ʾ
		{
			show_prompt_msg();
		}
		else if( 0 == strcmp("X", szUpper))	// �����˳�
		{
			break;
		}
		else if( 0 == strcmp("T7", szUpper))	
		{
			pService->m_pRoomMgr->PrintRoomUser();// ��ӡ�����û�
		}
		else if( 0 == strcmp("T3", szUpper))	// ��ӡ��Ϣ
		{
			// ��ʾ���еĳ���Ϣ
			pService->display_all_pool();

			// ��ӡδ��أ��ڳ��⣩��Ԫ��
			vector<OUT_POOL_ELEMENT> vecOutPool;
			pService->m_pMsgPool->display_out_pool(TRUE, vecOutPool);

			pService->display_all_guard();
		}
		else if( 0 == strcmp("T4", szUpper))	// �ر����еĶԶ�
		{
			pService->close_all_peer();
		}
		else if( 0 == strcmp("T5", szUpper))	// 
		{
			pService->test_05();
		}
		else if( 0 == strcmp("T6", szUpper))	
		{
			pService->test_06();
		}
		else if( 0 == strcmp("T8", szUpper))	
		{
			pService->m_pRoomMgr->PrintAllTableUser();
		}

		memset(szInput, 0, sizeof(szInput));
		memset(szUpper, 0, sizeof(szUpper));
	}

	{	// ��������һ����˳�򣬲��ܵߵ�

		// �����������ӵ���Ϸ��ʼ�Ķ�ʱ��
		pService->destroy_game_start_timer();

		// �Ͽ����ܷ����� RMS��RoomMgrServer ��
		pService->destroy_client_to_rms();

		// ������������ uninit ����֮ǰִ�б�����
		iRes = pService->stop();
		assert(0==iRes);

		// �ͷ���Դ�������� stop ����֮��ִ�б�����
		iRes = pService->uninit();
		assert(0==iRes);

		CFishTrunk::annihilate();	// ����
	}

	_tprintf_s(_T("�����������....."));
	getchar();
	return 0;
}

