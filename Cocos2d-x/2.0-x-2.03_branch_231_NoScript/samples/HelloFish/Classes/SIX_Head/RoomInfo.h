
#ifndef ROOM_INFO_H
#define ROOM_INFO_H

#include "./PublicMacro.h"

#include "UserInfo.h"

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

#define ROOM_GAME_TYPE_POINT					(1)						// ���ֳ�
#define ROOM_GAME_TYPE_GOLD						(2)						// ��ҳ�
#define ROOM_GAME_TYPE_MATCH					(3)						// ������

//--- ö�� ---------------------------------------------------------
enum ROOM_STATE	// ����״̬������������
{
	RS_CAN_LOGIN	= 0x0000000000000001,	// ��¼����
	RS_CAN_SIT		= 0x0000000000000002,	// ����
};

//--- �ṹ ---------------------------------------------------------

struct MY_TEST
{
	int a;
	int b;
};

struct ROOM_MGR_CONFIG	// ���������ļ�����
{
	ROOM_MGR_CONFIG()
	{
		iRoomMgrPort=6150;
		sprintf(DbIp, "127.0.0.1");
		iDbPort=3306; 
	}

	int iRoomMgrPort;			// ���ܼ����˿ڣ�������������
	char DbIp[IP_ADDRES_LEN];	// �������ӵ����ݿ�Ip
	int iDbPort;				// �������ӵ����ݿ�ļ����˿�
	char szDbUserName[DB_USER_NAME_LEN];		// ���ݿ��û�����
	char szDbUserPwd[DB_PASS_LEN];				// ���ݿ��û�����
	char szDbName[DB_NAME_LEN];					// ���ݿ�����
};

struct REQUEST_ROOM_INFO	// ���뷿����Ϣ
{
	REQUEST_ROOM_INFO() {	memset(this, 0, sizeof(*this)); }

	int	iRoomId;			// ����ID����Ψһ�ġ�ע��ǰ 100 ��ֵ��ϵͳ�ڲ�ʹ��
};

struct REQUEST_ROOM_ERR	// ���뷿����Ϣʧ��
{
	REQUEST_ROOM_ERR() {	memset(this, 0, sizeof(*this)); }

	int	iRoomId;	// ����ID����Ψһ�ġ�ע��ǰ 100 ��ֵ��ϵͳ�ڲ�ʹ��
	int	iRes;		// ʧ����
};

// ���ӵĿ�ܲ���
struct CLIENT_FRAME_PARAM:public DATA_BASE<CLIENT_FRAME_PARAM>
{
	CLIENT_FRAME_PARAM()
	{
		iMsgBlockSize = 2048;
		iSendHeartbeatTime = 30*1000;	// 30 �룬��׼Ĭ��ֵ;
		iShrinkPoolsTime = 3*60*1000;	// ��׼Ĭ��ֵ�ģ�5���ӣ�

		bAutoReConnect = true;
		iAutoReConnectTime = 2*1000;
	}

	int iMsgBlockSize;				// �ں���Ϣ��ĳ���
	long long iSendHeartbeatTime;	// ������������ʱ�䣬��λ�� ms
	long long iShrinkPoolsTime;		// �������ֳص�ʱ�䣬��λ�� ms

	bool bAutoReConnect;			// TRUE ��ʾ���ߺ��Զ�������FALSE ��ʾ���ߺ�������
	int  iAutoReConnectTime;		// ���������ļ��ʱ�䣬��λms
};

// ���ӷ��ܷ����� RMS��RoomMgrServer ���Ĳ���
struct CLIENT_TO_RMS_PARAM:public DATA_BASE<CLIENT_TO_RMS_PARAM>
{
	CLIENT_TO_RMS_PARAM(char *IP="127.0.0.1",int Port=6150,int MsgBlockSize=2048,int SendHeartbeatTime=30*1000,int ShrinkPoolsTime=3*60*1000,bool AutoReConnect=true,int AutoReConnectTime=2*1000)
	{ 
		_snprintf(szIP, sizeof(szIP)-1,"%s", IP);
		iPort = Port;

		iMsgBlockSize = MsgBlockSize;
		iSendHeartbeatTime = SendHeartbeatTime;	// 30 �룬��׼Ĭ��ֵ;
		iShrinkPoolsTime = ShrinkPoolsTime;	// ��׼Ĭ��ֵ�ģ�5���ӣ�

		bAutoReConnect = AutoReConnect;
		iAutoReConnectTime = AutoReConnectTime;
	}

