//
//  RoomUserInfoText.cpp
//  Game
//
//  Created by 罗敏 on 13-6-26.
//
//

#include "GroupSprite.h"
#include "common/CocosUnits.h"
#include "configMgr/ConfigMgr.h"
GroupSprite::GroupSprite()
{
    
}
GroupSprite::~GroupSprite()
{
    
}
GroupSprite * GroupSprite::GroupSpriteWith(const char* str1,const char* str2,GorupSpriteType type,int level /* = 0 */)
{
    GroupSprite * text = new GroupSprite();
    if(text && text->initWithSpriteFrame(spriteFrame(str1)))
	{
		text->initGroupSprite(str1,str2,type,level);
		text->autorelease();
		return text;
	}
    CC_SAFE_DELETE(text);
    return NULL;
}

bool GroupSprite::initGroupSprite(const char* str1,const char* str2,GorupSpriteType type,int level)
{
	srand(unsigned(time(NULL)));
    if(type == GorupSpriteTypePhotoAndPhoto)
	{
		CCSprite* sprite = CCSprite::createWithSpriteFrame(spriteFrame(str2));
		sprite->setPosition(ccp(this->getContentSize().width * 0.5,this->getContentSize().height * 0.5));
		addChild(sprite);
	}
	else if(type == GorupSpriteTypePhotoAndWord)
	{
		labelWord = CCLabelTTF::create(str2,"",18);
		labelWord->setPosition(ccp(this->getContentSize().width * 0.5,this->getContentSize().height * 0.5));
		addChild(labelWord);
	}else if(type == GorupSpriteTypePhotoAndText0)
	{
		const char * str = CCString::createWithFormat("%s%s",str2,ConfigMgr::instance()->text("t453"))->getCString();
		labelWord = CCLabelTTF::create(str,"",18);
		labelWord->setPosition(ccp(this->getContentSize().width * 0.540,this->getContentSize().height * 0.145));
		addChild(labelWord);
		if(level == 5)
		{
			schedule(schedule_selector(GroupSprite::showCoinsLight),1.5f);
		}
	}else if(type == GorupSpriteTypePhotoAndText1)
	{
		int nIndex = level;
		int a = ConfigMgr::instance()->m_Config.nServerEnter[nIndex];
		int b = 0;
		char szLess[24] = {0};
		if (a >= 10000)
		{
			if (a%10000)
			{
				_snprintf(szLess, sizeof(szLess)-1, "%.1f%s", a/10000.f, ConfigMgr::instance()->text("t469"));
			}
			else
			{
				_snprintf(szLess, sizeof(szLess)-1, "%d%s", a/10000, ConfigMgr::instance()->text("t469"));
			}
		}
		else
		{
			_snprintf(szLess, sizeof(szLess)-1, "%d", a);
		}
		
		char szMax[24] = {0};
		if (b >= 10000)
		{
			if (b%10000)
			{
				_snprintf(szMax, sizeof(szMax)-1, "%.1f%s", b/10000.f, ConfigMgr::instance()->text("t469"));
			}
			else
			{
				_snprintf(szMax, sizeof(szMax)-1, "%d%s", b/10000, ConfigMgr::instance()->text("t469"));
			}
		}
		else
		{
			_snprintf(szMax, sizeof(szMax)-1, "%d", b);
		}

		char szText[64] = {0};
		if (0 != a && 0 != b)
		{
			_snprintf(szText, sizeof(szText) - 1, "%s-%s%s", szLess, szMax, ConfigMgr::instance()->text("t470"));	// a-b以下
		}
		else if (0 == b)
		{
			_snprintf(szText, sizeof(szText) - 1, "%s%s", szLess, ConfigMgr::instance()->text("t471"));	// a以上
		}
		else if (0 == a)
		{
			_snprintf(szText, sizeof(szText) - 1, "%s%s", szMax, ConfigMgr::instance()->text("t470"));	// b以下
		}
		else
		{
			_snprintf(szText, sizeof(szText) - 1, "0%s", ConfigMgr::instance()->text("t471"));	// 0以上
		}
		CCLabelTTF* label = CCLabelTTF::create(szText,"Verdana-Bold",20);
		label->setColor(ccc3(255,255,255));
		label->setPosition(ccp(this->getContentSize().width * 0.5,this->getContentSize().height * 0.3));
		//addChild(label);
		labelWord = CCLabelTTF::create(str2,"",18);
		labelWord->setAnchorPoint(ccp(1,0.5));
		labelWord->setPosition(ccp(this->getContentSize().width * 0.6,this->getContentSize().height * 0.13));
		//addChild(labelWord);
		if(level == 1)
		{
			CCSprite* spriteXigua = CCSprite::createWithSpriteFrame(spriteFrame("dt_xiguaba.png"));
			spriteXigua->setPosition(ccp(this->getContentSize().width * 0.28,this->getContentSize().height * 0.67));
			spriteXigua->setAnchorPoint(ccp(0.5,0.0));
			addChild(spriteXigua);

			CCRotateBy* action1 = CCRotateBy::create(0.8f,-10);
			CCRotateBy* action2 = CCRotateBy::create(0.8f,10);
			spriteXigua->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(action1,action2,NULL)));
		}
		if(level == 2)
		{
			CCSprite* spirteFlow = CCSprite::createWithSpriteFrame(spriteFrame("dt_flow.png"));
			spirteFlow->setPosition(ccp(this->getContentSize().width * 0.28,this->getContentSize().height * 0.68));
			addChild(spirteFlow);
			spirteFlow->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(CCScaleTo::create(0.4f,1.5),CCScaleTo::create(0.7f,0.9),NULL)));
		}
		if(level == 3)
		{
			CCSprite* spriteTree = CCSprite::createWithSpriteFrame(spriteFrame("dt_tree.png"));
			spriteTree->setPosition(ccp(17,this->getContentSize().height * 0.7));
			spriteTree->setAnchorPoint(ccp(0.0,0.5));
			addChild(spriteTree);
			spriteTree->setScale(0.5);

			CCRotateBy* action1 = CCRotateBy::create(0.9f,-10);
			CCRotateBy* action2 = CCRotateBy::create(0.9f,10);
			spriteTree->runAction(CCRepeatForever::create((cocos2d::CCActionInterval *)CCSequence::create(action1,action2,NULL)));
		}
	}
    return true;
}

void GroupSprite::showCoinsLight(float dt)
{
	int randNumber0 = 10+rand()%80;
	int randNumber2 = 30+rand()%30;
	CCSprite* spriteLight = CCSprite::createWithSpriteFrame(spriteFrame("dt_coinslight.png"));
	spriteLight->setPosition(ccp(this->getContentSize().width * randNumber0 *0.01,this->getContentSize().height * randNumber2*0.01));
	addChild(spriteLight);
	CCScaleTo* action1 = CCScaleTo::create(0.4f,1.3f);
	CCScaleTo* action2 = CCScaleTo::create(0.7f,0.4f);
	CCCallFuncN* actionDown = CCCallFuncN::create(this,callfuncN_selector(GroupSprite::actionDownAndRemove));
	spriteLight->runAction(CCSequence::create(action1,action2,actionDown,NULL));
}

void GroupSprite::actionDownAndRemove(CCNode* node)
{
	CCSprite* sprite = (CCSprite*)node;
	sprite->removeFromParentAndCleanup(true);
}

void GroupSprite::setTextSize(int size)
{
	labelWord->setFontSize(size);
}

void GroupSprite::setTextColor(int r,int g,int b){
	labelWord->setColor(ccc3(r,g,b));
}