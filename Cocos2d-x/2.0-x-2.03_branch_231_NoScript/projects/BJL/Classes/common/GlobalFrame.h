//
//  GlobalFrame.h
//  Game
//
//  Created by zhouwei on 13-6-27.
//
//

#ifndef GLOBAL_FRAME_HEAD_FILE
#define GLOBAL_FRAME_HEAD_FILE

#pragma once

#include "GlobalDef.h"
//////////////////////////////////////////////////////////////////////////
//�궨��

//��Ϸ״̬
#define GS_FREE							0								//����״̬
#define GS_PLAYING						100								//��Ϸ״̬

//////////////////////////////////////////////////////////////////////////
//IPC �����¼�

#define IPC_MAIN_SOCKET					1								//������Ϣ

#define IPC_SUB_SOCKET_SEND				1								//���緢��
#define IPC_SUB_SOCKET_RECV				2								//�������

//��ȡ����
enum enChargeKind
{
	enChargeKind_GoldEggs,
	enChargeKind_Score,
};

//IPC ������ṹ
struct IPC_SocketPackage
{
	CMD_Command							Command;						//������Ϣ
	BYTE								cbBuffer[SOCKET_PACKET];		//���ݻ���
};

//////////////////////////////////////////////////////////////////////////
//IPC ������Ϣ

#define IPC_MAIN_CONFIG					2								//������Ϣ

#define IPC_SUB_SERVER_INFO				1								//������Ϣ
#define IPC_SUB_COLUMN_INFO				2								//�б���Ϣ

//��Ϸ��Ϣ
struct IPC_GF_ServerInfo
{
	DWORD								dwUserID;						//�û� I D
	WORD								wTableID;						//���Ӻ���
	WORD								wChairID;						//���Ӻ���
	WORD								wKindID;						//���ͱ�ʶ
	WORD								wServerID;						//�����ʶ
	WORD								wGameGenre;						//��Ϸ����
	WORD								wChairCount;					//������Ŀ
	BYTE								cbHideUserInfo;					//������Ϣ
	DWORD								dwVideoAddr;					//��Ƶ��ַ
	char								szKindName[KIND_LEN];			//��������
	char								szServerName[SERVER_LEN];		//��������
	//WORD								wMatchType;						//��������
	BYTE                                cbLimitDraw;                    //���ƾ���
	LONG                                lCellScore;                     //���� 
};

//////////////////////////////////////////////////////////////////////////
//IPC �û���Ϣ

#define IPC_MAIN_USER					3								//�û���Ϣ

#define IPC_SUB_USER_COME				1								//�û���Ϣ
#define IPC_SUB_USER_STATUS				2								//�û�״̬
#define IPC_SUB_USER_SCORE				3								//�û�����
#define IPC_SUB_GAME_START				4								//��Ϸ��ʼ
#define IPC_SUB_GAME_FINISH				5								//��Ϸ����
#define IPC_SUB_UPDATE_FACE				6								//����ͷ��
#define IPC_SUB_MEMBERORDER				7								//����ͷ��
#define IPC_SUB_USER_GOLD				8								//�û����
#define IPC_SUB_USER_SORT				9								//�û�����
#define IPC_SUB_USER_MATCH_SCORE        10                              //�û������ɼ�
#define IPC_SUB_MATCH_USER_COM          11                              //�����û�����
//�û�״̬
struct IPC_UserStatus
{
	DWORD								dwUserID;						//�û� I D
	WORD								wNetDelay;						//������ʱ
	BYTE								cbUserStatus;					//�û�״̬
};

//�û�����
struct IPC_UserScore
{
	LONG								lLoveliness;					//�û�����
	DWORD								dwUserID;						//�û� I D
	tagUserScore						UserScore;						//�û�����
};

//�����û���Ϣ
struct IPC_Match_UserInfo
{
    DWORD                                dwUserID;                       //�û�ID
	LONG                                 lMatchScore;                    //��������
	char                                szName[NAME_LEN];               //�û���
};

//�����û�����
struct IPC_UserMatchScore
{
	DWORD                                dwUserID;                     //�û�ID
    LONG                                 lMatchScore;                  //��������
};

//�û�����
struct IPC_UserSort
{
	DWORD								dwUserID;					    //�û� I D
	WORD								wSortID;						//����
	EN_MatchStatus						enMatchStatus;					//����״̬
};
//��Ա�ȼ�
struct IPC_MemberOrder
{
	BYTE								cbMember;                       //��Ա�ȼ�
	DWORD								dwUserID;						//�û� I D
};

//�û�����
struct IPC_UpdateFace
{
	DWORD								dwCustomFace;					//�û� I D
};

//////////////////////////////////////////////////////////////////////////
//IPC ������Ϣ

#define IPC_MAIN_CONCTROL				4								//������Ϣ

#define IPC_SUB_START_FINISH			1								//�������
#define IPC_SUB_CLOSE_FRAME				2								//�رտ��
#define IPC_SUB_JOIN_IN_GAME			3								//������Ϸ
#define IPC_SUB_CLOSE_ROOM				5								//�رշ���
#define IPC_SUB_PLAZA_RESET_WND         6                               //������ԭ����
#define IPC_SUB_START_MAX_WND           7                               //һ������Ϸ��ȫ��
#define IPC_SUB_PLAZA_SPECIAL_MIN       8                               //�ֱ���С��,������С��
#define IPC_SUB_PLAZA_ACTIVE_FRAME      9                               ///������
//������Ϸ
struct IPC_JoinInGame
{
	WORD								wTableID;						//���Ӻ���
	WORD								wChairID;						//���Ӻ���
};

//////////////////////////////////////////////////////////////////////////
//����������

//#define MDM_GF_GAME						100								//��Ϸ��Ϣ
//#define MDM_GF_FRAME					101								//�����Ϣ
#define	MDM_GF_PRESENT					102								//������Ϣ
#define	MDM_GF_BANK						103								//������Ϣ

#define SUB_GF_INFO						1								//��Ϸ��Ϣ
#define SUB_GF_USER_READY				2								//�û�ͬ��
#define SUB_GF_LOOKON_CONTROL			3								//�Թۿ���
#define SUB_GF_KICK_TABLE_USER			4								//�����û�


#define SUB_GF_OPTION					100								//��Ϸ����
#define SUB_GF_SCENE					101								//������Ϣ

//#define SUB_GF_USER_CHAT				200								//�û�����

#define SUB_GF_MESSAGE					300								//ϵͳ��Ϣ


#define SUB_GF_GIFT						400								//������Ϣ
#define SUB_GF_ISLAND					410								//��ֵ����Ϣ
#define SUB_GF_BANK_STORAGE				450								//���д洢
#define SUB_GF_BANK_GET					451								//������ȡ
#define SUB_GF_TASK						452								//��������
#define SUB_GF_USER_LEVEL				453								//������Ϣ
#define SUB_GF_SZFCARD					454								//���ݸ���Ϣ
#define SUB_GF_PHONE_CONFIG				456                             //�ֻ�������Ϣ

#define SUB_GF_FLOWER_ATTRIBUTE			500								//�ʻ�����
#define SUB_GF_FLOWER					501								//�ʻ���Ϣ
#define SUB_GF_EXCHANGE_CHARM			502								//�һ�����

#define SUB_GF_PROPERTY					550								//������Ϣ
#define SUB_GF_PROPERTY_RESULT			551								//���߽��
#define SUB_GF_RESIDUAL_PROPERTY		552								//ʣ�����
#define SUB_GF_PROP_ATTRIBUTE			553								//��������
#define SUB_GF_PROP_BUGLE				554								//���ȵ���
#define SUB_GF_PLAY_SOUND				555								//��������
#define SUB_GF_CHAT_MESSAGE             556                             //������Ϣ
#define SUB_GF_ACTIVE_PLAZA             557                             //�������
#define SUB_GF_USER_CONTINUE_GAME       558                             //������Ϸ
#define SUB_GF_GAME_FRAME_RESET_WND     559                             //��ܻ�ԭ��Ϣ