	char szIP[IP_ADDRES_LEN];	// �������IP
	int	 iPort;					// ������Ķ˿�

	int iMsgBlockSize;				// �ں���Ϣ��ĳ���
	long long iSendHeartbeatTime;	// ������������ʱ�䣬��λ�� ms
	long long iShrinkPoolsTime;		// �������ֳص�ʱ�䣬��λ�� ms

	bool bAutoReConnect;			// TRUE ��ʾ���ߺ��Զ�������FALSE ��ʾ���ߺ�������
	int  iAutoReConnectTime;		// ���������ļ��ʱ�䣬��λms
};

struct ROOM_CONFIG	// ���������ļ�����
{
	ROOM_CONFIG()
	{
		memset(this, 0, sizeof(*this));
	}

	int		lRoomId;			// �������ID
	int		iLogicThreadNum;	// �����߼������߳�����
	int		iDbThreadNum;		// ���ݿ������߳�����

	char	szRoomMgrIp[IP_ADDRES_LEN];	// ����IP
	int		RoomMgrPort;				// ���ܼ����˿�
};

// �������� add by cxf
struct SERVER_ROOM_CONFIG
{
	SERVER_ROOM_CONFIG()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iId;										// ����ID
	int				iRoomId;									// ����ID
	int				iBeginMode;									// ��ʼģʽ(0û����Ҳ��ʼ��1���˽���Ϳ�ʼ��2���������Ϳ�ʼ)
	int				iStartNotEnter;								// ��Ϸ��ʼ���ܽ���(0:���ܽ���;1:�ܽ���);��:�������Ѿ��ڽ������ǲ��ܽ�����Ϸ�ġ�
	int				iEnterTradeGold;							// �����Ͻɱ������
	int				iEnterTradePoint;							// �����Ͻɱ�������
	int				iEnterPresentBullet;						// ���������ӵ�
	int				iGameTime;									// ÿ��������ʱ��
};

// ���佱�� add by cxf
struct SERVER_ROOM_REWARD
{
	SERVER_ROOM_REWARD()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iRoomId;									// ����ID
	int				iRewardGold1;								// ������ҵ�һ��
	int				iRewardGold2;								// ������ҵڶ���
};

// ����˵ķ�����Ϣ
struct SERVER_ROOM_INFO:public DATA_BASE<SERVER_ROOM_INFO>
{
	SERVER_ROOM_INFO() 
	{ 
		memset(this, 0, sizeof(*this)); 
		
		lRoomTeltComIp = 0x0100007F;	// 1.0.0.127 ��������й�����IP����Ҫ�ǿͻ��������ֵ������ inet_ntoa ������������ 127.0.0.1
		lRoomUnicomIp = 0x0100007F;		// 1.0.0.127 ��������й���ͨIP ��Ҳ��������ͨ��
		lRoomMobileIp = 0x0100007F;		// 1.0.0.127 ��������й��ƶ�IP

		iRoomPort = 5150;

		iOnlyReadDbIp = 0x6301A8C0;	// 99.1.168.192 ���� inet_ntoa ������������192.168.1.99
		iOnlyReadDbPort = 3306;

		iCanEnableRoom = 1;

		iTables = 10;	
		iSeatNum = 4;	

		iRoomVer = 0x00000001;
	}

	int			iRes;

	long long	lParentId;			// ���ڵ�ID��ͨ��������������Ķ�λ
	int			iRoomId;			// ����ID����Ψһ�ġ�ע��ǰ 100 ��ֵ��ϵͳ�ڲ�ʹ��

	char		szRoomName[ROOM_NAME_LEN];	// ��������
	int			iRoomPort;					// ����ļ����˿�

	long long	lRoomTeltComIp;	// ������й�����IP����Ҫ�ǿͻ��������ֵ
	long long	lRoomUnicomIp;	// ������й���ͨIP ��Ҳ��������ͨ�ȣ���Ҫ�ǿͻ��������ֵ
	long long	lRoomMobileIp;	// ������й��ƶ�IP����Ҫ�ǿͻ��������ֵ

	int			iOnlyReadDbIp;							// ����������ֻ�����ݿ�IP
	char		szOnlyReadDbName[DB_NAME_LEN];			// ����������ֻ�����ݿ����ƣ�ͨ���� six_devisions
	char		szOnlyReadDbUserName[DB_USER_NAME_LEN];	// ����������ֻ�����ݿ��û����ƣ�ͨ���� root
	char		szOnlyReadDbPass[DB_PASS_LEN];			// ����������ֻ�����ݿ�����

	int			iOnlyReadDbPort;	// ����������ֻ�����ݿ�����˿�

	int			iCanEnableRoom;		// 1 �����������أ�0 �˷����ѱ�����

	long long	lGameType;		// ��Ϸ���ͣ��Զ��ֽڵ�λ��ʾ���壺
	                            //     ��Ͷ��ֽڱ�ʾ���˿��ࡢ���ࡢ�����ࡣ
								//     �ٸ߶��ֽڱ�ʾ����ͨ��Ϸ�������Ϸ��������Ϸ����������Ϸ��cxf:1=���ַ��䡢2=�����Ϸ��3=������Ϸ��4=��������Ϸ

	int	iTables;		// �������ӵ�����
	int iSeatNum;		// ÿ����������ÿ������λ����

	int	iBasePoint;	// ��Ƶ��10������50������100����
	long long	lDoorsill;	// ������ż�������Ϊn ������Ҫn�Ļ��ֻ��Ҳ��ܽ��뷿�䡣

	long long	lRoomRule;		// ����������Ա���䡢��ַ���ơ������Թۡ��Զ����¡�������λ������ͬIP
	long long	lRoomRuleEx;	// ���������չ 

	char		szFightTable[FIGHT_TABLE_NAME_LEN];	// ս�������Ӧ�ı�����1���������Ϸͨ���� game_money��
													//                     2����������Ϸͨ���� match_x_x ��
													//                     3��������Ϸ�硰�����ڿӡ��� Cavern �����еġ������ڿӡ�������Ϸ���� Cavern ��

	int				iCanAutoOpenRoom;	// 1 ��ʾ�����Զ��������䣬0 ��ʾ��ֹ�Զ���������
	EASY_DATA_TIME	stOpenRoomTime;		// �Զ����������ʱ��
	int				iCanCloseRoom;		// 1 ��ʾ�����Զ��رշ��䣬0 ��ʾ��ֹ�Զ��رշ���
	EASY_DATA_TIME	stCloseRoomTime;	// �Զ��رշ����ʱ��

	
	char szRoomMessage[ROOM_MESSAGE_LEN];	// ��ҽ��뷿��ʱ���յ�����Ϣ��ʾ��
	char szGameMessage[GAME_MESSAGE_LEN];	// ��ҽ�����Ϸʱ���յ�����Ϣ��ʾ��

	int	iClientVer;	// �ͻ��˳����Ӧ�İ汾��
	int	iRoomVer;	// ��������Ӧ�İ汾��

	int	iRoomPeopleCount;

	SERVER_ROOM_CONFIG roomConfig;				// ��������
	SERVER_ROOM_REWARD roomReward;				// ���佱��
};

/*
author cxf
date 2013-07-06
description ������Ϣ����Ϣ
*/
struct SERVER_ROOM_INFO_SIM
{
	SERVER_ROOM_INFO_SIM()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lParentId;					// ���ڵ�ID��ͨ��������������Ķ�λ
	int			iRoomId;					// ����ID����Ψһ�ġ�ע��ǰ 100 ��ֵ��ϵͳ�ڲ�ʹ��
	long long	lGameType;					// ��Ϸ����: 1=���ַ��䡢2=�����Ϸ��3=������Ϸ��4=��������Ϸ��
	int			iBasePoint;					// ��Ƶ��10������50������100����
	long long	lRoomRule;					// ����������Ա���䡢��ַ���ơ������Թۡ��Զ����¡�������λ������ͬIP(��ʱû����)
	char		szRoomName[ROOM_NAME_LEN];	// ��������
	int			iTables;					// �������ӵ�����
	int			iSeatNum;					// ÿ����������ÿ������λ����
	int			iRoomPeopleCount;			// ��������
};
// �ͻ��˵ķ�����Ϣ
struct CLIENT_ROOM_INFO:public DATA_BASE<CLIENT_ROOM_INFO>
{
	CLIENT_ROOM_INFO(char *IP="",int Port=0,char *Name="",char *Password="") 
	{ 
		memset(this, 0, sizeof(*this)); 
		_snprintf(szIP,sizeof(szIP),"%s",IP);
		iPort = Port;

		_snprintf(szName,sizeof(szName),"%s",Name);
		_snprintf(szPassword,sizeof(szPassword),"%s",Password);
	}

