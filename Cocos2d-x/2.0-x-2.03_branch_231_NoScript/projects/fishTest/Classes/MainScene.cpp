#include "MainScene.h"

#include "Define.h"
#include "ActionExt.h"
#include "Numbers.h"
#include "PointHelper.h"

using namespace cocos2d;


const CCPoint ScreenCentre = ccp(ScreenSize.width/2, ScreenSize.height/2);

const CCPoint FishCreatPoint_0 = ccp(530.0f/1440.0f, 740.0f/900.0f);
const CCPoint FishCreatPoint_1 = ccp(380.0f/1440.0f, 230.0f/900.0f);
const CCPoint FishCreatPoint_2 = ccp(1140.0f/1440.0f, 450.0f/900.0f);
const int Max_Step = 50;
const float FishMoveSpeed = 75.0f;

const CCPoint Histroy_1_StartPosition = ccp(435, 285);
const CCPoint Histroy_2_StartPosition = ccp(995, 620);

const CCPoint light_10_Position = ccp(277 + 148 * 0, 40);
const CCPoint light_09_Position = ccp(277 + 148 * 1, 40);
const CCPoint light_08_Position = ccp(277 + 148 * 2, 40);
const CCPoint light_07_Position = ccp(277 + 148 * 3, 40);
const CCPoint light_06_Position = ccp(277 + 148 * 4, 40);
const CCPoint light_05_Position = ccp(277 + 148 * 5, 40);
const CCPoint light_04_Position = ccp(277 + 148 * 6, 40);

const CCPoint light_03_Position = ccp(1400, 90 + 120 * 0);
const CCPoint light_02_Position = ccp(1400, 90 + 120 * 1);
const CCPoint light_01_Position = ccp(1400, 90 + 120 * 2);
const CCPoint light_00_Position = ccp(1400, 90 + 120 * 3);
const CCPoint light_27_Position = ccp(1400, 90 + 120 * 4);
const CCPoint light_26_Position = ccp(1400, 90 + 120 * 5);
const CCPoint light_25_Position = ccp(1400, 90 + 120 * 6);

const CCPoint light_24_Position = ccp(277 + 148 * 6, 860);
const CCPoint light_23_Position = ccp(277 + 148 * 5, 860);
const CCPoint light_22_Position = ccp(277 + 148 * 4, 860);
const CCPoint light_21_Position = ccp(277 + 148 * 3, 860);
const CCPoint light_20_Position = ccp(277 + 148 * 2, 860);
const CCPoint light_19_Position = ccp(277 + 148 * 1, 860);
const CCPoint light_18_Position = ccp(277 + 148 * 0, 860);

const CCPoint light_17_Position = ccp(40, 90 + 120 * 6);
const CCPoint light_16_Position = ccp(40, 90 + 120 * 5);
const CCPoint light_15_Position = ccp(40, 90 + 120 * 4);
const CCPoint light_14_Position = ccp(40, 90 + 120 * 3);
const CCPoint light_13_Position = ccp(40, 90 + 120 * 2);
const CCPoint light_12_Position = ccp(40, 90 + 120 * 1);
const CCPoint light_11_Position = ccp(40, 90 + 120 * 0);

const CCPoint countDowm_1_Position = ccp(1120, 230);
const CCPoint countDowm_2_Position = ccp(320, 680);

const float FrogRotateMaxSpeed = 480.0f;

const CCPoint winer_Show_1_Position = ccp(720, 300);
const CCPoint winer_Show_2_Position = ccp(400, 450);
const CCPoint winer_Show_3_Position = ccp(720, 600);
const CCPoint winer_Show_4_Position = ccp(1040, 450);

CCScene* MainScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        MainScene *layer = MainScene::create();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);
    } while (0);

    return scene;
}

bool MainScene::init()
{
    bool bRet = false;
    do 
    {

		nowIndex = 0;
		isHistroyShow = false;
		isCaiGuang = false;

		gameResult[0] = Result_KongQue;
		gameResult[1] = Result_ShiZi;
		gameResult[2] = Result_End;
		nowDoResultIndex = 0;

		CCImage mapIMG;
		mapIMG.initWithImageFile("Image/background.jpg", CCImage::kFmtJpg);
		unsigned char * mapData = mapIMG.getData();
		int dataLen = mapIMG.getDataLen() * 3;
		for(int i = 0; i < dataLen; i += 3)
		{
			moveMap[(i/3)%360][(i/3)/360] = mapData[i];
		}


#if 0
		material.load_00();
		material.load_01();
		material.load_02();
		material.load_03();
		material.load_04();
		material.load_05();
		material.load_06();
		material.load_07();
		material.load_08();
		material.load_09();
		material.load_10();
		material.load_11();
		material.load_12();
		material.load_13();
		material.load_14();
		material.load_15();
		material.load_16();
		material.load_17();
#endif

		//frog = CCSprite::spriteWithFile("Image/frog/qingwa01.png");
		//frog->setPosition(ccp(ScreenSize.width/2.0f, ScreenSize.height/2.0f));
		//frogRandomRotate();
	//	addChild(frog, 3);
		
		lampInit();
		lampRotate();
#if 0
		gotoBG_1(true);

		fishBatch = CCSpriteBatchNode::batchNodeWithTexture(material.fishTexture, 29);
		addChild(fishBatch, 1);
#endif
		this->schedule(schedule_selector(MainScene::updateGame));

		buttomInit();

		countDowmInit();

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Audio/1.wav", true);

		KaiShiYaFen(true);

        bRet = true;
		
    } while (0);

    return bRet;
}

