#include "SIX_GlobalMgr.h"

void SIX_GlobalMgr::LoadMusic(const char *fName)
{
	CCString oldFolder(CCFileUtils::sharedFileUtils()->getResourceDirectory());
#ifdef WIN32
	pMusicMgr->SetSoundResourceFolder(/*Sound*/XorStr<0x1E,6,0xD6677D0B>("\x4D\x70\x55\x4F\x46"+0xD6677D0B).s);
	CCFileUtils::sharedFileUtils()->setResourceDirectory(/*Sound*/XorStr<0x1E,6,0xD6677D0B>("\x4D\x70\x55\x4F\x46"+0xD6677D0B).s);
#else
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		pMusicMgr->SetSoundResourceFolder(/*Music*/XorStr<0x75,6,0x27F1E448>("\x38\x03\x04\x11\x1A"+0x27F1E448).s);
		CCFileUtils::sharedFileUtils()->setResourceDirectory(/*Music*/XorStr<0x75,6,0x27F1E448>("\x38\x03\x04\x11\x1A"+0x27F1E448).s);
	#endif
#endif
	int retv = pMusicMgr->LoadXMLFromFile(fName);
	if (retv!=0)
	{
		SIXLog("LoadMusic[%s].Error[%d]",fName,retv);
		return;
	}
	pMusicMgr->ReleaseXML();

	// 恢复原始的资源路径
	CCFileUtils::sharedFileUtils()->setResourceDirectory(oldFolder.getCString());

	int total = pMusicMgr->GetTotalSoundCount();
	int soundCount = pMusicMgr->GetBgSoundCount();
	int effectCount = pMusicMgr->GetEffectSoundCount();

	SIXLog("Music.Total[%d].soundCount[%d].effectCount[%d]",total,soundCount,effectCount);
}

void SIX_GlobalMgr::StopAllMusicAndEffect()
{
	pMusicMgr->stopAllEffects();
	pMusicMgr->stopBackgroundMusic();
}

void SIX_GlobalMgr::PlayNextBackgroundMusic()
{
	// 随机背景音乐，且不为上次播放的音乐
	int soundCount = pMusicMgr->GetBgSoundCount();
	if (soundCount==0)
		return;
	int rnd = SIX_Utility::GetInstance()->RNDNUM(0,soundCount-1);
	int retry = 0;
	while (rnd==m_LastBackgroundMusicIdx && retry<3)
	{
		rnd = SIX_Utility::GetInstance()->RNDNUM(0,soundCount-1);
		retry++;
	}
	m_LastBackgroundMusicIdx = rnd;
	StopAllMusicAndEffect();
	pMusicMgr->playBackgroundMusic(m_LastBackgroundMusicIdx,true);
	SIXLog("Using BG[%d] Now!",m_LastBackgroundMusicIdx);
}

void SIX_GlobalMgr::PlayChangeSceneMusic()
{
	StopAllMusicAndEffect();
	pMusicMgr->playEffect(22);
}

void SIX_GlobalMgr::ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet)
{
	if (!pMusicMgr)
		return;

	SIX_XmlDataSet *pDataSet = 0;

	//SIXLog("ParseXML.GetChildrenCount[%d]",pXmlDataSet->GetChildrenCount());
	CCARRAY_FOREACH_T(pXmlDataSet->GetChildren(),pDataSet,SIX_XmlDataSet*)
	{
		// 跳过Root和Comment
		if (pDataSet->getKey().compareIgnoreCase("Element"))
			continue;

		if (pDataSet->pDataElement)
		{
			if (!pDataSet->getValue().compareIgnoreCase("Volume"))
			{
				SIX_KV *pKV = 0;
				CCARRAY_FOREACH_T(pDataSet->pDataElement->GetChildren(),pKV,SIX_KV*)
				{
					if (!STRCMP(pKV->getKey().getCString(),"Background"))
					{
						float vol = atof(pKV->getValue().getCString());
						if (vol<=0.0f)
							vol = 0.0f;
						if (vol>=1.0f)
							vol = 1.0f;
						pMusicMgr->m_BackgroundVolume = vol;
					}
					else if (!STRCMP(pKV->getKey().getCString(),"Effect"))
					{
						float vol = atof(pKV->getValue().getCString());
						if (vol<=0.0f)
							vol = 0.0f;
						if (vol>=1.0f)
							vol = 1.0f;
						pMusicMgr->m_EffectVolume = vol;
					}
				}
			}
		}
	}
}

void SIX_GlobalMgr::LoadProfile(char *ProfPath)
{
	// 音量
	if (pMusicMgr)
	{
		// 默认音量百分比50%
		// Cool.Cat
		pMusicMgr->m_BackgroundVolume = 0.5f;
		pMusicMgr->m_EffectVolume = 0.5f;

#ifdef WIN32
		string savePath(SIX_Utility::GetInstance()->GetAppBasePath(ProfPath));
		wstring ufolder(SIX_Utility::GetInstance()->Utf8ToUnicode(savePath.c_str()).c_str());
		CreateDirectory(ufolder.c_str(),0);

		const char *proFile = CCString::createWithFormat("%sprof.dat",SIX_Utility::GetInstance()->U2G(savePath.c_str()).c_str())->getCString();

		SIX_XMLParser *pXML = new SIX_XMLParser();

		int retv = pXML->LoadXMLFromFile(proFile);
		if (retv==-1 || retv==-2)
			return;

		ParseXML(pXML->GetXMLDataSet());

		pXML->ReleaseXMLDataSet();

		CC_SAFE_DELETE(pXML);
#endif
	}
}

void SIX_GlobalMgr::SaveProfile(char *ProfPath)
{
	// 音量
	if (pMusicMgr)
	{
#ifdef WIN32
		string savePath(SIX_Utility::GetInstance()->GetAppBasePath(ProfPath));
		wstring ufolder(SIX_Utility::GetInstance()->Utf8ToUnicode(savePath.c_str()).c_str());
		CreateDirectory(ufolder.c_str(),0);

		TiXmlDocument *pDoc = new TiXmlDocument();
		TiXmlDeclaration* pDec = new TiXmlDeclaration("1.0","UTF-8","");
		pDoc->LinkEndChild(pDec);
		
		TiXmlElement *pRoot = new TiXmlElement("Profile");
		SYSTEMTIME st;
		SIX_Utility::GetInstance()->GetLocalTime(&st);
		CCString *timeNow = CCString::createWithFormat("%04d-%02d-%02d %02d:%02d:%02d %03d",
			st.wYear,st.wMonth,st.wDay,
			st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		pRoot->SetAttribute("Update",timeNow->getCString());
		pDoc->LinkEndChild(pRoot);
		
		TiXmlElement *pNode = new TiXmlElement("Volume");
		pRoot->LinkEndChild(pNode);
		pNode->SetAttribute("Background",CCString::createWithFormat("%.2f",pMusicMgr->m_BackgroundVolume)->getCString());
		pNode->SetAttribute("Effect",CCString::createWithFormat("%.2f",pMusicMgr->m_EffectVolume)->getCString());

		const char *profPath = CCString::createWithFormat("%sprof.dat",SIX_Utility::GetInstance()->U2G(savePath.c_str()).c_str())->getCString();
		pDoc->SaveFile(profPath);
		pDoc->Clear();
		CC_SAFE_DELETE(pDoc);
#endif
	}
}