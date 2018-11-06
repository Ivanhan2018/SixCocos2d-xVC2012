/*
�û���Ϸ�����б�
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

	// �������
	void AddTask(CMD_UserTaskInfo* pUserTaskInfo, int iDataSize);

	// ɾ������
	void DelTask(int iTaskId);

	// ��������
	CMD_UserTaskInfo *FindTask(int iTaskId);


public:
	// �û������б�
	std::map<int, CMD_UserTaskInfo> m_mapUserTaskList;
};

#endif