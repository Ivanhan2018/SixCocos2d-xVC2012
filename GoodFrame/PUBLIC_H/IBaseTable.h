
/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\IBaseTable.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	IBaseTable
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef I_BASE_TABLE_H
#define I_BASE_TABLE_H

#include <vector>
using std::vector;

#include "TaskMsgResult.h"
#include "SingleUser.h"
#include "TableInfo.h"
#include "ThreadGuardEx.h"
#include "MemBlockPool.h"
#include "RoomInfo.h"
#include "GameTaskList.h"

#include ".\EndlessLoopGuard.h"

enum TASK_MSG_RESULT;	// 任务消息结果
class CMemBlock;
class IRoomMgr;

// 桌子
class __declspec(dllexport) IBaseTable
{
public:
	IBaseTable(void);
	~IBaseTable(void);

public:
	// 桌子消息
	virtual void OnTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen) = 0;

	// 离座之前
	virtual int OnLeaveSeatBefore(LONGLONG lUserId, int iSeatNo) = 0;

	// 离座之后
	virtual int OnLeaveSeatLast(int iSeatNo) = 0;

	// 断线
	virtual int OnCut(LONGLONG lUserId) = 0;

	// 断线重入响应，仅仅在用用户名、密码登录房间时才会响应
	virtual int OnRecomeAfterCut(int iSeatNo) = 0;

	//游戏开始
	virtual int OnGameBegin() = 0;

	//游戏结束
	virtual int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag)= 0;

	// 桌子定时器响应
	virtual int OnTableTimer(int iTableNo, int iIDEvent) = 0;

	// 举手
	virtual int OnRaiseHand(int iSeatNo) = 0;

	// 收取台费 和赠送子弹
	virtual void TradeFee() = 0;

	// 结算
	virtual int OnAccounts(int iSeatNo) = 0;

	// 用户坐下
	virtual void OnUserSitDown(int iSeatNo) = 0 ;

public:

	/* --------------------------------------------------------------------------
	函数说明：初始化
	传入参数：
		pRoomMgr		房间管理器的指针
		tableInfo		桌子信息
		iGameBeginType	游戏开始的类型，参考 GAME_BEGIN_TYPE_AUTO 等
	传出参数：
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	void init(IRoomMgr* pRoomMgr, const TABLE_INFO& tableInfo, int iGameBeginType);

	// 释放资源
	void uninit();

	// 建立游戏骨架使用的定时器
	int create_game_skeleton_timer();

	// 销毁游戏骨架使用的定时器
	int destroy_game_start_timer();

	// 向单个用户发送游戏消息
	int send_game_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 向单个用户发送游戏消息
	int send_game_data(LONGLONG lChannelNo, int iMainCode, int iSubCode);

	// 向单个用户发送游戏消息
	int send_data(int iSeatNo, int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 向单个用户发送游戏消息
	int send_data(int iSeatNo, int iMainCode, int iSubCode);

	// 房间内广播
	int broadcast_in_room(int iMainCode, int iSubCode, BYTE* pData, int iDataLen,LONGLONG lChannelNoIngore=INVALID_CHANNEL_NO, int iTableNo=INVAL_TABLE_NO);
	
	// 桌内广播
	int send_table_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen, LONGLONG lChannelNoIngore=INVALID_CHANNEL_NO);

	// 桌内广播指定状态的用户
	int send_table_state_user(int iMainCode, int iSubCode, BYTE* pData, int iDataLen, int iUserState, LONGLONG lChannelNoIngore=INVALID_CHANNEL_NO);

	// 打印桌子用户列表
	void PrintTableUser();

	// 设置桌子定时器
	int set_table_timer(int iIDEvent, int iElapse);

	// 结束桌子定时器
	int kill_table_timer(int iIDEvent);

	// 桌子定时器
	int OnBaseTableTimer(int iTableNo, int iIDEvent);

	// 响应桌子消息
	void OnBaseTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen);

	// 桌内举手者广播
	int broadcast_raise_hand(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);
	
	/* --------------------------------------------------------------------------
	函数说明：写入日志语句
	传入参数：
		bShowInScreen	显示于屏幕上
		iType	类型，参考 LOG_ERR_TYPE 枚举，
				LOG_TYPE_PROMPT = 0,	// 提示
				LOG_TYPE_WARING = 1,	// 警告
				LOG_TYPE_ERR = 2,		// 错误与异常

		pszSentence		日志语句
		iSentenceLen	日志语句的长度
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int write_log(BOOL bShowInScreen, int iType, char* pszSentence, int iSentenceLen);

	// 改变金币值
	//int change_gold(LONGLONG lChannelNo, LONGLONG lChangeScore);

	// 设置死循环监测指针
	void set_endless_loop(CEndlessLoop* pEndlessLoop);

	// 根据座位号获取当前入座者
	CSingleUser *get_SingleUser_by_seatNo(int iSeatNo);

	// 获得桌内入座的人数，
	int get_sit_down_count();

	// 获得桌内入座并且举手的人数
	int get_sit_down_raise_count();

	/* --------------------------------------------------------------------------
	函数说明：判断是否可以开始游戏
	返回值：
		可以开始则返回 0，不能开始返回错误码如下：
	--------------------------------------------------------------------------*/
	int can_begin_game();

	/* --------------------------------------------------------------------------
	函数说明：判断是否可以结束游戏
	返回值：
		可以开始则返回 0，不能开始返回错误码如下：
	--------------------------------------------------------------------------*/
	int can_finish_game();

	// 断线重入
	int recome_after_cut(int iSeatNo);

