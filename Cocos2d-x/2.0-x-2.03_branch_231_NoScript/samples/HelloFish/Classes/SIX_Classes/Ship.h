/*********************************************************
Name��Ship
Desc����ʵ�������
Auth��lijianming
*********************************************************/
#pragma once
#include "cocos2d.h"
#include "SIX_Common.h"
#include <SIX_Typedef.h>
#include <SIX_NumberBatchNode.h>
#include "SIX_PlayerMgr.h"
#include "SIX_RoomMgr.h"

//add by Ivan_han 20130716
class PlayerTreasureInfo
{
public:
	enum emFishCount{StatFishCount=19};
	PlayerTreasureInfo();
	PlayerTreasureInfo(PlayerTreasureInfo &p);
	static PlayerTreasureInfo & Instance();
	static TFishMulti getFishMulti(TFishKind fishType);
	void UpdateFishKindNums(unsigned int FishCount[StatFishCount]);
	void ResetFishKindNums();
public:
	// 17����+��Ϻը��+����ը��
	unsigned int m_FishCount[StatFishCount];

	long long	m_lGameType;					// ��Ϸ����: 1=���ַ��䡢2=�����Ϸ��3=������Ϸ��4=��������Ϸ��
	int			m_iBasePoint;					// ���ʣ�10������50������100����
};

USING_NS_CC;

typedef struct tagGunDataInfo
{
	int m_gunOffestY;						///< ��Y����Դ�ƫ�� 19 ����
	TGunGrade m_curGunType;					///< ��ǰ������
	bool m_completeWhirlGun;		///< ��ת�����
	TPoint m_unfinishedPT;			///< ��ת������δ���������
	tagGunDataInfo()
	{
		m_gunOffestY = 0;
		m_curGunType = 1;
		m_completeWhirlGun = true;
		m_unfinishedPT = TPoint(0,0);
	}
}GUN_DATA;

typedef enum {
	BTN_DEC = 100,
	BTN_INC = 200,
} SHIP_BTN_TYPE;

/// ������ң���
class CShip : public CCNode
{
public:
	CShip();
	~CShip();
	void Init();
public:
	void setNetType(int NetType);
	void onWhirlGun(CCPoint TouchPT, bool bAnimation=true);
	void onWhirlGun(bool bLeft, bool bContinuous);
	CCPoint getGunPos();
	void setVisible(bool bVisible);

	//add by Ivan_han 20130710
	unsigned long long getFishCoin()const;
	void setFishCoin(unsigned long long	lFishCoin);
	unsigned long long getBulletCount()const;
	void setBulletCount(unsigned long long	lBulletCount);
	unsigned long long getGoldCoin(int tag=3)const;
	void setGoldCoin(unsigned long long	lGoldCoin,int tag=3,bool doAnimate=true);
	//add by Ivan_han 20130723
	TGunGrade getGunGrade()const;
	void setGunGrade(TGunGrade GunGrade);
	void SetName(const char *pName);

	void setNetGapTime(long long iNetGapTIme){m_iNetGapTime = iNetGapTIme;};	// ����������ʱ��			// add by cxf
	long long getNetGapTime(){return m_iNetGapTime;};							// ��ȡ������ʱ��			// add by cxf
	void setLastPingTime(long long t){m_lLastPingTime = t;}				// �����ϴη���ping��ʱ��
	long long getLastPingTime(){return m_lLastPingTime;}				// ��ȡ�ϴη���ping��ʱ��

#ifdef WIN32
	void AccelerometerKeyHook(unsigned int MSG,unsigned int wParam,long long lParam);
#endif

	void onCallFucRepeatShootBullet();
	void onWhirlGunComplete(CCNode *gun);

	// �ڹ�����
	// �ȼ���Ӧ���ͣ�(1~5��) ��Ӧ ����1��(6~10��) ��Ӧ ����2��(11~15��) ��Ӧ ����3��(16~20��) ��Ӧ ����4
	int GetGunType();
	void SetGunImg();
	// �Ӽ�����
	// Cool.Cat
	void IncBet();
	void DecBet();
	virtual void doEvents(CCObject* pSender, CCControlEvent event);
	virtual void update(float dt);

