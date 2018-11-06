
#ifndef FISH_TABLE_H
#define FISH_TABLE_H

#include "./ThreadGuard.h"

#include "./GameSkeletonID.h"
#include "./TaskMsgResult.h"
#include "./IBaseTable.h"
#include "../GameMsg/ProFish.h"//add by Ivan_han

#include "FishTraceMgr.h"
#include "BulletMgr.h"
#include "AwardPool.h"//add by Ivan_han

enum ENUM_GAME_PHASE
{
	ENUM_GAME_START,
	ENUM_GAME_END,
};

#define M_PI       3.14159265358979323846

#define USESLEEP 0	// 1 表示模拟外网环境测试时间同步，0 表示走正常流程

//add by Ivan_han 20130624
//////////////////////////////////////////////////////////////////////////
#define VIEW_WIDTH  1280
#define VIEW_HEIGHT  733

#define IDI_BUILD_TRACE				1									//捕渔期产生单鱼或鱼群轨迹
#define IDI_CLEAR_TRACE				2									//销毁轨迹
#define IDI_CHANGE_SCENE			3									//切换场景
#define IDI_REGULAR_FISH			4									//休渔期产生鱼阵轨迹
#define IDI_BONUS					5									//递增彩金
#define IDI_SYS_MESSAGE				6									//系统消息
//#define IDI_REGULAR_READY			7									//鱼阵准备
//#define IDI_REGULAR_END			    8									//鱼阵结束
#define IDI_STATUS                  9                                   //检测状态
#define IDI_Adjust_Vh              10                                   //检测奖池状态，调整上水位标，add by Ivan_han 20130730
#define IDI_Adjust_Vl               11                                   //检测奖池状态，调整下水位标，add by Ivan_han 20130730
#define IDI_AWARD_POOL_SAVE         12                                   //奖池存盘
#define IDI_TestCommonPool              13                                   //体验普通池检测状态
#define IDI_TestBonusPool               14                                  //体验彩金池检测状态
#define IDI_FIRE_OVERTIME			15									// 开火超时 add by cxf
#define IDI_GAME_END_TIMER			16									// 结束游戏定时器
#define IDI_BULLET_OVERTIME			17									// 子弹超时

#define TIMES_INFINITY     DWORD (-1)

#define TIME_BUILD_TRACE			2000								//捕渔期产生单鱼或鱼群轨迹
#define TIME_CLEAR_TRACE			10000								//销毁轨迹
#define TIME_CHANGE_SCENE			30000								//切换场景
#define TIME_CAPTURE		        120000				                //捕渔期持续时间
#define TIME_OFF		            60000					            //休渔期持续时间

//#define TIME_REGULAR_READY			10000								//10秒钟准备
#define TIME_REGULAR_FISH			10000							    //休渔期产生鱼阵轨迹
//#define TIME_REGULAR_END			20000								//20秒后规则鱼群结束
#define TIME_SYS_MESSAGE			5*60								//系统消息
#define TIME_FIRE_OVERTIME			(10000)								// 开火超时时间
#define TIME_BULLET_OVERTIME		(10000)								// 检查子弹超时间隔

#define FISH_ALIVE_TIME				20							//存活时间

#define MAX_FLOAT_NUM              4                                  //炮浮动击攻力倍数

#define FIER_OVERTIME_WARNING_TIME	40									// 开火超时提示
#define FIER_OVERTIME_TIME			60									// 开火超时时间
#define FIER_BULLET_OVERTIME		15									// 子弹存活时间
//////////////////////////////////////////////////////////////////////////

class IRoomMgr;

class CFishTable : public IBaseTable
{
public:
	CFishTable(void);
	~CFishTable(void);

public:
	// 初始化
	void OnInit();
	// 初始化比赛数据
	void OnSitDownInit(int iSeatNo);
	// 响应桌子消息
	void OnTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen);

public:
	//--- 要从父类继承的纯虚函数 --------------------------------

	// 断线
	virtual int OnCut(LONGLONG lUserId);

	// 断线重入响应，仅仅在用用户名、密码登录房间时才会响应
	virtual int OnRecomeAfterCut(int iSeatNo);

	// 桌子定时器响应
	virtual int OnTableTimer(int iTableNo, int iIDEvent);

	//游戏开始
	virtual int OnGameBegin();

	// 举手
	virtual int OnRaiseHand(int iSeatNo);

	//游戏结束
	virtual int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag);

	// 离座之前
	virtual int OnLeaveSeatBefore(LONGLONG lUserId, int iSeatNo);

	// 离座之后
	virtual int OnLeaveSeatLast(int iSeatNo);

	// 收取台费 和赠送子弹
	virtual void TradeFee();

	// 结算
	virtual int OnAccounts(int iSeatNo);

	// 用户坐下
	virtual void OnUserSitDown(int iSeatNo);

	//服务器端发送网络包时不再调用::GetTickCount64()，add by Ivan_han 20130627
	static unsigned long long GetTickCount64();

public:

	// 开火
	int fire(int iSeatNo, SHOT_FIRE* pReal);
	/// 子弹反射
	int BulletReflection(int iSeatNo, BULLET_REFLECTION* pReal);
	/// 捕获鱼
	int CaptureFish(int iSeatNo, CAPTURE_FISH* pReal);
		
	TBulletID getNewBulletID();
	CFishTraceMgr& getFishTraceMgr();

	// 根据鱼号/龙虾炸弹号查找对应的数组索引
	static int GetIndexFromArray(TFishKind fishType);

private:
	int Check(SEAT_INFO** pSeatInfo, int iSeatNo);

private:
	// 设置炮的等级
	void UserSetGunGrade(int iSeatNo,Req_SetGunGrade * pReq);
	// 购买子弹
	void UserBuyBullet(int iSeatNo, USER_BUY_BULLET * userBuyBullet);
	// 删除所有定时器
	void KillAllTimer();
	// 检查超时退出桌子
	void OnCheckOverTime();
	// 比赛结束
	void OnMatchEnd();
	// 检查用户子弹
	bool OnCheckAllUserBullet();
	// 排序
	void SortMatch(CMD_GameUserInfo matchInfo[]);

protected:
	CFishTraceMgr	m_stFishTraceMgr;	// 鱼轨迹管理类
	CBulletMgr		m_stBulletMgr;		// 子弹管理
	CAwardPool      m_stAwardPool;      //奖池对象

private:
	// 比赛用户信息
	CMD_GameUserInfo m_gameUserInfo[GAME_PLAYER_COUNT];
	// 比赛剩余时间
	int m_iMatchCountDown;
	// 游戏阶段
	ENUM_GAME_PHASE m_eGamePhase;		//比赛游戏状态

};

#endif