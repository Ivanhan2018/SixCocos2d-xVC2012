#include <SIX_XMLParser.h>

int SIX_XMLParser::LoadXMLFromFile(const char *xmlPath)
{
	const char *path = 0;
	CCString *pFileName = 0;
	int retv = 0;
	// XMLDOC对象创建失败 或 XML文件不存在
	if (!xmlDoc)
	{
		retv = -1;
		goto doExit;
	}

	path = pFileUtils->fullPathFromRelativePath(xmlPath);
	pFileName = CCString::createWithFormat("%s",path);

	// XML解析失败，格式异常等
	if (!xmlDoc->LoadFile(pFileName->getCString()))
	{
		SIXLog("LoadXMLFromFile.Parse[%s].Error[%d].Row[%d].Col[%d]=%s",xmlPath,xmlDoc->ErrorId(),xmlDoc->ErrorRow(),xmlDoc->ErrorCol(),xmlDoc->ErrorDesc());
		retv=-2;
		goto doExit;
	}

	// 版本信息
	pDecl = xmlDoc->FirstChild()->ToDeclaration();
	// 根节点
	rootElement = xmlDoc->RootElement();
	// 遍历
	LoopNode(rootElement,pXmlDataSet);

doExit:
	return retv;
}

int SIX_XMLParser::LoadXMLFromMemory(unsigned char *xmlStream,unsigned long len,int encoding)
{
	TIXML_STRING pData;
	pData.reserve(len);
	const char *pResult = 0;
	int retv = 0;
	bool LoadSuccessed = false;
	// XMLDOC对象创建失败
	if (!xmlDoc)
	{
		retv = -1;
		goto doExit;
	}

	SIXLog("LoadXMLFromMemory.xmlStream[0x%02X/0x%02X/0x%02X][0x%02X/0x%02X/0x%02X].len[%d].encoding[%d]...",
		xmlStream[0],xmlStream[1],xmlStream[2],
		xmlStream[len-3],xmlStream[len-2],xmlStream[len-1],
		len,encoding);

//// ---------------------------------------------------
//// 其实可以不用把Win32下的0D0A替换成Linux下的0A。。。
//// Cool.Cat
//// ---------------------------------------------------
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	LoadSuccessed = LoadMemoryForLinux(&pData,xmlStream,len);
//	SIXLog("LoadXMLFromMemory.encoding[%d].LoadSuccessed[%d]",encoding,LoadSuccessed);
//	if (!LoadSuccessed)
//	{
//		retv = -3;
//		goto doExit;
//	}
//
//	SIXLog("pData[%d]=%s",pData.length(),pData.c_str());
//
//	pResult = xmlDoc->Parse(pData.c_str(),0,(TiXmlEncoding)encoding);
//#else
	pResult = xmlDoc->Parse((const char*)xmlStream,0,(TiXmlEncoding)encoding);
//#endif
	//// XML解析失败，格式异常等
	//// pResult永远返回0，So用ErrodID判断是否成功
	//// Cool.Cat
	//if (!pResult)
	if (xmlDoc->ErrorId()!=0)
	{
		SIXLog("LoadXMLFromMemory.encoding[%d].Parse.Error[%d]=%s",encoding,xmlDoc->ErrorId(),xmlDoc->ErrorDesc());
		retv=-2;
		goto doExit;
	}
	// 版本信息
	pDecl = xmlDoc->FirstChild()->ToDeclaration();
	// 根节点
	rootElement = xmlDoc->RootElement();
	// 遍历
	LoopNode(rootElement,pXmlDataSet);

doExit:
	pData.clear();
	TIXML_STRING().swap(pData);
	return retv;
}

bool SIX_XMLParser::LoadMemoryForLinux(TIXML_STRING *pData,unsigned char * pBuff,unsigned long length)
{
	if (!pBuff || !length || !pData)
		return false;

	char* buf = new char[length+1];
	memcpy(buf,pBuff,length);
	buf[length] = 0;
 
	const char *lastPos = buf;
	const char *p = buf;
	int count = 0;

	while(*p)
	{
		assert(p<(buf+length));
		if ( *p == 0x0D && (*(p+1) && *(p+1)==0x0A))
		{
			// 拷贝换行符之前的内容
			count = p-lastPos;
			if (count)
			{
				//SIXLog("LoadMemoryForLinux.B=%d.text=[%.*s]",count,count,lastPos);
				pData->append(lastPos,count);
				//SIXLog("LoadMemoryForLinux.C.pData[%d]=[%s]",pData->length(),pData->c_str());
			}

			// 追加linux换行符(0x0A)
			(*pData) += 0x0A;

			// 跳过换行符
			p += 2;
			lastPos = p;
			assert(p<=(buf+length));
		}
		else
		{
			++p;
		}
	}
	
	// 剩余的部分
	count = p-lastPos;
	if (count)
	{
		//SIXLog("LoadMemoryForLinux.E=%d",count);
		pData->append(lastPos,count);
		//SIXLog("LoadMemoryForLinux.F.pData[%d]=%s",pData->length(),pData->c_str());
	}
	CC_SAFE_DELETE_ARRAY(buf);

	//SIXLog("LoadMemoryForLinux.Done");

	return true;
}

bool SIX_XMLParser::SaveToFile(const char *xmlPath)
{
	if (xmlDoc)
		return xmlDoc->SaveFile(xmlPath);
	return false;
}

void SIX_XMLParser::LoopNode(TiXmlNode* pParent,SIX_DSTPL<SIX_XmlDataSet> *pNode)
{
	if(!pParent)
		return;

#ifdef DEBUG_PRINT_XML
	SIXLog("pParent=%s",pParent->Value());
	SIXLog("Parent = 0x%08X",pParent->Parent()->Parent());
#endif

	// 添加根节点
	if (!pParent->Parent()->Parent())
	{
		SIX_XmlDataSet *pDataSet = new SIX_XmlDataSet();
		pNode->Add(pDataSet);

		pDataSet->setKey("Root");
		pDataSet->setValue(pParent->Value());
		pDataSet->setParent("");
	}

	TiXmlNode* pchild = pParent->FirstChild();
	while(pchild)
	{
#ifdef DEBUG_PRINT_XML
		SIXLog("Child=%s",pchild->Value());
#endif

		SIX_XmlDataSet *pDataSet = new SIX_XmlDataSet();
		pNode->Add(pDataSet);
		
		pDataSet->setValue(pchild->Value());
		pDataSet->setParent(pchild->Parent()->Value());

		switch( pchild->Type())
		{
			// 注释
		case TiXmlNode::TINYXML_COMMENT:
			{
				pDataSet->setKey("comment");
				break;
			}
			// 节点
		case TiXmlNode::TINYXML_ELEMENT:
			{
				pDataSet->setKey("element");
				// 查找当前节点第一个属性
				TiXmlAttribute* attr = pchild->ToElement()->FirstAttribute();
				if(attr)
				{
					pDataSet->pDataElement = new SIX_DSTPL<SIX_KV>;
					// 遍历当前节点剩下所有属性
					TiXmlNode* node = pchild;
					while(node)
					{
						while(attr)
						{
#ifdef DEBUG_PRINT_XML
							SIXLog("TINYXML_ELEMENT=[%s].[%s]",attr->Name(),attr->Value());
#endif
							SIX_KV *pKV = new SIX_KV();
							pKV->setKey(attr->Name());
							pKV->setValue(attr->Value());
							pDataSet->pDataElement->Add(pKV);

							attr = attr->Next();
						}
						// 下一个相邻元素
						node =  node->NextSiblingElement();
					}
				}
				LoopNode(pchild,pDataSet->pNode);
				break;
			}
		default:
			{
#ifdef DEBUG_PRINT_XML
				SIXLog("LoopNode.Type=%d",pchild->Type());
#endif
				break;
			}
		}

#ifdef DEBUG_PRINT_XML
		if (pchild)
		{
			SIXLog("Parent.Value=%s/%s , child.Value=%s",
				pchild->Parent()->Value(),
				pDataSet->getParent().getCString(),
				pchild->Value()
			);
		}
		else
			SIXLog("Parent.Nil");
		SIXLog("*************************");
#endif

		pchild = pchild->NextSibling();
	}
}