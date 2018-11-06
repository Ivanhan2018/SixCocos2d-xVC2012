#include "SIX_PointCard.h"
#include "SIX_ClientHall.h"
#include "SIX_PlayerMgr.h"
#include "SIX_SceneHall.h"

extern SIX_SceneHall *pSceneHall;

SIX_PopWndPointCard::SIX_PopWndPointCard()
{
}

SIX_PopWndPointCard::~SIX_PopWndPointCard()
{
	CC_SAFE_RELEASE(pEditName);
	CC_SAFE_RELEASE(pEditPass);
}

SIX_PopWndPointCard *SIX_PopWndPointCard::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset,MOVABLE_TYPE showType,MOVABLE_TYPE hideType,bool bSeqExec)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_PopWndPointCard *pPanel = new SIX_PopWndPointCard();
	if (pPanel && pPanel->init())
	{
		pPanel->initWithColor(color,width,height);
		pPanel->setPosition(x,y);
		pPanel->setRedrawBorder(false);
		pPanel->m_ForbiddenTouch = true;
		pPanel->m_bCloseThenCleanup = false;
		pPanel->setShakeOffset(shakeOffset);
		pPanel->setShowType(showType);
		pPanel->setHideType(hideType);
		pPanel->setSeqExec(bSeqExec);
		pPanel->setObjName("SIX_PopWndPointCard");
		//pPanel->setRectDirty();
	}
	return pPanel;
}

bool SIX_PopWndPointCard::onTextFieldAttachWithIME(SIX_EditBox * pSender)
{
	switch (pSender->getTag())
	{
	case EDIT_NAME:
		{
			break;
		}
	case EDIT_PASS:
		{
			break;
		}
	}
	return true;
}

bool SIX_PopWndPointCard::onTextFieldDetachWithIME(SIX_EditBox * pSender)
{
	switch (pSender->getTag())
	{
	case EDIT_NAME:
		{
			break;
		}
	case EDIT_PASS:
		{
			break;
		}
	}
	return true;
}

void SIX_PopWndPointCard::onHideFinished()
{
	if (m_bOpenShopWnd)
	{
		pSceneHall->GetPopWndShop()->Show();
		m_bOpenShopWnd = false;
	}
	return;
}

bool SIX_PopWndPointCard::init()
{
	if (!SIX_EffectPopWnd::init())
		return false;
	pLabelReg = 0;
	pSprBgEdit = 0;
	pEditName = pEditPass = 0;
	pLabelTips = 0;
	pBtnBack = 0;
	m_bOpenShopWnd = false;
	return true;
}

