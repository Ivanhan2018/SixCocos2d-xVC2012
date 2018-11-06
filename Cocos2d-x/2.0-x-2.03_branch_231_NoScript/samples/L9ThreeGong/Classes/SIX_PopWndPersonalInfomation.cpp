#include "SIX_PopWndPersonalInfomation.h"
#include "SIX_PlayerMgr.h"
#include "SIX_ClientLogin.h"

enum
{
	PI_ROOT_NODE = 1000,			// 个人信息根结点
	EHP_ROOT_NODE,					// 修改头像根结点
	IDA_ROOT_NODE,					// 身份认证根结点
	EP_ROOT_NODE,						// 修改密码根结点

	PERSONAL_INFO_BT,				// 标题栏按钮 - 个人信息按钮
	EDIT_HEAD_PICTURE_BT,		// 标题栏按钮 - 修改头像按钮
	ID_ATTEST_BT,							// 标题栏按钮 - 身份认证按钮
	EDIT_PW_BT,								// 标题栏按钮 - 修改密码按钮

	MY_PICTURE,							// 个人信息 - 个人的头像
	MY_PICTURE_FRAME,				// 个人信息 - 个人头像像框
	EDIT_NICKNAME,						// 个人信息 - 昵称ID
	EIDT_NICKNAME_BT,				// 个人信息 - 修改昵称按钮
	EDIT_NICKNAME_BG,				// 个人信息 - 昵称背景
	
	LIST_VIEW_ID,							// 修改头像 - 头像列表
	LIST_CELL_BG,							// 修改头像 - 头像列表项背景

	EDIT_REALNAME_ID,				// 身份认证 - 真实姓名
	EDIT_IDCARD_ID,						// 身份认证 - 身份证号码
	TIP_ID,										// 身份认证 - 提示控件
	SUBMIT_BUTTON_ID,				// 身份认证 - 提交按钮

	EDIT_PASS_OLD_ID,					// 修改密码 - 旧密码
	EDIT_PASS_NEW_ID,				// 修改密码 - 新密码
	EDIT_PASS_NEW_AGAIN,		// 修改密码 - 再输一次密码
	OK_BUTTON_ID,						// 修改密码 - 确认按钮
	MODIFY_PW_TIP,						// 修改密码 - 提示控件
};

const int C_LINECOUNT = 4;	// 每行多少个头像按钮

SIX_PopWndPersonalInfomation::~SIX_PopWndPersonalInfomation(void)
{
	//CC_SAFE_DELETE(m_pNickName);
}

SIX_PopWndPersonalInfomation *SIX_PopWndPersonalInfomation::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset/*=DEFAULT_SHAKEOFFSET*/,MOVABLE_TYPE showType/*=MOVABLE_LEFT*/,MOVABLE_TYPE hideType/*=MOVABLE_RIGHT*/,bool bSeqExec/*=true*/)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	CCSize szWind = CCDirector::sharedDirector()->getWinSize();
	if (0.0001 > x && 0.0001 > y)
	{
		x = (szWind.width - width) / 2;
		y = (szWind.height - height) / 2;
	}
	if (0.0001 > width  &&  0.0001 > height)
	{
		width = szWind.width;
		height = szWind.height;
	}

	SIX_PopWndPersonalInfomation *pPersonalInformation = new SIX_PopWndPersonalInfomation();
	if (pPersonalInformation && pPersonalInformation->init())
	{
		pPersonalInformation->initWithColor(color,width,height);
		pPersonalInformation->setPosition(x,y);
		pPersonalInformation->setRedrawBorder(false);
		pPersonalInformation->setTouchEnabled(true);
		pPersonalInformation->setAllowDragged(false);
		pPersonalInformation->m_ForbiddenTouch = true;
		pPersonalInformation->m_bCloseThenCleanup = false;
		pPersonalInformation->setShakeOffset(shakeOffset);
		pPersonalInformation->setShowType(showType);
		pPersonalInformation->setHideType(hideType);
		pPersonalInformation->setSeqExec(bSeqExec);
		pPersonalInformation->setObjName("SIX_PopWndPersonalInfomation");
		pPersonalInformation->backgroundWithFile("wndBG.jpg");
		pPersonalInformation->buttonCloseWithFileCell("wndReturn.png", 2);		
	}
	return pPersonalInformation;
}

bool SIX_PopWndPersonalInfomation::init()
{
	if (!SIX_EffectPopWnd::init())
		return false;

	m_pNickName = 0;
	InitMask(ccc4(0,0,0,128));

	// 默认头像初始化
	int iManMaxLogoID = 21;
	for (int iManMinLogoID=0; iManMinLogoID <=iManMaxLogoID; ++iManMinLogoID)
		m_vDefaultLogo.push_back(iManMinLogoID);
	int iWomanMaxLogoID = 10019;
	for (int iWomanMinLogoID=10000; iWomanMinLogoID <=iWomanMaxLogoID; ++iWomanMinLogoID)
		m_vDefaultLogo.push_back(iWomanMinLogoID);
	SIXLog("m_vDefaultLogo.size=%d",m_vDefaultLogo.size());

	m_iCurRootNode = -1;
	return true;
}

void SIX_PopWndPersonalInfomation::onEnterTransitionDidFinish()
{
	char cBuffer[128]="";
	CCSize sizeWnd = getContentSize();

	GetBtnClose()->setPosition(_ptRatio(5, getContentSize().height-GetBtnClose()->getContentSize().height-5));
	
	CCSprite * pTitleBG = CCSprite::create("wndTitleBG.png");
	if (pTitleBG)
	{
		pTitleBG->ignoreAnchorPointForPosition(true);
		pTitleBG->setPosition(ccp(0, sizeWnd.height-pTitleBG->getContentSize().height));
		addChild(pTitleBG);
		if (pTitleBG->getContentSize().width<sizeWnd.width)
		{
			CCSprite * pCramTitleBG = CCSprite::create("wndTitleBG.png");
			if (pCramTitleBG)
			{
				pCramTitleBG->ignoreAnchorPointForPosition(true);
				pCramTitleBG->setPositionX(pTitleBG->getPositionX()+pTitleBG->getContentSize().width);
				pTitleBG->addChild(pCramTitleBG);
			}
		}
	}

	CCSprite * pTitleName = CCSprite::create("data_titleBG.png");
	if (pTitleName && pTitleBG)
	{
		pTitleName->ignoreAnchorPointForPosition(true);
		pTitleName->setPosition(_ptRatio(95, pTitleBG->getPositionY()+(pTitleBG->getContentSize().height-pTitleName->getContentSize().height)/2+5));
		addChild(pTitleName);
	}

	char szButtonFile[][64]={"data_editPWBT.png", "data_idAttestBT.png", "data_editHeadPictureInfo.png", "data_personalInfoBT.png"};
	for (int i=0; i<sizeof(szButtonFile)/sizeof(szButtonFile[0]); i++)
	{
		CCControlButton * pPanelButton = SIX_Utility::GetInstance()->CreateButtonWithFileCell(szButtonFile[i], 2);
		if (pPanelButton)
		{
			pPanelButton->setZoomOnTouchDown(false);
			pPanelButton->setDefaultTouchPriority(m_nPriority-1);
			pPanelButton->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndPersonalInfomation::doEvents),32);
			pPanelButton->setPosition(_ptRatio(655-i*130,415));
			pPanelButton->setTag(EDIT_PW_BT-i);
			addChild(pPanelButton);
		}
	}
	
	// 个人头像
	m_llNoChangeLogoID = SIX_PlayerMgr::GetInstance()->getMyLogoID();
	CCString *pstrPicture = CCString::createWithFormat("face_%lld.jpg", SIX_PlayerMgr::GetInstance()->getMyLogoID());
	CCSprite *pPictureFrame = CCSprite::create("data_BigPicture.png");
	if (pPictureFrame)
	{
		pPictureFrame->ignoreAnchorPointForPosition(true);
		pPictureFrame->setContentSize(CCSize(130,130));
		pPictureFrame->setPosition(_ptRatio(68,244));
		pPictureFrame->setTag(MY_PICTURE_FRAME);
		addChild(pPictureFrame);
	}
	CCSprite *pPicture = CCSprite::create(pstrPicture->getCString());
	if (pPicture && pPictureFrame)
	{
		pPicture->ignoreAnchorPointForPosition(true);
		pPicture->setPosition(ccp(5, 5));
		pPicture->setTag(MY_PICTURE);
		pPictureFrame->addChild(pPicture);
	}

	m_iCurRootNode = PI_ROOT_NODE;
	changePanel(PERSIONAL_INFO);
}

