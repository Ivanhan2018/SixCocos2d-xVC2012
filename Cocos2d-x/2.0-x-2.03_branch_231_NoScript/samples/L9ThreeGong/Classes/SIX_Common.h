#pragma once
#include <TSingleton.h>
#include "cocos-ext.h"
#include <SIX_IInterface.h>
#include <SIX_Interface.h>
#include <SIX_DSTPL.h>
#include <SIX_TVector.h>
#include <SIX_MsgBox.h>
// ������ⲿͷ�ļ�ͳһ������
// Cool.Cat
#include <SelfModuleID.h>
#include <UserInfo.h>
#include <RoomInfo.h>
#include <TableInfo.h>
#include "CMD_SanGong.h"
#include <GameSkeletonMsgCode.h>

// ��ʾFPSͳ����Ϣ
//#define SHOW_FPS

USING_NS_CC;
USING_NS_CC_EXT;

#define	PROJECT_NAME			/*�Ͼ�*/XorStr<0x05,5,0x3B9AAA5F>("\xC5\xC9\xB9\xCD"+0x3B9AAA5F).s
#define PROJECT_ALIAS			/*��������*/XorStr<0x8D,9,0xB8964EDE>("\x41\x62\x43\x7C\x59\x6F\x2A\x3F"+0xB8964EDE).s
#define PROJECT_PACK			/*L9ThreeGong*/XorStr<0x85,12,0x7E53850D>("\xC9\xBF\xD3\xE0\xFB\xEF\xEE\xCB\xE2\xE0\xE8"+0x7E53850D).s
#define PROFILE_PATH			/*Prof*/XorStr<0xF1,5,0x82A10215>("\xA1\x80\x9C\x92"+0x82A10215).s

// �ߴ�
#define MAX_WIDTH				800
#define MAX_HEIGHT				480

// �汾
#define VER_MAIN				1
#define VER_CHILD				0
#define VER_STAGE				0
#define VER_BUILD				1027

// ��ϷID
const int GAME_ID = 2;

typedef enum {
	SCENE_IDX_MIN = 0,
	// ��¼����
	SCENE_IDX_LOGIN,
	// ��������
	SCENE_IDX_HALL,
	// ��Ϸ����
	SCENE_IDX_GAME,
	SCENE_IDX_MAX,
} SCENE_IDX;

#ifdef WIN32
#define WLOG(fmt,...)		SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile(##fmt,##__VA_ARGS__);
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define WLOG(fmt,...)		SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile(fmt,##__VA_ARGS__);
#else
#define WLOG(fmt,...)
#endif
#endif