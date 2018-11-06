/********************************************************************
	created:	2013/05/17
	created:	17:5:2013   17:18
	filename: 	E:\SixDivisions\GoodFRame\PUBLIC_H\GameSkeletonMsgCode.h
	file path:	E:\SixDivisions\GoodFRame\PUBLIC_H
	file base:	SkeletonMsgCode
	file ext:	h
	author:		�����
	
	purpose:	�Ǽ���Ϣ��
*********************************************************************/

#ifndef SKELETON_MSG_CODE_H
#define SKELETON_MSG_CODE_H

///#include "CMD_InnerServer.h"

enum MAIN_MSG_CODE	// ע��Ϣ��
{
	CONNECT_SUCC						= 10,	// ��Ӧ���ӳɹ�
	CONNECT_FAIL						= 20,	// ��Ӧ����ʧ��
	CLOSE_PEER							= 40,	// ��Ӧ�Զ˹رյ���Ϣ
	ROOM_TIMER							= 50,	// ��Ӧ���䶨ʱ��
	TABLE_TIMER							= 60,	// ��Ӧ���Ӷ�ʱ��
	NO_HEARTBEAT_DIE					= 70,    // ��Ӧ������������

	ROOM_MAIN							= 100,	// ������Ϣ
	ROOM_MGR_SERVER						= 150,	// ���ܷ��������

	MANAGER_MAIN						= 200,	// ����Ա��Ϣ
	MATCH_MAIN							= 400,	// ������Ϣ
	TASK_MAIN							= 500,	// ��Ϸ������Ϣ
	PROP_MAIN							= 600,	// ������Ϣ

	TABLE_MAIN							= 1000,	// ������Ϣ
	SYS_MAIN							= 1010,	// ϵͳ��Ϣ
};

enum SYS_SUB_MSG_CODE
{
	SYS_SUB_HEARTBEAT					= 10,	// ������Ϣ
};

enum ROOM_MGR_SERVER	// ���ܷ�����������Ϣ��
{
	RMS_SUB_FIRST_REQUEST_ROOM_INFO		=  50,	// ��һ�����뷿����Ϣ
	RMS_SUB_REQUEST_ROOM_INFO_ERR		=  52,	// ���뷿����Ϣʧ��

	RMS_SUB_WRITE_SCORE				= 200,	// д��
	RMS_SUB_WRITE_SCORE_RESULT		= 210,	// д�ֽ���
	RMS_SUB_MATCH_WRITE_SCORE		= 211,	// ����д��
	RMS_SUB_USER_TASK_FINISH		= 212,	// �û��������
	RMS_SUB_USER_NEXT_TASK			= 213,	// �û�������ɻ�ȡ��һ������
};

enum ROOM_SUB_MSG_CODE	// ���丨����Ϣ��
{

	ROOM_SUB_MY_TEST					= 10,	// ������
	ROOM_SUB_LOGIN						= 100,	// �����¼
	ROOM_SUB_PASS_VERIFY				= 110,	// �û���������Ч��
	ROOM_SUB_LOGIN_SUCC					= 115,	// ��¼����ɹ�
	ROOM_SUB_LOGIN_FAIL					= 120,	// �û���¼ʧ��
	ROOM_SUB_USER_INFO					= 126,	// �û���Ϣ
	ROOM_SUB_TABLE_LIST					= 127,	// ��ȡ�����б�
	ROOM_SUB_TABLE_LIST_OVER			= 128,	// ��ȡ�����б����
	ROOM_SUB_USER_LIST					= 130,	// �����ڵ��û��б�
	ROOM_SUB_USER_LIST_OVER				= 132,	// �û��б����
	ROOM_SUB_USER_LOGIN_FINISH			= 133,	// �û���¼���
	ROOM_SUB_LEAVE_ROOM					= 180,	// �뷿

	ROOM_SUB_RECOME						= 190,	// ��������

	ROOM_SUB_ROOM_INFO					= 300,	// ���뷿����Ϣ
	ROOM_SUB_ANTI_ADDICTION				= 301,	// ��ȡ�Ƿ����÷�����
	ROOM_SUB_ROOM_USER_COUNT			= 302,	// ��������
	ROOM_SUB_ROOM_SPEAK					= 303,	// ��������
	ROOM_SUB_USER_GET_TASK				= 304,	// �û�����
	ROOM_SUB_GRADE_LIST					= 305,	// �ȼ��б�
	ROOM_SUB_GRADE_LIST_SEND_FINISH		= 306,	// �ȼ��б������
};

