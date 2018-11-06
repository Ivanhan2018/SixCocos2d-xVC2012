#include "FreeCell.h"
#include "common/CocosUnits.h"
#include "configMgr/ConfigMgr.h"
#include "entity/EntityMgr.h"
#include "FreeLayer.h"
#include "FreeScrollLayer.h"
#include "MovingLabelLayer.h"
#include "RoomLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

FreeCell::FreeCell(void){
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(FreeCell::setMenuEnable), MSG_UI_ANS_CANNELDOWNLOADGAME, NULL);
}
FreeCell::~FreeCell(void){
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_RUNBREAD);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_CHANGSHAMAJIADOWNLOAD);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_RUNFASTDOWNLOAD);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_THREETOONE);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_CANNELDOWNLOADGAME);
}
FreeCell *FreeCell::FreeCellWith(int type,bool isGet){
	FreeCell* Cell = new FreeCell();
	if(Cell)
	{
		Cell->initFreeCellWith(type,isGet);
		Cell->autorelease();
		return Cell;
	}
	CC_SAFE_DELETE(Cell);
	return NULL;
}
bool FreeCell::initFreeCellWith(int type,bool isGet){
	    m_nType = type;

		m_nIsget = isGet;

		if(m_nType == 0)
		{
			CCNotificationCenter::sharedNotificationCenter()->addObserver(
				this, callfuncO_selector(FreeCell::setPesent), MSG_UI_ANS_CHANGSHAMAJIADOWNLOAD, NULL);
		}
		if(m_nType == 1)
		{
			CCNotificationCenter::sharedNotificationCenter()->addObserver(
				this, callfuncO_selector(FreeCell::setPesent), MSG_UI_ANS_RUNFASTDOWNLOAD, NULL);
		}
		if(m_nType == 2)
		{
			CCNotificationCenter::sharedNotificationCenter()->addObserver(
				this, callfuncO_selector(FreeCell::setPesent), MSG_UI_ANS_RUNBREAD, NULL);
		}
		if(m_nType == 3)
		{
			CCNotificationCenter::sharedNotificationCenter()->addObserver(
				this, callfuncO_selector(FreeCell::setPesent), MSG_UI_ANS_THREETOONE, NULL);
		}

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pBGLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_4.png"));
		pBGLeft->setPosition(CCPointMake(211.5f,45.0f));
		addChild(pBGLeft,0);
		CCSprite *pBGRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_4.png"));
		//pBGRight->setRotationY(180.0f);
		pBGRight->setPosition(CCPointMake(596.5f - 1.0f,45.0f));
		addChild(pBGRight,0);
		const char *pStr = CCString::createWithFormat("dt_free_1%d.png",m_nType)->getCString();
		pSprite = CCSprite::createWithSpriteFrame(spriteFrame(pStr));
		pSprite->setPosition(CCPointMake(64.0f,45.0f));
		addChild(pSprite,1);


		/**��ӽ�����**/
		pJinDuTiao0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_14.png"));
		pJinDuTiao0->setAnchorPoint(ccp(0,0.5f));
		pJinDuTiao0->setPosition(CCPointMake(148.0f,48.0f));
		addChild(pJinDuTiao0,1);

		pJinDuTiao1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_15.png"));
		pJinDuTiao = CCProgressTimer::create(pJinDuTiao1);
		///**�����ý�������������**/
		pJinDuTiao->setMidpoint(ccp(0.0f,0.0f));
		pJinDuTiao->setBarChangeRate(ccp(1,0));
		pJinDuTiao->setType(kCCProgressTimerTypeBar);
		pJinDuTiao->setPercentage(0.0f);
		pJinDuTiao->setAnchorPoint(ccp(0,0.5f));
		pJinDuTiao->setPosition(CCPointMake(148.0f,48.0f)); 
		addChild(pJinDuTiao,2);
		
	
		m_titile = CCLabelTTF::create("","",18);
		m_titile->setAnchorPoint(ccp(0,0.5));
		m_titile->setPosition(ccp(148.0f,72.0f));
		m_titile->setColor(ccc3(0,0,0));
		addChild(m_titile,1);

		m_text = CCLabelTTF::create("","",18);
		m_text->setAnchorPoint(ccp(0,0.5));
		m_text->setPosition(ccp(148.0f,23.0f));
		m_text->setColor(ccc3(0,0,0));
		addChild(m_text,1);
				
        
			
		if(!isGet)
		{
			pTextWaring = CCLabelTTF::create(ConfigMgr::instance()->text("t170"),"",18);
		}
		else
		{
			pTextWaring = CCLabelTTF::create(ConfigMgr::instance()->text("t459"),"",18);
		}
		pTextWaring->setPosition(CCPointMake(710.0f,72.0f));
		pTextWaring->setColor(ccc3(0,0,0));
		addChild(pTextWaring,1);
		CCSprite *pNormalDownload;
		CCSprite *pSelectDownload;
		CCSprite* pDisDownload;

		bool bExit = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if(m_nType == 0)
		{
			bExit = isGameExit(3);
		}
		else if(m_nType == 1)
		{
			bExit = isGameExit(6);
		}
		else if(m_nType == 2)
		{
			bExit = isGameExit(2);
		}
		else if(m_nType == 3)
		{
			bExit = isGameExit(5);
		}
		CCLOG("ALREADY GET GAMEINFO");
#endif

		if(bExit)
		{
			if(isGet)
			{
				pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
				pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
				pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
				pJinDuTiao->setVisible(false);
				pJinDuTiao0->setVisible(false);
			}
			else
			{
				pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
				pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
				pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
				pJinDuTiao->setVisible(false);
				pJinDuTiao0->setVisible(false);
			}
		}
		else
		{
			pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
			pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
			pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
		}
		
		m_pMenuButton = CCMenuItemSprite::create(pNormalDownload,pSelectDownload,this,menu_selector(FreeCell::chooseFree));
	    pSelectDownload->setScale(0.9f);
		pSelectDownload->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pMenu = CCMenu::create(m_pMenuButton,NULL);
		pMenu->setPosition(CCPointMake(720.0f,30.0f));
		addChild(pMenu,1);

		

		//const char *str = CCString::createWithFormat("%s%d%s",ConfigMgr::instance()->text("t452"),0,"%")->getCString();
		//pTTF = CCLabelTTF::create("","",18);
		//pTTF->setColor(ccc3(0,255,0));
		//pTTF->setAnchorPoint(ccp(0,0.5f));
		//pTTF->setPosition(CCPointMake(148.0f+pJinDuTiao0->getContentSize().width+20,48.0f));
		//addChild(pTTF,2);
		

		/**csmj**/
		 m_csmj_per = 0.0f;
		/**pdk**/
		 m_pdk_per=   0.0f;
		/**phz**/
		 m_phz_per=   0.0f;
		/**sdh**/
		 m_sdh_per=   0.0f;
		 
		 CCLOG("INIT OVER");
	return true;
}
void FreeCell::setCellIdx(int idx,bool isGet){
	m_choose = idx;
	m_nIsget = isGet;
	const char *pStr = CCString::createWithFormat("dt_free_1%d.png",m_choose)->getCString();
	pSprite->setDisplayFrame(spriteFrame(pStr));
	if(!m_nIsget)
	{
		pTextWaring->setString(ConfigMgr::instance()->text("t170"));
	}
	else
	{
		pTextWaring->setString(ConfigMgr::instance()->text("t459"));
	}

	bool bExit = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(m_choose == 0)
	{
		bExit = isGameExit(3);
	}
	else if(m_choose == 1)
	{
		bExit = isGameExit(6);
	}
	else if(m_choose == 2)
	{
		bExit = isGameExit(2);
	}
	else if(m_choose == 3)
	{
		bExit = isGameExit(5);
	}
#endif
	CCLOG("ALREADY GET GAMEINFO IN SET ID");
	switch(m_choose){
	case 0:
		{	
			pJinDuTiao->setPercentage(m_csmj_per);
			CCSprite *pNormalDownload;
			CCSprite *pSelectDownload;
			CCSprite* pDisDownload;
			if(bExit)
			{
				if(!m_nIsget)
				{
					pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
					pJinDuTiao->setSprite(pJinDuTiao1);
					pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
					pJinDuTiao->setVisible(false);
					pJinDuTiao0->setVisible(false);
				}
				else
				{
					pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
					pJinDuTiao->setSprite(pJinDuTiao1);
					pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
					pJinDuTiao->setVisible(false);
					pJinDuTiao0->setVisible(false);
				}
			}
			else
			{
				pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
				pJinDuTiao->setSprite(pJinDuTiao1);
				pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
				pJinDuTiao->setVisible(true);
				pJinDuTiao0->setVisible(true);
			}
			m_pMenuButton->setNormalImage(pNormalDownload);
			m_pMenuButton->setSelectedImage(pSelectDownload);
			m_pMenuButton->setDisabledImage(pDisDownload);
			pSelectDownload->setScale(0.9f);
			pSelectDownload->setAnchorPoint(ccp(-0.5/9,-0.5/9));
			m_titile->setString(ConfigMgr::instance()->text("t171"));	
			m_text->setString(ConfigMgr::instance()->text("t175"));	
 			//pTTF->setString(CCString::createWithFormat("%s%d%s",ConfigMgr::instance()->text("t452"),m_csmj_per,"%")->getCString());	
			break;
		}
	case 1:
		{
			CCSprite *pNormalDownload;
			CCSprite *pSelectDownload;
			CCSprite* pDisDownload;
			if(bExit)
			{
				if(!m_nIsget)
				{
					pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
					pJinDuTiao->setSprite(pJinDuTiao1);
					pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
					pJinDuTiao->setVisible(false);
					pJinDuTiao0->setVisible(false);
				}
				else
				{
					pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
					pJinDuTiao->setSprite(pJinDuTiao1);
					pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
					pJinDuTiao->setVisible(false);
					pJinDuTiao0->setVisible(false);
				}
			}
			else
			{
				pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
				pJinDuTiao->setSprite(pJinDuTiao1);
				pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
				pJinDuTiao->setVisible(true);
				pJinDuTiao0->setVisible(true);
			}
			m_pMenuButton->setNormalImage(pNormalDownload);
			m_pMenuButton->setSelectedImage(pSelectDownload);
			m_pMenuButton->setDisabledImage(pDisDownload);
			pSelectDownload->setScale(0.9f);
			pSelectDownload->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		    m_titile->setString(ConfigMgr::instance()->text("t174"));	
			m_text->setString(ConfigMgr::instance()->text("t178"));	
 		    //pTTF->setString(CCString::createWithFormat("%s%d%s",ConfigMgr::instance()->text("t452"),m_pdk_per,"%")->getCString());
		break;
		  }
	case 2:
		{
			CCSprite *pNormalDownload;
			CCSprite *pSelectDownload;
			CCSprite* pDisDownload;
			if(bExit)
			{
				if(!m_nIsget)
				{
					pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
					pJinDuTiao->setSprite(pJinDuTiao1);
					pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
					pJinDuTiao->setVisible(false);
					pJinDuTiao0->setVisible(false);
				}
				else
				{
					pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
					pJinDuTiao->setSprite(pJinDuTiao1);
					pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
					pJinDuTiao->setVisible(false);
					pJinDuTiao0->setVisible(false);
				}
			}
			else
			{
				pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
				pJinDuTiao->setSprite(pJinDuTiao1);
				pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
				pJinDuTiao->setVisible(true);
				pJinDuTiao0->setVisible(true);
			}
			m_pMenuButton->setNormalImage(pNormalDownload);
			m_pMenuButton->setSelectedImage(pSelectDownload);
			m_pMenuButton->setDisabledImage(pDisDownload);
			pSelectDownload->setScale(0.9f);
			pSelectDownload->setAnchorPoint(ccp(-0.5/9,-0.5/9));
			m_titile ->setString(ConfigMgr::instance()->text("t173"));	
			m_text->setString(ConfigMgr::instance()->text("t177"));	
 			//pTTF->setString(CCString::createWithFormat("%s%d%s",ConfigMgr::instance()->text("t452"),m_phz_per,"%")->getCString());
			break;
		}

	case 3:
		{
			CCSprite *pNormalDownload;
			CCSprite *pSelectDownload;
			CCSprite* pDisDownload;
			if(bExit)
			{
				if(!m_nIsget)
				{
					pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_lingqu.png"));
					pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
					pJinDuTiao->setSprite(pJinDuTiao1);
					pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
					pJinDuTiao->setVisible(false);
					pJinDuTiao0->setVisible(false);
				}
				else
				{
					pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_2.png"));
					pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
					pJinDuTiao->setSprite(pJinDuTiao1);
					pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
					pJinDuTiao->setVisible(false);
					pJinDuTiao0->setVisible(false);
				}
			}
			else
			{
				pNormalDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pSelectDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pDisDownload = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_0.png"));
				pJinDuTiao1->setDisplayFrame(spriteFrame("dt_free_15.png"));
					pJinDuTiao->setSprite(pJinDuTiao1);
				pJinDuTiao->setPercentage(pJinDuTiao->getPercentage());
				pJinDuTiao->setVisible(true);
				pJinDuTiao0->setVisible(true);
			}
			m_pMenuButton->setNormalImage(pNormalDownload);
			m_pMenuButton->setSelectedImage(pSelectDownload);
			m_pMenuButton->setDisabledImage(pDisDownload);
			pSelectDownload->setScale(0.9f);
			pSelectDownload->setAnchorPoint(ccp(-0.5/9,-0.5/9));
			m_titile ->setString(ConfigMgr::instance()->text("t172"));	
			m_text->setString(ConfigMgr::instance()->text("t176"));	
 			//pTTF->setString(CCString::createWithFormat("%s%d%s",ConfigMgr::instance()->text("t452"),m_sdh_per,"%")->getCString());
			break;
		}

	default:
		{
			break;
		}

	}
	CCLOG("SET OVER");

}
void FreeCell:: chooseFree(CCObject* obj)
{
	playButtonSound();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(EntityMgr::instance()->m_nDownLoadPe == -1)
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t458"),ccp(427,240));
		this->getParent()->addChild(layer,50);
		return;
	}
	if(m_choose == 2)
	{
		if(isGameExit(2))
		{
			if(!m_nIsget)
			{
				EntityMgr::instance()->getDispatch()->connectLoginServer();
				EntityMgr::instance()->getDispatch()->getDownLoadAward(SeverID_PHZ,1);
				m_pMenuButton->setEnabled(false);
			}
			else
			{
				CCLOG("have gameID = 2");
				openAndriodGame("2");
			}
		}
		else
		{
			downloadGame("2");
			CCLOG("not have gameID = 2 start download");
			m_pMenuButton->setEnabled(false);
			EntityMgr::instance()->m_nDownLoadPe = -1;
		}
		
	}
	else if(m_choose == 0)
	{
		if(isGameExit(3))
		{
			if(!m_nIsget)
			{
				EntityMgr::instance()->getDispatch()->connectLoginServer();
				EntityMgr::instance()->getDispatch()->getDownLoadAward(SeverID_CSMJ,1);
				m_pMenuButton->setEnabled(false);
			}
			else
			{
				CCLOG("have gameID = 3");
				openAndriodGame("3");
			}
		}
		else
		{
			downloadGame("3");
			CCLOG("not have gameID = 3 start download");
			m_pMenuButton->setEnabled(false);
			EntityMgr::instance()->m_nDownLoadPe = -1;
		}
	}
	else if(m_choose == 1)
	{
		if(isGameExit(6))
		{
			if(!m_nIsget)
			{
				EntityMgr::instance()->getDispatch()->connectLoginServer();
				EntityMgr::instance()->getDispatch()->getDownLoadAward(SeverID_PDK,1);
				m_pMenuButton->setEnabled(false);
			}
			else
			{
				CCLOG("have gameID = 6");
				openAndriodGame("6");
			}
		}
		else
		{
			downloadGame("6");
			CCLOG("not have gameID = 6start download");
			m_pMenuButton->setEnabled(false);
			EntityMgr::instance()->m_nDownLoadPe = -1;
		}
	}
	else if(m_choose == 3)
	{
		if(isGameExit(5))
		{
			if(!m_nIsget)
			{
				EntityMgr::instance()->getDispatch()->connectLoginServer();
				EntityMgr::instance()->getDispatch()->getDownLoadAward(SeverID_SDH,1);
				m_pMenuButton->setEnabled(false);
			}
			else
			{
				CCLOG("have gameID = 5");
				openAndriodGame("5");
			}
		}
		else
		{
			downloadGame("5");
			CCLOG("not have gameID = 5start download");
			m_pMenuButton->setEnabled(false);
			EntityMgr::instance()->m_nDownLoadPe = -1;
		}
	}
	
#endif
}
void FreeCell::setPesent(CCObject* obj)
{
	CCInteger* inter = (CCInteger*)obj;
	pJinDuTiao->runAction(CCProgressTo::create(1.0f,inter->getValue()));
}

void FreeCell::setMenuEnable(CCObject* obj)
{
	if(EntityMgr::instance()->m_nDownLoadPe == 1)
	{
		m_pMenuButton->setEnabled(true);
	}
	else
	{
		m_pMenuButton->setEnabled(false);
	}
}
