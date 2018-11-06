/*
*  CMD_LogonServer.h
*  test
*
*  Created by Aden on 14-11-20.
*  Copyright 2014 __MyCompanyName__. All rights reserved.
*
*/
#pragma once
#include "packet.h"
#pragma pack(1)

#define MDM_CM_SYSTEM				1000								//ϵͳ����
///////////////////////////////////////////////////////////////////////////
// ��¼���� ��Ϸ����
#define MDM_GR_LOGON				1									// ��¼��Ϣ

#pragma mark -
#pragma mark ��¼ģʽ
#define SUB_GR_LOGON_USERID			1									// id ��¼
#define SUB_GR_LOGON_MOBILE			2									// �ֻ���¼
#define SUB_GR_LOGON_ACCOUNTS		3									// �˻���¼

//#pragma mark -
//#pragma mark ��¼���
//#define SUB_GR_LOGON_SUCCESS		100									// ��¼�ɹ�
#define SUB_GR_LOGON_FAILURE		101									// ��¼ʧ��
//#define SUB_GR_LOGON_FINISH			102									// ��¼���

#define	SUB_GR_LOGON_NOTIFY			104                                 // ��½��ʾTIPS     mojunxin

//#pragma mark -
//#pragma mark ������ʾ
#define SUB_GR_UPDATE_NOTIFY		200									// ������ʾ

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//#pragma mark -
//#pragma mark �豸����
#define DEVICE_TYPE_ITOUCH			0x20								// iTouch
#define DEVICE_TYPE_IPHONE			0x40								// iPhone
#define DEVICE_TYPE_IPAD			0x80								// iPad
#define DEVICE_TYPE_ADNROID			0x13								// android


//#pragma mark -
//#pragma mark ��ͼģʽ
#define	VIEW_MODE_ALL				0x0001								// ȫ������
#define	VIEW_MODE_PART				0x0002								// ���ֿ���

//#pragma mark -
//#pragma mark ��Ϣģʽ
#define VIEW_INFO_LEVEL_1			0x0010								// ������Ϣ
#define VIEW_INFO_LEVEL_2			0x0020								// ������Ϣ
#define VIEW_INFO_LEVEL_3			0x0040								// ������Ϣ
#define VIEW_INFO_LEVEL_4			0x0080								// ������Ϣ

//#pragma mark -
//#pragma mark ��������
#define RECVICE_GAME_CHAT			0x0100								// ��������
#define RECVICE_ROOM_CHAT			0x0200								// ��������
#define RECVICE_ROOM_WHISPER		0x0400								// ����˽��

//#pragma mark -
//#pragma mark ��Ϊ��ʶ
#define BEHAVIOR_LOGON_NORMAL       0x0000                              // ��ͨ��¼
#define BEHAVIOR_LOGON_IMMEDIATELY  0x1000                              // ������¼


//id ��¼
typedef struct
{
	// �汾��Ϣ
	DWORD							dwPlazaVersion;						// �㳡�汾
	DWORD							dwFrameVersion;						// ��ܰ汾
	DWORD							dwProcessVersion;					// ���̰汾
	
	// ��¼��Ϣ
	DWORD							dwUserID;							// �û�id
	TCHART							szPassword[LEN_MD5];				// ��¼����
	TCHART							szMachineID[LEN_MACHINE_ID];		// ��������
	
} CMD_GR_LogonUserID;

// �ֻ���¼
typedef struct
{
	// �汾��Ϣ
	WORD							wGameID;							// ��Ϸ��ʶ
	DWORD							dwProcessVersion;					// ���̰汾
	
	// ��������
	BYTE                            cbDeviceType;                       // �豸����
	WORD                            wBehaviorFlags;                     // ��Ϊ��ʶ
	WORD                            wPageTableCount;                    // ��ҳ����
	
	// ��¼��Ϣ
	DWORD							dwUserID;							// �û� I D
	TCHART							szPassword[LEN_MD5];				// ��¼����
	TCHART							szMachineID[LEN_MACHINE_ID];		// ������ʶ
	
}CMD_GR_LogonMobile;


// �ʺŵ�¼
typedef struct
{
	// �汾��Ϣ
	DWORD							dwPlazaVersion;						// �㳡�汾
	DWORD							dwFrameVersion;						// ��ܰ汾
	DWORD							dwProcessVersion;					// ���̰汾
	
	// ��¼��Ϣ
	TCHART							szAccounts[LEN_ACCOUNTS];			// ��¼�ʺ�
	TCHART							szPassword[LEN_MD5];				// ��¼����
	TCHART							szMachineID[LEN_MACHINE_ID];		// ��������

} CMD_GR_LogonAccounts;

// ��¼�ɹ�
typedef struct
{
	DWORD							dwUserRight;						// �û�Ȩ��
	DWORD							dwMasterRight;						// ����Ȩ��                            
} CMD_GR_LogonSuccess;

// ��¼ʧ��
typedef struct
{
	long							lErrorCode;							// �������
	TCHART							szDescribeString[128];				// ��������
} CMD_GR_LogonFailure;


// ��½��ʾTIPS
typedef struct  // mojunxin
{
	DWORD                           dwTick;
	TCHART							szDescribeString[64];
} CMD_GP_LogonNotify;

// ������ʾ
typedef struct
{	
	// ������־
	BYTE							cbMustUpdatePlaza;					// ǿ������
	BYTE							cbMustUpdateClient;					// ǿ������
	BYTE							cbAdviceUpdateClient;				// ��������
	
	// ��ǰ�汾
	DWORD							dwCurrentPlazaVersion;				// ��ǰ�汾
	DWORD							dwCurrentFrameVersion;				// ��ǰ�汾
	DWORD							dwCurrentClientVersion;				// ��ǰ�汾
} CMD_GR_UpdateNotify;


////////////////////////////////////////////////////////////////////////////////
//#pragma mark -
//#pragma mark ��������

#define	MDM_GR_CONFIG				2									// ������Ϣ

#define	SUB_GR_CONFIG_COLUMN		100									// �б�����
#define SUB_GR_CONFIG_SERVER		101									// ��������
#define SUB_GR_CONFIG_PROPERTY		102									// ��������

#define SUB_GR_CONFIG_FINISH		103									// �������




/////////////////////////////////////////////////////////////////////////////////

// �б�����
typedef struct
{
	BYTE							cbColumnCount;						// �б���Ŀ
	tagColumnItem					ColumnItem[MAX_COLUMN];				// �б�����
} CMD_GR_ConfigColumn;

// ��������
typedef struct
{
	//��������
	WORD							wTableCount;						// ������Ŀ
	WORD							wChairCount;						// ������Ŀ
	
	//��������
	WORD							wServerType;						// ��������
	DWORD							dwServerRule;						// �������
    WORD                            wTime;                              // ���䵹��ʱʱ��  mojunxin add
} CMD_GR_ConfigServer;

// ��������
typedef struct
{
	BYTE							cbPropertyCount;					// ������Ŀ
//	tagPropertyInfo					PropertyInfo[MAX_PROPORTY];			// ��������
} CMD_GR_ConfigProperty;


/////////////////////////////////////////////////////////////////////////////////
//#pragma mark -
//#pragma mark �û�����

#define MDM_GR_USER					3									// �û���Ϣ

// �û�����
#define SUB_GR_USER_RULE			1									// �û�����
#define	SUB_GR_USER_LOOKON			2									// �Թ�����
#define	SUB_GR_USER_SITDOWN			3									// ��������
#define	SUB_GR_USER_STANDUP			4									// ��������
#define SUB_GR_USER_INVITE			5									// �û�����
#define SUB_GR_USER_INVITE_REQ		6									// ��������
#define SUB_GR_USER_REPULSE_SIT  	7									// �ܾ��������
#define SUB_GR_USER_KICK_USER       8                                   // �߳��û�     ���� ��Ϣ
#define SUB_GR_USER_INFO_REQ        9                                   // �����û���Ϣ
#define SUB_GR_USER_CHAIR_REQ       10                                  // �������λ��
#define SUB_GR_USER_CHAIR_INFO_REQ	11									// ���������û���Ϣ
#define SUB_GR_USER_WAIT_DISTRIBUTE 12                                  // �ȴ�����



// �û�״̬
#define	SUB_GR_USER_ENTER			100									// �û�����
#define	SUB_GR_USER_SCORE			101									// �û�����
#define SUB_GR_USER_STATUS			102									// �û�״̬
#define	SUB_GR_REQUEST_FAILURE		103									// ����ʧ��

// ��������
#define	SUB_GR_USER_CHAT			201									// ������Ϣ
#define	SUB_GR_USER_EXPRESSION		202									// ������Ϣ
#define SUB_GR_WISPER_CHAT			203									// ˽����Ϣ
#define	SUB_GR_WISPER_EXPRESSION	204									// ˽�ı���
#define SUB_GR_COLLOQUY_CHAT		205									// �Ự��Ϣ
#define	SUB_GR_COLLOQUY_ERPRESSION	206									// �Ự����

// ��������
#define SUB_GR_PROPERTY_BUY			300									// �������
#define SUB_GR_PROPERTY_SUCCESS		301									// ���߳ɹ�
#define SUB_GR_PROPERTY_FAILURE		302									// ����ʧ��
#define SUB_GR_PROPERTY_MESSAGE     303                                 // ������Ϣ
#define SUB_GR_PROPERTY_EFFECT      304                                 // ����ЧӦ
#define SUB_GR_PROPERTY_TRUMPET     305                                 // �û�����

// �ֻ���Ϸ��������ָ����  add by mojunxin
#define	SUB_GR_CLICK_BONUS			403									// ÿ��N���ӵĶ�����ȡ���ͻ��˷���
#define	SUB_GR_GET_BONUS			1404								// �������˷��ؽ�����Լ�������
#define	SUB_GR_GET_ERROR			1405								// ������䷵�ش�����Ϣ����


//// ��ֵ add by mojunxin  for android
//#define SUB_GR_APPLY_PAY			500									// �����ֵ
//#define SUB_GR_PAY_SUCCESS			501								// ����ɹ�
//#define SUB_GR_PAY_FAIL				502								// ��ֵʧ��

//��ֵ - iPhone   add by mojunxin
#define SUB_GP_APPLY_PAY_IP			600									// appleӦ���ڹ�����ɣ�������������ֵ
#define SUB_GP_PAY_REVE_IP			601									// �����ֵ�󣬷��������ص�����





/////////////////////////////////////////////////////////////////////////////////

// �Թ�����
typedef struct
{
	WORD							wTableID;							// ����λ��
	WORD							wChairID;							// ����λ��
} CMD_GR_UserLookon;

// ��������
typedef struct
{
	WORD							wTableID;							// ����λ��
	WORD							wChairID;							// ����λ��
	TCHART							szPassword[LEN_PASSWORD];			// ��������
} CMD_GR_UserSitDown;

// ��������
typedef struct
{
	WORD							wTableID;							// ����λ��
	WORD							wChairID;							// ����λ��
	BYTE							cbForceLeave;						// ǿ���뿪
} CMD_GR_UserStandUp;

/*
// �û�������Ϣ
typedef struct
{
	DWORD							dwUserID;							// �û���ʶ
	tagUserScore					UserScore;							// ������Ϣ
} CMD_GR_UserScore;


/////////////////////////////////////////////////////////////////////////////////
// add by mojunxin

// ������ͻ�����ұ��˷���ÿ��N����
typedef struct
{
	WORD							wTableID;							// ����λ��
	WORD							wChairID;							// ����λ��

} CMD_GR_ClickBonus;


// ������������˷��ؽ�����Լ���������
typedef struct
{
	//DWORD							wBonusAmount;						// ��������������
    TCHART							szDesc[256];                        // ���������ķ�����Ϣ
	WORD							wNextMunites;						// �˴α���򿪵���ʱ ����Ϊ��λ
} CMD_GR_GetBonus;

// ��������䷵�ش�����Ϣ�����������쳣����
typedef struct
{
	TCHART							szErrorDesc[256];                  // ������䷵�ش�����Ϣ����
} CMD_GR_GetError;



// �ͻ��˷��ͣ�ĳ����Ҵ���������  
typedef struct
{
	WORD							wTableID;							// ����λ��
	WORD							wChairID;							// ����λ��
} CMD_GR_BoxTouch;

// �������˷��ͣ����ϱ�����˭���
typedef struct
{
	WORD							wWinChairID;						// ����λ��
	TCHART							szDescription[128];					// ������Ϣ��Ӧ������Ϸ���������ʾ
} CMD_GR_BoxEnd;


// appleӦ���ڹ�����ɣ�������������ֵ
typedef struct
{
	DWORD							dwUserID;							// �û�ID
	LONGLONG						lPayMoney;							// ��ֵ��� (Ϊ����ң�������Ϸ����)
    BYTE							cbPhoneMode;						// ϵͳ  1��Android  2:iPhone
	TCHART							szPayDesc[128];						// ��֤�ַ���
} CMD_GP_ApplyPayIP;

// �����ֵ�󣬷��������ص�����
typedef struct
{
	DWORD							dwUserID;							// �û�ID
	TCHART							szDesc[128];						// ���ؿͻ�������
} CMD_GP_PayDescIP;
*/

//#pragma mark -
//#pragma mark �û�����
typedef struct 
{
	DWORD							dwUserID;							// �û���ʶ
	tagMobileUserScore				UserScore;							// ������Ϣ
} CMD_GR_MobileUserScore;


// �û�״̬
typedef struct
{
	DWORD							dwUserID;							// �û���ʶ
	tagUserStatus					UserStatus;							// �û�״̬
} CMD_GR_UserStatus;

// �����û���Ϣ
typedef struct 
{
	DWORD                           dwUserIDReq;                        // �����û�
	WORD							wTablePos;							// ����λ��
} CMD_GR_UserInfoReq;


// �����û���Ϣ
typedef struct 
{
	WORD							wTableID;							// ���Ӻ���
	WORD							wChairID;							// ���Ӻ���
} CMD_GR_ChairUserInfoReq;


// ����ʧ��
typedef struct
{
	long							cbFailureCode;						// �������
	TCHART							szDescribeString[256];				// ������Ϣ
} CMD_GR_RequestFailure;

// �û�����
typedef struct
{
	WORD							wChatLength;						// ��Ϣ����
	DWORD							dwChatColor;						// ��Ϣ��ɫ
	DWORD							dwTargerUserID;						// Ŀ���û�
	TCHART							szChatString[LEN_USER_CHAT];		// ������Ϣ
} CMD_GR_C_UserChat;

// �û�����
typedef struct
{
	WORD							wChatLength;						// ��Ϣ����
	DWORD							dwChatColor;						// ��Ϣ��ɫ
	DWORD							dwSendUserID;						// �����û�
	DWORD							dwTargetUserID;						// Ŀ���û�
	TCHART							szChatString[LEN_USER_CHAT];		// ������Ϣ
} CMD_GR_S_UserChat;

// �û�����
typedef struct
{
	WORD							wItemIndex;							// ��������
	DWORD							dwTargetUserID;						// Ŀ���û�
} CMD_GR_C_UserExpression;
//��¼��Ϣ
struct tagServerGameRecord
{
	BYTE							cbKingWinner;						//����Ӯ��
	BYTE							bPlayerTwoPair;						//���ӱ�ʶ
	BYTE							bBankerTwoPair;						//���ӱ�ʶ
	BYTE							cbPlayerCount;						//�мҵ���
	BYTE							cbBankerCount;						//ׯ�ҵ���
};
// �û�����
typedef struct
{
	WORD							wItemIndex;							// ��������
	DWORD							dwSendUserID;						// �����û�
	DWORD							dwTargetUserID;						// Ŀ���û�
} CMD_GR_S_UserExpression;

// �û�˽��
typedef struct
{
	WORD							wChatLength;						// ��Ϣ����
	DWORD							dwChatColor;						// ��Ϣ��ɫ
	DWORD							dwTargetUserID;						// Ŀ���û�
	TCHART							szChatString[LEN_USER_CHAT];		// ������Ϣ
} CMD_GR_C_WisperChat;

// �û�˽��
typedef struct
{
	WORD							wChatLength;						// ��Ϣ����
	DWORD							dwChatColor;						// ��Ϣ��ɫ
	DWORD							dwSendUserID;						// �����û�
	DWORD							dwTargetUserID;						// Ŀ���û�
	TCHART							szChatString[LEN_USER_CHAT];		// ������Ϣ
} CMD_GR_S_WisperChat;

// ˽�ı���
typedef struct
{
	WORD							wItemIndex;							// ��������
	DWORD							dwTargetUserID;						// Ŀ���û�
} CMD_GR_C_WisperExpression;

// ˽�ı���
typedef struct
{
	DWORD							wItemIndex;							// ��������
	DWORD							dwSendUserID;						// �����û�
	DWORD							dwTargetUserID;						// Ŀ���û�
} CMD_GR_S_WisperExpression;

// �û��Ự
typedef struct
{
	WORD							wChatLength;						// ��Ϣ����
	DWORD							dwChatColor;						// ��Ϣ��ɫ
	DWORD							dwSendUserID;						// �����û�
	DWORD							dwConversationID;					// �Ự��ʶ
	DWORD							dwTargetUserID[16];					// Ŀ���û�
	TCHART							szChatString[LEN_USER_CHAT];		// ������Ϣ
} CMD_GR_GR_ColloquyChat;


// �����û�
typedef struct
{
	WORD							wTableID;							// ���Ӻ���
	DWORD							dwSendUserID;						// �����û�
} CMD_GR_C_InviteUser;

// �����û�
typedef struct
{
	DWORD							dwTargetUserID;						// Ŀ���û�
} CMD_GR_S_InviteUser;


typedef enum
{
    kPropTypeBrick  = 12,
    kPropTypeFlower = 13,

} Prop_type;

// �������
typedef struct 
{
	BYTE                            cbRequestArea;						// ����Χ
	BYTE							cbConsumeScore;						// ��������
	WORD							wItemCount;							// ������Ŀ
	WORD							wPropertyIndex;						// ��������  // �ʻ�:13����ש:12
	DWORD							dwTargetUserID;						// ʹ�ö���
} CMD_GR_C_PropertyBuy;


// ���߳ɹ�  ������Ϣ�ɹ���
typedef struct
{
	BYTE                            cbRequestArea;						// ʹ�û���
	WORD							wItemCount;							// ������Ŀ
	WORD							wPropertyIndex;						// �������� // �ʻ�:13����ש:12
	DWORD							dwSourceUserID;						// ʹ���û�
	DWORD							dwTargetUserID;						// Ŀ�����
} CMD_GR_S_PropertySuccess;

// ����ʧ�� ʧ�ܰ�
typedef struct
{
	WORD                            wRequestArea;                       // ��������
	LONG							lErrorCode;							// �������
	TCHART							szDescribeString[256];				// ������Ϣ
} CMD_GR_PropertyFailure;


// ������Ϣ
typedef struct
{
    WORD                            wPropertyIndex;                     // ��������
    WORD                            wPropertyCount;                     // ������Ŀ
    DWORD                           dwSourceUserID;                     // ʹ���û�
    DWORD                           dwTargetUserID;                     // ʹ�ö���
} CMD_GR_S_PropertyMessage;



// �߳��û�
typedef struct
{
	DWORD							dwTargetUserID;						// Ŀ���û�
} CMD_GR_KickUser;






/*

// ����ЧӦ û���õ�
//typedef struct _CMD_GR_S_PropertyEffect
//{
//    DWORD                           wUserID;                            //�û�I D
//    BYTE                            cbMemberOrder;                      //��Ա�ȼ�
//} CMD_GR_S_PropertyEffect;

// ��������
typedef struct _CMD_GR_C_SendTrumpet
{
    BYTE                            cbRequestArea;                      //
    WORD                            wPropertyIndex;
    DWORD                           TrumpetColor;
    TCHART                           szTrumpetContent[TRUMPET_MAX_CHAR];
} CMD_GR_C_SendTrumpet;

// ��������
typedef struct _CMD_GR_S_SendTrumpet
{
    WORD                            wPropertyIndex;
    DWORD                           dwSendUserID;
    DWORD                           TrumpetColor;
    TCHART                           szSendNickName[32];
    TCHART                           szTrumpetContent[TRUMPET_MAX_CHAR];
} CMD_GR_S_SendTrumpet;

/////////////////////////////////////////////////////////////////////////////////

//�����־
#define UR_LIMIT_SAME_IP			0x01								//���Ƶ�ַ
#define UR_LIMIT_WIN_RATE			0x02								//����ʤ��
#define UR_LIMIT_FLEE_RATE			0x04								//��������
#define UR_LIMIT_GAME_SCORE			0x08								//���ƻ���

//�û�����
typedef struct
{
	BYTE							cbRuleMask;							//��������
	WORD							wMinWinRate;						//���ʤ��
	WORD							wMaxFleeRate;						//�������
	long							lMaxGameScore;						//��߷���
	long							lMinGameScore;						//��ͷ���
	
}CMD_GR_UserRule;
*/

/////////////////////////////////////////////////////////////////////////////////
//#pragma mark -
//#pragma mark ״̬����

#define MDM_GR_STATUS				4									//״̬��Ϣ

