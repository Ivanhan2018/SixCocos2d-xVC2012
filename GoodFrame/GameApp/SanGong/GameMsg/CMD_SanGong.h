#ifndef CMD_SANGONG_H
#define CMD_SANGONG_H

/*
**description:
******CS  -> �ͻ��˷�����������
******SC  -> �����������ͻ��˵�
******CSG -> �ͻ���/����������
******MAIN -> ����Ϣ
******SUB -> ����Ϣ
*/

#include "PublicMacro.h"
#include <string.h>

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

// ��Ϸ״̬:5+1+14+1+(0.45n+5.5)+(2.5n+6)
enum e_GameState:unsigned char
{
	E_GAME_FREE = 0,		// ����״̬����Ϸû��ʼ���ѽ���
	//E_GAME_START,			// ��ʼ״̬
	E_GAME_CALL_BANKER,	    // ��ׯ״̬
	E_GAME_CALL_BANKER_END,	    // ��ׯ����עǰ״̬
	E_GAME_CALL_SCORE,		// ��ע״̬
	E_GAME_CALL_SCORE_END,		// ��ע��̯��ǰ״̬
	E_GAME_SEND_CARD,		// ϴ�ơ�����״̬
	E_GAME_SHOW_CARD,		// ����״̬
	//E_GAME_ERROR,           // ����״̬ 
};

//////////////////////////////////////////////////////////////////////////
//��غ궨��
#define GAME_PLAYER_COUNT			(5)									// ��Ϸ����

//��Ч��ֵ
#define INVALID_BYTE				((unsigned char)(0xFF))						//��Ч��ֵ
#define INVALID_WORD				((unsigned short int)(0xFFFF))				//��Ч��ֵ
#define INVALID_DWORD				((unsigned long)(0xFFFFFFFF))				//��Ч��ֵ
#define INVALID_TABLE				INVALID_DWORD						//��Ч����
#define INVALID_CHAIR				INVALID_WORD						//��Ч����

#define LO4(c)           ((((unsigned char)(c)) & 0x0f))
#define HI4(c)           ((((unsigned char)(c)) & 0xf0)>>4)
#define CARD_VALUE(cbCardData) LO4(cbCardData)//��ȡ��ֵ
#define CARD_COLOR(cbCardData) HI4(cbCardData)//��ȡ��ɫ
#define CARD_COLOR_C(cbCardData) (CARD_TYPE)(CARD_COLOR(cbCardData)<4?(4-CARD_COLOR(cbCardData)):(cbCardData-73))//��ȡ�ͻ����˿�����
//////////////////////////////////////////////////////////////////////////////////
//��������������
typedef long long TChip;//�������ע������
typedef unsigned long long TUserID;//�û�ID
typedef unsigned int TTableID;//���Ӻ�
typedef unsigned short int TChairID;//���Ӻţ��û�λ��
typedef unsigned char TCardData;//�����˿�
typedef unsigned char TCardType;//����={1ɢ�ƺ�7-9��,2����,4ը��,5��ը,6����}
typedef unsigned char TCardTypeMulti;//���ͱ���={9,8,7,6,5,3,2,1}
typedef unsigned char TCardPoint;//�Ƶĵ���={0,��,9}
typedef int TError;//0��ʾ�ɹ�,10��ʾ�׶δ���20��ʾ�в�������30��ʾ����ɢ�����
///////////////////////////////////////////////////////////////////////////////

/**************************************************************************
//�������������
**************************************************************************/
enum PROTOCOL_THREEKING
{
	REQ_USER_CALL_BANKER=400,//�û���ׯ
	REQ_USER_CHIPIN,//�û���ע
	REQ_SEND_FINISH,//�ͻ�������ϴ�ơ����ƶ���,�޶�Ӧ�ṹ�壬�Ի����˻������ͻ��ˣ����˷��ƶ���,ֱ�ӷ���"ϴ�ơ��������"
	REQ_USER_KILL,//ɢ��ɱ����С
	REQ_SHOW_FINISH,//�ͻ���������ƶ���,�޶�Ӧ�ṹ�壬�Ի����˻������ͻ��ˣ����˱��ƶ���,ֱ�ӷ���"�������"
	
	RSP_CALL_BANKER_NOTIFY=500,//������ׯ֪ͨ
	RSP_USER_CALL_BANKER,//�û���ׯ����
	RSP_DICE_NOTIFY,//���ӵ�����Ϣ
	RSP_CALL_BANKER_RESULT,//��ׯ���
	RSP_USER_CHIPIN,//�û���ע
	RSP_CALL_SCORE_END_NOTIFY,//��ע������Ϣ,�޶�Ӧ�ṹ��
	RSP_SEND_CARD_LIST,//������Ϣ
	RSP_SEND_FINISH,//�ͻ�������ϴ�ơ����ƶ�������
	RSP_GAME_END_LIST,//��Ϸ����
	RSP_USER_KILL,//ɢ��ɱ����С����
	RSP_BANKER_CHIPIN_SENDCARD_INFO,//��;����������յ���ͬ����Ϣ
	RSP_SHOW_FINISH,//�ͻ���������ƶ�������

