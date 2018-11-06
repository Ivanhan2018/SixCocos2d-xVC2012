/***********************************************
Name：UI管理器
Desc：XML<=>UI解析，UI控件管理
Auth：Cool.Cat@2013-03-29
***********************************************/
#pragma once
#include <SIX_DSTPL.h>
#include <SIX_EntityMgr.h>
#include <SIX_UIScene.h>
#include <SIX_ListView.h>
#include <SIX_NumberBatchNode.h>
#include "SIX_CacheMgr.h"
#include <SIX_CardSuit.h>
#include <SIX_CardItem.h>

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_UIScene;

class SIX_UIMgr:public SIX_EntityMgr {
public:
	SIX_UIMgr();
	~SIX_UIMgr();
public:
	virtual int ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet);
	virtual int Run();
	virtual int Release();
public:
	void SetParent(SIX_UIScene *pParnet)	{m_Parent = pParnet;}
	SIX_UIScene *GetParent()				{return m_Parent;}
public:
	// CCNode
	bool ParseAttribute(CCNode *pControl,SIX_KV *pKV);
	// CCNode->CCSpriteBatchNode
	bool ParseAttribute(CCSpriteBatchNode *pControl,SIX_KV *pKV);
	// CCNode->CCScale9Sprite
	bool ParseAttribute(CCScale9Sprite *pControl,SIX_KV *pKV);
	// CCNode->CCProgressTimer
	bool ParseAttribute(CCProgressTimer *pControl,SIX_KV *pKV);
	// CCNode->CCSprite
	bool ParseAttribute(CCSprite *pControl,SIX_KV *pKV);
	// CCSprite->CCLabelTTF
	bool ParseAttribute(CCLabelTTF *pControl,SIX_KV *pKV);
	// CCNode->CCMenuItem
	bool ParseAttribute(CCMenuItem *pControl,SIX_KV *pKV);
	// CCMenuItem->CCMenuItemToggle
	bool ParseAttribute(CCMenuItemToggle *pControl,SIX_KV *pKV);
	// CCMenuItem->CCMenuItemSprite
	bool ParseAttribute(CCMenuItemSprite *pControl,SIX_KV *pKV);
	// CCMenuItemSprite->CCMenuItemImage
	bool ParseAttribute(CCMenuItemImage *pControl,SIX_KV *pKV);
	// CCMenuItem->CCMenuItemLabel
	bool ParseAttribute(CCMenuItemLabel *pControl,SIX_KV *pKV);
	// CCMenuItemLabel->CCMenuItemAtlasFont
	bool ParseAttribute(CCMenuItemAtlasFont *pControl,SIX_KV *pKV);
	// CCMenuItemLabel->CCMenuItemFont
	bool ParseAttribute(CCMenuItemFont *pControl,SIX_KV *pKV);
	// CCNode->CCLayer
	bool ParseAttribute(CCLayer *pControl,SIX_KV *pKV);
	// CCLayer->CCMenu
	bool ParseAttribute(CCMenu *pControl,SIX_KV *pKV);
	// CCLayer->CCLayerMultiplex
	bool ParseAttribute(CCLayerMultiplex *pControl,SIX_KV *pKV);
	// CCLayer->CCLayerColor
	bool ParseAttribute(CCLayerColor *pControl,SIX_KV *pKV);
	// CCLayerColor->CCLayerGradient
	bool ParseAttribute(CCLayerGradient *pControl,SIX_KV *pKV);
	// CCLayer->CCControl
	bool ParseAttribute(CCControl *pControl,SIX_KV *pKV);
	// CCControl->CCControlButton
	bool ParseAttribute(CCControlButton *pControl,SIX_KV *pKV);
	// CCControl->SIX_CardSuit
	bool ParseAttribute(SIX_CardSuit *pControl,SIX_KV *pKV);
	// CCControl->SIX_CardItem
	bool ParseAttribute(SIX_CardItem *pControl,SIX_KV *pKV);

	bool GetAttributeSplit(const char *src,const char *name,string &value);
	int GetAttributeAndPos(SIX_DSTPL<SIX_KV> *pDataElement,const char *attribute,SIX_KV *pResult);

	CCObject *ParseObject(SIX_XmlDataSet *pDataSet,const char *nodeName);
	CCNode *ParseControl(SIX_XmlDataSet *pDataSet,CCNode *pRoot);

	//CCAction *CreateAction(CCObject *pObject,SIX_DSTPL<SIX_KV> *pDataElement);
	//CCAnimate *CreateAnimate(CCObject *pObject,SIX_DSTPL<SIX_KV> *pDataElement);
	CCAnimation *CreateAnimation(CCObject *pObject,SIX_XmlDataSet *pDataSet);
	CCSpriteFrame *CreateSpriteFrame(CCObject *pObject,SIX_DSTPL<SIX_KV> *pDataElement);

	CCSprite *CreateSprite(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);
	CCScale9Sprite *CreateScale9Sprite(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);
	CCControlButton *CreateButton(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);
	CCProgressTimer *CreateProgressTimer(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);
	CCSpriteBatchNode *CreateSpriteBatchNode(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);
	SIX_NumberBatchNode *CreateNumberBatchNode(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);
	SIX_ListView *CreateListView(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);
	SIX_ListViewCell *CreateListViewCell(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);
	// 新增2种牌控件
	// Cool.Cat
	SIX_CardSuit *CreateCardSuit(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);
	SIX_CardItem *CreateCardItem(CCNode *pControl,SIX_DSTPL<SIX_KV> *pDataElement);

	// 传入控件内部属性节点描述，解析后返回一个DSTPL对象
	SIX_DSTPL<SIX_KV> *SIX_UIMgr::ParseKV(const char *name,SIX_DSTPL<SIX_KV> *pDataElement);

	// 加载帧精灵缓存
	void LoadFrameCache(SIX_DSTPL<SIX_KV> *pDataElement);
	// 移除帧精灵缓存
	void UnloadFrameCache();
	//unsigned int GetFrameCacheCount()	{return m_FrameCache.size();}

	// 加载动作组
	void LoadAnimationCache(SIX_XmlDataSet *pDataSet);
	// 查找动作
	CCAnimation *GetAnimationFromCache(const char *animationName);
	// 移除动作组
	void UnloadAnimationCache();
	unsigned int GetAnimationCacheCount()	{return m_AnimationCache.count();}

	void addControlEvents(unsigned int controlEvents,CCControl *pContrl,CCObject *pTarget=0);
	void doEvents(CCObject* pSender, CCControlEvent event);
	////弹起(鼠标在控件区域内)
	//void onCCControlEventTouchUpInside(CCObject* pSender, CCControlEvent event);
	//void setAllDirty(bool bDirty);
	//bool getAllDirty();
public:
	SIX_UIScene *m_Parent;

	// 动作组缓存容器
	CCDictionary m_AnimationCache;
	//map<const char*,CCAnimation*> m_AnimationCache;
	bool m_bDirty;
};