#define SUB_GF_CELL						600								//��λ��Ϣ
#define SUB_GF_EXPRESSION               601                             //������Ϣ
#define SUB_GF_ROOM_SOCRE_LIMIT			602						// �����������
#define SUB_GF_ROOM_SCOREUPDATA		603						//�����ֵ����ˢ��				


#define SMT_CELL_N						0x0000							//�޵�λ�仯
#define SMT_CELL_H						0x0001							//������Ϣ �����������
#define SMT_CELL_L						0x0002							//������Ϣ ��������
#define SMT_CELL_L_SELF					0x0003							//������Ϣ ��Ҽ�����������
#define SMT_CELL_TABLE_H				0x0004							//��������
#define SMT_CELL_TABLE_L				0x0005							//���ӽ���
#define SMT_CELL_USER_H					0x0006							//�û�����
#define SMT_CELL_USER_L					0x0007							//�û�����

#define SUB_C_ALL_READY              5004                //֪ͨ������Ѿ�׼���õ���

//��λ��Ϣ
struct CMD_GF_CELL_MESSAGE
{
	WORD								wMessageType;					//��Ϣ����
	LONG								lCellScoreH;					//�͵�λ
	LONG								lCellScoreL;					//�ߵ�λ
	WORD								wMessageLength;					//��Ϣ����
	char								szContent[1024];				//��Ϣ����
};

//�����������
struct CMD_GR_RoomScoreLimit
{
	long							lScore;				// �ҵķ���
	long							lMinScore;			// ��ͷ���
	long							lMaxScore;			// ������

	CMD_GR_RoomScoreLimit()
	{
		memset(this, 0, sizeof(*this));
	}
};
//�汾��Ϣ
struct CMD_GF_Info
{
	BYTE								bAllowLookon;					//�Թ۱�־
};

/////2011.1.7 by gaoshan ��ҵ�����ʾ������Ϣ
struct CMD_GF_DisPlay_Info
{
	WORD                               dwDisplayWidth;                   //��ʾ�����
	WORD                               dwDisplayHeight;                  //��ʾ���߶�
};

//��Ϸ����
struct CMD_GF_Option
{
	BYTE								bGameStatus;					//��Ϸ״̬
	BYTE								bAllowLookon;					//�����Թ�
};

//�Թۿ���
struct CMD_GF_LookonControl
{
	DWORD								dwUserID;						//�û���ʶ
	BYTE								bAllowLookon;					//�����Թ�
};

//�����û�
struct CMD_GF_KickTableUser
{
	DWORD								dwUserID;						//�û� I D
};

//����ṹ
struct CMD_GF_UserChat
{
	WORD								wChatLength;					//��Ϣ����
	//COLORREF							crFontColor;					//��Ϣ��ɫ
	DWORD								dwSendUserID;					//�����û�
	DWORD								dwTargetUserID;					//Ŀ���û�
	char								szChatMessage[MAX_CHAT_LEN];	//������Ϣ
};

//�������� 2010-01-19 hjw add
struct CMD_GF_PlaySound
{
	BYTE cbChairID;
	BYTE cbGender;
	BYTE cbSoundID;
	char szNickName[NAME_LEN];
};

//������Ϣ
struct CMD_GF_Chat_Message
{
	char   szNickName[NAME_LEN];               //����������Ϣ���û�
	char   szChatMsg[MAX_CHAT_LEN];            //��Ϣ����
	WORD    wChatUserTableID;                   //�����û������Ӻ�
	WORD    wChatUserChairID;                   //�����û������Ӻ�
	char   strChatMsg[3][MAX_CHAT_LEN];
	WORD    wChatLen[3];
};

//������Ϣ
struct CMD_GF_EXPRESSION
{
    WORD    wType;                             //���� ��1���� 2������
	WORD	wChairID;						   //�û�����
	WORD    wIndex;							   //��������
};

enum enChatMsgType
{
	enSounChatMsg     =0,                      ///��������������Ϣ
	enInPutMsg        =1                       ////�����������Ϣ
};

////С��Ϸ�������������ݵ���ʽ��ʾ
//struct CMD_Show_Chat_Message
//{
//    WORD       wChatUserChairID;                  ///�����û������Ӻ�
//	CString    strChatMsg;                        ///������Ϣ
//	char      strInPutMsg[3][128];
//	WORD       wMsgLen[3];
//	enChatMsgType enChatMessageType;              ///������Ϣ������
//};
//////////////////////////////////////////////////////////////////////////

