/*********************************************************
Name：Ship
Desc：船实体管理器
Auth：lijianming
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
	// 17种鱼+龙虾炸弹+金龙炸弹
	unsigned int m_FishCount[StatFishCount];

	long long	m_lGameType;					// 游戏类型: 1=积分房间、2=金币游戏、3=比赛游戏、4=测试类游戏。
	int			m_iBasePoint;					// 倍率，10倍区、50倍区、100倍区
};

USING_NS_CC;

typedef struct tagGunDataInfo
{
	int m_gunOffestY;						///< 炮Y轴相对船偏移 19 像素
	TGunGrade m_curGunType;					///< 当前炮类型
	bool m_completeWhirlGun;		///< 旋转炮完成
	TPoint m_unfinishedPT;			///< 旋转过程中未处理的坐标
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

/// 船（玩家）类
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

	void setNetGapTime(long long iNetGapTIme){m_iNetGapTime = iNetGapTIme;};	// 设置网络间隔时间			// add by cxf
	long long getNetGapTime(){return m_iNetGapTime;};							// 获取网络间隔时间			// add by cxf
	void setLastPingTime(long long t){m_lLastPingTime = t;}				// 设置上次发送ping包时间
	long long getLastPingTime(){return m_lLastPingTime;}				// 获取上次发送ping包时间

#ifdef WIN32
	void AccelerometerKeyHook(unsigned int MSG,unsigned int wParam,long long lParam);
#endif

	void onCallFucRepeatShootBullet();
	void onWhirlGunComplete(CCNode *gun);

	// 炮管类型
	// 等级对应类型：(1~5级) 对应 类型1；(6~10级) 对应 类型2；(11~15级) 对应 类型3；(16~20级) 对应 类型4
	int GetGunType();
	void SetGunImg();
	// 加减倍率
	// Cool.Cat
	void IncBet();
	void DecBet();
	virtual void doEvents(CCObject* pSender, CCControlEvent event);
	virtual void update(float dt);

	void ShowHereTips(bool IsShow=true);

public:
	long long m_UserID;											///< 玩家ID
	int m_seatIndex;												///< 游戏场景内座位的相对椅子号
	int m_seatAbsoluteIndex;									///< 房间内座位的绝对椅子号
	int mBulletSpeed;												///< 打出的子弹速度
	int mBulletType;												///< 子弹类型
	CCSize mNetSize;												///< 鱼网大小
	unsigned long m_ulRepeatShoottartTime;			///< 连续发射开始时间
	long long m_ullastShootTime;								///< 上次子弹发射时间

	CCSprite *m_shipSprite;
	CCSprite *m_gunSprite;
	CCSprite *m_TreasureSprite;//add by Ivan_han 20130705
	CCLabelTTF *m_pGunGrade;//add by Ivan_han 20130723
	CCSprite *m_ping;
	GUN_DATA *m_gun;

private:
	long long  m_iNetGapTime;									// 网络间隔时间			add by cxf
	long long  m_lLastPingTime;							//  上次ping请求事件
};

/// 船（玩家）管理类
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
	//获取别人在自己客户端中的视图ID
	int getViewID(int CurLogicID, int MyLogicID, int MyViewID);
	void AdjustmentPos(long long llUserID, CCPoint &pt);
	void AdjustmentPos(long long llUserID, qcPoint &pt);

	//add by Ivan_han 20130816
	void onShootBullet(long long UserID, TBulletID llID, CCPoint TouchPT, bool RepeatShoot, bool bSetTouchPT/*=false*/ );

	//add by Ivan_han 20130529
	/*
		逻辑ID唯一决定视图ID（{左下方=3、右下方=2}），视图ID不再从{左下方=3、右下方=2}中随机选择；
		服务器端矩形<->客户端矩形的坐标映射要满足内点<->内点、外点<->外点、边界点<->边界点；
		矩形不能旋转90°和270°，只能旋转0°和180°。
	*/
	int getViewID(int LogicID,bool *IsNeedTransform);					/// 根据逻辑ID获取客户端的视图ID以及决定是否进行坐标变换
	CCPoint SP2CP(const CCPoint& SP);											///< 收包时坐标转换
	CCPoint CP2SP(const CCPoint& CP);											///< 发包时坐标转换
	CCPoint SD2CD(const CCPoint& SD);											///< 收包时方向转换
	CCPoint CD2SD(const CCPoint& CD);											///< 发包时方向转换
	float SD2CD(float SD);											///< 收包时方向转换
	float CD2SD(float CD);											///< 发包时方向转换
	//add by Ivan_han 20130617
	static float ScaleXTrans(int W,int W1,float x);
	static float ScaleXTrans(float ScaleX,float x);
	static CCPoint ScaleTrans(int W,int H,int W1,int H1,const CCPoint& p);
	static CCPoint ScaleTrans(float ScaleX,float ScaleY,const CCPoint& p);

	CCPoint mTouchPT;																	///< 鼠标位置(实时)
	CShip * mShipData[MAX_PLAYER];
	//vector<PLAYER_LIST*> mPlayerList;											///< 玩家列表
	bool mIsNeedTransform;															///比例变换是一定需要的，true表示需要旋转变换和平移变换，false表示不需要<del: false:SP=CP,true:SP≠CP //add by Ivan_han 20130529
};

extern CShipMgr * g_pShipMgr;