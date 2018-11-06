#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Fish.h"
#include "Bezier.h"
#include "Material.h"
#include "MersenneTwister.h"
#include "NumberSprite.h"
#include "Lamp.h"
#include "Numbers.h"
#include <list>
#include <vector>
#include "CCScene.h"

using namespace cocos2d;

const int MAX_LIGHT_NUMBER = 4;

class MainScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
	void start(void);
    static cocos2d::CCScene* scene();
    CREATE_FUNC(MainScene);
private:
	void updateGame(float dt);
	void fishRestart(void);
	void fishExt(float time);
	void fishHideEnd(CCNode* pSender);
	void updateFishEgg(float dt);
	void updeteBezierPath(float len, float angle);

	void gotoBG_1(bool first);
	void gotoBG_2(void);
	void bg_CEnd(CCNode* sender);

	void historyScaleActionEnd(CCNode* sender);
	void historyEnd(void);
	void historyRestart(unsigned char *data);

	void lampInit(void);
	void lampRotate(void);
	void lampStop(void);

	void frogRandomRotate(void);
	void frogYaFenRotateEnd(CCNode* sender);
	void frogStartPaoDengRotate(void);
	void frogStartPaoDengAction(Result rt, int roudCnt);
	void frogPaoDengRotateEnd(CCNode* sender);
	int frogNextAngle(float nowAngle);
	void lampUnderLightEnd(CCNode* sender);
	void frogLightStopDT(CCNode* sender);
	void frogLightEnd(CCNode* sender);
	void nextResult(void);
	void frogLightRemove(CCNode* sender);

	void winerShow_Show(Result r);
	void winerShow_Hide(void);
	void winerShow_Hide_Done(CCNode* sender);

	void sharkShootStart(void);
	void sharkRoundParticleEnd(CCNode* sender);
	void sharkShoot(void);
	void sharkParticleShoot(CCNode* sender);
	void sharkParticleEndDone(CCNode* sender);
	void randomFireworkNext(CCNode* sender);
	void randomFirework(void);

	void countDowmInit(void);
	void countDowmShow(int time);
	void countDowmHide(void);
	void countDowmSet(int time);

	float GetJiaJiao(float s_a, float e_a);
	int getStopIndex(Result rt);
	int getStep(int startIndex, int endIndex);
	int GetBeiLv(Result r);

	void buttomInit(void);

	void KaiShiYaFen(bool first);
	void KaiShiPaoDeng(void);
	void ShowCaiJin(void);
	void buttom_A_Put(CCObject* pSender);
	void buttom_B_Put(CCObject* pSender);
	void buttom_C_Put(CCObject* pSender);
	void buttom_D_Put(CCObject* pSender);
	void buttom_E_Put(CCObject* pSender);
	void buttom_F_Put(CCObject* pSender);
	void buttom_G_Put(CCObject* pSender);
	void buttom_H_Put(CCObject* pSender);

public:
	//static CDirtyRect dirtyRect;

private:
	Material material;
	MTRand random;
	unsigned char moveMap[360][225];
	BezierPath bp;

	#pragma region 鱼原始指针
	Fish *fish_JinSha;
	Fish *fish_YinSha;
	Fish *fish_MoGuiYu;
	Fish *fish_DengLongYu[2];
	Fish *fish_HaiGui[2];//2
	Fish *fish_QiPaoYu[3];
	Fish *fish_BanYu[4];
	Fish *fish_CaiHuaYu[4];
	Fish *fish_HuDieYu[6];
	CCSpriteBatchNode *fishBatch;
	#pragma endregion

	//背景
	CCSpriteBatchNode *shuiCaoBatch;
	CCSprite *backGroup_1;
	CCSprite *backGroup_2;
	CCSprite* SCSprite_1;
	CCSprite* SCSprite_2;
	CCSprite* SCSprite_3;
	CCSprite* shuiWen_1;
	CCSprite* shuiWen_2;

	//跑灯的树桩
	Lamp *lamp[28];
	float lampAngle[28];

	//中奖显示
	bool isWinerShow;
	CCSprite *winerShow[4];
	Numbers *winerBeiLv[4];
	
	//青蛙
	CCSprite *frog;
	CCSprite *light[MAX_LIGHT_NUMBER];
	int lastLampIndex;
	float frogRotateSpeed;
	int rotateCnt;
	int rotateCntM;
	int nowIndex;
	bool isCaiGuang;
	Result gameResult[3];
	int nowDoResultIndex;

	//倒计时
	NumberSprite *countDowm[2][2];

	//发射鲨鱼
	int shootCnt;

	Numbers *numberTest;

	bool isHistroyShow;
	CCSprite *historySPRArray[2][20];


};

#endif  // __HELLOWORLD_SCENE_H__