
#ifndef TABLE_INFO_H
#define TABLE_INFO_H

#include "./PublicMacro.h"

class CSingleUser;
//typedef int BOOL;	// ΢���ڶ�������

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

//--- �궨�����Ϣ�� -----------------------------------------------




//--- ö�� ---------------------------------------------------------


enum // ��Ϸϵͳ��״̬
{
	GAME_SYS_STATE_NO = 0,	// ��Ϸδ��ʼ
	GAME_SYS_STATE_RUNING,	// ��Ϸ������
	GAME_SYS_STATE_PAUSH,	// ��Ϸ���ᣬ����ͣ
};

enum  // ��Ϸ��ʼ������
{
	GAME_BEGIN_TYPE_AUTO = 0,	// �������������¶����Զ���ʼ
	GAME_BEGIN_TYPE_ONLY_ONE,// ֻҪ��һ�����¾Ϳ�ʼ
	GAME_BEGIN_TYPE_ALL_SIT,// ȫ�����²ſ�ʼ
	GAME_BEGIN_TYPE_ANY,// ��λ�����ڵ����⼸���˶����Կ��򣬱���2����Ҳ���Դ�������Ҳ���Դ�
};

//--- �ṹ ---------------------------------------------------------
struct SEAT_INFO;

// ������Ϣ
struct TABLE_INFO:public DATA_BASE<TABLE_INFO>
{
	TABLE_INFO() {	memset(this, 0, sizeof(*this)); }
	

	int	iTableNo;	// ����
	int	iSeatNum;	// ÿ����λ��
	int	iScenesID; // ����ID
};

// ��λ��Ϣ
struct SEAT_INFO:public DATA_BASE<SEAT_INFO>
{
	SEAT_INFO()
	{
		memset(this, 0, sizeof(*this)); 
	//	bFreeSeat = true;
		pSingleUser = NULL;
		bWarning = false;
	}

	//int			 iSeatNo;		// ��λ��
	//bool		 bFreeSeat;		// ����λ
	unsigned int nOperateTime;	// ����ʱ��		// add by cxf(����ʱ�����δ�������˳�����)
	bool		 bWarning;		// �Ƿ��͹���ʱ����
	CSingleUser* pSingleUser;	// �����û�
};

// ����
struct SITDOWN:public DATA_BASE<SITDOWN>
{
	enum
	{
		ERR_CAN_NOT_BEGIN = 1000,		// ���ܿ�ʼ��Ϸ
		ERR_CAN_NOT_SIT_DOWN = 1010,	// �����ֹ����״̬
	};

	SITDOWN()
	{
		memset(this, 0, sizeof(*this));
		lUserId = INVALID_USER_ID;
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
	}

	long long lUserId; 

	int iTableNo;	// ����
	int iSeatNo;	// ��λ��
	int iRes;		// ���ֵ
	//add by Ivan_han 20130713
	long long	lGoldLogin;		// ��¼ʱ�Ľ��ֵ
	long long	lPointLogin;	// ��¼ʱ�Ļ���

};

// ���֣����º����Ϣ���ͻ���Ҫ�ȵ���ʼ����Ϻ󣬷�����Ϣ������˲ŷ���
struct RAISE_HAND : public DATA_BASE<RAISE_HAND>
{
	RAISE_HAND()
	{
		memset(this, 0, sizeof(*this));
	}
	
	int iRes;		// ���ֵ
};

// ����
struct LEAVE_SEAT:public DATA_BASE<LEAVE_SEAT>
{
	LEAVE_SEAT(long long UserId=INVALID_USER_ID,int TableNo=INVAL_TABLE_NO,int SeatNo=INVAL_SEAT_NO) 
	{	
		memset(this, 0, sizeof(*this));	
		lUserId = UserId;
		iTableNo = TableNo;
		iSeatNo = SeatNo;
	}

	long long lUserId;

	int iTableNo;	// ����
	int iSeatNo;	// ��λ��
	int iRes;
};

// ��һ���������
struct TICK_ONE_LEAVE_SEAT:public DATA_BASE<TICK_ONE_LEAVE_SEAT>
{
	enum
	{
		TFLS_MGR_ERR = 1,	// �����߷Ƿ�
		TFLS_TABLE_ERR,		// ���ŷǷ�
		TFLS_SEAT_ERR,		// ���ŷǷ�
	};

	TICK_ONE_LEAVE_SEAT()
	{
		iRes = 0;
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
	}

	int iRes;
	int	iTableNo;		// ���ߵ�����
	int	iSeatNo;		// ���ߵ�����
};

// ��һ���������
struct TICK_TABLE_LEAVE_SEAT:public DATA_BASE<TICK_TABLE_LEAVE_SEAT>
{
	enum
	{
		TFLS_MGR_ERR = 1,	// �����߷Ƿ�
		TFLS_TABLE_ERR,		// ���ŷǷ�
	};

	TICK_TABLE_LEAVE_SEAT()
	{
		iRes = 0;
		iTableNo = INVAL_TABLE_NO;
		bWriteScore = false;
	}

	int iRes;
	int	iTableNo;		// ���ߵ�����
	bool bWriteScore;	// ������Ƿ�д��
};

// �������������������
struct TICK_ALL_LEAVE_SEAT:public DATA_BASE<TICK_ALL_LEAVE_SEAT>
{
	enum
	{
		TFLS_MGR_ERR = 1,	// �����߷Ƿ�
	};

	TICK_ALL_LEAVE_SEAT()
	{
		iRes = 0;
		bWriteScore = false;
	}

	int iRes;
	bool bWriteScore;	// ������Ƿ�д��
};

// 
struct CMD_SC_USER_DATA_CHANGE
{
	CMD_SC_USER_DATA_CHANGE()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lUserId;				// �û�ID
	int			iGold;					// �û����
	int			iPoint;					// �û�����
	int			iPresentBullet;			// �����ӵ�����
};

// ��������
struct CMD_SC_RECOMEAFTERCUT
{
	CMD_SC_RECOMEAFTERCUT()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lUserId;					// �û�ID
	int					iBuyBulletCount;	// �����ӵ�����
	int					iBulletCount;		// ʣ���ӵ�����
	int					iFeats;				// ��ѫ
	long long			lGameCoin;			// ���
	long long			lGoldChange;		// ���
	long long			lPointChange;		// ����
};

struct CMD_SC_ANTI_ADDICTION
{
	CMD_SC_ANTI_ADDICTION()
	{
		memset(this, 0, sizeof(*this));
	}
	long long lUserId;					// �û�ID
	char szContent[CHAT_CONTENT_LEN];	// ����
};

struct CMD_SC_MATCH_COUNTDOWN
{
	CMD_SC_MATCH_COUNTDOWN()
	{
		memset(this, 0, sizeof(*this));
	}
	int iMatchCountDown;
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif