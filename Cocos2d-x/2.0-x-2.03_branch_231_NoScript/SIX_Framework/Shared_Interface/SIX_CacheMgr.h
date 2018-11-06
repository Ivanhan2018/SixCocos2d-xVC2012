/***********************************************
Name��UI���������
Desc�����ڶೡ������UI���棬����֡����Ͷ�������
Auth��Cool.Cat@2013-08-22
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_DSTPL.h>
#include <TSingleton.h>

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_UIScene;

typedef struct tagFrameCacheInfo{
	// �Ƿ��Զ��ͷ�
	bool m_autorelease;
	// ����·��
	string m_file;

	tagFrameCacheInfo()
	{
		m_autorelease = true;
		m_file.clear();
	}
} FRAMECACHE_INFO;

typedef multimap<SIX_UIScene*,FRAMECACHE_INFO*> MMAP_FRAMECACHE;
typedef MMAP_FRAMECACHE::iterator ITER_FRAMECACHE;
typedef pair<ITER_FRAMECACHE,ITER_FRAMECACHE> RANGE_FRAMECACHE;

class SIX_CacheMgr:public TSingleton<SIX_CacheMgr>
{
public:
	virtual ~SIX_CacheMgr();
	void Load(SIX_UIScene *,FRAMECACHE_INFO *);
	void Unload(SIX_UIScene *,bool bOnlyAutoRelease=true);
	void UnloadAll();
private:
	// ֡���黺������
	MMAP_FRAMECACHE m_FrameCache;
};