	void ShowHereTips(bool IsShow=true);

public:
	long long m_UserID;											///< ���ID
	int m_seatIndex;												///< ��Ϸ��������λ��������Ӻ�
	int m_seatAbsoluteIndex;									///< ��������λ�ľ������Ӻ�
	int mBulletSpeed;												///< ������ӵ��ٶ�
	int mBulletType;												///< �ӵ�����
	CCSize mNetSize;												///< ������С
	unsigned long m_ulRepeatShoottartTime;			///< �������俪ʼʱ��
	long long m_ullastShootTime;								///< �ϴ��ӵ�����ʱ��

	CCSprite *m_shipSprite;
	CCSprite *m_gunSprite;
	CCSprite *m_TreasureSprite;//add by Ivan_han 20130705
	CCLabelTTF *m_pGunGrade;//add by Ivan_han 20130723
	CCSprite *m_ping;
	GUN_DATA *m_gun;

private:
	long long  m_iNetGapTime;									// ������ʱ��			add by cxf
	long long  m_lLastPingTime;							//  �ϴ�ping�����¼�
};

/// ������ң�������
class CShipMgr : public TSingleton<CShipMgr>
{
public:
	CShipMgr();

	void Enter(CCNode *Parent, long long UserID, int seatAbsoluteIndex, bool isMyself=true);
	void Leave( long long UserID );
	void Release();

	CShip *getShip(long long UserID);
	CShip *getMySelfShip();
	
	void onUpdateMousePT(CCPoint pt);
	void ResetPlayer();
	int getPlayerDirection(long long UserID);
	//��ȡ�������Լ��ͻ����е���ͼID
	int getViewID(int CurLogicID, int MyLogicID, int MyViewID);
	void AdjustmentPos(long long llUserID, CCPoint &pt);
	void AdjustmentPos(long long llUserID, qcPoint &pt);

	//add by Ivan_han 20130816
	void onShootBullet(long long UserID, TBulletID llID, CCPoint TouchPT, bool RepeatShoot, bool bSetTouchPT/*=false*/ );

	//add by Ivan_han 20130529
	/*
		�߼�IDΨһ������ͼID��{���·�=3�����·�=2}������ͼID���ٴ�{���·�=3�����·�=2}�����ѡ��
		�������˾���<->�ͻ��˾��ε�����ӳ��Ҫ�����ڵ�<->�ڵ㡢���<->��㡢�߽��<->�߽�㣻
		���β�����ת90���270�㣬ֻ����ת0���180�㡣
	*/
	int getViewID(int LogicID,bool *IsNeedTransform);					/// �����߼�ID��ȡ�ͻ��˵���ͼID�Լ������Ƿ��������任
	CCPoint SP2CP(const CCPoint& SP);											///< �հ�ʱ����ת��
	CCPoint CP2SP(const CCPoint& CP);											///< ����ʱ����ת��
	CCPoint SD2CD(const CCPoint& SD);											///< �հ�ʱ����ת��
	CCPoint CD2SD(const CCPoint& CD);											///< ����ʱ����ת��
	float SD2CD(float SD);											///< �հ�ʱ����ת��
	float CD2SD(float CD);											///< ����ʱ����ת��
	//add by Ivan_han 20130617
	static float ScaleXTrans(int W,int W1,float x);
	static float ScaleXTrans(float ScaleX,float x);
	static CCPoint ScaleTrans(int W,int H,int W1,int H1,const CCPoint& p);
	static CCPoint ScaleTrans(float ScaleX,float ScaleY,const CCPoint& p);

	CCPoint mTouchPT;																	///< ���λ��(ʵʱ)
	CShip * mShipData[MAX_PLAYER];
	//vector<PLAYER_LIST*> mPlayerList;											///< ����б�
	bool mIsNeedTransform;															///�����任��һ����Ҫ�ģ�true��ʾ��Ҫ��ת�任��ƽ�Ʊ任��false��ʾ����Ҫ<del: false:SP=CP,true:SP��CP //add by Ivan_han 20130529
};

extern CShipMgr * g_pShipMgr;