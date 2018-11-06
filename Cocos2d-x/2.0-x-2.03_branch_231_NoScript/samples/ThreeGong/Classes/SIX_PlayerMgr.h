/*********************************************************
Name��SIX_PlayerMgr
Desc��������ݹ���
Auth��Cool.Cat@2013-08-06
*********************************************************/
#pragma once
#include "SIX_Common.h"
#include <SIX_Typedef.h>
#include <SIX_TMap.h>

// �������
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
	// ��������
	int SeatId;
	int iTableId;
	TUserID	UserIdx;// Ϊ0��ʾ�뿪��������û��
	long long	lGoldLogin;// ��¼ʱ�Ľ��ֵ
	long long	lPointLogin;// ��¼ʱ�Ļ���
	long long  lSysLogoID;// ͷ��ID
	char		szName[USER_NAME_LEN];// �û��ʺż���¼����
	char		szNickname[USER_NAME_LEN];// �ǳ�
	// ��������
	TChip	UserChipIn;	// ��ע��Ϣ
	TCardData UserCardData[3];// �˿�����
	TCardType CardType;
	TCardPoint CardPoint;
	bool bRaiseHand;// ���ֱ�־
	bool bSendFinish;// ������ϱ�־
	unsigned char byCallBanker;// ��ׯ��־={255,0,1}
};

typedef struct tagCustomWinInfo {
	int ViewID;
	bool bBanker;
	TUserID UserID;
	// ˰��
	TChip lGameTax;
	// ��������
	TChip ChipCount;
	// ����
	TCardType CardType;
	// �Ƶ�
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
	// ��ȡ�������Լ��ͻ����е���ͼID
	static int getViewID(int CurLogicID, int MyLogicID);
	// ��ȡ�Լ��ͻ�������ͼID��Ӧ���߼�ID
	static int getLogicID(int CurViewID, int MyLogicID);

	// ��ȡׯ����ͼID
	int getBankerViewID();

	// ��ȡׯ������ָ��
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
	// �����������
	SinglePlayer m_Players[GAME_PLAYER_COUNT];
	// һ����Ϸ�е�ׯ���û�
	TChairID m_wBankerChairID;
	// ��ע������Ŀ(C3>C2>C1)����ť����ʾ
	TChip m_C3;
	TChip m_C2;
	TChip m_C1;
	// �м�Ӯ����
	SIX_TVector<CUSTOM_INFO*> mCustomWin;
private:
	static SIX_PlayerMgr *m_gPlayerMgr;
	// ����Լ�����
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
	// �ϴν������°���Ϣ��ʱ��
	unsigned long long m_LastRecvSitDownTime;
	// �Ƿ������л�����������
	bool m_bAllowChangeToHall;
};