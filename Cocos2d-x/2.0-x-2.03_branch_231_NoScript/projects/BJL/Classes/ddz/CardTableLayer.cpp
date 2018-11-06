#include "CardTableLayer.h"
#include "SoundControl.h"
#include "SceneView.h"
#include "ViewMenuLayer.h"
#include "globalUnits/GlobalUnits.h"
#include "common/CocosUnits.h"
CardTableLayer::CardTableLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CardTableLayer::SetPlaceLandScore), "UpdatePlacelBankScore", NULL);
}
CardTableLayer::~CardTableLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "UpdatePlacelBankScore");
}

bool CardTableLayer::init()
{
	size = CCDirector::sharedDirector()->getWinSize();
	//背景图片
	//if(!CCNode::init())
	//{
	//	return false;
	//}
	CCSprite *Sprite = CCSprite::create("BJL/BJL_02.png");
	Sprite->setAnchorPoint(CCPointZero);
	Sprite->setPosition(ccp(0,0));
	addChild(Sprite);

	//游戏记录
	SpriteGameRecord = CCSprite::createWithSpriteFrame(spriteFrame("BJL_06.png"));
	SpriteGameRecord->setAnchorPoint(CCPointZero);
	SpriteGameRecord->setPosition(ccp(60,size.height*0.8));
	addChild(SpriteGameRecord);

	CCSprite *SpriteBankerUser = CCSprite::create("BJL/BJL_05.png");
	SpriteBankerUser->setAnchorPoint(CCPointZero);
	SpriteBankerUser->setPosition(ccp(size.width/2+90,size.height*0.8));
	addChild(SpriteBankerUser);

	//--背景效果
	//schedule(schedule_selector(CardTableLayer::upHaiou),8.0f);
	m_cardTableBatchNode = CCSpriteBatchNode::create(texture_name::s_cardTable);
	this->addChild(m_cardTableBatchNode);


	//玩家信息

	int m_cbGender = g_GlobalUnits.getGolbalUserData()->cbGender;
	if (m_cbGender == 1)
	{
		SpriteMyUsed = CCSprite::createWithSpriteFrame(spriteFrame("head_4.png"));
	}else
	{
		SpriteMyUsed = CCSprite::createWithSpriteFrame(spriteFrame("min_4.png"));

	}
	SpriteMyUsed->setAnchorPoint(CCPointZero);
	SpriteMyUsed->setScale(0.8);
	SpriteMyUsed->setPosition(ccp(5,5));
	addChild(SpriteMyUsed);
	string szText2 = g_GlobalUnits.getGolbalUserData()->szNickName;
	m_nikeName = CCLabelTTF::create(szText2.c_str(),"Helvetica-Bold",20);
	m_nikeName->setAnchorPoint(CCPointZero);
	m_nikeName->setColor(ccc3(255,204,0));
	m_nikeName->setPosition(ccp(size.width*0.2,62));
	this->addChild(m_nikeName,1);

	//金币数字
	szText0 = g_GlobalUnits.getGolbalUserData()->lScore;
	string szText1 =addCommaToNumber(szText0);
	m_coinNumberAtlas = CCLabelTTF::create(szText1.c_str(),"Helvetica-Bold",20);
	m_coinNumberAtlas->setAnchorPoint(ccp(0,0));
	m_coinNumberAtlas->setColor(ccc3(255,204,0));
	m_coinNumberAtlas->setPosition(ccp(size.width*0.2,35));
	this->addChild(m_coinNumberAtlas);

	m_Chengji  = CCLabelTTF::create("0","Helvetica-Bold",20);
	m_Chengji->setAnchorPoint(CCPointZero);
	m_Chengji->setColor(ccc3(255,204,0));
	m_Chengji->setPosition(ccp(size.width*0.2,7));
	addChild(m_Chengji);


	//显示庄家数目

	FinUsedSprite = CCSprite::createWithSpriteFrame(spriteFrame("head_1.png"));
	FinUsedSprite->setAnchorPoint(ccp(0,0));
	FinUsedSprite->setScale(0.5);
	FinUsedSprite->setPosition(ccp(size.width*0.65-14,size.height*0.85-8));
	addChild(FinUsedSprite);

	laberName=CCLabelTTF::create("","",16);
	laberName->setAnchorPoint(ccp(0,0));
	laberName->setColor(ccc3(173,118,0));
	laberName->setPosition(ccp(size.width*0.8-20,size.height*0.95));
	addChild(laberName);

	goldname=CCLabelTTF::create("","",16);
	goldname->setAnchorPoint(CCPointZero);
	goldname->setColor(ccc3(173,118,0));
	goldname->setPosition(ccp(size.width*0.8-20,size.height*0.95-20));
	addChild(goldname);

	ChengjiScore=CCLabelTTF::create("0","",16);
	ChengjiScore->setAnchorPoint(CCPointZero);
	ChengjiScore->setColor(ccc3(173,118,0));
	ChengjiScore->setPosition(ccp(size.width*0.8-20,size.height*0.95-40));
	addChild(ChengjiScore);

	JiNumber = CCLabelTTF::create("0","",16);
	JiNumber->setAnchorPoint(CCPointZero);
	JiNumber->setColor(ccc3(173,118,0));
	JiNumber->setPosition(ccp(size.width*0.8-20,size.height*0.95-60));
	addChild(JiNumber);

	FinUsedSprite->setVisible(false);
	laberName->setVisible(false);
	goldname->setVisible(false);
	ChengjiScore->setVisible(false);
	JiNumber->setVisible(false);
	//排队动画
	m_pdNode = CCSpriteBatchNode::create(texture_name::s_cardTable);
	m_pdNode->setPosition(ccp(size.width/2,size.height/2));
	CCSprite * paiziSprite = CCSprite::createWithSpriteFrameName(texture_name::s_paizi);
	paiziSprite->setAnchorPoint(ccp(0.5f,0));
	//CCSprite * zawuSprite = CCSprite::createWithSpriteFrameName(texture_name::s_zawu);
	//zawuSprite->setAnchorPoint(ccp(0.5f,1.0f));
	//m_pdNode->addChild(paiziSprite);
	//m_pdNode->addChild(zawuSprite);
	m_pdNode->setPositionY(size.height/2-50.0f);
	//等待其他玩家中
	CCSprite * dengSprite = CCSprite::createWithSpriteFrameName(texture_name::s_font_deng);
	dengSprite->setPosition(ccp(-40.0f,40.0f));
	float runTime = 0.1f;
	dengSprite->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCMoveTo::create(runTime,ccp(dengSprite->getPositionX(),dengSprite->getPositionY()+10)),
		CCMoveTo::create(runTime,ccp(dengSprite->getPositionX(),dengSprite->getPositionY())),CCDelayTime::create(6*runTime),NULL)));

	m_pdNode->addChild(dengSprite);
	CCSprite * daiSprite = CCSprite::createWithSpriteFrameName(texture_name::s_font_dai);
	daiSprite->setPosition(ccp(dengSprite->getPositionX()+dengSprite->getContentSize().width,dengSprite->getPositionY()));
	daiSprite->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCDelayTime::create(runTime),CCMoveTo::create(runTime,ccp(daiSprite->getPositionX(),daiSprite->getPositionY()+10)),
		CCMoveTo::create(runTime,ccp(daiSprite->getPositionX(),daiSprite->getPositionY())),CCDelayTime::create(5*runTime),NULL)));

	m_pdNode->addChild(daiSprite);
	CCSprite * qiSprite = CCSprite::createWithSpriteFrameName(texture_name::s_font_qi);
	qiSprite->setPosition(ccp(daiSprite->getPositionX()+daiSprite->getContentSize().width,dengSprite->getPositionY()));
	qiSprite->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCDelayTime::create(2*runTime),CCMoveTo::create(runTime,ccp(qiSprite->getPositionX(),qiSprite->getPositionY()+10)),
		CCMoveTo::create(runTime,ccp(qiSprite->getPositionX(),qiSprite->getPositionY())),CCDelayTime::create(4*runTime),NULL)));

	m_pdNode->addChild(qiSprite);
	CCSprite * taSprite = CCSprite::createWithSpriteFrameName(texture_name::s_font_ta);
	taSprite->setPosition(ccp(qiSprite->getPositionX()+qiSprite->getContentSize().width,dengSprite->getPositionY()));
	taSprite->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCDelayTime::create(3*runTime),CCMoveTo::create(runTime,ccp(taSprite->getPositionX(),taSprite->getPositionY()+10)),
		CCMoveTo::create(runTime,ccp(taSprite->getPositionX(),taSprite->getPositionY())),CCDelayTime::create(3*runTime),NULL)));

	m_pdNode->addChild(taSprite);
	CCSprite * wanSprite = CCSprite::createWithSpriteFrameName(texture_name::s_font_wan);
	wanSprite->setPosition(ccp(taSprite->getPositionX()+taSprite->getContentSize().width,dengSprite->getPositionY()));
	wanSprite->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCDelayTime::create(4*runTime),CCMoveTo::create(runTime,ccp(wanSprite->getPositionX(),wanSprite->getPositionY()+10)),
		CCMoveTo::create(runTime,ccp(wanSprite->getPositionX(),wanSprite->getPositionY())),CCDelayTime::create(2*runTime),NULL)));

	m_pdNode->addChild(wanSprite);
	CCSprite * jiaSprite = CCSprite::createWithSpriteFrameName(texture_name::s_font_jia);
	jiaSprite->setPosition(ccp(wanSprite->getPositionX()+wanSprite->getContentSize().width,dengSprite->getPositionY()));
	jiaSprite->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCDelayTime::create(5*runTime),CCMoveTo::create(runTime,ccp(jiaSprite->getPositionX(),jiaSprite->getPositionY()+10)),
		CCMoveTo::create(runTime,ccp(jiaSprite->getPositionX(),jiaSprite->getPositionY())),CCDelayTime::create(runTime),NULL)));

	m_pdNode->addChild(jiaSprite);
	CCSprite * zhongSprite = CCSprite::createWithSpriteFrameName(texture_name::s_font_zhong);
	zhongSprite->setPosition(ccp(jiaSprite->getPositionX()+jiaSprite->getContentSize().width,dengSprite->getPositionY()));
	zhongSprite->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCDelayTime::create(6*runTime),CCMoveTo::create(runTime,ccp(zhongSprite->getPositionX(),zhongSprite->getPositionY()+10)),
		CCMoveTo::create(runTime,ccp(zhongSprite->getPositionX(),zhongSprite->getPositionY())),NULL)));
	m_pdNode->addChild(zhongSprite);
	this->addChild(m_pdNode);

	//排队粒子效果
	CCParticleSystemQuad * yanwu_particle = CCParticleSystemQuad::create("hlddz_particle/souren.plist");
	yanwu_particle->setPosition(ccp(422.0f,285.0f));
	//yanwu_particle->setDuration(-1);
	this->addChild(yanwu_particle,100,-77);
	SetUpdate();
	hnnnnnnn = false;
	return true;
}
void CardTableLayer::waitingMatching(bool isWaiting)
{
	if (!isWaiting)
	{
		this->removeChild(m_pdNode,true);
		this->getChildByTag(-77)->setVisible(false);
	}else{
		m_pdNode->setVisible(true);
		this->getChildByTag(-77)->setVisible(true);
	}
}

