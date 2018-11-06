
#ifndef SELF_MODULE_ID
#define SELF_MODULE_ID

#ifdef WIN32
#include <tchar.h>
#include <strsafe.h>
#pragma comment(lib, "strsafe.lib") 
#endif
#include "PublicMacro.h"			// add by cxf

enum TASK_MODULE_ID	// ����ģ��� ID
{
	MODULE_ID_MY_LOGIC = 1,
	MODULE_ID_OTHER_LOGIC = 2,
	MODULE_ID_DB_MY_NAME = 3,
};

#define TIMER_ID_TEST_01 1
#define TIMER_ID_TEST_02 2

// ��ʱ��ID
#define TIMER_ID_GET_FEATS_LIST		100		// ��ѫ�б�
#define TIMER_ID_GET_MATCH_LIST		101		// �����б�
#define TIMER_ID_GENERATE_RANKING	102		// ��������
#define TIMER_ID_GET_GAME_ROOM_INFO	103		// ��ȡ��Ϸ�ͷ���

// ��ʱ��ʱ�� generate
#define TIMER_TIME_GET_FEATS_LIST	(60*1000)*60	// ��ȡ��ѫʱ��
#define TIMER_TIME_GET_MATCH_LIST	(60*1000)*60	// ��ȡ����ʱ��
#define TIMER_TIME_GENERATE_RANKING	(60*1000)*60	// ��ȡ����ʱ��
#define TIMER_TIME_GET_GAME_ROOM_INFO (60*1000)*10	// ��ȡ��Ϸ�ͷ���ʱ��


#define MAIN_TEST_USER_INFO		10	// ģ�������û���Ϣ
#define SUB_TEST_USER_INFO_01  101	// ��ʾ�û���Ϣ	
#define SUB_TEST_USER_INFO_02  102	// ����ʾ�û���Ϣ
#define SUB_HALL_LOGIN		 103	// ������½

#define MAIN_TEST_INTENSIVE     15	// ϵͳ�ܼ�������
#define SUB_TEST_INTENSIVE_01 1001	// �ܼ����ԣ��������ֱ�ӻط����Զ�
#define SUB_TEST_INTENSIVE_02 1003	// �ܼ����ԣ��򵥴�����ֱ�ӻط����Զ�

#define MAIN_TEST_DB  20				// �������ݿ�
#define SUB_TEST_DB_INTENSIVE				201	// �ܼ��������ݿ�
#define SUB_TEST_DB_COMPREHENSIVE			202	// �ۺϲ������ݿ�
#define SUB_TEST_REQUEST_USER_LIST			301	// �����û��б�
#define SUB_TEST_REQUEST_USER_LIST_OVER		302	// �û��б����

#define MAIN_TEST_IMMEDIATELY_CUT		25	// �յ������̶Ͽ�


/*
**author : add by cxf
**description:
******CS  -> �ͻ��˷�����������
******SC  -> �����������ͻ��˵�
******CSG -> �ͻ���/����������
******MAIN_MSG -> ����Ϣ
******SUB -> ����Ϣ
*/
#define MAIN_MSG_LOGIN						2000		// �û���¼����Ϣ
#define SUB_CS_USER_LOGIN					2101		// �û���¼����Ϣ
#define SUB_SC_USER_LOGIN_SUC				2102		// �û���¼�ɹ�
#define SUB_SC_USER_LOGIN_FINISH			2103		// �û���¼���
#define SUB_SC_GAME_LIST					2104		// ��Ϸ�б�
#define SUB_CSG_GAME_ROOM_LIST				2015		// �����б�
#define SUB_SC_GAME_ROOM_LIST_SEDN_FINISH	2016		// �����б������

#define SUB_CS_USER_REGISTER				2120		// �û�ע��
#define SUB_SC_USER_REGISTER_FINISH			2121		// �û�ע��ɹ�
#define SUB_CS_UPDATE_USER_IDENTITY			2122		// �޸��û����
#define SUB_CS_UPDATE_USER_IDENTITY_SUC		2123		// �޸��û�������
#define SUB_CS_UPDATE_USER_SYSLOGOID		2124		// �޸��û�ͷ��
#define SUB_CS_UPDATE_USER_SYSLOGOID_SUC	2125		// �޸��û�ͷ�����

