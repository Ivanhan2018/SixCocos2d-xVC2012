#include "PlayerInfoLayer.h"
#include "RoomLayer.h"
#include "ChoosePlayerPhotoLayer.h"
#include "GroupSprite.h"
#include "entity/EntityMgr.h"
#include "MovingLabelLayer.h"
#include "ans/utf-8.h"
#include "PromptBox.h"
#include "FreeLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

PlayerInfoLayer::PlayerInfoLayer()
{
	photoTable = NULL;
	medalTable = NULL;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(PlayerInfoLayer::onModifyNickNameResult), MSG_UI_ANS_NICKNAMEUPDATE,NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(PlayerInfoLayer::onModifyTouxiangResult), MSG_UI_ANS_TOUXIANGUPDATE,NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(PlayerInfoLayer::setTouxiangModifyResult), MSG_UI_ANS_UPDATETOUXIANGNUM,NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(PlayerInfoLayer::removeTouxiangLayer), MSG_UI_ANS_UPDATETOUXIANGLAYER,NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(PlayerInfoLayer::onSureModifyNickName), MSG_UI_ANS_SUREMODYFINICKNAME,NULL);
}

PlayerInfoLayer::~PlayerInfoLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_NICKNAMEUPDATE);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_TOUXIANGUPDATE);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_UPDATETOUXIANGNUM);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_UPDATETOUXIANGLAYER);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_SUREMODYFINICKNAME);
	if(photoTable != NULL)
	{
		photoTable->release();
		photoTable = NULL;
	}
	if(medalTable != NULL)
	{
		medalTable->release();
		medalTable = NULL;
	}
}

CCScene* PlayerInfoLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		PlayerInfoLayer *layer = PlayerInfoLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

/**画面即将显示*/
void PlayerInfoLayer::onEnter()
{
	CCLayer::onEnter();
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(medalTable);
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(medalTable, kCCMenuHandlerPriority, false);
}

PlayerInfoLayer *PlayerInfoLayer::create()
{
	CCArray *normalName = CCArray::create();
	CCArray *selectedName = CCArray::create();
	normalName->addObject(CCString::create("Sprite_PlayerInfo1.png"));
	selectedName->addObject(CCString::create("Sprite_PlayerInfo2.png"));
	normalName->addObject(CCString::create("Sprite_PlayerInfo5.png"));
	selectedName->addObject(CCString::create("Sprite_PlayerInfo6.png"));
	normalName->addObject(CCString::create("Sprite_PlayerInfo3.png"));
	selectedName->addObject(CCString::create("Sprite_PlayerInfo4.png"));
	return PlayerInfoLayer::createWithTabItems(normalName, selectedName);
}

PlayerInfoLayer *PlayerInfoLayer::createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName)
{
	PlayerInfoLayer *tabLayer = new PlayerInfoLayer();
	if (tabLayer && tabLayer->initWithTabItems(itemNormalName, itemSelectedName))
	{
		tabLayer->init();
		tabLayer->autorelease();
		return tabLayer;
	}
	else
	{
		CC_SAFE_DELETE(tabLayer);
		return NULL;
	}
}