void CardTableLayer::setUserIsOnline(WORD wBankerUser,LONGLONG lBankerScore,LONGLONG lBankerWinScore,WORD wBankerTime)
{
	goldname->setString(CCString::createWithFormat("%I64d",lBankerScore)->getCString());
	ChengjiScore->setString(CCString::createWithFormat("%I64d",lBankerWinScore)->getCString());
	JiNumber->setString(CCString::createWithFormat("%I64d",wBankerTime)->getCString());
	goldname->setVisible(true);
	ChengjiScore->setVisible(true);
	JiNumber->setVisible(true);
	FinUsedSprite->setVisible(true);
}
//系统坐庄的时候
void CardTableLayer::setUserIcon( int userId,int gender,char* name,int gold,char* huafeidian )
{
	if (!hnnnnnnn)
	{
		if (gender == 1)
		{
			FinUsedSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("head_2.png"));
		}else
		{
			FinUsedSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("min_2.png"));
		}
		laberName->setString(name);
		goldname->setString(CCString::createWithFormat("%d",gold)->getCString());
		//	huafeidianname->setString(CCString::createWithFormat("%I64d",0)->getCString());
		//	JiNumber->setString(CCString::createWithFormat("%I64d",0)->getCString());
		hnnnnnnn = true;
	}
	laberName->setVisible(true);
	goldname->setVisible(true);
	ChengjiScore->setVisible(true);
	JiNumber->setVisible(true);
	FinUsedSprite->setVisible(true);
}

