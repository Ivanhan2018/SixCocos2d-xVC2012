/*********************************************************
Name：SIX_PlayerMgr
Desc：玩家数据管理
Auth：Cool.Cat@2013-08-06
*********************************************************/
#pragma once

#include <SIX_Typedef.h>
#include <SIX_TMap.h>
#include "Ship.h"

/// 玩家列表
typedef struct tagPLAYER_LIST
{
	tagPLAYER_LIST()
	{
		memset(this, 0, sizeof(*this));
	}
	int SeatId;
	int iTableId;
	long long UserIdx;
	//add by Ivan_han 20130713
	long long	lGoldLogin;		// 登录时的金币值
	long long	lPointLogin;	// 登录时的积分
	char		szName[USER_NAME_LEN];			// 用户帐号即登录名称
	char		szNickname[USER_NAME_LEN];		// 昵称
}PLAYER_LIST;

class SIX_PlayerMgr:public TSingleton<SIX_PlayerMgr>,public SIX_TMap<long long,PLAYER_LIST*>
{
public:
	SIX_PlayerMgr();
	virtual ~SIX_PlayerMgr();
	static SIX_PlayerMgr *GetInstance() 
	{
		if (!m_gPlayerMgr)
			m_gPlayerMgr = new SIX_PlayerMgr();
		return m_gPlayerMgr;
	}
	void Release()
	{
		//if (!m_gPlayerMgr)
		//	return;
		//CC_SAFE_DELETE(m_gPlayerMgr);
	}
public:
	void setMyUserInfo(char *name,char *pass)
	{
		memcpy(m_MyName,name,32);
		memcpy(m_MyPass,pass,32);
	}

	char *getMyName(){return m_MyName;}
	char *getMyPass(){return m_MyPass;}
	
	void setMyUserIdx(long long idx){m_MyUserIdx = idx;}
	long long getMyUserIdx(){return m_MyUserIdx;}

	void setMyTableIdx(long long idx){m_MyTableIdx = idx;}
	long long getMyTableIdx(){return m_MyTableIdx;}

	void setMySeatIdx(long long idx){m_MySeatIdx = idx;}
	long long getMySeatIdx(){return m_MySeatIdx;}

	PLAYER_LIST *getSelfPlayer();

	void Enter(CCLayerColor *background);
	void LeaveSeat(long long,int,int);
private:
	void OnDelegateDestory(PLAYER_LIST*);
private:
	static SIX_PlayerMgr *m_gPlayerMgr;
	long long m_MyUserIdx;
	char m_MyName[33];
	char m_MyPass[33];
	int m_MyTableIdx;
	int m_MySeatIdx;
};