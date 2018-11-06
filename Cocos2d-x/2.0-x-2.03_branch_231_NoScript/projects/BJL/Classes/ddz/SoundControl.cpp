#include "SoundControl.h"
static SoundControl * s_SharedSoundControl = NULL;

SoundControl::SoundControl()
{
	m_musicVol = CCUserDefault::sharedUserDefault()->getFloatForKey("ZJD_SOUNDNUM",0.5f);
	m_soundEffVol = CCUserDefault::sharedUserDefault()->getFloatForKey("SOUNDEFFVOL",0.5f);
	m_voiceIsOpen = CCUserDefault::sharedUserDefault()->getBoolForKey("ZJD_SOUNDSTATE",false);
}

SoundControl::~SoundControl()
{
}

SoundControl * SoundControl::sharedSoundControl()
{
	if (!s_SharedSoundControl)
	{
		s_SharedSoundControl = new SoundControl();
	}
	return s_SharedSoundControl;
}

void SoundControl::playBackGroundMusic(const char * soundName,bool loop)
{
	if (m_voiceIsOpen)
	{
		return;
	}
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(soundName,loop);
}

void SoundControl::playSoundEffect(const char * soundName)
{
	if (m_voiceIsOpen)
	{
		return;
	}
	SimpleAudioEngine::sharedEngine()->playEffect(soundName);
}

void SoundControl::setVoiceIsOpen(bool var)
{
	m_voiceIsOpen = var;
	CCUserDefault::sharedUserDefault()->setBoolForKey("ZJD_SOUNDSTATE",m_voiceIsOpen);
	if (!m_voiceIsOpen)
	{
		playBackGroundMusic(sound_name::s_bgMusic,true);
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
	}
}

void SoundControl::setSoundEffVol(float vol)
{
	m_soundEffVol = CCUserDefault::sharedUserDefault()->getFloatForKey("SOUNDEFFVOL",0.5f);
	if (vol!=-1)
	{
		m_soundEffVol = vol;
	}
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_soundEffVol);
 	CCUserDefault::sharedUserDefault()->setFloatForKey("SOUNDEFFVOL",m_soundEffVol);
 	CCUserDefault::sharedUserDefault()->flush();
}

void SoundControl::setMusicVol(float vol)
{
	m_musicVol = CCUserDefault::sharedUserDefault()->getFloatForKey("ZJD_SOUNDNUM",0.5f);
	if (vol!=-1)
	{
		m_musicVol = vol;
	}
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m_musicVol);
	CCUserDefault::sharedUserDefault()->setFloatForKey("ZJD_SOUNDNUM",m_musicVol);
	CCUserDefault::sharedUserDefault()->flush();
}

void SoundControl::coloseBackGroundMusic()
{
	if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()){
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	}
}
static SoundEffect * s_sharedSoundEffect = NULL;

SoundEffect::SoundEffect()
{
	m_leftUser.userId = 0;
	m_leftUser.gender = 1;
	m_self.userId = 0;
	m_self.gender = 1;
	m_rightUser.userId = 0;
	m_rightUser.gender = 1;
}

SoundEffect::~SoundEffect()
{

}

SoundEffect * SoundEffect::sharedSoundEffect()
{
	if (!s_sharedSoundEffect)
	{
		s_sharedSoundEffect = new SoundEffect();
	}
	return s_sharedSoundEffect;
}

void SoundEffect::initLeftTag(Tag left)
{
	m_leftUser = left;

}

void SoundEffect::initRightTag(Tag right)
{
	m_rightUser = right;
}

void SoundEffect::initSelfTag(Tag self)
{
	m_self = self;
}

void SoundEffect::playEffect(const char * soundName,int userId)
{
	int gender = 0;
	switch (userId)
	{
	case 0://�ϼ�
		gender = m_leftUser.gender;
		break;
	case 1://�Լ�
		gender = m_self.gender;
		break;
	case 2://�¼�
		gender = m_rightUser.gender;
		break;
	}
	CCString str;
	if (gender==1)//1��ʾ��
	{
		str.initWithFormat("soundeffect/man/%s",soundName);
	}else
	{
		str.initWithFormat("soundeffect/woman/%s",soundName);
	}
	SoundControl::sharedSoundControl()->playSoundEffect(str.getCString());

}

void SoundEffect::playPassEffect(int userId)
{
	int i=rand()%3;
	switch(i)
	{
	case 0:
		playEffect(sound_name::s_buyao,userId);
		break;
	case 1:
		playEffect(sound_name::s_guo,userId);
		break;
	case 2:
		playEffect(sound_name::s_yaobuqi,userId);
		break;
	}
}

void SoundEffect::playDaPaiEffect(int userId)
{
	switch(rand()%2)
	{
	case 0:
		playEffect(sound_name::s_yasi,userId);
		break;
	case 1:
		playEffect(sound_name::s_dani,userId);
		break;
	}
}