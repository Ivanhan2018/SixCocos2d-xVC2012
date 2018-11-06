#ifndef PRO_FISH_H
#define PRO_FISH_H
#include <string.h>
#include "DB_Head.h"
#include "PublicMacro.h"
#include <map>
using namespace std;

//////////////////////////////////////////////////////////////////////////
//��غ궨��

#define GAME_PLAYER_COUNT			(4)									// ��Ϸ����

#define MAX_HIT_FISH_COUNT    5//�����ڵ����������ĸ���
#define CCP(pt) ccp(pt.x,pt.y)
//add by Ivan_han 20130724
//#define MAKE32(Lo16,Hi16)      ((unsigned int)(((unsigned short int)(Lo16)) | ((unsigned int)((unsigned short int)(Hi16))) << 16))
//#define LO16(l)           ((unsigned short int)(((unsigned int)(l)) & 0xffff))
//#define HI16(l)           ((unsigned short int)((((unsigned int)(l)) >> 16) & 0xffff))
//////////////////////////////////////////////////////////////////////////////////
typedef unsigned int TSeaSceneKind;    //���׳�����
typedef unsigned int TGunGrade;  //�ڵĵȼ���Ҳ��Ϊ������
typedef unsigned short int TFishKind;    //���1-99
typedef unsigned int TFishMulti;    //��ı���
typedef unsigned long long TBulletID;	 //һ���ڵ���ʶ
typedef unsigned int TFishID;    //һ�����ʶ
typedef unsigned int TTableID;   //���Ӻ�
typedef unsigned int TChairID;   //���Ӻ�
typedef float TAngle; //����Ƕ�
typedef unsigned short int TFishPathType;    //��켣����<1ֱ�ߣ�2Բ��3���ߣ�4�������ߣ�5���ױ��������ߣ�6�����׵�����>
typedef unsigned short int TFishGroupType;    //��Ⱥ��������<0���㣬1Բֱ����LtoR��2-4����ֱ����LtoR��5����ֱ����LToR��11-15ֱ����RToL����Ⱥ������101��ʼ>�����ⷢ�ظ���Ⱥ������ķ������Ҫ�õ�
typedef unsigned int TFishGroupID;    //����ID���շ��������ʱ�õ�
typedef unsigned char TFishMoveSecs;//��켣ʱ����Ҳ�����������ʱ��
typedef unsigned char TFishMoveStatus;//��켣״̬<0����״̬��1��켣�����Ҳ��ɲ���״̬��2��켣�����䲻ͬ�����ɲ���״̬>�����㳡��->���󳡾�ʱ�õ�
typedef unsigned char TFishNumOfAck;//�㱻���������������㷨Ҫ�õ�
typedef unsigned long long TBuildTraceTime;//�������˹켣����ʱ��ms
typedef long long TFallIntegral;//���������������(>=0)
typedef long long TWinIntegral;//�۳��ڵ��ɱ���Ӯ�Ļ���
//typedef unsigned int TFishKindNum;//ͳ�����ʱ�õ���FishKindNum=FishKind(4)+Num(4)

const int SCENES_MIN = 1;			// ����ID ��Сֵ
const int SCENES_MAX = 4;			// ����ID ���ֵ

struct qcPoint
{
	float x, y;
	qcPoint() : x(0), y(0) {}
	qcPoint(float _x, float _y) : x(_x), y(_y) {}
	qcPoint& operator= (const qcPoint& point) {x = point.x; y = point.y; return *this;}
};

typedef qcPoint TPoint;


///////////////////////////////////////////////////////////////////////////////

/**************************************************************************
//���㷿�������
**************************************************************************/
enum PROTOCOL_FISH
{
	TABLE_SUB_BUY_BULLET				= 210,	// �����ӵ�
	TABLE_SUB_BUY_BULLET_RET			= 220,	// �����ӵ�����
	TABLE_SUB_EXCHANGE_INFO_RET			= 250,	// ���ضһ���Ϣ
	//TABLE_SUB_USER_INFO					= 260,	// �û���Ϣ	
	TABLE_SUB_USER_OVERTIME				= 271,	// �û���ʱ�˳�


	REQ_BUY_BULLET=400,									//�����ӵ�
	REQ_USER_SHOOT,									//�����ڵ�
	REQ_CAPTURE_FISH,									//��������
	REQ_GET_SCORE_INFO,								//������Ϣ
	REQ_SET_PROPABILITY,								//���ø���
	REQ_CALC_SCORE,									//�������
	REQ_SET_GUNGRADE,								//�����ڵĵȼ���add by Ivan_han 20130724
	REQ_HIT_FISH,										//������Ⱥ
	REQ_OPEN_BOSSBOX,                                 //�򿪱���
	REQ_SHOOT_FORCECANNON,                            //ʹ��������

	RSP_GAME_SCENE=500,									//������Ϣ
	RSP_ADD_ONE_FISH,                                    //���һ����켣
	RSP_ADD_ONE_FISH_LIST_UNFINISH,						//���һ����켣�󣬴������δ�������
	RSP_ADD_ONE_FISH_LIST_FINISH,						//���һ����켣�󣬴�������ѷ������
	RSP_ADD_ONE_FISH_ARR,								//���һ����켣��
	RSP_ADD_ONE_FISH_LIST,								//���һ����켣��
	RSP_USER_SHOOT,									//�����ڵ�
	RSP_CAPTURE_FISH,									//������Ⱥ
	RSP_BULLET_COUNT,									//�ӵ���Ŀ
	RSP_COIN_COUNT,									//�����Ŀ
	RSP_FISH_COUNT,									//��Ⱥ��Ŀ
	RSP_CHANGE_SCENE,									//�л��������ǳ���������->�����ڣ���add by Ivan_han 20130806
	RSP_SET_GUNGRADE,								//�����ڵĵȼ���add by Ivan_han 20130724
	RSP_BONUS_INFO,									//�ʽ���Ϣ
	RSP_GAME_MESSAGE,									//��Ϸ��Ϣ
	RSP_GET_PROP,                                     //��õ���
	RSP_OPEN_BOSSBOX,                                 //�򿪱���
	RSP_SHOOT_FORCECANNON,                            //ʹ��������
	// Ϊ�˷�ֹ��ϢID�ظ�������ϢID��600��ʼ���ܴ��ڵ���2000 (��Ϊ��GameSkeletonMsgCode.h��Ҳ�õ���������Ϣ)
};

//���Ӵ�����		// add by cxf
enum GAME_RETURN_CODE
{
	RET_GAME_OPERATE_SUCCEED				= 0,		// �����ɹ�
	RET_GAME_USER_NOT_EXIST					= 10,		// �û�������
	RET_GAME_BUY_BULLET_GOLD_LACK			= 20,		// ��Ҳ��������ӵ�
	RET_GAME_ERROR_CODE_BULLET_LACK			= 30,		// ȱ���ӵ�
	RET_GAME_BUY_BULLET_FAIL				= 40,		// �����ӵ�ʧ��
};

//�л��������ǳ�
struct Rsp_ChangeScene
{
	TSeaSceneKind SeaSceneKind;
	bool          bRToL;       //��ʱ������Ϊtrue
};

//��һ��ָ���켣����,�μ�CFishMgr:addOneFish
struct Rsp_AddOneFish
{
    Rsp_AddOneFish(){memset(this, 0, sizeof(*this));}
	TTableID TableID;

	TFishKind FishKind;
	TFishPathType FishPathType;

	TFishGroupType FishGroupType;
	TFishMoveStatus FishMoveStatus;
	TFishNumOfAck FishNumOfAck;

	TFishMoveSecs FishMoveSecs;
	TFishMoveSecs FishEntryTime;
	TFishMoveSecs FishDepartureTime;
	TFishMoveSecs reserved;

	TBuildTraceTime BuildTraceTime;
	TFishID FishID;
	TPoint	startP;
	TPoint  arg1;
	TPoint  arg2;
	TPoint  arg3;
};

//�����ڵĵȼ�
struct Req_SetGunGrade
{
	Req_SetGunGrade(){memset(this, 0, sizeof(*this));}
	long long		llUserID;// �û�ID
	TGunGrade		GunGrade;
	//S->Cʹ�õ��ֶ�
	int iRes;
};

//��һ��ָ���켣����,�μ�CFishMgr:addOneGroupFish
struct Rsp_AddOneFish_Arr
{
	Rsp_AddOneFish_Arr(){memset(this, 0, sizeof(*this));}
	TTableID TableID;
	unsigned int nFishCount;
	Rsp_AddOneFish Arr[20];
};

//��һ��ָ���켣����,�μ�CFishMgr:addOneGroupFish
struct Rsp_AddOneFish_List
{
	Rsp_AddOneFish_List(){memset(this, 0, sizeof(*this));}
	//TTableID TableID;
	TFishGroupID FishGroupID;
	unsigned int nFishCount;
	unsigned int nTotalFishCount;//��������е�������
	inline Rsp_AddOneFish & operator [](unsigned int);
	int getLength()const{return sizeof(*this) + nFishCount * sizeof(Rsp_AddOneFish);}
};