#define SUB_GR_TABLE_INFO			100									//������Ϣ
#define	SUB_GR_TABLE_STATUS			101									//����״̬

/*
//������Ϣ
typedef struct
{
	WORD							wTableCount;						//������Ŀ
	tagTableStatus					TableStatusArray[512];				//����״̬
}CMD_GR_TableInfo;

//����״̬
typedef struct
{
	WORD							wTableID;							//���Ӻ���
	tagTableStatus					TableStatus;						//����״̬
}CMD_GR_TableStatus;
*/

/////////////////////////////////////////////////////////////////////////////////
// ���չ�����

#define MDM_GR_INSURE					5								// �û���Ϣ

// ���չ�����
#define SUB_GR_QUERY_INSURE_INFO		1								// ��ѯ���չ�
#define SUB_GR_SAVE_SCORE_REQUEST		2								// �������
#define SUB_GR_TAKE_SCORE_REQUEST		3								// ȡ������
#define SUB_GR_TRANSFER_SCORE_REQUEST	4								// ת������

#define SUB_GR_USER_INSURE_INFO			100								// ���չ�����
#define SUB_GR_USER_INSURE_SUCCESS		101								// ���չ�ɹ�
#define SUB_GR_USER_INSURE_FAILURE		102								// ���չ�ʧ��

//// ������ʽ delete
//#define INSURE_SAVE                     0                               // ��ȡ��ʽ
//#define INSURE_TRANSFER                 1                               // ת����ʽ

/*
// ���չ���Ϣ
typedef struct
{
	WORD	wRevenueTake;
	WORD	wRevenueTransfer;
	WORD	wServerID;
	SCORE	lUserScore;
	SCORE	lUserInsure;
	SCORE	lTransferPrerequisite;
}tagUserInsureInfo;


//#pragma mark -
//#pragma mark �ͻ��˽ṹ��
// ��ѯ���չ�
typedef struct
{
	BYTE	cbActivityGame;						// ��Ϸ����
    TCHART	szInsurePass[LEN_PASSWORD];			// ���չ�����

} CMD_GR_C_QueryInsureInfoRequest;

// ��������
typedef struct
{
	BYTE	cbActivityGame;							// ��Ϸ����
	SCORE	lSaveScore;								// ������Ŀ
} CMD_GR_C_SaveScoreRequest;

// ȡ������
typedef struct
{
	BYTE	cbActivityGame;							// ��Ϸ����
	SCORE	lTakeScore;								// ȡ����Ŀ
	TCHART	szInsurePass[LEN_PASSWORD];				// ���չ�����
} CMD_GR_C_TakeScoreRequest;

// ת������
typedef struct
{
	BYTE	cbActivityGame;							// ��Ϸ����
	BYTE	cbByNickName;							// �ǳ����� 0ID 1�ǳ�
	SCORE	lTransferScore;							// ת������
	TCHART	szNickName[LEN_NICKNAME];				// Ŀ���û�
	TCHART	szInsurePass[LEN_PASSWORD];				// ���չ�����
} CMD_GR_C_TransferScoreRequest;

//#pragma mark -
//#pragma mark ���������ͽṹ��
// ���չ�����
typedef struct
{
	BYTE	cbActivityGame;							//��Ϸ����
	WORD	wRevenueTake;							//˰�ձ���
	WORD	wRevenueTransfer;						//˰�ձ���
	WORD	wServerID;								//�����ʶ
	SCORE	lUserScore;								//�û�����
	SCORE	lUserInsure;							//���չ񶹶�
	SCORE	lTransferPrerequisite;					//ת������
    
} CMD_GR_S_UserInsureInfo;

// ���չ�ɹ�
typedef struct	
{
	BYTE	cbActivityGame;							//��Ϸ����
	SCORE	lUserScore;								//�û�����
	SCORE	lUserInsure;							//���չ񶹶�
	TCHART	szDescribrString[128];					//������Ϣ
}CMD_GR_S_UserInsureSuccess;		

// ���չ�ʧ��
typedef struct	
{
	BYTE	cbActivityGame;							//��Ϸ����
	long	lErrorCode;								//�������
	TCHART	szDescribeString[128];					//������Ϣ
}CMD_GR_S_UserInsureFailure;
*/


/////////////////////////////////////////////////////////////////////////////////
//��������

#define	MDM_GR_MANAGE				6									//��������

#define SUB_GR_SEND_WARNING			1									//���;���
#define SUB_GR_SEND_MESSAGE			2									//������Ϣ
#define SUB_GR_LOOK_USER_IP			3									//�鿴��ַ
#define SUB_GR_KICK_USER			4									//�߳��û�
#define SUB_GR_LIMIT_ACCOUNTS		5									//�����˻�
#define SUB_GR_SET_USER_RIGHT		6									//Ȩ������

//��������
#define	SUB_GR_QUERY_OPTION			7									//��ѯ����
#define SUB_GR_OPTION_SERVER		8									//��������
#define SUB_GR_OPTION_CURRENT		9									//��ǰ����

//...


////////////////////////////////////////////////////////////////////////////////
//...


//...

//���ñ�־
#define OSF_ROOM_CHAT               1                                   //��������
#define OSF_GAME_CHAT               2                                   //��Ϸ����
#define OSF_ROOM_WISPER             3                                   //����˽��
#define OSF_ENTER_TABLE             4                                   //������Ϸ
#define OSF_ENTER_SERVER            5                                   //���뷿��
#define OSF_SEND_BUGLE              12                                  //��������


///////////////////////////////////////////////////////////////////////////////
//�������

#define	MDM_GF_FRAME				100									// �������

// �û�����
#define SUB_GF_GAME_OPTION			1									// ��Ϸ����
#define SUB_GF_USER_READY			2									// �û�׼��
#define SUB_GF_LOOKON_CONFIG		3									// �Թ�����

// ��������
#define SUB_GF_USER_CHAT			10									// �û�����
#define SUB_GF_USER_EXPRESSION		11									// �û�����

// ��Ϸ��Ϣ
#define SUB_GF_GAME_STATUS			100									// ��Ϸ״̬
#define SUB_GF_GAME_SCENE			101									// �Թ۳���
#define SUB_GF_LOOKON_STATUS		102									// �Թ�״̬

// ϵͳ��Ϣ
#define SUB_GF_SYSTEM_MESSAGE		200									// ϵͳ��Ϣ
#define SUB_GF_ACTION_MESSAGE		201									// ������Ϣ

/////////////////////////////////////////////////////////////////////////////////



//��Ϸ����
typedef struct
{
	BYTE							cbAllowLookon;						//�Թ۱�־
	DWORD							dwFrameVersion;						//��ܰ汾
	DWORD							dwClientVersion;					//��Ϸ�汾

}CMD_GF_GameOption;
/*
//�Թ�����
typedef struct
{
	DWORD							dwUserID;							//�û���ʶ
	BYTE							cbAllowLookon;						//�����Թ�
}CMD_GF_LookonConfig;

//�Թ�״̬
typedef struct
{
	BYTE							cbAllowLookon;						//�����Թ�
}CMD_GF_LookonStatus;

//��Ϸ����
typedef struct
{
	BYTE							cbGameStatus;						//��Ϸ״̬
	BYTE							cbAllowLookon;						//�Թ۱�־
}CMD_GF_GameStatus;
*/
//...

/////////////////////////////////////////////////////////////////////////////////

//��Ϸ����
#define MDM_GF_GAME					200									//��Ϸ����

//������Ϣ
#define DTP_GR_TABLE_PASSWORD		1									//��������

//�û�����
#define DTP_GR_NICK_NAME			10									//�û��ǳ�
#define DTP_GR_GROUP_NAME			11									//��������
#define DTP_GR_UNDER_WRITE			12									//����ǩ��

//������Ϣ
#define DTP_GR_USER_NOTE			20									//�û���ע
#define DTP_GR_CUSTOM_FACE			21									//�Զ�ͷ��


/////////////////////////////////////////////////////////////////////////////////

//�������
#define REQUEST_FAILURE_NORMAL		0									//����ԭ��
#define REQUEST_FAILURE_NOGOLD		1									//��������
#define REQUEST_FAILURE_NOSCORE		2									//���ֲ���
#define REQUEST_FAILURE_PASSWORD	3									//�������

#define REQUEST_FAILURE_ACCOUNTS	7									//�ǳƴ���

struct CMD_CM_SystemMessage
{
	WORD							wType;								//��Ϣ����
	WORD							wLength;							//��Ϣ����
	TCHART							szString[1024];						//��Ϣ����
};


#pragma pack()