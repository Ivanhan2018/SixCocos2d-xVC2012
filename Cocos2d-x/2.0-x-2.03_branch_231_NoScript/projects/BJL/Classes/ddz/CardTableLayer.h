//  [3/26/2014 xieyi]
#ifndef __CARDTABLE_LAYER__
#define __CARDTABLE_LAYER__

#include "cocos2d.h"
#include "DDZRes.h"
#include "SceneData.h"
#include "Timer.h"
#include "User.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class CardTableLayer : public CCNode
{
public:

	CardTableLayer();
	~CardTableLayer();
	CREATE_FUNC(CardTableLayer);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void waitingMatching(bool isWaiting);			//等待排队
	void setUserIsOnline(WORD wBankerUser,LONGLONG lBankerScore,LONGLONG lBankerWinScore, WORD	wBankerTime);//用户坐庄
	void setUserIcon(int userId,int gender,char* name,int gold,char* huafeidian );//设置庄家头像信息
	void setNickName(const char * nikeName);				//设置昵称
	CCSize size;
	void upHaiou(float ft);
	void haiouCall(CCObject* _obj);
	//设置庄家的金币
	void setBabnkUsedScore(LONGLONG Score);
	//设置庄家的成绩和局数
	void setBankUsedChengjiORrJuNumber(LONGLONG Chengji,LONGLONG JuNumber);
	//设置玩家的分数成绩
	void setPlayAllScoreORchengji(LONGLONG Chengji);

	//用户下注更新积分
	void SetPlaceLandScore(CCObject *obj);

	void initScrollView(BYTE m_cbPlayerCount ,BYTE m_cbBankerCount);

	void SetUpdate();
public:
	cocos2d::extension::CCScrollView      *m_pScrollView;
	LONG szText0;
private:
	CC_SYNTHESIZE(int,m_coinNumber,CoinNum); 	//金币数量
	CC_SYNTHESIZE(int,m_hhdNumber,HhdNumber);		//话费点数量
	CC_SYNTHESIZE(int,m_times,Times);			//倍率
	CCLabelTTF * m_coinNumberAtlas;				//金币数字
	CCSprite *SpriteMyUsed;                        //用户头像
	//	CCLabelAtlas * m_hhdAtlas;						//花费点字
	CCLabelTTF * m_nikeName;						//玩家昵称
	CCLabelTTF *m_Chengji;                          //用户成绩
	CCSpriteBatchNode * m_cardTableBatchNode;		//牌桌batchnode
	CCSpriteBatchNode * m_pdNode;						//排队动画
	CCString getDateNow();						//获得系统当前时间

	CCSprite *SpriteGameRecord;             //游戏记录
public:
	CCSprite *FinUsedSprite;
	CCLabelTTF* laberName;   //姓名
	CCLabelTTF* goldname;        //金币
	CCLabelTTF* ChengjiScore;  //地址
	CCLabelTTF *JiNumber;   //局数


 //   CCLabelAtlas* lBankTTf;    //庄
	//CCLabelAtlas* PlayKingTTf;   //闲天王
	//CCLabelAtlas* lBankKingTTf;    //庄天王 
	//CCLabelAtlas* DittoPingTTf;    //同上平
	//CCLabelAtlas* PlaySubTTf;    //闲对子
	//CCLabelAtlas* lBankSubTTf;    //庄对子
	bool hnnnnnnn;
};

#endif
