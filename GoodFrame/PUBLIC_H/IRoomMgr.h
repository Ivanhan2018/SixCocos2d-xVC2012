
#ifndef I_ROOM_MGR_H
#define I_ROOM_MGR_H

#include "./MemBlockPool.h"
#include "./EasyDataTime.h"

/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\IRoomMgr.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	IRoomMgr
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#include "./ThreadGuardEx.h"
#include "./LightweightPool.h"

#include "./GameSkeletonMsgCode.h"
#include "./RoomInfo.h"
#include "./SingleUser.h"
#include "./TableInfo.h"
#include "./RoomState.h"
#include "./CloseType.h"
#include "GradeMgr.h"

#include <hash_map>
using std::hash_map;
using std::pair;

#include <vector>
using std::vector;

#include <map>

class CEndlessLoop;
class IBaseTable;
class CCoreServer;
class CClientToRMS;

enum TASK_MSG_RESULT;	// 任务消息结果

#define ROOM_TIMER_FLAG  0x0001000000000000	// 房间定时器标识，高32位的前16位表示房间或桌子
#define TABLE_TIMER_FLAG 0x0002000000000000	// 桌子定时器标识，高32位的后16位表示桌子号

// 房间管理
class __declspec(dllexport) IRoomMgr
{
	
public:
	IRoomMgr(void);
	~IRoomMgr(void);


public:
	// 响应连接成功
	virtual void OnConnect(LONGLONG lChannelNo);	

	// 响应连接失败
	virtual void OnConnectFail(int iErrorCode);

	// 响应对端已关闭了
	virtual int OnClose(LONGLONG lChannelNo, CLOSE_TYPE iCloseType);

	// 主动踢出用户
	int OnKickOutUser(LONGLONG lChannelNo);

	/* --------------------------------------------------------------------------
	函数说明：响应无心跳至死
	传入参数：
		lChannelNo	被服务端断开的通道号
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int OnNoHeartbeatDie(LONGLONG lChannelNo);

	// 列印所有的死循环、死锁
	int display_all_guard();

public:	//--- 子类要继承的纯虚函数 -----------------------------------------------

	// 响应房间消息
	virtual TASK_MSG_RESULT OnRoomMsg(CMemBlock*& pMsgBlock) = 0;
	
	// 响应房间管理服务器的消息
	virtual void OnRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen) = 0;
	
	// 对端关闭之前一刹那的响应
	virtual int OnCloseBefore(LONGLONG lUserId) = 0;

public:	//--- 回调函数 -----------------------------------------------

	// 房管服务器相关
	TASK_MSG_RESULT OnSkeletonRoomMgrServer(CMemBlock*& pMsgBlock);

	/* --------------------------------------------------------------------------
	函数说明：响应房间消息
	传出参数：
		pMsgBlock	消息块，注意自动归池信号，若不想归池，可以参考 TASK_MSG_RESULT 的值
	返回值
		参考 TASK_MSG_RESULT 枚举
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT OnSkeletonRoomMsg(CMemBlock*& pMsgBlock);

	/* --------------------------------------------------------------------------
	函数说明：响应桌子消息
	传出参数：
		pMsgBlock	消息块，注意自动归池信号，若不想归池，可以参考 TASK_MSG_RESULT 的值
	返回值
		参考 TASK_MSG_RESULT 枚举
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT OnSkeletonTableMsg(CMemBlock*& pMsgBlock);

	/* --------------------------------------------------------------------------
	函数说明：响应管理员消息
	传出参数：
		pMsgBlock	消息块，注意自动归池信号，若不想归池，可以参考 TASK_MSG_RESULT 的值
	返回值
		参考 TASK_MSG_RESULT 枚举
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT OnSkeletonMagagerMsg(CMemBlock*& pMsgBlock);

	// 响应比赛消息
	TASK_MSG_RESULT OnSkeletonMatchMsg(CMemBlock*& pMsgBlock);

	// 响应游戏任务消息
	TASK_MSG_RESULT OnSkeletonTaskMsg(CMemBlock*& pMsgBlock);

	// 响应房间管理服务器的消息
	void OnSkeletonRMS(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应道具消息
	TASK_MSG_RESULT OnSkeletonPropMsg(CMemBlock*& pMsgBlock);

	// 系统消息
	TASK_MSG_RESULT OnSkeletonSysMsg(CMemBlock*& pMsgBlock);

	// 房间定时器响应
	int OnRoomTimer(int iIDEvent);

	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);

public:

	// 启动
	void start(const CCoreServer* pCCoreServer, const CMemBlockPool* pMsgPool, const SERVER_ROOM_INFO& serverRoomInfo);

	// 设置定时器
	int set_room_timer(int iIDEvent, int iElapse);

	// 结束定时器
	int kill_room_timer(int iIDEvent);

	// 设置桌子定时器
	int set_table_timer(int iTableNo, int iIDEvent, int iElapse);

	// 结束桌子定时器
	int kill_table_timer(int iTableNo, int iIDEvent);

	// 发送游戏消息，低效率
	int send_game_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 发送游戏消息，// add by cxf
	int send_game_data(LONGLONG lChannelNo, int iMainCode, int iSubCode);

	// 房间内广播
	int broadcast_in_room(int iMainCode, int iSubCode, BYTE* pData=NULL, int iDataLen=0,LONGLONG lChannelNoIngore=INVALID_CHANNEL_NO,int iTableNo=INVAL_TABLE_NO);

	// 关闭对端
	int close_peer(LONGLONG lChannelNo);

	/* --------------------------------------------------------------------------
	函数说明：投递任务消息，将消息投给指定的任务模块
	传入参数：
		iTaskModuleID	任务模块ID
	传出参数：
		pMsgBlock		消息块
	返回值：
		返回参考 TASK_MSG_RESULT 枚举
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT post_work_msg(int iTaskModuleID, CMemBlock*& pMsgBlock);

	// 获得消息池的指针
	CMemBlockPool* get_msg_pool();

	// 获得死循环监测指针
	CEndlessLoop* get_endless_loop();

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

	// 打印房间用户列表
	void PrintRoomUser();

	// 打印桌子用户列表
	void PrintAllTableUser();

	// 获得房间信息
	SERVER_ROOM_INFO get_server_room_info();

	// 设置房间信息
	void set_server_room_info(SERVER_ROOM_INFO info);

public:

	// 获得通道号
	LONGLONG get_channel(CMemBlock* pMsgBlock);

	/* --------------------------------------------------------------------------
	函数说明：获得桌号与座位号
	传入参数：
		lChannelNo	通道号
	传出参数：
		iTableNo	桌号
		iSeatNo		座号
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	座号无效
			20	桌号无效
			30	没有入座
			40  找不到该用户
	--------------------------------------------------------------------------*/
	int get_table_seat_no(LONGLONG lChannelNo, int& iTableNo, int& iSeatNo);

