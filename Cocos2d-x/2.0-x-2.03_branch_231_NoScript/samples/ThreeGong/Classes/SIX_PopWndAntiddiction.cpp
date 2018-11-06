#include "SIX_PopWndAntiddiction.h"

SIX_PopWndAntiddiction::~SIX_PopWndAntiddiction()
{
	CC_SAFE_RELEASE(pEditRealName);
	CC_SAFE_RELEASE(pEditIDCard);
}

SIX_PopWndAntiddiction *SIX_PopWndAntiddiction::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset,MOVABLE_TYPE showType,MOVABLE_TYPE hideType,bool bSeqExec)
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

	SIX_PopWndAntiddiction *pAntiddiction = new SIX_PopWndAntiddiction();
	if (pAntiddiction && pAntiddiction->init())
	{
		pAntiddiction->initWithColor(color,width,height);
		pAntiddiction->setPosition(x,y);
		pAntiddiction->setRedrawBorder(false);
		pAntiddiction->setTouchEnabled(true);
		pAntiddiction->m_ForbiddenTouch = true;
		pAntiddiction->m_bCloseThenCleanup = false;
		pAntiddiction->setShakeOffset(shakeOffset);
		pAntiddiction->setShowType(showType);
		pAntiddiction->setHideType(hideType);
		pAntiddiction->setSeqExec(bSeqExec);
		pAntiddiction->setObjName("SIX_PopWndAntiddiction");
	}
	return pAntiddiction;
}

bool SIX_PopWndAntiddiction::init()
{
	if (!SIX_EffectPopWnd::init())
		return false;
	pEditRealName = pEditIDCard = 0;
	pLabelTips = 0;
	return true;
}

void SIX_PopWndAntiddiction::onEnterTransitionDidFinish()
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
	pLabelTitle->setString(SIX_Utility::GetInstance()->G2U(/*防沉迷验证*/XorStr<0x64,11,0xAF5E9165>("\xD3\xA5\xD5\xA6\xAB\xBD\xBB\x82\xBA\xC9"+0xAF5E9165).s).c_str());
	pLabelTitle->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelTitle->setFontSize(30);
	pLabelTitle->setColor(ccc3(228,178,91));
	pLabelTitle->setOpacity(255);
	pLabelTitle->ignoreAnchorPointForPosition(true);
	pLabelTitle->setPosition(ccp(255,370));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTitle->getTexture(),true);
	this->addChild(pLabelTitle);

	// 真实姓名输入框
	pEditRealName = new SIX_EditBox();
	pEditRealName->setPosition(ccp(130,270));
	pEditRealName->setInputTextMaxCount(33);
	pEditRealName->setContentSize(CCSize(360,35));
	pEditRealName->getTTF()->setPosition(ccp(5,10));
	pEditRealName->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditRealName->getTTF()->setScissorSize(CCSize(350,35));
	// -- 默认提示文字
	pEditRealName->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*真实姓名*/XorStr<0x70,9,0xBC75247B>("\xA5\x97\xB8\xC6\xA4\xA0\xB5\x8C"+0xBC75247B).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditRealName->getTTF()->getTexture(),true);
	// -- 提示文字颜色
	pEditRealName->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditRealName->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditRealName->InitCursor(0xFF,1,16);
	pEditRealName->setTag(EDIT_REALNAME);
	this->addChild(pEditRealName);

	// 身份证号码输入框
	pEditIDCard = new SIX_EditBox();
	pEditIDCard->setPosition(ccp(130,200));
	pEditIDCard->setInputTextMaxCount(33);
	pEditIDCard->setContentSize(CCSize(360,35));
	pEditIDCard->getTTF()->setPosition(ccp(5,10));
	pEditIDCard->getTTF()->setFontSize(12);
	// -- 设置最大裁剪尺寸
	pEditIDCard->getTTF()->setScissorSize(CCSize(350,35));
	// -- 默认提示文字
	pEditIDCard->getTTF()->setPlaceHolder(SIX_Utility::GetInstance()->G2U(/*身份证号码*/XorStr<0x8D,11,0xA8B0FF94>("\x44\x63\x38\x4D\x47\x36\x29\x51\x57\x7D"+0xA8B0FF94).s).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pEditIDCard->getTTF()->getTexture(),true);
	// -- 提示文字颜色
	pEditIDCard->getTTF()->setColorSpaceHolder(ccc3(128,128,128));
	// -- 输入文字颜色
	pEditIDCard->getTTF()->setColor(ccc3(0,0,0));
	// -- 输入光标(支持rgba)
	pEditIDCard->InitCursor(0xFF,1,16);
	pEditIDCard->setTag(EDIT_IDCARD);
	// -- 设置密码框模式
	//pEditIDCard->setPasswordMode();
	this->addChild(pEditIDCard);

	// 文字提示
	pLabelTips = CCLabelTTF::create();
	pLabelTips->setString(" ");
	pLabelTips->setColor(ccc3(255,255,255));
	pLabelTips->setOpacity(255);
	pLabelTips->ignoreAnchorPointForPosition(true);
	pLabelTips->setPosition(ccp(130,165));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture(),true);
	this->addChild(pLabelTips);

	// 文字提示
	CCLabelTTF *pLabelDesc = CCLabelTTF::create();
	pLabelDesc->setString(SIX_Utility::GetInstance()->G2U(/*为保障您的游戏利益，请准确填写防沉迷身份验证信息！*/XorStr<0x55,51,0x2E78C743>("\x9B\xFC\xE6\xFB\x8C\x95\x9F\xA6\xE8\x9A\x8C\xAE\xAE\xD5\xA3\x9F\xB7\x80\xC4\xC4\xAE\x81\xBC\xD0\xA5\xD9\xA3\x9E\xA1\xC6\xC4\xB4\xC6\xB7\xB4\xAC\xB0\x97\xCC\xA1\xAC\x97\xA9\x24\x51\x47\x4C\x26\x26\x27"+0x2E78C743).s).c_str());
	pLabelDesc->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
	pLabelDesc->setFontSize(18);
	pLabelDesc->setColor(ccc3(255,255,255));
	pLabelDesc->setOpacity(255);
	pLabelDesc->ignoreAnchorPointForPosition(true);
	pLabelDesc->setPosition(ccp(87,40));
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelDesc->getTexture(),true);
	this->addChild(pLabelDesc);
}

