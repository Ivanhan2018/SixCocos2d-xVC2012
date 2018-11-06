#include "ViewCardEffect.h"
#include "SceneData.h"
#include "MyTools.h"

bool ViewCardEffect::init()
{
	bool ret =false;
	do 
	{
		m_leftAlarm = false;
		m_rightAlarm = false;
		m_RobotNode=CCNode::create();
		this->addChild(m_RobotNode);
		ret =true;
	} while (0);
	return ret;
}

void ViewCardEffect::runEffect( EffectType _type, int userId)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	_ccColor3B color = ccc3(255,255,255);
	switch (_type)
	{
	case Effect_gameStart://普通开始
		effectOpenStart(false,userId);
		break;
	case Effect_OpenStart://明牌开始
		effectOpenStart(true,userId);
		break;
	case Effect_openCard://发牌时候明牌
		effectOpenCard(userId);
		break;
	case 	Effect_LandLord://叫地主
		effectLandLord(true,userId);
		break;
	case Effect_NoLandLord://不叫地主
		effectLandLord(false,userId);
		break;
	case Effect_RobLord://抢地主
		effectRodLord(true,userId);
		break;
	case Effect_NoRobLord://不抢
		effectRodLord(false,userId);
		break;
	case Effect_PassCard://过牌
		effectPassCard(userId);
		break;
	case Effect_jiaBei://加倍
		effectJiaBei(userId,true);
		break;
	case Effect_alarm://警报
		effectAlarm(userId);
		break;
	case Effect_outcardErr://出牌错误
		{
			addEffect("outcarderr",ccp(size.width*0.5,size.height*0.2),color,20,true);
		}
		break;
	case Effect_noBigCard:
		{
			addEffect("nobigcard",ccp(size.width*0.5,size.height*0.2),color,20,true);
		}
		break;
	case Effect_task:
		{
			addEffect("tasktips",ccp(size.width*0.5,size.height*0.2),color,20,true);
		}
		break;
	case Effect_LlinkOFF:
		{
			addEffect("linkofftips",ccp(size.width*0.5,size.height*0.5),color,20,true);
		}
		break;
	}
}

void ViewCardEffect::effectOpenStart( bool isOpen,int userId )
{
	return;
	CCSize size =CCDirector::sharedDirector()->getWinSize();
	CCPoint point = getEffectPos(userId);
	_ccColor3B color = ccc3(161,84,32);
	if (isOpen)
	{
		addPictureEffect(texture_name::s_font_visiblecard,point);
		SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_mingpai,userId);
	}else
	{
//		addEffect("ptks",point,color,12);
	}
}

void ViewCardEffect::effectOpenCard( int userId )
{
	return;
	CCSize size =CCDirector::sharedDirector()->getWinSize();
	CCPoint point = getEffectPos(userId);
	SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_mingpai,userId);
	_ccColor3B color = ccc3(161,84,32);
	addPictureEffect(texture_name::s_font_visiblecard,point);
}

void ViewCardEffect::effectLandLord( bool isLand, int userId)
{
 	CCSize size =CCDirector::sharedDirector()->getWinSize();
	CCPoint point = getEffectPos(userId);
	if(isLand)
	{
		addPictureEffect(texture_name::s_font_jiaodizhu,point);
		SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_jiaodizhu,userId);
	}else{
		addPictureEffect(texture_name::s_font_bujiao,point);
		SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_bujiao,userId);
	}
}

void ViewCardEffect::effectRodLord( bool isRob ,int userId)
{
	CCSize size =CCDirector::sharedDirector()->getWinSize();
	CCPoint point = getEffectPos(userId);
	if(isRob)
	{
		addPictureEffect(texture_name::s_font_qiangdizhu,point);
		SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_qiangdizhu,userId);
	}else{
		addPictureEffect(texture_name::s_font_buqiang,point);
		SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_buqiang,userId);
	}
}

void ViewCardEffect::effectPassCard(int userId)
{
	CCSize size =CCDirector::sharedDirector()->getWinSize();
	_ccColor3B color = ccc3(161,84,32);
	CCPoint point = getEffectPos(userId);
	SoundEffect::sharedSoundEffect()->playPassEffect(userId);
	addPictureEffect(texture_name::s_font_pass,point);
}

