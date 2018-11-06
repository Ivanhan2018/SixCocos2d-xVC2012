/***********************************************
Name：SIX_ConsoleGM
Desc：关卡场景GM命令行操作窗口
Auth：Ivan_han@2013-09-03
***********************************************/
#pragma once
#include "SIX_Console.h"

class SIX_ConsoleGM:public SIX_Console
{
public:
	SIX_ConsoleGM();
	virtual ~SIX_ConsoleGM();
public:
	static SIX_ConsoleGM *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
public:
	virtual void OnInputDone(CCLayer *pLayer,const char *text);
public:
	void OnProcessCommand(const char *cmd);
	void ON_ROOM_SUB_USER_LIST(long long lUserId,const char *szName,const char *szNickname,int stUserState,int iTableNo,int iSeatNo,long long lGoldLogin,long long lPointLogin);
};