inline Rsp_AddOneFish & Rsp_AddOneFish_List::operator [](unsigned int index)
{
	return ((Rsp_AddOneFish *)((unsigned char *)this + sizeof(*this)))[index];
}

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
// ����
const int BULLET_REFLECTION_MAX = 3; // �ӵ�����������
struct SHOT_FIRE
{
	SHOT_FIRE(TBulletID iID,long long iUserID,int iBulletNum,int iBulletType,TGunGrade iGunType,int iRes,
		TPoint fDesPT, TPoint fPlayerPos, bool bRepeatShoot,bool bHaveCarry=false)
	{
		memset(this, 0, sizeof(*this));
		this->bHaveCarry = bHaveCarry;
		this->bRepeatShoot = bRepeatShoot;
		this->iID = iID;
		this->iUserID = iUserID;
		this->iBulletNum = iBulletNum;
		this->iBulletType = iBulletType;
		this->iGunType = iGunType;
		this->iRes = iRes;
		this->fDesPT = fDesPT;
		this->fPlayerPos = fPlayerPos;
	}
	SHOT_FIRE()
	{
		memset(this, 0, sizeof(*this));
	}
	bool bHaveCarry;		// �����
	bool bRepeatShoot;		// �������䣨��ֹ���Ʒ���������أ�
	int iTableNo;			// ����
	int iSeatNo;			// ��λ��
	int iBulletNum;			// �ӵ�����
	int iBulletType;		// �ӵ�����
	TGunGrade iGunType;		// �ڹ�����
	int iRes;	
	TBulletID iID;		// �ӵ�ID
	long long iUserID;		// �û�ID
	TPoint fDesPT;			// �ӵ�Ŀ�ĵ�X����
	TPoint fPlayerPos;		// �������
	int iUserBulletCount;	// �û��ӵ�����
};

// �ӵ�����
struct BULLET_REFLECTION
{
	BULLET_REFLECTION()
	{	
		memset(this, 0, sizeof(*this)); 
		iReflectionMax = BULLET_REFLECTION_MAX;
	}

	int iRes;	
	int iReflectionCount;			//�������
	int iReflectionMax;			//����������
	float fMoveTime;				// �ƶ�ʱ��
	float fCurRotation;			// ��ǰ�Ƕ�
	TBulletID llID;					// �ӵ�ID
	long long llUserID;			// �û�ID
	TPoint fCurPos;					// �ӵ���ǰλ�ã���ײ��collidePT
	TPoint fMovePos;				// �ӵ�Ҫ�ƶ�����λ�ã����䷽��(�����������)newMoveBy
};

/// ������
struct CAPTURE_FISH
{
	CAPTURE_FISH() {	memset(this, 0, sizeof(*this));	}
	int iRes;
	TBulletID llBulletID;
	long long llUserID;
	unsigned int nFishCount;//��ײ��⵽��������
	TFishID FishIDs[12];
	//add by Ivan_han 20130724��S->C���ذ��õ�
	TFishID DeadFullScreenBombFishID;//DeadFullScreenBombFishID=0��ʾû�л���ȫ��ը��
	unsigned int FishKindNums[19];//����0-18��Ӧ���������Ϊ1,2,3,4,5,6,7,8,9,10,15,18,20,25,30,40,12,112,113
	TFallIntegral FallIntegral;
	TGunGrade GunGrade;
	long long  llUserGameCoinCount;  // �û��������
	unsigned int nDeadFishCount;//��������
	inline TFishID & operator [](unsigned int);
	int getLength()const{return sizeof(*this) + nDeadFishCount * sizeof(TFishID);}
};

inline TFishID & CAPTURE_FISH::operator [](unsigned int index)
{
	return ((TFishID *)((unsigned char *)this + sizeof(*this)))[index];
}

//add by Ivan_han 20130718
struct CAPTURE_FISH_MAX :public CAPTURE_FISH
{
	TFishID m_DeadFishIDs[300];
	void SetData(const vector<TFishID> & vDeadFish)
	{
		nDeadFishCount=(vDeadFish.size()>300?300:vDeadFish.size());
		for(unsigned int i=0;i<nDeadFishCount;i++)
			m_DeadFishIDs[i]=vDeadFish[i];
	}
};


/// ������������ӵ�����
struct BULLET_DATA
{
	BULLET_DATA() { memset(this, 0, sizeof(*this)); }
	void SetFire(SHOT_FIRE *pFire)
	{
		Fire = *pFire;
	}
	void SetReflection(BULLET_REFLECTION *pReflection)
	{
		// Reflection = *pReflection; //del cxf
		Reflection.iRes = pReflection->iRes;
		Reflection.fMoveTime = pReflection->fMoveTime;					// �ƶ�ʱ��
		Reflection.fCurRotation = pReflection->fCurRotation;			// ��ǰ�Ƕ�
		Reflection.llID = pReflection->llID;							// �ӵ�ID
		Reflection.llUserID = pReflection->llUserID;					// �û�ID
		Reflection.fCurPos = pReflection->fCurPos;						// �ӵ���ǰλ��
		Reflection.fMovePos = pReflection->fMovePos;					// �ӵ�Ҫ�ƶ�����λ��
	}