bool SIX_PopWndPersonalInfomation::OnClose()
{
	if (m_llNoChangeLogoID!=SIX_PlayerMgr::GetInstance()->getMyLogoID()  ||  
		0!=STRCMP(m_pNickName->getTTF()->getString(), SIX_PlayerMgr::GetInstance()->getMyNickName()))
	{
		char szNickName[33]="";
		memcpy(szNickName, m_pNickName->getTTF()->getString(), sizeof(szNickName));
		SIX_PlayerMgr::GetInstance()->setMyNickName(szNickName);
		SIX_PlayerMgr::GetInstance()->setMyLogoID(m_llNoChangeLogoID);
		SIX_ClientLogin::GetInstance()->Connect(false);
	}

	setEditNickNameIME(false);
	return true;
}

void SIX_PopWndPersonalInfomation::OnTouchLogic(CCTouch *pTouch,int pEvent)
{
	SIX_EffectPopWnd::OnTouchLogic(pTouch,pEvent);

	SIX_EditBox *pEditRealName = 0;
	SIX_EditBox *pEditIDCard = 0;

	SIX_EditBox *pEditPassOld = 0;
	SIX_EditBox *pEditPassNew = 0;
	SIX_EditBox *pEditPassNewAga = 0;
	CCNode * pRoot = getRootNode();
	if ( pRoot )
	{
		pEditRealName = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_REALNAME_ID));
		pEditIDCard = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_IDCARD_ID));
		pEditPassOld = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_OLD_ID));
		pEditPassNew = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_NEW_ID));
		pEditPassNewAga = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_NEW_AGAIN));
	}

	switch (pEvent)
	{
	case CCTOUCHBEGAN:
		{
			if (PERSIONAL_INFO == m_curPanelType)
			{
				if (m_pNickName)
					m_pNickName->ccTouchBegan(pTouch,0);
			}
			else if (ID_ATTEST == m_curPanelType)
			{
				if ( !pEditRealName  ||  !pEditIDCard )
					return;
				pEditRealName->ccTouchBegan(pTouch, 0);
				pEditIDCard->ccTouchBegan(pTouch, 0);
			}
			else if (EDIT_PW == m_curPanelType)
			{
				if (!pEditPassOld  ||  !pEditPassNew  ||  !pEditPassNewAga)
					return;
				pEditPassOld->ccTouchBegan(pTouch, 0);
				pEditPassNew->ccTouchBegan(pTouch, 0);
				pEditPassNewAga->ccTouchBegan(pTouch, 0);
			}
			break;
		}
	case CCTOUCHMOVED:
		{
			if (PERSIONAL_INFO == m_curPanelType)
			{
				if (m_pNickName)
					m_pNickName->ccTouchMoved(pTouch,0);
			}
			else if (ID_ATTEST == m_curPanelType)
			{
				if ( !pEditRealName  ||  !pEditIDCard )
					return;
				pEditRealName->ccTouchMoved(pTouch, 0);
				pEditIDCard->ccTouchMoved(pTouch, 0);
			}
			else if (EDIT_PW == m_curPanelType)
			{
				if (!pEditPassOld  ||  !pEditPassNew  ||  !pEditPassNewAga)
					return;
				pEditPassOld->ccTouchMoved(pTouch, 0);
				pEditPassNew->ccTouchMoved(pTouch, 0);
				pEditPassNewAga->ccTouchMoved(pTouch, 0);
			}
			break;
		}
	case CCTOUCHENDED:
		{
			if (PERSIONAL_INFO == m_curPanelType)
			{
				if (m_pNickName)
				{
					m_pNickName->ccTouchEnded(pTouch,0);
					//tmp setEditNickNameIME(true);
				}
			}
			else if (ID_ATTEST == m_curPanelType)
			{
				if ( !pEditRealName  ||  !pEditIDCard )
					return;
				pEditRealName->ccTouchEnded(pTouch, 0);
				pEditIDCard->ccTouchEnded(pTouch, 0);
			}
			else if (EDIT_PW == m_curPanelType)
			{
				if (!pEditPassOld  ||  !pEditPassNew  ||  !pEditPassNewAga)
					return;
				pEditPassOld->ccTouchEnded(pTouch, 0);
				pEditPassNew->ccTouchEnded(pTouch, 0);
				pEditPassNewAga->ccTouchEnded(pTouch, 0);
			}
			break;
		}
	case CCTOUCHCANCELLED:
		{
			if (PERSIONAL_INFO == m_curPanelType)
			{
				if (m_pNickName)
					m_pNickName->ccTouchCancelled(pTouch,0);
			}
			else if (ID_ATTEST == m_curPanelType)
			{
				if ( !pEditRealName  ||  !pEditIDCard )
					return;
				pEditRealName->ccTouchCancelled(pTouch, 0);
				pEditIDCard->ccTouchCancelled(pTouch, 0);
			}
			else if (EDIT_PW == m_curPanelType)
			{
				if (!pEditPassOld  ||  !pEditPassNew  ||  !pEditPassNewAga)
					return;
				pEditPassOld->ccTouchCancelled(pTouch, 0);
				pEditPassNew->ccTouchCancelled(pTouch, 0);
				pEditPassNewAga->ccTouchCancelled(pTouch, 0);
			}
			break;
		}
	}
}

void SIX_PopWndPersonalInfomation::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
}

void SIX_PopWndPersonalInfomation::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();
	if (CCControlEventTouchUpInside != event)
		return;

	if (PERSONAL_INFO_BT <= tag  &&  EDIT_PW_BT >= tag)
	{
		panel_type panelType = PERSIONAL_INFO;
		if (PERSONAL_INFO_BT == tag)
			panelType = PERSIONAL_INFO;
		else if (EDIT_HEAD_PICTURE_BT == tag)
			panelType = EDIT_HEAD_PICTURE;
		else if (ID_ATTEST_BT == tag)
			panelType = ID_ATTEST;
		else if (EDIT_PW_BT == tag)
			panelType = EDIT_PW;

		setEditNickNameIME(false);
		changePanel(panelType);
		return;
	}

	switch ( tag )
	{
	case EIDT_NICKNAME_BT:
		{
			setEditNickNameIME(true);
			break;
		}
	case SUBMIT_BUTTON_ID:
		{
			if (ID_ATTEST == m_curPanelType)
				OnOkIDAttest();
			break;
		}
	case OK_BUTTON_ID:
		{
			if (EDIT_PW == m_curPanelType)
				OnOkModifyPW();
			break;
		}
	default:
		{
			vector<long long>::const_iterator vDefaultLogo = m_vDefaultLogo.begin();
			for (; vDefaultLogo != m_vDefaultLogo.end(); ++vDefaultLogo)
			{
				if (*vDefaultLogo==tag)
					break;
			}

			if (vDefaultLogo != m_vDefaultLogo.end())
			{
				CCSprite *pPictureFrame = dynamic_cast<CCSprite *>(getChildByTag(MY_PICTURE_FRAME));
				if (!pPictureFrame)
					return;
				CCSprite *pPicture = dynamic_cast<CCSprite *>(pPictureFrame->getChildByTag(MY_PICTURE));
				if (!pPicture)
					return;

				m_llNoChangeLogoID = tag;
				CCString *pstrPicture = CCString::createWithFormat("face_%d.jpg", tag);
				CCTexture2D * pTexture = CCTextureCache::sharedTextureCache()->addImage(pstrPicture->getCString());
				pPicture->setTexture(pTexture);
			}
		}
	}
	return;
}

