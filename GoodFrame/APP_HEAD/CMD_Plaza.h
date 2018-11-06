#ifndef CMD_PLAZA_H
#define CMD_PLAZA_H

#include "PublicMacro.h"

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

/*
**description:
******CS  -> �ͻ��˷�����������
******SC  -> �����������ͻ��˵�
******CSG -> �ͻ���/����������
******MAIN -> ����Ϣ
******SUB -> ����Ϣ
*/

#define MAIN_MSG_TASK					5000					// ����
#define SUB_CSG_TASK_LIST				5001					// ��ȡ�����б�
#define SUB_CSG_TASK_LIST_COMPLETE		5002					// ��ȡ�����б����
#define SUB_CSG_RECEIVE_REWARD			5003					// ��ȡ������
#define SUB_SC_GET_NEXT_TASK			5004					// ��ȡ��һ������

#define MAIN_MSG_ACTIVITY				5100					// �
#define SUB_CSG_ACTIVITY_LIST			5101					// ��ȡ��б�
#define SUB_CSG_ACTIVITY_LIST_COMPLETE	5102					// ��ȡ��б����

#define MAIN_MSG_PLAZA_RANKING			5200					// ����
#define SUB_CSG_RANKING					5201					// ���а�
#define SUB_CSG_RANKING_COMPLETE		5103					// ��ȡ���а����
#define SUB_SC_MY_RANKING				5202					// ���Լ�������

#define MAIN_MSG_SHOP					5300					// �̳�
#define SUB_CSG_POINTCARD				5301					// �㿨��ֵ

#define MAIN_MSG_HALL					5400					// ����
#define SUB_CSG_INIT_HALL				5401					// ��ȡ��������

#define MAIN_MSG_BANKER					5500					// ���й���
#define SUB_CSG_BANKER_INFO				5501					// ��ȡ������Ϣ
#define SUB_CS_SET_BANKER_PWD			5502					// ������������
#define SUB_SC_SET_BANKER_RET			5503					// �������뷵��
#define SUB_CS_BANKER_DRAWINGS			5504					// ����ȡ��
#define SUB_SC_BANKER_DRAWINGS_RET		5505					// ȡ���
#define SUB_CS_BANKER_DEPOSIT			5506					// ���д��
#define SUB_SC_BANKER_DEPOSIT_RET		5507					// ����


// =================================�������к�
// ��������
#define IDI_ERROR_BANKER_OLD_PWD		1000					// ���������
// ����ȡ��
#define IDI_ERROR_BANKER_PWD			1001					// �����������
#define IDI_BANKER_GLOD_DEFICIENCY		1002					// ���н�Ҳ���
// ���д��
#define IDI_USER_NOT_EXIST				1003					// �û�������
#define IDI_GLOD_DEFICIENCY				1004					// �����Ҳ���


// ��ʱ��ID
const int TIMER_ID_UPDATE = 100;								// ���¼�ʱ��
// ��ʱ��ʱ��
const int TIMER_TIME = 60*1000*60*24;							// 24Сʱ

// ��������
struct CMD_PlazaServerList
{
	CMD_PlazaServerList()
	{
		memset(this, 0, sizeof(*this));
	}
	int			iPort;					// �˿�
	char		szIp[IP_ADDRES_LEN];	// IP

};
// ��¼���ڲ�����
struct CMD_PlazaConfig
{
	CMD_PlazaConfig()
	{
		memset(this, 0, sizeof(*this));
	}
	char			szLocalIp[IP_ADDRES_LEN];					// ����IP
	int				iPort;										// �����˿�
	int				iDbPort;									// ���ݿ�˿�
	char			szDbIp[IP_ADDRES_LEN];						// ���ݿ��ַ
	char			szDbUserName[DB_USER_NAME_LEN];				// ���ݿ��û���
	char			szDbUserPwd[DB_PASS_LEN];					// ���ݿ�����
	char			szDbName[DB_NAME_LEN];						// ���ݿ�����
	char			szCenterIp[IP_ADDRES_LEN];					// ���ķ�����Ip
	int				iCenterPort;								// ���ķ������˿�
};

// �����б�
struct  CMD_SC_TaskList
{
	CMD_SC_TaskList()
	{
		memset(this, 0, sizeof(*this));
	}
	int			nIsEveryday;								// �Ƿ�ÿ������
	int			nID;												// ����ID
	int			nTypeID;									// ����ID
	int			nGameID;									// ����������ϷID��0��������1<ר����Ϸ����
	int			nReward;									// ������
	int			nState;										// ����״̬��0���Խ��ܣ�1�����У�2������ɣ�3��������ȡ��
	int			nCurSchedule;							// ��ǰ����
	int			nTotalSchedule;						// �ܽ���
	int			nPriority;									// ���ȼ�
	char		szTaskName[TASK_NAME_LEN];		// ��������
	char		szTaskDescription[DESCRIPTION_LEN];	// ��������
};
struct CMD_CS_TaskList
{
	CMD_CS_TaskList()
	{
		memset(this, 0, sizeof(*this));
	}
	int					nGame;							// ��ϷID
	long long		lUserID;							// �û�ID
};
// ��ȡ������
struct CMD_CSG_TaskAward
{
	CMD_CSG_TaskAward()
	{
		memset(this, 0, sizeof(*this));
	}
	int					nRet;							// ��ȡ������0���ɹ���
	int					nTaskID;						// ����ID
	int					nReward;					// ������
	long long		lUserID;						// �û�ID
};
// ��ȡ��һ������
struct CMD_SC_GET_NEXT_TASK
{
	CMD_SC_GET_NEXT_TASK()
	{
		memset(this, 0, sizeof(*this));
	}