void CardTableLayer::onEnter()
{
	CCNode::onEnter();
	SoundControl::sharedSoundControl()->setMusicVol(-1);//-1表示上次系统音量
	SoundControl::sharedSoundControl()->setSoundEffVol(-1);//
	SoundControl::sharedSoundControl()->playBackGroundMusic(sound_name::s_bgMusic,true);
}

void CardTableLayer::onExit()
{
	CCNode::onExit();
	SoundControl::sharedSoundControl()->coloseBackGroundMusic();
}

CCString CardTableLayer::getDateNow()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	struct tm *tm;
	time_t tp = now.tv_sec;
	tm = localtime(&tp);
	int year = (int)tm->tm_year+1900;
	int mon = (int)tm->tm_mon+1;
	int day = (int)tm->tm_mday;
	int min = (int)tm->tm_min;
	int hour = (int)tm->tm_hour;
	int sec = (int)tm->tm_sec;
	CCString str;
	str.initWithFormat("%02d:%02d",hour,min);
	return str;
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm * tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	int year = (int)tm->tm_year+1900;
	int mon = (int)tm->tm_mon+1;
	int day = (int)tm->tm_mday;
	int min = (int)tm->tm_min;
	int hour = (int)tm->tm_hour;
	int sec = (int)tm->tm_sec;
	CCString str;
	str.initWithFormat("%02d:%02d",hour,min);
	return str;
