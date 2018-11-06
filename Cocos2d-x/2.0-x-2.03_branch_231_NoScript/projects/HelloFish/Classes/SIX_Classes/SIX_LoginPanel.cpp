#include "SIX_LoginPanel.h"
#include "SIX_ClientLogin.h"

SIX_LoginPanel::SIX_LoginPanel()
{
}

SIX_LoginPanel::~SIX_LoginPanel()
{
	CC_SAFE_RELEASE(pEditName);
	CC_SAFE_RELEASE(pEditPass);
	CC_SAFE_RELEASE(pEditIP);
}

SIX_LoginPanel *SIX_LoginPanel::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset,MOVABLE_TYPE showType,MOVABLE_TYPE hideType,bool bSeqExec)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_LoginPanel *pLoginPanel = new SIX_LoginPanel();
	if (pLoginPanel && pLoginPanel->init())
	{
		pLoginPanel->initWithColor(color,width,height);
		pLoginPanel->setPosition(x,y);
		pLoginPanel->setRedrawBorder(false);
		pLoginPanel->m_ForbiddenTouch = true;
		pLoginPanel->m_bCloseThenCleanup = false;
		pLoginPanel->setShakeOffset(shakeOffset);
		pLoginPanel->setShowType(showType);
		pLoginPanel->setHideType(hideType);
		pLoginPanel->setSeqExec(bSeqExec);
		pLoginPanel->setObjName("SIX_LoginPanel");
		//pLoginPanel->setRectDirty();
	}
	return pLoginPanel;
}

bool SIX_LoginPanel::init()
{
	if (!SIX_PopWnd::init())
		return false;
	pSprBgName = 0;
	pSprBgPass = 0;
	pSprBgIP=0;
	pEditName = 0;
	pEditPass = 0;
	pEditIP=0;
	pLabelTips = 0;
	return true;
}

void SIX_LoginPanel::onEnter()
{
	CCLayerColor::onEnter();
}

void SIX_LoginPanel::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	// 用户名背景
	pSprBgName = CCSprite::create("Scene/Gate/accountEditBG.png",CCRect(0,0,203,32));
	if (pSprBgName)
	{
		pSprBgName->ignoreAnchorPointForPosition(true);
		pSprBgName->setPosition(ccp(110,125));
		this->addChild(pSprBgName);
	}

	// 密码背景
	pSprBgPass = CCSprite::create("Scene/Gate/PasswordEditBG.png",CCRect(0,0,203,32));
	if (pSprBgPass)
	{
		pSprBgPass->ignoreAnchorPointForPosition(true);
		pSprBgPass->setPosition(ccp(110,85));
		this->addChild(pSprBgPass);
	}

	// IP背景
	pSprBgIP = CCSprite::create("Scene/Gate/accountEditBG.png",CCRect(0,0,203,32));
	if (pSprBgIP)
	{
		pSprBgIP->ignoreAnchorPointForPosition(true);
		pSprBgIP->setPosition(ccp(110,45));
		this->addChild(pSprBgIP);
	}

	// 用户名输入框
	pEditName = new SIX_EditBox();
	pEditName->setPosition(ccp(110,120));
	pEditName->setInputTextMaxCount(32);
	pEditName->setContentSize(CCSize(203,35));
	pEditName->getTTF()->setPosition(ccp(5,10));
	pEditName->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditName->getTTF()->setScissorSize(CCSize(160,35));
	//pEditName->getTTF()->setDimensions(CCSize(193,16));
	// -- 默认提示文字
	pEditName->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*请输入用户名*/XorStr<0x5E,13,0x9D0067B1>("\x99\xB4\xAA\x85\xAA\x88\xB7\xA6\xDD\xC0\xAB\x92"+0x9D0067B1).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditName->getTTF()->getTexture());
	// -- 提示文字颜色
	pEditName->getTTF()->setColorSpaceHolder(ccc3(0,0,0));
	// -- 输入文字颜色
	pEditName->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditName->InitCursor(0xFF,1,16);
	//pEditName->attachWithIME();
	pEditName->setTag(1);
	pEditName->getTTF()->setString("T1");
	this->addChild(pEditName);

	// 密码输入框
	pEditPass = new SIX_EditBox();
	pEditPass->setPosition(ccp(110,80));
	pEditPass->setInputTextMaxCount(32);
	pEditPass->setContentSize(CCSize(203,35));
	pEditPass->getTTF()->setPosition(ccp(5,10));
	pEditPass->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditPass->getTTF()->setScissorSize(CCSize(160,35));
	//pEditPass->getTTF()->setDimensions(CCSize(193,16));
	// -- 默认提示文字
	pEditPass->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*请输入密码*/XorStr<0x2C,11,0x501ACE6F>("\xEB\xC6\xE4\xCB\xF8\xDA\xF1\xEF\xF6\xDE"+0x501ACE6F).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditPass->getTTF()->getTexture());
	// -- 提示文字颜色
	pEditPass->getTTF()->setColorSpaceHolder(ccc3(0,0,0));
	// -- 输入文字颜色
	pEditPass->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditPass->InitCursor(0xFF,1,16);
	pEditPass->setTag(2);
	// -- 设置密码框模式
	pEditPass->setPasswordMode();
	pEditPass->getTTF()->setString("123");
	this->addChild(pEditPass);

	// IP输入框
	pEditIP = new SIX_EditBox();
	pEditIP->setPosition(ccp(110,40));
	pEditIP->setInputTextMaxCount(32);
	pEditIP->setContentSize(CCSize(203,35));
	pEditIP->getTTF()->setPosition(ccp(5,10));
	pEditIP->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditIP->getTTF()->setScissorSize(CCSize(160,35));
	//pEditName->getTTF()->setDimensions(CCSize(193,16));
	// -- 默认提示文字
	pEditIP->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U("请输入服务器IP(可选)").c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditIP->getTTF()->getTexture());
	// -- 提示文字颜色
	pEditIP->getTTF()->setColorSpaceHolder(ccc3(0,0,0));
	// -- 输入文字颜色
	pEditIP->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditIP->InitCursor(0xFF,1,16);
	//pEditName->attachWithIME();
	pEditIP->setTag(3);
	this->addChild(pEditIP);

	// 文字提示
	pLabelTips = CCLabelTTF::create();
	pLabelTips->setString(" ");
	pLabelTips->setColor(ccc3(255,0,0));
	pLabelTips->setOpacity(255);
	pLabelTips->ignoreAnchorPointForPosition(true);
	pLabelTips->setPosition(ccp(110,65));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture());
	this->addChild(pLabelTips);
}