enum MANAGER_SUB_MSG_CODE	// ����Ա������Ϣ��
{
	MANAGER_SUB_POWER_ERR				= 100,	// �޴˹���Ȩ��
	MANAGER_SUB_SET_ROOM_STATE			= 150,	// ���÷���״̬
	MANAGER_SUB_TICK_ONE_LEAVE_SEAT		= 300,	// ��һ���������
	MANAGER_SUB_TICK_TABLE_LEAVE_SEAT	= 310,	// ��һ���������
	MANAGER_SUB_TICK_ALL_LEAVE_SEAT		= 320,	// �������������������
	MANAGER_SUB_TICK_USER_OUT_ROOM		= 350,	// ������뷿
};

enum MATCH_SUB_MSG_CODE	// ����������Ϣ��
{
	MATCH_SUB_CS_ARRANGE_QUEUE					= 10,	// �����Ŷ�
	MATCH_SUB_SC_ARRANGE_QUEUE_FINISH			= 11,	// �Ŷ����
	MATCH_SUB_CS_CANCEL_ARRANGE_QUEUE			= 12,	// ȡ���Ŷ�
	MATCH_SUB_SC_CANCEL_ARRANGE_QUEUE_FINISH	= 13,	// ȡ���Ŷ����
	MATCH_SUB_SC_GAME_END						= 14,	// ��Ϸ����
	MATCH_SUB_SC_MATCH_COUNTDOWN				= 15,	// ��������ʱ
};

enum TASK_SUB_MSG_CODE	// ��Ϸ��������Ϣ��
{
	TASK_SUB_TEST = 10,	// ������
};

enum PROP_SUB_MSG_CODE	// ���߸�����Ϣ��
{
	PROP_SUB_TEST = 10,	// ������
};

//--- ���Ӳ��� -----------------------------------------------------

enum TABLE_SUB_MSG_CODE	// ���Ӹ�����Ϣ��
{
	TABLE_SUB_SITDOWN					= 140,	// ����
	TABLE_SUB_INIT_GAME				= 141,	// ��ʼ��Ϸ
	TABLE_SUB_FIRE							= 150,	// ����
	TABLE_SUB_REFLECTION				= 151,	// �ӵ�����
	TABLE_SUB_CAPTURE_FISH			= 152,	// ������
	TABLE_SUB_WRITE_SCORE				= 160,	// д��
	TABLE_SUB_LEAVE_SEAT				= 170,	// ����

	TABLE_SUB_RAISE_HAND				= 200,	// ���֣����º����Ϣ���ͻ���Ҫ�ȵ���ʼ����Ϻ󣬷�����Ϣ������˲ŷ���
	TABLE_SUB_WRITE_SCORE_RET			= 230,	// д�ַ���			// add by cxf
	TABLE_SUB_NET_GAP_TIME				= 280,	// �����ӳټ��(ƴ�����ӳ�)		// add by cxf
	// ���´�2000 ��ʼ����Ϊ�˺�������Ϣ(ProThreeGong.h)���ظ�
	TABLE_SUB_GAME_BEGIN				= 2000, // ��Ϸ��ʼ��Ϣ
	TABLE_SUB_USER_DATA_CHANGE			= 2001,	// �û����ݸı�
	TABLE_SUB_ANTI_ADDICTION			= 2002,	// ������
	TABLE_SUB_RECOMEAFTERCUT			= 2003,	// ��������
	TABLE_SUB_TABLE_SPEAK				= 2004,	// ����
	TABLE_SUB_SITDOWN_FINISH			= 2005,	// �������
	TABLE_SUB_CHANGE_DESK				= 2006,	// ����
	TABLE_SUB_CHANGE_DESK_SUC			= 2007,	// �����ɹ�
};

// ���ӹǼܷ��ش����� add by cxf
enum TABLE_RETURN_CODE
{
	RET_TABLE_OPERATE_SUCCEED			= 0,	// �����ɹ�
	RET_TABLE_USER_EXIST				= 10,	// �û��Ѿ�����������
	RET_TABLE_CHAIR_ERROR				= 20,	// ���Ӵ���
	RET_TABLE_CHAIR_OCCUPY				= 30,	// �����Ѿ�ռ��
	RET_TABLE_TABLE_START				= 40,	// �����Ѿ���ʼ��,���ܽ�����
	RET_TABLE_ENTER_GOLD_LACK			= 50,	// �����Ҳ������뷿��
	RET_TABLE_NOT_FOUND_FIT				= 60,	// δ�ҵ����ʵ����ӻ�����
	RET_TABLE_NOT_SITDOWN_MULTI_HIGH_PLAYER	= 70,	// ͬһ�����Ӳ������������߼��û�
};

struct CLOSE_PEER_DETAIL // ��Ӧ�Զ˹رյ���Ϣ��ϸ��
{
	LONGLONG lChannelNo;	// ͨ����
	int iCloseType;	
};

#endif