void MainScene::fishRestart(void)
{
	fish_JinSha = new Fish(material.fishTexture, CCRect(840, 143, 144, 72), FishMoveSpeed);
	fish_JinSha->setAnchorPoint(ccp(0.5f, 0.5f));
	fishBatch->addChild(fish_JinSha);
	CCAnimate *animate_00 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("JinSha")/*, false*/); 
	fish_JinSha->runAction(CCRepeatForever::actionWithAction(animate_00));
	updeteBezierPath(120, 30);
	fish_JinSha->restart(&bp.pathPoints);

	fish_YinSha = new Fish(material.fishTexture, CCRect(450, 380, 144, 72), FishMoveSpeed);
	fish_YinSha->setAnchorPoint(ccp(0.5f, 0.5f));
	fishBatch->addChild(fish_YinSha);
	CCAnimate *animate_01 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("YinSha")/*, false*/); 
	fish_YinSha->runAction(CCRepeatForever::actionWithAction(animate_01));
	updeteBezierPath(120, 30);
	fish_YinSha->restart(&bp.pathPoints);

	fish_MoGuiYu = new Fish(material.fishTexture, CCRect(840, 143, 144, 72), FishMoveSpeed);
	fish_MoGuiYu->setAnchorPoint(ccp(0.5f, 0.5f));
	fishBatch->addChild(fish_MoGuiYu);
	CCAnimate *animate_02 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("MoGuiYu")/*, false*/); 
	fish_MoGuiYu->runAction(CCRepeatForever::actionWithAction(animate_02));
	updeteBezierPath(100, 32);
	fish_MoGuiYu->restart(&bp.pathPoints);

	for(int i = 0; i < 2; i++)
	{
		fish_DengLongYu[i] = new Fish(material.fishTexture, CCRect(840, 143, 144, 72), FishMoveSpeed);
		fish_DengLongYu[i]->setAnchorPoint(ccp(0.5f, 0.5f));
		fishBatch->addChild(fish_DengLongYu[i]);
		CCAnimate *animate_03 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("DengLongYu")/*, false*/); 
		fish_DengLongYu[i]->runAction(CCRepeatForever::actionWithAction(animate_03));
		updeteBezierPath(100, 30);
		fish_DengLongYu[i]->restart(&bp.pathPoints);
	}

	for(int i = 0; i < 2; i ++)//2
	{
		fish_HaiGui[i] = new Fish(material.fishTexture, CCRect(840, 143, 144, 72), FishMoveSpeed);
		fish_HaiGui[i]->setAnchorPoint(ccp(0.5f, 0.5f));
		fishBatch->addChild(fish_HaiGui[i]);
		CCAnimate *animate_04 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("HaiGui")/*, false*/); 
		fish_HaiGui[i]->runAction(CCRepeatForever::actionWithAction(animate_04));
		updeteBezierPath(90, 50);
		fish_HaiGui[i]->restart(&bp.pathPoints);
	}

	for(int i = 0; i < 3; i++)
	{
		fish_QiPaoYu[i] = new Fish(material.fishTexture, CCRect(840, 143, 144, 72), FishMoveSpeed);
		fish_QiPaoYu[i]->setAnchorPoint(ccp(0.5f, 0.5f));
		fishBatch->addChild(fish_QiPaoYu[i]);
		CCAnimate *animate_05 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("QiPaoYuA")/*, false*/); 
		fish_QiPaoYu[i]->runAction(CCRepeatForever::actionWithAction(animate_05));
		updeteBezierPath(75, 45);
		fish_QiPaoYu[i]->restart(&bp.pathPoints);
	}

	for(int i = 0; i < 4; i++)
	{
		fish_BanYu[i] = new Fish(material.fishTexture, CCRect(840, 143, 144, 72), FishMoveSpeed);
		fish_BanYu[i]->setAnchorPoint(ccp(0.5f, 0.5f));
		fishBatch->addChild(fish_BanYu[i]);
		CCAnimate *animate_06 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("BanYu")/*, false*/); 
		fish_BanYu[i]->runAction(CCRepeatForever::actionWithAction(animate_06));
		updeteBezierPath(80, 45);
		fish_BanYu[i]->restart(&bp.pathPoints);
	}

	updeteBezierPath(100, 30);
	float fedt = 0;
	for(int i = 0; i < 4; i++)
	{
		fish_CaiHuaYu[i] = new Fish(material.fishTexture, CCRect(840, 143, 144, 72), FishMoveSpeed);
		fish_CaiHuaYu[i]->setAnchorPoint(ccp(0.5f, 0.5f));
		fishBatch->addChild(fish_CaiHuaYu[i]);
		CCAnimate *animate_07 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("CaiHuaYu")/*, false*/); 
		fish_CaiHuaYu[i]->runAction(CCRepeatForever::actionWithAction(animate_07));
		fish_CaiHuaYu[i]->restart(&bp.pathPoints, fedt);
		fedt += 0.8f;
	}

	updeteBezierPath(150, 30);
	fedt = 0;
	for(int i = 0; i < 6; i++)
	{
		fish_HuDieYu[i] = new Fish(material.fishTexture, CCRect(840, 143, 144, 72), FishMoveSpeed*1.1f);
		fish_HuDieYu[i]->setAnchorPoint(ccp(0.5f, 0.5f));
		fishBatch->addChild(fish_HuDieYu[i]);
		fish_HuDieYu[i]->restart(&bp.pathPoints, fedt);
		CCAnimate *animate_08 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("HuDieYu")/*, false*/); 
		fish_HuDieYu[i]->runAction(CCRepeatForever::actionWithAction(animate_08));
		fedt += 0.5f;
	}
}

void MainScene::fishExt(float time)
{
	fish_JinSha->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(time), 
												CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::fishHideEnd)), 
												NULL));

	fish_YinSha->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(time), 
												CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::fishHideEnd)), 
												NULL));

	fish_MoGuiYu->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(time), 
												CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::fishHideEnd)), 
												NULL));

	for(int i = 0; i < 2; i++)
	{
		fish_DengLongYu[i]->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(time), 
															CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::fishHideEnd)), 
															NULL));
	}

	for(int i = 0; i < 2; i ++)
	{
		fish_HaiGui[i]->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(time), 
														CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::fishHideEnd)), 
														NULL));
	}

	for(int i = 0; i < 3; i++)
	{
		fish_QiPaoYu[i]->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(time), 
														CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::fishHideEnd)), 
														NULL));
	}

	for(int i = 0; i < 4; i++)
	{
		fish_BanYu[i]->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(time), 
													CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::fishHideEnd)), 
													NULL));
	}

	for(int i = 0; i < 4; i++)
	{
		fish_CaiHuaYu[i]->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(time), 
														CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::fishHideEnd)), 
														NULL));
	}

	for(int i = 0; i < 6; i++)
	{
		fish_HuDieYu[i]->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(time), 
														CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::fishHideEnd)), 
														NULL));
	}
}

void MainScene::fishHideEnd(CCNode* pSender)
{
	Fish *f = (Fish *)pSender;
	f->stopAllActions();
	fishBatch->removeChild(f, true);
}


void MainScene::updateGame(float dt)
{

}