void SIX_LoginPanel::DoSwitchIMEFocus()
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

bool SIX_LoginPanel::onTextFieldAttachWithIME(SIX_EditBox * pSender)
{
	switch (pSender->getTag())
	{
	case 1:
	//case 3:
		{
			if (pSprBgName)
			{
				CCSprite *pSpr = CCSprite::create("Scene/Gate/accountEditBG.png");
				pSprBgName->setTexture(pSpr->getTexture());
				pSprBgName->setTextureRect(CCRect(203,0,203,32));
				pSprBgName->setDirty(true);
			}
			if (pSprBgPass)
			{
				CCSprite *pSpr = CCSprite::create("Scene/Gate/PasswordEditBG.png");
				pSprBgPass->setTexture(pSpr->getTexture());
				pSprBgPass->setTextureRect(CCRect(0,0,203,32));
				pSprBgPass->setDirty(true);
			}
			break;
		}
	case 2:
		{
			if (pSprBgName)
			{
				CCSprite *pSpr = CCSprite::create("Scene/Gate/accountEditBG.png");
				pSprBgName->setTexture(pSpr->getTexture());
				pSprBgName->setTextureRect(CCRect(0,0,203,32));
				pSprBgName->setDirty(true);
			}
			if (pSprBgPass)
			{
				CCSprite *pSpr = CCSprite::create("Scene/Gate/PasswordEditBG.png");
				pSprBgPass->setTexture(pSpr->getTexture());
				pSprBgPass->setTextureRect(CCRect(203,0,203,32));
				pSprBgPass->setDirty(true);
			}
			break;
		}
	}
	return true;
}

bool SIX_LoginPanel::onTextFieldDetachWithIME(SIX_EditBox * pSender)
{
	switch (pSender->getTag())
	{
	case 1:
	//case 3:
		{
			if (pSprBgName)
			{
				CCSprite *pSpr = CCSprite::create("Scene/Gate/accountEditBG.png");
				pSprBgName->setTexture(pSpr->getTexture());
				pSprBgName->setTextureRect(CCRect(0,0,203,32));
				pSprBgName->setDirty(true);
			}
			break;
		}
	case 2:
		{
			if (pSprBgPass)
			{
				CCSprite *pSpr = CCSprite::create("Scene/Gate/PasswordEditBG.png");
				pSprBgPass->setTexture(pSpr->getTexture());
				pSprBgPass->setTextureRect(CCRect(0,0,203,32));
				pSprBgPass->setDirty(true);
			}
			break;
		}
	}
	return true;
}

void SIX_LoginPanel::OnTouchLogic(CCTouch *pTouch,int pEvent)
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
			if (pEditIP)
				pEditIP->ccTouchBegan(pTouch,0);
			break;
		}
	case CCTOUCHMOVED:
		{
			if (pEditName)
				pEditName->ccTouchMoved(pTouch,0);
			if (pEditPass)
				pEditPass->ccTouchMoved(pTouch,0);
			if (pEditIP)
				pEditIP->ccTouchMoved(pTouch,0);
			break;
		}
	case CCTOUCHENDED:
		{
			if (pEditName)
				pEditName->ccTouchEnded(pTouch,0);
			if (pEditPass)
				pEditPass->ccTouchEnded(pTouch,0);
			if (pEditIP)
				pEditIP->ccTouchEnded(pTouch,0);
			break;
		}
	case CCTOUCHCANCELLED:
		{
			if (pEditName)
				pEditName->ccTouchCancelled(pTouch,0);
			if (pEditPass)
				pEditPass->ccTouchCancelled(pTouch,0);
			if (pEditIP)
				pEditIP->ccTouchCancelled(pTouch,0);
			break;
		}
	}
}

bool SIX_LoginPanel::OnBtn(CCObject* pObject,int tag)
{
	CCControlButton *pButton = dynamic_cast<CCControlButton*>(pObject);
	if (!pButton)
		return true;

	return true;
}

// 登录
bool SIX_LoginPanel::OnSubmit()
{
	return DoLogin();
}

// 退出
bool SIX_LoginPanel::OnClose()
{
	CCDirector::sharedDirector()->end();
	return false;
}

void SIX_LoginPanel::showTips(const char *msg)
{
	if (!pLabelTips)
		return;

	pLabelTips->setString(msg);
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture());
}

void SIX_LoginPanel::DoEnter()
{
	if (isVisible()==false)
		return;
	if (pEditName)
		pEditName->attachWithIME();
}

void SIX_LoginPanel::OnInputDone(CCLayer *pLayer,const char *text)
{
#ifdef WIN32
	SIX_EditBox *pThis = (SIX_EditBox*)pLayer;
	if (!pThis || !pThis->getParent())
		return;
	pThis->getTTF()->detachWithIME();
#endif
}

bool SIX_LoginPanel::DoLogin()
{
	this->DoLockPanel(true);

	CCString *pName = 0;
	CCString *pPass = 0;
	CCString *pIP = 0;
	char md5Dst[33] = {0};
	ERROR_INFO err = ERROR_NONE;
	
	pName = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditName->getTTF()->getString());
	// 用户名不能为空
	if (!pName->length())
	{
		pLabelTips->setString(SIX_Utility::GetInstance()->G2U(/*用户名不能为空！*/XorStr<0xF2,17,0xE41E31E4>("\x21\x30\x4F\x52\x35\x0C\x4A\x42\x3E\x27\x32\x57\x41\x2A\xA3\xA0"+0xE41E31E4).s).c_str());
		SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture());
		pEditName->attachWithIME();
		goto clean;
	}

	// add by Ivan_han 20140915
	//SIX_GlobalMgr::GetInstance()->GetConfig()->ip="192.168.1.101";
	pIP = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditIP->getTTF()->getString());
	// IP非空
	if (pIP->length()>0)
	{
		SIX_GlobalMgr::GetInstance()->GetConfig()->ip=pIP->getCString();
	}

	pPass = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditPass->getTTF()->getString());
	// 密码不能为空
	if (!pPass->length())
	{
		pLabelTips->setString(SIX_Utility::GetInstance()->G2U(/*密码不能为空！*/XorStr<0x23,15,0x7C58FD91>("\xE0\xF8\xE7\xCD\x95\x93\xED\xF6\xE5\x86\x92\xFB\x8C\x91"+0x7C58FD91).s).c_str());
		SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture());
		pEditPass->attachWithIME();
		goto clean;
	}

	// 正常流程开始
	pLabelTips->setString(SIX_Utility::GetInstance()->G2U(/*正在登录 ...*/XorStr<0x82,13,0xA48FCE3D>("\x57\x7E\x50\x5F\x33\x40\x4A\x35\xAA\xA5\xA2\xA3"+0xA48FCE3D).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture());
	pEditName->detachWithIME();
	pEditPass->detachWithIME();

	err = SIX_GlobalMgr::GetInstance()->GetFS()->GetMicroEncryptAndDecrypt()->HashByMD5((char*)(pPass->getCString()),pPass->length(),md5Dst,false);
	if (err!=ERROR_NONE)
	{
		SIXLog("pName[%s].pPass[%s].md5Dst[%s]",pName->getCString(),pPass->getCString(),md5Dst);
		this->showTips(SIX_Utility::GetInstance()->G2U(/*用户登录信息异常*/XorStr<0x66,17,0x6801096D>("\xB5\xA4\xD3\xCE\xDF\xAC\xAE\xD1\xBE\xAA\xBF\xD3\xA0\x9F\xC7\xD6"+0x6801096D).s).c_str());
		goto clean;
	}

	// save it
	SIX_PlayerMgr::GetInstance()->setMyUserInfo((char*)pName->getCString(),md5Dst);

	// 请求登录服务器，获取房间列表
	
        SIX_ClientLogin::GetInstance()->Connect(false);

	return false;
clean:
	this->DoLockPanel(false);
	return false;
}

void SIX_LoginPanel::DoLockPanel(bool lock)
{
	pEditName->setTouchEnabled(!lock);
	pEditPass->setTouchEnabled(!lock);
	this->GetBtnSubmit()->setEnabled(!lock);
}