/*
用户游戏任务列表
*/
#ifndef GAME_TASK_LIST_H
#define GAME_TASK_LIST_H

#include "UserInfo.h"
#include <map>

class GameTaskList
{
public:
	GameTaskList();
	~GameTaskList();

	// 添加任务
	void AddTask(CMD_UserTaskInfo* pUserTaskInfo, int iDataSize);

	// 删除任务
	void DelTask(int iTaskId);

	// 查找任务
	CMD_UserTaskInfo *FindTask(int iTaskId);


public:
	// 用户任务列表
	std::map<int, CMD_UserTaskInfo> m_mapUserTaskList;
};

#endif