void ViewCardEffect::addEffect(const char* key,CCPoint point,_ccColor3B color,int fontSize,bool showDi)
{
	CCDictionary * strings = CCDictionary::createWithContentsOfFile("xml/strings.xml");
	const char * str = ((CCString*)strings->objectForKey(key))->m_sString.c_str();
	CCLabelTTF * pLableTTF = CCLabelTTF::create(str,"",fontSize);
	//CCStrokeLabel * strokLable = CCStrokeLabel::create(pLableTTF,ccc3(0,0,0),ccc3(255,255,255),1.0f);
	pLableTTF->setAnchorPoint(ccp(0.5f,0.5f));
	pLableTTF->setColor(color);
	pLableTTF->setPosition(point);
	//pLableTTF->setAnchorPoint(ccp(0.5f,0.5f));
	CCSprite * notifySprite = CCSprite::createWithSpriteFrameName(texture_name::s_notify);
	notifySprite->setPosition(point);
	CCNode * effectNode = CCNode::create();
	if (showDi)
	{
		effectNode->addChild(notifySprite);
	}
	effectNode->addChild(pLableTTF);
	this->addChild(effectNode);
	effectNode->setPosition(CCPointZero);
	effectNode->runAction(CCSequence::create(CCMoveTo::create(0.8f,ccp(0,30)),CCDelayTime::create(1.0f),
		CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
}

void ViewCardEffect::addUserInputMsgEffect(const char* key,CCPoint point,_ccColor3B color,int fontSize,bool showDi)
{
	CCLabelTTF * pLableTTF = CCLabelTTF::create(key,"",fontSize);
	//CCStrokeLabel * strokLable = CCStrokeLabel::create(pLableTTF,ccc3(0,0,0),ccc3(255,255,255),1.0f);
	pLableTTF->setAnchorPoint(ccp(0.5f,0.5f));
	pLableTTF->setColor(color);
	pLableTTF->setPosition(point);
	CCSprite * notifySprite = CCSprite::createWithSpriteFrameName(texture_name::s_notify);
	notifySprite->setPosition(point);
	CCNode * effectNode = CCNode::create();
	if (showDi)
	{
		effectNode->addChild(notifySprite);
	}
	effectNode->addChild(pLableTTF);
	this->addChild(effectNode);
	effectNode->setPosition(CCPointZero);
	effectNode->runAction(CCSequence::create(CCMoveTo::create(0.8f,ccp(0,30)),CCDelayTime::create(1.0f),
		CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
}

void ViewCardEffect::addPictureEffect(const char* key,CCPoint point,bool isAddPartiCar)
{
	CCSprite * sprite = CCSprite::createWithSpriteFrameName(key);
	sprite->setAnchorPoint(ccp(0.5,0.5));
	sprite->setPosition(point);
	this->addChild(sprite);
	//	if (isAddPartiCar)
// 	{
// 		CCParticleSystemQuad* partcall=CCParticleSystemQuad::create("hlddz_particle/cardtype/duizi.plist");
// 		partcall->setPosition(CCPointZero);
// 		sprite->addChild(partcall);
// 	}

	sprite->runAction(CCSequence::create(CCMoveTo::create(0.2f,ccp(sprite->getPositionX(),
		sprite->getPositionY()+30)),CCDelayTime::create(1.0f),
		CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
}

void ViewCardEffect::removerSelf(CCNode* node)
{
	if (node)
	{
		node->removeFromParentAndCleanup(true);
	}
}

void ViewCardEffect::effectJiaBei(int userId,bool isJiaBei)
{
	CCSize size =CCDirector::sharedDirector()->getWinSize();
	CCPoint point = getEffectPos(userId);
	_ccColor3B color = ccc3(161,84,32);
	if (isJiaBei)
	{
		addPictureEffect(texture_name::s_font_jiabei,point);
		SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_jiabei,userId);
		return;
	}
}

void ViewCardEffect::runCardEffect(int cardType,int userId,int cardNum,int userOutCardState)
{
	CCSize size =CCDirector::sharedDirector()->getWinSize();
	CCPoint point = getEffectPos(userId);
	switch(cardType)
	{
	case CT_ERROR://错误牌型
		break;
	case CT_SINGLE://单牌
		if (userOutCardState!=3)//表示普通出牌
		{
			SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_yizhang,userId);
		}else{
			SoundEffect::sharedSoundEffect()->playDaPaiEffect(userId);
		}
		break;
	case CT_DOUBLE://对牌
		if (userOutCardState!=3)
		{
			SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_yidui,userId);
		}else{
			SoundEffect::sharedSoundEffect()->playDaPaiEffect(userId);
		}
		break;
	case CT_THREE://三条
		if (userOutCardState!=3)
		{
			SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_sanzhang,userId);
		}else{
			SoundEffect::sharedSoundEffect()->playDaPaiEffect(userId);
		}
		break;
	case CT_SINGLE_LINE://顺子
		{
			addPictureEffect(texture_name::s_ctSingleLine,point);
			if (userOutCardState!=3)
			{
				SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_shunzi,userId);
			}else{
				SoundEffect::sharedSoundEffect()->playDaPaiEffect(userId);
			}
			SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_ct_shunzi);
		}
		break;
	case CT_DOUBLE_LINE://连对
		{
			addPictureEffect(texture_name::s_ctDoubleLine,point);
			if (userOutCardState!=3)
			{
				SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_liandui,userId);
			}else{
				SoundEffect::sharedSoundEffect()->playDaPaiEffect(userId);
			}
			SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_ct_liandui);
		}
		break;
	case CT_THREE_LINE://三连
		{
			if (userOutCardState!=3)
			{
				SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_sanshun,userId);
			}else{
				SoundEffect::sharedSoundEffect()->playDaPaiEffect(userId);
			}
			SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_ct_sanshun);
		}
		break;
	case CT_THREE_LINE_TAKE_ONE://三带一
		{
			if (cardNum>=8)//飞机
			{
				SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_feiji,userId);
				SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_ct_feiji);
				CCNode * animNode = CCNode::create();
				CCSprite * planeSprite = CCSprite::createWithSpriteFrameName(texture_name::s_plane);//飞机
				planeSprite->setAnchorPoint(ccp(0.5f,0));
				animNode->addChild(planeSprite,1,0);
				CCSprite * planeyySpriteLeft = CCSprite::createWithSpriteFrameName(texture_name::s_planeyy);//飞机左边阴影
				planeyySpriteLeft->setAnchorPoint(ccp(1.0f,1.0f));
				CCSprite * planeyySpriteRight = CCSprite::createWithSpriteFrameName(texture_name::s_planeyy);//飞机右边阴影
				planeyySpriteRight->setFlipX(true);
				planeyySpriteRight->setAnchorPoint(ccp(0,1.0f));
				animNode->addChild(planeyySpriteRight);
				animNode->addChild(planeyySpriteLeft);
				//头部螺旋桨
				CCArray * animFrames = new CCArray(2);
				for (int i=0;i<2;i++)
				{
					CCString str;
					str.initWithFormat("lxj%d.png",i);
					CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
					animFrames->addObject(frame);
				}
				CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
				CCSprite * lxjHead = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames->objectAtIndex(0));
				lxjHead->setAnchorPoint(ccp(0,0));
				lxjHead->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
				lxjHead->setPosition(ccp(-planeSprite->getContentSize().width/2-15,15.0f));
				animNode->addChild(lxjHead,2,1);
				animNode->setPosition(ccp(size.width/2,size.height/2));
				//尾部螺旋桨
				CCArray * animFrames2 = new CCArray(2);
				for (int i=0;i<2;i++)
				{
					CCString str;
					str.initWithFormat("lxj%d.png",i);
					CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
					animFrames2->addObject(frame);
				}
				CCAnimation * animation2 = CCAnimation::createWithSpriteFrames(animFrames2,0.2f);
				CCSprite * lxjEnd = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames2->objectAtIndex(0));
				lxjEnd->setAnchorPoint(ccp(1.0f,0));
				lxjEnd->runAction(CCRepeatForever::create(CCAnimate::create(animation2)));
				lxjEnd->setPosition(ccp(planeSprite->getContentSize().width/2+15,15.0f));
				animNode->addChild(lxjEnd,0,3);
				animNode->setPosition(ccp(size.width+planeSprite->getContentSize().width/2,size.height/2));
				animNode->runAction(CCSequence::create(CCMoveTo::create(1.5f,ccp(-planeSprite->getContentSize().width/2-100,size.height/2)),
					CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
				this->addChild(animNode);

			}else
			{
				if (userOutCardState!=3)
				{
					SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_sandaiyi,userId);
				}else{
					SoundEffect::sharedSoundEffect()->playDaPaiEffect(userId);
				}
			}
		}
		break;
	case CT_THREE_LINE_TAKE_TWO://三带一对
		{
			if (cardNum>=8)//飞机
			{
				SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_feiji,userId);
				SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_ct_feiji);
				CCNode * animNode = CCNode::create();
				CCSprite * planeSprite = CCSprite::createWithSpriteFrameName(texture_name::s_plane);//飞机
				planeSprite->setAnchorPoint(ccp(0.5f,0));
				animNode->addChild(planeSprite,1,0);
				CCSprite * planeyySpriteLeft = CCSprite::createWithSpriteFrameName(texture_name::s_planeyy);//飞机左边阴影
				planeyySpriteLeft->setAnchorPoint(ccp(1.0f,1.0f));
				CCSprite * planeyySpriteRight = CCSprite::createWithSpriteFrameName(texture_name::s_planeyy);//飞机右边阴影
				planeyySpriteRight->setFlipX(true);
				planeyySpriteRight->setAnchorPoint(ccp(0,1.0f));
				animNode->addChild(planeyySpriteRight);
				animNode->addChild(planeyySpriteLeft);
				//头部螺旋桨
				CCArray * animFrames = new CCArray(2);
				for (int i=0;i<2;i++)
				{
					CCString str;
					str.initWithFormat("lxj%d.png",i);
					CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
					animFrames->addObject(frame);
				}
				CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
				CCSprite * lxjHead = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames->objectAtIndex(0));
				lxjHead->setAnchorPoint(ccp(0,0));
				lxjHead->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
				lxjHead->setPosition(ccp(-planeSprite->getContentSize().width/2-15,15.0f));
				animNode->addChild(lxjHead,2,1);
				animNode->setPosition(ccp(size.width/2,size.height/2));
				//尾部螺旋桨
				CCArray * animFrames2 = new CCArray(2);
				for (int i=0;i<2;i++)
				{
					CCString str;
					str.initWithFormat("lxj%d.png",i);
					CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
					animFrames2->addObject(frame);
				}
				CCAnimation * animation2 = CCAnimation::createWithSpriteFrames(animFrames2,0.2f);
				CCSprite * lxjEnd = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames2->objectAtIndex(0));
				lxjEnd->setAnchorPoint(ccp(1.0f,0));
				lxjEnd->runAction(CCRepeatForever::create(CCAnimate::create(animation2)));
				lxjEnd->setPosition(ccp(planeSprite->getContentSize().width/2+15,15.0f));
				animNode->addChild(lxjEnd,0,3);
				animNode->setPosition(ccp(size.width+planeSprite->getContentSize().width/2,size.height/2));
				animNode->runAction(CCSequence::create(CCMoveTo::create(1.5f,ccp(-planeSprite->getContentSize().width/2-100,size.height/2)),
					CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
				this->addChild(animNode);
				
			}else
			{
				if (userOutCardState!=3)
				{
					SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_sandaier,userId);
				}else{
					SoundEffect::sharedSoundEffect()->playDaPaiEffect(userId);
				}
			}
		}
		break;
	case CT_FOUR_LINE_TAKE_ONE://四带二
		{
			if (userOutCardState!=3)
			{
				SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_sidaier,userId);
			}else{
				SoundEffect::sharedSoundEffect()->playDaPaiEffect(userId);
			}
		}
		break;
	case CT_FOUR_LINE_TAKE_TWO://四代两对
		{

		}
		break;
	case CT_BOMB_CARD://炸弹
		{
			CCNode * animNode = CCNode::create();
			CCSprite * bombSprite = CCSprite::createWithSpriteFrameName(texture_name::s_bomb);
			bombSprite->setAnchorPoint(ccp(0.5f,0));
			animNode->addChild(bombSprite,0,0);
			CCArray * animFrames = new CCArray(8);
			for (int i=0;i<8;i++)
			{
				CCString str;
				str.initWithFormat("bomb%d.png",i);
				CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
				animFrames->addObject(frame);
			}
			CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
			CCSprite * bombAnimation = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames->objectAtIndex(0));
			bombAnimation->setScale(2.6f);
			bombAnimation->setAnchorPoint(ccp(0.5f,0));
			bombAnimation->setPositionY(10.0f);
			animNode->addChild(bombAnimation,1,1);
			bombAnimation->runAction(CCAnimate::create(animation));
			bombSprite->runAction(CCFadeOut::create(1.6f));
			animNode->setPosition(ccp(size.width/2,150.0f));
			animNode->runAction(CCSequence::create(CCDelayTime::create(1.6f),
				CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
			this->addChild(animNode);
			SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_zhadan,userId);
			SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_ct_zhadan);
			CCDirector::sharedDirector()->getRunningScene()->runAction(CCShake::create(0.4f,20));
		}
		break;
	case CT_MISSILE_CARD://火箭
		{
			CCNode*		_node=CCNode::create();
			this->addChild(_node);
			CCSprite *_sptTou=CCSprite::createWithSpriteFrameName(texture_name::s_huojian);
			_sptTou->setAnchorPoint(ccp(0.5f,0.0));
			_sptTou->setPosition(ccp(size.width*0.5f,size.height*0.4f));
			_sptTou->runAction(CCSequence::create(CCDelayTime::create(0.1f),CCMoveTo::create(0.6f,ccp(size.width*0.5,size.height+300)),NULL));
			CCSprite* _sptWei=CCSprite::createWithSpriteFrameName(texture_name::s_huoyan);
			_sptWei->setAnchorPoint(ccp(0.5f,1.0f));
			_sptWei->setPosition(ccp(_sptTou->getContentSize().width*0.5,0));
			_sptWei->runAction(CCFadeIn::create(0.4f));
			_sptTou->addChild(_sptWei);
			CCArray * animFrames = new CCArray(4);
			for (int i=0;i<4;i++)
			{
				CCString str;
				str.initWithFormat("yun%d.png",i);
				CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
				animFrames->addObject(frame);
			}
			CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
			CCSprite * _yunAnimation = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames->objectAtIndex(0));
			_yunAnimation->setAnchorPoint(ccp(0.5f,0.5f));
			_yunAnimation->setPosition(ccp(size.width*0.5,size.height*0.4));
			_yunAnimation->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCAnimate::create(animation),NULL));

			_node->addChild(_sptTou);
			_node->addChild(_yunAnimation);
			_node->runAction(CCSequence::create(CCDelayTime::create(1.0f),CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
			CCDirector::sharedDirector()->getRunningScene()->runAction(CCShake::create(0.4f,20));
			SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_huojian,userId);
			SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_ct_huojian);
		}
		break;
	}
	
}

void ViewCardEffect::runRobot( bool isOnRobot )
{
	m_RobotNode->removeAllChildrenWithCleanup(true);
	if (isOnRobot)
	{
		CCSize size= CCDirector::sharedDirector()->getWinSize();
		CCSpriteFrame * pFrameNormal = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture_name::s_cancleRobot);
		CCSpriteFrame * pFrameSelected = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture_name::s_cancleRobot);
		CCSpriteFrame * pFrameDisable = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture_name::s_cancleRobot);
		CCSprite * normalSprite = CCSprite::createWithSpriteFrame(pFrameNormal);
		CCSprite * selectedSprite = CCSprite::createWithSpriteFrame(pFrameSelected);
		selectedSprite->setColor(ccc3(100,100,100));
		CCSprite * disableSprite = CCSprite::createWithSpriteFrame(pFrameDisable);
		CCMenuItemSprite * menuItemSprite = CCMenuItemSprite::create(normalSprite,selectedSprite,disableSprite,this,menu_selector(ViewCardEffect::RobotCallBack));
		CCMenu* menu=CCMenu::create(menuItemSprite,NULL);
		menu->setPosition(ccp(size.width*0.5,size.height*0.2));
		m_RobotNode->addChild(menu,100,100);

		//机器人
		CCSprite* spt=CCSprite::createWithSpriteFrameName(texture_name::s_robot_pic);
		spt->setPosition(ccp(menu->getPositionX(),menu->getPositionY()+70));
		spt->setAnchorPoint(ccp(0.5,0.5));
		m_RobotNode->addChild(spt,2,2);

		CCSprite* spt_eyeL=CCSprite::createWithSpriteFrameName(texture_name::s_eye);
		spt_eyeL->setPosition(ccp(spt->getPositionX()+8,spt->getPositionY()+7));
		spt_eyeL->setAnchorPoint(ccp(0.5,0.5));
		m_RobotNode->addChild(spt_eyeL,3,3);
		spt_eyeL->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCFadeIn::create(0.2f),CCDelayTime::create(0.5f),CCFadeOut::create(0.2f),NULL)));
		CCSprite* spt_eyeR=CCSprite::createWithSpriteFrameName(texture_name::s_eye);
		spt_eyeR->setPosition(ccp(spt->getPositionX()-11,spt->getPositionY()+7));
		spt_eyeR->setAnchorPoint(ccp(0.5,0.5));
		spt_eyeR->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCFadeIn::create(0.2f),CCDelayTime::create(0.5f),CCFadeOut::create(0.2f),NULL)));
		m_RobotNode->addChild(spt_eyeR,4,4);

		CCSprite* spt_banshou=CCSprite::createWithSpriteFrameName(texture_name::s_banshou);
		CCPoint banshou_pt=ccp(spt->getPositionX()+spt->getContentSize().width*0.4,spt->getPositionY()-30);
		spt_banshou->setPosition(banshou_pt);
		spt_banshou->setAnchorPoint(ccp(0.5,0.5));
		spt_banshou->runAction(CCRepeatForever::create(CCJumpBy::create(1.0f,CCPointZero,10,1)));
		m_RobotNode->addChild(spt_banshou,5,5);
	}
}

void ViewCardEffect::RobotCallBack(CCObject* obj)
{
	m_RobotNode->removeAllChildrenWithCleanup(true);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_MENUCLICKED,CCInteger::create(menu_OutAgency));
}

void ViewCardEffect::runVoiceAndFace( int _type,int _key,int _userID )
{	
	bool voiceIsOpen = CCUserDefault::sharedUserDefault()->getBoolForKey("voiceIsOpen",true);
	bool faceIsOpen = CCUserDefault::sharedUserDefault()->getBoolForKey("faceIsOpen",true);
	CCPoint point	=getEffectPos(_userID);
	if (_type==1 && faceIsOpen)		//--表情
	{
		addPictureEffect(CCString::createWithFormat("face_%d.png",_key)->getCString(),point);
	}
	else if (_type ==2 && voiceIsOpen)	//--语音
	{
		_ccColor3B color = ccc3(255,255,255);
		addEffect(CCString::createWithFormat("wav%d",_key)->getCString(),point,color,20,true);
		SoundEffect::sharedSoundEffect()->playEffect(CCString::createWithFormat("wav%d.mp3",_key)->getCString(),_userID);
	}
}

void ViewCardEffect::runVoice(string voiceString,int _userID )
{
	bool voiceIsOpen = CCUserDefault::sharedUserDefault()->getBoolForKey("voiceIsOpen",true);
	CCPoint point	=getEffectPos(_userID);
	if(voiceIsOpen)
	{
		_ccColor3B color = ccc3(255,255,255);
		addUserInputMsgEffect(voiceString.c_str(),point,color,20,true);
		//SoundEffect::sharedSoundEffect()->playEffect(CCString::createWithFormat("wav%d.mp3",_key)->getCString(),_userID);
	}
}

cocos2d::CCPoint ViewCardEffect::getEffectPos( int _userID )
{
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCPoint point;
	switch(_userID)
	{
	case 0://上家
		point = ccp(size.width*0.3,size.height*0.5);
		break;
	case 1://自己
		point = ccp(size.width*0.5,size.height*0.3);
		break;
	case 2://下家
		point = ccp(size.width*0.7,size.height*0.5);
		break;
	}
	return point;
}

void ViewCardEffect::effectAlarm(int userId)
{
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCPoint point;
	switch(userId)
	{
	case 0://上家
		{
			if (m_leftAlarm)
			{
				return;
			}
			point = ccp(185.0f,290.0f);
			CCArray * animFrames = new CCArray(6);
			for(int i=0;i<6;i++)
			{
				CCString str;
				str.initWithFormat("jingbao%d.png",i);
				CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
				animFrames->addObject(frame);
			}
			CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
			CCSprite * jingBaoSprite = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames->objectAtIndex(0));
			jingBaoSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
			jingBaoSprite->setPosition(point);
			jingBaoSprite->setScale(0.4f);
			this->addChild(jingBaoSprite,0,100);
			SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_warning);
			m_leftAlarm = true;
		}
		break;
	case 1://自己
		point = ccp(size.width*0.5,size.height*0.3);
		break;
	case 2://下家
		{
			if (m_rightAlarm)
			{
				return;
			}
			point = ccp(size.width-185,290);
			CCArray * animFrames = new CCArray(6);
			for(int i=0;i<6;i++)
			{
				CCString str;
				str.initWithFormat("jingbao%d.png",i);
				CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
				animFrames->addObject(frame);
			}
			CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
			CCSprite * jingBaoSprite = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames->objectAtIndex(0));
			jingBaoSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
			jingBaoSprite->setPosition(point);
			jingBaoSprite->setScale(0.4f);
			this->addChild(jingBaoSprite,0,101);
			SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_warning);
			m_rightAlarm = true;
		}
		break;
	}
}

