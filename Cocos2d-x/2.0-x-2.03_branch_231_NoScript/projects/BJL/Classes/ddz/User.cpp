#include "User.h"
#include "MyTools.h"
User::User()
{

}

User::~User()
{

}

bool User::init()
{
	CCLayer::init();
	m_userIcon=CCSprite::createWithSpriteFrameName(texture_name::s_usericon);
	m_userIcon->setAnchorPoint(ccp(0.5f,0.5f));
	m_userIcon->setPosition(ccp(-300,-300));
	this->addChild(m_userIcon);

	m_userInfor=CCSprite::createWithSpriteFrameName(texture_name::s_userMessage);
	m_userInfor->setAnchorPoint(ccp(0.5f,0.5f));
	this->addChild(m_userInfor,1,100);
	m_userInfor->setVisible(false);
	m_pos =ccp(0,0);
	m_UserSptKey=0;
	m_userEye=NULL;

	setTouchEnabled(true);
	//setTouchMode(kCCTouchesOneByOne);

	m_isOut=true;
	m_isOnline=true;
	return true;
}

void User::setIsOnline(bool isOnline)
{
	m_isOnline=isOnline;
	if (isOnline)
	{
		m_userIcon->setColor(ccc3(255,255,255));
		if(m_userEye)m_userEye->setColor(ccc3(255,255,255));
	}
	else
	{
		m_userIcon->setColor(ccc3(100,100,100));
		if(m_userEye)m_userEye->setColor(ccc3(100,100,100));
	}
}

void User::setUserIcon( int gender )
{
	m_userInfor->setPosition(m_pos);
	m_gender=gender;
	m_userIcon->removeFromParentAndCleanup(true);
	m_userEye=NULL;

	if (m_gender==1)	//--ÄÐ
	{
		m_UserSptKey=1;
		m_userIcon = CCSprite::createWithSpriteFrameName(texture_name::s_usericon);
	}
	else
	{
		m_UserSptKey=2;
		m_userIcon = CCSprite::createWithSpriteFrameName(texture_name::s_womanIcon);
	}
	//if (m_pos.x>CCDirector::sharedDirector()->getWinSize().width*0.5)
	//	m_userIcon->setRotationY(180.0f);
	m_userIcon->setScale(0.8f);
	m_userIcon->setPosition(m_pos);
	addChild(m_userIcon);
	eyeCallUp(NULL);

	setIsOnline(m_isOnline);
	m_isOut=true;
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCPoint pt=m_pos;
	CCPoint posPt=m_pos;
	if (m_pos.x>size.width*0.5)
	{
		pt.x+=(m_userInfor->getContentSize().width+100);
		posPt.x-=60;
	}
	else
	{
		pt.x-=(m_userInfor->getContentSize().width+100);
		posPt.x+=60;
	}
	m_userInfor->stopAllActions();
	m_userInfor->setVisible(true);
	m_userInfor->setPosition(posPt);
	m_userInfor->runAction(CCSequence::create(CCDelayTime::create(5.0f),CCMoveTo::create(0.2f,pt),NULL));
}

void User::setLordIcon( bool blord )
{
	m_userInfor->setPosition(m_pos);
	m_userIcon->stopAllActions();
	m_userIcon->removeFromParentAndCleanup(true);
	m_userEye=NULL;

	m_userIcon=CCSprite::createWithSpriteFrameName(texture_name::s_usericon);
	CCSpriteFrame * frame=NULL;
	CCArray * animFrames = new CCArray(6);
	for(int i=0;i<5;i++)
	{
		CCString str;
		str.initWithFormat("yanwu%d.png",i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
		animFrames->addObject(frame);
	}
	if (blord)	//--µØÖ÷
	{	
		if (m_gender==1)
		{
			m_UserSptKey=3;
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture_name::s_dizhu_man);
		}
		else
		{
			m_UserSptKey=4;
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture_name::s_dizhu_woman);
		}
	}
	else
	{
		if (m_gender==1)
		{
			m_UserSptKey=5;
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture_name::s_farmer_man);
		}
		else
		{
			m_UserSptKey=6;
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture_name::s_farmer_woman);
		}
	}
	animFrames->addObject(frame);
	CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
	m_userIcon->setScale(0.8f);
	m_userIcon->runAction(CCSequence::create(CCAnimate::create(animation),CCCallFuncO::create(this,callfuncO_selector(User::eyeCallUp),NULL),NULL));
	m_userIcon->setPosition(m_pos);
	this->addChild(m_userIcon);
	//if (m_pos.x>CCDirector::sharedDirector()->getWinSize().width*0.5)
	//	m_userIcon->setRotationY(180.0f);

	setIsOnline(m_isOnline);
	m_isOut=false;
	userIconCallBack(NULL);
}

void User::setUserInfor( char* name,int gold,char* huafeidian )
{
		m_userInfor->removeAllChildrenWithCleanup(true);
		CCSize size=m_userInfor->getContentSize();

		CCLabelTTF* laberName=CCLabelTTF::create(name,"",16);
		//CCStrokeLabel* laberNameStrokeLabel=CCStrokeLabel::create(laberName,ccc3(0,0,0),ccc3(255,255,255),1.0f);
		laberName->setAnchorPoint(ccp(0.5f,0.5f));
		laberName->setColor(ccc3(173,118,0));
		laberName->setPosition(ccp(size.width*0.5,size.height*0.8));
		m_userInfor->addChild(laberName);

		CCLabelTTF* goldname=CCLabelTTF::create(CCString::createWithFormat("%d",gold)->getCString(),"",16);
		//CCStrokeLabel* goldStrokeLabel=CCStrokeLabel::create(goldname,ccc3(0,0,0),ccc3(255,255,255),1.0f);
		goldname->setAnchorPoint(ccp(0.5f,0.5f));
		goldname->setColor(ccc3(173,118,0));
		goldname->setPosition(ccp(size.width*0.5,size.height*0.5));
		m_userInfor->addChild(goldname);

		CCLabelTTF* huafeidianname=CCLabelTTF::create(huafeidian,"",16);
		//CCStrokeLabel* huafeidianStrokeLabel=CCStrokeLabel::create(huafeidianname,ccc3(0,0,0),ccc3(255,255,255),1.0f);
		huafeidianname->setAnchorPoint(ccp(0.5f,0.5f));
		huafeidianname->setColor(ccc3(173,118,0));
		huafeidianname->setPosition(ccp(size.width*0.5,size.height*0.2));
		m_userInfor->addChild(huafeidianname);
}

void User::userIconCallBack( CCObject* obj )
{
	m_isOut=!m_isOut;

	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCPoint pt=m_pos;
	CCPoint posPt=m_pos;
	//pt.y+=26;
	//posPt.y+=26;
	if (m_pos.x>size.width*0.5)
	{
		pt.x+=(m_userInfor->getContentSize().width+100);
		posPt.x-=60;
	}
	else
	{
		pt.x-=(m_userInfor->getContentSize().width+100);
		posPt.x+=60;
	}
	m_userInfor->stopAllActions();
	m_userInfor->setVisible(true);
	if (m_isOut)
	{
		//m_userInfor->setPosition(posPt);
		m_userInfor->runAction(CCMoveTo::create(0.2f,pt));
	}
	else
	{
		m_userInfor->setPosition(pt);
		m_userInfor->runAction(CCSequence::create(CCMoveTo::create(0.2f,posPt),CCDelayTime::create(3.0f),CCMoveTo::create(0.2f,pt),NULL));
	}
}

bool User::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pt=pTouch->getLocation();
	if (m_userIcon->boundingBox().containsPoint(pt))
	{
		userIconCallBack(NULL);
	}
	return false;
}

void User::eyeCallUp( CCObject* _obj )
{
	if (m_userIcon==NULL)return;
	if (m_userEye)
	{
		m_userEye->stopAllActions();
		m_userEye->removeFromParentAndCleanup(true);
	}

	CCSpriteFrame * frame=NULL;
	CCArray * animFrames = new CCArray(3);
	CCPoint pt;
	for(int i=0;i<3;i++)
	{
		CCString str;
		switch (m_UserSptKey)
		{
		case 1:
			str.initWithFormat("m_eye%d.png",i);
			pt=ccp(55,126);
			break;
		case 2:
			str.initWithFormat("wm_eye%d.png",i);
			pt=ccp(55+12,125);
			break;
		case 3:
			str.initWithFormat("dz_m_eye%d.png",i);
			pt=ccp(54,126+38+12+3);
			break;
		case 4:
			str.initWithFormat("dz_wm_eye%d.png",i);
			pt=ccp(54.5,126+21);
			break;
		case 5:
			str.initWithFormat("fm_m_eye%d.png",i);
			pt=ccp(55+1,126+38);
			break;
		case 6:
			str.initWithFormat("fm_wm_eye%d.png",i);
			pt=ccp(55+12,126+36);
			break;
		}
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.getCString());
		animFrames->addObject(frame);
	}
	CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
	m_userEye=CCSprite::createWithSpriteFrame(frame);
	m_userEye->setAnchorPoint(ccp(0,0));
	m_userEye->setPosition(pt);
	m_userEye->runAction(CCSequence::create(CCAnimate::create(animation),CCDelayTime::create(rand()%10),CCCallFuncO::create(this,callfuncO_selector(User::eyeCallUp),NULL),NULL));
	m_userIcon->addChild(m_userEye);
	setIsOnline(m_isOnline);
}
