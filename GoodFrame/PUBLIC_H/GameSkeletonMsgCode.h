/********************************************************************
	created:	2013/05/17
	created:	17:5:2013   17:18
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\GameSkeletonMsgCode.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	SkeletonMsgCode
	file ext:	h
	author:		侯国江
	
	purpose:	骨架消息码
*********************************************************************/

#ifndef SKELETON_MSG_CODE_H
#define SKELETON_MSG_CODE_H

///#include "CMD_InnerServer.h"

enum MAIN_MSG_CODE	// 注消息码
{
	CONNECT_SUCC						= 10,	// 响应连接成功
	CONNECT_FAIL						= 20,	// 响应连接失败
	CLOSE_PEER							= 40,	// 响应对端关闭的消息
	ROOM_TIMER							= 50,	// 响应房间定时器
	TABLE_TIMER							= 60,	// 响应桌子定时器
	NO_HEARTBEAT_DIE					= 70,    // 响应无心跳至死的

	ROOM_MAIN							= 100,	// 房间消息
	ROOM_MGR_SERVER						= 150,	// 房管服务器相关

	MANAGER_MAIN						= 200,	// 管理员消息
	MATCH_MAIN							= 400,	// 比赛消息
	TASK_MAIN							= 500,	// 游戏任务消息
	PROP_MAIN							= 600,	// 道具消息

	TABLE_MAIN							= 1000,	// 桌子消息
	SYS_MAIN							= 1010,	// 系统消息
};

enum SYS_SUB_MSG_CODE
{
	SYS_SUB_HEARTBEAT					= 10,	// 心跳消息
};

enum ROOM_MGR_SERVER	// 房管服务器辅助消息码
{
	RMS_SUB_FIRST_REQUEST_ROOM_INFO		=  50,	// 第一次申请房间信息
	RMS_SUB_REQUEST_ROOM_INFO_ERR		=  52,	// 申请房间信息失败

	RMS_SUB_WRITE_SCORE				= 200,	// 写分
	RMS_SUB_WRITE_SCORE_RESULT		= 210,	// 写分结束
	RMS_SUB_MATCH_WRITE_SCORE		= 211,	// 比赛写分
	RMS_SUB_USER_TASK_FINISH		= 212,	// 用户任务完成
	RMS_SUB_USER_NEXT_TASK			= 213,	// 用户任务完成获取下一个任务
};

enum ROOM_SUB_MSG_CODE	// 房间辅助消息码
{

	ROOM_SUB_MY_TEST					= 10,	// 测试用
	ROOM_SUB_LOGIN						= 100,	// 房间登录
	ROOM_SUB_PASS_VERIFY				= 110,	// 用户名与密码效验
	ROOM_SUB_LOGIN_SUCC					= 115,	// 登录房间成功
	ROOM_SUB_LOGIN_FAIL					= 120,	// 用户登录失败
	ROOM_SUB_USER_INFO					= 126,	// 用户信息
	ROOM_SUB_TABLE_LIST					= 127,	// 获取桌子列表
	ROOM_SUB_TABLE_LIST_OVER			= 128,	// 获取桌子列表结束
	ROOM_SUB_USER_LIST					= 130,	// 房间内的用户列表
	ROOM_SUB_USER_LIST_OVER				= 132,	// 用户列表结束
	ROOM_SUB_USER_LOGIN_FINISH			= 133,	// 用户登录完成
	ROOM_SUB_LEAVE_ROOM					= 180,	// 离房

	ROOM_SUB_RECOME						= 190,	// 断线重入

	ROOM_SUB_ROOM_INFO					= 300,	// 申请房间信息
	ROOM_SUB_ANTI_ADDICTION				= 301,	// 获取是否启用防沉迷
	ROOM_SUB_ROOM_USER_COUNT			= 302,	// 房间人数
	ROOM_SUB_ROOM_SPEAK					= 303,	// 房间聊天
	ROOM_SUB_USER_GET_TASK				= 304,	// 用户任务
	ROOM_SUB_GRADE_LIST					= 305,	// 等级列表
	ROOM_SUB_GRADE_LIST_SEND_FINISH		= 306,	// 等级列表发送完成
};