#define MAIN_MSG_SYS						3000		// ϵͳ����Ϣ�������¼ʱ������ȵȣ�

#define MAIN_MSG_RANKING					4000		// �û�����
#define SUB_CSG_GET_FEATS_RANKING			4001		// ��ȡ��ѫ����
#define SUB_SC_GET_FEATS_RANKING_FINISH		4002		// ��ȡ��ѫ�������
#define SUB_CS_UPD_USER_FEATS_RANKING		4003		// ��ȡ�û���ѫ��������
#define SUB_SC_UPD_USER_FEATS_RANKING_SUC	4004		// ��ȡ�û���ѫ���������ɹ�
#define SUB_SC_UPD_USER_FEATS_RANKING_ERR	4005		// ��ȡ�û���ѫ��������ʧ��
#define SUB_CSG_GET_MATCH_RANKING			4006		// ��ȡ��������
#define SUB_SC_GET_MATCH_RANKING_FINISH		4007		// ��ȡ�����������
#define SUB_CS_UPD_USER_MATCH_RANKING		4008		// ��ȡ�û�������������
#define SUB_SC_UPD_USER_MATCH_RANKING_SUC	4009		// ��ȡ�û��������������ɹ�
#define SUB_SC_UPD_USER_MATCH_RANKING_ERR	4010		// ��ȡ�û�������������ʧ��


// ���е�¼������
#define	RET_LOGIN_OPERATE_SUCCEED			0			// �����ɹ�
// ��¼
#define	RET_USER_NOT_EXIST					10			// �û������������
// ע��
#define	RET_USER_NAME_EXIST					20			// �ʺ��Ѿ�����
#define RET_USER_NAME_IS_EMPTY				21			// �û���Ϊ��
#define	RET_USER_NICKNAME_EXIST				30			// �ǳ��Ѿ�����
// ��ȡ����
#define RET_RANKING_NOT_CURRENT_USER		40			// ������ȡ���˽���
#define RET_RANKING_IS_GET					50			// �����Ѿ���ȡ����
#define RET_RANKING_SEND_ID_NOT_EXIST		60			// ����ID������

// �û���¼
struct CMD_CS_UserLogin
{
	CMD_CS_UserLogin()
	{
		memset(this,0,sizeof(*this));
	}
	char		szName[USER_NAME_LEN];					// �ʺ�
	char		szPwd[USER_PASSWORD_LEN];				// ����
	char		szIp[IP_ADDRES_LEN];					// IP��ַ(��������)
	int			iGameID;								// ��ϷID(0:������¼;��0:��Ϸ��¼)
};

// �û���¼�ɹ�
struct CMD_SC_UserLoginInfo
{
	CMD_SC_UserLoginInfo()
	{
		memset(this, 0, sizeof(*this));
		iRet = -1;
	}
	int				iRet;								// ����״̬(0:�ɹ�;1:)
	LONGLONG		llUserID;							// �û�ID
	LONGLONG		llGold;								// ���
	LONGLONG		llPoint;							// ����
	char			szName[USER_NAME_LEN];				// �ʺ�
	char			szNickName[USER_NAME_LEN];			// �û��س�
	int				iSex;								// �Ա�
	LONGLONG		lSysLogoID;							// ͷ��ID
	LONGLONG		lExperience;						// ����ֵ
	char			szIdCardNo[USER_IDENTITY_CARD_LEN];	// ���֤����
	char			szIdCardName[USER_REAL_NAME_LEN];	// ���֤����
};

// ��Ϸ��Ϣ
struct CMD_SC_GAME_LIST
{
	CMD_SC_GAME_LIST()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iRet;								// ����ֵ
	int				iID;								// ��ϷID
	char			szGameName[GAME_NAME_LEN];			// ��Ϸ����
	char			szProgressName[PROGRESS_NAME_LEN];	// ��Ϸ�������ֳ���
	int				iGameType;							// ��Ϸ����
	int				iSortVal;							// ����
};

// ��ѫ��Ϣ
struct CMD_SC_FEATS_LIST
{
	CMD_SC_FEATS_LIST()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSortId;								// �б�ID
	int				iID;									// ID
	long long		lUserID;								// �û�ID
	char			szNickName[USER_NAME_LEN];				// �û��س�
	int				iRankingCode;							// ��������
	int				iRankingNo;								// ����
	int				iFeats;									// ��ѫ
	int				iRewardGold;							// �������
	int				iIsGet;									// �Ƿ��Ѿ���ȡ
};

// ��Ϣ
struct CMD_SC_MATCH_LIST
{
	CMD_SC_MATCH_LIST()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSortId;								// �б�ID
	int				iID;									// ID
	long long		lUserID;								// �û�ID
	char			szNickName[USER_NAME_LEN];				// �û��س�
	int				iRankingCode;							// ��������
	int				iRankingNo;								// ����
	int				iGameCoin;								// ���
	int				iRewardGold;							// �������
	int				iIsGet;									// �Ƿ��Ѿ���ȡ
};

// ��ȡ��ѫ����
struct CMD_CS_UPD_FEATS_RANKING_REWARD
{
	CMD_CS_UPD_FEATS_RANKING_REWARD()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSortId;								// �б�ID
	int				iID;									// ID
	long long		lUserID;								// �û�ID
	int				iRankingNo;								// ����
};

// ��ȡ��������
struct CMD_CS_UPD_MATCH_RANKING_REWARD
{
	CMD_CS_UPD_MATCH_RANKING_REWARD()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSortId;								// �б�ID
	int				iID;									// ID
	long long		lUserID;								// �û�ID
	int				iRankingNo;								// ����
};

// ��ȡ��ѫ�����ɹ�
struct CMD_SC_UPD_FEATS_RANKING_SUC
{
	CMD_SC_UPD_FEATS_RANKING_SUC()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iID;									// ID
	long long		lUserID;								// �û�ID
	int				iRewardGold;							// �������
};

// ��ȡ���������ɹ�
struct CMD_SC_UPD_MATCH_RANKING_SUC
{
	CMD_SC_UPD_MATCH_RANKING_SUC()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iID;									// ID
	long long		lUserID;								// �û�ID
	int				iRewardGold;							// �������
};

// ��ȡ��ѫ����ʧ��
struct CMD_SC_UPD_FEATS_RANKING_ERR
{
	CMD_SC_UPD_FEATS_RANKING_ERR()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		lUserID;								// �û�ID
	int				iRet;									// ʧ��ԭ��
};

// ��ȡ��������ʧ��
struct CMD_SC_UPD_MATCH_RANKING_ERR
{
	CMD_SC_UPD_MATCH_RANKING_ERR()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		lUserID;								// �û�ID
	int				iRet;									// ʧ��ԭ��
};

// �û���¼
struct CMD_CS_UserRegister
{
	CMD_CS_UserRegister()
	{
		memset(this,0,sizeof(*this));
	}
	char		szName[USER_NAME_LEN];					// �ʺ�
	char		szPwd[USER_PASSWORD_LEN];				// ����
	char		szNickName[USER_NAME_LEN];				// �ǳ�
	char		szIp[IP_ADDRES_LEN];					// IP��ַ(��������)
	int			iSex;									// �Ա�
	char		szIdCardNo[USER_IDENTITY_CARD_LEN];		// ���֤����
	char		szIdCardName[USER_REAL_NAME_LEN];		// ���֤����
};

// �޸����
struct CMD_CS_UpdateUserIdentity
{
	CMD_CS_UpdateUserIdentity()
	{
		memset(this,0,sizeof(*this));
	}
	long long	lUserID;								// �û�ID
	char		szIdCardNo[USER_IDENTITY_CARD_LEN];		// ���֤����
	char		szIdCardName[USER_REAL_NAME_LEN];		// ���֤����
};

// �޸���ݷ���
struct CMD_CS_UpdateUserIdentityRet
{
	CMD_CS_UpdateUserIdentityRet()
	{
		memset(this,0,sizeof(*this));
	}
	int			iRet;									// ����ֵ
	long long	lUserID;								// �û�ID
	char		szIdCardNo[USER_IDENTITY_CARD_LEN];		// ���֤����
	char		szIdCardName[USER_REAL_NAME_LEN];		// ���֤����
};

