/*
 *  define.h
 *  test
 *
 *  Created by WJ on 14-11-20.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEFINE_DEFINE_FILE
#define DEFINE_DEFINE_FILE
#pragma once

#include "cocos2d.h"
#include <string>
using namespace std;
using namespace cocos2d;
#pragma pack(1)

const int GameId_DDZ		= 1;
const int GameId_PHZ		= 2;
const int GameId_CSMJ		= 3;
const int GameId_ZJH		= 4;
const int GameId_SDK		= 5;
const int GameId_PDK		= 6;

const int SeverID_CSMJ      = 0;
const int SeverID_PDK       = 1;
const int SeverID_PHZ       = 2;
const int SeverID_SDH       = 3;

// ��Ӧ��������

#ifdef WIN32
typedef wchar_t		TCHART;
//typedef unsigned short		TCHART;
#else
typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef unsigned long		DWORD;
typedef	long long			LONGLONG;
typedef unsigned short		TCHART;
typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
//typedef wchar_t		TCHART;
#endif

typedef long long			SCORE;
typedef double              DOUBLE;
typedef long                LONG;

//#pragma mark ��ֵ����
// ͷ���С
#define	FACE_CX				48						// ͷ����
#define FACE_CY				48						// ͷ��߶�

// ���ȶ���
#define	LEN_LESS_ACCOUNTS	3						// ����ʺ�
#define LEN_LESS_NICKNAME	3						// ����ǳ�
#define LED_LESSPASSWORD	6						// �������

// ��������
#define MAX_CHAIR			100						// �������
#define	MAX_TABLE			512						// �������
#define	MAX_COLUMN			32						// ����б�
#define	MAX_ANDROID			256						// ������
#define	MAX_PROPORTY		128						// ������
#define	MAX_WHISPER_USER	16						// ���˽��

// �ѱ���
#define MAX_KIND			128						// �������
#define MAX_SERVER			1024					// ��󷿼�

// ��������
//#define	INVALID_CHAIR		0xFFFF					// ��Ч����
//#define	INVALID_TABLE		0xFFFF					// ��Ч����
//#define INVALID_USERID		0						// ��Ч�û�

// ˰�����
#define	REVENUE_BENCHMARK	1000L					// ˰�����
#define	REVENUE_DENOMINATOR	1000L					// ˰�շ�ĸ

//#pragma mark ϵͳ����
// ��Ϸ״̬
//��Ϸ״̬
#define GAME_STATUS_FREE			0									//����״̬
#define GAME_STATUS_PLAY			100									//��Ϸ״̬
#define GAME_STATUS_WAIT			101									//�ȴ�״̬
// ϵͳ����
#define LEN_USER_CHAT		128						// ���쳤��
#define	TIME_USER_CHAT		1L						// ������
#define TRUMPET_MAX_CHAR    128                     // ���ȳ���
	

//#pragma mark ��������
// �б�����
#define PRIME_TYPE			11L						// ������Ŀ
#define PRIME_KIND			53L						// ������Ŀ
#define PRIME_NODE			101L					// �ڵ���Ŀ
#define	PRIME_PAGE			53L						// �Զ���ľ
#define PRIME_SERVER		1009L					// ������ľ

// ��������
#define PRIME_SERVER_USER	503L					// ��������
#define PRIME_ANDROID_USER	503L					// ��������
#define PRIME_PLATFORM_USER	100003L					// ƽ̨����


//#pragma mark ���ݳ���
// ��������
#define LEN_MD5				33						// ��������
#define LEN_ACCOUNTS		32						// ��ע����
#define LEN_NICENAME		32						// �ʺų���
#define LEN_NICKNAME		32						// �ǳƳ���
#define LEN_PASSWORD		33						// ���볤��
#define LEN_GROUP_NAME		32						// ��������
#define LEN_UNDER_WRITE		32						// ����ǩ��

// ���ݳ���
#define LEN_QQ				16						// q q����
#define LEN_EMAIL			33						// �����ʼ�
#define LEN_USER_NOTE		256						// �û���ע
#define LEN_SEAT_PHONE		33						// �̶��绰
#define LEN_MOBILE_PHONE	12						// �ƶ��绰
#define Len_PASS_PORT_ID	19						// ֤������
#define LEN_COMPELLATION	16						// ��ʵ����
#define LEN_DWELLING_PLACE	128						// ��ϵ��ַ


// ������ʶ
#define LEN_MACHINE_ID		33						// ���г���
#define LEN_NETWORK_ID		13						// ��������

// �б�����
#define LEN_TYPE			32						// ���೤��
#define LEN_KIND			32						// ���ͳ���
#define LEN_NODE			32						// �ڵ㳤��
#define LEN_PAGE			32						// ���Ƴ���
#define LEN_SERVER			32						// ���䳤��
#define LEN_PROCESS			32						// ���̳���


//#pragma mark ���ѹ�ϵ
#define CP_NORMAL			0						// δ֪��ϵ
#define CP_ERIEND			1						// ���ѹ�ϵ
#define CP_DETEST			2						// ����ϵ

//#pragma mark �Ա���
#define GENDER_FRMALE		0						// Ů���Ա�
#define	GENDER_MANKIND		1						// �����Ա�

//#pragma mark ��Ϸģʽ
//#define GAME_GENRE_GOLD		0x0001					// ��������
//#define GAME_GENRE_SCORE	0x0002					// ��ֵ����
//#define GAME_GENRE_EDUCATE	0x0003					// ��������
//#define GAME_GENREMATCH		0x0004					// ѵ������

//#pragma mark ����ģʽ
#define	SCORE_GENRE_NORMAL		0x0100				// ��ͨģʽ
#define SCORE_GENRE_POSITIVE	0x0200				// �Ǹ�ģʽ

//�û�״̬
#define US_NULL						0x00								//û��״̬
#define US_FREE						0x01								//վ��״̬
#define US_SIT						0x02								//����״̬
#define US_READY					0x03								//ͬ��״̬
#define US_LOOKON					0x04								//�Թ�״̬
#define US_PLAYING					0x05								//��Ϸ״̬
#define US_OFFLINE					0x06								//����״̬

//#pragma mark �������
#define	SRL_LOOKON			0x00000001				// �Թ۱�־
#define SRL_OFFLINE			0x00000002				// ���߱�־
#define	SRL_SAME_IP			0x00000004				// ͬ����־

#define	SRL_ROOM_CHAT		0x00000100				// �����־
#define SRL_GAME_CHAT		0x00000200				// �����־
#define SRL_WISPER_CHAT		0x00000400				// ˽�ı�־
#define SRL_HIDE_USER_INFO	0x00000800				// ���ر�־

//#pragma mark �б�����
//��Ч����
#define	UD_NULL				0						// ��Ч����
#define UD_IMAGE			100						// ͼ������

//��������
#define UD_GAME_ID			1						// ��Ϸ��ʶ
#define UD_USER_ID			2						// �û���ʶ
#define UD_NICKNAME			3						// �û��ǳ�

//��չ����
#define	UD_GENDER			10						// �û��Ա�
#define UD_GROUP_NAME		11						// ��������
#define	US_UNDER_WRITE		12						// ����ǩ��

//״̬��Ϣ
#define	UD_TABLE			20						// ��Ϸ����
#define UD_CHAIR			21						// ���Ӻ���

//������Ϣ
#define	UD_SCORE			30						// �û�����
#define UD_BANKER			31						// �û����չ�
#define UD_EXPERIENCE		32						// �û�����
#define UD_LOVELINESS		33						// �û�����
#define	UD_WIN_COUNT		34						// ʤ������
#define UD_LOSE_COUNT		35						// �������
#define	UD_DRAW_COUNT		36						// �;�����
#define UD_FLEE_COUNT		37						// �Ӿ�����
#define UD_PLAY_COUNT		38						// �ܾ�����

//���ֱ���
#define	UD_WIN_RATE			40						// �û�ʤ��
#define	UD_LOSE_RATE		41						// �û�����
#define UD_DRAW_RATE		42						// �û�����
#define	UD_FLEE_RATE		43						// �û�����
#define UD_GAME_LEVEL		44						// ��Ϸ�ȼ�

//��չ��Ϣ
#define	UD_NOTE_INFO		50						// �û���ע
#define	UD_LOOKON_USER		51						// �Թ��û�

//ͼ���б�
#define	UD_FLAG				(UD_IMAGE+1)			// �û���־
#define UD_STATUS			(UD_IMAGE+2)			// �û�״̬

//#pragma mark ���ݿⶨ��
#define	DB_ERROR			-1						// ����ʧ��
#define	DB_SUCCESS			0						// ����ɹ�


//Macro.h
///////////////////////////////////////////////////////////////////////
//���ó���

//��Ч��ֵ
//#define	INVALID_BYTE		((BYTE)(0xff))			// ��Ч��ֵ
//#define INVALID_WORD		((WORD)(0xffff))		// ��Ч��ֵ
//#define INVALID_DWORD		((DWORD)(0xffffffff))	// ��Ч��ֵ

//����ά��
#define CountArray(Array)	(sizeof(Array)/sizeof(Array[0]))

//��Ч��ַ
#define INVALID_IP_ADDRESS(IPAddress)	(((IPAddress == 0L) || (IPAddress == INADDR_NONE)))


// �û�ע�������ַ�
#define strAccounts         "m_pAccounts"          // �ʺ�
#define strPassword         "m_pPassword"          // ����
#define strNickname         "m_pNickname"          // �ǳ�
#define strBankword         "m_pBankWord"          // ���չ�����

#define strQuickRegCount    "m_pQuickRegCount"     // ����ע��Ĵ���



#define IMAGE_BG_480        "game_bg-hd.png"
#define IMAGE_BG_568        "game_bg-hd568.png"

#define ROOM_BG_480         "common_bg.png"
#define ROOM_BG_568         "common_bg.png"

#define WEB_BG_480          "common_bg_2.png"
#define WEB_BG_568          "common_bg_2.png"

// ��Ϸ���䶹������
#define ROOM_MAX_PK               (500000)  // 50������Ϊpk��
#define ROOM_MAX_NORMAL           (100000)  // �����м�Ϊ��ͨ��
#define ROOM_MAX_PRIMARY          (10000)   // 1������Ϊ������

#define ROOM_MENU_POSX          (15)
#define ROOM_MENU_POSY          (85.0-13)      // 92
#define ROOM_MENU_W             (450.0)      // 92
#define ROOM_MENU_H             (86.0/2)      // 92


#define SPACE_LEFT_W            ( 112.0/2)
#define SPACE_RIGHT_W           ( 113.0/2)


// ���������������Ϸ������
typedef enum
{
	type_appStoreLove = 1,      // appstore����
	type_GoodFriends,           // ΢�ź���
	type_FriendsCircle,         // ΢�����ч�
	type_txWeb,                 // ��Ѷ΢��
	type_sineWeb,               // ����΢��
	
} ShareType;

// ֧����Ʒ����
#define PAY_NAME_6            "6���Ƥ��"
#define PAY_NAME_12           "13.2���Ƥ��"
#define PAY_NAME_50           "60���Ƥ��"
#define PAY_NAME_98           "117.6���Ƥ��"
#define PAY_NAME_328          "475.6���Ƥ��"
#define PAY_NAME_648          "1069���Ƥ��"


#define PAY_NAME_EN6          "6wan hapidou"
#define PAY_NAME_EN12         "13.2wan hapidou"
#define PAY_NAME_EN50         "60wan hapidou"
#define PAY_NAME_EN98         "117.6wan hapidou"
#define PAY_NAME_EN328        "475.6wan hapidou"
#define PAY_NAME_EN648        "1069wan hapidou"

#define ERROR_NEED_BUY			(0x203)						//515 ������Ϸ���䣬��Ҫ����
#endif
#pragma pack()