
#ifndef USER_INFO_H
#define USER_INFO_H

#include "./PublicMacro.h"
#include "./EasyDataTime.h"

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

struct EASY_DATA_TIME;

enum USER_STATE	// �û�״̬
{
	US_OFFLINE = 0,				// ���ߣ����ڷ�����
	US_ONLINE_LEAVE_SIT,		// ���ߣ��ڷ����������
	US_ONLINE_SITDOWN,			// ���ߣ��ڷ������������û����
	US_ONLINE_SITDOWN_RAISE,	// ����,�ڷ�����������Ѿ���
	US_ONLINE_PLAYLING,			// ����Ϸ��
	US_WAIT_RECONNECT,			// ���ߺ�ȴ�����
};

// �û����
enum UserIdentity
{// ��ݱ�ʶ����λ��ʾ00000001=1��ʾ�߼����,00000010=2��ʾһ������Ա........
	US_IDENTITY_HIGH_PLAYER = 1,				// �߼����(����Ϸ�п��Ի�ȡ����)
	//xxx					= 2,				// һ������Ա
	//xxx					= 4,				// ��������Ա
	//xxx					= 8,				// ��������Ա
	//....
};

// �ͻ��˵��û���Ϣ
struct USER_INFO
{
	USER_INFO()
	{
		memset(this, 0, sizeof(*this));

		lChannelNo = INVALID_CHANNEL_NO;
		lUserId = INVALID_USER_ID;
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
	}
	
	char				szName[USER_NAME_LEN];					// �û��ʺż���¼����
	char				szNickname[USER_NAME_LEN];				// �ǳ�
	char				szPassword[USER_PASSWORD_LEN];			// ��¼���룬MD5 ���ֵ
	char				szBankPassword[USER_PASSWORD_LEN];		// �������룬MD5 ���ֵ
	char				szIdentityCard[USER_IDENTITY_CARD_LEN];	// ���������

	EASY_DATA_TIME		stRegistTime;							// ע��ʱ��
	EASY_DATA_TIME		stLastLoginTime;						// ����½ʱ��

	int					iSex;									// �Ա�0���ԡ�1Ů��
	int					iRegisterIP;							// ע�� IP
	int					iLastLoginIP;							// ����½ IP
	int					iTableNo;								// ����
	int					iSeatNo;								// ��λ��
	int					iFeats;									// ��ѫ

	long long			lChannelNo;								// ͨ���ţ������ר��
	long long			lUserId;								// �û�ID
	long long			lClubId;								// ����ID�����Ź��ܿ��԰���һЩ���ӣ�ֻ�и����ų�Ա����������
	long long			lIdentity;								// ��ҵ���ݣ�һ������Ա����������Ա�������Ա�������Ա����ͨ��ҵ�
	long long			lMasterPower;							// ����Ȩ�ޣ������룩������������Ϣ��������Ϸ��Ϣ����ֹ��������Ϸ����������ߡ�����Ӽ���������ֹ�������� ��
	long long			lMasterPowerEx;							// ����Ȩ�ޣ���չ
	long long			lGamePower;								// �����ϷȨ�ޣ������룩��������Ϸ���졢��������Ϣ�����κ��Թ� ��
	long long			lGamePowerEx;							// �����ϷȨ�ޣ���չ��
	long long			lSysLogoID;								// ϵͳ�ṩ��ͷ��ϵ�С�
	long long			lExperience;							// ����ֵ
	long long			lAllLoginCounts;						// �ܵ�½����
	long long			lGoldLogin;								// ��¼ʱ�Ľ��ֵ
	long long			lPointLogin;							// ��¼ʱ�Ļ���
	long long			lNetGapTime;							// �û�����pingʱ��
	long long			lAntiAddictionTime;						// ������ʱ��
	long long			lAntiAddictionPlayTime;					// �û���������Ϸʱ��
	bool				bIsJuveniles;							// true:��δ����;false:������
	long long			lRevenue;								// ˰��
	int					iWinCount;								// Ӯ����
	int					iLostCount;								// ������
	USER_STATE			stUserState;							// �û�״̬
};

// �ͻ��˵��û���Ϣ
struct USER_INFO_SIM
{
	USER_INFO_SIM()
	{
		memset(this, 0, sizeof(*this));
		lUserId = INVALID_USER_ID;
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
	}

	long long	lUserId;						// �û�ID
	char		szName[USER_NAME_LEN];			// �û��ʺż���¼����
	char		szNickname[USER_NAME_LEN];		// �ǳ�
	char		szPassword[USER_PASSWORD_LEN];	// ��¼���룬MD5 ���ֵ
	int			iSex;							// �Ա�0���ԡ�1Ů��

	long long	lIdentity;						// ��ҵ���ݣ�һ������Ա����������Ա�������Ա�������Ա����ͨ��ҵ�
	long long	lMasterPower;					// ����Ȩ�ޣ������룩������������Ϣ��������Ϸ��Ϣ����ֹ��������Ϸ����������ߡ�����Ӽ���������ֹ�������� ��
	long long	lGamePower;						// �����ϷȨ�ޣ������룩��������Ϸ���졢��������Ϣ�����κ��Թ� ��
	long long	lSysLogoID;						// ϵͳ�ṩ��ͷ��ϵ�С�
	long long	lExperience;					// ����ֵ
	long long	lGoldLogin;						// ��¼ʱ�Ľ��ֵ
	long long	lPointLogin;					// ��¼ʱ�Ļ���
	int			iTableNo;						// ����
	int			iSeatNo;						// ��λ��
	USER_STATE	stUserState;					// �û�״̬
};

// �����б�
struct CMD_UserTaskInfo
{
	CMD_UserTaskInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	long long lUserId;	// �û�ID
	int iTaskId;		// ����ID
	int	iSchedule;		// ����ǰ��ɽ���ֵ	
};

// ������־
struct CMD_UserBattleRecord
{
	CMD_UserBattleRecord()
	{
		memset(this, 0, sizeof(*this));
	}
	int iResult;		// ���ֽ��(0:��;1:Ӯ;2:ƽ)
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif
