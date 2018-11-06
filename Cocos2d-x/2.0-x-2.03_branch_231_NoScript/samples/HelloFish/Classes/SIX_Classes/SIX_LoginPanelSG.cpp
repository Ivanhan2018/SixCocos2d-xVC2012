#include "SIX_LoginPanelSG.h"
#include "SIX_ClientLogin.h"
#include "SIX_PlayerMgr.h"
//#include "SIX_SceneLogin.h"
//
//extern SIX_SceneLogin *pSceneLogin;

SIX_LoginPanelSG::SIX_LoginPanelSG()
{
}

SIX_LoginPanelSG::~SIX_LoginPanelSG()
{
	CC_SAFE_RELEASE(pEditLoginName);
	CC_SAFE_RELEASE(pEditLoginPass);
	CC_SAFE_RELEASE(pEditRegName);
	CC_SAFE_RELEASE(pEditRegPass);
}

SIX_LoginPanelSG *SIX_LoginPanelSG::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset,MOVABLE_TYPE showType,MOVABLE_TYPE hideType,bool bSeqExec)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_LoginPanelSG *pLoginPanel = new SIX_LoginPanelSG();
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
		pLoginPanel->setObjName("SIX_LoginPanelSG");
		//pLoginPanel->setRectDirty();
	}
	return pLoginPanel;
}

bool SIX_LoginPanelSG::init()
{
	if (!SIX_PopWnd::init())
		return false;
	pLabelLogin = pLabelReset = pLabelReg = 0;
	pBtnResetBackLogin = 0;
	pSprBgLoginEdit = pSprBgRegEdit = 0;
	pEditLoginName = pEditLoginPass = 0;
	pEditRegName = pEditRegPass = 0;
	pLabelLoginTips = pLabelRegTips = 0;
	pBtnGetPass = pBtnLoginReg = 0;
	pBtnRegBackLogin = pBtnRegReg = 0;
	checkStatus = 0;
	return true;
}

void SIX_LoginPanelSG::onEnter()
{
	CCLayerColor::onEnter();
}

void SIX_LoginPanelSG::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	// 用户登录节点
	pLabelLogin = CCNode::create();
	pLabelLogin->setVisible(true);
	this->addChild(pLabelLogin);

	// 输入框背景
	pSprBgLoginEdit = CCSprite::create("edit.png",CCRect(0,0,384,135));
	if (pSprBgLoginEdit)
	{
		pSprBgLoginEdit->ignoreAnchorPointForPosition(true);
		pSprBgLoginEdit->setPosition(ccp(122,185));
		pLabelLogin->addChild(pSprBgLoginEdit);
	}

	// 文字提示
	CCLabelTTF *pLabelLoginTitle = CCLabelTTF::create();
	pLabelLoginTitle->setString(SIX_Utility::GetInstance()->G2U(/*欢迎回到*/XorStr<0xF5,9,0x95393442>("\x4E\x40\x24\x55\x42\x22\x4E\x41"+0x95393442).s).c_str());
	pLabelLoginTitle->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelLoginTitle->setFontSize(30);
	pLabelLoginTitle->setColor(ccc3(228,178,91));
	pLabelLoginTitle->setOpacity(255);
	pLabelLoginTitle->ignoreAnchorPointForPosition(true);
	pLabelLoginTitle->setPosition(ccp(255,370));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelLoginTitle->getTexture()/*,true*/);
	pLabelLogin->addChild(pLabelLoginTitle);

	CCLabelTTF *pLabelLoginDesc = CCLabelTTF::create();
	pLabelLoginDesc->setString(SIX_Utility::GetInstance()->G2U(/*老九天天三公*/XorStr<0xBE,13,0x80DE8441>("\x7E\x70\x7E\x04\x0E\x2F\x08\x29\x0E\x3A\x71\x62"+0x80DE8441).s).c_str());
	pLabelLoginDesc->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelLoginDesc->setFontSize(30);
	pLabelLoginDesc->setColor(ccc3(228,178,91));
	pLabelLoginDesc->setOpacity(255);
	pLabelLoginDesc->ignoreAnchorPointForPosition(true);
	pLabelLoginDesc->setPosition(ccp(225,325));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelLoginDesc->getTexture()/*,true*/);
	pLabelLogin->addChild(pLabelLoginDesc);

	// 用户名输入框
	pEditLoginName = new SIX_EditBox();
	pEditLoginName->setPosition(ccp(130,270));
	pEditLoginName->setInputTextMaxCount(33);
	pEditLoginName->setContentSize(CCSize(360,35));
	pEditLoginName->getTTF()->setPosition(ccp(5,10));
	pEditLoginName->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditLoginName->getTTF()->setScissorSize(CCSize(350,35));
	//pEditLoginName->getTTF()->setDimensions(CCSize(193,16));
	// -- 默认提示文字
	pEditLoginName->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*请输入用户名*/XorStr<0x5E,13,0x9D0067B1>("\x99\xB4\xAA\x85\xAA\x88\xB7\xA6\xDD\xC0\xAB\x92"+0x9D0067B1).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditLoginName->getTTF()->getTexture()/*,true*/);
	// -- 提示文字颜色
	pEditLoginName->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditLoginName->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditLoginName->InitCursor(0xFF,1,16);
	//pEditLoginName->attachWithIME();
	pEditLoginName->setTag(EDIT_LOGIN_NAME);
	pLabelLogin->addChild(pEditLoginName);

	// 密码输入框
	pEditLoginPass = new SIX_EditBox();
	pEditLoginPass->setPosition(ccp(130,200));
	pEditLoginPass->setInputTextMaxCount(33);
	pEditLoginPass->setContentSize(CCSize(360,35));
	pEditLoginPass->getTTF()->setPosition(ccp(5,10));
	pEditLoginPass->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditLoginPass->getTTF()->setScissorSize(CCSize(350,35));
	//pEditLoginPass->getTTF()->setDimensions(CCSize(193,16));
	// -- 默认提示文字
	pEditLoginPass->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*请输入密码*/XorStr<0x2C,11,0x501ACE6F>("\xEB\xC6\xE4\xCB\xF8\xDA\xF1\xEF\xF6\xDE"+0x501ACE6F).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditLoginPass->getTTF()->getTexture()/*,true*/);
	// -- 提示文字颜色
	pEditLoginPass->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditLoginPass->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditLoginPass->InitCursor(0xFF,1,16);
	pEditLoginPass->setTag(EDIT_LOGIN_PASS);
	// -- 设置密码框模式
	pEditLoginPass->setPasswordMode();
	pLabelLogin->addChild(pEditLoginPass);

	// 文字提示
	pLabelLoginTips = CCLabelTTF::create();
	pLabelLoginTips->setString(" ");
	pLabelLoginTips->setColor(ccc3(255,255,255));
	pLabelLoginTips->setOpacity(255);
	pLabelLoginTips->ignoreAnchorPointForPosition(true);
	pLabelLoginTips->setPosition(ccp(130,165));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelLoginTips->getTexture()/*,true*/);
	pLabelLogin->addChild(pLabelLoginTips);

	// 找回密码
	pBtnGetPass = SIX_Utility::GetInstance()->CreateButtonWithFileCell("login_btn_getpass.png",2);
	if (pBtnGetPass)
	{
		pBtnGetPass->setDefaultTouchPriority(m_nPriority-1);
		pBtnGetPass->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		pBtnGetPass->setPosition(ccp(122,20));
		pBtnGetPass->setTag(BTN_GETPASS);
		pLabelLogin->addChild(pBtnGetPass);
	}

	// 注册帐号
	pBtnLoginReg = SIX_Utility::GetInstance()->CreateButtonWithFileCell("login_btn_reg.png",2);
	if (pBtnLoginReg)
	{
		pBtnLoginReg->setDefaultTouchPriority(m_nPriority-1);
		pBtnLoginReg->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		pBtnLoginReg->setPosition(ccp(315,20));
		pBtnLoginReg->setTag(BTN_GOTOREG);
		pLabelLogin->addChild(pBtnLoginReg);
	}

	// 找回密码节点
	pLabelReset = CCNode::create();
	pLabelReset->setVisible(false);
	this->addChild(pLabelReset);

	// 文字提示
	CCLabelTTF *pLabelResetTitle = CCLabelTTF::create();
	pLabelResetTitle->setString(SIX_Utility::GetInstance()->G2U(/*找回密码*/XorStr<0x9C,9,0xBB8036B4>("\x49\x4F\x25\x47\x63\x7D\x60\x48"+0xBB8036B4).s).c_str());
	pLabelResetTitle->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelResetTitle->setFontSize(30);
	pLabelResetTitle->setColor(ccc3(228,178,91));
	pLabelResetTitle->setOpacity(255);
	pLabelResetTitle->ignoreAnchorPointForPosition(true);
	pLabelResetTitle->setPosition(ccp(255,370));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelResetTitle->getTexture()/*,true*/);
	pLabelReset->addChild(pLabelResetTitle);

	CCLabelTTF *pLabelResetDesc = CCLabelTTF::create();
	pLabelResetDesc->setString(SIX_Utility::GetInstance()->G2U(/*请加客服QQ：88888888\n核实信息后将为您重置密码*/XorStr<0x65,46,0xF154CB73>("\xA2\x8D\xDB\xBB\xD6\xA7\xDC\x92\x3C\x3F\xCC\xCA\x49\x4A\x4B\x4C\x4D\x4E\x4F\x40\x73\xC0\xB0\xB6\xC8\xAE\xBA\x4F\x23\x38\x70\x39\x2E\x48\x2D\x4C\x73\x5C\x53\x5A\x4E\x4D\x53\x52\x7A"+0xF154CB73).s).c_str());
	pLabelResetDesc->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelResetDesc->setFontSize(30);
	pLabelResetDesc->setColor(ccc3(255,255,255));
	pLabelResetDesc->setOpacity(255);
	pLabelResetDesc->ignoreAnchorPointForPosition(true);
	pLabelResetDesc->setHorizontalAlignment(kCCTextAlignmentCenter);
	pLabelResetDesc->setPosition(ccp(130,220));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelResetDesc->getTexture()/*,true*/);
	pLabelReset->addChild(pLabelResetDesc);

	// 返回登录
	pBtnResetBackLogin = SIX_Utility::GetInstance()->CreateButtonWithFileCell("reset_btn_login.png",2);
	if (pBtnResetBackLogin)
	{
		pBtnResetBackLogin->setDefaultTouchPriority(m_nPriority-1);
		pBtnResetBackLogin->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		pBtnResetBackLogin->setPosition(ccp(240,80));
		pBtnResetBackLogin->setTag(BTN_BACKLOGIN);
		pBtnResetBackLogin->setVisible(false);
		pLabelReset->addChild(pBtnResetBackLogin);
	}

	// 用户注册节点
	pLabelReg = CCNode::create();
	pLabelReg->setVisible(false);
	this->addChild(pLabelReg);

	// 输入框背景
	pSprBgRegEdit = CCSprite::create("edit.png",CCRect(0,0,384,135));
	if (pSprBgRegEdit)
	{
		pSprBgRegEdit->ignoreAnchorPointForPosition(true);
		pSprBgRegEdit->setPosition(ccp(122,185));
		pLabelReg->addChild(pSprBgRegEdit);
	}

	// 文字提示
	CCLabelTTF *pLabelRegTitle = CCLabelTTF::create();
	pLabelRegTitle->setString(SIX_Utility::GetInstance()->G2U(/*账户注册*/XorStr<0x9C,9,0x751FF6A0>("\x49\x56\x25\x38\x77\x03\x10\x42"+0x751FF6A0).s).c_str());
	pLabelRegTitle->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelRegTitle->setFontSize(30);
	pLabelRegTitle->setColor(ccc3(228,178,91));
	pLabelRegTitle->setOpacity(255);
	pLabelRegTitle->ignoreAnchorPointForPosition(true);
	pLabelRegTitle->setPosition(ccp(255,370));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelRegTitle->getTexture()/*,true*/);
	pLabelReg->addChild(pLabelRegTitle);

	CCLabelTTF *pLabelRegDesc = CCLabelTTF::create();
	pLabelRegDesc->setString(SIX_Utility::GetInstance()->G2U(/*注册后可保留游戏中的筹码，让您升级设备\n或在其他设备上游戏时没有后顾之忧！*/XorStr<0x44,74,0x37EB9CCD>("\x93\xE7\xF4\xA6\xF2\xBA\xF5\x82\xFD\xEE\x8F\xBB\x83\x9F\x9D\xE4\x82\x85\xE3\x93\xEB\xB6\x98\xB0\xFF\xF1\x96\x9C\xA4\x9B\xAB\x9E\xD8\xD3\xAF\x8F\xD9\xD1\x60\xD0\x9E\xB9\xB4\xA9\x94\xBA\x89\xBA\x9C\xC4\xCE\xBE\xB7\xAA\xB4\xB4\xCB\xB7\xCF\xBC\x3B\x52\x52\x39\x77\x3C\x4D\x51\x26\x5A\x4D\x28\x2D"+0x37EB9CCD).s).c_str());
	pLabelRegDesc->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelRegDesc->setFontSize(16);
	pLabelRegDesc->setColor(ccc3(255,255,255));
	pLabelRegDesc->setOpacity(255);
	pLabelRegDesc->ignoreAnchorPointForPosition(true);
	pLabelRegDesc->setHorizontalAlignment(kCCTextAlignmentCenter);
	pLabelRegDesc->setPosition(ccp(157,325));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelRegDesc->getTexture()/*,true*/);
	pLabelReg->addChild(pLabelRegDesc);

	// 用户名输入框
	pEditRegName = new SIX_EditBox();
	pEditRegName->setPosition(ccp(130,270));
	pEditRegName->setInputTextMaxCount(33);
	pEditRegName->setContentSize(CCSize(360,35));
	pEditRegName->getTTF()->setPosition(ccp(5,10));
	pEditRegName->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditRegName->getTTF()->setScissorSize(CCSize(350,35));
	//pEditRegName->getTTF()->setDimensions(CCSize(193,16));
	// -- 默认提示文字
	pEditRegName->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*请输入用户名*/XorStr<0x5E,13,0x9D0067B1>("\x99\xB4\xAA\x85\xAA\x88\xB7\xA6\xDD\xC0\xAB\x92"+0x9D0067B1).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditRegName->getTTF()->getTexture()/*,true*/);
	// -- 提示文字颜色
	pEditRegName->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditRegName->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditRegName->InitCursor(0xFF,1,16);
	//pEditRegName->attachWithIME();
	pEditRegName->setTag(EDIT_REG_NAME);
	pLabelReg->addChild(pEditRegName);

	// 密码输入框
	pEditRegPass = new SIX_EditBox();
	pEditRegPass->setPosition(ccp(130,200));
	pEditRegPass->setInputTextMaxCount(33);
	pEditRegPass->setContentSize(CCSize(360,35));
	pEditRegPass->getTTF()->setPosition(ccp(5,10));
	pEditRegPass->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditRegPass->getTTF()->setScissorSize(CCSize(350,35));
	//pEditRegPass->getTTF()->setDimensions(CCSize(193,16));
	// -- 默认提示文字
	pEditRegPass->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*请输入密码*/XorStr<0x2C,11,0x501ACE6F>("\xEB\xC6\xE4\xCB\xF8\xDA\xF1\xEF\xF6\xDE"+0x501ACE6F).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditRegPass->getTTF()->getTexture()/*,true*/);
	// -- 提示文字颜色
	pEditRegPass->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditRegPass->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditRegPass->InitCursor(0xFF,1,16);
	pEditRegPass->setTag(EDIT_REG_PASS);
	// -- 设置密码框模式
	pEditRegPass->setPasswordMode();
	pLabelReg->addChild(pEditRegPass);

	// 文字提示
	pLabelRegTips = CCLabelTTF::create();
	pLabelRegTips->setString(" ");
	pLabelRegTips->setColor(ccc3(255,255,255));
	pLabelRegTips->setOpacity(255);
	pLabelRegTips->ignoreAnchorPointForPosition(true);
	pLabelRegTips->setPosition(ccp(130,165));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelRegTips->getTexture()/*,true*/);
	pLabelReg->addChild(pLabelRegTips);

	// 返回登录
	pBtnRegBackLogin = SIX_Utility::GetInstance()->CreateButtonWithFileCell("reg_btn_login.png",2);
	if (pBtnRegBackLogin)
	{
		pBtnRegBackLogin->setDefaultTouchPriority(m_nPriority-1);
		pBtnRegBackLogin->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		pBtnRegBackLogin->setPosition(ccp(122,80));
		pBtnRegBackLogin->setTag(BTN_BACKLOGIN);
		pBtnRegBackLogin->setVisible(false);
		pLabelReg->addChild(pBtnRegBackLogin);
	}

	// 注册帐号
	pBtnRegReg = SIX_Utility::GetInstance()->CreateButtonWithFileCell("reg_btn_reg.png",2);
	if (pBtnRegReg)
	{
		pBtnRegReg->setDefaultTouchPriority(m_nPriority-1);
		pBtnRegReg->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		pBtnRegReg->setPosition(ccp(275,80));
		pBtnRegReg->setTag(BTN_REGISTER);
		pBtnRegReg->setVisible(false);
		pLabelReg->addChild(pBtnRegReg);
	}
}

void SIX_LoginPanelSG::DoSwitchIMEFocus()
{
	if (checkStatus==BTN_BACKLOGIN || checkStatus==BTN_SUBMIT || checkStatus==0)
	{
		if (pEditLoginName->IsAttachWithIME())
		{
			pEditLoginName->detachWithIME();
			pEditLoginPass->attachWithIME();
		}
		else
		{
			pEditLoginName->attachWithIME();
			pEditLoginPass->detachWithIME();
		}
	}
	else if (checkStatus!=BTN_GETPASS)
	{
		if (pEditRegName->IsAttachWithIME())
		{
			pEditRegName->detachWithIME();
			pEditRegPass->attachWithIME();
		}
		else
		{
			pEditRegName->attachWithIME();
			pEditRegPass->detachWithIME();
		}
	}
}

bool SIX_LoginPanelSG::onTextFieldAttachWithIME(SIX_EditBox * pSender)
{
	switch (pSender->getTag())
	{
	case EDIT_LOGIN_NAME:
		{
			break;
		}
	case EDIT_LOGIN_PASS:
		{
			break;
		}
	case EDIT_REG_NAME:
		{
			break;
		}
	case EDIT_REG_PASS:
		{
			break;
		}
	}
	return true;
}

bool SIX_LoginPanelSG::onTextFieldDetachWithIME(SIX_EditBox * pSender)
{
	switch (pSender->getTag())
	{
	case EDIT_LOGIN_NAME:
		{
			break;
		}
	case EDIT_LOGIN_PASS:
		{
			break;
		}
	case EDIT_REG_NAME:
		{
			break;
		}
	case EDIT_REG_PASS:
		{
			break;
		}
	}
	return true;
}

void SIX_LoginPanelSG::OnTouchLogic(CCTouch *pTouch,int pEvent)
{
	SIX_EffectPopWnd::OnTouchLogic(pTouch,pEvent);

	switch (pEvent)
	{
	case CCTOUCHBEGAN:
		{
			if (checkStatus==BTN_BACKLOGIN || checkStatus==BTN_SUBMIT || checkStatus==0)
			{
				if (pEditLoginName)
					pEditLoginName->ccTouchBegan(pTouch,0);
				if (pEditLoginPass)
					pEditLoginPass->ccTouchBegan(pTouch,0);
			}
			else if (checkStatus!=BTN_GETPASS)
			{
				if (pEditRegName)
					pEditRegName->ccTouchBegan(pTouch,0);
				if (pEditRegPass)
					pEditRegPass->ccTouchBegan(pTouch,0);
			}
			break;
		}
	case CCTOUCHMOVED:
		{
			if (checkStatus==BTN_BACKLOGIN || checkStatus==BTN_SUBMIT || checkStatus==0)
			{
				if (pEditLoginName)
					pEditLoginName->ccTouchMoved(pTouch,0);
				if (pEditLoginPass)
					pEditLoginPass->ccTouchMoved(pTouch,0);
			}
			else if (checkStatus!=BTN_GETPASS)
			{
				if (pEditRegName)
					pEditRegName->ccTouchMoved(pTouch,0);
				if (pEditRegPass)
					pEditRegPass->ccTouchMoved(pTouch,0);
			}
			break;
		}
	case CCTOUCHENDED:
		{
			if (checkStatus==BTN_BACKLOGIN || checkStatus==BTN_SUBMIT || checkStatus==0)
			{
				if (pEditLoginName)
					pEditLoginName->ccTouchEnded(pTouch,0);
				if (pEditLoginPass)
					pEditLoginPass->ccTouchEnded(pTouch,0);
			}
			else if (checkStatus!=BTN_GETPASS)
			{
				if (pEditRegName)
					pEditRegName->ccTouchEnded(pTouch,0);
				if (pEditRegPass)
					pEditRegPass->ccTouchEnded(pTouch,0);
			}
			break;
		}
	case CCTOUCHCANCELLED:
		{
			if (checkStatus==BTN_BACKLOGIN || checkStatus==BTN_SUBMIT || checkStatus==0)
			{
				if (pEditLoginName)
					pEditLoginName->ccTouchCancelled(pTouch,0);
				if (pEditLoginPass)
					pEditLoginPass->ccTouchCancelled(pTouch,0);
			}
			else if (checkStatus!=BTN_GETPASS)
			{
				if (pEditRegName)
					pEditRegName->ccTouchCancelled(pTouch,0);
				if (pEditRegPass)
					pEditRegPass->ccTouchCancelled(pTouch,0);
			}
			break;
		}
	}
}

