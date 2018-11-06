/*********************************************************
Name：通用数据模版(DataSet Template)
Desc：增删改查接口、值对/集合、无限扩展
Auth：Cool.Cat@2013-03-15
*********************************************************/
#pragma once
#include <SIX_Interface.h>

template <typename T>
INTERFACE_BEGIN_BASED(SIX_DSTPL,SIX_Interface)
	CONSTRUCTOR(
		SIX_DSTPL,
		this->setInterfaceName("SIX_DSTPL");

		// 子对象集合交给CCPoolManager管理，
		// 所以要retain防止在下一帧被自动释放
		// Cool.Cat@2013-03-16
		pChildren = CCArray::create();
		pChildren->retain();
		// ref must be 2
		//SIXLog("pChildren.retainCount[%d]",pChildren->retainCount());
	);
	DESTRUCTOR(
		SIX_DSTPL,
		DelAll();
		// ref must be 1
		//SIXLog("~pChildren.retainCount[%d]",pChildren->retainCount());
		CC_SAFE_RELEASE_NULL(pChildren);
	);
public:
	// 节点数量
	virtual unsigned int GetChildrenCount()										{return pChildren->count();}
	// 引用计数
	virtual unsigned int GetChildrenRetainCount()								{return pChildren->retainCount();}
public:
	// 增
	virtual void Add(T *pChild)													{pChildren->addObject(pChild);}
	virtual void Add(T *pChild,unsigned int Idx)								{pChildren->insertObject(pChild,Idx);}
	// 删
	virtual void Del(unsigned int Idx,bool bRelease=true)						{T *pChild = Get(Idx);Del(pChild,bRelease);}
	virtual void Del(T *pChild,bool bRelease=true)
	{
		// 先将pChild子对象的引用计数自减=1
		CC_SAFE_RELEASE(pChild);
		// 再释放pChild
		pChildren->removeObject(pChild,bRelease);
	}
	virtual void DelAll()
	{
		// 先将pChild子对象的引用计数自减=1
		for (unsigned int i=0;i<pChildren->count();i++)
		{
			T *pChild = Get(i);
			CC_SAFE_RELEASE(pChild);
		}
		// 再释放pChild
		pChildren->removeAllObjects();
	}
	// 改
	virtual void Update(unsigned int Idx,T *pChild,bool bRelease=true)			{pChildren->replaceObjectAtIndex(Idx,pChild,bRelease);}
	// 查
	virtual bool Find(T *pChild)												{return pChildren->containsObject(pChild);}
	virtual T *Random()															{return (T*)(pChildren->randomObject());}
	virtual T *Get(unsigned int Idx)											{return (T*)(pChildren->objectAtIndex(Idx));}
	virtual unsigned int Get(T *pChild)											{return pChildren->indexOfObject(pChild);}
	//
	virtual CCArray *GetChildren() const										{return pChildren;}
private:
	CCArray *pChildren;
INTERFACE_END()

// KV值对
INTERFACE_BEGIN_BASED(SIX_KV,SIX_Interface)
	CONSTRUCTOR(SIX_KV);
	CC_SYNTHESIZE(CCString,m_Key,Key);
	CC_SYNTHESIZE(CCString,m_Value,Value);
INTERFACE_END()

// DataSet
INTERFACE_BEGIN_BASED(SIX_DataSet,SIX_KV)
	CONSTRUCTOR(SIX_DataSet,pDataElement=new SIX_DSTPL<SIX_KV>;);
	DESTRUCTOR(SIX_DataSet,CC_SAFE_DELETE(pDataElement););
	SIX_DSTPL<SIX_KV> *pDataElement;
INTERFACE_END()

INTERFACE_BEGIN_BASED(SIX_XmlDataSet,SIX_DataSet)
	CONSTRUCTOR(SIX_XmlDataSet,pNode=new SIX_DSTPL<SIX_XmlDataSet>;);
	DESTRUCTOR(SIX_XmlDataSet,CC_SAFE_DELETE(pNode););
	CC_SYNTHESIZE(CCString,m_Parent,Parent);
	SIX_DSTPL<SIX_XmlDataSet> *pNode;
INTERFACE_END()