#ifndef __STATIC_PROPERTY_H__
#define __STATIC_PROPERTY_H__

#pragma mark rootView

using namespace std;

#define PLPot 100
#define PLPotY 450

const int PLPotX[3] = { -900, 860, 100};

const int ReadyTipDot[6] = {480, 280, 740, 330, 200, 330};

#define PLGlgPotx 10

#define tagPlayerInfo 100                // 右侧头像点击TAG

#define CARDItemTag 100

#define HandCardStartPot 50         // 当前用户手牌绘制起点
#define HandCardDisplay 45          // 当前用户手牌间距
#define HandCardNormalPotY 65
#define HandCardSelectPotY 100

#define ACTmenuDisplayDotY 225

#define CARD_NULL 14

#define TIMER_FIRSTCALLBANKER 30    // 首次叫地主时间
#define TIMER_CALLBANKER 20         // 叫地主时间
#define TIMER_RodBANKER 20          // 抢地主时间
#define TIMER_DOUBLE 20             // 加倍时间
#define TIMER_START 30              // 开始时间
#define TIMER_FIRSTOUTCARD 30       // 首出牌时间
#define TIMER_OUTCARD 20            // 出牌时间

#define ACTMenuNum 15

//游戏大厅页面
//底部按钮名称
const string SquareBottomMenuName[10] = {
    "square_store_on.png","square_store_off.png",
    "square_active_on.png","square_active_off.png",
    "square_bank_on.png","square_bank_off.png",
    "square_task_on.png","square_task_off.png",
    "aboutconpany_on.png","aboutconpany_off.png"
};//"square_ranck_on.png","square_ranck_off.png",
//

//游戏页面（主）
const int Lv[21] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
const int Exp[21] = {0,60,160,320,560,1400,2080,3200,4800,7200,10800,16000,27200,48000,80000,136000,240000,400000,1000000};
const std::wstring Title[21] = {L"",L"农奴",L"乞丐",L"佃农",L"流浪汉",L"包身工",L"短工",L"长工",L"贫农",L"中农",L"富农",L"地主",L"土财主",L"大地主",L"大财主",L"恶霸地主",L"恶霸财主",L"奴隶主",L"大奴隶主",L"地方豪强",L"诸侯"};

//聊天快捷语言
const std::wstring TalkMsg[6] = {
    L"快点出，我等的花儿也谢了",
    L"初次见面，各位大侠可得手下留情哦！",
    L"你牌打得太好了",
    L"玩完这局得先撤了，下次再继续。",
    L"手气太差了，郁闷！赶紧让我时来运转吧～",
    L"跟你一起玩的很开心，但愿下次能再一起玩！"};

const std::wstring FaceMsg[8] = {
    L"大哭",
    L"愤怒",
    L"大笑",
    L"发呆",
    L"砸头",
    L"傻笑",
    L"眨眼",
    L"郁闷"};

//游戏页面（主）
//闹钟显示位置
const int ONAct[6] = {480,300, 760,500, 200,500};
//用户操作显示位置
const int ONActTip[6] = {480,300, 660,400, 300,400};

//游戏商店页面

//上架商品 图标
const std::string PUD[14] = {"SYMBOL_CAR.png", "SYMBOL_EGG.png", "SYMBOL_CLAP.png", "SYMBOL_KISS.png","SYMBOL_BEER.png", "SYMBOL_CAKE.png", "SYMBOL_RING.png", "SYMBOL_BEAT.png", "SYMBOL_BOMB.png", "SYMBOL_SMOKE.png", "SYMBOL_VILLA.png","SYMBOL_BRICK.png", "SYMBOL_FLOWER.png",  "SYMBOL_VIPROOM_CARD.png"};
//上架商品 名称
const std::wstring PUDNAME[14] = {L"汽车礼物", L"臭蛋礼物", L"鼓掌礼物", L"香吻礼物", L"啤酒礼物", L"蛋糕礼物", L"钻戒礼物", L"暴打礼物", L"炸弹礼物", L"香烟礼物", L"别墅礼物", L"砖头礼物", L"鲜花礼物", L"VIP房道具"
};


const std::wstring MONEY[14] = {
    L"钓鱼豆：1500",
    L"钓鱼豆：100",
    L"钓鱼豆：300",
    L"钓鱼豆：200",
    L"钓鱼豆：500",
    L"钓鱼豆：800",
    L"钓鱼豆：1000",
    L"钓鱼豆：500",
    L"钓鱼豆：1000",
    L"钓鱼豆：500",
    L"钓鱼豆：2000",
    L"钓鱼豆：300",
    L"钓鱼豆：300",
    L"钓鱼豆：100"
};
//上架商品 金额及物品描述
const std::wstring PUDTEXT[14] = {
    L"金额：1500（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有汽车刹车的动画效果",
    L"金额：100（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近， 有扔臭蛋的动画效果",
    L"金额：300（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有拍手动画效果",
    L"金额：200（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有吻的动画效果",
    L"金额：500（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有喝啤酒的动画效果",
    L"金额：800（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有手捧蛋糕献上的动画效果",
    L"金额：1000（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有钻戒闪耀的动画效果",
    L"金额：500（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近， 有一人物被暴打的动画效果",
    L"金额：1000（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有炸弹爆头的动画效果",
    L"金额：500（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有抽烟的动画效果",
    L"金额：2000（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有房子出现的动画效果",
    L"金额：300（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有扔砖头的动画效果",
    L"金额：300（钓鱼豆 会员九折）\n效果：出现在获赠这头像附近，有手持花的动画效果",
    L"金额：100彩币(一个月)\n效果：购买该道具的用户可以进入特定的VIP房间游戏，购买道具礼物是可享受折扣优惠，有特殊的VIP特色标志，会员期间，名字ID在用户列表中以红色字体突出显示 ，并可优先进入埋怨房间"
};

//字符串转换方法
inline void WStrToUTF8(std::string& dest, const wstring& src){
    dest.clear();
    for (size_t i = 0; i < src.size(); i++){
        wchar_t w = src[i];
        if (w <= 0x7f)
            dest.push_back((char)w);
        else if (w <= 0x7ff){
            dest.push_back(0xc0 | ((w >> 6)& 0x1f));
            dest.push_back(0x80| (w & 0x3f));
        }else if (w <= 0xffff){
            dest.push_back(0xe0 | ((w >> 12)& 0x0f));
            dest.push_back(0x80| ((w >> 6) & 0x3f));
            dest.push_back(0x80| (w & 0x3f));
        }else if (sizeof(wchar_t) > 2 && w <= 0x10ffff){
            dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
            dest.push_back(0x80| ((w >> 12) & 0x3f));
            dest.push_back(0x80| ((w >> 6) & 0x3f));
            dest.push_back(0x80| (w & 0x3f));
        }else
            dest.push_back('?');
    }
}

//! simple warpper

inline std::string WStrToUTF8(const std::wstring& str){
    std::string result;
    WStrToUTF8(result, str);
    return result;
}


// 欢乐斗地主
const int HostDot[6] = {100,410, 100,410, 860,410};

#endif