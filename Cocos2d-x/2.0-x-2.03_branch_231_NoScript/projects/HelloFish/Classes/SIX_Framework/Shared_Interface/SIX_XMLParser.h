/*********************************************************
Name��XML������
Desc��ʵ��XML���ļ������ڴ���������������
Auth��Cool.Cat@2013-03-15
*********************************************************/
#pragma once
#include <TSingleton.h>
#include <Six_tinyxml/tinyxml.h>
#include <SIX_DSTPL.h>

USING_NS_CC;

//#define DEBUG_PRINT_XML

class SIX_XMLParser{
	//CONSTRUCTOR(
	//	SIX_XMLParser,
	//	pFileUtils = CCFileUtils::sharedFileUtils();
	//	pXmlDataSet = new SIX_DSTPL<SIX_XmlDataSet>;
	//	xmlDoc = new TiXmlDocument();
	//	rootElement=0;
	//	pDecl=0;
	//)
	//DESTRUCTOR(
	//	SIX_XMLParser,
	//	ReleaseXMLDataSet();
	//	CC_SAFE_DELETE(xmlDoc);
	//	CC_SAFE_DELETE(pXmlDataSet);
	//)
public:
	SIX_XMLParser()
	{
		pFileUtils = CCFileUtils::sharedFileUtils();
		pXmlDataSet = new SIX_DSTPL<SIX_XmlDataSet>;
		xmlDoc = new TiXmlDocument();
		rootElement=0;
		pDecl=0;	
	}
	~SIX_XMLParser()
	{
		ReleaseXMLDataSet();
		CC_SAFE_DELETE(xmlDoc);
		//CC_SAFE_DELETE(pXmlDataSet);
		CC_SAFE_RELEASE(pXmlDataSet);
	}
public:	
	int LoadXMLFromFile(const char *xmlPath);
	int LoadXMLFromMemory(unsigned char *xmlStream,unsigned long len,int encoding = TIXML_DEFAULT_ENCODING);
	bool LoadMemoryForLinux(TIXML_STRING *pData,unsigned char * pBuff,unsigned long length);
	bool SaveToFile(const char *xmlPath);
	void ReleaseXMLDataSet()
	{
		// �ͷ�XML�ڵ��ͷ��Ϣ
		if (xmlDoc)
			xmlDoc->Clear();

		// �ͷ�DSTPL�ڲ����ݼ���
		if (pXmlDataSet)
			pXmlDataSet->DelAll();
	}

	SIX_DSTPL<SIX_XmlDataSet> *GetXMLDataSet() const {return pXmlDataSet;}
private:
	void LoopNode(TiXmlNode* pParent,SIX_DSTPL<SIX_XmlDataSet> *pNode=0);
private:
	CCFileUtils *pFileUtils;
	TiXmlDocument *xmlDoc;
	TiXmlElement* rootElement;
	TiXmlDeclaration *pDecl;
	SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet;
};