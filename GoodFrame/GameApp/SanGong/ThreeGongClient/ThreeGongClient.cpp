// FishClient.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"

#include "./PublicHead.h"
#include "ClientLogic.h"

#include "../GameMsg/CMD_SanGong.h"//add by Ivan_han
#define M_PI_4     0.785398163397448309616
#include <iostream>
using std::cin ;	// 污染小些

#include "resource.h"		// 资源

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

// 程序图标
void set_logo()
{
	HWND   hwnd=GetConsoleWindow();   
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
}

// 显示提示信息
void show_prompt_msg()
{
	const int X = 21;
	const int Y = 64;

	char szPrompt[X][Y];

	sprintf(szPrompt[0],  "?   提示 \n");
	sprintf(szPrompt[1], "CLS 清屏 \n");
	sprintf(szPrompt[2], "X   退出 \n");

	sprintf(szPrompt[3],  "T3 登录房间    \n");
	sprintf(szPrompt[4],  "T4 离开房间  \n");
	sprintf(szPrompt[5],  "T5 a 发送抢庄（0不抢，1或非0抢）消息 \n");
	sprintf(szPrompt[6],  "T6 举手 \n");
	sprintf(szPrompt[7],  "T7 离座 \n");

	sprintf(szPrompt[8],  "T8 a 发送下注（a∈{C1,C2,C3}）消息\n");

	sprintf(szPrompt[9],  "T9 结算时写分 \n");
	sprintf(szPrompt[10], "T10 申请房内的用户列表 \n");
	sprintf(szPrompt[11], "RTLIST 获取房间信息 \n");

	sprintf(szPrompt[12], "TKU a b 踢a桌b座的玩家离座  \n");
	sprintf(szPrompt[13], "TKT a   踢a桌的玩家离座 \n");
	sprintf(szPrompt[14], "TKA 踢所有在座的玩家离座  \n");

	sprintf(szPrompt[15], "TR1 a b  踢a桌b座的玩家离房  \n");
	sprintf(szPrompt[16], "TR3 a    踢a桌所有的玩家离房  \n");
	sprintf(szPrompt[17], "TR4      踢所有的玩家离房  \n");

	sprintf(szPrompt[18], "SM a     发送（a 取值 0比赛 1游戏任务 2道具） 消息  \n");

	sprintf(szPrompt[19],  "CR a 连接房间a\n");
	sprintf(szPrompt[20],  "SIT a b 入座a桌b座 \n");

	for(int i=0; i<X; i++)
	{
		printf(szPrompt[i]);
	}

	printf("\n");
}

#define USER_NUMBER 90	// 数据库中的测试用户数量



// 解析命令行
void parse_cmd(char* szSource, int iSourceLen, char* pszMain, char* pszParam01, char* pszParam02, char* pszParam03)
{
	char szUpper[STR_LEN] = {0};	// 转成大写的字串

	int iNo = 0;
	char* p = szSource;

	// 转成大写的字串
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
	::setlocale(LC_ALL,"");     // 让控制台输出 Unicode 的中文

	char szName[32];
	int iTable = 0;	// 桌号，测试用
	int iSeatNo;	// 座号，测试用



	// 程序图标
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
	char szInput[STR_LEN] = {0};	// 输入的字串

	while(cin.getline(szInput, STR_LEN))
	{
		memset(szMain , 0, sizeof(szMain));
		memset(szParam01 , 0, sizeof(szParam01));
		memset(szParam02 , 0, sizeof(szParam02));
		memset(szParam03 , 0, sizeof(szParam03));

		parse_cmd(szInput, lstrlenA(szInput), szMain, szParam01, szParam02, szParam03);
	
		if( 0 == strcmp("CLS", szMain ))	// 清屏
		{
			system("cls");
		}
		else if( 0 == strcmp("?", szMain))	// 快捷键提示
		{
			show_prompt_msg();
		}
		else if( 0 == strcmp("X", szMain))	// 正常退出
		{
			break;
		}
		else if( 0 == strcmp("T3", szMain))	// 登录房间
		{
			pClientLogic->login_room();
		}
		else if( 0 == strcmp("T4", szMain))	// 离开房间，相当于退出去了
		{
			pClientLogic->leave_room();
			//break;
		}
		else if( 0 == strcmp("T5", szMain))	// 抢庄
		{
			bool bCall=atoi(szParam01)!=0?true:false;
			Req_UserCallBanker req;
			req.llUserID=pClientLogic->m_MeUserInfo.lUserId;
			req.iSeatNo=pClientLogic->m_MeUserInfo.iSeatNo;
			req.bCall=bCall;
			pClientLogic->send_data(TABLE_MAIN,REQ_USER_CALL_BANKER,(BYTE*)(&req), sizeof(req));
		}
		else if( 0 == strcmp("T6", szMain))	// 能够开始游戏
		{
			pClientLogic->raise_hand();
		}
		else if( 0 == strcmp("T7", szMain))  // 离座
		{
			pClientLogic->leave_seat();
		}
		else if( 0 == strcmp("T8", szMain))	// 下注
		{
			TChip lScore=_atoi64(szParam01);
			Req_UserChipin req;
			req.llUserID=pClientLogic->m_MeUserInfo.lUserId;
			req.iSeatNo=pClientLogic->m_MeUserInfo.iSeatNo;
			req.lScore=lScore;
			pClientLogic->send_data(TABLE_MAIN, REQ_USER_CHIPIN, (BYTE*)(&req), sizeof(req));			
		}
		else if( 0 == strcmp("T9", szMain))	// 结算时写分
		{
			CMD_WRITE_SCORE score;
			score.lGold = 0;

			pClientLogic->write_score(score);
		}
		else if( 0 == strcmp("T10", szMain))	// 申请房内的用户列表
		{
			pClientLogic->query_user_list();
		}
		else if( 0 == strcmp("RTLIST", szMain))	// 获取房间信息
		{
			pClientLogic->send_data(ROOM_MAIN, ROOM_SUB_TABLE_LIST);
		}
		else if( 0 == strcmp("TKU", szMain))	// 踢一个玩家离座或离房
		{
			pClientLogic->tick_one_leave_seat(atoi(szParam01), atoi(szParam02));
		}
		else if( 0 == strcmp("TKT", szMain))	// 踢一桌玩家离座
		{
			pClientLogic->tick_table_leave_seat(atoi(szParam01));
		}
		else if( 0 == strcmp("TKA", szMain))	// 踢一桌玩家离座
		{
			pClientLogic->tick_all_leave_seat();
		}
		else if( 0 == strcmp("TR1", szMain))	// 
		{
			int iTableNo = atoi(szParam01);
			int iSeatNo = atoi(szParam02);
			pClientLogic->tick_user_out_room(iTableNo, iSeatNo);
		}
		else if(0 == strcmp("TR3", szMain))	// 踢a桌所有的玩家离房
		{
			int iTableNo = atoi(szParam01);
			pClientLogic->tick_user_out_room(iTableNo);
		}
		else if(0 == strcmp("TR4", szMain))	// 踢所有的玩家离房
		{
			pClientLogic->tick_user_out_room();
		}
		else if(0 == strcmp("CR", szMain))	// 连接房间a
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

	_tprintf_s(_T("按任意键结束....."));
	getchar();

	return 0;
}