void MainScene::lampInit(void)
{
	CCPoint hp = ccp(0.5f, 0.2f);
	/*
	lamp[0] = new Lamp("Image/animal_static/lt10.png", Result_JinSha);
	lamp[0]->setAnchorPoint(hp);
	lamp[0]->setRotation(270);
	lamp[0]->setPosition(light_00_Position);
	this->addChild(lamp[0], 3);

	lamp[1] = new Lamp("Image/animal_static/lt02.png", Result_HouZi);
	lamp[1]->setAnchorPoint(hp);
	lamp[1]->setRotation(270);
	lamp[1]->setPosition(light_01_Position);
	this->addChild(lamp[1], 3);

	lamp[2] = new Lamp("Image/animal_static/lt02.png", Result_HouZi);
	lamp[2]->setAnchorPoint(hp);
	lamp[2]->setRotation(270);
	lamp[2]->setPosition(light_02_Position);
	this->addChild(lamp[2], 3);

	lamp[3] = new Lamp("Image/animal_static/lt09.png", Result_YinSha);
	lamp[3]->setAnchorPoint(hp);
	lamp[3]->setRotation(270);
	lamp[3]->setPosition(light_03_Position);
	this->addChild(lamp[3], 3);

	lamp[4] = new Lamp("Image/animal_static/lt09.png", Result_YinSha);
	lamp[4]->setAnchorPoint(hp);
	lamp[4]->setRotation(0);
	lamp[4]->setPosition(light_04_Position);
	this->addChild(lamp[4], 3);

	lamp[5] = new Lamp("Image/animal_static/lt02.png", Result_TuZi);
	lamp[5]->setAnchorPoint(hp);
	lamp[5]->setRotation(0);
	lamp[5]->setPosition(light_05_Position);
	this->addChild(lamp[5], 3);

	lamp[6] = new Lamp("Image/animal_static/lt02.png", Result_TuZi);
	lamp[6]->setAnchorPoint(hp);
	lamp[6]->setRotation(0);
	lamp[6]->setPosition(light_06_Position);
	this->addChild(lamp[6], 3);

	lamp[7] = new Lamp("Image/animal_static/lt10.png", Result_JinSha);
	lamp[7]->setAnchorPoint(hp);
	lamp[7]->setRotation(0);
	lamp[7]->setPosition(light_07_Position);
	this->addChild(lamp[7], 3);

	lamp[8] = new Lamp("Image/animal_static/lt00.png", Result_YanZi);
	lamp[8]->setAnchorPoint(hp);
	lamp[8]->setRotation(0);
	lamp[8]->setPosition(light_08_Position);
	this->addChild(lamp[8], 3);

	lamp[9] = new Lamp("Image/animal_static/lt00.png", Result_YanZi);
	lamp[9]->setAnchorPoint(hp);
	lamp[9]->setRotation(0);
	lamp[9]->setPosition(light_09_Position);
	this->addChild(lamp[9], 3);

	lamp[10] = new Lamp("Image/animal_static/lt08.png", Result_LanSha);
	lamp[10]->setAnchorPoint(hp);
	lamp[10]->setRotation(0);
	lamp[10]->setPosition(light_10_Position);
	this->addChild(lamp[10], 3);

	lamp[11] = new Lamp("Image/animal_static/lt08.png", Result_LanSha);
	lamp[11]->setAnchorPoint(hp);
	lamp[11]->setRotation(90);
	lamp[11]->setPosition(light_11_Position);
	this->addChild(lamp[11], 3);

	lamp[12] = new Lamp("Image/animal_static/lt07.png", Result_GeZi);
	lamp[12]->setAnchorPoint(hp);
	lamp[12]->setRotation(90);
	lamp[12]->setPosition(light_12_Position);
	this->addChild(lamp[12], 3);

	lamp[13] = new Lamp("Image/animal_static/lt07.png", Result_GeZi);
	lamp[13]->setAnchorPoint(hp);
	lamp[13]->setRotation(90);
	lamp[13]->setPosition(light_13_Position);
	this->addChild(lamp[13], 3);

	lamp[14] = new Lamp("Image/animal_static/lt10.png", Result_JinSha);
	lamp[14]->setAnchorPoint(hp);
	lamp[14]->setRotation(90);
	lamp[14]->setPosition(light_14_Position);
	this->addChild(lamp[14], 3);

	lamp[15] = new Lamp("Image/animal_static/lt06.png", Result_KongQue);
	lamp[15]->setAnchorPoint(hp);
	lamp[15]->setRotation(90);
	lamp[15]->setPosition(light_15_Position);
	this->addChild(lamp[15], 3);

	lamp[16] = new Lamp("Image/animal_static/lt06.png", Result_KongQue);
	lamp[16]->setAnchorPoint(hp);
	lamp[16]->setRotation(90);
	lamp[16]->setPosition(light_16_Position);
	this->addChild(lamp[16], 3);

	lamp[17] = new Lamp("Image/animal_static/lt08.png", Result_LanSha);
	lamp[17]->setAnchorPoint(hp);
	lamp[17]->setRotation(90);
	lamp[17]->setPosition(light_17_Position);
	this->addChild(lamp[17], 3);

	lamp[18] = new Lamp("Image/animal_static/lt08.png", Result_LanSha);
	lamp[18]->setAnchorPoint(hp);
	lamp[18]->setRotation(180);
	lamp[18]->setPosition(light_18_Position);
	this->addChild(lamp[18], 3);

	lamp[19] = new Lamp("Image/animal_static/lt05.png", Result_LaoYing);
	lamp[19]->setAnchorPoint(hp);
	lamp[19]->setRotation(180);
	lamp[19]->setPosition(light_19_Position);
	this->addChild(lamp[19], 3);

	lamp[20] = new Lamp("Image/animal_static/lt05.png", Result_LaoYing);
	lamp[20]->setAnchorPoint(hp);
	lamp[20]->setRotation(180);
	lamp[20]->setPosition(light_20_Position);
	this->addChild(lamp[20], 3);

	lamp[21] = new Lamp("Image/animal_static/lt10.png", Result_JinSha);
	lamp[21]->setAnchorPoint(hp);
	lamp[21]->setRotation(180);
	lamp[21]->setPosition(light_21_Position);
	this->addChild(lamp[21], 3);

	lamp[22] = new Lamp("Image/animal_static/lt04.png", Result_ShiZi);
	lamp[22]->setAnchorPoint(hp);
	lamp[22]->setRotation(180);
	lamp[22]->setPosition(light_22_Position);
	this->addChild(lamp[22], 3);

	lamp[23] = new Lamp("Image/animal_static/lt04.png", Result_ShiZi);
	lamp[23]->setAnchorPoint(hp);
	lamp[23]->setRotation(180);
	lamp[23]->setPosition(light_23_Position);
	this->addChild(lamp[23], 3);

	lamp[24] = new Lamp("Image/animal_static/lt09.png", Result_YinSha);//
	lamp[24]->setAnchorPoint(hp);
	lamp[24]->setRotation(180);
	lamp[24]->setPosition(light_24_Position);
	this->addChild(lamp[24], 3);

	lamp[25] = new Lamp("Image/animal_static/lt09.png", Result_YinSha);
	lamp[25]->setAnchorPoint(hp);
	lamp[25]->setRotation(270);
	lamp[25]->setPosition(light_25_Position);
	this->addChild(lamp[25], 3);

	lamp[26] = new Lamp("Image/animal_static/lt03.png", Result_XiongMao);
	lamp[26]->setAnchorPoint(hp);
	lamp[26]->setRotation(270);
	lamp[26]->setPosition(light_26_Position);
	this->addChild(lamp[26], 3);

	lamp[27] = new Lamp("Image/animal_static/lt03.png", Result_XiongMao);
	lamp[27]->setAnchorPoint(hp);
	lamp[27]->setRotation(270);
	lamp[27]->setPosition(light_27_Position);
	this->addChild(lamp[27], 3);
*/
	lampAngle[0] = PointAngle(ccpSub(light_00_Position, ScreenCentre));
	lampAngle[1] = PointAngle(ccpSub(light_01_Position, ScreenCentre));
	lampAngle[2] = PointAngle(ccpSub(light_02_Position, ScreenCentre));
	lampAngle[3] = PointAngle(ccpSub(light_03_Position, ScreenCentre));
	lampAngle[4] = PointAngle(ccpSub(light_04_Position, ScreenCentre));
	lampAngle[5] = PointAngle(ccpSub(light_05_Position, ScreenCentre));
	lampAngle[6] = PointAngle(ccpSub(light_06_Position, ScreenCentre));
	lampAngle[7] = PointAngle(ccpSub(light_07_Position, ScreenCentre));
	lampAngle[8] = PointAngle(ccpSub(light_08_Position, ScreenCentre));
	lampAngle[9] = PointAngle(ccpSub(light_09_Position, ScreenCentre));
	lampAngle[10] = PointAngle(ccpSub(light_10_Position, ScreenCentre));
	lampAngle[11] = PointAngle(ccpSub(light_11_Position, ScreenCentre));
	lampAngle[12] = PointAngle(ccpSub(light_12_Position, ScreenCentre));
	lampAngle[13] = PointAngle(ccpSub(light_13_Position, ScreenCentre));
	lampAngle[14] = PointAngle(ccpSub(light_14_Position, ScreenCentre));
	lampAngle[15] = PointAngle(ccpSub(light_15_Position, ScreenCentre));
	lampAngle[16] = PointAngle(ccpSub(light_16_Position, ScreenCentre));
	lampAngle[17] = PointAngle(ccpSub(light_17_Position, ScreenCentre));
	lampAngle[18] = PointAngle(ccpSub(light_18_Position, ScreenCentre));
	lampAngle[19] = PointAngle(ccpSub(light_19_Position, ScreenCentre));
	lampAngle[20] = PointAngle(ccpSub(light_20_Position, ScreenCentre));
	lampAngle[21] = PointAngle(ccpSub(light_21_Position, ScreenCentre));
	lampAngle[22] = PointAngle(ccpSub(light_22_Position, ScreenCentre));
	lampAngle[23] = PointAngle(ccpSub(light_23_Position, ScreenCentre));
	lampAngle[24] = PointAngle(ccpSub(light_24_Position, ScreenCentre));
	lampAngle[25] = PointAngle(ccpSub(light_25_Position, ScreenCentre));
	lampAngle[26] = PointAngle(ccpSub(light_26_Position, ScreenCentre));
	lampAngle[27] = PointAngle(ccpSub(light_27_Position, ScreenCentre));
}

void MainScene::lampRotate(void)
{
	/*
	float r = 0;
	for(int i = 0; i < 28; i++)
	{
		CCMoveByRound *mbr_00 = CCMoveByRound::actionWithDuration(5.0f, r, 3.0f, 3.0f);
		lamp[i]->runAction(CCRepeatForever::actionWithAction(mbr_00));
		r += 0.15f;
		if(r >= 1)
		{
			r = 0;
		}
	}
	*/
}