public:
	// 入座
	int sit_down(int iSeatNo, CSingleUser* pSingleUser, int iOldDeskNo=INVAL_TABLE_NO);

	// 离座(房间调用)
	int leave_seat_external(int iSeatNo);

	// 离座(桌子调用) bIsChangeTable=是否是换桌退出
	int leave_seat(int iSeatNo, bool bIsChangeTable=false);

	// 踢一桌玩家离座 
	int tick_table_leave_seat(LONGLONG lMgrChannelNo, BOOL bWriteScore=TRUE, BOOL bShowInfo=TRUE);

	// 获取桌子状态(开始/结束状态...)
	volatile long get_game_sys_state(){return m_iGameSysState;}; 

	// 检查是否有效椅子号
	SEAT_INFO* is_valid_seat_no(int iSeatNo);

	// 结算
	int OnUserAccountsWrite(int iSeatNo, CMD_WRITE_SCORE sendData);

	// 比赛结算
	int OnUserMatchAccounts(int iSeatNo, CMD_MatchAccounts sendData);

private:
	// 游戏开始前处理
	int OnGameStart();

	// 游戏结束
	int OnGameEnd();

	// 举手
	int OnBaseRaiseHand(int iSeatNo);

	// 检查未成年
	void OnCheckAntiAddiction();

	// 任务完成
	void UserTaskFinish(int iSeatNo, int iTaskId);

	// 检查举手情况
	void CheckTableRaise();

	// 获取桌内身份人数量
	int GetUserIdentityCount(UserIdentity eUserIdentity);

public:
	IRoomMgr*		m_pRoomMgr;	// 房间管理器的指针
	CMemBlockPool*	m_pMsgPool;
	TABLE_INFO	m_stTableInfo;	// 桌子信息
	vector<SEAT_INFO*>	m_vecSeatInfo;

	CEndlessLoop* m_pEndlessLoop;	// 死循环监测，同样可以监测死锁、长时间睡眠等问题

protected:
	CSRWLock	m_lockTable;	// 桌子锁，注意：此锁不能嵌套，一嵌套就会死锁

	int	m_iGameBeginType;				// 游戏开始的类型，参考 GAME_BEGIN_TYPE_AUTO 等
	volatile long m_iGameSysState;		// 游戏系统的状态，参考 GAME_SYS_STATE_NO 等

	int m_iWaitBegintick;		// 等待开始的滴答，目的是为了让框架全部准备完毕才让应用层开始游戏
	int m_iWaitBegintickCount;	// 等待开始的滴答计数

	LONGLONG m_lFinishAfterFreeTable;	// 空桌多长时间后可以结束游戏，以 ms 为单位
};

#endif