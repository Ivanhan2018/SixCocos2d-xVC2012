#include "SIX_CacheMgr.h"

SIX_CacheMgr::~SIX_CacheMgr()
{
	UnloadAll();
}

void SIX_CacheMgr::Load(SIX_UIScene *pScene,FRAMECACHE_INFO *pFrameCacheInfo)
{
	if (!pFrameCacheInfo)
		return;

	m_FrameCache.insert(MMAP_FRAMECACHE::value_type(pScene,pFrameCacheInfo));

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pFrameCacheInfo->m_file.c_str());
}

void SIX_CacheMgr::Unload(SIX_UIScene *pScene,bool bOnlyAutoRelease)
{
	RANGE_FRAMECACHE range = m_FrameCache.equal_range(pScene);
	// 只清理标志位=true的
	if (bOnlyAutoRelease)
	{
		for (ITER_FRAMECACHE iter=range.first;iter!=range.second;)
		{
			FRAMECACHE_INFO *pFrameCacheInfo = iter->second;
			if (pFrameCacheInfo->m_autorelease)
			{
				m_FrameCache.erase(iter++);
				CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(pFrameCacheInfo->m_file.c_str());
				CC_SAFE_DELETE(pFrameCacheInfo);
			}
			else
				iter++;
		}
	}
	// 全部咔嚓
	else
	{
		for (ITER_FRAMECACHE iter=range.first;iter!=range.second;)
		{
			FRAMECACHE_INFO *pFrameCacheInfo = iter->second;
			m_FrameCache.erase(iter++);
			CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(pFrameCacheInfo->m_file.c_str());
			CC_SAFE_DELETE(pFrameCacheInfo);
		}
	}
}

void SIX_CacheMgr::UnloadAll()
{
	for (ITER_FRAMECACHE iter=m_FrameCache.begin();iter!=m_FrameCache.end();)
	{
		FRAMECACHE_INFO *pFrameCacheInfo = iter->second;
		m_FrameCache.erase(iter++);
		CC_SAFE_DELETE(pFrameCacheInfo);
	}
#ifdef WIN32
	m_FrameCache.swap(MMAP_FRAMECACHE());
#endif
	m_FrameCache.clear();
}