void MainScene::lampStop(void)
{
	/*
	for(int i = 0; i < 28; i++)
	{
		lamp[i]->stopAllActions();
	}

	float t = 1;
	lamp[0]->runAction(CCMoveTo::actionWithDuration(t, light_00_Position));
	lamp[1]->runAction(CCMoveTo::actionWithDuration(t, light_01_Position));
	lamp[2]->runAction(CCMoveTo::actionWithDuration(t, light_02_Position));
	lamp[3]->runAction(CCMoveTo::actionWithDuration(t, light_03_Position));
	lamp[4]->runAction(CCMoveTo::actionWithDuration(t, light_04_Position));
	lamp[5]->runAction(CCMoveTo::actionWithDuration(t, light_05_Position));
	lamp[6]->runAction(CCMoveTo::actionWithDuration(t, light_06_Position));
	lamp[7]->runAction(CCMoveTo::actionWithDuration(t, light_07_Position));
	lamp[8]->runAction(CCMoveTo::actionWithDuration(t, light_08_Position));
	lamp[9]->runAction(CCMoveTo::actionWithDuration(t, light_09_Position));
	lamp[10]->runAction(CCMoveTo::actionWithDuration(t, light_10_Position));
	lamp[11]->runAction(CCMoveTo::actionWithDuration(t, light_11_Position));
	lamp[12]->runAction(CCMoveTo::actionWithDuration(t, light_12_Position));
	lamp[13]->runAction(CCMoveTo::actionWithDuration(t, light_13_Position));
	lamp[14]->runAction(CCMoveTo::actionWithDuration(t, light_14_Position));
	lamp[15]->runAction(CCMoveTo::actionWithDuration(t, light_15_Position));
	lamp[16]->runAction(CCMoveTo::actionWithDuration(t, light_16_Position));
	lamp[17]->runAction(CCMoveTo::actionWithDuration(t, light_17_Position));
	lamp[18]->runAction(CCMoveTo::actionWithDuration(t, light_18_Position));
	lamp[19]->runAction(CCMoveTo::actionWithDuration(t, light_19_Position));
	lamp[20]->runAction(CCMoveTo::actionWithDuration(t, light_20_Position));
	lamp[21]->runAction(CCMoveTo::actionWithDuration(t, light_21_Position));
	lamp[22]->runAction(CCMoveTo::actionWithDuration(t, light_22_Position));
	lamp[23]->runAction(CCMoveTo::actionWithDuration(t, light_23_Position));
	lamp[24]->runAction(CCMoveTo::actionWithDuration(t, light_24_Position));
	lamp[25]->runAction(CCMoveTo::actionWithDuration(t, light_25_Position));
	lamp[26]->runAction(CCMoveTo::actionWithDuration(t, light_26_Position));
	lamp[27]->runAction(CCMoveTo::actionWithDuration(t, light_27_Position));
	*/
}

void MainScene::frogRandomRotate(void)
{
	int ri = random.randInt(6) + 6;
	if(random.randInt(100) < 50)
	{
		ri *= -1;
	}
	int ni = ri + nowIndex;
	if(ni < 0)
	{
		ni += 28;
	}
	else if(ni > 27)
	{
		ni -= 28;
	}

	nowIndex = ni;

	float r = 60;//random.randFloat(30, 60);//= GetJiaJiao(frog->getRotation(), lampAngle[ni]);

	float s = 60;//random.randFloat(75.0f, 90.0f);
	//CCFiniteTimeAction* actionDelayTime = CCDelayTime::actionWithDuration(random.randFloat(1.0f, 3.0f));
	CCFiniteTimeAction* actionRotate = CCRotateBy::actionWithDuration(abs(r/s), r);
	CCFiniteTimeAction* actionRotateDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::frogYaFenRotateEnd));
	frog->runAction( CCSequence::actions(actionRotate, actionRotateDone, NULL) );
}

void MainScene::frogYaFenRotateEnd(CCNode* sender)
{
	//frogRandomRotate();
}

void MainScene::frogStartPaoDengRotate(void)
{
	/*
	frog->stopAllActions();

	if(!isCaiGuang)
	{
		light[0] = CCSprite::spriteWithTexture(material.light_0);
		light[0]->setPosition(ccp(88, 88));
		light[0]->setAnchorPoint(ccp(-0.035f,0.5f));
		CCAnimate *animate_00 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("Light_01"), false); 
		light[0]->runAction(animate_00);
		frog->addChild(light[0], 4, 0);
	}
	else
	{
		light[0] = CCSprite::spriteWithTexture(material.light_1);
		light[0]->setPosition(ccp(88, 88));
		light[0]->setAnchorPoint(ccp(-0.035f,0.5f));
		CCAnimate *animate_00 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("Light_03"), false); 
		light[0]->runAction(animate_00);
		frog->addChild(light[0], 4, 0);

		float r = 0;
		for(int i = 1; i < 4; i++)
		{
			r -= 18;
			light[i] = CCSprite::spriteWithTexture(material.light_2);
			light[i]->setPosition(ccp(88, 88));
			light[i]->setAnchorPoint(ccp(-0.035f, 0.5f));
			light[i]->setOpacity(0);
			CCFiniteTimeAction* actionLigheDelayTime = CCDelayTime::actionWithDuration(1);
			CCFiniteTimeAction* actionLightRotate = CCRotateTo::actionWithDuration(abs(r) / 18, r);
			light[i]->runAction(CCSequence::actions(actionLigheDelayTime, CCSpawn::actions(CCFadeIn::actionWithDuration(1), actionLightRotate, NULL), NULL));
			frog->addChild(light[i], 4, i);
		}
	}

 //	nowDoResultIndex = 0;

	frogStartPaoDengAction(gameResult[nowDoResultIndex], 5);
	*/

}

void MainScene::frogStartPaoDengAction(Result rt, int roudCnt)
{
	frogRotateSpeed = 60.0f;
	rotateCnt = 0;
	rotateCntM = getStep(nowIndex, getStopIndex(rt)) + roudCnt * 28;

	if(++nowIndex > 27)
	{
		nowIndex = 0;
	}

	float nextAngle = lampAngle[nowIndex];
	float jiaJiao = GetJiaJiao(frog->getRotation(), nextAngle);
	
	CCFiniteTimeAction* actionfrogDelayTime = CCDelayTime::actionWithDuration(1);
	CCFiniteTimeAction* actionRotate = CCRotateBy::actionWithDuration(abs(jiaJiao) / frogRotateSpeed, jiaJiao);
	CCFiniteTimeAction* actionRotateDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::frogPaoDengRotateEnd));
	frog->runAction( CCSequence::actions(actionfrogDelayTime, actionRotate, actionRotateDone, NULL) );
}

int MainScene::getStep(int startIndex, int endIndex)
{
	int c = 0;
	while(startIndex != endIndex)
	{
		c++;
		if(++startIndex > 27)
		{
			startIndex = 0;
		}
	}
	return c;
}

int MainScene::GetBeiLv(Result r)
{
	int b = 1;
	switch(r)
	{
	case  Result_YanZi:
		b = 3;
		break;
	case Result_TuZi:
		b = 6;
		break;
	case  Result_HouZi:
		b = 8;
		break;
	case  Result_XiongMao:
		b = 12;
		break;
	case  Result_ShiZi:
		b = 3;
		break;
	case  Result_LaoYing:
		b = 6;
		break;
	case  Result_KongQue:
		b = 8;
		break;
	case  Result_GeZi:
		b = 12;
		break;
	case  Result_LanSha:
		b = 24;
		break;
	case  Result_YinSha:
		b = 36;
		break;
	case  Result_JinSha:
		b = 48;
		break;
	default:
		break;
	}
	return b;
}