	char szIP[IP_ADDRES_LEN];	// �������IP
	int	 iPort;					// ������Ķ˿�

	char szName[USER_NAME_LEN];			// �û���
	char szPassword[USER_PASSWORD_LEN];	// ���ܺ�����룬������ MD5 ���ܺ󲻿��������

	
};

// ��¼����
struct LOGIN_ROOM:public DATA_BASE<LOGIN_ROOM>
{
	LOGIN_ROOM()
	{ 
		memset(this, 0, sizeof(*this)); 
	}
	long long lUserID;
	char szName[USER_NAME_LEN];			// �û���
	char szPassword[USER_PASSWORD_LEN];	// ���ܺ�����룬������ MD5 ���ܺ󲻿��������
};

// ��¼����ɹ�
struct LOGIN_ROOM_SUCC
{
	LOGIN_ROOM_SUCC() 
	{ 
		memset(this, 0, sizeof(*this)); 
		bAlreadyInRoom = false;
	}

	// ���԰���һЩ�������Ϣ

	char szIP[IP_ADDRES_LEN];	// �������IP
	int	 iPort;					// ������Ķ˿�
	bool bAlreadyInRoom;		// �Ѿ��ڷ�������

	USER_INFO_SIM userInfo;	// �û���
};

struct RECOME_AFTER_CUT	// ��������
{
	RECOME_AFTER_CUT()
	{
		memset(this, 0, sizeof(*this)); 

		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
		bAlreadyInRoom = true;
	}

	int	 iErrCode;	// ����¼�ǳɹ�������0ֵ��
					// ���ǵ�¼ʧ�ܣ����ط�0ֵ�Ĵ��������£�

	int	 iPort;				// ������Ķ˿�

	bool bAlreadyInRoom;	// �Ѿ��ڷ�������
	int iTableNo;	// ����
	int iSeatNo;	// ��λ��

	char szName[USER_NAME_LEN];			// �û���
};

// ��¼����ʧ��
struct LOGIN_ROOM_FAIL:public DATA_BASE<LOGIN_ROOM_FAIL>
{
	enum
	{
		ERR_CAN_NOT_LOGIN = 10,	// �����ֹ��¼״̬
		ERR_01 = 20,				// �û��������벻�����򲻴��ڸ��û�
		ERR_02 = 30,				// �û�����Ψһ
		ERR_30 = 40,				// ������������û�ʧ��
	};

	LOGIN_ROOM_FAIL() { memset(this, 0, sizeof(*this)); }

	int	 iErrCode;	// ����¼�ǳɹ�������0ֵ��
					// ���ǵ�¼ʧ�ܣ����ط�0ֵ�Ĵ��������£�
};

// �뿪����Ľ��
struct LEAVE_ROOM_RESULT:public DATA_BASE<LEAVE_ROOM_RESULT>
{
	LEAVE_ROOM_RESULT() { memset(this, 0, sizeof(*this)); }

	USER_INFO userInfo;
	int	 iErrCode;	// ����¼�ǳɹ�������0ֵ��
					// ���ǵ�¼ʧ�ܣ����ط�0ֵ�Ĵ��������£�
};

struct MANAGER_POWER_ERR:public DATA_BASE<MANAGER_POWER_ERR>	// �޴˹���Ȩ��
{
	MANAGER_POWER_ERR()
	{
		iWantPower = 0;
	}
	int iWantPower;		// ��ʩ�ӵ�Ȩ��
};


// ������뷿
struct TICK_USER_OUT_ROOM:public DATA_BASE<TICK_USER_OUT_ROOM>
{
	enum
	{
		TUOR_NO_FIND = 10,			// �����޴���ң���������û��¼����
		TUOR_TABLE_ERR = 15,		// ���ŷǷ�
		TUOR_SEAT_NO_USER = 20,		// ������û����
	};

	enum
	{
		TICK_BY_TABLE_SEAT = 10,	// �����š�������
		TICK_BY_NAME = 20,			// ��������
		TICK_BY_TABLE = 30,			// �������ߣ���һ�������뷿
		TICK_BY_ALL = 40,			// �����е����뷿
	};

	TICK_USER_OUT_ROOM()
	{
		iRes = 0;
		iTickMode = TICK_BY_TABLE_SEAT;
		bWriteScore = false;	
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
		memset(szName, 0, sizeof(szName));
	}

