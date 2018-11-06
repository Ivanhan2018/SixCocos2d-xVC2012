#pragma once
// 开发模式
//#define DEVELOP_MODE

#ifdef DEVELOP_MODE
	// 内存泄漏检测
	//#define CHECK_MEM_LEAK

	// 本地房间
	//#define LOCAL_SERVER
#endif

// 大厅登陆
#define HALL_LOGIN

// 鱼阴影
#define USING_FISH_SHADOW
#ifdef USING_FISH_SHADOW
// 阴影偏移
#define FISH_SHADOW_OFFSET	30.0f
// 阴影缩放
#define FISH_SHADOW_RATIO	0.65f
#endif

#include <math.h>
#include <TSingleton.h>
#include "cocos-ext.h"
#include <SIX_IInterface.h>
#include <SIX_Interface.h>
#include <SIX_DSTPL.h>
#include <SIX_MsgBox.h>
// 网络层外部头文件统一放这里
// Cool.Cat
#include <SelfModuleID.h>
#include <UserInfo.h>
#include <RoomInfo.h>
#include <TableInfo.h>
#include <ProFish.h>
#include <GameSkeletonMsgCode.h>

USING_NS_CC_EXT;

#define	PROJECT_NAME			/*老九捕鱼*/XorStr<0xB8,9,0xEB019F53>("\x78\x76\x04\x7E\x0E\x0B\x6D\x5C"+0xEB019F53).s
#define PROJECT_PACK			/*SixFish*/XorStr<0x1B,8,0xC218A501>("\x48\x75\x65\x58\x76\x53\x49"+0xC218A501).s
#define PROFILE_PATH			/*Prof*/XorStr<0xF1,5,0x82A10215>("\xA1\x80\x9C\x92"+0x82A10215).s

#define MAX_WIDTH				1280
#define MAX_HEIGHT				733

// 版本
#define VER_MAIN				1
#define VER_CHILD				1
#define VER_STAGE				0
#define VER_BUILD				914

// 场景切换持续时间
#define TRANSITION_DURATION		1.2f
// 鱼类型
#define	MAX_FISH_TYPECOUNT		10
// 鱼帧
#define MAX_FISH_FRAMECOUNT		10

// 按钮
ENUM_BEGIN(ENUM_BTNIDX)
	BTN_CLOSE=1,
	BTN_CONFIG=2,
	BTN_START=3,
	BTN_MUSIC_ON=4,
	BTN_MUSIC_OFF=5,
ENUM_END()

typedef enum {
	SCENE_IDX_MIN = 0,
	SCENE_IDX_GATE,
	SCENE_IDX_GAME,
	SCENE_IDX_MAX,
} SCENE_IDX;

USING_NS_CC;
USING_UTILITY;

#define CREATE_GLOBALMGR	SIX_GlobalMgr *pGlobalMgr = SIX_GlobalMgr::GetInstance();
#define USING_GLOBALMGR		extern SIX_GlobalMgr *pGlobalMgr;

// 玩家最大数目
const int MAX_PLAYER = 4;

// 资源加载最大数目
const int LOAD_MAX = 24;