void MainScene::frogPaoDengRotateEnd(CCNode* sender)
{
	if(++rotateCnt > (rotateCntM - 14))
	{
		if(rotateCnt >= rotateCntM)
		{
			winerShow_Show(gameResult[nowDoResultIndex]);
			
			if(++nowDoResultIndex < 3 && gameResult[nowDoResultIndex] != Result_End)
			{
				CCAnimate *animateLampWin = 0;//CCAnimate::actionWithAnimation(material.lamp_Animatin_2.objectForKey(lamp[nowIndex]->r_type), false);
				lamp[nowIndex]->runAction(CCRepeatForever::actionWithAction(animateLampWin));
			}
			else
			{
				CCFiniteTimeAction* actionfrogLightDelayTimeDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::frogLightStopDT));
				CCFiniteTimeAction* actionfrogLightDelayTime = CCDelayTime::actionWithDuration(1);

				frog->runAction(CCSequence::actions(actionfrogLightDelayTime, actionfrogLightDelayTimeDone, NULL));

				CCAnimate *animateLampWin = 0;//CCAnimate::actionWithAnimation(material.lamp_Animatin_2.objectForKey(lamp[nowIndex]->r_type), false);
				lamp[nowIndex]->runAction(CCRepeatForever::actionWithAction(animateLampWin));
			}
			return;
		}

		if(frogRotateSpeed > 75)
		{
			frogRotateSpeed -= 30;
		}
	}
	else
	{
		if(frogRotateSpeed < FrogRotateMaxSpeed)
		{
			frogRotateSpeed *= 1.2f;
			if(frogRotateSpeed > FrogRotateMaxSpeed)
			{
				frogRotateSpeed = FrogRotateMaxSpeed;
			}
		}
	}

	//出第一个结果时候彩光收起来
	if(nowDoResultIndex == 0 && isCaiGuang && rotateCnt == (rotateCntM - 14))
	{
		for(int i = 1; i < 4; i++)
		{
			CCFiniteTimeAction* actionLightRotate = CCRotateTo::actionWithDuration(1, 0);
			CCFiniteTimeAction* actionLigetRemove = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::frogLightRemove));
			light[i]->runAction(CCFadeOut::actionWithDuration(1));
			light[i]->runAction(CCSequence::actions(actionLightRotate, actionLigetRemove, NULL));
		}
	}

	if(++nowIndex > 27)
	{
		nowIndex = 0;
	}

	float jiaJiao = GetJiaJiao(frog->getRotation(), lampAngle[nowIndex]);
	CCAnimation *animationLamp = 0;//material.lamp_Animatin_1.objectForKey(lamp[nowIndex]->r_type);

	//if(isCaiGuang)
	//{
	//	animationLamp->setDelay(0.2f);
	//}
	//else
	//{
	//	animationLamp->setDelay(0.1f);
	//}

	CCAnimate *animateLamp = CCAnimate::actionWithAnimation(animationLamp/*, false*/);
	CCFiniteTimeAction* actionUnderDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::lampUnderLightEnd));
	lamp[nowIndex]->runAction(CCSequence::actions(animateLamp, actionUnderDone, NULL));

	CCFiniteTimeAction* actionRotate = CCRotateBy::actionWithDuration(abs(jiaJiao) / frogRotateSpeed, jiaJiao);
	CCFiniteTimeAction* actionRotateDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::frogPaoDengRotateEnd));
	frog->runAction( CCSequence::actions(actionRotate, actionRotateDone, NULL) );
}

void MainScene::frogLightStopDT(CCNode* sender)
{
	if (isCaiGuang)
	{
		CCFiniteTimeAction* actionfrogLightEndDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::frogLightEnd));
		CCAnimate *animate_00 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("Light_04")/*, false*/); 
		light[0]->runAction(CCSequence::actions(animate_00, actionfrogLightEndDone, NULL));
	} 
	else
	{
		CCFiniteTimeAction* actionfrogLightEndDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::frogLightEnd));
		CCAnimate *animate_00 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("Light_02")/*, false*/); 
		light[0]->runAction(CCSequence::actions(animate_00, actionfrogLightEndDone, NULL));
	}
}

void MainScene::frogLightEnd(CCNode* sender)
{
	light[0]->stopAllActions();
	frog->removeChildByTag(0, true);
}

//下一个结果
void MainScene::nextResult(void)
{
	if(nowDoResultIndex < 3 && gameResult[nowDoResultIndex] != Result_End)
	{
		winerShow_Hide();
		frogStartPaoDengAction(gameResult[nowDoResultIndex], 0);
	}
}

void MainScene::frogLightRemove(CCNode* sender)
{
	CCSprite *sp = (CCSprite *)sender;
	frog->removeChild(sp, true);
}

void MainScene::winerShow_Show(Result r)
{

	for(int i = 0; i < 4; i++)
	{
		winerShow[i] = CCSprite::spriteWithTexture(material.winer_Texture[0]);
		winerBeiLv[i] = new Numbers(material.winerNumer, CCSize(40,48), ccp(0,0), 0, ccp(0, 0), ALIGN_AT_CENTRE);

		CCAnimate *animate = 0;//CCAnimate::actionWithAnimation(material.winer_Animatin_0.objectForKey((int)r), false); 
		winerShow[i]->runAction(CCRepeatForever::actionWithAction(animate));
		winerShow[i]->runAction(CCFadeIn::actionWithDuration(1));
		addChild(winerShow[i], 5);

		winerBeiLv[i]->setValue(-GetBeiLv(r));
		for(int j = 0; j < MAX_NUMBER_LENGTH; j++)
		{
			winerBeiLv[i]->numberList[j]->runAction(CCFadeIn::actionWithDuration(1));
			addChild(winerBeiLv[i]->numberList[j], 5);
		}
	}

	//设置位置
	winerShow[0]->setPosition(winer_Show_1_Position);
	winerShow[0]->setRotation(0);
	winerShow[0]->setAnchorPoint(ccp(0.5f, 0));
	winerBeiLv[0]->reset(winer_Show_1_Position, 0, ccp(0.5f, 1), ALIGN_AT_CENTRE);

	winerShow[1]->setPosition(winer_Show_2_Position);
	winerShow[1]->setRotation(270);
	winerShow[1]->setAnchorPoint(ccp(0.5f, 0));
	winerBeiLv[1]->reset(winer_Show_2_Position, 270, ccp(0.5f, 1), ALIGN_AT_CENTRE);

	winerShow[2]->setPosition(winer_Show_3_Position);
	winerShow[2]->setRotation(180);
	winerShow[2]->setAnchorPoint(ccp(0.5f, 0));
	winerBeiLv[2]->reset(winer_Show_3_Position, 180, ccp(0.5f, 1), ALIGN_AT_CENTRE);

	winerShow[3]->setPosition(winer_Show_4_Position);
	winerShow[3]->setRotation(90);
	winerShow[3]->setAnchorPoint(ccp(0.5f, 0));
	winerBeiLv[3]->reset(winer_Show_4_Position, 90, ccp(0.5f, 1), ALIGN_AT_CENTRE);
}

void MainScene::winerShow_Hide()
{
	for(int i = 0; i < 4; i++)
	{
		CCFiniteTimeAction* hDone_1 = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::winerShow_Hide_Done));
		CCFiniteTimeAction* fadeOut_1 = CCFadeOut::actionWithDuration(1);
		winerShow[i]->runAction(CCSequence::actions(fadeOut_1, hDone_1, NULL));

		for(int j = 0; j < MAX_NUMBER_LENGTH; j++)
		{
			CCFiniteTimeAction* hDone_2 = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::winerShow_Hide_Done));
			CCFiniteTimeAction* fadeOut_2 = CCFadeOut::actionWithDuration(1);
			winerBeiLv[i]->numberList[j]->runAction(CCSequence::actions(fadeOut_2, hDone_2, NULL));
		}
	}
}

void MainScene::winerShow_Hide_Done(CCNode* sender)
{
	this->removeChild(sender, true);
}

void MainScene::sharkShootStart(void)
{
	//圈圈效果

}

void MainScene::sharkRoundParticleEnd(CCNode* sender)
{
	this->removeChild(sender, true);
	shootCnt = 0;
	sharkShoot();
	
	CCFiniteTimeAction* actionDelayTime = CCDelayTime::actionWithDuration(random.randFloat(0.5f, 1.0f));
	CCFiniteTimeAction* dtDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::randomFireworkNext));
	frog->runAction(CCSequence::actions(actionDelayTime, dtDone, NULL));

	randomFirework();
}

