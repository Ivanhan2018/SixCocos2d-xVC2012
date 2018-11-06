
/********************************************************************
	created:	2013/05/09
	created:	9:5:2013   11:44
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\GameSkeletonID.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	GameSkeletonID
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef GAME_SKELETON_ID
#define GAME_SKELETON_ID

#include <tchar.h>
#include <strsafe.h>
#include "PublicMacro.h"
#pragma comment(lib, "strsafe.lib") 

// ����
#define TABLE_IDI_RAISE_TIME				20		// ׼��ʱ��

// ��ʱ��
#define SYS_TIMER_EVENT_STARTING 10000	// ϵͳ��ʱ���¼������
#define TABLE_TIMER_GAME_BEGIN_ID (SYS_TIMER_EVENT_STARTING + 10)	// ��Ϸ��ʼ��ʱ��ID��
#define TABLE_TIMER_GAME_BEGIN_ELAPSE 2000							// ��Ϸ��ʼ��ʱ��������� ms Ϊ��λ

#define TABLE_TIMER_GAME_FINISH_ID (SYS_TIMER_EVENT_STARTING + 20)	// ��Ϸ������ʱ��ID��
#define TABLE_TIMER_GAME_FINISH_ELAPSE 3000							// ��Ϸ������ʱ��������� ms Ϊ��λ

#define TABLE_TIMER_ADD_FISH	(SYS_TIMER_EVENT_STARTING + 21)			// ������
#define TABLE_TIMER_ADD_FISH_INTERVAL 4000								// �����㶨ʱ�����

#define TABLE_TIME_IDI_ANTI_ADDICTION	(SYS_TIMER_EVENT_STARTING + 22)	// ������
#define TABLE_TIMER_ANTI_ADDICTION_SPACE	10000						// ������ʱ����

#define TABLE_TIME_IDI_RAISE	(SYS_TIMER_EVENT_STARTING + 23)		// ���ֶ�ʱ��
#define TABLE_TIMER_RAISE_ELAPSE	5000							// ����ʱ����

enum TASK_MODULE_ID	// ����ģ��� ID
{
	MODULE_ID_LOGIC_SKELETON = 1,
	MODULE_ID_DB_SKELETON = 2,
};

enum
{
	WORKER_NUM=6,		// ���˵�����
};

// �ȼ���Ϣ
struct CMD_GradeInfo
{
	CMD_GradeInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	int			iGradeId;					// �ȼ�ID
	int			iMinExp;					// ��С����
	int			iMaxExp;					// �����
	char		szTitle[GRADE_TITLE_LEN];	// �ƺ�
};

#endif