	int					nLastTaskID;				// ��һ������ID
	CMD_SC_TaskList NextTask;
};


// ��ȡ����
struct CMD_SC_Award
{
	CMD_SC_Award()
	{
		memset(this, 0, sizeof(*this));
	}

	int					nAwardID;					// ����ID
	int					nReward;					// ������
	int					nCount;						// ��Ŀ
	char				szFileName[FILE_NAME_LEN];		// �������Ͷ�Ӧ���ļ���
	char				szDescription[DESCRIPTION_LEN];		// ˵��
};
struct CMD_CS_Award
{
	CMD_CS_Award()
	{
		memset(this, 0, sizeof(*this));
	}

	int					nTaskID;						// ����ID
	int					nRet;							// ��ȡ������0���ɹ���
	int					nReward;					// ������
	long long		lUserID;						// �û�ID
};

// ��б�
struct CMD_SC_ActivityList
{
	CMD_SC_ActivityList()
	{
		memset(this, 0, sizeof(*this));
	}
	int			nID;															// �ID
	char			szStartTime[TIME_LEN];					// ��ʼʱ��
	char			szEndTime[TIME_LEN];						// ����ʱ��
	char			szName[ACTIVITY_NAME_LEN];							// �����
	char			szTitle[ACTIVITY_TITLE_LEN];							// �����
	char			szDescription[DESCRIPTION_LEN];		// �����
};

// ���а�
struct CMD_SC_RankingList
{
	CMD_SC_RankingList()
	{
		memset(this, 0, sizeof(*this));
	}
	int				nRank;																		// ����
	long long	nValue;																		// ����ֵ����һ���֣�
	long long	lSyslogoid;																// ͷ��ID
	char				szNickName[USER_NAME_LEN];										// �ǳ�
};

struct CMD_CSG_Ranking
{
	CMD_CSG_Ranking()
	{
		memset(this, 0, sizeof(*this));
	}
	int					nMyRank;																// �Լ�������
	long long		lUserID;																	// �û�ID
};

// �̵�
struct CMD_SC_Shop
{
	CMD_SC_Shop()
	{
		memset(this, 0, sizeof(*this));
	}
	int			nID;																				// ��ƷID
	int			nGold;																		// ����
	int			nRenminbi;																// �����
};
struct CMD_PointCard_AddMoney
{
	CMD_PointCard_AddMoney()
	{
		memset(this, 0, sizeof(*this));
	}
	static const int CARD_LEN = 10;
	static const int PW_LEN = 7;

	long long		lUserID;																// �û�ID
	char					szCardNumber[CARD_LEN];							// ����
	char					szPassword[PW_LEN];										// ����
};

struct CMD_InitHall
{
	CMD_InitHall(){	memset(this, 0, sizeof(*this)); }

	long long		llUserID;
	int					iGameID;
	int					iCurCompleteTaskCount;							// ��ǰ��ɵ�������
};


// ��ȡ������Ϣ
struct CMD_GetBankerInfo
{
	CMD_GetBankerInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// �û�ID
};

// ����������Ϣ
struct CMD_BankerInfo
{
	CMD_BankerInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// �û�ID
	long long			lGold;								// ������
	long long			lBankerGold;						// ���н��
};

// �޸���������
struct CMD_SetBankerPwd
{
	CMD_SetBankerPwd()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// �û�ID
	char				szOldPwd[USER_PASSWORD_LEN];		// ������
	char				szNewPwd[USER_PASSWORD_LEN];		// ������
};

// �޸��������뷵��
struct CMD_SetBankerPwdRet
{
	CMD_SetBankerPwdRet()
	{
		memset(this, 0, sizeof(*this));
	}
	int					iRet;								// �޸ķ���
	long long			lUserId;							// �û�ID
};

// ����ȡ��
struct CMD_BankerDrawings
{
	CMD_BankerDrawings()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// �û�ID
	char				szBankerPwd[USER_PASSWORD_LEN];		// ��������
	long long			lDrawingsGold;						// ȡ����
};

// ȡ���
struct CMD_BankerDrawingsRet
{
	CMD_BankerDrawingsRet()
	{
		memset(this, 0, sizeof(*this));
	}
	int					iRet;								// ȡ���״̬
	long long			lUserId;							// �û�ID
	long long			lGold;								// ������
	long long			lBankerGold;						// ���н��
};

// ���д��
struct CMD_BankerDeposit
{
	CMD_BankerDeposit()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// �û�ID
	long long			lDepositGold;						// �����
};

// ����
struct CMD_BankerDepositRet
{
	CMD_BankerDepositRet()
	{
		memset(this, 0, sizeof(*this));
	}
	int					iRet;								// ����״̬
	long long			lUserId;							// �û�ID
	long long			lGold;								// ������
	long long			lBankerGold;						// ���н��
};


#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif