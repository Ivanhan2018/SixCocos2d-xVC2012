
#include "PublicHead.h"
#include "SingleUser.h"

#include <stdio.h>

CSingleUser::CSingleUser(void)
{
	memset(&m_userInfo,0,sizeof(m_userInfo));
	m_userInfo.lChannelNo = INVALID_CHANNEL_NO;
	m_userInfo.lUserId = INVALID_USER_ID;
	m_userInfo.iTableNo = INVAL_TABLE_NO;
	m_userInfo.iSeatNo = INVAL_SEAT_NO;
	m_userInfo.stUserState = US_OFFLINE;	// �û�״̬
	m_iStepAntiAddiction = 0;
	m_pGameTaskPool = NULL;

	m_pGameTaskList = NULL;
	m_listBattleRecord.clear();
}


CSingleUser::~CSingleUser(void)
{
	exit_destroy();
}

// �ı��û���ֵ����;��������
void CSingleUser::change_user_test(int iFireNo, int iTableNo, int iSeatNo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);

	printf("Start ��� %d, �����߳� %d ����%d , ����%d \n", 
		iFireNo, GetCurrentThreadId(), iTableNo, iSeatNo);

	printf("  ���ĸı� CSingleUser ʵ����ֵ�ɣ������ģ���� %d, �����߳� %d ����%d , ����%d \n", 
		iFireNo, GetCurrentThreadId(), iTableNo, iSeatNo);

	printf("End ��� %d, �����߳� %d ����%d , ����%d \n\n", 
		iFireNo, GetCurrentThreadId(), iTableNo, iSeatNo);
}

void CSingleUser::set_game_task_pool(CLightweightPool<GameTaskList>* pGameTaskPool)
{
	if (NULL==m_pGameTaskPool)
	{
		m_pGameTaskPool = pGameTaskPool;
	}
}


// ��ʼ��
void CSingleUser::init()
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	memset(&m_userInfo, 0, sizeof(m_userInfo));
	m_userInfo.lChannelNo = INVALID_CHANNEL_NO;
	m_userInfo.lUserId = INVALID_USER_ID;
	m_userInfo.iTableNo = INVAL_TABLE_NO;
	m_userInfo.iSeatNo = INVAL_SEAT_NO;
	m_userInfo.stUserState = US_OFFLINE;	// �û�״̬
	m_lHeartBeatTime =(long long(time(NULL)));
	m_iStepAntiAddiction = 0;

	m_pGameTaskList = NULL;
	m_pGameTaskPool->retrieve(&m_pGameTaskList);
	assert(m_pGameTaskList);
	m_listBattleRecord.clear();
}

// �鵵
void CSingleUser::exit_destroy()
{
	memset(&m_userInfo, 0, sizeof(m_userInfo));
	assert(m_pGameTaskList);

	m_pGameTaskPool->recycle(m_pGameTaskList);
	m_pGameTaskList = NULL;
	m_listBattleRecord.clear();
}

GameTaskList* CSingleUser::GetGameTaskListPtr()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_pGameTaskList;
}

// �����û���Ϣ
void CSingleUser::set_user_info(LONGLONG lNo, const USER_INFO* pUserInfo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	assert(pUserInfo);
	if(!pUserInfo)
	{
		return;
	}

	memcpy(&m_userInfo, pUserInfo, sizeof(m_userInfo));
	m_userInfo.lChannelNo = lNo;
}

// ����û���Ϣ
USER_INFO& CSingleUser::get_user_info()
{
	//CThreadGuardRead guard(&m_lockSingleUser);

	return m_userInfo;
}

USER_INFO_SIM CSingleUser::get_user_info_sim()
{
	//CThreadGuardRead guard(&m_lockSingleUser);

	USER_INFO_SIM userInfoSim;

	_snprintf(userInfoSim.szName, sizeof(userInfoSim.szName), m_userInfo.szName);
	_snprintf(userInfoSim.szPassword, sizeof(userInfoSim.szPassword), m_userInfo.szPassword);
	_snprintf(userInfoSim.szNickname, sizeof(userInfoSim.szNickname), m_userInfo.szNickname);

	userInfoSim.lUserId			= m_userInfo.lUserId;			// �û�ID
	userInfoSim.stUserState		= m_userInfo.stUserState;		// �û�״̬
	userInfoSim.iTableNo		= m_userInfo.iTableNo;			// ����
	userInfoSim.iSeatNo			= m_userInfo.iSeatNo;			// ��λ��
	userInfoSim.lGoldLogin		= m_userInfo.lGoldLogin;		// ��������Ľ��ֵ
	userInfoSim.iSex			= m_userInfo.iSex;				// �Ա�0���ԡ�1Ů��
	userInfoSim.lIdentity		= m_userInfo.lIdentity;			// ��ҵ���ݣ�һ������Ա����������Ա�������Ա�������Ա����ͨ��ҵ�
	userInfoSim.lMasterPower	= m_userInfo.lMasterPower;		// ����Ȩ�ޣ������룩������������Ϣ��������Ϸ��Ϣ����ֹ��������Ϸ����������ߡ�����Ӽ���������ֹ�������� ��
	userInfoSim.lGamePower		= m_userInfo.lGamePower;		// �����ϷȨ�ޣ������룩��������Ϸ���졢��������Ϣ�����κ��Թ� ��
	userInfoSim.lSysLogoID		= m_userInfo.lSysLogoID;		// ϵͳ�ṩ��ͷ��ϵ�С�
	userInfoSim.lExperience		= m_userInfo.lExperience;		// ����ֵ
	userInfoSim.lPointLogin		= m_userInfo.lPointLogin;		// ����

	return userInfoSim;
}

