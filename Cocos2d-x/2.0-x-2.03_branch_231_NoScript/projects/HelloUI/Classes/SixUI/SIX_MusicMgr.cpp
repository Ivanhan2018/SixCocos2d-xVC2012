#include "SIX_MusicMgr.h"

// 忽略大小写
int compareIgnoreCase(CCString str,const char * pStr)
{
#ifdef WIN32
	return stricmp(str.getCString(),pStr);
#else
	return strcasecmp(str.getCString(),pStr);
#endif
}

void SIX_MusicMgr::ParseNode(SIX_XmlDataSet *pDataSet,const char *nodeName)
{
	if (compareIgnoreCase(pDataSet->getValue(),nodeName))
		return;

	// 如果没有子节点
	if (!pDataSet->pNode || !pDataSet->pNode->GetChildrenCount())
		return;

	// 解析子节点
	SIX_XmlDataSet *pChild = 0;
	CCARRAY_FOREACH_T(pDataSet->pNode->GetChildren(),pChild,SIX_XmlDataSet*)
	{
		if (compareIgnoreCase(pChild->getKey(),"Element") && compareIgnoreCase(pChild->getValue(),"Music"))
		{
			SIXLog("key=%s,value=%s",pChild->getKey().getCString(),pChild->getValue().getCString());
			continue;
		}

		// 解析属性
		SIX_SoundData *pSound = new SIX_SoundData();
		if (compareIgnoreCase(pChild->getParent(),"BackgroundMusic")==0)
			pSound->setType(0);
		else if (compareIgnoreCase(pChild->getParent(),"EffectMusic")==0)
			pSound->setType(1);
		else
		{
			CC_SAFE_DELETE(pSound);
			continue;
		}

		int col_count = 0;
		SIX_KV *pKV = 0;

		CCARRAY_FOREACH_T(pChild->pDataElement->GetChildren(),pKV,SIX_KV*)
		{
			if (!compareIgnoreCase(pKV->getKey(),"id"))
			{
				col_count++;
				pSound->setId(pKV->getValue().intValue());
			}
			else if (!compareIgnoreCase(pKV->getKey(),"path"))
			{
				col_count++;
				pSound->setPath(pKV->getValue().getCString());
			}
		}

		// 如果字段数不一致
		if (col_count!=2)
		{
			CC_SAFE_DELETE(pSound);
		}
		else
		{
			AddObjToDict(pSound,pSound->getId());

			SIXLog("预加载.Id[%d].Type[%d].Path[%s]...",
				pSound->getId(),
				pSound->getType(),
				pSound->getPath().getCString());

			// 加载音效
			switch (pSound->getType())
			{
				// 背景
			case 0:
				{
					// AudioEngine未实现预加载背景音乐功能。。。
					// Cool.Cat@2013-03-18
					this->preloadBackgroundMusic(pSound->getId());
					break;
				}
				// 特效
			case 1:
				{
					this->preloadEffect(pSound->getId());
					break;
				}
			}

			SIXLog("预加载.Id[%d].Type[%d].Path[%s]...OK!",
				pSound->getId(),
				pSound->getType(),
				pSound->getPath().getCString());
		}
	}
}

int SIX_MusicMgr::ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet)
{
	m_BgCount = m_EffectCount = 0;
	SIX_XmlDataSet *pDataSet = 0;

	SIXLog("SIX_MusicMgr.Parse=%d",pXmlDataSet->GetChildrenCount());
	CCARRAY_FOREACH_T(pXmlDataSet->GetChildren(),pDataSet,SIX_XmlDataSet*)
	{
		// 跳过Root和Comment
		if (compareIgnoreCase(pDataSet->getKey(),"Element"))
			continue;

		// 解析背景音乐
		ParseNode(pDataSet,"BackgroundMusic");
		// 解析特效音乐
		ParseNode(pDataSet,"EffectMusic");
	}

	return 0;
}

int SIX_MusicMgr::Run()
{
	return 0;
}

int SIX_MusicMgr::Release()
{
	stopAllEffects();
	stopBackgroundMusic();
	return 0;
}
/////////////////////////////
// 背景
void SIX_MusicMgr::preloadBackgroundMusic(unsigned int nSoundId)
{
	SIX_SoundData *pSound = dynamic_cast<SIX_SoundData*>(GetObjFromDict(nSoundId));
	if (pSound && !pSound->getIsPreload())
	{
		m_BgCount++;
		pSound->setIsPreload(true);
		CCString *absPath = CCString::createWithFormat("%s/%s",m_SoundBasePath->getCString(),pSound->getPath().getCString());
		m_AudioEngine->preloadBackgroundMusic(absPath->getCString());
	}
}
void SIX_MusicMgr::playBackgroundMusic(unsigned int nSoundId, bool bLoop)
{
	SIX_SoundData *pSound = dynamic_cast<SIX_SoundData*>(GetObjFromDict(nSoundId));
	if (pSound && pSound->getIsPreload())
	{
		CCString *absPath = CCString::createWithFormat("%s/%s",m_SoundBasePath->getCString(),pSound->getPath().getCString());
		SIXLog("playBackgroundMusic.absPath[%s]",absPath->getCString());
		m_AudioEngine->playBackgroundMusic(absPath->getCString(),bLoop);
	}
}
void SIX_MusicMgr::playBackgroundMusic(unsigned int nSoundId)
{
	this->playBackgroundMusic(nSoundId, false);
}
void SIX_MusicMgr::stopBackgroundMusic(bool bReleaseData)
{
	m_AudioEngine->stopBackgroundMusic(bReleaseData);
}
void SIX_MusicMgr::stopBackgroundMusic()
{
	this->stopBackgroundMusic(false);
}
void SIX_MusicMgr::pauseBackgroundMusic()
{
	m_AudioEngine->pauseBackgroundMusic();
}
void SIX_MusicMgr::resumeBackgroundMusic()
{
	m_AudioEngine->resumeBackgroundMusic();
}
void SIX_MusicMgr::rewindBackgroundMusic()
{
	m_AudioEngine->rewindBackgroundMusic();
}
bool SIX_MusicMgr::willPlayBackgroundMusic()
{
	return m_AudioEngine->willPlayBackgroundMusic();
}
bool SIX_MusicMgr::isBackgroundMusicPlaying()
{
	return m_AudioEngine->isBackgroundMusicPlaying();
}
float SIX_MusicMgr::getBackgroundMusicVolume()
{
	return m_AudioEngine->getBackgroundMusicVolume();
}
void SIX_MusicMgr::setBackgroundMusicVolume(float volume)
{
	m_AudioEngine->setBackgroundMusicVolume(volume);
}
// 特效
float SIX_MusicMgr::getEffectsVolume()
{
	return m_AudioEngine->getEffectsVolume();
}
void SIX_MusicMgr::setEffectsVolume(float volume)
{
	m_AudioEngine->setEffectsVolume(volume);
}
unsigned int SIX_MusicMgr::playEffect(unsigned int nSoundId, bool bLoop)
{
	SIX_SoundData *pSound = dynamic_cast<SIX_SoundData*>(GetObjFromDict(nSoundId));
	if (pSound && pSound->getIsPreload())
	{
		CCString *absPath = CCString::createWithFormat("%s/%s",m_SoundBasePath->getCString(),pSound->getPath().getCString());
		return m_AudioEngine->playEffect(absPath->getCString(),bLoop);
	}
	return 0;
}
unsigned int SIX_MusicMgr::playEffect(unsigned int nSoundId)
{
	return this->playEffect(nSoundId, false);
}
void SIX_MusicMgr::pauseEffect(unsigned int nSoundId)
{
	m_AudioEngine->pauseEffect(nSoundId);
}
void SIX_MusicMgr::pauseAllEffects()
{
	m_AudioEngine->pauseAllEffects();
}
void SIX_MusicMgr::resumeEffect(unsigned int nSoundId)
{
	m_AudioEngine->resumeEffect(nSoundId);
}
void SIX_MusicMgr::resumeAllEffects()
{
	m_AudioEngine->resumeAllEffects();
}
void SIX_MusicMgr::stopEffect(unsigned int nSoundId)
{
	m_AudioEngine->stopEffect(nSoundId);
}
void SIX_MusicMgr::stopAllEffects()
{
	m_AudioEngine->stopAllEffects();
}
void SIX_MusicMgr::preloadEffect(unsigned int nSoundId)
{
	SIX_SoundData *pSound = dynamic_cast<SIX_SoundData*>(GetObjFromDict(nSoundId));
	if (pSound && !pSound->getIsPreload())
	{
		m_EffectCount++;
		pSound->setIsPreload(true);
		CCString *absPath = CCString::createWithFormat("%s/%s",m_SoundBasePath->getCString(),pSound->getPath().getCString());
		SIXLog("preloadEffect.absPath[%s]",absPath->getCString());
		m_AudioEngine->preloadEffect(absPath->getCString());
	}
}
void SIX_MusicMgr::unloadEffect(unsigned int nSoundId,bool bDel)
{
	SIX_SoundData *pSound = dynamic_cast<SIX_SoundData*>(GetObjFromDict(nSoundId));
	if (pSound && pSound->getIsPreload())
	{
		CCString *absPath = CCString::createWithFormat("%s/%s",m_SoundBasePath->getCString(),pSound->getPath().getCString());
		m_AudioEngine->unloadEffect(absPath->getCString());

		m_EffectCount--;
		this->DelObjFromDict(nSoundId);
	}
}