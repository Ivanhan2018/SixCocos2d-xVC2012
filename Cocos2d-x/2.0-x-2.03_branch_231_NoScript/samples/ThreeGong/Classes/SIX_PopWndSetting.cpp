#include "SIX_PopWndSetting.h"

SIX_PopWndSetting::~SIX_PopWndSetting()
{
	CC_SAFE_RELEASE(pPopResetPassWord);
	CC_SAFE_RELEASE(pPopAntiddiction);
}

SIX_PopWndSetting *SIX_PopWndSetting::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset,MOVABLE_TYPE showType,MOVABLE_TYPE hideType,bool bSeqExec)
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

	SIX_PopWndSetting *pSetting = new SIX_PopWndSetting();
	if (pSetting && pSetting->init())
	{
		pSetting->initWithColor(color,width,height);
		pSetting->setPosition(x,y);
		pSetting->setRedrawBorder(false);
		pSetting->setTouchEnabled(true);
		pSetting->m_ForbiddenTouch = true;
		pSetting->m_bCloseThenCleanup = false;
		pSetting->setShakeOffset(shakeOffset);
		pSetting->setShowType(showType);
		pSetting->setHideType(hideType);
		pSetting->setSeqExec(bSeqExec);
		pSetting->setObjName("SIX_PopWndSetting");
	}
	return pSetting;
}

bool SIX_PopWndSetting::init()
{
	if (!SIX_EffectPopWnd::init())
		return false;
	pScrollBarAudio = 0;
	pBtnAudioMute = 0;
	m_LastAudioRatio = 0.0f;
	pBtnRubCard = 0;
	pPopResetPassWord = 0;
	pPopAntiddiction = 0;
	return true;
}

