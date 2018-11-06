// FishClient.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"

#include "./PublicHead.h"
#include "ClientLogic.h"

#include "../GameMsg/ProFish.h"//add by Ivan_han
#define M_PI_4     0.785398163397448309616
#include <iostream>
using std::cin ;	// 污染小些

#include "resource.h"		// 资源

#include "Often.h"
#pragma comment(lib,"ws2_32.lib")

#define STR_LEN 32

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
	sprintf(szPrompt[5],  "T5 入座 \n");
	sprintf(szPrompt[6],  "T6 举手 \n");
	sprintf(szPrompt[7],  "T7 离座 \n");

	sprintf(szPrompt[8],  "T8 开火 \n");

	sprintf(szPrompt[9],  "T9 结算时写分 \n");
	sprintf(szPrompt[10], "T10 申请房内的用户列表 \n");
	sprintf(szPrompt[11], "T11 密集开火，主要测用户锁 \n");

	sprintf(szPrompt[12], "TKU a b 踢a桌b座的玩家离座  \n");
	sprintf(szPrompt[13], "TKT a   踢a桌的玩家离座 \n");
	sprintf(szPrompt[14], "TKA 踢所有在座的玩家离座  \n");

	sprintf(szPrompt[15], "TR1 a b  踢a桌b座的玩家离房  \n");
	sprintf(szPrompt[16], "TR3 a    踢a桌所有的玩家离房  \n");
	sprintf(szPrompt[17], "TR4      踢所有的玩家离房  \n");

	sprintf(szPrompt[18], "SM a     发送（a 取值 0比赛 1游戏任务 2道具） 消息  \n");

	sprintf(szPrompt[19],  "FIRE 开火 \n");//add by Ivan_han
	sprintf(szPrompt[20],  "SIT a b 入座a桌b座 \n");//add by Ivan_han

	for(int i=0; i<X; i++)
	{
		printf(szPrompt[i]);
	}

	printf("\n");
}

#define USER_NUMBER 90	// 数据库中的测试用户数量

// 获得客户端配置信息，主要用于调试，目的是调试时自动启用不同的用户名
void get_client_config(char* pszName, int& iSeatNo)
{
	char szTmp[32];
	string strPath, strPathFile;
	COften::get_current_path(strPath);

	strPathFile = strPath + "FishClientConfig.ini";

	UINT iChangeNameNo = GetPrivateProfileIntA("NAME_NO", "ChangeNameNo", 1, strPathFile.c_str());	// 从配置文件中读取

	UINT iNameNo = GetPrivateProfileIntA("NAME_NO", "NameNo", 0, strPathFile.c_str());	// 从配置文件中读取
	printf("iNameNo=%d \n",iNameNo);

	int iUserNo = iNameNo%USER_NUMBER;
	iSeatNo = iUserNo%4;

	switch(iUserNo)
	{
	case 0:
		sprintf(pszName, "懂毛");
		break;
	case 1:
		sprintf(pszName, "孙一");
		break;
	case 2:
		sprintf(pszName, "杨二");
		break;
	case 3:
		sprintf(pszName, "张三");
		break;
	case 4:
		sprintf(pszName, "李四");
		break;
	case 5:
		sprintf(pszName, "王五");
		break;
	case 6:
		sprintf(pszName, "赵六");
		break;
	case 7:
		sprintf(pszName, "孙七");
		break;
	case 8:
		sprintf(pszName, "金八");
		break;
	case 9:
		sprintf(pszName, "钱九");
		break;
	default:
		sprintf(pszName, "T%2d", iUserNo);
		break;
	}

	if(iChangeNameNo>0)
	{
		_snprintf(szTmp, sizeof(szTmp)-1, "%d", iNameNo+1);
		WritePrivateProfileStringA("NAME_NO", "NameNo", szTmp, strPathFile.c_str());	// 写入配置文件
	}

	int iTmp = 0;
}

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

	// 获得客户端配置信息，主要用于调试，目的是调试时自动启用不同的用户名
	get_client_config(szName, iSeatNo);

	// 程序图标
	set_logo();
	show_prompt_msg();

	CClientLogic* pClientLogic = new CClientLogic;
	assert(pClientLogic);

	int iRes = 0;
	

	// 桌子的框架参数，构造函数里有默认值
	CLIENT_FRAME_PARAM frameParam;	
	frameParam.iSendHeartbeatTime = 5*60*1000;	// 测试用，不让它频繁的出现干扰调试

	// 客户端的房间信息，应该从命令行传入的或者是管道从大厅程序中传入的，还未做???
	CLIENT_ROOM_INFO clientRoomInfo;

	int iType = 0;
	if(0==iType)
		_snprintf(clientRoomInfo.szIP, sizeof(clientRoomInfo.szIP)-1, "127.0.0.1");		// 本地房间IP
	else if(1==iType)
		_snprintf(clientRoomInfo.szIP, sizeof(clientRoomInfo.szIP)-1, "192.168.1.99");		// 内网99服房间IP
	else if(2==iType)
		_snprintf(clientRoomInfo.szIP, sizeof(clientRoomInfo.szIP)-1, "112.124.39.86");		// 外网的房间IP

	clientRoomInfo.iPort = 7000;													// 房间端口

	//_snprintf(clientRoomInfo.szName, sizeof(clientRoomInfo.szName)-1, szName);		// 用户名
	strcpy(clientRoomInfo.szName,"T9");
	#if 1
		_snprintf(clientRoomInfo.szPassword, sizeof(clientRoomInfo.szPassword)-1, "202cb962ac59075b964b07152d234b70");	// 密码
	#else
		_snprintf(clientRoomInfo.szPassword, sizeof(clientRoomInfo.szPassword)-1, "123ttt");	// 密码，故意错误，测试用
	#endif

    pClientLogic->setUserID(9);
	
	iRes = pClientLogic->init(clientRoomInfo, frameParam);
	iRes = pClientLogic->start();

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
			break;
		}
		else if( 0 == strcmp("T5", szMain))	// 入座
		{
			int iTableNumInRoom = 2;	// 房间中的桌子数量
			srand( (unsigned)time( NULL ) );
			iTable = rand()%iTableNumInRoom;
			pClientLogic->sit_down(iTable, iSeatNo);
		}
		else if( 0 == strcmp("T6", szMain))	// 能够开始游戏
		{
			pClientLogic->raise_hand();
		}
		else if( 0 == strcmp("T7", szMain))  // 离座
		{
			pClientLogic->leave_seat();
		}
		else if( 0 == strcmp("T8", szMain))	// 开火
		{
			pClientLogic->fire();
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
		else if( 0 == strcmp("T11", szMain))	// 密集开火，主要测用户锁
		{
			// 密集开火
			for(int i=0; i<20; i++)
			{
				pClientLogic->fire();
				//Sleep(100);
			}
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
		else if(0 == strcmp("SM", szMain))	// 发送测试消息
		{
			int iType = atoi(szParam01);
			pClientLogic->send_test_msg(iType);	
		}

		////add by Ivan_han
		//else if( 0 == strcmp("FIRE", szMain))	// 开火
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

	_tprintf_s(_T("按任意键结束....."));
	getchar();

	return 0;
}