	SHOT_FIRE Fire;
	BULLET_REFLECTION Reflection;
	unsigned int nCurrTime;			// ��ǰ�ӵ�����ʱ��
};
typedef std::map<long long, BULLET_DATA *> MAP_BULLET;

/// ��ʼ��Ϸ
struct INIT_GAME
{
	INIT_GAME()
	{
		iScenesID = 0;
		tServerTime = 0;
		tCurrentServerTime=0;
	}

	int iScenesID;									///< ����ID
	unsigned int uiBulletMaxCount;						///< ��������ӵ������Ŀ
	unsigned long long tServerTime;							///< ����������������ʱ�̣�����SK��
	unsigned long long tCurrentServerTime;					///< ����������������ʱ�̣�����ST����ע��CEasyDataTime::get_current_time_diff_millitm_from_1970()���صĲ��ǵ�ǰ��ʵʱ����1970��1��1�յĺ����ֵ
};

/*
author cxf
description �����ӵ�		
*/
struct USER_BUY_BULLET
{
	USER_BUY_BULLET()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		llUserID;					// �û�ID
	int				iBulletNum;					// �����ӵ�����
};

/*
author cxf
description �����ӵ�������Ϣ		
*/
struct USER_BUY_BULLET_RET
{
	USER_BUY_BULLET_RET()
	{
		memset(this, 0, sizeof(this));
	}

	int				iRes;						// ����״̬(0:�ɹ�;10:�û�����;20:��Ҳ���;)
	long long		llUserID;					// �û�ID
	int				iSeatNo;					// ���Ӻ�
	int				iBulletNum;					// �����ӵ�����
	long long		llGold;						// ��������
	long long		llPoint;					// �������
};

/*
author cxf
description �һ���Ϣ
*/
struct USER_EXCHANGE_INFO
{
	USER_EXCHANGE_INFO()
	{
		memset(this, 0, sizeof(*this));
	}

	int				iRes;						// ����״̬(0:�ɹ�;10:�û�����;20:��Ҳ���;)
	long long		llUserID;					// �û�ID
	int				iSeatNo;					// ���Ӻ�
	int				iBulletNum;					// �ӵ�����
	int				iBulletScore;				// �ӵ����Զһ������
	long long		llGameCoin;					// ���
	long long		llGameCoinScore;			// ��ҿ��Զһ������
	long long		llGold;						// ��������
};

// ��ʱ�Ͽ�ʣ��
struct USER_OVERTIME_SURPLUS
{
	USER_OVERTIME_SURPLUS()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSurplusTime;				// �Ͽ�����ʣ��ʱ�� (��Ϊ��λ)
};

// �����û���Ϣ
struct CMD_GameUserInfo
{
	CMD_GameUserInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	bool				bExit;							// �Ƿ��˳���Ϸ(false:�˳���Ϸ; true:����Ϸ)
	long long			lUserID;						// �û�ID
	char				szName[USER_NAME_LEN];			// �û���
	char				szNickname[USER_NAME_LEN];		// �ǳ�
	int					iBuyBulletCount;				// �����ӵ�����
	int					iBulletCount;					// �ӵ�����
	int					iFeats;							// ��ѫ
	long long			lGameCoin;						// ���
	long long			lGoldChange;					// ���
	long long			lPointChange;					// ����
	long long			lAntiAddictionTime;				// ������ʱ��
	long long			lAntiAddictionPlayTime;			// ��������Ϸʱ��

	long long			lCurrentTime;					// ����ʱ��
};

// ����������Ϣ
struct CMD_MatchEnd
{
	CMD_MatchEnd()
	{
		memset(this, 0, sizeof(CMD_MatchEnd));
	}
	long long			lUserID[GAME_PLAYER_COUNT];							// �û�ID
	char				szName[GAME_PLAYER_COUNT][USER_NAME_LEN];			// �û���
	char				szNickname[GAME_PLAYER_COUNT][USER_NAME_LEN];		// �ǳ�
	long long			lGameCoin[GAME_PLAYER_COUNT];						// ���
	int					iRewardGold[GAME_PLAYER_COUNT];						// �������
	long long			lGoldChange[GAME_PLAYER_COUNT];						// ���
	long long			lPointChange[GAME_PLAYER_COUNT];					// ����
};

//////////////////////////////////////////////////////////////////////////

#endif