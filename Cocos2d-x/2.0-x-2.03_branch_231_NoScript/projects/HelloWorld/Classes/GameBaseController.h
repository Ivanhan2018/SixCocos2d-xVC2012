//
//  GameBaseController.h
//  XXDDZ
//
//  Created by XXY on 13-11-29.
//
//

#ifndef __XXDDZ__GameBaseController__
#define __XXDDZ__GameBaseController__

#include "Packet.h"

typedef bool _BOOL_;

// 定义三个位置

#define     HancCardClear 3           // 所有玩家（用户初始化 等）

enum GameFrame {
    GF_FREE = 1,
    GF_CALLBanker = 10,
    GF_CALLBankerOver = 11,
    GF_DOUBLE = 20,
    GF_DOUBLEOver = 21,
    GF_ONGAME = 90,
    GF_NULL = 100
};

// 游戏状态
enum RaceGameControllerUserSettingMenuType {
    GMVUSMT_CallScore_1= 1,
    GMVUSMT_CallScore_2 = 2,
    GMVUSMT_CallScore_3 = 3,
    GMVUSMT_Double = 4,
    GMVUSMT_OutCard = 5,
    GMVUSMT_SetBaseScore = 6,
    GMVUSMT_Trustee = 7,
    GMVUSMT_ValidCard = 8,
    GMVUSMT_MaStOutCard = 9,
    GMVUSMT_NotOutCard = 11,            // 不出
    GMVUSMT_RestartGame = 70,
    GMVUSMT_StartGame = 71,
    GMVUSMT_END = 80,
    GMVUSMT_RestartClear = 90,
    
    GMVUSMT_NULL = 100,
    
    GMVUSMT_CaneChangeTable = 200,
    GMVUSMT_CaneChangeTable_Clear = 201
    
};

enum UserActType {
    UAT_callBanker = 1,  // 叫地主
    UAT_notCallBanker = 2, // 不叫地主
    UAT_rodBanker = 3, // 抢地主
    UAT_notRodBanker = 4,  //不抢地主
    
    UAT_YFEN = 10,  // 叫地主
    UAT_EFEN = 11, // 不叫地主
    UAT_SFEN = 20, // 抢地主
    UAT_notCallScore = 21,  //不抢地主
    UAT_double = 30,    //加倍
    UAT_notDouble = 31, //不加倍
    UAT_outCard = 40,   // 出牌
    UAT_notOutCard = 41,    // 不出牌
    UAT_Tip = 42, //提示
    UAT_trustee = 50,   // 托管
    UAT_notTrustee = 51,   // 取消托管
    UAT_prepare = 70,   // 准备(发送准备包)
    UAT_changeTable = 71, //玩家换桌子
    UAT_prepareValidCard = 80,   // 明牌开始
    UAT_validCard = 90,   // 明牌
    UAT_NULL  = 100
};


enum GAMEType {
    GT_Race = 10,
    GT_Race_Back = 11,
    GT_Normal = 20,
    GT_Normal_Back = 21,
    GT_SELF = 30,
    GT_SELF_Back = 31
};

class GameBaseController {
public:
    // 设置玩家当前进入的 桌子 椅子
    static void setUserCurrentTableIndexAndChairIndex(_BYTE_ tabIdx, _BYTE_ ChairIdx);
};

#endif /* defined(__XXDDZ__GameBaseController__) */