void ViewCardEffect::runSettlementEffect(CCInteger * obj,int tableConsume,CardTableLayer * layer)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	g_cardTableLayer = layer;
	//this->removeAllChildren();
	//金币动画
	removeAlarm();//移除警报
 	CCSettmentUserMessage * user = (CCSettmentUserMessage*)obj;
 	CCPoint point = getEffectPos(user->m_userId);
	CCString str;
	if (user->m_updScore>0)
	{
		str.initWithFormat(":%d",user->m_updScore-tableConsume);
	}
	else
	{
		str.initWithFormat(";%d",user->m_updScore-tableConsume);
	}
	CCLabelAtlas * labelAtlas = CCLabelAtlas::create(str.getCString(),texture_name::s_coinNumber1,16,22,'0');
	labelAtlas->setAnchorPoint(ccp(0.5f,0.5f));
	labelAtlas->setScale(1.2f);
	labelAtlas->setPosition(point);
// 	switch(user->m_userId)
// 	{
// 	case 0:
// 		{
// 			labelAtlas->runAction(CCSequence::create(CCMoveTo::create(0.4f,ccp(point.x,point.y+40.0f)),
// 				CCDelayTime::create(6.0f),
// 				CCSpawn::create(CCMoveTo::create(1.0f,ccp(100.0f,400.0f)),CCScaleTo::create(1.0f,0.3f,0.3f),NULL),
// 				CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
// 		}
// 		break;
// 	case 1:
// 		{
// 			labelAtlas->runAction(CCSequence::create(CCMoveTo::create(0.4f,ccp(point.x,point.y+40.0f)),
// 				CCDelayTime::create(6.0f),
// 				CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
// 		}
// 		break;
// 	case 2:
// 		{
// 			labelAtlas->runAction(CCSequence::create(CCMoveTo::create(0.4f,ccp(point.x,point.y+40.0f)),
// 				CCDelayTime::create(6.0f),
// 				CCSpawn::create(CCMoveTo::create(1.0f,ccp(754.0f,400.0f)),CCScaleTo::create(1.0f,0.3f,0.3f),NULL),
// 				CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
// 		}
// 		break;
// 	}
	labelAtlas->runAction(CCSequence::create(CCMoveTo::create(0.4f,ccp(point.x,point.y+40.0f)),
		CCDelayTime::create(6.0f),
		CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),NULL));
	this->addChild(labelAtlas);
	//左下角金币变化动画
	if (user->m_userId==1)
	{
		g_udpCoinNumber = user->m_updScore-tableConsume;
		CCLabelAtlas * udpAtlas = CCLabelAtlas::create(str.getCString(),texture_name::s_coinNumber1,16,22,'0');
		udpAtlas->setAnchorPoint(ccp(0.5f,0.5f));
		udpAtlas->setPosition(ccp(size.width/2,90.0f));
		udpAtlas->runAction(CCSequence::create(CCMoveTo::create(1.0f,ccp(size.width/2,30.0f)),
			CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),
			CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::changeCoinNumber)),NULL));
		this->addChild(udpAtlas);
	}

	//输赢动画
	if(user->m_userId==1)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		if (user->m_updScore>0)
		{
			CCSprite * sprite = CCSprite::createWithSpriteFrameName(texture_name::s_winner);
			sprite->setPosition(ccp(size.width/2,size.height/2));
			sprite->runAction(CCSequence::create(CCFadeIn::create(0.2f),CCJumpBy::create(0.4f,ccp(0,-10),20.0f,2),NULL));
			this->addChild(sprite);
			SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_winner);
		}
		if (user->m_updScore<0)
		{
			CCSprite * sprite = CCSprite::createWithSpriteFrameName(texture_name::s_loser);
			sprite->setPosition(ccp(size.width/2,size.height/2));
			sprite->runAction(CCSequence::create(CCFadeIn::create(0.2f),CCJumpBy::create(0.4f,ccp(0,-10),20.0f,2),NULL));
			this->addChild(sprite);
			SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_loser);
		}
	}
}

void ViewCardEffect::removeAlarm()
{
	if(this->getChildByTag(100))
	{
		this->getChildByTag(100)->removeFromParentAndCleanup(true);
	}
	if(this->getChildByTag(101))
	{
		this->getChildByTag(101)->removeFromParentAndCleanup(true);
	}
}

void ViewCardEffect::changeCoinNumber(CCNode * node)
{
}

void ViewCardEffect::runHfdEffect(CCInteger * obj)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CChuafeidian * hfd = (CChuafeidian*)obj;
	g_hfdCoinNumber = hfd->m_huafeidian;
	CCString str;
	str.initWithFormat(":%d",g_hfdCoinNumber);

	CCLabelAtlas * udpAtlas = CCLabelAtlas::create(str.getCString(),texture_name::s_coinNumber1,16,22,'0');
	udpAtlas->setAnchorPoint(ccp(0.5f,0.5f));
	udpAtlas->setPosition(ccp(size.width-udpAtlas->getContentSize().width/2-15,90.0f));
	udpAtlas->runAction(CCSequence::create(CCMoveTo::create(1.0f,ccp(size.width-udpAtlas->getContentSize().width/2-15,30.0f)),
		CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::removerSelf)),
		CCCallFuncN::create(this,callfuncN_selector(ViewCardEffect::changeHfdNumber)),NULL));
	this->addChild(udpAtlas);
}

void ViewCardEffect::changeHfdNumber(CCNode * node)
{
}

// CCAnimation * ViewCardEffect::getAnimation(const char * key,int frameNum)
// {
//  	CCArray * animFrames = new CCArray(frameNum);
//  	for (int i=0;i<frameNum;i++)
//  	{
//  		CCString str;
//  		str.initWithFormat("%s%d.png",key,i);
//  		CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
//  		animFrames->addObject(frame);
//  	}
//  	CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
// 	return animation;
// }