void MainScene::sharkShoot(void)
{
	//计数
	if(++shootCnt > 10)
	{
		return;
	}

	//旋转
	int ri = random.randInt(5) + 5;
	if(random.randInt(100) < 50)
	{
		ri *= -1;
	}

	int ni = ri + nowIndex;
	if(ni < 0)
	{
		ni += 28;
	}
	else if(ni > 27)
	{
		ni -= 28;
	}

	nowIndex = ni;

	frog->setRotation(lampAngle[nowIndex]);

	CCAnimate *animate = 0;//CCAnimate::actionWithAnimation(material.animationCache.animationByName("QingWaBianShen"), false); 
	CCFiniteTimeAction* actionDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::sharkParticleShoot));
	frog->runAction( CCSequence::actions(animate, actionDone, NULL) );

	//发射鲨鱼
	//鲨鱼
	//粒子效果

	int i = random.randInt(2) + 8;
	CCSprite *shark = CCSprite::spriteWithTexture(material.winer_Texture[i]);
	shark->setPosition(ScreenCentre);
	shark->setScale(0.1f);
	shark->setRotation(frog->getRotation() - 90);

	CCPoint moveAimP = ccpSub(lamp[nowIndex]->getPosition(), ScreenCentre);
	moveAimP.x *= 2.0f;
	moveAimP.y *= 2.0f;
	moveAimP = ccpAdd(ScreenCentre, moveAimP);

	float t = ccpDistance(moveAimP, ScreenCentre) / 1200;

	CCAnimate *sharkAnimate = 0;//CCAnimate::actionWithAnimation(material.winer_Animatin_0.objectForKey(i)/*, false*/);
	CCFiniteTimeAction* actionScale_1 = CCScaleTo::actionWithDuration(t, 2.0f, 2.0f);
	CCFiniteTimeAction* actionMove_1 = CCMoveTo::actionWithDuration(t, moveAimP);
	CCFiniteTimeAction* moveDone_1 = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::sharkParticleEndDone));

	shark->runAction(CCRepeatForever::actionWithAction(sharkAnimate));
	shark->runAction(actionScale_1);
	shark->runAction(CCSequence::actions(actionMove_1, moveDone_1, NULL));

	CCSprite *ptc = CCSprite::spriteWithTexture(material.sharkShootParticleTX);
	ptc->setPosition(ScreenCentre);
	ptc->setAnchorPoint(ccp(0, 0.5f));
	ptc->setScale(0.17f);
	ptc->setRotation(frog->getRotation() + 180);

	CCAnimate *ptcAnimate = CCAnimate::actionWithAnimation(material.animationCache.animationByName("SharkShootParticle")/*, false*/);
	CCFiniteTimeAction* actionScale_2 = CCScaleTo::actionWithDuration(t, 3.4f, 3.4f);
	CCFiniteTimeAction* actionMove_2 = CCMoveTo::actionWithDuration(t, moveAimP);
	CCFiniteTimeAction* moveDone_2 = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::sharkParticleEndDone));

	ptc->runAction(CCRepeatForever::actionWithAction(ptcAnimate));
	ptc->runAction(actionScale_2);
	ptc->runAction(CCSequence::actions(actionMove_2, moveDone_2, NULL));

	addChild(ptc, 7);
	addChild(shark, 7);
}

void MainScene::sharkParticleShoot(CCNode* sender)
{
	sharkShoot();
}

void MainScene::sharkParticleEndDone(CCNode* sender)
{
	this->removeChild(sender, true);
}

void MainScene::randomFirework(void)
{
	CCSprite *spr = CCSprite::spriteWithTexture(material.sharkFireParticleTX);
	spr->setPosition(ccp(random.randInt(ScreenSize.width), random.randInt(ScreenSize.height)));
	spr->setRotation(random.randInt(360));
	spr->setScale(1.5f);

	CCAnimate *animate = NULL;

	if(random.randInt(100) < 50)
	{
		animate = CCAnimate::actionWithAnimation(material.animationCache.animationByName("CaiJinParticle_B")/*, false*/);
	}
	else
	{
		animate = CCAnimate::actionWithAnimation(material.animationCache.animationByName("CaiJinParticle_A")/*, false*/);
	}

	CCFiniteTimeAction* actionDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::sharkParticleEndDone));
	spr->runAction(CCSequence::actions(animate, actionDone, NULL));

	addChild(spr, 6);
}

void MainScene::randomFireworkNext(CCNode* sender)
{
	if(shootCnt > 10)
	{
		return;
	}

	CCFiniteTimeAction* actionDelayTime = CCDelayTime::actionWithDuration(random.randFloat(0.4f, 0.6f));
	CCFiniteTimeAction* dtDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::randomFireworkNext));
	frog->runAction(CCSequence::actions(actionDelayTime, dtDone, NULL));

	randomFirework();
}

void MainScene::lampUnderLightEnd(CCNode* sender)
{
	Lamp *l = (Lamp *)sender;
	//CCAnimate *animateLamp = CCAnimate::actionWithAnimation(material.lamp_Animatin_0.objectForKey(l->r_type)/*, false*/);
	//l->runAction(animateLamp);
}

void MainScene::countDowmInit(void)
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			countDowm[i][j] = new NumberSprite(material.daoJiShiNumer, CCSize(40, 48));
		}
	}

	countDowm[0][0]->setPosition(countDowm_1_Position);
	countDowm[0][1]->setPosition(countDowm_1_Position);
	countDowm[0][0]->setAnchorPoint(ccp(1, 0.5f));
	countDowm[0][1]->setAnchorPoint(ccp(0, 0.5f));

	countDowm[1][0]->setPosition(countDowm_2_Position);
	countDowm[1][1]->setPosition(countDowm_2_Position);
	countDowm[1][0]->setAnchorPoint(ccp(1, 0.5f));
	countDowm[1][1]->setAnchorPoint(ccp(0, 0.5f));
	countDowm[1][0]->setRotation(180);
	countDowm[1][1]->setRotation(180);
}

void MainScene::countDowmShow(int time)
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			addChild(countDowm[i][j], 4);
		}
	}
	countDowmSet(time);
}

void MainScene::countDowmHide(void)
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			removeChild(countDowm[i][j], false);
		}
	}
}

float MainScene::GetJiaJiao(float s_a, float e_a)
{
	float jr = e_a - s_a;

	while (jr > 180)
	{
		jr -= 360;
	}

	while(jr < -180)
	{
		jr += 360;
	}

	return jr;
}

int MainScene::getStopIndex(Result rt)
{
	switch(rt)
	{
	case  Result_YanZi:
		if(random.randInt(1000) < 500)
		{
			return 8;
		}
		else
		{
			return 9;
		}
	case Result_TuZi:
		if(random.randInt(1000) < 500)
		{
			return 5;
		}
		else
		{
			return 6;
		}
	case  Result_HouZi:
		if(random.randInt(1000) < 500)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	case  Result_XiongMao:
		if(random.randInt(1000) < 500)
		{
			return 27;
		}
		else
		{
			return 26;
		}
	case  Result_ShiZi:
		if(random.randInt(1000) < 500)
		{
			return 23;
		}
		else
		{
			return 22;
		}
	case  Result_LaoYing:
		if(random.randInt(1000) < 500)
		{
			return 20;
		}
		else
		{
			return 19;
		}
	case  Result_KongQue:
		if(random.randInt(1000) < 500)
		{
			return 16;
		}
		else
		{
			return 15;
		}
	case  Result_GeZi:
		if(random.randInt(1000) < 500)
		{
			return 13;
		}
		else
		{
			return 12;
		}
	case  Result_LanSha:
		if(random.randInt(1000) < 250)
		{
			return 10;
		}
		else if(random.randInt(1000) < 500)
		{
			return 11;
		}
		else if(random.randInt(1000) < 750)
		{
			return 17;
		}
		else
		{
			return 18;
		}
	case  Result_YinSha:
		if(random.randInt(1000) < 250)
		{
			return 3;
		}
		else if(random.randInt(1000) < 500)
		{
			return 4;
		}
		else if(random.randInt(1000) < 750)
		{
			return 25;
		}
		else
		{
			return 24;
		}
	case  Result_JinSha:
		if(random.randInt(1000) < 250)
		{
			return 0;
		}
		else if(random.randInt(1000) < 500)
		{
			return 7;
		}
		else if(random.randInt(1000) < 750)
		{
			return 14;
		}
		else
		{
			return 21;
		}
	default:
		break;
	}

	return 1;
}

void MainScene::countDowmSet(int time)
{
	countDowm[0][0]->setValue(time%10);
	countDowm[0][1]->setValue(time/10);

	countDowm[1][0]->setValue(time%10);
	countDowm[1][1]->setValue(time/10);
}

