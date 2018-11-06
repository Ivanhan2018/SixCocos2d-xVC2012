/***********************************************
Name：全局管理器
Desc：封装资源管理器、场景管理器，由游戏世界调用
Auth：Cool.Cat@2013-03-15
***********************************************/
#pragma once
//#include "SIX_Common.h"
#include "SIX_MusicMgr.h"
#include "SIX_FileSystem.h"
#include "SIX_Proxy.h"
#include "SIX_Logger.h"
#include <SIX_XMLParser.h>
#include <SIX_DSTPL.h>

USING_NS_CC;

class SIX_MusicMgr;
class SIX_FileSystem;
class SIX_Proxy;
class SIX_Logger;

typedef struct tagConfigInfo {
	string ip;
	unsigned int port;
	float debug_number1;
	float debug_number2;
	tagConfigInfo()
	{
		ip.clear();
		port = 0;
		debug_number1 = 0.0f;
		debug_number2 = 0.0f;
	}
} CONFIG_INFO;

class SIX_GlobalMgr:public TSingleton<SIX_GlobalMgr> {
public:
	SIX_GlobalMgr(char *ProjName="SixDivisions")
	{
		m_LastBackgroundMusicIdx = 0;

		pLogger = new SIX_Logger();
		pLogger->SetLogName(ProjName);
		pMusicMgr = SIX_MusicMgr::GetInstance();
		this->LoadProfile();
		pProxy = SIX_Proxy::GetInstance();
		pFS = SIX_FileSystem::GetInstance();
		pConfig = new CONFIG_INFO();
		this->GetConfigFile();
	}
	~SIX_GlobalMgr()
	{
		this->SaveProfile();
		CC_SAFE_DELETE(pMusicMgr);
		CC_SAFE_DELETE(pProxy);
		CC_SAFE_DELETE(pFS);
		CC_SAFE_DELETE(pLogger);
	}

	// 玩家信息本地存储
	void LoadProfile(char *ProPath="Prof");
	void SaveProfile(char *ProPath="Prof");

	void LoadMusic(const char *fName);
	void StopAllMusicAndEffect();
	void PlayNextBackgroundMusic();
	void PlayChangeSceneMusic();

	void GetConfigFile()
	{
		CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
		const char *pPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath( "config.xml" );
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		unsigned long len = 0;
		unsigned char *pData = CCFileUtils::sharedFileUtils()->getFileData(pPath, "r", &len);
		if (!pData || !len)
		{
			CC_SAFE_DELETE(pData);
			CC_SAFE_DELETE_ARRAY(pPath);
			SIXLog("GetConfigFile.C.Error");
			return;
		}

		SIX_XMLParser *pXML = new SIX_XMLParser();
		int retv = pXML->LoadXMLFromMemory(pData,len);
		if (retv!=0)
		{
			CC_SAFE_DELETE(pXML);
			CC_SAFE_DELETE(pData);
			CC_SAFE_DELETE_ARRAY(pPath);
			SIXLog("GetConfigFile.D.Error");
			return;
		}

		this->ParseXML(pXML->GetXMLDataSet());

		CC_SAFE_DELETE(pData);

		SIX_XmlDataSet *pDataSet = 0;

		CCARRAY_FOREACH_T(pXML->GetXMLDataSet()->GetChildren(),pDataSet,SIX_XmlDataSet*)
		{
			// 跳过Root和Comment
			if (pDataSet->getKey().compareIgnoreCase("Element"))
				continue;

			if (pDataSet->pDataElement)
			{
				if (!pDataSet->getValue().compareIgnoreCase("address"))
				{
					SIX_KV *pKV = 0;
					CCARRAY_FOREACH_T(pDataSet->pDataElement->GetChildren(),pKV,SIX_KV*)
					{
						if (!STRCMP(pKV->getKey().getCString(),"ip"))
						{
							pConfig->ip.clear();
							pConfig->ip.append(pKV->getValue().getCString());
						}
						else if (!STRCMP(pKV->getKey().getCString(),"port"))
						{
							pConfig->port = pKV->getValue().uintValue();
						}
					}
				}
				else if (!pDataSet->getValue().compareIgnoreCase("debug_number"))
				{
					SIX_KV *pKV = 0;
					CCARRAY_FOREACH_T(pDataSet->pDataElement->GetChildren(),pKV,SIX_KV*)
					{
						if (!STRCMP(pKV->getKey().getCString(),"number1"))
						{
							pConfig->debug_number1 = pKV->getValue().floatValue();
						}
						else if (!STRCMP(pKV->getKey().getCString(),"number2"))
						{
							pConfig->debug_number2 = pKV->getValue().floatValue();
						}
					}
				}
			}
		}

		pXML->ReleaseXMLDataSet();
		CC_SAFE_DELETE(pXML);
		CC_SAFE_DELETE_ARRAY(pPath);

		SIXLog("pConfig.ip[%s].port[%d].debug_number1[%.4f].debug_number2[%.4f]",
			pConfig->ip.c_str(),
			pConfig->port,
			pConfig->debug_number1,
			pConfig->debug_number2
		);
//#else
//
//		TiXmlDocument *pXmlDocument = new TiXmlDocument();
//		if (!pXmlDocument->LoadFile( pPath ))
//		{
//			CC_SAFE_DELETE_ARRAY(pPath);
//			return;
//		}
//		CC_SAFE_DELETE_ARRAY(pPath);
//		TiXmlElement *pRoot = pXmlDocument->RootElement();
//		if (NULL == pRoot)
//		{
//			assert( 0 );
//			return;
//		}
//
//		TiXmlNode *pAddress = pRoot->FirstChild( "address" );
//		if (NULL == pAddress)
//		{
//			assert( 0 );
//			return;
//		}
//
//		TiXmlAttribute *pAttribute = pAddress->ToElement()->FirstAttribute();
//		while ( pAttribute )
//		{
//			const char *pName = pAttribute->Name();
//			if (0 == STRCMP(pName, "ip")  &&  0<strlen( pAttribute->Value() ))
//			{
//				sprintf(pIP, "%s", pAttribute->Value());
//			}
//			else if (0 == STRCMP(pName, "port")  &&  0<strlen( pAttribute->Value() ))
//			{
//				nPort = atoi( pAttribute->Value() );
//			}
//			pAttribute = pAttribute->Next();
//		}
//		pXmlDocument->Clear();
//		CC_SAFE_DELETE( pXmlDocument );
//#endif
	}
private:
	void ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet);
public:
	SIX_MusicMgr *GetMusicMgr() const {return &(*pMusicMgr);}
	SIX_Proxy *GetProxy() const {return &(*pProxy);}
	SIX_FileSystem *GetFS() const {return &(*pFS);}
	SIX_Logger *GetLogger() const {return pLogger;}
	CONFIG_INFO *GetConfig() const {return &(*pConfig);}
private:
	// 音效管理器
	SIX_MusicMgr *pMusicMgr;
	// 网络消息代理
	SIX_Proxy *pProxy;
	// 文件管理器
	SIX_FileSystem *pFS;
	// 日志
	SIX_Logger *pLogger;
	int m_LastBackgroundMusicIdx;
	// 配置参数
	CONFIG_INFO *pConfig;
};