#endif
}

void CardTableLayer::setNickName(const char * nikeName )
{
	//m_nikeName->setPosition(ccp(m_hhdAtlas->getPositionX()+m_hhdAtlas->getContentSize().width+10,0));
	m_nikeName->setString(nikeName);
}

void CardTableLayer::upHaiou(float ft)
{
//	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
//	CCSpriteFrame * frame=NULL;
//	CCAnimation* animation = CCAnimation::create();
//	CCString* buf=CCString::createWithFormat("haiou%d.png",rand()%2);
//	for(int i=0;i<3;i++)
//	{
//		CCSprite* sprite = CCSprite::create(buf->getCString());
//		frame = CCSpriteFrame::createWithTexture(sprite->getTexture(),CCRectMake(43*i,0,43,32));
//		//frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
//		animation->addSpriteFrame(frame);
//	}
//#define sUniformMapHeight		96
//#define sUniformMapWidth			854
//	CCPoint ptStar=ccp(-50,rand()%sUniformMapHeight+winSize.height * 0.9f);
//	CCPoint ptEnd=ccp(sUniformMapWidth+50,rand()%sUniformMapHeight+winSize.height * 0.9f);
//	float    time=rand()%10+10;
//	float   scal=(time/20)*0.6f;
//	animation->setDelayPerUnit(0.2f);
//
//	CCSprite * HAIOUsPT=CCSprite::createWithSpriteFrame(frame);
//
//	if (rand()%4==0)
//	{
//		ptStar=ccp(sUniformMapWidth+50,rand()%sUniformMapHeight+winSize.height * 0.9f);
//		ptEnd=ccp(-50,rand()%sUniformMapHeight+winSize.height * 0.9f);
//		HAIOUsPT->setRotationY(180.0f);
//	}
//	HAIOUsPT->setPosition(ptStar);
//	HAIOUsPT->setScale(0.6f);
//	HAIOUsPT->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
//	HAIOUsPT->runAction(CCSequence::create(CCSpawn::create(CCMoveTo::create(time,ptEnd),CCScaleTo::create(time,scal),NULL),
//		CCCallFuncO::create(this,callfuncO_selector(CardTableLayer::haiouCall),HAIOUsPT),NULL));
//
//	this->addChild(HAIOUsPT);
}

