
/********************************************************************
	created:	2013/05/09
	created:	9:5:2013   11:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\GameSkeletonID.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	GameSkeletonID
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef GAME_SKELETON_ID
#define GAME_SKELETON_ID

#include <tchar.h>
#include <strsafe.h>
#include "PublicMacro.h"
#pragma comment(lib, "strsafe.lib") 

// 常量
#define TABLE_IDI_RAISE_TIME				20		// 准备时间

// 定时器
#define SYS_TIMER_EVENT_STARTING 10000	// 系统定时器事件的起点
#define TABLE_TIMER_GAME_BEGIN_ID (SYS_TIMER_EVENT_STARTING + 10)	// 游戏开始定时器ID，
#define TABLE_TIMER_GAME_BEGIN_ELAPSE 2000							// 游戏开始定时器间隔，以 ms 为单位

#define TABLE_TIMER_GAME_FINISH_ID (SYS_TIMER_EVENT_STARTING + 20)	// 游戏结束定时器ID，
#define TABLE_TIMER_GAME_FINISH_ELAPSE 3000							// 游戏结束定时器间隔，以 ms 为单位

#define TABLE_TIMER_ADD_FISH	(SYS_TIMER_EVENT_STARTING + 21)			// 增加鱼
#define TABLE_TIMER_ADD_FISH_INTERVAL 4000								// 增加鱼定时器间隔

#define TABLE_TIME_IDI_ANTI_ADDICTION	(SYS_TIMER_EVENT_STARTING + 22)	// 防沉迷
#define TABLE_TIMER_ANTI_ADDICTION_SPACE	10000						// 防沉迷时间间隔

#define TABLE_TIME_IDI_RAISE	(SYS_TIMER_EVENT_STARTING + 23)		// 举手定时器
#define TABLE_TIMER_RAISE_ELAPSE	5000							// 举手时间间隔

enum TASK_MODULE_ID	// 任务模块的 ID
{
	MODULE_ID_LOGIC_SKELETON = 1,
	MODULE_ID_DB_SKELETON = 2,
};

enum
{
	WORKER_NUM=6,		// 工人的数量
};

// 等级信息
struct CMD_GradeInfo
{
	CMD_GradeInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	int			iGradeId;					// 等级ID
	int			iMinExp;					// 最小经验
	int			iMaxExp;					// 最大经验
	char		szTitle[GRADE_TITLE_LEN];	// 称号
};

#endif
