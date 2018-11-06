#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#include "../GameMsg/CMD_SanGong.h"

//////////////////////////////////////////////////////////////////////////
//宏定义
#define FULL_COUNT					54									//全牌数目
#define MAX_COUNT					3									//最大数目

//数值掩码
#define	LOGIC_MASK_COLOR			0xF0								//花色掩码
#define	LOGIC_MASK_VALUE			0x0F								//数值掩码

//扑克类型（爆玖>王炸>炸弹>三公>点值）
#define CT_VALUES					1									//点值类型（9点>8点>7点>0-6点散牌）
//三公:任意三张由J、 Q、 K、小王、大王组成的牌型
#define CT_THREE_JQK				2									//三公类型
//炸弹:任意三张相同的牌
#define CT_THREE_BOMB				4									//炸弹类型
//王炸：大小王加任意一张牌
#define CT_JOKER_BOMB				5									//王炸类型
//爆玖：由3个3组成的牌
#define CT_THREE_333				6									//爆玖类型
//////////////////////////////////////////////////////////////////////////

//实现发牌、牌型及大小、牌型倍率的游戏逻辑类
class CGameLogic
{
	//变量定义
private:
	static TCardData						m_cbCardListData[FULL_COUNT];				//扑克定义

	//函数定义
public:
	//构造函数
	CGameLogic();
	//析构函数
	virtual ~CGameLogic();

	//属性函数
public:
	//获取数值
	static unsigned char GetCardValue(TCardData cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	//获取花色={0方块,16梅花,32红桃,48黑桃,64王}
	static unsigned char GetCardColor(TCardData cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

	//有效判断
	static bool IsValidCard(TCardData cbCardData);
	//测试用
	static const char * GetCardName(TCardData cbCardData);

	//类型函数
public:
	//获取类型
	static TCardType GetCardType(TCardData cbCardData[], unsigned char cbCardCount);
	//获取倍数
	static TCardTypeMulti GetCardTimes(TCardData cbCardData[], unsigned char cbCardCount);
	//获取点数
	static TCardPoint GetCardPoint(TCardData cbCardData[], unsigned char cbCardCount);

	//控制函数
public:
	//排列扑克，按逻辑数值降序排列
	static void SortCardList(TCardData cbCardData[], unsigned char cbCardCount);
	//混乱扑克
	static void RandCardList(TCardData cbCardBuffer[], unsigned char cbBufferCount);

	//取[nMin,nMax]之间的随机整数
	static int GetRand(const int nMin,const int nMax);

	//根据概率选择，返回true的概率为p
	static bool SelectBoolByProb(float p);

	//功能函数
public:
	//逻辑数值，54张扑克升序排列：A<2<3<4<5<6<7<8<9<方块10<梅花10<红桃10<黑桃10<J<Q<K<小王<大王
	static unsigned char GetCardLogicValue(TCardData cbCardData);
	//对比扑克，ibankerflag={0,1,2}，非0值用于0点牌型的比较，ibankerflag=1表示cbFirstData对应的玩家赢，ibankerflag=2表示cbNextData对应的玩家赢
	static bool CompareCard(TCardData cbFirstData[], TCardData cbNextData[],unsigned char cbCardCount,int ibankerflag=0);
};

//////////////////////////////////////////////////////////////////////////

#endif
