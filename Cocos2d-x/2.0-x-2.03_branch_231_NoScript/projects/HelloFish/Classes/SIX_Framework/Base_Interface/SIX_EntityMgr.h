/*********************************************************
Name：管理器基类
Desc：抽象加载、执行、释放接口
Auth：Cool.Cat@2013-03-15
*********************************************************/
#pragma once
#include <SIX_XMLParser.h>
#include <SIX_Interface.h>
#include <SIX_DSTPL.h>

//INTERFACE_BEGIN_BASED(SIX_EntityMgr,SIX_Interface)
//	CONSTRUCTOR(
//		SIX_EntityMgr,
//		this->setInterfaceName("SIX_EntityMgr");
//		this->setInterfaceType(INTERFACE_TYPE::INTERFACE_ENTITYMGR);
//		pFileUtils = CCFileUtils::sharedFileUtils();
//		pDict = CCDictionary::create();
//		pDict->retain();
//		//SIXLog("A.pDict=0x%08X , retainCount=%d",pDict,pDict->retainCount());
//		pXML = new SIX_XMLParser();
//	);
//	DESTRUCTOR(
//		SIX_EntityMgr,
//		//SIXLog("B.pDict=0x%08X , retainCount=%d",pDict,pDict->retainCount());
//		DelAllObjFromDict();
//		CC_SAFE_RELEASE_NULL(pDict);
//		CC_SAFE_DELETE(pXML);
//	);
class SIX_EntityMgr:public SIX_Interface{
public:
	SIX_EntityMgr()
	{
		this->setInterfaceName("SIX_EntityMgr");
		pFileUtils = CCFileUtils::sharedFileUtils();
		pDict = CCDictionary::create();
		pDict->retain();
		//SIXLog("A.pDict=0x%08X , retainCount=%d",pDict,pDict->retainCount());
		pXML = new SIX_XMLParser();
	}
	~SIX_EntityMgr()
	{
		//SIXLog("B.pDict=0x%08X , retainCount=%d",pDict,pDict->retainCount());
		DelAllObjFromDict();
		CC_SAFE_RELEASE_NULL(pDict);
		CC_SAFE_DELETE(pXML);
	}
public:
	int LoadXMLFromFile(const char *file)
	{
	// android默认从内存中加载XML，修复无法从文件加载的BUG
	// /mnt/sdcard/
	// /data/data/
	// Cool.Cat@2013-05-02
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		char content[256];
		const char *pXMLPath = pFileUtils->fullPathFromRelativePath(file);
		sprintf(content,"file[%s].pXMLPath[%s].LoadXMLFromMemory...",file,pXMLPath);
		SIXLog("content=%s",content);
		unsigned long len = 0;
		unsigned char *pXMLData = CCFileUtils::sharedFileUtils()->getFileData(pXMLPath, "r", &len);
		CC_SAFE_DELETE_ARRAY(pXMLPath);
		sprintf(content, "file[%s].pXMLPath[%s].pXMLData[0x%08X]=%d",file,pXMLPath,pXMLData,len);
		SIXLog("content=%s",content);
		if (pXMLData && len)
		{
			if (LoadXMLFromMemory(pXMLData,len)!=0)
			{
				sprintf(content,"file[%s].pXMLPath[%s].LoadXMLFromMemory.Error.len[%d]",file,pXMLPath,len);
				SIXLog("content=%s",content);
			}
		}
#else
		switch (pXML->LoadXMLFromFile(file))
		{
		case -1:return 1;
		case -2:return 2;
		}
		ParseXML(pXML->GetXMLDataSet());
#endif
		return 0;
	}
	int LoadXMLFromMemory(unsigned char *stream,unsigned long len,int encoding = TIXML_DEFAULT_ENCODING)
	{
		switch (pXML->LoadXMLFromMemory(stream,len,encoding))
		{
		case -1:return 1;
		case -2:return 2;
		}
		ParseXML(pXML->GetXMLDataSet());
		return 0;
	}

	void ReleaseXML()											{pXML->ReleaseXMLDataSet();}

	virtual int ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet)=0;
	virtual int Run()=0;
	virtual int Release()=0;

	CCFileUtils *GetFilePtr()const{return pFileUtils;}
	CCDictionary *GetDictPtr()const{return pDict;}
public:
	void AddObjToDict(CCObject *pValue,int idx)					{GetDictPtr()->setObject(pValue,idx);}
	void AddObjToDict(CCObject *pValue,const std::string& key)	{GetDictPtr()->setObject(pValue,key);}

	CCObject *GetObjFromDict(int idx)							{return GetDictPtr()->objectForKey(idx);}
	CCObject *GetObjFromDict(const std::string& key)			{return GetDictPtr()->objectForKey(key);}

	void DelObjFromDict(int idx)								{GetDictPtr()->removeObjectForKey(idx);}
	void DelObjFromDict(const std::string& key)					{GetDictPtr()->removeObjectForKey(key);}
	void DelAllObjFromDict()									{GetDictPtr()->removeAllObjects();}

	unsigned int GetObjCount()									{return pDict->count();}
public:
	CCFileUtils *pFileUtils;
	CCDictionary *pDict;
	SIX_XMLParser *pXML;
};
//INTERFACE_END();