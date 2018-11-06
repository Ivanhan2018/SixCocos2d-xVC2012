#include "SIX_PopWndShop.h"

const int BTN_POINT_CARD = 100;			// µã¿¨

SIX_PopWndShop::~SIX_PopWndShop(void)
{
	CC_SAFE_RELEASE(m_pPointCard);
}

SIX_PopWndShop *SIX_PopWndShop::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup/*=false*/)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_PopWndShop *pPopWnd = new SIX_PopWndShop();
	SIX_PopWndHaveListView::Create(pPopWnd, ccp(x,y), color, CCSize(width,height), bRedrawBorder, bCloseThenCleanup);
	
	pPopWnd->SetListViewCellSize(CCSize(width-c_smallWndBorderX*2-10, 73));
	pPopWnd->SetListViewRect(CCRect(c_smallWndBorderX+7, c_smallWndBorderY+10, width-c_smallWndBorderX*2-10, height-c_titleHeight-c_smallWndBorderY));
	return pPopWnd;
}

bool SIX_PopWndShop::init()
{
	if (!SIX_PopWndHaveListView::init())
		return false;

	m_bOpenPointCardWnd = false;
	m_pPointCard = NULL;
	SetTitlePath("shop_titleBG.png");
	return true;
}

void SIX_PopWndShop::onEnter()
{
	CCLayerColor::onEnter();

	m_pBtnPointCard = SIX_Utility::GetInstance()->CreateButtonWithFileCell("PointCardBT.png",2);
	if (m_pBtnPointCard)
	{
		m_pBtnPointCard->setDefaultTouchPriority(m_nPriority-1);
		m_pBtnPointCard->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndShop::doEvents),32);
		m_pBtnPointCard->setPosition(ccp(25,getContentSize().height-50));
		m_pBtnPointCard->setTag(BTN_POINT_CARD);
		addChild(m_pBtnPointCard);
	}
}

void SIX_PopWndShop::onHideFinished()
{
	if (m_bOpenPointCardWnd)
	{
		m_pPointCard->Show();
		m_bOpenPointCardWnd = false;
	}
}