	/* --------------------------------------------------------------------------
	函数说明：桌号是否有效
	传入参数：
		liTableNo	桌号
	返回值：
		有效则返回非零的指针，失败返回0：
	--------------------------------------------------------------------------*/
	IBaseTable* is_valid_table_no(int iTableNo);

	// 设置游戏开始的类型，iType 参考 GAME_BEGIN_TYPE_AUTO 等
	void game_begin_type(int iType);

	// 获得游戏开始的类型， 返回值参考 GAME_BEGIN_TYPE_AUTO 等
	int game_begin_type();

public:
	//--- 房间相关 -----------------------------------------------

	// 获得房内所有用户的通道号
	int find_all_user_channel(vector<LONGLONG>* pVecChannel);


	/* --------------------------------------------------------------------------
	函数说明：由通道号获得单个用户指针
	传入参数：
		lChannelNo	通道号
		bLock		true表示带锁查找，false 表示不锁查找
	传出参数：
	返回值：
		成功则返回 0，失败返回错误码如下：
	-------------------------------------------------------------------------- */
	CSingleUser* find_user_by_channel(LONGLONG lChannelNo, BOOL bLock=true);

	// 由用户ID获得单个用户指针
	CSingleUser* find_user_by_user_id(LONGLONG lUserId);

	// 获得单个玩家指针，根据桌号与座位号
	CSingleUser* find_user_by_table_seat(int iTableNo, int iSeatNo);

	// 获得单个玩家指针，根据用户名与密码
	CSingleUser* find_user_by_name_password(const char* pszName, const char* pszPassword);

	// 变更用户的通道号，根据用户ID
	int modi_user_by_channel(LONGLONG lUserId, LONGLONG lChannelNo, CSingleUser* singleUser);

	/* --------------------------------------------------------------------------
	函数说明：增加一个单个用户
	传入参数：
		lChannelNo	通道号
		pUserInfo	用户信息
	返回值：
		成功则返回 0，失败返回错误码如下：
			10 形参是空值
			20 已存在该用户，无法增加
	--------------------------------------------------------------------------*/
	int add_user(LONGLONG lChannelNo, const USER_INFO* pUserInfo);

	/* --------------------------------------------------------------------------
	函数说明：移除一个单个用户，根据通道号
	传入参数：
		lChannelNo	通道号
	传出参数：
		userInfo	离房者的信息
	返回值：
		成功则返回 0，失败返回错误码如下：
			10  未找到
			20  m_pUserPool 归池失败
	--------------------------------------------------------------------------*/
	int remove_one_user(LONGLONG lChannelNo);
	