void SIX_PopWndAntiddiction::DoSwitchIMEFocus()
{
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

bool SIX_PopWndAntiddiction::OnSubmit()
{
	return DoAntiddiction();
}

bool SIX_PopWndAntiddiction::DoAntiddiction()
{
	this->DoLockPanel(true);

	CCString *pRealName = 0;
	CCString *pIDCard = 0;
	char md5Dst[33] = {0};
	char md5NewDst[33] = {0};
	ERROR_INFO err = ERROR_NONE;
	
	pRealName = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditRealName->getTTF()->getString());
	// 真实姓名不能为空
	if (!pRealName->length())
	{
		this->showTips(/*真实姓名不能为空！*/XorStr<0xFC,19,0x172B6F11>("\x29\x1B\x34\x4A\xD0\xD4\xC1\xF8\xB6\xBE\xC2\xDB\xC6\xA3\xB5\xDE\xAF\xAC"+0x172B6F11).s);
		pEditRealName->attachWithIME();
		goto clean;
	}

	pIDCard = CCString::createWithFormat(/*%s*/XorStr<0x65,3,0xFEA4929C>("\x40\x15"+0xFEA4929C).s,pEditIDCard->getTTF()->getString());
	// 身份证号码不能为空
	if (!pIDCard->length())
	{
		this->showTips(/*身份证号码不能为空！*/XorStr<0x3F,21,0x8311C732>("\xF6\xAD\xF6\x9F\x95\xE0\xFF\x83\x85\xA3\xFB\xF1\x8F\x90\x83\xE4\xF0\x85\xF2\xF3"+0x8311C732).s);
		pEditIDCard->attachWithIME();
		goto clean;
	}

	// 正常流程开始
	this->showTips(/*正在验证防沉迷信息 ...*/XorStr<0x78,23,0x7D439EF8>("\xAD\x84\xAE\xA1\xAD\x94\xA8\xDB\x37\x41\x31\x42\x47\x51\x56\x42\x47\x2B\xAA\xA5\xA2\xA3"+0x7D439EF8).s);
	pEditRealName->detachWithIME();
	pEditIDCard->detachWithIME();

	SIXLog("pRealName[%s].pIDCard[%s]",pRealName->getCString(),pIDCard->getCString());

	//// 连接服务器，提交修改密码请求
	//SIX_ClientLogin::GetInstance()->Connect(false);

	return false;
clean:
	this->DoLockPanel(false);
	return false;
}

void SIX_PopWndAntiddiction::OnInputDone(CCLayer *pLayer,const char *text)
{
#ifdef WIN32
	SIX_EditBox *pThis = (SIX_EditBox*)pLayer;
	if (!pThis || !pThis->getParent())
		return;
	pThis->getTTF()->detachWithIME();
#endif
}

void SIX_PopWndAntiddiction::showTips(const char *msg)
{
	if (!pLabelTips)
		return;

	pLabelTips->setString(SIX_Utility::GetInstance()->G2U(msg).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pLabelTips->getTexture(),true);
}

void SIX_PopWndAntiddiction::DoLockPanel(bool lock)
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

	if (pEditRealName)
	{
		pEditRealName->setTouchEnabled(!lock);
	}
	if (pEditIDCard)
	{
		pEditIDCard->setTouchEnabled(!lock);
	}
}