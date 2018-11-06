#include "EmailCell.h"
#include "common/CocosUnits.h"
#include "configMgr/ConfigMgr.h"
#include "entity/EntityMgr.h"

EmailCell::EmailCell(void)
{
}


EmailCell::~EmailCell(void)
{
}

EmailCell* EmailCell::EmailCellWith(int type)
{
	EmailCell* buyCell = new EmailCell();
	if(buyCell && buyCell->initWithSpriteFrame(spriteFrame("dt_email9.png")))
	{
		buyCell->initEmailCellWith(type);
		buyCell->autorelease();
		return buyCell;
	}
	CC_SAFE_DELETE(buyCell);
	return NULL;
}

void EmailCell::setCellIdx(int idx)
{
	if(idx < 10)
	{
		messageTitle = CCLabelTTF::create(ConfigMgr::instance()->text("t406"),"",20);
		messageTitle->setPosition(ccp(this->getContentSize().width * 0.01,this->getContentSize().height * 0.81));
		messageTitle->setAnchorPoint(ccp(0.0,0.5));
		messageTitle->setColor(ccc3(0,0,0));
		addChild(messageTitle);
		CCString* strGonggao0 = CCString::createWithFormat("%s",ConfigMgr::instance()->text("t404"));
		messageContext->setString(strGonggao0->getCString());
		messageContext->setPosition(ccp(this->getContentSize().width * 0.01,this->getContentSize().height * 0.4));
		//messageContext->setZOrder(10);
	}
	else
	{
		messageTitle = CCLabelTTF::create(ConfigMgr::instance()->text("t405"),"",20);
		messageTitle->setPosition(ccp(this->getContentSize().width * 0.01,this->getContentSize().height * 0.81));
		messageTitle->setAnchorPoint(ccp(0.0,0.5));
		messageTitle->setColor(ccc3(0,0,0));
		addChild(messageTitle);
		std::string userAccount = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_ACCOUNT");
		std::string userPassword = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_PASSWORD");
		CCString* strGonggao0 = CCString::createWithFormat("%s%s%s%s",ConfigMgr::instance()->text(CCString::createWithFormat("t%d",401)->getCString()),userAccount.c_str(),ConfigMgr::instance()->text(CCString::createWithFormat("t%d",402)->getCString()),ConfigMgr::instance()->text("t403"));
		messageContext->setString(strGonggao0->getCString());
		messageContext->setPosition(ccp(this->getContentSize().width * 0.01,this->getContentSize().height * 0.4));
		//messageContext->setZOrder(10);
	}
}
bool EmailCell::initEmailCellWith(int type)
{
	//É¾³ý
	//CCSprite* backNormal= CCSprite::createWithSpriteFrame(spriteFrame("dt_email3.png"));
	//CCSprite* backSelect= CCSprite::createWithSpriteFrame(spriteFrame("dt_email3.png"));
	//CCMenuItemSprite* backItemSprite = CCMenuItemSprite::create(backNormal,backSelect,this,menu_selector(EmailCell::DeleteMessage));
	//backSelect->setScale(0.9);
	//backSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	//CCMenu* backMenu= CCMenu::create(backItemSprite,NULL);
	//backMenu->setPosition(ccp(this->getContentSize().width - backSelect->getContentSize().width * 0.5,this->getContentSize().height - backSelect->getContentSize().height * 0.5));
	//addChild(backMenu);
	if(type < 10)
	{
		CCString* strGonggao0 = CCString::createWithFormat("%s",ConfigMgr::instance()->text("t404"));
		messageContext = CCLabelTTF::create(strGonggao0->getCString(),"", 18,CCSizeMake(750.0f,0.0f),kCCTextAlignmentLeft);
		messageContext->setPosition(ccp(this->getContentSize().width * 0.05,this->getContentSize().height * 0.4));
		messageContext->setColor(ccc3(0,0,0));
		messageContext->setAnchorPoint(ccp(0.0,0.5));
		this->addChild(messageContext,10);
	}
	else
	{
		std::string userAccount = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_ACCOUNT");
		std::string userPassword = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_PASSWORD");
		CCString* strGonggao0 = CCString::createWithFormat("%s%s%s%s%s",ConfigMgr::instance()->text(CCString::createWithFormat("t%d",401)->getCString()),userAccount.c_str(),ConfigMgr::instance()->text(CCString::createWithFormat("t%d",402)->getCString()),userPassword.c_str(),ConfigMgr::instance()->text("403"));
		messageContext = CCLabelTTF::create(strGonggao0->getCString(),"", 18,CCSizeMake(750.0f,0.0f),kCCTextAlignmentLeft);
		messageContext->setPosition(ccp(this->getContentSize().width * 0.05,this->getContentSize().height * 0.4));
		messageContext->setColor(ccc3(0,0,0));
		messageContext->setAnchorPoint(ccp(0.0,0.5));
		this->addChild(messageContext,10);
	}
	return true;
}

void EmailCell::DeleteMessage(CCObject* obj)
{
	this->removeFromParentAndCleanup(true);
}
