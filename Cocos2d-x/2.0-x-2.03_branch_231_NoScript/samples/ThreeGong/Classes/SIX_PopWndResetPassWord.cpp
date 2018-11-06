#include "SIX_PopWndResetPassWord.h"

SIX_PopWndResetPassWord::~SIX_PopWndResetPassWord()
{
	CC_SAFE_RELEASE(pEditPassOld);
	CC_SAFE_RELEASE(pEditPassNew);
}

SIX_PopWndResetPassWord *SIX_PopWndResetPassWord::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset,MOVABLE_TYPE showType,MOVABLE_TYPE hideType,bool bSeqExec)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	if (0.0001 > x && 0.0001 > y)
	{
		CCSize szWind = CCDirector::sharedDirector()->getWinSize();
		x = (szWind.width - width) / 2;
		y = (szWind.height - height) / 2;
	}

	SIX_PopWndResetPassWord *pResetPassWord = new SIX_PopWndResetPassWord();
	if (pResetPassWord && pResetPassWord->init())
	{
		pResetPassWord->initWithColor(color,width,height);
		pResetPassWord->setPosition(x,y);
		pResetPassWord->setRedrawBorder(false);
		pResetPassWord->setTouchEnabled(true);
		pResetPassWord->m_ForbiddenTouch = true;
		pResetPassWord->m_bCloseThenCleanup = false;
		pResetPassWord->setShakeOffset(shakeOffset);
		pResetPassWord->setShowType(showType);
		pResetPassWord->setHideType(hideType);
		pResetPassWord->setSeqExec(bSeqExec);
		pResetPassWord->setObjName("SIX_PopWndSetting");
	}
	return pResetPassWord;
}

bool SIX_PopWndResetPassWord::init()
{
	if (!SIX_EffectPopWnd::init())
		return false;
	pEditPassOld = pEditPassNew = 0;
	pLabelTips = 0;
	return true;
}

void SIX_PopWndResetPassWord::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	// 输入框背景
	CCSprite *pSprEdit = CCSprite::create("edit.png",CCRect(0,0,384,135));
	if (pSprEdit)
	{
		pSprEdit->ignoreAnchorPointForPosition(true);
		pSprEdit->setPosition(ccp(122,185));
		this->addChild(pSprEdit);
	}

	// 文字提示
	CCLabelTTF *pLabelTitle = CCLabelTTF::create();
	pLabelTitle->setString(SIX_Utility::GetInstance()->G2U(/*修改密码*/XorStr<0x2B,9,0xFD974A9F>("\xFB\xF2\x95\xEA\xEC\xEC\xF3\xD9"+0xFD974A9F).s).c_str());
	pLabelTitle->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelTitle->setFontSize(30);
	pLabelTitle->setColor(ccc3(228,178,91));
	pLabelTitle->setOpacity(255);
	pLabelTitle->ignoreAnchorPointForPosition(true);
	pLabelTitle->setPosition(ccp(255,370));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTitle->getTexture(),true);
	this->addChild(pLabelTitle);

	// 原密码输入框
	pEditPassOld = new SIX_EditBox();
	pEditPassOld->setPosition(ccp(130,270));
	pEditPassOld->setInputTextMaxCount(33);
	pEditPassOld->setContentSize(CCSize(360,35));
	pEditPassOld->getTTF()->setPosition(ccp(5,10));
	pEditPassOld->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditPassOld->getTTF()->setScissorSize(CCSize(350,35));
	// -- 默认提示文字
	pEditPassOld->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*原密码*/XorStr<0x68,7,0x8FF80F08>("\xBC\xC4\xA9\xB7\xAE\x86"+0x8FF80F08).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditPassOld->getTTF()->getTexture(),true);
	// -- 提示文字颜色
	pEditPassOld->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditPassOld->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditPassOld->InitCursor(0xFF,1,16);
	pEditPassOld->setTag(EDIT_PASS_OLD);
	this->addChild(pEditPassOld);

	// 新密码输入框
	pEditPassNew = new SIX_EditBox();
	pEditPassNew->setPosition(ccp(130,200));
	pEditPassNew->setInputTextMaxCount(33);
	pEditPassNew->setContentSize(CCSize(360,35));
	pEditPassNew->getTTF()->setPosition(ccp(5,10));
	pEditPassNew->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditPassNew->getTTF()->setScissorSize(CCSize(350,35));
	// -- 默认提示文字
	pEditPassNew->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*新密码*/XorStr<0x57,7,0x21B6C714>("\x87\x9A\x9A\x86\x99\xB7"+0x21B6C714).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditPassNew->getTTF()->getTexture(),true);
	// -- 提示文字颜色
	pEditPassNew->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditPassNew->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditPassNew->InitCursor(0xFF,1,16);
	pEditPassNew->setTag(EDIT_PASS_NEW);
	// -- 设置密码框模式
	//pEditPassNew->setPasswordMode();
	this->addChild(pEditPassNew);

	// 文字提示
	pLabelTips = CCLabelTTF::create();
	pLabelTips->setString(" ");
	pLabelTips->setColor(ccc3(255,255,255));
	pLabelTips->setOpacity(255);
	pLabelTips->ignoreAnchorPointForPosition(true);
	pLabelTips->setPosition(ccp(130,165));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture(),true);
	this->addChild(pLabelTips);
}

