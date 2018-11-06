
/*
**�������ڲ�ʹ��ͷ�ļ�
**description:
**    C		 -> ���ķ�����
**	  L		 -> ��¼������
**    G		 -> ��Ϸ������
**    D		 -> ���ݿ������
**    F		 -> ��ѯ������
**    P		 -> ����������
**    **G	 -> ��������Ϣ

**    (LC)         -> ��¼�������������ķ�����
**    (GC)         -> ��Ϸ�������������ķ�����
**    (DC)         -> ���ݿ�������������ķ�����
**    (DCG)        -> ���ݿ�������������ķ�����/���ķ������������ݿ������
******MAIN		   -> �ڲ�����������Ϣ
******SUB		   -> �ڲ�����������Ϣ
*/

#include "PublicMacro.h"

#ifndef CMD_INNER_SERVER_H
#define CMD_INNER_SERVER_H

// ��¼������Ϣ
#define MAIN_LCG_LOGIN										10000
#define SUB_LC_LOGIN_REGISTER								10001		// ��¼������ע��
#define SUB_CL_GAME_REGISTER_NOTIFY							10002		// ��Ϸ������ע��֪ͨ
#define SUB_CL_PLAZA_REGISTER_NOTIFY						10003		// ����������ע��֪ͨ
#define SUB_CL_GAME_CLOSE_NOTIFY							10004		// ��Ϸ�������ر�֪ͨ
#define SUB_CL_PLAZA_CLOSE_NOTIFY							10005		// �����������ر�֪ͨ

// DB������Ϣ
#define MAIN_LCG_WRITEDB									11000
#define SUB_LC_WRITEDB_REGISTER								11001

// ����������Ϣ
#define MAIN_PCG_PLAZA										12000
#define SUB_PC_PLAZA_REGISTER								12001

// ��Ϸ������Ϣ
#define MAIN_GCG_GAME										13000
#define SUB_GC_GAME_REGISTER								13001

enum // ��Ϸ
{
	GAME_FISH = 1,		// ������Ϸ
	GAME_SANGONG = 2,	// ������Ϸ
	GAME_NIUNIU = 3,	// ţţ��Ϸ
	GAME_SHIDIANBAN = 4,// ʮ�����Ϸ
};


// �������ر�֪ͨ
struct CMD_ServerCloseNotify
{
	CMD_ServerCloseNotify()
	{
		memset(this, 0, sizeof(*this));
	}
	long long lHandleId;
};

// ��¼������ע��
struct CMD_Login_Register
{
	CMD_Login_Register()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lChannelNo;				// ͨ����
	int			iPort;					// �˿�
};

// DB������ע��
struct CMD_WriteDbServer_Register
{
	CMD_WriteDbServer_Register()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lChannelNo;				// ͨ����
	int			iPort;					// �˿�
};

// DB������ע��
struct CMD_PlazaServer_Register
{
	CMD_PlazaServer_Register()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lChannelNo;				// ͨ����
	int			iPort;					// �˿�
	char		szIp[IP_ADDRES_LEN];	// IP
};

// ��Ϸ
struct CMD_GameServer_Register
{
	CMD_GameServer_Register()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		lChannelNo;							// ͨ����

	long long		lParentId;							// ���ڵ㣨�ؿ� 1:������;2:�м���....��..
	int				iGameID;							// ��ϷID(���磺1����; 2������; 3�齫...)
	int				iRoomType;							// ��Ϸ����(1=���ַ��䡢2=�����Ϸ��3=������Ϸ)..
	int				iRoomId;							// ����ID
	long long		lRoomTeltComIp;						// ������й�����IP
	long long 		lRoomUnicomIp;						// ������й���ͨIP
	long long		lRoomMobileIp;						// ������й��ƶ�IP
	int				iRoomPort;							// ����˿�
	char			szRoomName[ROOM_NAME_LEN];			// ��������
	bool			bAutoSit;							// �Ƿ��Զ�����(0:���Զ�����Ҫ�ֶ������������ӽ���; 1:�Զ�����������Ҫ������Ӻ�)
	int				iBasePoint;							// ����..
	int				iDoorsill;							// �����ż�(�����������ż����ܽ��뷿��)..
	int				iMaxDoorsill;						// ��߽����ż�(�����������ż����ܽ��뷿��)..
	int				iTables;							// �������ӵ�����
	int				iSeatNum;							// ÿ����������ÿ������λ����

	int				iEnterTradeGold;					// ������(���)
	int				iEnterTradePoint;					// ������(����)
	int				iRewardGold1;						// ��һ������
	int				iRewardGold2;						// �ڶ�������
	int				iPlayerCount;						// ��Ϸ����
};

#endif