void SIX_PopWndShop::setCellContent()
{
	if (0 == GetListView())
		return;

	GetListView()->RemoveCellAll();
	map<int, CMD_SC_Shop>::iterator mAward = m_mapShop.begin();
	for (int nIndex = 1; mAward != m_mapShop.end(); ++mAward, ++nIndex)
	{
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		GetListView()->AppendCell(pCell);
		CCSize cellSize = GetListView()->getContentSize();

		// Ïî±³¾°
		CCSprite *pItemBG = CCSprite::create("ItemBG.jpg");
		if (0 != pItemBG)
		{
			pItemBG->ignoreAnchorPointForPosition(true);
			pItemBG->setPosition(ccp(0,0));
			pCell->addChild(pItemBG);
		}
		// ½ð±Ò±êÖ¾
		CCSprite *pGoldSignBG = CCSprite::create("GoldSignBG.png");
		if (0 != pGoldSignBG  &&  0!=pItemBG)
		{
			pGoldSignBG->ignoreAnchorPointForPosition(true);
			pGoldSignBG->setPosition(ccp(10,(pItemBG->getContentSize().height-pGoldSignBG->getContentSize().height)/2));
			pCell->addChild(pGoldSignBG);
		}
		CCString *pstrGold = CCString::createWithFormat("GoldSign_%d.png",6>=nIndex?nIndex:6);
		CCSprite *pGoldSign = CCSprite::create(pstrGold->getCString());
		if (0 != pGoldSign  &&  0!=pItemBG)
		{
			pGoldSign->ignoreAnchorPointForPosition(true);
			pGoldSign->setPosition(ccp(10-7,(pItemBG->getContentSize().height-pGoldSign->getContentSize().height)/2));
			pCell->addChild(pGoldSign);
		}
		// ³ïÂë
		CCLabelTTF *pGold = CCLabelTTF::create();
		char cGold[128]="";
		sprintf(cGold, "%d ³ïÂë", mAward->second.nGold);
		pGold->setString(SIX_Utility::GetInstance()->G2U(cGold).c_str());
		pGold->setColor(ccc3(132,188,51));
		pGold->setFontSize(18.0f);
		pGold->setFontName("Î¢ÈíÑÅºÚ");
		pGold->setOpacity(255);
		pGold->ignoreAnchorPointForPosition(true);
		pGold->setPosition(ccp(pItemBG->getContentSize().width*0.156,(pItemBG->getContentSize().height-pGold->getContentSize().height)/2));
		SIX_Utility::GetInstance()->FixedTexParameters(pGold->getTexture(),true);
		pCell->addChild(pGold);
		//  ÈËÃñ±Ò
		CCLabelTTF *pRenminbi = CCLabelTTF::create();
		CCString *pStrRenminbi = CCString::createWithFormat("%d", mAward->second.nRenminbi);
		pRenminbi->setString(SIX_Utility::GetInstance()->G2U(pStrRenminbi->getCString()).c_str());
		pRenminbi->setColor(ccc3(254,247,0));
		pRenminbi->setFontSize(20.0f);
		pRenminbi->setFontName("Î¢ÈíÑÅºÚ");
		pRenminbi->ignoreAnchorPointForPosition(true);
		pRenminbi->setPosition(ccp(pItemBG->getContentSize().width*0.358,(pItemBG->getContentSize().height-pRenminbi->getContentSize().height)/2));
		SIX_Utility::GetInstance()->FixedTexParameters(pRenminbi->getTexture(),true);
		pCell->addChild(pRenminbi);
		// ±ÈÖµ
		CCLabelTTF *pRatio = CCLabelTTF::create();
		CCString *pStrRatio = CCString::createWithFormat("1Ôª=%d³ïÂë", mAward->second.nGold/mAward->second.nRenminbi);
		pRatio->setString(SIX_Utility::GetInstance()->G2U(pStrRatio->getCString()).c_str());
		pRatio->setColor(ccc3(255,255,255));
		pRatio->setFontSize(20.0f);
		pRatio->setFontName("Î¢ÈíÑÅºÚ");
		pRatio->ignoreAnchorPointForPosition(true);
		pRatio->setPosition(ccp(pItemBG->getContentSize().width*0.53,(pItemBG->getContentSize().height-pRatio->getContentSize().height)/2));
		SIX_Utility::GetInstance()->FixedTexParameters(pRatio->getTexture(),true);
		pCell->addChild(pRatio);
		// ¹ºÂò°´Å¥
		CCControlButton * pBuy = SIX_Utility::GetInstance()->CreateButtonWithFileCell("BuyBT.png", 2);
		if (0 == pBuy)
			return;
		pBuy->setTag(nIndex);
		pBuy->setObjName("BuyButton");
		pBuy->setZoomOnTouchDown(false);
		pBuy->setDefaultTouchPriority(m_nPriority-1);
		pBuy->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndShop::doEvents),32);
		pBuy->setPosition(ccp(cellSize.width-pBuy->getContentSize().width-30,(pItemBG->getContentSize().height-pBuy->getContentSize().height)/2-3));
		pCell->addChild(pBuy);
	}

	GetListView()->refresh();
}

void SIX_PopWndShop::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
			case BTN_POINT_CARD:
				{
					m_bOpenPointCardWnd = true;
					if (!m_pPointCard)
					{
						m_pPointCard = SIX_PopWndPointCard::Create(0.0f,0.0f,ccc4(0,0,0,0),623,423,50.0f,MOVABLE_TOP,MOVABLE_TOP,true);
						m_pPointCard->InitMask(ccc4(0,0,0,128));
						m_pPointCard->backgroundWithFile("box_bg.png");
						m_pPointCard->buttonSubmitWithFileCell("OKBTN.png",2);
						m_pPointCard->GetBtnSubmit()->setPosition(ccp(122,85));
						m_pPointCard->buttonCloseWithFileCell("btn_close.png",2);
						m_pPointCard->GetBtnClose()->setPosition(ccp(590,392));
						m_pPointCard->setAllowDragged(false);
						//m_pPointCard->setRectDirty();
					}
					Show(false);
					break;
				}
			default:
				SIXLog("SIX_SceneHall::doEvents Î´Öª°´Å¥ÊÂ¼þ,  tag=%d", tag);
				break;
			}
		}
	}
	return;
}

void SIX_PopWndShop::SetData(CMD_SC_Shop *& pShop)
{
	CMD_SC_Shop shop;
	memcpy(&shop, pShop, sizeof(shop));
	m_mapShop.insert(make_pair(shop.nID, shop));
}