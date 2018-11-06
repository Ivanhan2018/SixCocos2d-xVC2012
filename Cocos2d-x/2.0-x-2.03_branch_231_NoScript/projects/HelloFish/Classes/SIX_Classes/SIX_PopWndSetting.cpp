#include "SIX_PopWndSetting.h"

SIX_PopWndSetting::~SIX_PopWndSetting()
{
}

SIX_PopWndSetting *SIX_PopWndSetting::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
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
		pSetting->setRedrawBorder(bRedrawBorder);
		pSetting->setTouchEnabled(true);
		pSetting->m_ForbiddenTouch = true;
		pSetting->m_bCloseThenCleanup = bCloseThenCleanup;
		pSetting->setObjName("SIX_PopWndSetting");
	}
	return pSetting;
}

bool SIX_PopWndSetting::init()
{
	if (!SIX_PopWnd::init())
		return false;
	pScrollBarAudio = pScrollBarEffect = 0;
	pBtnAudioMute = pBtnEffectMute = 0;
	m_LastAudioRatio = m_LastEffectRatio = 0.0f;
	return true;
}

void SIX_PopWndSetting::onEnterTransitionDidFinish()
{
	// 音量
	if (!pScrollBarAudio)
	{
		//float audioRatio = SIX_GlobalMgr::GetInstance()->GetMusicMgr()->getBackgroundMusicVolume();
		CCScale9Sprite *bgSprite = CCScale9Sprite::create("Common/Setting/progress_bg.png");
		CCSprite *progressSprite = CCSprite::create("Common/Setting/progress.png");
		CCScale9Sprite *thumbSprite = CCScale9Sprite::create("Common/Setting/volume.png",CCRect(0,0,41,46));
		CCScale9Sprite *thumbSelectSprite = CCScale9Sprite::create("Common/Setting/volume.png",CCRect(41,0,41,46));
		pScrollBarAudio = SIX_ScrollBar::create(
			bgSprite,CCSize(236,25),
			progressSprite,
			thumbSprite,
			thumbSelectSprite,
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
		pScrollBarAudio->setPosition(135,135);
		// 设置回调
		pScrollBarAudio->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::ScrollBarChanged),CCControlEventValueChanged);
		this->addChild(pScrollBarAudio);
	}

	// 音效
	if (!pScrollBarEffect)
	{
		//float effectRatio = SIX_GlobalMgr::GetInstance()->GetMusicMgr()->getEffectsVolume();
		CCScale9Sprite *bgSprite = CCScale9Sprite::create("Common/Setting/progress_bg.png");
		CCSprite *progressSprite = CCSprite::create("Common/Setting/progress.png");
		CCScale9Sprite *thumbSprite = CCScale9Sprite::create("Common/Setting/volume.png",CCRect(0,0,41,46));
		CCScale9Sprite *thumbSelectSprite = CCScale9Sprite::create("Common/Setting/volume.png",CCRect(41,0,41,46));
		pScrollBarEffect = SIX_ScrollBar::create(
			bgSprite,CCSize(236,25),
			progressSprite,
			thumbSprite,
			thumbSelectSprite,
			0,
			0,
			CCSize(0,0),
			true
			);
		pScrollBarEffect->ignoreAnchorPointForPosition(true);
		pScrollBarEffect->setMinimumValue(0.0);
		pScrollBarEffect->setMaximumValue(1.0);
		//pScrollBarEffect->setValue(effectRatio);
		pScrollBarEffect->setValue(SIX_GlobalMgr::GetInstance()->GetMusicMgr()->m_EffectVolume);
		pScrollBarEffect->setDefaultTouchPriority(m_nPriority-1);
		pScrollBarEffect->setPosition(135,75);
		// 设置回调
		pScrollBarEffect->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::ScrollBarChanged),CCControlEventValueChanged);
		this->addChild(pScrollBarEffect);
	}

	// 音量禁音
	if (!pBtnAudioMute)
	{
		//pBtnAudioMute = SIX_Utility::GetInstance()->CreateButtonWithFrameName("audio_on.png");
		CCString *frameName = CCString::create("Common/Setting/audio.png");
		CCRect rc = CCRectZero;
		int IsMute = 0;
		if (SIX_GlobalMgr::GetInstance()->GetMusicMgr()->m_BackgroundVolume>0.0f)
		{
			rc = CCRect(0,0,31,35);
		}
		else
		{
			IsMute = 1;
			rc = CCRect(31,0,31,35);
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
		pBtnAudioMute->setPosition(ccp(385,140));
		pBtnAudioMute->setTag(AUDIO_MUTE);
		pBtnAudioMute->setUserData((void*)IsMute);
		pBtnAudioMute->setDefaultTouchPriority(m_nPriority-1);
		pBtnAudioMute->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::doEvents),32);
		this->addChild(pBtnAudioMute);
	}

	// 音效禁音
	if (!pBtnEffectMute)
	{
		//pBtnEffectMute = SIX_Utility::GetInstance()->CreateButtonWithFrameName("effect_on.png");
		CCString *frameName = CCString::create("Common/Setting/effect.png");
		CCRect rc = CCRectZero;
		int IsMute = 0;
		if (SIX_GlobalMgr::GetInstance()->GetMusicMgr()->m_EffectVolume>0.0f)
		{
			rc = CCRect(0,0,30,35);
		}
		else
		{
			IsMute = 1;
			rc = CCRect(30,0,30,35);
		}
		CCScale9Sprite *pScale9Sprite = CCScale9Sprite::create(frameName->getCString(),rc);
		CC_SAFE_RELEASE(frameName);
		if (!pScale9Sprite)
			return;
		pBtnEffectMute = CCControlButton::create(pScale9Sprite);
		if (!pBtnEffectMute)
			return;
		pBtnEffectMute->setZoomFactor(1.0f);
		pBtnEffectMute->setPreferredSize(pScale9Sprite->getOriginalSize());
		pBtnEffectMute->ignoreAnchorPointForPosition(true);
		pBtnEffectMute->setPosition(ccp(385,85));
		pBtnEffectMute->setTag(EFFECT_MUTE);
		pBtnEffectMute->setUserData((void*)IsMute);
		pBtnEffectMute->setDefaultTouchPriority(m_nPriority-1);
		pBtnEffectMute->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndSetting::doEvents),32);
		this->addChild(pBtnEffectMute);
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
			CCScale9Sprite *pSprite = CCScale9Sprite::create("Common/Setting/audio.png",CCRect(31,0,31,35));
			if (!pSprite)
				return;
			pBtnAudioMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
		}
		else
		{
			CCScale9Sprite *pSprite = CCScale9Sprite::create("Common/Setting/audio.png",CCRect(0,0,31,35));
			if (!pSprite)
				return;
			pBtnAudioMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);		
		}
	}
	// 音效
	else if (pScrollbar->isEqual(pScrollBarEffect))
	{
		m_LastEffectRatio = value;
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->setEffectsVolume(value);
		// 刷新UI
		if (value==0.0f)
		{
			CCScale9Sprite *pSprite = CCScale9Sprite::create("Common/Setting/effect.png",CCRect(30,0,30,35));
			if (!pSprite)
				return;
			pBtnEffectMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
		}
		else
		{
			CCScale9Sprite *pSprite = CCScale9Sprite::create("Common/Setting/effect.png",CCRect(0,0,30,35));
			if (!pSprite)
				return;
			pBtnEffectMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);		
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
			if (tag==AUDIO_MUTE)
				setAudioMuteOrNot();
			else if (tag==EFFECT_MUTE)
				setEffectMuteOrNot();
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

		CCScale9Sprite *pSprite = CCScale9Sprite::create("Common/Setting/audio.png",CCRect(31,0,31,35));
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

		CCScale9Sprite *pSprite = CCScale9Sprite::create("Common/Setting/audio.png",CCRect(0,0,31,35));
		if (!pSprite)
			return;
		pBtnAudioMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
	}
}

void SIX_PopWndSetting::setEffectMuteOrNot()
{
	if (!pBtnEffectMute)
		return;
	int IsMute = (int)(pBtnEffectMute->getUserData());
	// 禁用
	if (IsMute==0)
	{
		m_LastEffectRatio = SIX_GlobalMgr::GetInstance()->GetMusicMgr()->m_EffectVolume;
		pScrollBarEffect->setValue(0.0f);
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->setEffectsVolume(0.0f);
		pBtnEffectMute->setUserData((void*)1);

		CCScale9Sprite *pSprite = CCScale9Sprite::create("Common/Setting/effect.png",CCRect(30,0,30,35));
		if (!pSprite)
			return;
		pBtnEffectMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
	}
	// 恢复
	else
	{
		if (m_LastEffectRatio==0.0f)
			m_LastEffectRatio = 0.5f;
		pScrollBarEffect->setValue(m_LastEffectRatio);
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->setEffectsVolume(m_LastEffectRatio);
		pBtnEffectMute->setUserData((void*)0);

		CCScale9Sprite *pSprite = CCScale9Sprite::create("Common/Setting/effect.png",CCRect(0,0,30,35));
		if (!pSprite)
			return;
		pBtnEffectMute->setBackgroundSpriteForState(pSprite,CCControlStateNormal);
	}
}