void SIX_PopWndResetPassWord::DoSwitchIMEFocus()
{
	if (pEditPassOld->IsAttachWithIME())
	{
		pEditPassOld->detachWithIME();
		pEditPassNew->attachWithIME();
	}
	else
	{
		pEditPassOld->attachWithIME();
		pEditPassNew->detachWithIME();
	}
}

bool SIX_PopWndResetPassWord::OnSubmit()
{
	return DoResetPassword();
}

bool SIX_PopWndResetPassWord::DoResetPassword()
{
	this->DoLockPanel(true);

	CCString *pPassOld = 0;
	CCString *pPassNew = 0;
	char md5Dst[33] = {0};
	char md5NewDst[33] = {0};
	ERROR_INFO err = ERROR_NONE;
	
	pPassOld = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditPassOld->getTTF()->getString());
	// 原密码不能为空
	if (!pPassOld->length())
	{
		this->showTips(/*原密码不能为空！*/XorStr<0x42,17,0x991412F8>("\x96\xEE\x87\x99\x84\xAC\xFA\xF2\x8E\x97\x82\xE7\xF1\x9A\xF3\xF0"+0x991412F8).s);
		pEditPassOld->attachWithIME();
		goto clean;
	}

	pPassNew = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditPassNew->getTTF()->getString());
	// 密码不能为空
	if (!pPassNew->length())
	{
		this->showTips(/*新密码不能为空！*/XorStr<0xEC,17,0x582928CB>("\x3C\x2F\x2D\x33\x32\x1A\x40\x48\x30\x29\x38\x5D\x47\x2C\x59\x5A"+0x582928CB).s);
		pEditPassNew->attachWithIME();
		goto clean;
	}

	// 正常流程开始
	this->showTips(/*正在修改密码 ...*/XorStr<0x28,17,0x98C5B6A7>("\xFD\xD4\xFE\xF1\xFC\xF3\x96\xEB\xF3\xED\xF0\xD8\x14\x1B\x18\x19"+0x98C5B6A7).s);
	pEditPassOld->detachWithIME();
	pEditPassNew->detachWithIME();

	err = SIX_GlobalMgr::GetInstance()->GetFS()->GetMicroEncryptAndDecrypt()->HashByMD5((char*)(pPassOld->getCString()),pPassOld->length(),md5Dst,false);
	if (err!=ERROR_NONE)
	{
		SIXLog("pPassOld[%s].md5Dst[%s]",pPassOld->getCString(),md5Dst);
		this->showTips(/*原密码异常！*/XorStr<0xDA,13,0x0487AF10>("\x0E\x76\x1F\x01\x1C\x34\x32\x0D\x51\x40\x47\x44"+0x0487AF10).s);
		goto clean;
	}

	err = SIX_GlobalMgr::GetInstance()->GetFS()->GetMicroEncryptAndDecrypt()->HashByMD5((char*)(pPassNew->getCString()),pPassNew->length(),md5NewDst,false);
	if (err!=ERROR_NONE)
	{
		SIXLog("pPassNew[%s].md5NewDst[%s]",pPassNew->getCString(),md5NewDst);
		this->showTips(/*新密码异常！*/XorStr<0x70,13,0xE9B32512>("\xA0\xB3\xB1\xAF\xB6\x9E\xA4\x9B\xCB\xDA\xD9\xDA"+0xE9B32512).s);
		goto clean;
	}

	SIXLog("pPassOld[%s].pPassNew[%s]",pPassOld,pPassNew);

	//// 连接服务器，提交修改密码请求
	//SIX_ClientLogin::GetInstance()->Connect(false);

	return false;
clean:
	this->DoLockPanel(false);
	return false;
}

void SIX_PopWndResetPassWord::OnInputDone(CCLayer *pLayer,const char *text)
{
#ifdef WIN32
	SIX_EditBox *pThis = (SIX_EditBox*)pLayer;
	if (!pThis || !pThis->getParent())
		return;
	pThis->getTTF()->detachWithIME();
#endif
}

void SIX_PopWndResetPassWord::showTips(const char *msg)
{
	if (!pLabelTips)
		return;

	pLabelTips->setString(SIX_Utility::GetInstance()->G2U(msg).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture(),true);
}

void SIX_PopWndResetPassWord::DoLockPanel(bool lock)
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

	if (pEditPassOld)
	{
		pEditPassOld->setTouchEnabled(!lock);
	}
	if (pEditPassNew)
	{
		pEditPassNew->setTouchEnabled(!lock);
	}
}