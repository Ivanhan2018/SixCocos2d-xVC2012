#include "ChoosePhotoCell.h"
#include "common/CocosUnits.h"
#include "configMgr/ConfigMgr.h"
#include "entity/EntityMgr.h"
#include "ChoosePhotoScrollLayer.h"
#include "ChoosePlayerPhotoLayer.h"
#include "PromptBox.h"
#include "PlayerInfoLayer.h"
#include "GroupSprite.h"
#include "MovingLabelLayer.h"
ChoosePhotoCell::ChoosePhotoCell(void){

}
ChoosePhotoCell::~ChoosePhotoCell(void){

}
ChoosePhotoCell* ChoosePhotoCell::PhotoCellWith(int type){
	ChoosePhotoCell* photoCell = new ChoosePhotoCell();
	if(photoCell)
	{
		photoCell->initPhotoCellWith(type);
		photoCell->autorelease();
		return photoCell;
	}
	CC_SAFE_DELETE(photoCell);
	return NULL;
}
bool ChoosePhotoCell::initPhotoCellWith(int type){
	    m_nType = type;
		winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *pNormalPlayerBG = CCSprite::createWithSpriteFrame(spriteFrame("dt_player_bj.png"));
		/*CCSprite *pSelectPlayerBG = CCSprite::createWithSpriteFrame(spriteFrame("dt_player_bj.png"));
		CCMenuItemSprite *pPlayerButtom = CCMenuItemSprite::create(pNormalPlayerBG,pSelectPlayerBG,this,menu_selector(ChoosePhotoCell::choosePhoto));
		CCMenu *pMenu = CCMenu::create(pPlayerButtom,NULL);*/
		pNormalPlayerBG->setPosition(CCPointMake(82.0f,77.0f));
		addChild(pNormalPlayerBG);

		const char *pStr;
		if(m_nType < 100)
		{
			if(m_nType >= 1)
			{
				pStr = CCString::createWithFormat("dt_player_1.png")->getCString();
			}
			else
			{
				/**Í¼ÏñÎªÅ®£¬±àÂëÎª0**/
				pStr = CCString::createWithFormat("dt_player_%d.png",m_nType)->getCString();
			}
		}
		else
		{
			if(m_nType >= 101)
			{
				pStr = CCString::createWithFormat("dt_player_101.png")->getCString();
			}
			else
			{
				/**Í¼ÏñÎªÄÐ£¬±àÂëÎª100**/
				pStr = CCString::createWithFormat("dt_player_%d.png",m_nType)->getCString();
			}
		}
		pPhotoBJ1 = CCSprite::createWithSpriteFrame(spriteFrame(pStr));
		
		pPhotoBJ1->setPosition(CCPointMake(82.0f,80.0f));
		addChild(pPhotoBJ1,2);	
        
	    CCSprite *pChooseKuang0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_playinfo_4.png"));
		CCSprite *pChooseKuang1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_playinfo_4.png"));
		CCMenuItemSprite *pChooseKuang=CCMenuItemSprite::create(pChooseKuang0,pChooseKuang1,this,menu_selector(ChoosePhotoCell::choosePhoto));
		pMenu = CCMenu::create(pChooseKuang,NULL);
		pMenu->setPosition(CCPointMake(82.0f+48.0f,25.0f));
		addChild(pMenu,2);

		pChoose = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_0.png"));
		pChoose->setPosition(CCPointMake(78.0f+48.0f,27.0f));
		pChoose->setVisible(false);
		addChild(pChoose,3);

		/*layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t29"),ccp(82.0f,80.0f));
		addChild(layer,10);*/

         if(type==0||type==100){
			pPhotoBJ1->setScale(0.5f);
			pMenu->setVisible(true);
		 }else{
          pMenu->setVisible(false);
		 }
	    return true;
}
void ChoosePhotoCell::setCellIdx(int idx){
	m_choose = idx;
	const char *pStr;
	if(m_choose < 100)
	{
		if(m_choose >= 1)
		{
			pStr = CCString::createWithFormat("dt_player_1.png")->getCString();
		}
		else
		{
			pStr = CCString::createWithFormat("dt_player_%d.png",m_choose)->getCString();
		}
	}
	else
	{
		if(m_choose >= 101)
		{
			pStr = CCString::createWithFormat("dt_player_101.png")->getCString();
		}
		else
		{
			pStr = CCString::createWithFormat("dt_player_%d.png",m_choose)->getCString();
		}
	}
	
	
	pPhotoBJ1->setDisplayFrame(spriteFrame(pStr));
	if(m_choose==0||m_choose==100){
		pPhotoBJ1->setScale(0.5f);
	}
	if(m_choose==0||m_choose==100){
		pPhotoBJ1->setScale(0.5f);	
		pMenu->setVisible(true);
	}else{
		pMenu->setVisible(false);
	}
	

}
void ChoosePhotoCell:: choosePhoto(CCObject* obj){
	playButtonSound();
	CCLog("m_choose==%d",m_choose);
	pChoose->setVisible(true);
	
	
	CCActionInterval * delaytime = CCDelayTime::create(0.2f);
	CCCallFunc * funcall= CCCallFunc::create(this, callfunc_selector(ChoosePhotoCell::callbackC));
	CCFiniteTimeAction *pAction = CCSequence::create(delaytime,funcall,NULL);
	this->runAction(pAction);


	

}
void ChoosePhotoCell::callbackC(){
	if(EntityMgr::instance()->getDispatch()->connectLoginServer())
	{
		int nhead;
		int nGente;
		if(m_choose >= 100)
		{
			nhead = m_choose - 100;
			nGente = 1;
		}
		else
		{
			nhead = m_choose;
			nGente = 2;
		}
		EntityMgr::instance()->getDispatch()->modifyTouxiang(nhead,nGente);
		CCInteger* pNickNameResult = CCInteger::create(nGente*10+nhead);
		CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_UPDATETOUXIANGNUM,pNickNameResult);

	}
	else
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_UPDATASEVERSHUT,NULL);
	}
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_UPDATETOUXIANGLAYER,NULL);

	//pLayer1->setVisible(false);
	
}