void CardTableLayer::haiouCall( CCObject* _obj )
{
	CCNode*node=(CCNode*)_obj;
	///if(node)node->removeFromParent();
}

void CardTableLayer::setBabnkUsedScore( LONGLONG Score )
{
	goldname->setString(CCString::createWithFormat("%I64d",Score)->getCString());
}

void CardTableLayer::setBankUsedChengjiORrJuNumber( LONGLONG Chengji,LONGLONG JuNumber )
{
	ChengjiScore->setString(CCString::createWithFormat("%I64d",Chengji)->getCString());
	JiNumber->setString(CCString::createWithFormat("%I64d",JuNumber)->getCString());
}

void CardTableLayer::setPlayAllScoreORchengji(LONGLONG Chengji )
{
	szText0+=Chengji;
	m_coinNumberAtlas->setString(CCString::createWithFormat("%d",szText0)->getCString());
	m_Chengji->setString(CCString::createWithFormat("%I64d",Chengji)->getCString());

}
void CardTableLayer::SetPlaceLandScore( CCObject *obj )
{
	long ManNumber = ((CCInteger *)obj)->getValue();
	szText0-=ManNumber;
	m_coinNumberAtlas->setString(CCString::createWithFormat("%d",szText0)->getCString());
	CCNotificationCenter::sharedNotificationCenter()->postNotification("UpdatePlacelinitUnClickTouch", CCInteger::create(szText0));

}

void CardTableLayer::initScrollView( BYTE m_cbPlayerCount ,BYTE m_cbBankerCount )
{
	//ScrollView一般用在游戏的关卡选择这种类似的场景
//	CCSize EL_W = SpriteGameRecord->getContentSize();
//	m_pScrollView = CCScrollView::create();// 位置不是居中的
//	m_pScrollView->setPosition(CCPointZero);
//	m_pScrollView->setContentOffset(CCPointZero);
//	//设置滚动区域的大小
//	m_pScrollView->setViewSize(CCSizeMake(EL_W.width, EL_W.height));
//	m_pScrollView->setContentSize(CCSizeMake(EL_W.width*2, EL_W.height));		//设置显示区域的大小
////	m_pScrollView->setContainer(SpriteGameRecord);                            //设置需要滚动的内容
//	m_pScrollView->setDirection(kCCScrollViewDirectionVertical);  //设置滚动的方向，有三种可以选择
//	m_pScrollView->setAnchorPoint(ccp(0.5, 0.5));
//	m_pScrollView->setPosition(ccp((size.width-EL_W.width)/2,(size.height-EL_W.height)/2));
//	this->addChild(m_pScrollView,4);
}

void CardTableLayer::SetUpdate()
{
	CCLabelAtlas *PlayhomeTTf7  = CCLabelAtlas::create("000000",texture_name::s_ChipMagerNumber,12,17,'0');
	PlayhomeTTf7->setAnchorPoint(CCPointZero);
	PlayhomeTTf7->setPosition(ccp(SpriteGameRecord->getPositionX(),SpriteGameRecord->getPositionY()));
	SpriteGameRecord->addChild(PlayhomeTTf7,2);

}