	// 发送房间的桌子列表
	int send_table_list(LONGLONG lChannelNo);

	// 发送房间内的用户列表
	int send_user_list(LONGLONG lChannelNo);

	// 结算写分
	int SendWriteData(int iMainCode, int iSubCode, BYTE* byData, int iDataLen);

public:
	//--- 桌子相关 -----------------------------------------------

	// 判断管理者的权限
	int is_manager_power(LONGLONG lChannelNo, LONGLONG lManagerPower);

	// 离开房间
	int leave_room(LONGLONG lChannelNo);

	// 找桌子和椅子
	int allot_table_seat(CSingleUser *pSingleUser, SITDOWN* pSeatdown, int iOldDeskNo=INVAL_TABLE_NO);

	// 找椅子
	int allot_seat(CSingleUser *pSingleUser, SITDOWN* pSeatdown);

	// 入座
	int user_sit_down(CSingleUser *pSingleUser, SITDOWN* pSeatdown);

	// 离座
	int leave_seat(LONGLONG lChannelNo);

	/* --------------------------------------------------------------------------
	函数说明：踢一桌玩家离座 
	传入参数：
		lMgrChannelNo	管理者的通道号
		iTableNo		被踢的桌号
		bWriteScore		踢后是否写金币变化值
	返回值：
	   成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int tick_table_leave_seat(LONGLONG lMgrChannelNo, int iTableNo, BOOL bWriteScore=FALSE);

	// 踢所有的玩家离座
	int tick_all_leave_seat(LONGLONG lMgrChannelNo, BOOL bWriteScore=FALSE);

	// 踢一桌玩家离房
	int tick_table_out_room(LONGLONG lMgrChannelNo, int iTableNo);

	// 踢玩家离房
	int tick_user_out_room(LONGLONG lMgrChannelNo, const TICK_USER_OUT_ROOM* pTickOutRoom);
private:
	// 设置房间信息
	void SetRoomInfoSim(SERVER_ROOM_INFO_SIM &serverRoomInfoSim);	// add by cxf 2013-07-06

	// 用户排队
	void OnArrangeQueue(LONGLONG lChannelNo, BYTE *pData, int iDataLen);

	// 取消排队
	void OnCancelArrangeQueue(CSingleUser* pSingleUser);

	// 排队用户组桌
	void OnConstituteTables();

	// 寻找空桌子
	IBaseTable* Find_Null_Table();

	// 检查心跳
	void OnCheckUserHeartbeat();

	// 获取是否启用防沉迷
	void OnAntiAddiction();

	// 获取房间人数
	void get_room_user_count(CMD_RoomUserCount &roomUserCount);

	// 换桌
	void OnUserChangeDesk(CSingleUser *pSingleUser);

public:
	CCoreServer*		 m_pCoreServer;
	CMemBlockPool*		 m_pMsgPool;
	
	vector<IBaseTable*>	 m_vecTable;
	bool				m_bIsAntiAddiction;		// 是否启用	
	GradeMgr*			m_pGradeMgr;			// 等级管理

	

private:

	// 第1个是通道号，第2个是单个用户，通过 Channel 号高速查询 CSingleUser
    typedef	hash_map<LONGLONG, CSingleUser*>	MAP_SINGLE_USER; 	// 
	typedef pair <LONGLONG, CSingleUser*>		PAIR_SINGLE_USER;	// 键值对
	MAP_SINGLE_USER m_mapChannel;	// 房间里的用户
	
	// 第1个是 UserId，第2个是通道号，目的是通过 UserId 号高速查询通道号
	typedef hash_map<LONGLONG, LONGLONG> MAP_USERID_CHANNEL;
	typedef pair<LONGLONG, LONGLONG>	 PAIR_USERID_CHANNEL;
	MAP_USERID_CHANNEL m_mapUserid;		// 房间里的用户，
	
	CLightweightPool<CSingleUser>*	m_pUserPool;	// 用户池，一个房间内所有的用户，无论进房的还是离房的。
	
	CSRWLock	m_lock;		// 针对 m_mapChannel 与 m_mapUserid 的锁

	std::map<LONGLONG, CMD_USER_ARRANGE_QUEUE_LIST> m_mapUserQueueList;
	CSRWLock	m_lockQueueList;

private:
	int		 m_iGameBeginType;	// 游戏开始的类型，参考 GAME_BEGIN_TYPE_AUTO 等

	CRoomState	m_stRoomState;	// 房间状态

	SERVER_ROOM_INFO	 m_stServerRoomInfo;	// 房间信息

	CLightweightPool<GameTaskList>* m_pGameTaskPool;

protected:
	CEndlessLoop* m_pEndlessLoop;	// 死循环监测，同样可以监测死锁、长时间睡眠等问题
};

#endif