bool SIX_LoginPanelSG::OnBtn(CCObject* pObject,int tag)
{
	CCControlButton *pButton = dynamic_cast<CCControlButton*>(pObject);
	if (!pButton)
		return true;

	switch (pButton->getTag())
	{
	case BTN_GETPASS:
		{
			checkStatus = pButton->getTag();
			this->Show(false);
			break;
		}
	case BTN_GOTOREG:
		{
			checkStatus = pButton->getTag();
			this->Show(false);
			break;
		}
	case BTN_BACKLOGIN:
		{
			checkStatus = pButton->getTag();
			this->Show(false);
			break;
		}
	case BTN_REGISTER:
		{
			checkStatus = pButton->getTag();
			this->DoRegister();
			break;
		}
	}

	return true;
}

// 登录
bool SIX_LoginPanelSG::OnSubmit()
{
	checkStatus = BTN_SUBMIT;
	return DoLogin();
}

// 退出
bool SIX_LoginPanelSG::OnClose()
{
	checkStatus = 0;
	return true;
}

void SIX_LoginPanelSG::showLoginTips(const char *msg)
{
	if (!pLabelLoginTips)
		return;

	pLabelLoginTips->setString(SIX_Utility::GetInstance()->G2U(msg).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelLoginTips->getTexture()/*,true*/);
}

void SIX_LoginPanelSG::showRegTips(const char *msg)
{
	if (!pLabelRegTips)
		return;

	pLabelRegTips->setString(SIX_Utility::GetInstance()->G2U(msg).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelRegTips->getTexture()/*,true*/);
}

void SIX_LoginPanelSG::DoEnter()
{
	if (isVisible()==false)
		return;
	if (checkStatus==BTN_BACKLOGIN || checkStatus==BTN_SUBMIT || checkStatus==0)
	{
		if (pEditLoginName)
			pEditLoginName->attachWithIME();
	}
	else if (checkStatus!=BTN_GETPASS)
	{
		if (pEditRegName)
			pEditRegName->attachWithIME();
	}
}

void SIX_LoginPanelSG::OnInputDone(CCLayer *pLayer,const char *text)
{
#ifdef WIN32
	SIX_EditBox *pThis = (SIX_EditBox*)pLayer;
	if (!pThis || !pThis->getParent())
		return;
	pThis->getTTF()->detachWithIME();
#endif
}

bool SIX_LoginPanelSG::DoLogin()
{
	this->DoLockPanel(true);

	CCString *pName = 0;
	CCString *pPass = 0;
	char md5Dst[33] = {0};
	ERROR_INFO err = ERROR_NONE;
	
	pName = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditLoginName->getTTF()->getString());
	// 用户名不能为空
	if (!pName->length())
	{
		this->showLoginTips(/*用户名不能为空！*/XorStr<0xF2,17,0xE41E31E4>("\x21\x30\x4F\x52\x35\x0C\x4A\x42\x3E\x27\x32\x57\x41\x2A\xA3\xA0"+0xE41E31E4).s);
		pEditLoginName->attachWithIME();
		goto clean;
	}

	pPass = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditLoginPass->getTTF()->getString());
	// 密码不能为空
	if (!pPass->length())
	{
		this->showLoginTips(/*密码不能为空！*/XorStr<0x23,15,0x7C58FD91>("\xE0\xF8\xE7\xCD\x95\x93\xED\xF6\xE5\x86\x92\xFB\x8C\x91"+0x7C58FD91).s);
		pEditLoginPass->attachWithIME();
		goto clean;
	}

	// 正常流程开始
	this->showLoginTips(/*正在登录 ...*/XorStr<0x82,13,0xA48FCE3D>("\x57\x7E\x50\x5F\x33\x40\x4A\x35\xAA\xA5\xA2\xA3"+0xA48FCE3D).s);
	pEditLoginName->detachWithIME();
	pEditLoginPass->detachWithIME();

	err = SIX_GlobalMgr::GetInstance()->GetFS()->GetMicroEncryptAndDecrypt()->HashByMD5((char*)(pPass->getCString()),pPass->length(),md5Dst,false);
	if (err!=ERROR_NONE)
	{
		SIXLog("pName[%s].pPass[%s].md5Dst[%s]",pName->getCString(),pPass->getCString(),md5Dst);
		this->showLoginTips(/*用户登录信息异常*/XorStr<0x66,17,0x6801096D>("\xB5\xA4\xD3\xCE\xDF\xAC\xAE\xD1\xBE\xAA\xBF\xD3\xA0\x9F\xC7\xD6"+0x6801096D).s);
		goto clean;
	}

	// save it
	SIX_PlayerMgr::GetInstance()->setMyUserInfo((char*)pName->getCString(),md5Dst);

	// 请求登录服务器，获取房间列表
	SIX_ClientLogin::GetInstance()->Connect(/*false*/);

	return false;
clean:
	this->DoLockPanel(false);
	return false;
}

bool SIX_LoginPanelSG::DoRegister()
{
	this->DoLockPanel(true);

	CCString *pName = 0;
	CCString *pPass = 0;
	char md5Dst[33] = {0};
	ERROR_INFO err = ERROR_NONE;
	
	pName = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditRegName->getTTF()->getString());
	// 用户名不能为空
	if (!pName->length())
	{
		this->showRegTips(/*用户名不能为空！*/XorStr<0xF2,17,0xE41E31E4>("\x21\x30\x4F\x52\x35\x0C\x4A\x42\x3E\x27\x32\x57\x41\x2A\xA3\xA0"+0xE41E31E4).s);
		pEditRegName->attachWithIME();
		goto clean;
	}

	pPass = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditRegPass->getTTF()->getString());
	// 密码不能为空
	if (!pPass->length())
	{
		this->showRegTips(/*密码不能为空！*/XorStr<0x23,15,0x7C58FD91>("\xE0\xF8\xE7\xCD\x95\x93\xED\xF6\xE5\x86\x92\xFB\x8C\x91"+0x7C58FD91).s);
		pEditRegPass->attachWithIME();
		goto clean;
	}

	// 正常流程开始
	this->showRegTips(/*正在注册 ...*/XorStr<0x51,13,0xB5196A6B>("\x84\xAF\x87\x8E\x82\xF4\xE5\xB9\x79\x74\x75\x72"+0xB5196A6B).s);
	pEditRegName->detachWithIME();
	pEditRegPass->detachWithIME();

	err = SIX_GlobalMgr::GetInstance()->GetFS()->GetMicroEncryptAndDecrypt()->HashByMD5((char*)(pPass->getCString()),pPass->length(),md5Dst,false);
	if (err!=ERROR_NONE)
	{
		SIXLog("pName[%s].pPass[%s].md5Dst[%s]",pName->getCString(),pPass->getCString(),md5Dst);
		this->showRegTips(/*用户登录信息异常*/XorStr<0x66,17,0x6801096D>("\xB5\xA4\xD3\xCE\xDF\xAC\xAE\xD1\xBE\xAA\xBF\xD3\xA0\x9F\xC7\xD6"+0x6801096D).s);
		goto clean;
	}

	// save it
	SIX_PlayerMgr::GetInstance()->setMyUserInfo((char*)pName->getCString(),md5Dst);

	// 请求登录服务器，获取房间列表
	SIX_ClientLogin::GetInstance()->Connect();

	return false;
clean:
	this->DoLockPanel(false);
	return false;
}

void SIX_LoginPanelSG::DoLockPanel(bool lock)
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

	if (pEditLoginName)
	{
		pEditLoginName->setTouchEnabled(!lock);
	}
	if (pEditLoginPass)
	{
		pEditLoginPass->setTouchEnabled(!lock);
	}
	if (pEditRegName)
	{
		pEditRegName->setTouchEnabled(!lock);
	}
	if (pEditRegPass)
	{
		pEditRegPass->setTouchEnabled(!lock);
	}

	if (pBtnGetPass)
	{
		pBtnGetPass->setEnabled(!lock);
		pBtnGetPass->setTouchEnabled(!lock);
	}
	if (pBtnLoginReg)
	{
		pBtnLoginReg->setEnabled(!lock);
		pBtnLoginReg->setTouchEnabled(!lock);
	}
	if (pBtnRegBackLogin)
	{
		pBtnRegBackLogin->setEnabled(!lock);
		pBtnRegBackLogin->setTouchEnabled(!lock);
	}
	if (pBtnRegReg)
	{
		pBtnRegReg->setEnabled(!lock);
		pBtnRegReg->setTouchEnabled(!lock);
	}
}

void SIX_LoginPanelSG::DoShowLogin(bool bShow)
{
	if (pLabelLogin)
		pLabelLogin->setVisible(bShow);
	if (pLabelReset)
		pLabelReset->setVisible(!bShow);
	if (pLabelReg)
		pLabelReg->setVisible(!bShow);
	if (pLabelLoginTips)
	{
		pLabelLoginTips->setVisible(bShow);
		pLabelLoginTips->setString("");
	}
	if (pLabelRegTips)
	{
		pLabelRegTips->setVisible(!bShow);
		pLabelRegTips->setString("");
	}
	DoShowEditBox(pEditLoginName,bShow);
	DoShowEditBox(pEditLoginPass,bShow);
	DoShowEditBox(pEditRegName,!bShow);
	DoShowEditBox(pEditRegPass,!bShow);
	if (GetBtnSubmit())
		GetBtnSubmit()->setVisible(bShow);
	if (pBtnResetBackLogin)
		pBtnResetBackLogin->setVisible(!bShow);
	if (pBtnRegBackLogin)
		pBtnRegBackLogin->setVisible(!bShow);
	if (pBtnRegReg)
		pBtnRegReg->setVisible(!bShow);
}

void SIX_LoginPanelSG::DoShowReset(bool bShow)
{
	if (pLabelLogin)
		pLabelLogin->setVisible(!bShow);
	if (pLabelReset)
		pLabelReset->setVisible(bShow);
	if (pLabelReg)
		pLabelReg->setVisible(!bShow);
	if (pLabelLoginTips)
	{
		pLabelLoginTips->setVisible(!bShow);
		pLabelLoginTips->setString("");
	}
	if (pLabelRegTips)
	{
		pLabelRegTips->setVisible(!bShow);
		pLabelRegTips->setString("");
	}
	DoShowEditBox(pEditLoginName,!bShow);
	DoShowEditBox(pEditLoginPass,!bShow);
	DoShowEditBox(pEditRegName,!bShow);
	DoShowEditBox(pEditRegPass,!bShow);
	if (GetBtnSubmit())
		GetBtnSubmit()->setVisible(!bShow);
	if (pBtnResetBackLogin)
		pBtnResetBackLogin->setVisible(bShow);
	if (pBtnRegBackLogin)
		pBtnRegBackLogin->setVisible(!bShow);
	if (pBtnRegReg)
		pBtnRegReg->setVisible(!bShow);
}

void SIX_LoginPanelSG::DoShowReg(bool bShow)
{
	if (pLabelLogin)
		pLabelLogin->setVisible(!bShow);
	if (pLabelReset)
		pLabelReset->setVisible(!bShow);
	if (pLabelReg)
		pLabelReg->setVisible(bShow);
	if (pLabelLoginTips)
	{
		pLabelLoginTips->setVisible(!bShow);
		pLabelLoginTips->setString("");
	}
	if (pLabelRegTips)
	{
		pLabelRegTips->setVisible(bShow);
		pLabelRegTips->setString("");
	}
	DoShowEditBox(pEditLoginName,!bShow);
	DoShowEditBox(pEditLoginPass,!bShow);
	DoShowEditBox(pEditRegName,bShow);
	DoShowEditBox(pEditRegPass,bShow);
	if (GetBtnSubmit())
		GetBtnSubmit()->setVisible(!bShow);
	if (pBtnResetBackLogin)
		pBtnResetBackLogin->setVisible(!bShow);
	if (pBtnRegBackLogin)
		pBtnRegBackLogin->setVisible(bShow);
	if (pBtnRegReg)
		pBtnRegReg->setVisible(bShow);
}

void SIX_LoginPanelSG::DoShowEditBox(SIX_EditBox *pEditBox,bool bShow)
{
	if (!pEditBox)
		return;

	pEditBox->setVisible(bShow);
	pEditBox->setTouchEnabled(bShow);
	if (pEditBox->getTTF())
		pEditBox->getTTF()->setString("");
	if (!bShow)
		pEditBox->detachWithIME();
}

void SIX_LoginPanelSG::onHideFinished()
{
	//SIXLog("checkStatus=%d",checkStatus);
	if (!checkStatus)
		return;

	switch (checkStatus)
	{
	case BTN_GETPASS:
		{
			this->DoShowReset();
			break;
		}
	case BTN_GOTOREG:
		{
			this->DoShowReg();
			break;
		}
	case BTN_BACKLOGIN:
		{
			this->DoShowLogin();
			break;
		}
	case BTN_SUBMIT:
	case BTN_REGISTER:
		{
			//pSceneLogin->DoChangeScene();
			return;
		}
	}

	this->Show();
}