void MainScene::updeteBezierPath(float len, float angle)
{
	CCPoint p;
	switch(random.randInt(2))
	{
	case 0:
		p = ccp(FishCreatPoint_0.x * ScreenSize.width, FishCreatPoint_0.y * ScreenSize.height);
		break;
	case 1:
		p = ccp(FishCreatPoint_1.x * ScreenSize.width, FishCreatPoint_1.y * ScreenSize.height);
		break;
	case 2:
		p = ccp(FishCreatPoint_2.x * ScreenSize.width, FishCreatPoint_2.y * ScreenSize.height);
		break;
	default:
		p = ccp(FishCreatPoint_0.x * ScreenSize.width, FishCreatPoint_0.y * ScreenSize.height);
		break;
	}

	bp.ClearAnchorPoints();
	bp.ClearPathPoints();
	bp.AddAnchorPoint(p);

	angle = CC_DEGREES_TO_RADIANS(angle);

	float maxLen = len;
	float minLen = len * 0.8f;

	float r = random.randFloat(0, 6.28f);
	float l = random.randFloat(minLen, maxLen);
	p = ccpAdd(p, ccp(l * cos(r), l * sin(r)));
	bp.AddAnchorPoint(p);

	int c = 0;
	do
	{
		CCPoint cp;
		float br = r;
		int d = 0;
		do 
		{
			if(d++ < 8)
			{
				if(random.randInt(100) > 50)
				{
					br += random.randFloat(0, angle);
				}
				else
				{
					br -= random.randFloat(0, angle);
				}
				l = random.randFloat(minLen, maxLen);
				cp = ccpAdd(p, ccp(l * cos(br), l * sin(br)));
			}
			else
			{
				//======================================================
				float ar = PointAngle(ccpSub(p, ccp(720, 450)));
				br = r;
				if(ar - br < 0)
				{
					//顺时针
					do 
					{
						br += 0.1f;
						l = 100;
						cp = ccpAdd(p, ccp(l * cos(br), l * sin(br)));
					} while (! CCRect::CCRectContainsPoint(ScreenRect, cp) || moveMap[(int)(cp.x/4.0f)][225 - (int)(cp.y/4.0f)] < 200);
					break;
				}
				else
				{
					do 
					{
						br -= 0.1f;
						l = 100;
						cp = ccpAdd(p, ccp(l * cos(br), l * sin(br)));
					} while (! CCRect::CCRectContainsPoint(ScreenRect, cp) || moveMap[(int)(cp.x/4.0f)][225 - (int)(cp.y/4.0f)] < 200);
					break;
				}
			}
		} while( ! CCRect::CCRectContainsPoint(ScreenRect, cp) || moveMap[(int)(cp.x/4.0f)][225 - (int)(cp.y/4.0f)] < 200);

		p = cp;
		r = br;
		bp.AddAnchorPoint(p);
	}while(c++ < Max_Step);

	bp.UpdatePath();
}

void MainScene::gotoBG_1(bool first)
{
	float t = 1;
	
	backGroup_1 = CCSprite::spriteWithFile("Image/bg_1.png");
	backGroup_1->setPosition(ccp(ScreenSize.width/2.0f, ScreenSize.height/2.0f));
	backGroup_1->setScale(2);
	backGroup_1->setTextureRect(CCRect(0,0,720,450));
	backGroup_1->runAction(CCFadeIn::actionWithDuration(t));
	this->addChild(backGroup_1, 0);
  

	shuiWen_1 = CCSprite::spriteWithFile("Image/wave/Ashui720x450/Ashui_001.png");
	shuiWen_1->setPosition(ccp(ScreenSize.width/2.0f, ScreenSize.height/2.0f));
	shuiWen_1->setScale(2);
	CCAnimate *shuiWenAnimate_1 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("ShuiWen_1")/*, false*/);
	shuiWen_1->runAction(CCRepeatForever::actionWithAction(shuiWenAnimate_1));
	shuiWen_1->runAction(CCFadeIn::actionWithDuration(t));
	this->addChild(shuiWen_1, 3);

	shuiCaoBatch = CCSpriteBatchNode::batchNodeWithTexture(material.shuiCaoTexture, 29);

	SCSprite_1 = CCSprite::spriteWithTexture(material.shuiCaoTexture, CCRectMake(305, 289, 144, 160));
	SCSprite_1->setAnchorPoint(ccp(0, 0));
	SCSprite_1->setPosition(ccp(828, 275));
	CCAnimate *shuiChaoAnim_1 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("ShuiCao_01")/*, false*/); 
	SCSprite_1->runAction(CCRepeatForever::actionWithAction(shuiChaoAnim_1));
	SCSprite_1->runAction(CCFadeIn::actionWithDuration(t));
	shuiCaoBatch->addChild(SCSprite_1);

	SCSprite_2 = CCSprite::spriteWithTexture(material.shuiCaoTexture, CCRectMake(289, 610, 216, 256));
	SCSprite_2->setAnchorPoint(ccp(0, 0));
	SCSprite_2->setPosition(ccp(242, 300));
	CCAnimate *shuiChaoAnim_2 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("ShuiCao_02")/*, false*/); 
	SCSprite_2->runAction(CCRepeatForever::actionWithAction(shuiChaoAnim_2));
	SCSprite_2->runAction(CCFadeIn::actionWithDuration(t));
	shuiCaoBatch->addChild(SCSprite_2);

	SCSprite_3 = CCSprite::spriteWithTexture(material.shuiCaoTexture, CCRectMake(0, 0, 152, 144));
	SCSprite_3->setAnchorPoint(ccp(0, 0));
	SCSprite_3->setPosition(ccp(671, 578));
	CCAnimate *shuiChaoAnim_3 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("ShuiCao_03")/*, false*/); 
	SCSprite_3->runAction(CCRepeatForever::actionWithAction(shuiChaoAnim_3));
	SCSprite_3->runAction(CCFadeIn::actionWithDuration(t));
	shuiCaoBatch->addChild(SCSprite_3);

	this->addChild(shuiCaoBatch, 2);

	if(!first)
	{
		backGroup_2->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(t), 
			CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::bg_CEnd)), 
			NULL));
		shuiWen_2->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(t), 
			CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::bg_CEnd)), 
			NULL));
	}

}

void MainScene::gotoBG_2(void)
{
	float t = 1;
	
	backGroup_1->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(t), 
							CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::bg_CEnd)), 
							NULL));
							
	shuiWen_1->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(t), 
							CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::bg_CEnd)), 
							NULL));

	SCSprite_1->runAction(CCFadeOut::actionWithDuration(t));
	SCSprite_2->runAction(CCFadeOut::actionWithDuration(t));
	SCSprite_3->runAction(CCFadeOut::actionWithDuration(t));
	shuiCaoBatch->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(t), 
							CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::bg_CEnd)), 
							NULL));
	
	backGroup_2 = CCSprite::spriteWithFile("Image/bg_2.png");
	backGroup_2->setPosition(ccp(ScreenSize.width/2.0f, ScreenSize.height/2.0f));
	backGroup_2->setScale(2);
	backGroup_2->setTextureRect(CCRect(0,0,720,450));
	backGroup_2->runAction(CCFadeIn::actionWithDuration(t));
	this->addChild(backGroup_2, 1);
  
	shuiWen_2 = CCSprite::spriteWithFile("Image/wave/Bshui720x450/Bshui_01.png");
	shuiWen_2->setPosition(ccp(ScreenSize.width/2.0f, ScreenSize.height/2.0f));
	shuiWen_2->setScale(2);
	CCAnimate *shuiWenAnimate_2 = CCAnimate::actionWithAnimation(material.animationCache.animationByName("ShuiWen_2")/*, false*/);
	shuiWen_2->runAction(CCRepeatForever::actionWithAction(shuiWenAnimate_2));
	shuiWen_2->runAction(CCFadeIn::actionWithDuration(t));
	this->addChild(shuiWen_2, 3);
}

void MainScene::bg_CEnd(CCNode* sender)
{
	removeChild(sender, true);
}

