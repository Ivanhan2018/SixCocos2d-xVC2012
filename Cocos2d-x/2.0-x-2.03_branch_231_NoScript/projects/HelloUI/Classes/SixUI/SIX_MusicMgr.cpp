#include "SIX_MusicMgr.h"

// ���Դ�Сд
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

	// ���û���ӽڵ�
	if (!pDataSet->pNode || !pDataSet->pNode->GetChildrenCount())
		return;

	// �����ӽڵ�
	SIX_XmlDataSet *pChild = 0;
	CCARRAY_FOREACH_T(pDataSet->pNode->GetChildren(),pChild,SIX_XmlDataSet*)
	{
		if (compareIgnoreCase(pChild->getKey(),"Element") && compareIgnoreCase(pChild->getValue(),"Music"))
		{
			SIXLog("key=%s,value=%s",pChild->getKey().getCString(),pChild->getValue().getCString());
			continue;
		}

		// ��������
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

		// ����ֶ�����һ��
		if (col_count!=2)
		{
			CC_SAFE_DELETE(pSound);
		}
		else
		{
			AddObjToDict(pSound,pSound->getId());

			SIXLog("Ԥ����.Id[%d].Type[%d].Path[%s]...",
				pSound->getId(),
				pSound->getType(),
				pSound->getPath().getCString());

			// ������Ч
			switch (pSound->getType())
			{
				// ����
			case 0:
				{
					// AudioEngineδʵ��Ԥ���ر������ֹ��ܡ�����
					// Cool.Cat@2013-03-18
					this->preloadBackgroundMusic(pSound->getId());
					break;
				}
				// ��Ч
			case 1:
				{
					this->preloadEffect(pSound->getId());
					break;
				}
			}

			SIXLog("Ԥ����.Id[%d].Type[%d].Path[%s]...OK!",
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
		// ����Root��Comment
		if (compareIgnoreCase(pDataSet->getKey(),"Element"))
			continue;

		// ������������
		ParseNode(pDataSet,"BackgroundMusic");
		// ������Ч����
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
// ����
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
// ��Ч
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