//��Ϣ����
#define SMT_INFO						0x0001							//��Ϣ��Ϣ
#define SMT_EJECT						0x0002							//������Ϣ
#define SMT_GLOBAL						0x0004							//ȫ����Ϣ
#define SMT_CLOSE_GAME					0x1000							//�ر���Ϸ
#define SMT_TABLE_ROLL					0x0010							//��Ϸ���������Ϣ 
#define SMT_TABLE_FIX					0x0020							//��Ϸ����̶���Ϣ

//��Ϣ���ݰ�
struct CMD_GF_Message
{
	WORD								wMessageType;					//��Ϣ����
	WORD								wMessageLength;					//��Ϣ����
	char								szContent[1024];				//��Ϣ����
};

//////////////////////////////////////////////////////////////////////////

////�����ڴ涨��
//struct tagShareMemory
//{
//	WORD								wDataSize;						//���ݴ�С
//	HWND								hWndGameFrame;					//��ܾ��
//	HWND								hWndGamePlaza;					//�㳡���
//	HWND								hWndGameServer;					//������
//};

//////////////////////////////////////////////////////////////////////////

//���ͳ���
#define	LOCATION_GAME_ROOM				1								//��Ϸ����
#define	LOCATION_PLAZA_ROOM				2								//��������

//////////////////////////////////////////////////////////////////////////

//���ͽṹ
struct CMD_GF_Gift
{
	BYTE								cbSendLocation;					//���ͳ���
	DWORD								dwSendUserID;					//������ID
	DWORD								dwRcvUserID;					//������ID
	WORD								wGiftID;						//����	ID
	WORD								wFlowerCount;					//�ʻ���Ŀ
};

//���߽ṹ
struct CMD_GF_Property
{
	BYTE								cbSendLocation;					//���ͳ���
	int									nPropertyID;					//����ID
	DWORD								dwPachurseCount;				//������Ŀ
	DWORD								dwOnceCount;					//������Ŀ
	DWORD								dwSourceUserID;					//�������
	DWORD								dwTargetUserID;					//Ŀ�����
	char								szRcvUserName[32];				//�û�����
};

////���Ƚṹ
//struct CMD_GF_BugleProperty
//{
//	BYTE								cbSendLocation;					//���ͳ���
//	char								szUserName[32];					//����ʺ�
//	COLORREF							crText;							//������ɫ
//	char								szContext[BUGLE_MAX_CHAR];		//��������
//};

//�һ��ṹ
struct CMD_GF_ExchangeCharm
{
	BYTE								cbSendLocation;					//���ͳ���
	LONG								lLoveliness;					//������ֵ
	DWORD								lGoldValue;						//�����ֵ
};

//����֪ͨ
struct CMD_GF_GiftNotify
{
	BYTE								cbSendLocation;					//���ͳ���
	DWORD								dwSendUserID;					//������ID
	DWORD								dwRcvUserID;					//������ID
	WORD								wGiftID;						//����	ID
	WORD								wFlowerssCount;					//�ʻ���Ŀ
};

//�洢/��ȡ���
struct CMD_GF_Bank
{
	DWORD								dwUserID;						//�û�ID
	DWORD								dwGameKindID;					// ��ϷID
	long								lValue;							//�洢/��ȡ���
	char								szPassword[PASS_LEN];			//�û��ֻ� QQ
	char								szRealPsd[PASS_LEN];			//�û�����

	CMD_GF_Bank()
	{
		memset(this, 0, sizeof(*this));
	}
};

//�컰����Ϣ
struct CM_GF_CHARGE
{
	BYTE								cbChargeType;					//��Ϣ����
	char								szMessage[128];					//��Ϣ����
};


////ʣ�����
//struct CMD_GF_ResidualProperty
//{
//	DWORD								dwResidualTime[PROPERTY_COUNT];	//ʣ��ʱ��
//};

//////////////////////////////////////////////////////////////////////////
#endif