void SIX_PopWndSetting::onEnterTransitionDidFinish()
{
	// 名称
	CCSprite *pTitle = CCSprite::create("pop_set_title.png");
	if (pTitle)
	{
		pTitle->setPosition(ccp(278,365));
		pTitle->ignoreAnchorPointForPosition(true);
		this->addChild(pTitle);
	}

	// 声音
	CCLabelTTF *pLabelSound = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(/*声　音*/XorStr<0xC1,7,0x8C35CB48>("\x08\x3B\x62\x65\x17\x32"+0x8C35CB48).s).c_str(),/*微软雅黑*/XorStr<0x87,9,0xCE86298F>("\x49\x2A\x41\x67\x5A\x49\x37\x54"+0xCE86298F).s,30);
	pLabelSound->ignoreAnchorPointForPosition(true);
	pLabelSound->setPosition(ccp(33,313));
	this->addChild(pLabelSound);

	// 音量
	if (!pScrollBarAudio)
	{
		CCScale9Sprite *bgSprite = CCScale9Sprite::create("pop_set_sound_bg.png");
		CCSprite *progressSprite = CCSprite::create("pop_set_sound_proc.png");
		CCScale9Sprite *thumbSprite = CCScale9Sprite::create("pop_set_sound_thumb.png");
		pScrollBarAudio = SIX_ScrollBar::create(
			bgSprite,CCSize(342,23),
			progressSprite,
			thumbSprite,
			0,
			0,
			0,
			CCSize(0,0),
			true
			);
		pScrollBarAudio->ignoreAnchorPointForPosition(true);
		pScrollBarAudio->setMinimumValue(0.0);
		pScrollBarAudio->setMaximumValue(1.0);
		//pScrollBarAudio->setValue(audioRatio);
		pScrollBarAudio->setValue(SIX_GlobalMgr::GetInstance()->GetMusicMgr()->m_BackgroundVolume);
		pScrollBarAudio->setDefaultTouchPriority(m_nPriority-1);
		pScrollBarAudio->setPosition(150,310);
		// 设置回调
		pScrollBarAudio->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::ScrollBarChanged),CCControlEventValueChanged);
		this->addChild(pScrollBarAudio);
	}

	// 音量禁音
	if (!pBtnAudioMute)
	{
		CCString *frameName = CCString::create("pop_set_sound.png");
		CCRect rc = CCRectZero;
		int IsMute = 0;
		if (SIX_GlobalMgr::GetInstance()->GetMusicMgr()->m_BackgroundVolume>0.0f)
		{
			rc = CCRect(0,0,60,52);
		}
		else
		{
			IsMute = 1;
			rc = CCRect(60,0,60,52);
		}
		CCScale9Sprite *pScale9Sprite = CCScale9Sprite::create(frameName->getCString(),rc);
		CC_SAFE_RELEASE(frameName);
		if (!pScale9Sprite)
			return;
		pBtnAudioMute = CCControlButton::create(pScale9Sprite);
		if (!pBtnAudioMute)
			return;
		pBtnAudioMute->setZoomFactor(1.0f);
		pBtnAudioMute->setPreferredSize(pScale9Sprite->getOriginalSize());
		pBtnAudioMute->ignoreAnchorPointForPosition(true);
		pBtnAudioMute->setPosition(ccp(512,308));
		pBtnAudioMute->setTag(AUDIO_MUTE);
		pBtnAudioMute->setUserData((void*)IsMute);
		pBtnAudioMute->setDefaultTouchPriority(m_nPriority-1);
		pBtnAudioMute->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::doEvents),32);
		this->addChild(pBtnAudioMute);
	}

	// 手动搓牌
	CCLabelTTF *pLabelRubCard = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(/*搓　牌*/XorStr<0x0D,7,0x3DDA6F9B>("\xB9\xE4\xAE\xB1\xD4\xD4"+0x3DDA6F9B).s).c_str(),/*微软雅黑*/XorStr<0x87,9,0xCE86298F>("\x49\x2A\x41\x67\x5A\x49\x37\x54"+0xCE86298F).s,30);
	pLabelRubCard->ignoreAnchorPointForPosition(true);
	pLabelRubCard->setPosition(ccp(33,253));
	this->addChild(pLabelRubCard);

	// 按钮
	if (!pBtnRubCard)
	{
		CCScale9Sprite *pScale9Sprite = CCScale9Sprite::create("pop_set_btn_rub_card.png",CCRect(0,0,125,39));
		if (pScale9Sprite)
		{
			pBtnRubCard = CCControlButton::create(pScale9Sprite);
			if (pBtnRubCard)
			{
				pBtnRubCard->setZoomFactor(1.0f);
				pBtnRubCard->setPreferredSize(pScale9Sprite->getOriginalSize());
				pBtnRubCard->ignoreAnchorPointForPosition(true);
				pBtnRubCard->setPosition(ccp(447,253));
				pBtnRubCard->setTag(RUB_CARD);
				pBtnRubCard->setUserData((void*)0);
				pBtnRubCard->setDefaultTouchPriority(m_nPriority-1);
				pBtnRubCard->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::doEvents),32);
				this->addChild(pBtnRubCard);
			}
		}
	}

	// 密码
	CCLabelTTF *pLabelResetPass = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(/*密　码*/XorStr<0x9D,7,0xC9F0AD4B>("\x5E\x42\x3E\x01\x63\x49"+0xC9F0AD4B).s).c_str(),/*微软雅黑*/XorStr<0x87,9,0xCE86298F>("\x49\x2A\x41\x67\x5A\x49\x37\x54"+0xCE86298F).s,30);
	pLabelResetPass->ignoreAnchorPointForPosition(true);
	pLabelResetPass->setPosition(ccp(33,178));
	this->addChild(pLabelResetPass);

	// 按钮
	CCControlButton *pBtnResetPass = SIX_Utility::GetInstance()->CreateButtonWithFileCell("pop_set_btn_resetpwd.png",2);
	if (pBtnResetPass)
	{
		pBtnResetPass->setZoomFactor(1.0f);
		pBtnResetPass->setPreferredSize(CCSize(189,53));
		pBtnResetPass->ignoreAnchorPointForPosition(true);
		pBtnResetPass->setPosition(ccp(384,173));
		pBtnResetPass->setTag(RESET_PASS);
		pBtnResetPass->setDefaultTouchPriority(m_nPriority-1);
		pBtnResetPass->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::doEvents),32);
		this->addChild(pBtnResetPass);
	}

	// 防沉迷
	CCLabelTTF *pLabelRealName = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(/*防沉迷*/XorStr<0x5D,7,0x17BEFAA4>("\xEA\x9E\xEC\xA1\xA2\xB6"+0x17BEFAA4).s).c_str(),/*微软雅黑*/XorStr<0x87,9,0xCE86298F>("\x49\x2A\x41\x67\x5A\x49\x37\x54"+0xCE86298F).s,30);
	pLabelRealName->ignoreAnchorPointForPosition(true);
	pLabelRealName->setPosition(ccp(33,107));
	this->addChild(pLabelRealName);

	// 按钮
	CCControlButton *pBtnRealName = SIX_Utility::CreateButtonWithFileCell("pop_set_btn_realname.png",2);
	if (pBtnRealName)
	{
		pBtnRealName->setZoomFactor(1.0f);
		pBtnRealName->setPreferredSize(CCSize(189,53));
		pBtnRealName->ignoreAnchorPointForPosition(true);
		pBtnRealName->setPosition(ccp(384,102));
		pBtnRealName->setTag(REAL_NAME);
		pBtnRealName->setDefaultTouchPriority(m_nPriority-1);
		pBtnRealName->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::doEvents),32);
		this->addChild(pBtnRealName);
	}

	// 帐号
	CCLabelTTF *pLabelLogOff = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(/*帐　号*/XorStr<0x3B,7,0x3914F528>("\xEE\xF6\x9C\x9F\x85\x85"+0x3914F528).s).c_str(),/*微软雅黑*/XorStr<0x87,9,0xCE86298F>("\x49\x2A\x41\x67\x5A\x49\x37\x54"+0xCE86298F).s,30);
	pLabelLogOff->ignoreAnchorPointForPosition(true);
	pLabelLogOff->setPosition(ccp(33,40));
	this->addChild(pLabelLogOff);

	// 按钮
	CCControlButton *pBtnLogOff = SIX_Utility::CreateButtonWithFileCell("pop_set_btn_logoff.png",2);
	if (pBtnLogOff)
	{
		pBtnLogOff->setZoomFactor(1.0f);
		pBtnLogOff->setPreferredSize(CCSize(189,53));
		pBtnLogOff->ignoreAnchorPointForPosition(true);
		pBtnLogOff->setPosition(ccp(384,35));
		pBtnLogOff->setTag(LOG_OFF);
		pBtnLogOff->setDefaultTouchPriority(m_nPriority-1);
		pBtnLogOff->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::doEvents),32);
		this->addChild(pBtnLogOff);
	}
}

// 滚动条回调
void SIX_PopWndSetting::ScrollBarChanged(CCObject *pSender,CCControlEvent controlEvent)
{
	SIX_ScrollBar* pScrollbar = (SIX_ScrollBar*)pSender;
	if (!pScrollbar)
		return;

	// 滚动条当前值
	float value = pScrollbar->getValue();
	//SIXLog("ScrollBarChanged.value=%.2f",value);

	// 音量
	if (pScrollbar->isEqual(pScrollBarAudio))
	{
		m_LastAudioRatio = value;
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->setBackgroundMusicVolume(value);
		// 刷新UI
		if (value==0.0f)
		{
			CCScale9Sprite *pSprite = CCScale9Sprite::create("pop_set_sound.png",CCRect(60,0,60,52));
			if (!pSprite)
				return;
			pBtnAudioMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
		}
		else
		{
			CCScale9Sprite *pSprite = CCScale9Sprite::create("pop_set_sound.png",CCRect(0,0,60,52));
			if (!pSprite)
				return;
			pBtnAudioMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);		
		}
	}
}

void SIX_PopWndSetting::doEvents(CCObject* pSender, CCControlEvent event)
{
	if (!pSender)
		return;

	CCControl *pControl = dynamic_cast<CCControl*>(pSender);
	if (!pControl)
		return;

	CCString *name = CCString::create(pControl->getObjName());
	int tag = pControl->getTag();
	SIXLog("SIX_PopWndSetting.doEvents.pSender[0x%08X][%s].event[%d].tag[%d].onCCControlEventTouchUpInside",pSender,name->getCString(),event,tag);
	CC_SAFE_RELEASE(name);

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
				// 音量
			case AUDIO_MUTE:
				{
					setAudioMuteOrNot();
					break;
				}
				// 搓牌
			case RUB_CARD:
				{
					setRubCardYesOrNot();
					break;
				}
				// 密码
			case RESET_PASS:
				{
					if (!pPopResetPassWord)
					{
						pPopResetPassWord = SIX_PopWndResetPassWord::Create(0.0,0.0,ccc4(0,0,0,0),627,423,50.0f,MOVABLE_TOP,MOVABLE_TOP,true);
						pPopResetPassWord->InitMask(ccc4(0,0,0,129));
						pPopResetPassWord->backgroundWithFile("box_bg.png");
						pPopResetPassWord->buttonSubmitWithFileCell("btn_submit.png",2);
						pPopResetPassWord->GetBtnSubmit()->setPosition(ccp(121,85));
						pPopResetPassWord->buttonCloseWithFileCell("btn_close.png",2);
						pPopResetPassWord->GetBtnClose()->setPosition(ccp(590,392));
						pPopResetPassWord->setAllowDragged(false);
					}
					pPopResetPassWord->Show();
					break;
				}
				// 防沉迷
			case REAL_NAME:
				{
					if (!pPopAntiddiction)
					{
						pPopAntiddiction = SIX_PopWndAntiddiction::Create(0.0,0.0,ccc4(0,0,0,0),627,423,50.0f,MOVABLE_TOP,MOVABLE_TOP,true);
						pPopAntiddiction->InitMask(ccc4(0,0,0,129));
						pPopAntiddiction->backgroundWithFile("box_bg.png");
						pPopAntiddiction->buttonSubmitWithFileCell("btn_verify.png",2);
						pPopAntiddiction->GetBtnSubmit()->setPosition(ccp(121,85));
						pPopAntiddiction->buttonCloseWithFileCell("btn_close.png",2);
						pPopAntiddiction->GetBtnClose()->setPosition(ccp(590,392));
						pPopAntiddiction->setAllowDragged(false);
					}
					pPopAntiddiction->Show();
					break;
				}
				// 退出
			case LOG_OFF:
				{
					// 要给玩家退出提示
					break;
				}
			}
			break;
		}
	}
}

void SIX_PopWndSetting::setAudioMuteOrNot()
{
	if (!pBtnAudioMute)
		return;
	int IsMute = (int)(pBtnAudioMute->getUserData());
	// 禁用
	if (IsMute==0)
	{
		m_LastAudioRatio = SIX_GlobalMgr::GetInstance()->GetMusicMgr()->m_BackgroundVolume;
		pScrollBarAudio->setValue(0.0f);
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->setBackgroundMusicVolume(0.0f);
		pBtnAudioMute->setUserData((void*)1);

		CCScale9Sprite *pSprite = CCScale9Sprite::create("pop_set_sound.png",CCRect(60,0,60,52));
		if (!pSprite)
			return;
		pBtnAudioMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
	}
	// 恢复
	else
	{
		if (m_LastAudioRatio==0.0f)
			m_LastAudioRatio = 0.5f;
		pScrollBarAudio->setValue(m_LastAudioRatio);
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->setBackgroundMusicVolume(m_LastAudioRatio);
		pBtnAudioMute->setUserData((void*)0);

		CCScale9Sprite *pSprite = CCScale9Sprite::create("pop_set_sound.png",CCRect(0,0,60,52));
		if (!pSprite)
			return;
		pBtnAudioMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
	}
}

void SIX_PopWndSetting::setRubCardYesOrNot()
{
	if (!pBtnRubCard)
		return;
	int IsOn = (int)(pBtnRubCard->getUserData());
	// 启用->禁用
	if (IsOn==0)
	{
		pBtnRubCard->setUserData((void*)1);

		CCScale9Sprite *pSprite = CCScale9Sprite::create("pop_set_btn_rub_card.png",CCRect(125,0,125,39));
		if (!pSprite)
			return;
		pBtnRubCard->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
	}
	// 禁用->启用
	else
	{
		pBtnRubCard->setUserData((void*)0);

		CCScale9Sprite *pSprite = CCScale9Sprite::create("pop_set_btn_rub_card.png",CCRect(0,0,125,39));
		if (!pSprite)
			return;
		pBtnRubCard->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
	}
}

#ifdef WIN32
int SIX_PopWndSetting::OnAccelerometerKeyHook( UINT message,WPARAM wParam,LPARAM lParam )
{
	//SIXLog("SIX_SceneLogin.OnAccelerometerKeyHook.MSG[%u].wParam[%u].lParam[%ul]",message,wParam,lParam);
	switch (message)
	{
	/*case WM_KEYDOWN:*/
	case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_TAB:
				{
					if (pPopResetPassWord && pPopResetPassWord->IsShow())
						pPopResetPassWord->DoSwitchIMEFocus();
					if (pPopAntiddiction && pPopAntiddiction->IsShow())
						pPopAntiddiction->DoSwitchIMEFocus();
					break;
				}
			case VK_RETURN:
				{
					if (pPopResetPassWord && pPopResetPassWord->IsShow())
						pPopResetPassWord->DoResetPassword();
					if (pPopAntiddiction && pPopAntiddiction->IsShow())
						pPopAntiddiction->DoAntiddiction();
					break;
				}
				break;
			}
		}
        break;
	}
	return 0;
}
#endif