// �޸�ͷ��
struct CMD_CS_UpdateUserSyslogoid
{
	CMD_CS_UpdateUserSyslogoid()
	{
		memset(this,0,sizeof(*this));
	}
	long long	lUserID;								// �û�ID
	long long	lSyslogoid;								// ͷ��
};

// �޸�ͷ�񷵻�
struct CMD_CS_UpdateUserSyslogoidRet
{
	CMD_CS_UpdateUserSyslogoidRet()
	{
		memset(this,0,sizeof(*this));
	}
	int			iRet;									// ����ֵ(0��ȷ;!0����)
	long long	lUserID;								// �û�ID
	long long	lSyslogoid;								// ͷ��
};

// �û�ע��״̬
struct CMD_CS_UserRegisterRet
{
	CMD_CS_UserRegisterRet()
	{
		memset(this,0,sizeof(*this));
	}
	int				iRet;								// ����ֵ
};

// ��ȡ�����б�
struct CMD_CS_RequestRoomList
{
	CMD_CS_RequestRoomList()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iGameID;							// ��ϷID(���磺1����; 2������; 3�齫...)
};

// �����б�
struct CMD_SC_RoomList
{
	CMD_SC_RoomList()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		lParentId;							// ���ڵ㣨�ؿ� 1:������;2:�м���....��..
	int				iGameID;							// ��ϷID(���磺1����; 2������; 3�齫...)
	long long		lGameType;							// ��Ϸ����(1=���ַ��䡢2=�����Ϸ��3=������Ϸ)..
	int				iRoomId;							// ����ID
	long long		lRoomTeltComIp;						// ������й�����IP
	long long 		lRoomUnicomIp;						// ������й���ͨIP
	long long		lRoomMobileIp;						// ������й��ƶ�IP
	int				iRoomPort;							// ����˿�
	char			szRoomName[ROOM_NAME_LEN];			// ��������
	bool			bAutoSit;							// �Ƿ��Զ�����(0:���Զ�����Ҫ�ֶ������������ӽ���; 1:�Զ�����������Ҫ������Ӻ�)
	int				iBasePoint;							// ����..
	long long		lDoorsill;							// �����ż�(�����������ż����ܽ��뷿��)..
	int				iTables;							// �������ӵ�����
	int				iSeatNum;							// ÿ����������ÿ������λ����
	int				iEnterTradeGold;					// ������(���)
	int				iEnterTradePoint;					// ������(����)
	int				iRewardGold1;						// ��һ������
	int				iRewardGold2;						// �ڶ�������
};

// ��¼���ڲ�����
struct CMD_INNER_LoginConfig
{
	CMD_INNER_LoginConfig()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iListenPort;						// �����˿�
	int				iDbPort;							// ���ݿ�˿�
	char			szDbIp[IP_ADDRES_LEN];				// ���ݿ��ַ
	char			szDbUserName[DB_USER_NAME_LEN];		// ���ݿ��û���
	char			szDbUserPwd[DB_PASS_LEN];			// ���ݿ�����
	char			szDbName[DB_NAME_LEN];				// ���ݿ�����
};
// add end

struct TEST_USER_INFO	// ������
{
	TEST_USER_INFO(){	memset(this, 0, sizeof(*this));	}

	//// �����ʵ�ĳ���
	//int GetLen() 
	//{
	//	size_t iNameLen = 0;
	//	//StringCchLength(szName, _countof(szName), &iNameLen);
	//	StringCchLength(szName, sizeof(szName), &iNameLen);
	//	iNameLen++;  // ��������� 0 �ĳ���
	//	int iSize = (int)sizeof(*this) - (int)sizeof(szName) + (int)iNameLen*(int)sizeof(TCHAR);
	//	return iSize;
	//}

	int		iAge; 
	wchar_t	szName[128];
};

struct TEST_DB_QUERY
{
	TEST_DB_QUERY(){	memset(this, 0, sizeof(*this));	}

	int		iQueryType;		// ��ѯ������
	char	szContent[64];	// ����
};

#endif