bool PlayerInfoLayer::init()
{
	bool bRet = false;
	do 
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		photoNum = 2;


		m_bInputNickName = NULL;


		/**添加底图背景**/
		photoBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_PlayerInfo13.png"));
		photoBk->setPosition(CCPointMake(135.0f, 200.5f));
		this->addChild(photoBk, 1);
		//用户照片
		const char* pSZPhonoName;
		if(g_GlobalUnits.getGolbalUserData()->cbGender == 1)
		{
			if(g_GlobalUnits.getGolbalUserData()->wFaceID > 1)
			{
				g_GlobalUnits.getGolbalUserData()->wFaceID = 0;
			}
			pSZPhonoName = CCString::createWithFormat("dt_player_%d.png",100+g_GlobalUnits.getGolbalUserData()->wFaceID)->getCString();
		}
		else
		{
			if(g_GlobalUnits.getGolbalUserData()->wFaceID > 1)
			{
				g_GlobalUnits.getGolbalUserData()->wFaceID = 0;
			}
			pSZPhonoName = CCString::createWithFormat("dt_player_%d.png",g_GlobalUnits.getGolbalUserData()->wFaceID)->getCString();
		}
		m_pPlayerPhoto = CCSprite::createWithSpriteFrame(spriteFrame(pSZPhonoName));
		m_pPlayerPhoto->setPosition(CCPointMake(135.0f,206.0f));
		addChild(m_pPlayerPhoto,1);

		float startX = 286;
		float startY = 350.0f;
		float gapY = 50;
		ccColor3B textColor = ccc3(255, 192, 0);

		//用户名字
		string pTextUserName;
		if(strlen(g_GlobalUnits.getGolbalUserData()->szNickName)>0)
		{
			CCLOG("have nick name");
			pTextUserName = g_GlobalUnits.getGolbalUserData()->szNickName;
		}
		else
		{
			CCLOG("not have nick name");
			pTextUserName = EntityMgr::instance()->login()->getAccout();
		}

		if(g_GlobalUnits.getGolbalUserData()->cbVisitor == 0)
		{
			m_pUserName = CCLabelTTF::create(CCString::createWithFormat("%s%s",ConfigMgr::instance()->text("t82"),pTextUserName.c_str())->getCString(),"",22);
		}
		else
		{
			m_pUserName = CCLabelTTF::create(CCString::createWithFormat("%s%s",ConfigMgr::instance()->text("t82"),pTextUserName.c_str())->getCString(),"",22);
		}
		m_pUserName->setColor(textColor);
		m_pUserName->setAnchorPoint(CCPointMake(0,0));
		m_pUserName->setPosition(CCPointMake(startX,startY));
		addChild(m_pUserName,1);

		//用户性别
		//CCSprite *pButtonBJ = CCSprite::create("dt_warning_8.png");
		const char *pTextUserSex;
		if(g_GlobalUnits.getGolbalUserData()->cbGender == 1)
		{
			pTextUserSex = CCString::createWithFormat
				("%s%s",ConfigMgr::instance()->text("t83"),ConfigMgr::instance()->text("t150"))->getCString();
		}
		else
		{
			pTextUserSex = CCString::createWithFormat
				("%s%s",ConfigMgr::instance()->text("t83"),ConfigMgr::instance()->text("t151"))->getCString();
		}

		m_pUserSex = CCLabelTTF::create(pTextUserSex,"HelveticaNeue-Bold", 22);
		m_pUserSex->setColor(textColor);
		m_pUserSex->setAnchorPoint(CCPointMake(0,0));
		m_pUserSex->setPosition(CCPointMake(startX,startY-gapY));
		addChild(m_pUserSex,1);

		//用户金币
		const char *pTextUserGold = CCString::createWithFormat
			("%s%d",ConfigMgr::instance()->text("t85"),g_GlobalUnits.getGolbalUserData()->lScore)->getCString();
		pUserGold = CCLabelTTF::create(pTextUserGold,"HelveticaNeue-Bold", 22);
		pUserGold->setColor(textColor);
		pUserGold->setAnchorPoint(CCPointMake(0,0));
		pUserGold->setPosition(CCPointMake(startX,startY-2*gapY));
		addChild(pUserGold,1);

		//用户战绩
		const char *pTextUserRecord = CCString::createWithFormat
			("%s%d%s/%d%s",ConfigMgr::instance()->text("t88"),g_GlobalUnits.getGolbalUserData()->lWinCount,ConfigMgr::instance()->text("t165"),g_GlobalUnits.getGolbalUserData()->lLostCount,ConfigMgr::instance()->text("t166"))->getCString();
		pUserRecord = CCLabelTTF::create(pTextUserRecord,"HelveticaNeue-Bold", 22);
		pUserRecord->setColor(textColor);
		pUserRecord->setAnchorPoint(CCPointMake(0,0));
		pUserRecord->setPosition(CCPointMake(startX,startY-3*gapY));
		addChild(pUserRecord,1);

		//用户胜率
		int lTotalCount = g_GlobalUnits.getGolbalUserData()->lWinCount+
			g_GlobalUnits.getGolbalUserData()->lLostCount+
			g_GlobalUnits.getGolbalUserData()->lFleeCount;
		const char *pTextUserWinning;
		if(lTotalCount == 0)
		{
			pTextUserWinning = CCString::createWithFormat
				("%s%d%%",ConfigMgr::instance()->text("t89"),0)->getCString();
		}
		else
		{
			pTextUserWinning = CCString::createWithFormat
				("%s%.2f%%",ConfigMgr::instance()->text("t89"),((float)g_GlobalUnits.getGolbalUserData()->lWinCount/(float)g_GlobalUnits.getGolbalUserData()->lTotalCount)*100)->getCString();
		}

		pUserWinning = CCLabelTTF::create(pTextUserWinning,"HelveticaNeue-Bold", 22);
		pUserWinning->setColor(textColor);
		pUserWinning->setAnchorPoint(CCPointMake(0,0));
		pUserWinning->setPosition(CCPointMake(startX,startY-4*gapY));
		addChild(pUserWinning,1);

		CCSprite *tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_PlayerInfo9.png"));
		tableViewCellSize = tempSprite->getContentSize();
		//照片
		CCSize tableViewSize;
		tableViewSize.width = 560;
		tableViewSize.height = tempSprite->getContentSize().height;
		photoTable = CCTableView::create(this, tableViewSize);
		photoTable->setDelegate(this);
		photoTable->setAnchorPoint(CCPointMake(0.5, 0.5));
		photoTable->setPosition(CCPointMake(256, 32));
		photoTable->setDirection(kCCScrollViewDirectionHorizontal);
		photoTable->retain();
		this->addChild(photoTable, 1);
		photoTable->reloadData();

		//勋章
		MedalTableHelper *helper = new MedalTableHelper(this);
		tableViewSize.width = 800;
		tableViewSize.height = 379;
		medalTable = CCTableView::create(helper, tableViewSize);
		medalTable->setContentSize(tableViewSize);
		medalTable->setDelegate(helper);
		medalTable->setAnchorPoint(CCPointMake(0.5, 0.5));
		medalTable->setPosition(CCPointMake(0, 10));
		medalTable->setVerticalFillOrder(kCCTableViewFillTopDown);
		medalTable->setDirection(kCCScrollViewDirectionVertical);
		medalTable->retain();
		this->addChild(medalTable, 1);
		medalTable->reloadData();
		medalTable->setVisible(false);

		labelMedalInfo = CCLabelTTF::create("","HelveticaNeue-Bold", 30, CCSizeMake(500,0),kCCTextAlignmentCenter);
		labelMedalInfo->setAnchorPoint(ccp(0.5f,0.5f));
		labelMedalInfo->setColor(textColor);
		labelMedalInfo->setPosition(ccp(0,0));
		this->addChild(labelMedalInfo,2);
		labelMedalInfo->setVisible(false);

		bRet = true;
		setKeypadEnabled(true);
	} while (0);

	return bRet;

}

void PlayerInfoLayer::doSomething()
{
	CCLog("PlayerInfoLayer::doSomething");
	if(currentItem == TabLayerBaseTag){
		m_pPlayerPhoto->setVisible(true);						//用户头像
		photoBk->setVisible(true);								//头像背景
		m_pUserName->setVisible(true);						//用户名字
		m_pUserSex->setVisible(true);							//用户性别
		pUserGold->setVisible(true);							//用户金币
		pUserRecord->setVisible(true);						//用户战绩
		pUserWinning->setVisible(true);						//用户胜率
		photoTable->setVisible(true);

		medalTable->setVisible(false);
		labelMedalInfo->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+2){
		m_pPlayerPhoto->setVisible(false);						//用户头像
		photoBk->setVisible(false);								//头像背景
		m_pUserName->setVisible(false);						//用户名字
		m_pUserSex->setVisible(false);							//用户性别
		pUserGold->setVisible(false);							//用户金币
		pUserRecord->setVisible(false);						//用户战绩
		pUserWinning->setVisible(false);						//用户胜率
		photoTable->setVisible(false);

		medalTable->setVisible(false);
		labelMedalInfo->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+1){
		m_pPlayerPhoto->setVisible(false);						//用户头像
		photoBk->setVisible(false);								//头像背景
		m_pUserName->setVisible(false);						//用户名字
		m_pUserSex->setVisible(false);							//用户性别
		pUserGold->setVisible(false);							//用户金币
		pUserRecord->setVisible(false);						//用户战绩
		pUserWinning->setVisible(false);						//用户胜率
		photoTable->setVisible(false);

		medalTable->setVisible(true);
		labelMedalInfo->setVisible(false);
	}
}
/**单元格大小
参数：table单元格所属的表格
*/
CCSize PlayerInfoLayer::cellSizeForTable(CCTableView *table)
{
	CCSize size = tableViewCellSize;
	size.width+=30;
	return size;
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int PlayerInfoLayer::numberOfCellsInTableView(CCTableView *table)
{
	int size;
	size = 4;
	return size;
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *PlayerInfoLayer::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell(); 
	cell->autorelease(); 
	char name[32];
	sprintf(name, "Sprite_PlayerInfo%d.png", index+9);
	CCPoint pos = cell->getPosition();
	CCSprite *normalSprite= CCSprite::createWithSpriteFrame(spriteFrame(name));
	CCSprite *selectSprite = CCSprite::createWithSpriteFrame(spriteFrame(name));
	selectSprite->setScale(0.9f);
	CCMenuItemSprite *pButton = CCMenuItemSprite::create
		(normalSprite,selectSprite,this,menu_selector(PlayerInfoLayer::pressChangePhoto));
	CCMenu *menu = CCMenu::createWithItem(pButton);
	menu->setAnchorPoint(CCPointMake(0.5f,0.5f));
	menu->setPosition(CCPointMake(2.5f+tableViewCellSize.width/2,tableViewCellSize.height/2));
	cell->addChild(menu);
	if(index>=photoNum)
	{
		menu->setEnabled(false);
	}
	return cell;  
}

/**点击单元格
参数：table，单元格所属的表格
cell，单元格
*/
void PlayerInfoLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
	//CCLabelTTF *nameLabel = (CCLabelTTF *)cell->getChildByTag(nameLabelTag);
	//const char *name = nameLabel->getString();
	//textField->setString(name);
	//this->removeChild(_tableView, true);
	//flag = 0;
}

void PlayerInfoLayer::scrollViewDidScroll(CCScrollView* view)
{

}
void PlayerInfoLayer::scrollViewDidZoom(CCScrollView* view)
{

}

void PlayerInfoLayer::pressChangePhoto(CCObject *pObject)
{

}

void PlayerInfoLayer::dismiss(cocos2d::CCObject *obj){
	playButtonSound();
	this->removeFromParentAndCleanup(true);
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void PlayerInfoLayer::keyBackClicked()
{
	dismiss(NULL);
}

void PlayerInfoLayer::changeUserName(cocos2d::CCObject *obj)
{
	playButtonSound();
	if(!m_bInputNickName)
	{	
		m_pNickNameInput->setTouchEnabled(true);
		m_pNickNameInput->setVisible(true);
		m_bInputNickName = true;
		return;
	}

	m_szModifyNickName = const_cast<char*>( m_pNickNameInput->getText());

	if(!isLegal(m_szModifyNickName))
	{
		PromptBox* box = PromptBox::PromptBoxWith(CCPointMake(427,240),mPromptNickNameError);
		addChild(box,10);
		return;
	}

	if(strlen(m_szModifyNickName) > 12 || strlen(m_szModifyNickName) < 4)
	{
		PromptBox* box = PromptBox::PromptBoxWith(CCPointMake(427,240),mPromptTypeErrorNickName);
		addChild(box,10);
	}
	else
	{
		PromptBox* box = PromptBox::PromptBoxWith(CCPointMake(427,240),mPromptTypeMakeSureModifyNickName);
		addChild(box,10);
	}
}

void PlayerInfoLayer::onSureModifyNickName(CCObject* obj)
{
	if(!EntityMgr::instance()->getDispatch()->connectLoginServer())
	{
		return;
	}
	/*char* szModifyNickName = const_cast<char*>( m_pNickNameInput->getText());*/
	//char buf[50];
	//memset(buf, 0, 50);
	////utf::utf_gb_convert("utf-8", "gb2312", buf,50, szModifyNickName, strlen(szModifyNickName));
	//utf::utf_gb_convert("utf-8", "gb2312", buf,50, m_szModifyNickName, strlen(m_szModifyNickName));
	EntityMgr::instance()->getDispatch()->modifyNickName(m_szModifyNickName);
}

void PlayerInfoLayer::setTouxiangModifyResult(CCObject* obj)
{
	CCInteger* inter = (CCInteger*)obj;
	m_nGenterResult = inter->getValue()/10;
	m_nHeadResult = inter->getValue()%10;
}

void PlayerInfoLayer::onModifyTouxiangResult(CCObject* obj)
{
	CCInteger* pNickNameResult = (CCInteger*)obj;
	int i = pNickNameResult->getValue();
	if(i == 0)
	{
		//更换性别
		g_GlobalUnits.getGolbalUserData()->cbGender = m_nGenterResult;
		const char *pTextUserSex;
		if(g_GlobalUnits.getGolbalUserData()->cbGender == 1)
		{
			pTextUserSex = CCString::createWithFormat
				("%s%s",ConfigMgr::instance()->text("t83"),ConfigMgr::instance()->text("t150"))->getCString();
		}
		else
		{
			pTextUserSex = CCString::createWithFormat
				("%s%s",ConfigMgr::instance()->text("t83"),ConfigMgr::instance()->text("t151"))->getCString();
		}

		m_pUserSex->setString(pTextUserSex);

		//更换头像
		g_GlobalUnits.getGolbalUserData()->wFaceID = m_nHeadResult;
		const char* pSZPhonoName;
		if(g_GlobalUnits.getGolbalUserData()->cbGender == 1)
		{
			if(g_GlobalUnits.getGolbalUserData()->wFaceID > 1)
			{
				g_GlobalUnits.getGolbalUserData()->wFaceID = 0;
			}
			pSZPhonoName = CCString::createWithFormat("dt_player_%d.png",100+g_GlobalUnits.getGolbalUserData()->wFaceID)->getCString();
		}
		else
		{
			if(g_GlobalUnits.getGolbalUserData()->wFaceID > 1)
			{
				g_GlobalUnits.getGolbalUserData()->wFaceID = 0;
			}
			pSZPhonoName = CCString::createWithFormat("dt_player_%d.png",g_GlobalUnits.getGolbalUserData()->wFaceID)->getCString();
		}
		m_pPlayerPhoto->setDisplayFrame(spriteFrame(pSZPhonoName));
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t408"),CCPointMake(427,240));
		addChild(layer,20);
		//成功
	}
	else
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t162"),CCPointMake(427,240));
		addChild(layer);
		//失败
	}
}

void PlayerInfoLayer::onModifyNickNameResult(CCObject* obj)
{
	CCInteger* pNickNameResult = (CCInteger*)obj;
	int i = pNickNameResult->getValue();
	if(i == 0)
	{
		if(g_GlobalUnits.getGolbalUserData()->cbVisitor == 1)
		{
			m_pUserName->setString(CCString::createWithFormat("%s%s",ConfigMgr::instance()->text("t82"),m_szModifyNickName)->getCString());
		}
		else
		{
			m_pUserName->setString(CCString::createWithFormat("%s%s",ConfigMgr::instance()->text("t82"),m_szModifyNickName)->getCString());
		}
		strcpy(g_GlobalUnits.getGolbalUserData()->szNickName, m_szModifyNickName);
		pMenu1->setVisible(false);
		pMenu1->removeFromParentAndCleanup(true);
		pMenu1 = NULL;
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t409"),CCPointMake(427,240));
		addChild(layer,20);
		//成功
	}
	else
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t162"),CCPointMake(427,240));
		addChild(layer);
		//失败
	}
	if(m_bInputNickName)
	{
		m_pNickNameInput->removeFromParentAndCleanup(true);
		m_pNickNameInput = NULL;
		m_bInputNickName = false;
	}
}

void PlayerInfoLayer::rechange(CCObject* obj)
{
	playButtonSound();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//低等级 = 1 中等级 = 2 高等级 = 3 有X = 1 没X = 2
	if(g_GlobalUnits.getGolbalUserData()->lScore < ConfigMgr::instance()->m_Config.nServerEnter[(((1-1) % 3 ) << 1) + 1])
	{
		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"1","5");
	}
	else if(g_GlobalUnits.getGolbalUserData()->lScore < ConfigMgr::instance()->m_Config.nServerEnter[(((2-1) % 3 ) << 1) + 1])
	{
		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"2","5");
	}
	else
	{
		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"3","5");
	}
#endif
}
//void PlayerInfoLayer::saveChange(cocos2d::CCObject *obj){

//}
void PlayerInfoLayer::changeUserPhoto(cocos2d::CCObject *obj){
	playButtonSound();
	this->forbidButtom();
	if(m_bInputNickName){
		m_pNickNameInput->setVisible(false);
		m_pNickNameInput->setTouchEnabled(false);
		m_bInputNickName = false;
	}
	ChoosePlayerPhotoLayer *pChoosePlayerPhoto = ChoosePlayerPhotoLayer::create();
	addChild(pChoosePlayerPhoto,5,100);

}

void PlayerInfoLayer::removeTouxiangLayer(CCObject* obj)
{
	ChoosePlayerPhotoLayer *pChoosePlayerPhoto = (ChoosePlayerPhotoLayer*)this->getChildByTag(100);
	pChoosePlayerPhoto->removeFromParentAndCleanup(true);
	this->permitButtom();
}
/**禁止该界面的所有按钮功能**/
void PlayerInfoLayer::forbidButtom(){
	pCloseButton->setEnabled(false);
	pMenuPlayer->setEnabled(false);
	mianfeiMenu->setEnabled(false);
	if(pMenu1)
	{
		pMenu1->setEnabled(false);
	}
	//pMenu2->setEnabled(false);
}
/**打开该界面的所有按钮功能**/
void PlayerInfoLayer::permitButtom(){
	pCloseButton->setEnabled(true);
	pMenuPlayer->setEnabled(true);
	mianfeiMenu->setEnabled(true);
	if(pMenu1)
	{
		pMenu1->setEnabled(true);
	}
	//pMenu2->setEnabled(true);
}
void PlayerInfoLayer::toFreeLayer(CCObject* obj)
{
	playButtonSound();
	CCDirector::sharedDirector()->replaceScene(FreeLayer::scene());
}

bool PlayerInfoLayer::isLegal(string str)
{
	//const char* s = str.c_str();
	char s[128] = {0};
	memcpy(s, str.c_str(), min(sizeof(s)-1, str.length()));
	CCLOG("get user accout str = %s, strlen(str)=%d",str.c_str(), strlen(str.c_str()));
	CCLOG("get user accout char = %s strlen(s)=%d", s, strlen(s));
	int i = 0;
	while (i++ < str.length() - 1)
	{
		if (s[i] < 0 || s[i] > 127)
		{
			//("中文");
			CCLOG("registLayer chinese");
		}
		else if (s[i]>='0' && s[i]<='9')
		{
			//("数字");
			CCLOG("registLayer number");
		}
		else if (s[i]>='A' && s[i]<='Z' || s[i]>='a' && s[i]<='z')
		{
			CCLOG("registLayer a b c");
		}
		else
		{
			//("其它");
			CCLOG("RegistLayer::isLegal false s[%d]:%d %s", i, s[i], &s[i]);
			return  false;
		}
	}
	return  true;
}

MedalTableHelper::MedalTableHelper(CCObject *fath)
{
	father = fath;
	winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *tempSprite = CCSprite::createWithSpriteFrame(spriteFrame(CCString::createWithFormat("%s0.png", SPRITE_MEDAL_L)->getCString()));
	tableItemSize = tempSprite->getContentSize();
	tableGapX = (winSize.width-tableItemSize.width*MEDAL_TABLE_COLUMN)/(MEDAL_TABLE_COLUMN+1);
	tableGapY = 10;
}

MedalTableHelper::~MedalTableHelper()
{

}

/**单元格大小
参数：table单元格所属的表格
*/
CCSize MedalTableHelper::cellSizeForTable(CCTableView *table)
{
	return CCSize(winSize.width, tableItemSize.height+tableGapY);
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int MedalTableHelper::numberOfCellsInTableView(CCTableView *table)
{
	int size;
	size = MEDAL_NUM/MEDAL_TABLE_COLUMN;
	if(MEDAL_NUM%MEDAL_TABLE_COLUMN!=0)
	{
		size++;
	}
	return size;
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *MedalTableHelper::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = NULL;
	//cell = table->dequeueCell();
	if(cell == NULL)
	{
		cell = new CCTableViewCell();  
		cell->autorelease(); 
		char name[32];
		float startX = tableItemSize.width/2+tableGapX;
		float startY = tableItemSize.height/2+tableGapY;
		for(int i = 0 ; i < MEDAL_TABLE_COLUMN&&(((int)index*MEDAL_TABLE_COLUMN+i)<MEDAL_NUM) ; i++)
		{
			sprintf(name, "%s%d.png", SPRITE_MEDAL_A, (int)index*MEDAL_TABLE_COLUMN+i);

			CCScale9Sprite *medalSprite = CCScale9Sprite::createWithSpriteFrame(spriteFrame(name));
			CCControlButton *button = CCControlButton::create(medalSprite);
			button->setPreferredSize(medalSprite->getPreferredSize());
			button->setTag(((int)index*MEDAL_TABLE_COLUMN+i));
			button->setPosition(ccp(startX, startY));
			button->addTargetWithActionForControlEvents(father, cccontrol_selector(PlayerInfoLayer::showMedalInfo), CCControlEventTouchDown);
			cell->addChild(button);
			startX+=tableItemSize.width+tableGapX;
		}
	}
	return cell;  
}

/**点击单元格
参数：table，单元格所属的表格
cell，单元格
*/
void MedalTableHelper::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{

}

void MedalTableHelper::scrollViewDidScroll(CCScrollView* view)
{

}
void MedalTableHelper::scrollViewDidZoom(CCScrollView* view)
{

}

void PlayerInfoLayer::showMedalInfo(cocos2d::CCObject *obj, CCControlEvent event)
{
	CCNode *target = ((CCNode *)obj);
	CCNode *parentNode = target->getParent();
	int tag = target->getTag();
	if(event == CCControlEventTouchDown)
	{
		ccColor3B textColor = ccc3(0,255,0);
		labelMedalInfo->setString(ConfigMgr::instance()->text(CCString::createWithFormat("t%d", 720+tag)->getCString()));
		labelMedalInfo->setColor(textColor);
		labelMedalInfo->setPosition(ccpAdd(target->convertToWorldSpace(target->getPosition()), ccp(0,0)));
		labelMedalInfo->setPositionX(target->getPositionX());
		CCTintTo *tintTo = CCTintTo::create(1.0f,0,50,0);
		//CCFiniteTimeAction *sequence = CCSequence::create(CCShow::create(), tintTo, CCHide::create(), NULL);
		CCFiniteTimeAction *sequence = CCSequence::create(CCShow::create(), CCDelayTime::create(1.5f), CCHide::create(), NULL);
		labelMedalInfo->stopAllActions();
		labelMedalInfo->runAction(sequence);
	}
}


