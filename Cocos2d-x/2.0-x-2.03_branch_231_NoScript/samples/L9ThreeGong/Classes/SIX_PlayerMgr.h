/*********************************************************
Name：SIX_PlayerMgr
Desc：玩家数据管理
Auth：Cool.Cat@2013-08-06
*********************************************************/
#pragma once
#include "SIX_Common.h"
#include <SIX_Typedef.h>
#include <SIX_TMap.h>

// 单个玩家
struct SinglePlayer
{
	SinglePlayer()
	{
		Init();
	}
	void Init()
	{
		memset(this, 0, sizeof(*this));
		byCallBanker=INVALID_BYTE;
	}
	// 基本数据
	int SeatId;
	int iTableId;
	TUserID	UserIdx;// 为0表示离开或椅子上没人
	long long	lGoldLogin;// 登录时的金币值
	long long	lPointLogin;// 登录时的积分
	long long  lSysLogoID;// 头像ID
	char		szName[USER_NAME_LEN];// 用户帐号即登录名称
	char		szNickname[USER_NAME_LEN];// 昵称
	// 打牌数据
	TChip	UserChipIn;	// 下注信息
	TCardData UserCardData[3];// 扑克数据
	TCardType CardType;
	TCardPoint CardPoint;
	bool bRaiseHand;// 举手标志
	bool bSendFinish;// 搓牌完毕标志
	unsigned char byCallBanker;// 抢庄标志={255,0,1}
};

typedef struct tagCustomWinInfo {
	int ViewID;
	bool bBanker;
	TUserID UserID;
	// 税收
	TChip lGameTax;
	// 筹码增量
	TChip ChipCount;
	// 牌型
	TCardType CardType;
	// 牌点
	TCardPoint CardPoint;
	tagCustomWinInfo()
	{
		ViewID = 0;
		bBanker = false;
		UserID = 0;
		lGameTax = 0;
		ChipCount = 0;
		CardType = 0;
		CardPoint = 0;
	}
} CUSTOM_INFO;

class SIX_PlayerMgr:public TSingleton<SIX_PlayerMgr>,public SIX_TMap<long long,USER_INFO_SIM*>
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

	void setMyNickName(char *name)
	{
		memcpy(m_MyNickName,name,32);
	}

	char *getMyName(){return m_MyName;}
	char *getMyPass(){return m_MyPass;}
	char *getMyNickName(){return m_MyNickName[0]==0 ? m_MyName : m_MyNickName;}

	void setMyUserIdx(long long idx){m_MyUserIdx = idx;}
	long long getMyUserIdx(){return m_MyUserIdx;}

	void setMyLogoID(long long llLogoID){m_MyLogoID = llLogoID;}
	long long getMyLogoID(){return m_MyLogoID;}

	void setMyChip(TChip Chip){m_MyChip = Chip;}
	TChip getMyChip(){return m_MyChip;}

	void setMyLevel(int Level){m_MyLevel = Level;}
	int getMyLevel(){return m_MyLevel;}

	void setMyTableIdx(long long idx){m_MyTableIdx = idx;}
	long long getMyTableIdx(){return m_MyTableIdx;}

	void setMySeatIdx(long long idx){m_MySeatIdx = idx;}
	long long getMySeatIdx(){return m_MySeatIdx;}

	void setMyUserIdentity(long long UserIdentity_){m_MyUserIdentity = UserIdentity_;}
	bool IsSanXianIdentity()const{return m_MyUserIdentity==US_IDENTITY_HIGH_PLAYER;}

	//add by Ivan_han 20131013
	// 获取别人在自己客户端中的视图ID
	static int getViewID(int CurLogicID, int MyLogicID);
	// 获取自己客户端中视图ID对应的逻辑ID
	static int getLogicID(int CurViewID, int MyLogicID);

	// 获取庄家视图ID
	int getBankerViewID();

	// 获取庄家数据指针
	CUSTOM_INFO *getBankerInfo()
	{
		for (unsigned int i=0;i<mCustomWin.GetCount();i++)
		{
			CUSTOM_INFO *pCustomInfo = mCustomWin.Get(i);
			if (pCustomInfo->bBanker)
				return pCustomInfo;
		}
		return 0;
	}

	void clearPlayers();

	void setLastRecvSitDownTime(unsigned long long time){m_LastRecvSitDownTime=time;}
	unsigned long long getLastRecvSitDownTime(){return m_LastRecvSitDownTime;}

	void setAllowChangeToHall(bool bAllowChange){m_bAllowChangeToHall=bAllowChange;}
	bool getAllowChangeToHall(){return m_bAllowChangeToHall;}

public:
	// 桌内玩家数据
	SinglePlayer m_Players[GAME_PLAYER_COUNT];
	// 一局游戏中的庄家用户
	TChairID m_wBankerChairID;
	// 下注筹码数目(C3>C2>C1)，按钮上显示
	TChip m_C3;
	TChip m_C2;
	TChip m_C1;
	// 闲家赢集合
	SIX_TVector<CUSTOM_INFO*> mCustomWin;
private:
	static SIX_PlayerMgr *m_gPlayerMgr;
	// 玩家自己数据
	long long m_MyUserIdx;
	long long m_MyLogoID;
	char m_MyName[33];
	char m_MyPass[33];
	char m_MyNickName[33];
	int m_MyLevel;
	TChip m_MyChip;
	int m_MyTableIdx;
	int m_MySeatIdx;
	long long m_MyUserIdentity;
	// 上次接收坐下包信息的时间
	unsigned long long m_LastRecvSitDownTime;
	// 是否允许切换到大厅场景
	bool m_bAllowChangeToHall;
};