void SIX_PopWndPersonalInfomation::CreateButtonWithFileCell(SIX_ControlButton ** pButton, const char *file,int cell,bool Hor/*=true*/)
{
	SIX_ControlButton *pBtn = 0;
	if (!file || cell<=1 || cell>=5)
		return;

	// 四态九宫格
	CCScale9Sprite *pScale9SpriteNor = 0;
	CCScale9Sprite *pScale9SpriteHov = 0;
	CCScale9Sprite *pScale9SpriteSel = 0;
	CCScale9Sprite *pScale9SpriteDis = 0;

	float cell_width = 0.0f;
	float cell_height = 0.0f;
	if (!SIX_Utility::GetInstance()->SplitSpriteWithCell(file,&pScale9SpriteNor,&pScale9SpriteHov,&pScale9SpriteSel,&pScale9SpriteDis,&cell_width,&cell_height,cell,Hor))
		return;

	// 必须要有常态，且长宽均不为零
	if (!pScale9SpriteNor || cell_width==0.0f || cell_height==0.0f)
		return;

	// 以常态创建按钮先~
	pBtn = SIX_ControlButton::create(pScale9SpriteNor);
	if (!pBtn)
		return;

	// 高亮
	if (pScale9SpriteHov)
		pBtn->setBackgroundSpriteForState(pScale9SpriteHov,CCControlStateHighlighted);
	// 选中
	if (pScale9SpriteSel)
		pBtn->setBackgroundSpriteForState(pScale9SpriteSel,CCControlStateSelected);
	// 禁用
	if (pScale9SpriteDis)
		pBtn->setBackgroundSpriteForState(pScale9SpriteDis,CCControlStateDisabled);

	pBtn->ignoreAnchorPointForPosition(true);
	pBtn->setZoomFactor(1.05f);
	pBtn->setPreferredSize(CCSize(cell_width,cell_height));
	*pButton = pBtn;
}

void SIX_PopWndPersonalInfomation::setEditNickNameIME(bool bAttach)
{
	if (PERSIONAL_INFO != m_curPanelType)
		return;

	if (m_pNickName)
	{
		if (bAttach)
			m_pNickName->attachWithIME();
		else
			m_pNickName->detachWithIME();
	}

	CCNode *pRoot = dynamic_cast<CCNode *>(getChildByTag(PI_ROOT_NODE));
	if ( !pRoot )
		return;
	CCSprite *pNickNameBG =dynamic_cast<CCSprite *>(pRoot->getChildByTag(EDIT_NICKNAME_BG));
	if (pNickNameBG)
	{
		pNickNameBG->setVisible(bAttach);
	}
}

void SIX_PopWndPersonalInfomation::setDetachEditBoxIME()
{
	CCNode * pRoot = getRootNode();
	if ( !pRoot )
		return;

	SIX_EditBox *pNickName = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_NICKNAME));
	if (pNickName)
		pNickName->detachWithIME();	

	SIX_EditBox *pEditRealName = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_REALNAME_ID));
	SIX_EditBox *pEditIDCard = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_IDCARD_ID));
	if (pEditRealName  &&  pEditIDCard)
	{
		pEditRealName->detachWithIME();
		pEditIDCard->detachWithIME();
	}

	SIX_EditBox *pEditPassOld = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_OLD_ID));
	SIX_EditBox *pEditPassNew = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_NEW_ID));
	SIX_EditBox *pEditPassNewAga = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_NEW_AGAIN));
	if (pEditPassOld  &&  pEditPassNew  &&  pEditPassNewAga)
	{
		pEditPassOld->detachWithIME();
		pEditPassNew->detachWithIME();
		pEditPassNewAga->detachWithIME();
	}
}

void SIX_PopWndPersonalInfomation::setTouch(int iTag)
{
	SIX_ListView *pListView = dynamic_cast<SIX_ListView *>(getChildByTag(LIST_VIEW_ID));
	if (pListView)
	{
		pListView->setTouchEnabled(EHP_ROOT_NODE==iTag ? true : false);
		pListView->setVisible(EHP_ROOT_NODE==iTag ? true : false);

		for (unsigned int iCell=0; iCell<pListView->GetCellCount(); ++iCell)
		{
			SIX_ListViewCell *pCell =pListView->GetCell(iCell);
			if ( !pCell )
				break;

			for (unsigned int iChild=0; iChild<pCell->getChildrenCount(); ++iChild)
			{
				CCSprite *pCellBG = dynamic_cast<CCSprite*>(pCell->getChildren()->objectAtIndex(iChild));
				if ( !pCellBG )
					break;
				SIX_ControlButton *pButton = dynamic_cast<SIX_ControlButton *>(pCellBG->getChildren()->objectAtIndex(0));
				if ( !pButton )
					break;
				pButton->setEnabled(EHP_ROOT_NODE==iTag ? true : false);
				pButton->setTouchEnabled(EHP_ROOT_NODE==iTag ? true : false);
			}			
		}
	}
	
	CCNode *pRoot = getRootNode(iTag);
	if ( !pRoot )
		return;

	CCControlButton * pEditNickNameBT = dynamic_cast<CCControlButton *>(pRoot->getChildByTag(EIDT_NICKNAME_BT));
	if (pEditNickNameBT)
	{
		pEditNickNameBT->setEnabled(PI_ROOT_NODE==iTag ? true : false);
		pEditNickNameBT->setTouchEnabled(PI_ROOT_NODE==iTag ? true : false);
	}

	CCControlButton * pSubmit = dynamic_cast<CCControlButton *>(pRoot->getChildByTag(SUBMIT_BUTTON_ID));
	if (pSubmit)
	{
		pSubmit->setEnabled(IDA_ROOT_NODE==iTag ? true : false);
		pSubmit->setTouchEnabled(IDA_ROOT_NODE==iTag ? true : false);
	}
}

void SIX_PopWndPersonalInfomation::showTips(const char *msg)
{
	int iTag = TIP_ID;
	if (ID_ATTEST == m_curPanelType)
		iTag = TIP_ID;
	else
		iTag = MODIFY_PW_TIP;

	CCNode *pRootNode = getRootNode();
	if ( !pRootNode )
		return;
	CCLabelTTF *pLabelTips = dynamic_cast<CCLabelTTF *>(pRootNode->getChildByTag(iTag));
	if ( !pLabelTips )
		return;

	pLabelTips->setString(SIX_Utility::GetInstance()->G2U(msg).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture(),true);
}

void SIX_PopWndPersonalInfomation::setFocus()
{
	if (PERSIONAL_INFO == m_curPanelType)
	{
		m_pNickName->attachWithIME();
	}
	else if (ID_ATTEST == m_curPanelType)
	{
		CCNode * pRoot = getRootNode();
		if ( !pRoot )
			return;

		SIX_EditBox *pEditRealName = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_REALNAME_ID));
		SIX_EditBox *pEditIDCard = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_IDCARD_ID));
		if (!pEditRealName  ||  !pEditIDCard)
			return;

		if (pEditRealName->IsAttachWithIME())
		{
			pEditRealName->detachWithIME();
			pEditIDCard->attachWithIME();
		}
		else
		{
			pEditRealName->attachWithIME();
			pEditIDCard->detachWithIME();
		}
	}
	else if (EDIT_PW == m_curPanelType)
	{
		CCNode *pRoot = getRootNode();
		if ( !pRoot )
			return;
		SIX_EditBox *pEditPassOld = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_OLD_ID));
		SIX_EditBox *pEditPassNew = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_NEW_ID));
		SIX_EditBox *pEditPassNewAga = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_NEW_AGAIN));
		if (!pEditPassOld  ||  !pEditPassNew  ||  !pEditPassNewAga)
			return;

		if (pEditPassOld->IsAttachWithIME())
		{
			pEditPassOld->detachWithIME();
			pEditPassNew->attachWithIME();
			pEditPassNewAga->detachWithIME();
		}
		else if (pEditPassNew->IsAttachWithIME())
		{
			pEditPassOld->detachWithIME();
			pEditPassNew->detachWithIME();
			pEditPassNewAga->attachWithIME();
		}
		else
		{
			pEditPassOld->attachWithIME();
			pEditPassNew->detachWithIME();
			pEditPassNewAga->detachWithIME();
		}
	}
}

void SIX_PopWndPersonalInfomation::setEnter()
{
	if (ID_ATTEST == m_curPanelType)
		OnOkIDAttest();
	else if (EDIT_PW == m_curPanelType)
		OnOkModifyPW();
}

void SIX_PopWndPersonalInfomation::OnOkIDAttest()
{
	if (ID_ATTEST != m_curPanelType)
		return;
	//this->DoLockPanel(true);
	CCNode *pRoot = getRootNode();
	if ( !pRoot )
		return;
	SIX_EditBox *pEditRealName = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_REALNAME_ID));
	SIX_EditBox *pEditIDCard = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_IDCARD_ID));
	if ( !pEditRealName  ||  !pEditIDCard )
		return;
	
	CCString *pRealName = 0;
	CCString *pIDCard = 0;
	char md5Dst[33] = {0};
	char md5NewDst[33] = {0};
	ERROR_INFO err = ERROR_NONE;

	do
	{
		pRealName = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditRealName->getTTF()->getString());
		// 真实姓名不能为空
		if (!pRealName->length())
		{
			this->showTips(/*真实姓名不能为空！*/XorStr<0xFC,19,0x172B6F11>("\x29\x1B\x34\x4A\xD0\xD4\xC1\xF8\xB6\xBE\xC2\xDB\xC6\xA3\xB5\xDE\xAF\xAC"+0x172B6F11).s);
			pEditRealName->attachWithIME();
			break;
		}

		pIDCard = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditIDCard->getTTF()->getString());
		// 身份证号码不能为空
		if (!pIDCard->length())
		{
			this->showTips(/*身份证号码不能为空！*/XorStr<0x3F,21,0x8311C732>("\xF6\xAD\xF6\x9F\x95\xE0\xFF\x83\x85\xA3\xFB\xF1\x8F\x90\x83\xE4\xF0\x85\xF2\xF3"+0x8311C732).s);
			pEditIDCard->attachWithIME();
			break;
		}

		// 正常流程开始
		this->showTips(/*正在验证防沉迷信息 ...*/XorStr<0x78,23,0x7D439EF8>("\xAD\x84\xAE\xA1\xAD\x94\xA8\xDB\x37\x41\x31\x42\x47\x51\x56\x42\x47\x2B\xAA\xA5\xA2\xA3"+0x7D439EF8).s);
		pEditRealName->detachWithIME();
		pEditIDCard->detachWithIME();

		SIXLog("pRealName[%s].pIDCard[%s]",pRealName->getCString(),pIDCard->getCString());

		//// 连接服务器，提交修改密码请求
		//SIX_ClientLogin::GetInstance()->Connect(false);
		return;
	}while (0);

	//this->DoLockPanel(false);
	return;
}

void SIX_PopWndPersonalInfomation::OnOkModifyPW()
{
	if (EDIT_PW != m_curPanelType)
		return;

	CCString *pPassOld = 0;
	CCString *pPassNew = 0;
	CCString *pPassNewAgain = 0;
	char md5Dst[33] = {0};
	char md5NewDst[33] = {0};
	ERROR_INFO err = ERROR_NONE;

	CCNode *pRoot = getRootNode();
	if ( !pRoot )
		return;
	SIX_EditBox *pEditPassOld = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_OLD_ID));
	SIX_EditBox *pEditPassNew = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_NEW_ID));
	SIX_EditBox *pEditPassNewAgain = dynamic_cast<SIX_EditBox *>(pRoot->getChildByTag(EDIT_PASS_NEW_AGAIN));
	if (!pEditPassOld  ||  !pEditPassNew  ||  !pEditPassNewAgain)
		return;

	do
	{
		pPassOld = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditPassOld->getTTF()->getString());
		if (!pPassOld->length())
		{
			this->showTips(/*原密码不能为空！*/XorStr<0x42,17,0x991412F8>("\x96\xEE\x87\x99\x84\xAC\xFA\xF2\x8E\x97\x82\xE7\xF1\x9A\xF3\xF0"+0x991412F8).s);
			pEditPassOld->attachWithIME();
			break;
		}

		pPassNew = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditPassNew->getTTF()->getString());
		if (!pPassNew->length())
		{
			this->showTips(/*新密码不能为空！*/XorStr<0xEC,17,0x582928CB>("\x3C\x2F\x2D\x33\x32\x1A\x40\x48\x30\x29\x38\x5D\x47\x2C\x59\x5A"+0x582928CB).s);
			pEditPassNew->attachWithIME();
			break;
		}
		pPassNewAgain = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditPassNewAgain->getTTF()->getString());
		if (!pPassNewAgain->length())
		{
			this->showTips(/*新密码不能为空！*/XorStr<0xEC,17,0x582928CB>("\x3C\x2F\x2D\x33\x32\x1A\x40\x48\x30\x29\x38\x5D\x47\x2C\x59\x5A"+0x582928CB).s);
			pEditPassNewAgain->attachWithIME();
			break;
		}
		if (0 != STRCMP(pPassNew->getCString(), pPassNewAgain->getCString()))
		{
			this->showTips(/*两次输入的密码不一致！*/XorStr<0x44,23,0xD9A220C9>("\x85\xF8\xF2\x89\x82\xAD\x82\xA0\xF9\x89\x8D\x93\x92\xBA\xE0\xE8\x86\xEE\x80\x95\xFB\xF8"+0xD9A220C9).s);
			pEditPassNewAgain->attachWithIME();
			break;
		}

		// 正常流程开始
		this->showTips(/*正在修改密码 ...*/XorStr<0x28,17,0x98C5B6A7>("\xFD\xD4\xFE\xF1\xFC\xF3\x96\xEB\xF3\xED\xF0\xD8\x14\x1B\x18\x19"+0x98C5B6A7).s);
		pEditPassOld->detachWithIME();
		pEditPassNew->detachWithIME();
		pEditPassNewAgain->detachWithIME();

		err = SIX_GlobalMgr::GetInstance()->GetFS()->GetMicroEncryptAndDecrypt()->HashByMD5((char*)(pPassOld->getCString()),pPassOld->length(),md5Dst,false);
		if (err!=ERROR_NONE)
		{
			SIXLog("pPassOld[%s].md5Dst[%s]",pPassOld->getCString(),md5Dst);
			this->showTips(/*原密码异常！*/XorStr<0xDA,13,0x0487AF10>("\x0E\x76\x1F\x01\x1C\x34\x32\x0D\x51\x40\x47\x44"+0x0487AF10).s);
			break;
		}

		err = SIX_GlobalMgr::GetInstance()->GetFS()->GetMicroEncryptAndDecrypt()->HashByMD5((char*)(pPassNew->getCString()),pPassNew->length(),md5NewDst,false);
		if (err!=ERROR_NONE)
		{
			SIXLog("pPassNew[%s].md5NewDst[%s]",pPassNew->getCString(),md5NewDst);
			this->showTips(/*新密码异常！*/XorStr<0x70,13,0xE9B32512>("\xA0\xB3\xB1\xAF\xB6\x9E\xA4\x9B\xCB\xDA\xD9\xDA"+0xE9B32512).s);
			break;
		}
	}while (0);

	SIXLog("pPassOld[%s].pPassNew[%s]",pPassOld,pPassNew);
}

void SIX_PopWndPersonalInfomation::changePanel(panel_type pType)
{
	m_curPanelType = pType;
	switch (pType)
	{
	case PERSIONAL_INFO: setPersonalInfoPanel(); break;
	case EDIT_HEAD_PICTURE: setEditHeadPicturePanel(); break;
	case ID_ATTEST: setIDAttestPanel(); break;
	case EDIT_PW: setModifyPW(); break;
	}
}

bool SIX_PopWndPersonalInfomation::setRootNode(int iTag, CCNode *&pNode)
{
	// 隐藏之前的面板
	CCNode *pLastRoot = getChildByTag(m_iCurRootNode);
	if ( pLastRoot )
	{
		pLastRoot->setVisible(false);
		// 显示个人头像（修改头像，个人信息共用）
		CCSprite *pPictureFrame = dynamic_cast<CCSprite*>(getChildByTag(MY_PICTURE_FRAME));
		if (pPictureFrame)
		{
			if (PI_ROOT_NODE==iTag  ||  EHP_ROOT_NODE==iTag)
				pPictureFrame->setVisible(true);
			else
				pPictureFrame->setVisible(false);
		}
	}
	// 头像列表Touch处理
	setTouch(iTag);
	// 取消息编辑框输入
	setDetachEditBoxIME();
	// 更新最新的面板
	m_iCurRootNode = iTag;
	CCNode *pNewRoot = dynamic_cast<CCNode *>(getChildByTag(iTag));
	if ( pNewRoot )
	{
		pNewRoot->setVisible(true);
		return false;
	}

	pNewRoot = CCNode::create();
	pNewRoot->setTag(iTag);
	addChild(pNewRoot);
	pNode = pNewRoot;
	return true;
}

CCNode * SIX_PopWndPersonalInfomation::getRootNode(int iTag/*=-1*/)
{
	if (-1 == m_iCurRootNode)
		return 0;
	else if (-1==iTag)
		return getChildByTag(m_iCurRootNode);

	return getChildByTag(iTag);
}