	int iRes;			// �ߵĽ��
	int iTickMode;		// �ߵķ�ʽ���ο� TICK_BY_TABLE_SEAT ��
	bool bWriteScore;	// ������Ƿ�д��ұ仯ֵ
	int	iTableNo;		// ���ߵ�����
	int	iSeatNo;		// ���ߵ�����
	
	char szName[USER_NAME_LEN];			// �û���
};

// д��ұ仯ֵ
struct CMD_WRITE_SCORE:public DATA_BASE<CMD_WRITE_SCORE>
{
	CMD_WRITE_SCORE() 
	{ 
		memset(this, 0, sizeof(*this)); 
		lUserId = INVALID_USER_ID;
		lChannelNo = INVALID_CHANNEL_NO;
	}

	long long	llType;			// ���ͣ����ֱ���ұ�
	long long	lUserId;		// ������Ҫ��������û����������ܲ�������ͨ����ȥ�������ݿ�
	long long	lChannelNo;		// ����Һ���Ϣ��ӷ��ܷ���������ʱ CSingleUser* ���Ѿ��������������Ա���Ҫ�ӷ��ܴ�����ҵ�ͨ��
	long long	lGold;			// ��ҵı仯��
	long long	lPoint;			// ���ֵı仯��
	long long	llGameCoin;		// ��ұ���
	int			iBasePoint;		// ���䱶��
	int			iBuyBulletCount;// �����ӵ�����
	int			iBulletCount;	// ʣ���ӵ�����
	int			iTableNo;		// ���Ӻ�
	int			iRoomNo;		// �����
	int			iFeats;			// ��ѫ
	long long	lAntiAddictionTime;// ������ʱ��
	long long	lAntiAddictionPlayTime;// ��������Ϸʱ��
};

// д��ұ仯ֵ���
struct WRITE_SCORE_RESULT:public DATA_BASE<WRITE_SCORE_RESULT>
{
	WRITE_SCORE_RESULT()
	{	
		memset(this, 0, sizeof(*this)); 
		lUserId = INVALID_USER_ID;
	}

	int			iRes;
	LONGLONG	lUserId;		// ������Ҫ��������û����������ܲ�������ͨ����ȥ�������ݿ�
	LONGLONG	lGold;			// ��ǰ�ķ�ֵ
	LONGLONG    lPoint;			// ����
};

// ƴ�����ӳ�
struct CMD_NET_GAP_TIME
{
	CMD_NET_GAP_TIME()
	{
		memset(this,0,sizeof(*this));
	}
	long long		llUserID;				// �û�ID
	long long		llSendTime;				// ����ʱ��
};

// �Ŷ�
struct CMD_USER_ARRANGE_QUEUE_LIST
{
	CMD_USER_ARRANGE_QUEUE_LIST()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lUserId;				// �û�ID
	long long	lChannelNo;				// �û�ͨ��
};

// �Ŷ����
struct CMD_USER_ARRANGE_QUEUE_FINISH
{
	CMD_USER_ARRANGE_QUEUE_FINISH()
	{
		memset(this,0,sizeof(*this));
	}
	int				iRet;				// �Ŷ�״̬
};

// ȡ���Ŷ����
struct CMD_USER_CANCEL_ARRANGE_QUEUE_FINISH
{
	CMD_USER_CANCEL_ARRANGE_QUEUE_FINISH()
	{
		memset(this,0,sizeof(*this));
	}
	int				iRet;				// ȡ��״̬
};


// д��
struct CMD_MatchAccounts
{
	CMD_MatchAccounts()
	{
		memset(this,0,sizeof(*this));
	}
	long long			lUserID;						// �û�ID
	long long			lGoldChange;					// �䶯���
	long long			lPointChange;					// �䶯����
	long long			lGameCoin;						// ��Ϸ��
	int					iRewardGold;					// �������
	int					iTableNo;						// ���Ӻ�
	int					iRoomID;						// �����
	long long			lAntiAddictionTime;				// ������ʱ��
	long long			lAntiAddictionPlayTime;			// ��������Ϸʱ��
};

//OnAntiAddiction�Ƿ����÷�����
struct CMD_Anti_Addiction
{
	CMD_Anti_Addiction()
	{
		memset(this,0,sizeof(*this));
	}
	bool bIsAntiAddiction;
};

struct CMD_RoomUserCount
{
	CMD_RoomUserCount()
	{
		memset(this,0,sizeof(*this));
	}
	int iRoomUserCount;								// ��������
	int iArrangeQueueCount;							// �Ŷ�����
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif