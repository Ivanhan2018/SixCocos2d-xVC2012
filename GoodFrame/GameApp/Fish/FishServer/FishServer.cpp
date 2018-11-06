// FishServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <locale.h>      // setlocale 所需头文件，让控制台输出 Unicode 的中文

#include <iostream>
using std::cin ;	// 污染小些

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

// 程序图标
void set_my_logo()
{
	HWND   hwnd=GetConsoleWindow();   
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
}

// 显示提示信息
void show_prompt_msg()
{
	const int X =  10;
	const int Y = 64;

	char szPrompt[X][Y];

	sprintf(szPrompt[0], "?   提示 \n");
	sprintf(szPrompt[1], "CLS 清屏 \n");
	sprintf(szPrompt[2], "X   退出 \n");
	sprintf(szPrompt[3],  "T3 列印消息 \n");
	sprintf(szPrompt[4],  "T4 关闭所有的对端 \n");

	sprintf(szPrompt[5], "T5 设置房间（或桌子）定时器 \n");
	sprintf(szPrompt[6], "T6 杀掉房间（或桌子）定时器 \n");

	sprintf(szPrompt[7],  "T7 打印房间用户列表信息 \n");
	sprintf(szPrompt[8],  "T8 打印所有桌子用户列表信息 \n");

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

	::setlocale(LC_ALL,"");     // 让控制台输出 Unicode 的中文

	// 程序图标
	set_my_logo();	

	// 显示提示信息
	show_prompt_msg();

	int iRes = 0;
	const int INPUT_STRING_LEN = 32;
	char szInput[INPUT_STRING_LEN] = {0};	// 输入的字串
	char szUpper[INPUT_STRING_LEN] = {0};	// 转成大写的字串
	char szTemp[INPUT_STRING_LEN] = {0};
	char* p = NULL;
	int iNo = 0;

	string str;
	if(argc>1)
	{
		str=ws2s(argv[1]);
	}
	CFishTrunk::spawn(str.c_str());	// 孵化
	CFishTrunk* pService =  CFishTrunk::get_singleton_ptr();
	assert(pService);

	while(cin.getline(szInput, INPUT_STRING_LEN))
	{
		iNo = 0;

		// 转成大写的字串
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

		if( 0 == strcmp("CLS", szUpper))	// 清屏
		{
			system("cls");
		}
		else if( 0 == strcmp("?", szUpper))	// 快捷键提示
		{
			show_prompt_msg();
		}
		else if( 0 == strcmp("X", szUpper))	// 正常退出
		{
			break;
		}
		else if( 0 == strcmp("T7", szUpper))	
		{
			pService->m_pRoomMgr->PrintRoomUser();// 打印在线用户
		}
		else if( 0 == strcmp("T3", szUpper))	// 列印消息
		{
			// 显示所有的池信息
			pService->display_all_pool();

			// 列印未归池（在池外）的元素
			vector<OUT_POOL_ELEMENT> vecOutPool;
			pService->m_pMsgPool->display_out_pool(TRUE, vecOutPool);

			pService->display_all_guard();
		}
		else if( 0 == strcmp("T4", szUpper))	// 关闭所有的对端
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

	{	// 下面销毁一定按顺序，不能颠倒

		// 销毁所有桌子的游戏开始的定时器
		pService->destroy_game_start_timer();

		// 断开房管服务器 RMS（RoomMgrServer ）
		pService->destroy_client_to_rms();

		// 结束，必需在 uninit 函数之前执行本函数
		iRes = pService->stop();
		assert(0==iRes);

		// 释放资源，必需在 stop 函数之后执行本函数
		iRes = pService->uninit();
		assert(0==iRes);

		CFishTrunk::annihilate();	// 湮灭
	}

	_tprintf_s(_T("按任意键结束....."));
	getchar();
	return 0;
}