enum MANAGER_SUB_MSG_CODE	// 管理员辅助消息码
{
	MANAGER_SUB_POWER_ERR				= 100,	// 无此管理权限
	MANAGER_SUB_SET_ROOM_STATE			= 150,	// 设置房间状态
	MANAGER_SUB_TICK_ONE_LEAVE_SEAT		= 300,	// 踢一个玩家离座
	MANAGER_SUB_TICK_TABLE_LEAVE_SEAT	= 310,	// 踢一桌玩家离座
	MANAGER_SUB_TICK_ALL_LEAVE_SEAT		= 320,	// 踢所有在座的玩家离座
	MANAGER_SUB_TICK_USER_OUT_ROOM		= 350,	// 踢玩家离房
};

enum MATCH_SUB_MSG_CODE	// 比赛辅助消息码
{
	MATCH_SUB_CS_ARRANGE_QUEUE					= 10,	// 比赛排队
	MATCH_SUB_SC_ARRANGE_QUEUE_FINISH			= 11,	// 排队完成
	MATCH_SUB_CS_CANCEL_ARRANGE_QUEUE			= 12,	// 取消排队
	MATCH_SUB_SC_CANCEL_ARRANGE_QUEUE_FINISH	= 13,	// 取消排队完成
	MATCH_SUB_SC_GAME_END						= 14,	// 游戏结束
	MATCH_SUB_SC_MATCH_COUNTDOWN				= 15,	// 比赛倒计时
};

enum TASK_SUB_MSG_CODE	// 游戏任务辅助消息码
{
	TASK_SUB_TEST = 10,	// 测试用
};

enum PROP_SUB_MSG_CODE	// 道具辅助消息码
{
	PROP_SUB_TEST = 10,	// 测试用
};

//--- 桌子部分 -----------------------------------------------------

enum TABLE_SUB_MSG_CODE	// 桌子辅助消息码
{
	TABLE_SUB_SITDOWN					= 140,	// 入座
	TABLE_SUB_INIT_GAME				= 141,	// 初始游戏
	TABLE_SUB_FIRE							= 150,	// 开火
	TABLE_SUB_REFLECTION				= 151,	// 子弹反弹
	TABLE_SUB_CAPTURE_FISH			= 152,	// 捕获鱼
	TABLE_SUB_WRITE_SCORE				= 160,	// 写分
	TABLE_SUB_LEAVE_SEAT				= 170,	// 离座

	TABLE_SUB_RAISE_HAND				= 200,	// 举手，坐下后的消息，客户端要等到初始化完毕后，发此消息，服务端才发鱼
	TABLE_SUB_WRITE_SCORE_RET			= 230,	// 写分返回			// add by cxf
	TABLE_SUB_NET_GAP_TIME				= 280,	// 网络延迟间隔(拼网络延迟)		// add by cxf
	// 以下从2000 开始，是为了和桌内消息(ProThreeGong.h)不重复
	TABLE_SUB_GAME_BEGIN				= 2000, // 游戏开始消息
	TABLE_SUB_USER_DATA_CHANGE			= 2001,	// 用户数据改变
	TABLE_SUB_ANTI_ADDICTION			= 2002,	// 防沉迷
	TABLE_SUB_RECOMEAFTERCUT			= 2003,	// 断线重入
	TABLE_SUB_TABLE_SPEAK				= 2004,	// 聊天
	TABLE_SUB_SITDOWN_FINISH			= 2005,	// 坐桌完成
	TABLE_SUB_CHANGE_DESK				= 2006,	// 换桌
	TABLE_SUB_CHANGE_DESK_SUC			= 2007,	// 换桌成功
};

// 桌子骨架返回错误码 add by cxf
enum TABLE_RETURN_CODE
{
	RET_TABLE_OPERATE_SUCCEED			= 0,	// 操作成功
	RET_TABLE_USER_EXIST				= 10,	// 用户已经在桌子上了
	RET_TABLE_CHAIR_ERROR				= 20,	// 椅子错误
	RET_TABLE_CHAIR_OCCUPY				= 30,	// 椅子已经占用
	RET_TABLE_TABLE_START				= 40,	// 桌子已经开始了,不能进入了
	RET_TABLE_ENTER_GOLD_LACK			= 50,	// 自身金币不够进入房间
	RET_TABLE_NOT_FOUND_FIT				= 60,	// 未找到合适的椅子或桌子
	RET_TABLE_NOT_SITDOWN_MULTI_HIGH_PLAYER	= 70,	// 同一个桌子不允坐下许多个高级用户
};

struct CLOSE_PEER_DETAIL // 响应对端关闭的消息的细节
{
	LONGLONG lChannelNo;	// 通道号
	int iCloseType;	
};

#endif