void MainScene::buttomInit(void)
{
	CCPoint p = ccp(180, 400 + 32);
	CCMenuItemImage *pCloseItem_01 = CCMenuItemImage::create/*itemFromNormalImage*/("Image/Buttom/Buttom_A.png",
																			"Image/Buttom/Buttom_A.png",
																			this,
																			menu_selector(MainScene::buttom_A_Put));
	pCloseItem_01->setPosition(p);
	CCMenu* pMenu_01 = CCMenu::menuWithItems(pCloseItem_01, NULL);
	pMenu_01->setPosition(CCPointZero);

	this->addChild(pMenu_01, 5);
	p.x += 64;

	CCMenuItemImage *pCloseItem_02 = CCMenuItemImage::create/*itemFromNormalImage*/("Image/Buttom/Buttom_B.png",
																			"Image/Buttom/Buttom_B.png",
																			this,
																			menu_selector(MainScene::buttom_B_Put));
	pCloseItem_02->setPosition(p);
	CCMenu* pMenu_02 = CCMenu::menuWithItems(pCloseItem_02, NULL);
	pMenu_02->setPosition(CCPointZero);
	this->addChild(pMenu_02, 5);
	p.x += 64;

	CCMenuItemImage *pCloseItem_03 = CCMenuItemImage::create/*itemFromNormalImage*/("Image/Buttom/Buttom_C.png",
																			"Image/Buttom/Buttom_C.png",
																			this,
																			menu_selector(MainScene::buttom_C_Put));
	pCloseItem_03->setPosition(p);
	CCMenu* pMenu_03 = CCMenu::menuWithItems(pCloseItem_03, NULL);
	pMenu_03->setPosition(CCPointZero);
	this->addChild(pMenu_03, 5);
	p.x += 64;

	CCMenuItemImage *pCloseItem_04 = CCMenuItemImage::create/*itemFromNormalImage*/("Image/Buttom/Buttom_D.png",
																			"Image/Buttom/Buttom_D.png",
																			this,
																			menu_selector(MainScene::buttom_D_Put));
	pCloseItem_04->setPosition(p);
	CCMenu* pMenu_04 = CCMenu::menuWithItems(pCloseItem_04, NULL);
	pMenu_04->setPosition(CCPointZero);
	this->addChild(pMenu_04, 5);
	p.x += 64;

	CCMenuItemImage *pCloseItem_05 = CCMenuItemImage::create/*itemFromNormalImage*/("Image/Buttom/Buttom_E.png",
																			"Image/Buttom/Buttom_E.png",
																			this,
																			menu_selector(MainScene::buttom_E_Put));
	pCloseItem_05->setPosition(p);
	CCMenu* pMenu_05 = CCMenu::menuWithItems(pCloseItem_05, NULL);
	pMenu_05->setPosition(CCPointZero);
	this->addChild(pMenu_05, 5);
	p.x += 64;

	CCMenuItemImage *pCloseItem_06 = CCMenuItemImage::create/*itemFromNormalImage*/("Image/Buttom/Buttom_F.png",
																			"Image/Buttom/Buttom_F.png",
																			this,
																			menu_selector(MainScene::buttom_F_Put));
	pCloseItem_06->setPosition(p);
	CCMenu* pMenu_06 = CCMenu::menuWithItems(pCloseItem_06, NULL);
	pMenu_06->setPosition(CCPointZero);
	this->addChild(pMenu_06, 5);
	p.x += 64;
}


void MainScene::historyRestart(unsigned char *data)
{
	if(isHistroyShow)
	{
		return;
	}

	isHistroyShow = true;
/*
	for(int i = 0; i < 20; i++)
	{
		if(data[i] >= 0 && data[i] <= 10)
		{
			//CCSprite *spr = CCSprite::spriteWithTexture(material.historyTexture[data[i]]);
			//spr->setPosition(ccpAdd(Histroy_1_StartPosition, ccp((i%10)*64, -(i/10)*64)));
			//spr->setRotation(0);
			//spr->setScale(0);
			//historySPRArray[0][i] = spr;
		//	CCFiniteTimeAction* actionScale = CCScaleTo::actionWithDuration(0.3f, 1, 1);
			//spr->runAction(actionScale);
			//CCMoveByRound *mbr = CCMoveByRound::actionWithDuration(3.0f, 0.0f, 2.0f, 2.0f);
		//	spr->runAction(CCRepeatForever::actionWithAction(mbr));

		//	this->addChild(spr, 3);
		}
	}

	for(int i = 0; i < 20; i++)
	{
		if(data[i] >= 0 && data[i] <= 10)
		{
			CCSprite *spr = CCSprite::spriteWithTexture(material.historyTexture[data[i]]);
			spr->setPosition(ccpAdd(Histroy_2_StartPosition, ccp(-(i%10)*64, (i/10)*64)));
			spr->setRotation(180);
			spr->setScale(0);
			historySPRArray[1][i] = spr;
			CCFiniteTimeAction* actionScale = CCScaleTo::actionWithDuration(0.3f, 1, 1);
			spr->runAction(actionScale);
			CCMoveByRound *mbr = CCMoveByRound::actionWithDuration(3.0f, 0.0f, 2.0f, 2.0f);
			spr->runAction(CCRepeatForever::actionWithAction(mbr));

			this->addChild(spr, 3);
		}
	}*/
}

void MainScene::historyEnd(void)
{
	isHistroyShow = false;

	for(int i = 0; i < 20; i++)
	{
		if(historySPRArray[0][i] != NULL)
		{
			CCFiniteTimeAction* actionScale = CCScaleTo::actionWithDuration(0.3f, 0, 0);
			CCFiniteTimeAction* actionScaleDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::historyScaleActionEnd));
			historySPRArray[0][i]->runAction(CCSequence::actions(actionScale, actionScaleDone, NULL));
		}
	}

	for(int i = 0; i < 20; i++)
	{
		if(historySPRArray[1][i] != NULL)
		{
			CCFiniteTimeAction* actionScale = CCScaleTo::actionWithDuration(0.3f, 0, 0);
			CCFiniteTimeAction* actionScaleDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::historyScaleActionEnd));
			historySPRArray[1][i]->runAction(CCSequence::actions(actionScale, actionScaleDone, NULL));
		}
	}
}

void MainScene::historyScaleActionEnd(CCNode* sender)
{
	CCSprite *h = (CCSprite *)sender;
	this->removeChild(h, true);
}

void MainScene::KaiShiYaFen(bool first)
{
	unsigned char data[20];
	data[0] = 0;
	data[1] = 1;
	data[2] = 2;
	data[3] = 3;
	data[4] = 4;
	data[5] = 5;
	data[6] = 6;
	data[7] = 7;
	data[8] = 8;
	data[9] = 9;
	data[10] = 10;
	data[11] = 0;
	data[12] = 1;
	data[13] = 2;
	data[14] = 3;
	data[15] = 4;
	data[16] = 5;
	data[17] = 6;
	data[18] = 7;
	data[19] = 8;
	historyRestart(data);
	fishRestart();
	lampRotate();
	//frogRandomRotate();
	gotoBG_1(first);
}

void MainScene::KaiShiPaoDeng(void)
{
	gotoBG_2();
	historyEnd();
	fishExt(1);
	frogStartPaoDengRotate();
}

void MainScene::ShowCaiJin(void)
{
	winerShow_Hide();
	//显示彩金Logo

}

void MainScene::buttom_A_Put(CCObject* pSender)
{
	KaiShiYaFen(false);
}

void MainScene::buttom_B_Put(CCObject* pSender)
{
	KaiShiPaoDeng();
}

void MainScene::buttom_C_Put(CCObject* pSender)
{
	nextResult();
}

void MainScene::buttom_D_Put(CCObject* pSender)
{
	ShowCaiJin();
}

void MainScene::buttom_E_Put(CCObject* pSender)
{
	//nextResult();
	//winerShow_Init(Result_GeZi);

	shootCnt = 0;
	sharkShoot();

	CCFiniteTimeAction* actionDelayTime = CCDelayTime::actionWithDuration(random.randFloat(0.5f, 1.0f));
	CCFiniteTimeAction* dtDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::randomFireworkNext));
	frog->runAction(CCSequence::actions(actionDelayTime, dtDone, NULL));
	randomFirework();
}

void MainScene::buttom_F_Put(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void MainScene::buttom_G_Put(CCObject* pSender)
{

}

void MainScene::buttom_H_Put(CCObject* pSender)
{
	
}
