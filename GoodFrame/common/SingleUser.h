
/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:45
	filename: 	E:\SixDivisions\GoodFRame\common\SingleUser.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	SingleUser
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef SINGLE_USER_H
#define SINGLE_USER_H

#include "RoomInfo.h"
#include "GameTaskList.h"
//#include "ThreadGuardEx.h"
#include "LightweightPool.h"
#include <list>

struct EASY_DATA_TIME;

// �����û�
class __declspec(dllexport) CSingleUser
{
	// ���಻���������Ԫ�࣬������Ա������˽�У��������б�������ֹ�ⲿ���������� m_lockSingleUser ����ֱ�Ӹı䱾��ʵ���ı�����
	// ��Ϊ�������б�����Ա�ĸı���辭�����ຯ���� m_lockSingleUser �� �������ܱ�֤�̼߳���ȫ

public:
	CSingleUser(void);
	~CSingleUser(void);

public:

	// �ı��û���ֵ����;��������
	void change_user_test(int iFireNo, int iTableNo, int iSeatNo);

	// ��ʼ��
	void init();
	
	// �鵵
	void exit_destroy();

	// �����û���Ϣ
	void set_user_info(LONGLONG lNo, const USER_INFO* pUserInfo);

	// ����û���Ϣ
	USER_INFO &get_user_info();
	// ����û���Ϣ
	USER_INFO_SIM get_user_info_sim();

	// ��ȡ�û�ID
	LONGLONG get_user_id();

	// �����û�ID
	void set_user_id(LONGLONG lVal);

	// �����û�״̬
	void set_user_state(USER_STATE userState);

	// ��ȡ�û�״̬
	USER_STATE get_user_state();

	// ����ͨ����
	void set_channel(LONGLONG lNo);

	// ��ȡͨ����
	LONGLONG get_channel();

	// ��������
	void set_table_no(int iNo);

		// ��ȡ����
	int	get_table_no();

	// ������λ��
	void set_seat_no(int iNo);

		// ��ȡ��λ��
	int	get_seat_no();

	// ��ȡ��¼ʱ�Ľ��
	LONGLONG get_gold_login();

	// ���õ�¼ʱ�Ľ��
	void set_gold_login(LONGLONG lVal);
	
	// �޸Ľ��
	void change_gold_login(long long lVal); 

	// ��ȡ��¼ʱ�Ļ���
	LONGLONG get_point_login();

	// ���õ�¼ʱ�Ļ���
	void set_point_login(LONGLONG lVal);

	// �޸Ļ���
	void change_point_login(long long lChange);
	
	// �����û���
	void set_name(const char* pszName);

	// ��ȡ�û���
	int get_name(char* pszName, int iNameLen);

	// ��������
	void set_password(const char* pszPassword);

	// ��ȡ�û���
	int get_password(char* pszPassword, int iPasswordLen);

	// ��ȡ��һ�οͻ��˷���ʱ��
	long long get_Net_Gap_Time();

	// ���ÿͻ��˷���ʱ��
	void set_Net_Gap_Time(long long llTime);

	// ��������ʱ��
	void SetHeatBeatTime(long long lHeartBeatTime);

	// ��ȡ����ʱ��
	long long GetHeatBeatTime();

	// ��ȡ��������ʾ����
	int GetStepAntiAddiction();

	// ���÷�������ʾ����
	void SetStepAntiAddiction(int iStepAntiAddiction);

	// ������Ϸ�����
	void set_game_task_pool(CLightweightPool<GameTaskList>* pGameTaskPool);

	// ��ȡ��Ϸ����ָ��
	GameTaskList* GetGameTaskListPtr();

	// ��ȡ�û��Ƿ��������
	bool GetIsIdentity(UserIdentity identityId);

	// ս����¼========================================
	// ����ս��
	void AddBattleRecord(int iResult);

	// ��ȡս����¼��Ӯ����
	int GetBattleRecordWinLostCount(int iResult);
	//======================================

private:
	// ������Ա������˽�У��������б�������ֹ�ⲿ���������� m_lockSingleUser ����ֱ�Ӹı䱾��ʵ���ı�����
	// ��Ϊ�������б�����Ա�ĸı���辭�����ຯ���� m_lockSingleUser �� �������ܱ�֤�̼߳���ȫ

//	CSRWLock		m_lockSingleUser;		// ��Ա�ʵ����������ÿ���û�����һ������
											// ������⣺�ܼ�����ʱ����ֶ���߳�ͬʱ����һ���û�ʵ���ĳ�Ա
	USER_INFO		m_userInfo;				// �û���Ϣ

	long long		m_lHeartBeatTime;		// ����ʱ��

	int				m_iStepAntiAddiction;	// ��������ʾ����
	
	GameTaskList*	m_pGameTaskList;		// ������

	CLightweightPool<GameTaskList>* m_pGameTaskPool;

	std::list<CMD_UserBattleRecord> m_listBattleRecord;	// �û�ս����¼;
};

#endif