void SIX_PopWndPointCard::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	// 用户注册节点
	pLabelReg = CCNode::create();
	this->addChild(pLabelReg);

	// 输入框背景
	pSprBgEdit = CCSprite::create("edit.png",CCRect(0,0,384,135));
	if (pSprBgEdit)
	{
		pSprBgEdit->ignoreAnchorPointForPosition(true);
		pSprBgEdit->setPosition(ccp(122,185));
		pLabelReg->addChild(pSprBgEdit);
	}

	// 文字提示
	CCLabelTTF *pLabelRegTitle = CCLabelTTF::create();
	pLabelRegTitle->setString(SIX_Utility::GetInstance()->G2U(/*使用老九点卡*/XorStr<0xB0,13,0xA50E6C36>("\x7A\x08\x61\x70\x74\x7A\x08\x72\x0D\x5A\x05\x13"+0xA50E6C36).s).c_str());
	pLabelRegTitle->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelRegTitle->setFontSize(30);
	pLabelRegTitle->setColor(ccc3(228,178,91));
	pLabelRegTitle->setOpacity(255);
	pLabelRegTitle->ignoreAnchorPointForPosition(true);
	pLabelRegTitle->setPosition(ccp((getContentSize().width-pLabelRegTitle->getContentSize().width)/2,370));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelRegTitle->getTexture(),true);
	pLabelReg->addChild(pLabelRegTitle);

	CCSprite *pLamp = CCSprite::create("lamp.png");
	if (NULL != pLamp)
	{
		pLamp->ignoreAnchorPointForPosition(true);
		pLamp->setPositionY(333.0f);
		pLabelReg->addChild(pLamp);
	}

	CCLabelTTF *pLabelRegDesc = CCLabelTTF::create();
	pLabelRegDesc->setString(SIX_Utility::GetInstance()->G2U(/*输入正确的卡号卡密后获赠相应的筹码*/XorStr<0x1B,35,0xD4DFCAD6>("\xD1\xF8\xD5\xF5\xCA\xDD\xE9\x95\x96\xE0\x9A\x8E\x9D\xED\x96\x82\xE8\xF0\x97\xDD\x94\xC1\xE5\xCB\xFC\xD4\xE6\x90\x82\xFC\x8A\xD5\xF9\xD7"+0xD4DFCAD6).s).c_str());
	pLabelRegDesc->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelRegDesc->setFontSize(16);
	pLabelRegDesc->setColor(ccc3(255,255,255));
	pLabelRegDesc->setOpacity(255);
	pLabelRegDesc->ignoreAnchorPointForPosition(true);
	pLabelRegDesc->setHorizontalAlignment(kCCTextAlignmentCenter);
	float fOffset = (getContentSize().width-pLabelRegDesc->getContentSize().width-pLamp->getContentSize().width-10)/2;
	pLamp->setPositionX(fOffset);
	pLabelRegDesc->setPosition(ccp(fOffset+10+pLamp->getContentSize().width,345));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelRegDesc->getTexture(),true);
	pLabelReg->addChild(pLabelRegDesc);

	pEditName = new SIX_EditBox();
	pEditName->setPosition(ccp(130,270));
	pEditName->setInputTextMaxCount(10);
	pEditName->setContentSize(CCSize(360,35));
	pEditName->getTTF()->setPosition(ccp(5,10));
	pEditName->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditName->getTTF()->setScissorSize(CCSize(350,35));
	//pEditName->getTTF()->setDimensions(CCSize(193,16));
	// -- 默认提示文字
	pEditName->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*请输入卡号*/XorStr<0x78,11,0xB44C8BEB>("\xBF\x92\xB0\x9F\xB4\x96\xC1\xD7\x3A\x44"+0xB44C8BEB).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditName->getTTF()->getTexture(),true);
	// -- 提示文字颜色
	pEditName->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditName->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditName->InitCursor(0xFF,1,16);
	//pEditName->attachWithIME();
	pEditName->setTag(EDIT_NAME);
	pLabelReg->addChild(pEditName);

	// 密码输入框
	pEditPass = new SIX_EditBox();
	pEditPass->setPosition(ccp(130,200));
	pEditPass->setInputTextMaxCount(7);
	pEditPass->setContentSize(CCSize(360,35));
	pEditPass->getTTF()->setPosition(ccp(5,10));
	pEditPass->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditPass->getTTF()->setScissorSize(CCSize(350,35));
	//pEditPass->getTTF()->setDimensions(CCSize(193,16));
	// -- 默认提示文字
	pEditPass->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*请输入密码*/XorStr<0xE3,11,0x678461A0>("\x24\x0F\x2F\x02\x2F\x03\x2A\x36\x29\x07"+0x678461A0).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditPass->getTTF()->getTexture(),true);
	// -- 提示文字颜色
	pEditPass->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditPass->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditPass->InitCursor(0xFF,1,16);
	pEditPass->setTag(EDIT_PASS);
	// -- 设置密码框模式
	//pEditPass->setPasswordMode();
	pLabelReg->addChild(pEditPass);

	// 文字提示
	pLabelTips = CCLabelTTF::create();
	pLabelTips->setString(" ");
	pLabelTips->setColor(ccc3(255,255,255));
	pLabelTips->setOpacity(255);
	pLabelTips->ignoreAnchorPointForPosition(true);
	pLabelTips->setPosition(ccp(130,165));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture(),true);
	pLabelReg->addChild(pLabelTips);

	pBtnBack = SIX_Utility::GetInstance()->CreateButtonWithFileCell("ReturnShopBTN.png",2);
	if (pBtnBack)
	{
		pBtnBack->setDefaultTouchPriority(m_nPriority-1);
		pBtnBack->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		pBtnBack->setTag(BTN_BACK);
		pLabelReg->addChild(pBtnBack);
	}

	if (0!=pSubmit  &&  0!=pBtnBack)
	{
		float fOffset = (getContentSize().width-pBtnBack->getContentSize().width-pSubmit->getContentSize().width-10)/2;
		pBtnBack->setPosition(ccp(fOffset,80));
		pSubmit->setPosition(ccp(fOffset+pBtnBack->getContentSize().width+10,80));
	}
}

void SIX_PopWndPointCard::OnTouchLogic(CCTouch *pTouch,int pEvent)
{
	SIX_EffectPopWnd::OnTouchLogic(pTouch,pEvent);

	switch (pEvent)
	{
	case CCTOUCHBEGAN:
		{
			if (pEditName)
				pEditName->ccTouchBegan(pTouch,0);
			if (pEditPass)
				pEditPass->ccTouchBegan(pTouch,0);
			break;
		}
	case CCTOUCHMOVED:
		{
			if (pEditName)
				pEditName->ccTouchMoved(pTouch,0);
			if (pEditPass)
				pEditPass->ccTouchMoved(pTouch,0);
			break;
		}
	case CCTOUCHENDED:
		{
			if (pEditName)
				pEditName->ccTouchEnded(pTouch,0);
			if (pEditPass)
				pEditPass->ccTouchEnded(pTouch,0);
			break;
		}
	case CCTOUCHCANCELLED:
		{
			if (pEditName)
				pEditName->ccTouchCancelled(pTouch,0);
			if (pEditPass)
				pEditPass->ccTouchCancelled(pTouch,0);
			break;
		}
	}
}

bool SIX_PopWndPointCard::OnBtn(CCObject* pObject,int tag)
{
	CCControlButton *pButton = dynamic_cast<CCControlButton*>(pObject);
	if (!pButton)
		return true;

	switch (pButton->getTag())
	{
	case BTN_BACK:
		{
			m_bOpenShopWnd = true;
			this->Show(false);
			break;
		}
	}

	return true;
}

bool SIX_PopWndPointCard::OnSubmit()
{
	this->DoOK();
	return false;
}

void SIX_PopWndPointCard::OnInputDone(CCLayer *pLayer,const char *text)
{
#ifdef WIN32
	SIX_EditBox *pThis = (SIX_EditBox*)pLayer;
	if (!pThis || !pThis->getParent())
		return;
	pThis->getTTF()->detachWithIME();
#endif
}

bool SIX_PopWndPointCard::DoOK()
{
	this->DoLockPanel(true);

	CCString *pName = 0;
	CCString *pPass = 0;
	char md5Dst[33] = {0};
	ERROR_INFO err = ERROR_NONE;
	
	do 
	{
		pName = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditName->getTTF()->getString());
		// 用户名不能为空
		if (!pName->length())
		{
			this->showTips(/*卡号不能为空！*/XorStr<0x0C,15,0x4263251F>("\xB3\xA5\xB4\xCA\xA2\xAA\xD6\xCF\xDA\xBF\xA9\xC2\xBB\xB8"+0x4263251F).s);
			pEditName->attachWithIME();
			break;
		}

		pPass = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditPass->getTTF()->getString());
		// 密码不能为空
		if (!pPass->length())
		{
			this->showTips(/*卡密不能为空！*/XorStr<0x66,15,0x20B170D1>("\xD9\xCF\xAB\xB5\xD8\xD0\xA8\xB1\xA0\xC5\xCF\xA4\xD1\xD2"+0x20B170D1).s);
			pEditPass->attachWithIME();
			break;
		}

		// 正常流程开始
		this->showTips(/*正在充值...*/XorStr<0xAD,12,0x301BABF3>("\x78\x53\x7B\x6A\x02\x56\x65\x01\x9B\x98\x99"+0x301BABF3).s);
		pEditName->detachWithIME();
		pEditPass->detachWithIME();

		CMD_PointCard_AddMoney pointcard;
		pointcard.lUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
#ifdef WIN32
		sprintf_s(pointcard.szCardNumber, CMD_PointCard_AddMoney::CARD_LEN, "%s", pName->getCString());
		sprintf_s(pointcard.szPassword, CMD_PointCard_AddMoney::PW_LEN, "%s", pPass->getCString());
#else
		if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		{
			snprintf(pointcard.szCardNumber, CMD_PointCard_AddMoney::CARD_LEN, "%s", pName->getCString());
			snprintf(pointcard.szPassword, CMD_PointCard_AddMoney::PW_LEN, "%s", pPass->getCString());
		}
#endif
		//SIX_ClientHall::GetInstance()->Connect(false);
		SIX_ClientHall::GetInstance()->SendData(MAIN_MSG_SHOP, SUB_CSG_POINTCARD, (BYTE *)&pointcard, sizeof(pointcard));
		return false;
	} while (0);

	this->DoLockPanel(false);
	return false;
}

void SIX_PopWndPointCard::DoLockPanel(bool lock)
{
	if (this->GetBtnSubmit())
	{
		this->GetBtnSubmit()->setEnabled(!lock);
		this->GetBtnSubmit()->setTouchEnabled(!lock);
	}
	if (this->GetBtnCancel())
	{
		this->GetBtnCancel()->setEnabled(!lock);
		this->GetBtnCancel()->setTouchEnabled(!lock);
	}
	if (this->GetBtnClose())
	{
		this->GetBtnClose()->setEnabled(!lock);
		this->GetBtnClose()->setTouchEnabled(!lock);
	}

	if (pEditName)
	{
		pEditName->setTouchEnabled(!lock);
	}
	if (pEditPass)
	{
		pEditPass->setTouchEnabled(!lock);
	}

	if (pBtnBack)
	{
		pBtnBack->setEnabled(!lock);
		pBtnBack->setTouchEnabled(!lock);
	}
}

void SIX_PopWndPointCard::DoSwitchIMEFocus()
{
	if (pEditName->IsAttachWithIME())
	{
		pEditName->detachWithIME();
		pEditPass->attachWithIME();
	}
	else
	{
		pEditName->attachWithIME();
		pEditPass->detachWithIME();
	}
}

void SIX_PopWndPointCard::EmptyCardAndPW()
{
	pEditName->getTTF()->setString("");
	pEditPass->getTTF()->setString("");
}

void SIX_PopWndPointCard::showTips(const char *msg)
{
	if (!pLabelTips)
		return;

	pLabelTips->setString(SIX_Utility::GetInstance()->G2U(msg).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture(),true);
}