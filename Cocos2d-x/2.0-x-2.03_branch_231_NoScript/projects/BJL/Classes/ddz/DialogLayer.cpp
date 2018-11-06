#include "DialogLayer.h"
#include "SceneData.h"
#include "SceneControl.h"

DialogLayer::DialogLayer(dialog_type type)
{
	m_type = type;
}

DialogLayer::~DialogLayer()
{
}

DialogLayer * DialogLayer::create(dialog_type type)
{
	DialogLayer * pRet = new DialogLayer(type);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool DialogLayer::init()
{
	//setTouchEnabled(true);
	//setTouchMode(kCCTouchesAllAtOnce);
	if(!CCLayer::init())
	{
		return false;
	}
	switch(m_type)
	{
	case dialog_hints:
		initTable("socketofboxstring",1);
		break;
	case dialog_back:
		initTable("backtodt",2);
		break;
	case dialog_poChan:
		initTable("pochan",1);
		break;
	case dialog_poChanSongCoin:
		initTable("pochansongcoin",1);
		break;
	case dialog_dismissTable:
		initTable("dismisstable",1);
		break;
	case dialog_roomLimitMax:
		initTable("roomLimitMax",1);
		break;
	case dialog_roomLimitMin:
		initTable("roomLimitMin",2);
		break;
	}
	return true;
}

bool DialogLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void DialogLayer::menuOkCallBack(CCObject * pSender)
{
	switch(m_type)
	{
	case dialog_back:
	case dialog_poChan:
	case dialog_hints:
	case dialog_dismissTable:
		{
			//EntityMgr::instance()->roomFrame()->setGameIsStart(false);
			CCDirector::sharedDirector()->replaceScene(SceneControl::sharedSceneControl()->getScene(SCENE_start,false));
		}
		break;
	case dialog_roomLimitMax:
		{
			SceneControl::sharedSceneControl()->getScene(SCENE_endAgain,false);					//--直接排队
		}
		break;
	case dialog_roomLimitMin:
		{
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_JNICONTROL,CCInteger::create(MSG_JNI_Recharge));//充值
			SceneControl::sharedSceneControl()->getScene(SCENE_endAgain,false);					//--直接排队
		}
		break;
	case dialog_poChanSongCoin:
		{
			CCDirector::sharedDirector()->replaceScene(SceneControl::sharedSceneControl()->getScene(SCENE_start,false));		//--返回大厅
			//SceneControl::sharedSceneControl()->getScene(SCENE_endAgain,false);
		}
		break;
	}
	getParent()->removeChild(this,true);
}

void DialogLayer::menuCancleCallBack(CCObject * pSender)
{
	switch(m_type)
	{
	case dialog_back:			//--不做处理
		break;
	case dialog_roomLimitMin:
		{
			SceneControl::sharedSceneControl()->getScene(SCENE_endAgain,false);					//--直接排队
		}
		break;
	}
	getParent()->removeChild(this,true);
}

void DialogLayer::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min)()+1,true);
}

void DialogLayer::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void DialogLayer::initTable( char* Name,int type)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor * colorLayer = CCLayerColor::create(ccc4(0,0,0,120));
	CCSprite * bj = CCSprite::createWithSpriteFrameName(texture_name::s_setup_bg);
	bj->setPosition(ccp(size.width/2,size.height/2));

	CCDictionary * strings = CCDictionary::createWithContentsOfFile("xml/strings.xml");
	CCLabelTTF *lableTTF = CCLabelTTF::create(((CCString*)strings->objectForKey(Name))->getCString(),
		"Helvetica-Bold",
		30,
		CCSizeMake(480,90),
		kCCTextAlignmentCenter,
		kCCVerticalTextAlignmentTop);
	lableTTF->setPosition(ccp(size.width/2,size.height/2+50));
	lableTTF->setColor(ccc3(118,78,0));
	if (type==1)
	{
		CCSprite * confirmNormalItem = CCSprite::createWithSpriteFrameName(texture_name::s_confirm);
		CCSprite * confirmSelectedItem = CCSprite::createWithSpriteFrameName(texture_name::s_confirm);
		confirmSelectedItem->setColor(ccc3(120,120,120));
		CCMenuItemSprite * itemOkSprite = CCMenuItemSprite::create(confirmNormalItem,confirmSelectedItem,NULL,this,menu_selector(DialogLayer::menuOkCallBack));
		itemOkSprite->setPosition(ccp(0,-80.0f));

		CCMenu * menu = CCMenu::create(itemOkSprite,NULL);
		//menu->setTouchPriority((std::numeric_limits<int>::min)());
		colorLayer->addChild(bj);
		colorLayer->addChild(lableTTF);
		colorLayer->addChild(menu);
	}
	else if(type==2)
	{
			CCSprite * confirmNormalItem = CCSprite::createWithSpriteFrameName(texture_name::s_confirm);
			CCSprite * confirmSelectedItem = CCSprite::createWithSpriteFrameName(texture_name::s_confirm);
			confirmSelectedItem->setColor(ccc3(120,120,120));
			CCMenuItemSprite * itemSprite = CCMenuItemSprite::create(confirmNormalItem,confirmSelectedItem,NULL,this,menu_selector(DialogLayer::menuOkCallBack));
			itemSprite->setPosition(ccp(-100.0f,-80.0f));

			CCSprite * cancleNormalItem = CCSprite::createWithSpriteFrameName(texture_name::s_btn_cancle);
			CCSprite * cancleSelectedItem = CCSprite::createWithSpriteFrameName(texture_name::s_btn_cancle);
			cancleSelectedItem->setColor(ccc3(120,120,120));
			CCMenuItemSprite * itemCancleSprite = CCMenuItemSprite::create(cancleNormalItem,cancleSelectedItem,NULL,this,menu_selector(DialogLayer::menuCancleCallBack));
			itemCancleSprite->setPosition(ccp(100.0f,-80.0f));

			CCMenu * menu = CCMenu::create(itemSprite,itemCancleSprite,NULL);
			//menu->setTouchPriority((std::numeric_limits<int>::min)());
			colorLayer->addChild(bj);
			colorLayer->addChild(lableTTF);
			colorLayer->addChild(menu);
	}
	this->addChild(colorLayer);
}