	// Ϊ�˷�ֹ��ϢID�ظ�������ϢID��600��ʼ���ܴ��ڵ���2000 (��Ϊ��GameSkeletonMsgCode.h��Ҳ�õ���������Ϣ)
};

struct Rsp_BankerChipinSendCardInfo
{
	Rsp_BankerChipinSendCardInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	e_GameState curGameState;//��ǰ��Ϸ״̬={E_GAME_CALL_BANKER,E_GAME_CALL_BANKER_END,E_GAME_CALL_SCORE,E_GAME_CALL_SCORE_END,E_GAME_SEND_CARD,E_GAME_SHOW_CARD}
	unsigned long long llElapsedMs;//��ǰ��Ϸ״̬���ŵĺ�������Ŀǰ��0
	unsigned char byCallBanker[GAME_PLAYER_COUNT];//�û���ׯ��־={255,0,1}
	TChairID wBankerChairID;//ׯ���û�={INVALID_CHAIR,0,1,2,3,4}
	TChip llUserChipIn[GAME_PLAYER_COUNT];//�û���ע��Ϣ
	TCardData cbUserCardData[GAME_PLAYER_COUNT][3];//�û��˿�
	TChip llGameTax[GAME_PLAYER_COUNT];//�û���Ϸ˰��
	TChip llGameScore[GAME_PLAYER_COUNT];//�û���������
};

// ��ׯ���ڿ�ʼ���·��Ŀ�����ׯ��Ϣ
struct Rsp_CallBankerNotify
{
	Rsp_CallBankerNotify()
	{
		memset(this, 0, sizeof(*this));
	}
	int iServerSecs;
};

// ��ׯ���ڵ��û���ׯ��Ϣ
struct Req_UserCallBanker
{
	Req_UserCallBanker()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TTableID iSeatNo;
	bool bCall;	// �Ƿ���ׯ
	//S->Cʹ�õ��ֶ�
	TError iRes;
};

//��ע���ڵ�ɢ��ɱ����С��Ϣ
struct Req_UserKill
{
	Req_UserKill()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TTableID iSeatNo;
	int KillMode;//ɢ�ɲ���ģʽ={0��ɢ�ɲ���,1ɱ����С,��}
	//S->Cʹ�õ��ֶ�
	TError iRes;
};

//��ע�����мҵ���ע��Ϣ
struct Req_UserChipin
{
	Req_UserChipin()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TTableID iSeatNo;
	TChip lScore;//��ע��Ŀ,C1,C2,C3�е�һ��ֵ
	//S->Cʹ�õ��ֶ�
	TError iRes;
};


//��ׯ�������ӦRSP_CALL_BANKER_RESULT
//ׯ��ȷ�����·���ׯ��λ�á������мҵĳ�����ע��
// ��ׯ����עǰ���ڿ�ʼ���·������ӵ�����Ϣ����Rsp_DiceNotify
struct Rsp_BankerC3Info
{
	Rsp_BankerC3Info()
	{
		memset(this, 0, sizeof(*this));
	}
	bool bNeedCallBanker;//�Ƿ񾭹���ׯ����
	unsigned int dice[2];//�������ӵ���
	unsigned int CallBankerNum;//��ׯ����={0,1,��},���Ϊ1��������
	TChairID wBankerUser;
	TChip C3;//���ĳ�����ע��
	TChip C2;//�м�ĳ�����ע��=C3/2
	TChip C1;//��С�ĳ�����ע��=C3/4
};

struct Rsp_SendCard
{
	Rsp_SendCard()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TChairID iSeatNo;
	TCardData cbUserCardData[3];
};

//����ϴ�ơ����ƻ��ڵ���Ϸ���ƣ���ӦRSP_SEND_CARD_LIST
struct Rsp_SendCard_List
{
	Rsp_SendCard_List(){memset(this, 0, sizeof(*this));}
	unsigned int nCount;
	Rsp_SendCard m_SendCards[GAME_PLAYER_COUNT];
};

//ϴ�ơ����ƻ���ׯ�Һ��мҵĶ�����Ϸ��أ���ӦRSP_SEND_FINISH
struct Rsp_SendFinish
{
	Rsp_SendFinish()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TChairID iSeatNo;
	TError iRes;
};

//���ƻ���ׯ�Һ��мҵĶ�����Ϸ��أ���ӦRSP_SHOW_FINISH
struct Rsp_ShowFinish
{
	Rsp_ShowFinish()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TChairID iSeatNo;
	TError iRes;
};

struct Rsp_GameEnd
{
	Rsp_GameEnd()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TChairID iSeatNo;
	TChip lGameTax;				//��Ϸ˰��
	TChip lGameScore;			//��������
	TCardType CardType;
	TCardPoint CardPoint;
};

//һ����Ϸ����ʱ����Ϸ���㣬��ӦRSP_GAME_END_LIST
struct Rsp_GameEnd_List
{
	Rsp_GameEnd_List(){memset(this, 0, sizeof(*this));}
	unsigned int nCount;
    Rsp_GameEnd m_GameEnds[GAME_PLAYER_COUNT];
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif