#include "HallLayer.h"
#include "SkinControls.h"
#include "PlayerLayer.h"
#include "FishSprite.h"

static int sp_ProcessBar_Tag = 0;
static int sp_ProcessAnimation_Tag = 1;

HallLayer::HallLayer(void)
{
	pSetting=nullptr;
	pBuyBullet=nullptr;

	setTouchEnabled(true);
}


HallLayer::~HallLayer(void)
{
}

void HallLayer::onEnter()
{
	CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCSprite * bg = CCSprite::create("bg/bg1.jpg");
	bg->setPosition(ccp(s.width/2, s.height/2));
	addChild(bg);

	CCMenuItemImage * pItemHelp = CCMenuItemImage::create("button/normal1.png", "button/select1.png", "button/hightlight1.png", this, menu_selector(HallLayer::OnHelp) );
	CCMenuItemImage * pItemSet = CCMenuItemImage::create("button/normal1.png", "button/select1.png", "button/hightlight1.png", this, menu_selector(HallLayer::OnHelp) );
	CCMenuItemImage * pItemSupplement = CCMenuItemImage::create("button/normal.png", "button/select.png", "button/hightlight.png", this, menu_selector(HallLayer::OnHelp) );
	CCMenuItemImage * pItemMyDepot = CCMenuItemImage::create("button/normal.png", "button/select.png", "button/hightlight.png", this, menu_selector(HallLayer::OnHelp) );
	CCMenuItemImage * pItemGam = CCMenuItemImage::create("button/normal.png", "button/select.png", "button/hightlight.png", this, menu_selector(HallLayer::OnHelp) );
	CCMenuItemImage * pItemShop = CCMenuItemImage::create("button/normal.png", "button/select.png", "button/hightlight.png", this, menu_selector(HallLayer::OnHelp) );
	CCMenuItemImage * pItemBullet = CCMenuItemImage::create("button/normal.png", "button/select.png", "button/hightlight.png", this, menu_selector(HallLayer::OnHelp) );
	CCMenuItemImage * pItemMission = CCMenuItemImage::create("button/normal.png", "button/select.png", "button/hightlight.png", this, menu_selector(HallLayer::OnHelp) );
	CCMenuItemImage * pItemSuccess = CCMenuItemImage::create("button/normal.png", "button/select.png", "button/hightlight.png", this, menu_selector(HallLayer::OnHelp) );
	CCMenuItemImage * pItemExit = CCMenuItemImage::create("button/normal.png", "button/select.png", "button/hightlight.png", this, menu_selector(HallLayer::OnHelp) );

	float fX=0, fY=0;
	setMenuItemEx( pItemHelp,1, fX, fY);
	setMenuItemEx( pItemSet,2, fX, fY);
	setMenuItemEx( pItemSupplement,3, fX, fY);
	setMenuItemEx( pItemMyDepot,4, fX, fY);
	setMenuItemEx( pItemGam,5, fX, fY);
	setMenuItemEx( pItemShop,6, fX, fY);
	setMenuItemEx( pItemBullet,7, fX, fY);
	setMenuItemEx( pItemMission,8, fX, fY);
	setMenuItemEx( pItemSuccess,9, fX, fY);
	setMenuItemEx( pItemExit,10, fX, fY);
	CCMenu * pMenu = CCMenu::create(pItemHelp, pItemSet, pItemSupplement, pItemMyDepot, pItemGam, pItemShop, pItemBullet, pItemMission, pItemSuccess, pItemExit, NULL);
	addChild( pMenu, 100 );
	pMenu->setAnchorPoint(ccp(0, 0));
	pMenu->setPosition( ccp(0, 0) );

	// 初始鱼群
	CFashManage::Init( this );

	// 初始玩家
	PlayerManage::create(this, 3);
	PlayerManage::create(this, 2, true);
	PlayerManage::create(this, 1);
	PlayerManage::create(this, 0);

	// 更新捕鱼情况
	schedule(schedule_selector(HallLayer::Update), 0.05f);
}

void HallLayer::onExit()
{
	CFashManage::Release();
}

void HallLayer::Update(float)
{
	CCObject* pBulletObject = NULL;
	CCObject* pFishObject = NULL;
	PlayerLayer *pPlayer=PlayerManage::GetMyPlayer();
	CBulletManage *pManage=PlayerManage::GetMyPlayer()->getBulletManage();
	CCSpriteBatchNode *pNode = PlayerManage::GetMyPlayer()->getBulletManage()->sharedBullet();
	unsigned int aa=pNode->getChildrenCount();

	CCARRAY_FOREACH(PlayerManage::GetMyPlayer()->getBulletManage()->sharedBullet()->getChildren(), pBulletObject)
	{
		BulletSprite *pBullet = (BulletSprite *)pBulletObject;
		if ( pBullet->getIsCatching() )
			continue;

		CCARRAY_FOREACH(CFashManage::sharedFish()->getChildren(), pFishObject)
		{
			FishSprite *pFish = (FishSprite *)pFishObject;
			if (pFish->getIsCatching())
				continue;

			if ( pFish->boundingBox().containsPoint( pBullet->getPosition() ) )
			{
				pFish->setIsCatching( true );
				pBullet->setIsCatching( true );

				CCArray* pArray = CCArray::create();
				for(int i = 1; i < 3; i++)
				{
					pArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("fish0%d_catch_0%d.png",pFish->getTag(),i)->getCString()));
				}

				CCPoint ptHit( pBullet->getPositionX(), pBullet->getPositionY() );
				CCRepeat* pStruggleAnimation = CCRepeat::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(pArray, 0.2f)), 2); // 鱼挣扎
				CCFiniteTimeAction *pReleaseFishAnimation = CCCallFunc::create(pFish, callfunc_selector(FishSprite::removeSelf)); // 释放鱼
				CCFiniteTimeAction *pBulletNetAnimation = CCCallFuncND::create(pBullet, callfuncND_selector(BulletSprite::FinishAnimation), (void *)&ptHit ); // 子弹隐藏，鱼网打开
				
				pBullet->stopAllActions();
				pBullet->setVisible( false );
				//CCActionInterval *pCastingNetAnimation = pBullet->castingNetAnimation();
				//CCFiniteTimeAction *pReleaseButtleAnimation = CCCallFunc::create(pBullet, callfunc_selector(BulletSprite::Release)); // 释放鱼

				CCFiniteTimeAction* catchSequence = CCSequence::create(pBulletNetAnimation, pStruggleAnimation, /*pReleaseButtleAnimation, */pReleaseFishAnimation, NULL);
				pFish->stopAllActions();
				pFish->runAction( catchSequence );
				
				//pBullet->runAction( pBulletNetAnimation );
			}
		}
	}

	// 保持鱼数目维持在 d_Fish_Max_Count
	while( CFashManage::sharedFish()->getChildrenCount() < d_Fish_Max_Count )
	{
		FishSprite::Fish_Type fishTytpe = (FishSprite::Fish_Type)(rand() % (FishSprite::Fish_Type_Count-1) + 1);
		CFashManage::addOneFish( fishTytpe );
	}
}

CCAnimate * HallLayer::CreateFrameAnimate(CCSpriteFrameCache * pCache, char * pSigleName, int iSize, float fTime)
{
	CCArray * pArray1 = CCArray::createWithCapacity( iSize );
	char cBuffer[100]="";
	for (int i=0; i<iSize; i++)
	{
		sprintf(cBuffer, pSigleName, i);
		CCSpriteFrame *pSpriteFrame = pCache->spriteFrameByName(cBuffer);
		pArray1->addObject( pSpriteFrame );
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(pArray1, fTime);
	return CCAnimate::create(animation);
}

void HallLayer::OnHelp(CCObject* pSender)
{
	int tag=(dynamic_cast<CCNode *>(pSender))->getTag();
	if(tag==3)
	{
	    ShowSetWnd(true);
		return;
	}
	if(tag==4)
	{
	    ShowBuyBulletWnd(true);
		return;
	}
	if(tag==5)//SIX_MusicMgr测试，PC/i809可跑(去掉路径中的./)
	{
		// 加载音效
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->SetSoundResourceFolder("Music");
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->LoadXMLFromFile("Music/SoundList.xml");
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->ReleaseXML();
		SIXLog("音效总数[%d] , 背景[%d] , 特效[%d]",
			SIX_GlobalMgr::GetInstance()->GetMusicMgr()->GetTotalSoundCount(),
			SIX_GlobalMgr::GetInstance()->GetMusicMgr()->GetBgSoundCount(),
			SIX_GlobalMgr::GetInstance()->GetMusicMgr()->GetEffectSoundCount()
			);

		// 随机背景音乐
		int soundID = SIX_Utility::RNDNUM(0,SIX_GlobalMgr::GetInstance()->GetMusicMgr()->GetBgSoundCount());
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playBackgroundMusic(soundID);	
	   return;
	}
}

void HallLayer::ShowSetWnd(bool bShow)
{
	if (!pSetting)
	{
		pSetting = SIX_PopWndSetting::Create(0.0,0.0,ccc4(0,0,0,0),459,258,false);
		pSetting->InitMask(ccc4(0,0,0,128));
		pSetting->backgroundWithFile("Common/Setting/popwnd.png");
		pSetting->buttonSubmitWithFileCell("Common/Button/return.png",3);
		//pSetting->GetBtnSubmit()->setPosition(ccp(167,10));
		//pSetting->buttonCancelWithFileCell("Common/Setting/btn_cancel.png",4);
		//pSetting->AutoCaclBtnPosWidthYesOrNo(45,20);
		pSetting->Show(bShow);
	}
	else
	{
		pSetting->Show(bShow);
	}
	//m_pCurShowWnd = pSetting;
}

void HallLayer::ShowBuyBulletWnd(bool bShow)
{
	// 小于等于0房间未初化，3为比赛房间
	/*if (0 >= PlayerTreasureInfo::Instance().m_lGameType  ||  3==PlayerTreasureInfo::Instance().m_lGameType)
		return;*/

	if (!pBuyBullet)
	{
		pBuyBullet = SIX_PopWndBuyBullet::Create(0.0,0.0,ccc4(0,0,0,0),512,382,false);
		pBuyBullet->InitMask(ccc4(0,0,0,128));
		pBuyBullet->backgroundWithFile("Common/BuyBullet/popwnd.png");
		//pBuyBullet->buttonSubmitWithFileCell("Common/Setting/btn_ok.png",3);
		pBuyBullet->buttonCancelWithFileCell("Common/Button/return.png",3);
		//pBuyBullet->GetBtnCancel()->setPosition(193,10);
		pBuyBullet->Show(bShow);
	}
	else
	{
		pBuyBullet->Show(bShow);
	}
	//m_pCurShowWnd = pBuyBullet;
}

void HallLayer::setMenuItemEx(CCMenuItemImage * pItem,int tag, float &fX, float &fY)
{
	pItem->setTag(tag);
	pItem->setAnchorPoint(ccp(0, 0));
	pItem->setPosition( fX, fY );
	fX += pItem->getContentSize().width;
}

void HallLayer::scene()
{
	CCScene * pScene = CCScene::create();
	HallLayer * pLoading = new HallLayer;
	pScene->addChild( pLoading );
	pLoading->release();

	CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(0.5f, pScene, ccBLACK) );
}