void SIX_PopWndPersonalInfomation::setPersonalInfoPanel()
{
	CCNode *pNode = 0;
	bool bCreate = setRootNode(PI_ROOT_NODE, pNode);
	if ( !bCreate || !pNode )
		return;

	// 用户名输入框
	CCSprite *pNickNameBG = CCSprite::create("data_editBG.png");
	if (pNickNameBG)
	{
		pNickNameBG->ignoreAnchorPointForPosition(true);
		pNickNameBG->setPosition(_ptRatio(245, 335));
		pNickNameBG->setVisible(false);
		pNickNameBG->setTag(EDIT_NICKNAME_BG);
		pNode->addChild(pNickNameBG);
	}
	m_pNickName = new SIX_EditBox();
	m_pNickName->setPosition(_ptRatio(245, 335));
	m_pNickName->setInputTextMaxCount(33);
	m_pNickName->setContentSize(CCSize(186,40));
	m_pNickName->getTTF()->setPosition(ccp(5,10));
	m_pNickName->getTTF()->setFontSize(20);
	m_pNickName->getTTF()->setString(SIX_PlayerMgr::GetInstance()->getMyNickName());
	m_pNickName->getTTF()->setScissorSize(CCSize(176,40));
	m_pNickName->getTTF()->setColor(ccc3(255,255,255));
	m_pNickName->InitCursor(0xFF,1,20);
	m_pNickName->setTag(EDIT_NICKNAME);
	pNode->addChild(m_pNickName);
	CCControlButton * pEditNickNameBT = SIX_Utility::GetInstance()->CreateButtonWithFile("data_EditNickNameBT.png", CCRect(0.0f, 0.0f, 37.0f, 36.0f));
	if (pEditNickNameBT)
	{
		pEditNickNameBT->setZoomOnTouchDown(true);
		pEditNickNameBT->setDefaultTouchPriority(m_nPriority-1);
		pEditNickNameBT->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndPersonalInfomation::doEvents),32);
		pEditNickNameBT->setPosition(_ptRatio(440,335));
		pEditNickNameBT->setTag(EIDT_NICKNAME_BT);
		pNode->addChild(pEditNickNameBT);
	}
	CCString *pStrID = CCString::createWithFormat(/*Id：%lld*/XorStr<0x13,9,0xE02F8D47>("\x5A\x70\xB6\xAC\x32\x74\x75\x7E"+0xE02F8D47).s, SIX_PlayerMgr::GetInstance()->getMyUserIdx());
	CCLabelTTF *pIDTxt = CCLabelTTF::create();
	pIDTxt->setString(SIX_Utility::GetInstance()->G2U(pStrID->getCString()).c_str());
	pIDTxt->setColor(ccc3(255,255,255));
	pIDTxt->setFontSize(18.0f);
	pIDTxt->setFontName(/*微软雅黑*/XorStr<0x8A,9,0x9B502C96>("\x44\x29\x44\x60\x5F\x4A\x2A\x4B"+0x9B502C96).s);
	pIDTxt->setOpacity(255);
	pIDTxt->ignoreAnchorPointForPosition(true);
	pIDTxt->setPosition(ccp(515,335));
	SIX_Utility::GetInstance()->FixedTexParameters(pIDTxt->getTexture(),true);
	pNode->addChild(pIDTxt);

	// 等级称呼
	CCSprite *plv = CCSprite::create("data_lv1.png");//tmp
	if (plv)
	{
		plv->ignoreAnchorPointForPosition(true);
		plv->setPosition(_ptRatio(245, 275));
		pNode->addChild(plv);
	}
	CCLabelTTF *plvTxt = CCLabelTTF::create();
	CCString *pStrLV = CCString::create(/*1星子爵*/XorStr<0x8C,8,0x7AEEC9C7>("\xBD\x5D\x49\x58\x43\x2F\x66"+0x7AEEC9C7).s);//tmp
	plvTxt->setString(SIX_Utility::GetInstance()->G2U(pStrLV->getCString()).c_str());
	plvTxt->setColor(ccc3(255,255,0));
	plvTxt->setFontSize(18.0f);
	plvTxt->setFontName(/*微软雅黑*/XorStr<0x93,9,0x8B7B4E5F>("\x5D\x36\x5D\x7B\x46\x5D\x23\x40"+0x8B7B4E5F).s);
	plvTxt->setOpacity(255);
	plvTxt->ignoreAnchorPointForPosition(true);
	plvTxt->setPosition(_ptRatio(285, 278));
	SIX_Utility::GetInstance()->FixedTexParameters(plvTxt->getTexture(),true);
	pNode->addChild(plvTxt);

	// 金砖
	CCSprite *pBullion = CCSprite::create("bullion.png");//tmp
	if (pBullion)
	{
		pBullion->ignoreAnchorPointForPosition(true);
		pBullion->setPosition(ccp(382, 270));
		pNode->addChild(pBullion);
	}
	CCLabelTTF *pBullionTxt = CCLabelTTF::create();
	CCString *pStrBullion = CCString::create("0");//tmp
	pBullionTxt->setString(SIX_Utility::GetInstance()->G2U(pStrBullion->getCString()).c_str());
	pBullionTxt->setColor(ccc3(255,255,0));
	pBullionTxt->setFontSize(18.0f);
	pBullionTxt->setFontName(/*微软雅黑*/XorStr<0x93,9,0x8B7B4E5F>("\x5D\x36\x5D\x7B\x46\x5D\x23\x40"+0x8B7B4E5F).s);
	pBullionTxt->setOpacity(255);
	pBullionTxt->ignoreAnchorPointForPosition(true);
	pBullionTxt->setPosition(ccp(440,278));
	SIX_Utility::GetInstance()->FixedTexParameters(pBullionTxt->getTexture(),true);
	pNode->addChild(pBullionTxt);
	// 筹码
	CCSprite *pChipSign = CCSprite::create("hall_ico_chip.png");
	if (pChipSign)
	{
		pChipSign->ignoreAnchorPointForPosition(true);
		pChipSign->setPosition(_ptRatio(510, 270));
		pNode->addChild(pChipSign);
	}
	CCLabelTTF *pChipTxt = CCLabelTTF::create();
	CCString *pStrChip = CCString::createWithFormat(/*%lld*/XorStr<0x43,5,0x4179A849>("\x66\x28\x29\x22"+0x4179A849).s, SIX_PlayerMgr::GetInstance()->getMyChip());
	pChipTxt->setString(SIX_Utility::GetInstance()->G2U(pStrChip->getCString()).c_str());
	pChipTxt->setColor(ccc3(255,255,0));
	pChipTxt->setFontSize(18.0f);
	pChipTxt->setFontName(/*微软雅黑*/XorStr<0x93,9,0x8B7B4E5F>("\x5D\x36\x5D\x7B\x46\x5D\x23\x40"+0x8B7B4E5F).s);
	pChipTxt->setOpacity(255);
	pChipTxt->ignoreAnchorPointForPosition(true);
	pChipTxt->setPosition(_ptRatio(550,278));
	SIX_Utility::GetInstance()->FixedTexParameters(pChipTxt->getTexture(),true);
	pNode->addChild(pChipTxt);

	// 升级进度
	CCLabelTTF *pLvNumberTxt = CCLabelTTF::create();
	if (pLvNumberTxt)
	{
		CCString *pStrLvNumber = CCString::createWithFormat(/*LV 0*/XorStr<0xCA,5,0x483DBF07>("\x86\x9D\xEC\xFD"+0x483DBF07).s);//tmp
		pLvNumberTxt->setString(SIX_Utility::GetInstance()->G2U(pStrLvNumber->getCString()).c_str());
		pLvNumberTxt->setColor(ccc3(255,255,255));
		pLvNumberTxt->setFontSize(18.0f);
		pLvNumberTxt->setFontName(/*微软雅黑*/XorStr<0x93,9,0x8B7B4E5F>("\x5D\x36\x5D\x7B\x46\x5D\x23\x40"+0x8B7B4E5F).s);
		pLvNumberTxt->setOpacity(255);
		pLvNumberTxt->ignoreAnchorPointForPosition(true);
		pLvNumberTxt->setPosition(_ptRatio(245,220));
		SIX_Utility::GetInstance()->FixedTexParameters(pLvNumberTxt->getTexture(),true);
		pNode->addChild(pLvNumberTxt);
	}
	CCSprite *pProgressBG = CCSprite::create("lv_progress_bg.png");
	if (pProgressBG)
	{
		pProgressBG->ignoreAnchorPointForPosition(true);
		pProgressBG->setPosition(_ptRatio(305, 220));
		pNode->addChild(pProgressBG);
	}
	CCSprite *pProgressSprite = CCSprite::create("lv_progress.png");
	CCProgressTimer *pProgress = CCProgressTimer::create(pProgressSprite);
	if (pProgress)
	{
		pProgress->setAnchorPoint(ccp(0,0));
		pProgress->setMidpoint(ccp(0,0));
		pProgress->setBarChangeRate(ccp(1,0));
		pProgress->setType(kCCProgressTimerTypeBar);
		pProgress->setPosition(_ptRatio(305, 220));
		pProgress->setPercentage(10.0f);//tmp
		pNode->addChild(pProgress);
	}

	// 经验
	CCLabelTTF *pExperience = CCLabelTTF::create();
	CCString *pStrExperience = CCString::createWithFormat(/*总经验：%d， 升级需：%d*/XorStr<0xAA,24,0xCA9082D3>("\x7D\x77\x12\x00\x7F\x46\x13\x0B\x97\xD7\x17\x19\x96\x7E\x45\x05\x0C\x6B\x54\x1E\x04\x9A\xA4"+0xCA9082D3).s, 0, 1000);//tmp
	pExperience->setString(SIX_Utility::GetInstance()->G2U(pStrExperience->getCString()).c_str());
	pExperience->setColor(ccc3(255,255,255));
	pExperience->setFontSize(18.0f);
	pExperience->setFontName(/*微软雅黑*/XorStr<0xF8,9,0x3BE18FD4>("\x36\x5B\x32\x16\x2D\x38\x44\x25"+0x3BE18FD4).s);
	pExperience->setOpacity(255);
	pExperience->ignoreAnchorPointForPosition(true);
	pExperience->setPosition(_ptRatio(245,185));
	SIX_Utility::GetInstance()->FixedTexParameters(pExperience->getTexture(),true);
	pNode->addChild(pExperience);

	// 已赢牌局
	CCLabelTTF *pWinCount = CCLabelTTF::create();
	CCString *pStrWinCount = CCString::createWithFormat(/*已赢牌局：%d*/XorStr<0x8B,13,0x81414EAC>("\x59\x5D\x5E\x20\x4A\x56\x2F\x44\x30\x2E\xB0\xF2"+0x81414EAC).s, 0);//tmp
	pWinCount->setString(SIX_Utility::GetInstance()->G2U(pStrWinCount->getCString()).c_str());
	pWinCount->setColor(ccc3(255,255,255));
	pWinCount->setFontSize(18.0f);
	pWinCount->setFontName(/*微软雅黑*/XorStr<0xF8,9,0x3BE18FD4>("\x36\x5B\x32\x16\x2D\x38\x44\x25"+0x3BE18FD4).s);
	pWinCount->setOpacity(255);
	pWinCount->ignoreAnchorPointForPosition(true);
	pWinCount->setPosition(_ptRatio(245,125));
	SIX_Utility::GetInstance()->FixedTexParameters(pWinCount->getTexture(),true);
	pNode->addChild(pWinCount);

	// 经验
	CCLabelTTF *pTotalCount = CCLabelTTF::create();
	CCString *pStrTotalCount = CCString::createWithFormat(/*已玩牌局：%d*/XorStr<0xB3,13,0x2B4EB3C9>("\x61\x65\x78\x50\x72\x7E\x07\x6C\x18\x06\x98\xDA"+0x2B4EB3C9).s, 0);//tmp
	pTotalCount->setString(SIX_Utility::GetInstance()->G2U(pStrTotalCount->getCString()).c_str());
	pTotalCount->setColor(ccc3(255,255,255));
	pTotalCount->setFontSize(18.0f);
	pTotalCount->setFontName(/*微软雅黑*/XorStr<0xF8,9,0x3BE18FD4>("\x36\x5B\x32\x16\x2D\x38\x44\x25"+0x3BE18FD4).s);
	pTotalCount->setOpacity(255);
	pTotalCount->ignoreAnchorPointForPosition(true);
	pTotalCount->setPosition(_ptRatio(245,95));
	SIX_Utility::GetInstance()->FixedTexParameters(pTotalCount->getTexture(),true);
	pNode->addChild(pTotalCount);
}

void SIX_PopWndPersonalInfomation::setEditHeadPicturePanel()
{
	SIX_ListView *pGetListView = dynamic_cast<SIX_ListView *>(getChildByTag(LIST_VIEW_ID));
	if (pGetListView)
	{
		pGetListView->setVisible(true);
	}

	CCNode *pNode = 0;
	bool bCreate = setRootNode(EHP_ROOT_NODE, pNode);
	if ( !bCreate || !pNode )
		return;

	CCSprite *pListBG = CCSprite::create("data_listviewBG.png");
	if (pListBG)
	{
		pListBG->ignoreAnchorPointForPosition(true);
		pListBG->setPosition(_ptRatio(225, 0));
		pNode->addChild(pListBG);
	}

	// 头像列表
	CCRect listViewRect = CCRect(pListBG->getPositionX(), pListBG->getPositionY()+15, pListBG->getContentSize().width, 360);
	CCSize listViewCell = CCSize(pListBG->getContentSize().width,100);
	SIX_UILayer *pContainer = SIX_UILayer::create(ccc4(0,0,0,0));
	pContainer->setContentSize(CCSize(listViewRect.size.width, listViewRect.size.height));
	pContainer->setPosition(ccp(listViewRect.getMinX(), listViewRect.getMinY()));
	
	SIX_ListView *pListView = SIX_ListView::create(ccc4(0,0,0,0),
		ccp(listViewRect.getMinX(),listViewRect.getMinY()),
		CCSize(listViewRect.size.width, listViewRect.size.height),
		CCSize(listViewCell.width, listViewCell.height),
		kCCScrollViewDirectionVertical,
		pContainer,
		0
		);
	pListView->setObjName("ListView");
	pListView->setTag(LIST_VIEW_ID);
	pListView->setTouchEnabled(true);	
	pListView->getTableView()->setClippingToBounds(true);
	pListView->getTableView()->setDirection(kCCScrollViewDirectionVertical);
	pListView->getTableView()->setVerticalFillOrder(kCCTableViewFillTopDown);
	pListView->getTableView()->setBounceable(true);
	pListView->getTableView()->setDelegate(this);
	addChild(pListView);

	int iOffsetX = 0, iCount = 0;
	SIX_ListViewCell *pChildCell = NULL;
	SIX_ListView *pChildListView = NULL;
	int iTag = 0;
	
	for (int j=0; j<m_vDefaultLogo.size(); ++j)
	{
		if (0==iCount%C_LINECOUNT)
		{
			iTag = 0;
			pChildCell = new SIX_ListViewCell();
			pListView->AppendCell(pChildCell);
		}

		CCString *pstrPicture = CCString::createWithFormat("face_%lld.jpg", m_vDefaultLogo.at(j));
		CCTexture2D *pLogo = CCTextureCache::sharedTextureCache()->addImage(pstrPicture->getCString());
		CCSprite *pPicture = CCSprite::create("face_medium.jpg");
		iOffsetX = iCount%C_LINECOUNT;
		iCount++;

		if (pPicture)
		{
			pPicture->setTexture(pLogo);
			pPicture->ignoreAnchorPointForPosition(true);
			pPicture->setPositionX(iOffsetX*(pPicture->getContentSize().width+10.0f)+80.0f);
			pPicture->setPositionY(10.0f);
			pPicture->setTag(LIST_CELL_BG+iTag);
			pChildCell->addChild(pPicture);
		}

		SIX_ControlButton * pButton = 0;
		CreateButtonWithFileCell(&pButton, "SmallPictureBT.png", 2);
		if (pButton)
		{
			pButton->setDefaultTouchPriority(m_nPriority);
			pButton->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndPersonalInfomation::doEvents),32);
			pButton->ignoreAnchorPointForPosition(true);
			pButton->setPosition(ccp(-3,-4));
			pButton->setTag(m_vDefaultLogo.at(j));
			pButton->setObjName("listvew_cell_button");
			pPicture->addChild(pButton);
		}
	}
}

void SIX_PopWndPersonalInfomation::setIDAttestPanel()
{
	CCNode *pNode = 0;
	bool bCreate = setRootNode(IDA_ROOT_NODE, pNode);
	if ( !bCreate || !pNode )
		return;
	
	// 输入框背景
	CCSprite *pSprEdit = CCSprite::create("edit.png");
	if (pSprEdit)
	{
		pSprEdit->ignoreAnchorPointForPosition(true);
		pSprEdit->setPosition(_ptRatio(205,190));
		pNode->addChild(pSprEdit);
	}
	// 文字提示
	CCLabelTTF *pLabelTitle = CCLabelTTF::create();
	pLabelTitle->setString(SIX_Utility::GetInstance()->G2U(/*完成身份认证后，可方便你找回密码*/XorStr<0xFE,33,0x021EC594>("\x33\x15\xB3\xC8\xCB\xEE\xB3\xD8\xCE\xC8\xDE\xAD\xB0\xF8\xAF\xA1\xB1\xC6\xA7\xAC\xA3\xF0\xD0\xF6\xC3\xC5\xA3\xC1\xD9\xC7\xDE\xF6"+0x021EC594).s).c_str());
	pLabelTitle->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelTitle->setFontSize(18.0f);
	pLabelTitle->setColor(ccc3(255,255,255));
	pLabelTitle->setOpacity(255);
	pLabelTitle->ignoreAnchorPointForPosition(true);
	pLabelTitle->setPosition(_ptRatio((getContentSize().width-pLabelTitle->getContentSize().width)/2,345));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTitle->getTexture(),true);
	pNode->addChild(pLabelTitle);
	CCSprite *pLight = CCSprite::create("lamp.png");
	if (pLight)
	{
		pLight->ignoreAnchorPointForPosition(true);
		pLight->setPosition(_ptRatio(pLabelTitle->getPositionX()-pLight->getContentSize().width-5,335));
		pNode->addChild(pLight);
	}

	// 真实姓名输入框
	SIX_EditBox *pEditRealName = new SIX_EditBox();
	pEditRealName->setPosition(_ptRatio(215,260));
	pEditRealName->setInputTextMaxCount(18);
	pEditRealName->setContentSize(CCSize(360,60));
	pEditRealName->getTTF()->setPosition(ccp(5,10));
	pEditRealName->getTTF()->setFontSize(16);
	pEditRealName->getTTF()->setScissorSize(CCSize(350,60));
	pEditRealName->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*真实姓名*/XorStr<0x70,9,0xBC75247B>("\xA5\x97\xB8\xC6\xA4\xA0\xB5\x8C"+0xBC75247B).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditRealName->getTTF()->getTexture(),true);
	pEditRealName->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	pEditRealName->getTTF()->setColor(ccc3(0,0,0));
	pEditRealName->InitCursor(0xFF,1,16);
	pEditRealName->setTag(EDIT_REALNAME_ID);
	pNode->addChild(pEditRealName);

	// 身份证号码输入框
	SIX_EditBox *pEditIDCard = new SIX_EditBox();
	pEditIDCard->setPosition(_ptRatio(215,200));
	pEditIDCard->setInputTextMaxCount(33);
	pEditIDCard->setContentSize(CCSize(360,60));
	pEditIDCard->getTTF()->setPosition(ccp(5,10));
	pEditIDCard->getTTF()->setFontSize(16);
	pEditIDCard->getTTF()->setScissorSize(CCSize(350,60));
	pEditIDCard->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*身份证号码*/XorStr<0x8D,11,0xA8B0FF94>("\x44\x63\x38\x4D\x47\x36\x29\x51\x57\x7D"+0xA8B0FF94).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditIDCard->getTTF()->getTexture(),true);
	pEditIDCard->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	pEditIDCard->getTTF()->setColor(ccc3(0,0,0));
	pEditIDCard->InitCursor(0xFF,1,16);
	pEditIDCard->setTag(EDIT_IDCARD_ID);
	//pEditIDCard->setPasswordMode();
	pNode->addChild(pEditIDCard);

	// 文字提示
	CCLabelTTF *pLabelTips = CCLabelTTF::create();
	pLabelTips->setString(" ");
	pLabelTips->setColor(ccc3(255,255,255));
	pLabelTips->setOpacity(255);
	pLabelTips->ignoreAnchorPointForPosition(true);
	pLabelTips->setPosition(_ptRatio(220,170));
	pLabelTips->setTag(TIP_ID);
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture(),true);
	pNode->addChild(pLabelTips);

	CCControlButton * pSubmit = SIX_Utility::GetInstance()->CreateButtonWithFileCell("btn_verify.png", 2);
	if (0 != pSubmit)
	{
		pSubmit->setTag(SUBMIT_BUTTON_ID);
		pSubmit->setPosition(_ptRatio((getContentSize().width-pSubmit->getContentSize().width)/2-10, 115));
		pSubmit->setZoomOnTouchDown(false);
		pSubmit->setDefaultTouchPriority(m_nPriority-1);
		pSubmit->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndPersonalInfomation::doEvents),32);
		pNode->addChild(pSubmit);
	}

	// 文字提示
	CCLabelTTF *pLabelDesc = CCLabelTTF::create();
	pLabelDesc->setString(SIX_Utility::GetInstance()->G2U(/*未满18周岁用户，在游戏过程中将有防沉迷提示！*/XorStr<0xC9,45,0x71121A30>("\x07\x7E\x09\x36\xFC\xF6\x19\x0C\x1A\x38\x00\x17\x6E\x71\x74\x74\x0D\x00\x08\x12\x12\x69\x66\x1D\x52\x2E\x35\x34\x58\x4D\x34\x38\x5E\x2A\x58\x2D\x2E\x3A\x23\x11\x3B\x4C\x50\x55"+0x71121A30).s).c_str());
	pLabelDesc->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelDesc->setFontSize(18);
	pLabelDesc->setColor(ccc3(255,255,255));
	pLabelDesc->setOpacity(255);
	pLabelDesc->ignoreAnchorPointForPosition(true);
	pLabelDesc->setPosition(_ptRatio((getContentSize().width-pLabelDesc->getContentSize().width)/2,55));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelDesc->getTexture(),true);
	pNode->addChild(pLabelDesc);
}

void SIX_PopWndPersonalInfomation::setModifyPW()
{
	CCNode *pNode = 0;
	bool bCreate = setRootNode(EP_ROOT_NODE, pNode);
	if ( !bCreate || !pNode )
		return;

	// 输入框背景
	CCSprite *pSprEdit = CCSprite::create("edit3.png");
	if (pSprEdit)
	{
		pSprEdit->ignoreAnchorPointForPosition(true);
		pSprEdit->setPosition(_ptRatio((getContentSize().width-pSprEdit->getContentSize().width)/2,158));
		pNode->addChild(pSprEdit);
	}

	// 原密码输入框
	SIX_EditBox *pEditPassOld = new SIX_EditBox();
	pEditPassOld->setPosition(_ptRatio(215,288));
	pEditPassOld->setInputTextMaxCount(33);
	pEditPassOld->setContentSize(CCSize(360,63));
	pEditPassOld->getTTF()->setPosition(ccp(5,10));
	pEditPassOld->getTTF()->setFontSize(16);
	pEditPassOld->getTTF()->setScissorSize(CCSize(350,63));
	pEditPassOld->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*原密码*/XorStr<0x68,7,0x8FF80F08>("\xBC\xC4\xA9\xB7\xAE\x86"+0x8FF80F08).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditPassOld->getTTF()->getTexture(),true);
	pEditPassOld->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	pEditPassOld->getTTF()->setColor(ccc3(0,0,0));
	pEditPassOld->InitCursor(0xFF,1,16);
	pEditPassOld->setTag(EDIT_PASS_OLD_ID);
	pNode->addChild(pEditPassOld);

	// 新密码输入框
	SIX_EditBox *pEditPassNew = new SIX_EditBox();
	pEditPassNew->setPosition(_ptRatio(215,225));
	pEditPassNew->setInputTextMaxCount(33);
	pEditPassNew->setContentSize(CCSize(360,63));
	pEditPassNew->getTTF()->setPosition(ccp(5,10));
	pEditPassNew->getTTF()->setFontSize(16);
	pEditPassNew->getTTF()->setScissorSize(CCSize(350,63));
	pEditPassNew->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*新密码*/XorStr<0x57,7,0x21B6C714>("\x87\x9A\x9A\x86\x99\xB7"+0x21B6C714).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditPassNew->getTTF()->getTexture(),true);
	pEditPassNew->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	pEditPassNew->getTTF()->setColor(ccc3(0,0,0));
	pEditPassNew->InitCursor(0xFF,1,16);
	pEditPassNew->setTag(EDIT_PASS_NEW_ID);
	//pEditPassNew->setPasswordMode();
	pNode->addChild(pEditPassNew);
	// 再输入一次密码
	SIX_EditBox *pEditPassNewAgain = new SIX_EditBox();
	pEditPassNewAgain->setPosition(_ptRatio(215,162));
	pEditPassNewAgain->setInputTextMaxCount(33);
	pEditPassNewAgain->setContentSize(CCSize(360,63));
	pEditPassNewAgain->getTTF()->setPosition(ccp(5,10));
	pEditPassNewAgain->getTTF()->setFontSize(16);
	pEditPassNewAgain->getTTF()->setScissorSize(CCSize(350,63));
	pEditPassNewAgain->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*再输入一次密码*/XorStr<0x84,15,0x2D697E95>("\x50\x5C\x4C\x63\x40\x62\x58\x30\x38\x43\x4D\x53\x52\x7A"+0x2D697E95).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditPassNewAgain->getTTF()->getTexture(),true);
	pEditPassNewAgain->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	pEditPassNewAgain->getTTF()->setColor(ccc3(0,0,0));
	pEditPassNewAgain->InitCursor(0xFF,1,16);
	pEditPassNewAgain->setTag(EDIT_PASS_NEW_AGAIN);
	//pEditPassNewAgain->setPasswordMode();
	pNode->addChild(pEditPassNewAgain);
	
	// 文字提示
	CCLabelTTF *pLabelTips = CCLabelTTF::create();
	pLabelTips->setString(" ");
	pLabelTips->setColor(ccc3(255,255,255));
	pLabelTips->setOpacity(255);
	pLabelTips->ignoreAnchorPointForPosition(true);
	pLabelTips->setPosition(_ptRatio(225,140));
	pLabelTips->setTag(MODIFY_PW_TIP);
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture(),true);
	pNode->addChild(pLabelTips);

	CCControlButton * pSubmit = SIX_Utility::GetInstance()->CreateButtonWithFileCell("OkBT.png", 2);
	if (0 != pSubmit)
	{
		pSubmit->setTag(OK_BUTTON_ID);
		pSubmit->setPosition(_ptRatio((getContentSize().width-pSubmit->getContentSize().width)/2, 80));
		pSubmit->setZoomOnTouchDown(false);
		pSubmit->setDefaultTouchPriority(m_nPriority-1);
		pSubmit->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndPersonalInfomation::doEvents),32);
		pNode->addChild(pSubmit);
	}
}