// ��ȡ�û�ID
LONGLONG CSingleUser::get_user_id()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.lUserId;		
}	

// �����û�ID
void CSingleUser::set_user_id(LONGLONG lVal)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lUserId = lVal;		
}	

// �����û�״̬
void CSingleUser::set_user_state(USER_STATE userState)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.stUserState = userState;	
}

// ��ȡ�û�״̬
USER_STATE CSingleUser::get_user_state()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.stUserState;	
}

// ����ͨ����
void CSingleUser::set_channel(LONGLONG lNo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lChannelNo = lNo;
}

// ��ȡͨ����
LONGLONG CSingleUser::get_channel()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.lChannelNo;
}

// ��������
void CSingleUser::set_table_no(int iNo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.iTableNo = iNo;		
}

// ��ȡ����
int	CSingleUser::get_table_no()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.iTableNo;		
}

// ������λ��
void CSingleUser::set_seat_no(int iNo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.iSeatNo = iNo;		
}	


// ��ȡ��λ��
int	CSingleUser::get_seat_no()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.iSeatNo;		
}	

// ���õ�¼ʱ�Ľ��
void CSingleUser::set_gold_login(LONGLONG lVal)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lGoldLogin = lVal;		
}	

// ��ȡ��¼ʱ�Ľ��
LONGLONG CSingleUser::get_gold_login()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.lGoldLogin;		
}	
// �޸Ľ�� // add by cxf
void CSingleUser::change_gold_login(long long lVa)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lGoldLogin += lVa;		
}	

 // ��ȡ��¼ʱ�Ļ���
 LONGLONG CSingleUser::get_point_login()
 {
	 //CThreadGuardRead guard(&m_lockSingleUser);
	 return m_userInfo.lPointLogin;
 }

 // ���õ�¼ʱ�Ļ���
 void CSingleUser::set_point_login(LONGLONG lVal)
 {
	// CThreadGuardWrite guard(&m_lockSingleUser);
	 m_userInfo.lPointLogin = lVal;		
 }	

 // ���õ�¼ʱ�Ļ���
 void CSingleUser::change_point_login(long long lChange)
 {
	//CThreadGuardWrite guard(&m_lockSingleUser);
	  m_userInfo.lPointLogin += lChange;		
 }

 // �����û���
 void CSingleUser::set_name(const char* pszName)
 {
	 //CThreadGuardWrite guard(&m_lockSingleUser);

	 _snprintf(m_userInfo.szName, sizeof(m_userInfo.szName)-1, "%s", pszName);
 }	


 // ��ȡ�û���
int CSingleUser::get_name(char* pszName, int iNameLen)
 {
	// CThreadGuardRead guard(&m_lockSingleUser);

	 if(!pszName)
		 return 10;
	 if(iNameLen<=0)
		 return 20;

	  _snprintf(pszName, iNameLen, "%s", m_userInfo.szName);

	 return 0;		
 }	

// ��������
void CSingleUser::set_password(const char* pszPassword)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);

	_snprintf(m_userInfo.szPassword, sizeof(m_userInfo.szPassword)-1, "%s", pszPassword);
}	

// ��ȡ�û���
int CSingleUser::get_password(char* pszPassword, int iPasswordLen)
{
	//CThreadGuardRead guard(&m_lockSingleUser);

	if(!pszPassword)
		return 10;
	if(iPasswordLen<=0)
		return 20;

	_snprintf(pszPassword, iPasswordLen, "%s", m_userInfo.szPassword);

	return 0;		
}	

// ��ȡ�û�����pingʱ��
long long CSingleUser::get_Net_Gap_Time()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.lNetGapTime;
}

// �����û�����pingʱ��
void CSingleUser::set_Net_Gap_Time(long long llTime)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lNetGapTime = llTime;
}

// ��ȡ�û�����ʱ��
long long CSingleUser::GetHeatBeatTime()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_lHeartBeatTime;
}

// �����û�����ʱ��
void CSingleUser::SetHeatBeatTime(long long lHeartBeatTime)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_lHeartBeatTime = lHeartBeatTime;
}

// ��ȡ��������ʾ����
int CSingleUser::GetStepAntiAddiction()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_iStepAntiAddiction;
}

// ���÷�������ʾ����
void CSingleUser::SetStepAntiAddiction(int iStepAntiAddiction)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_iStepAntiAddiction = iStepAntiAddiction;
}

// �û��Ƿ��������
bool CSingleUser::GetIsIdentity(UserIdentity identityId)
{
	return identityId & m_userInfo.lIdentity;
}

// ����ս��
void CSingleUser::AddBattleRecord(int iWinLost)
{
	if (m_listBattleRecord.size()>=10)
	{
		m_listBattleRecord.pop_front();
	}
	CMD_UserBattleRecord buf;
	buf.iResult = iWinLost;
	m_listBattleRecord.push_back(buf);
}

// ��ȡս����¼��Ӯ����
int CSingleUser::GetBattleRecordWinLostCount(int iWinLost)
{
	int iCount=0;
	std::list<CMD_UserBattleRecord>::iterator it = m_listBattleRecord.begin();
	for(;it!=m_listBattleRecord.end();++it)
	{
		CMD_UserBattleRecord record = (CMD_UserBattleRecord)*it;
		if (iWinLost==record.iResult)
		{
			++iCount;
		}
	}
	return iCount;
}