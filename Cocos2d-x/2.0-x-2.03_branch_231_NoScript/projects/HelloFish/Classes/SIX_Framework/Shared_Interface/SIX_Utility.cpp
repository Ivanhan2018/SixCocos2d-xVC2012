#include <SIX_Utility.h>
#include <SIX_XMLParser.h>

#ifdef WIN32
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
#endif

#include <math.h>

SIX_Utility *SIX_Utility::m_pUtility = 0;

SIX_MP::SIX_MP()
{
	mp = new MP();
}

SIX_MP::~SIX_MP()
{
	mp->clear();
#ifdef WIN32
	mp->swap(MP());
#endif
	CC_SAFE_DELETE(mp);
}

int SIX_MP::size()
{
	if (mp)
		return mp->size();
	return 0;
}

void SIX_MP::push_back(const char *val)
{
	if (mp)
		mp->push_back(val);
}

void SIX_MP::pop_back()
{
	if (mp)
		mp->pop_back();
}

const char *SIX_MP::at(int idx)
{
	if (mp)
		return mp->at(idx).c_str();
	return 0;
}

// ---------------------------------------
SIX_Utility *SIX_Utility::GetInstance()
{
    if (!m_pUtility)
        m_pUtility = new SIX_Utility();

    return m_pUtility;
}

SIX_Utility::SIX_Utility()
{
#if defined(_WIN32)
	srand((unsigned int)time(0));
	// 先取主频
	LARGE_INTEGER largeInteger;
	QueryPerformanceFrequency(&largeInteger);
	s_invFrequency = double(largeInteger.QuadPart);
	if (s_invFrequency > 0.0)
		s_invFrequency = 1000.0 / s_invFrequency;

	QueryPerformanceCounter(&m_GlobalTimerStart);
#elif defined(__linux__) || defined (__APPLE__)
	gettimeofday(&m_GlobalTimerStart,0);
#endif
}

SIX_Utility::~SIX_Utility()
{
	ReleaseHitBox();
	CC_SAFE_DELETE(pXML);
}

unsigned long SIX_Utility::REVE_DWORD(unsigned long x)
{
#ifdef WIN32
	// 0x12345678 => 0x78563412
	return MAKELONG(MAKEWORD(HIBYTE(HIWORD(x)),LOBYTE(HIWORD(x))),MAKEWORD(HIBYTE(LOWORD(x)),LOBYTE(LOWORD(x))));
#else
	return 0;
#endif
}

unsigned long SIX_Utility::GetCurrentThreadId()
{
#ifdef _WIN32
	return ::GetCurrentThreadId();
#else
	return pthread_self();
#endif
}

// 生成随机数
int SIX_Utility::RNDNUM(int min,int max)
{
	int rndnum = 0;

	rndnum = rand() % (max-min+1) + min;

	if (rndnum<min)
		rndnum=min;

	return rndnum;
};

int SIX_Utility::getIntPart(double x)
{
    if (x <= 0.0)
       return (int)(ceil(x));

    if (ceil(x) == x)
       x = ceil(x);
    else
       x = ceil(x) - 1;
    return (int)(x);
}

int SIX_Utility::code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
    iconv_t cd;

    const char *temp = inbuf;

    const char **pin = &temp;

    char **pout = &outbuf;

    memset(outbuf,0,outlen);

    cd = iconv_open(to_charset,from_charset);

    if(cd==0) 
		return -1;

    if(iconv(cd,pin,&inlen,pout,&outlen)==-1) 
		return -1;

    iconv_close(cd);

    return 0;

}

/*UTF8转GB2312*/
std::string SIX_Utility::U2G(const char *inbuf)
{
	size_t inlen = strlen(inbuf);

	char * outbuf = new char[inlen * 2 + 2];

	std::string strRet;

	if(code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}

	delete [] outbuf;

	return strRet;
}

/*GB2312转UTF8*/
std::string SIX_Utility::G2U(const char *inbuf)
{
	size_t inlen = strlen(inbuf);

	char * outbuf = new char[inlen * 2 + 2];
	memset(outbuf, 0, sizeof(char)*(inlen * 2 + 2));

	std::string strRet;

	if(code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}

	delete [] outbuf;

	return strRet;
}

wstring SIX_Utility::AnsiToUnicode(const char* buf)
{
#ifdef WIN32
	int len = ::MultiByteToWideChar(CP_ACP, 0, buf, -1, 0, 0);
	if (len == 0) return L"";

	std::vector<wchar_t> unicode(len);
	::MultiByteToWideChar(CP_ACP, 0, buf, -1, &unicode[0], len);
	return &unicode[0];
#else
	return 0;
#endif
}

string SIX_Utility::UnicodeToAnsi(const wchar_t* buf)
{
#ifdef WIN32
	int len = ::WideCharToMultiByte(CP_ACP, 0, buf, -1, 0, 0, 0, 0);
	if (len == 0) return "";

	std::vector<char> utf8(len);
	::WideCharToMultiByte(CP_ACP, 0, buf, -1, &utf8[0], len, 0, 0);

	return &utf8[0];
#else
	return 0;
#endif
}

wstring SIX_Utility::Utf8ToUnicode(const char* buf)
{
#ifdef WIN32
	int len = ::MultiByteToWideChar(CP_UTF8, 0, buf, -1, 0, 0);
	if (len == 0) return L"";

	std::vector<wchar_t> unicode(len);
	::MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);

	return &unicode[0];
#else
	return 0;
#endif
}

string SIX_Utility::UnicodeToUtf8(const wchar_t* buf)
{
#ifdef WIN32
	int len = ::WideCharToMultiByte(CP_UTF8, 0, buf, -1, 0, 0, 0, 0);
	if (len == 0) return "";

	std::vector<char> utf8(len);
	::WideCharToMultiByte(CP_UTF8, 0, buf, -1, &utf8[0], len, 0, 0);

	return &utf8[0];
#else
	return 0;
#endif
}

int SIX_Utility::Split(char *sp,char *src,SIX_MP *ptr,int SplitCount)
{
	if (!ptr)
		return 0;

	MP *mp = new MP();
	int retv = Split(sp,src,mp,SplitCount);
	if (mp->size())
	{
		for (unsigned int i=0;i<mp->size();i++)
			ptr->push_back(mp->at(i).c_str());
	}

	mp->clear();
#ifdef WIN32
	mp->swap(MP());
#endif
	CC_SAFE_DELETE(mp);

	return retv;
}

int SIX_Utility::Split(char *sp,char *src,MP *ptr,int SplitCount)
{
	if (!ptr)
		return 0;

	int splen = strlen(sp);
	char *ss=src;
	char *p = ss;
	char *last = ss;

	int index =0;
	int pos = 0;

	string tmpbuff("");

	p=strstr(p,sp);

	while (p)
	{
		// 本轮找到sp的位置
		pos = p - last;

		tmpbuff.resize(pos,0);

		memcpy((void*)tmpbuff.c_str(),last,pos);

		ptr->push_back(tmpbuff.c_str());

		p+=splen;
		last = p;

		if (SplitCount>0 && index==SplitCount-1)
		{
			int lastlen = strlen(src) - (last - ss);
			tmpbuff.resize(lastlen,0);
			memcpy((void*)tmpbuff.c_str(),last,lastlen);
			ptr->push_back(tmpbuff.c_str());
			break;
		}

		p=strstr(p,sp);

		if (!p)
		{
			int lastlen = strlen(src) - (last - ss);
			tmpbuff.resize(lastlen,0);
			memcpy((void*)tmpbuff.c_str(),last,lastlen);
			ptr->push_back(tmpbuff.c_str());
		}
		index++;
	}

	index = ptr->size();

	return index;
}

void SIX_Utility::replace(string &strBig,const string &strsrc,const string &strdst)
{
     string::size_type pos = 0;
     while((pos = strBig.find(strsrc,pos))!= string::npos)
     {
         strBig.replace(pos,strsrc.length(),strdst);
         pos += strdst.length();
     }
}

CCPoint SIX_Utility::getAnotherCoordinate(CCPoint pt, float fAngle, int nDistance)
{
	CCPoint ptReturn(0,0);
	fAngle = (float)(fAngle*M_PI/180);
	ptReturn.x = cos(fAngle)*nDistance + pt.x;
	ptReturn.y = sin(fAngle)*nDistance + pt.y;
	return ptReturn;
}
unsigned long long SIX_Utility::GetTickCount()
{
#ifdef WIN32
	struct __timeb64 tv;
	_ftime64(&tv);
	return tv.time * 1000 + tv.millitm;
#else
	struct timeval tv; 
	gettimeofday(&tv,0);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
}

void SIX_Utility::GetLocalTime(LPSYSTEMTIME st)
{
	if (!st)
		return;

#ifdef WIN32
	::GetLocalTime(st);
#else
	struct timeval tv;
	gettimeofday (&tv , NULL);

	tm tm_now ;
	localtime_r(&tv.tv_sec,&tm_now);

	st->wYear = tm_now.tm_year+1900;
	st->wMonth = tm_now.tm_mon+1;
	st->wDay = tm_now.tm_mday;
	st->wDayOfWeek = (tm_now.tm_wday+1)%7;
	st->wHour =tm_now.tm_hour;
	st->wMinute = tm_now.tm_min;
	st->wSecond = tm_now.tm_sec;
	st->wMilliseconds = tv.tv_usec/1000;
#endif
}

double SIX_Utility::Fixed(double n,int p)
{
	double x = pow(10.0,p);
#ifdef WIN32
	return ((_int64)(n*x+0.5))/x;
#else
	return ((long long)(n*x+0.5))/x;
#endif
}

// 定时器部分
#if defined(_WIN32) && !defined(SHP)

void SIX_Utility::TimerStart()
{
	QueryPerformanceCounter(&m_start);
}

void SIX_Utility::TimerEnd()
{
	QueryPerformanceCounter(&m_end);
}

double SIX_Utility::GetMilliseconds()
{
	return Fixed((s_invFrequency*(m_end.QuadPart-m_start.QuadPart)),4);
}

double SIX_Utility::GetGlobalSecond()
{
	QueryPerformanceCounter(&m_GlobalTimerEnd);
	// 保留小数点后4位
	return Fixed((s_invFrequency*(m_GlobalTimerEnd.QuadPart-m_GlobalTimerStart.QuadPart))/1000.0,4);
}

#elif defined(__linux__) || defined (__APPLE__)

#include <sys/time.h>

void SIX_Utility::TimerStart()
{
	gettimeofday(&m_start,0);
}

void SIX_Utility::TimerEnd()
{
	gettimeofday(&m_end,0);
}

double SIX_Utility::GetMilliseconds()
{
	return (m_end.tv_sec - m_start.tv_sec) * 1000 + m_end.tv_usec * 0.001f - m_start.tv_usec * 0.001f;
}

double SIX_Utility::GetGlobalSecond()
{
	return ((m_GlobalTimerEnd.tv_sec - m_GlobalTimerStart.tv_sec) * 1000 + m_GlobalTimerEnd.tv_usec * 0.001f - m_GlobalTimerStart.tv_usec * 0.001f) * 1000.0f;
}

#else

void SIX_Utility::TimerStart()
{
}

void SIX_Utility::TimerEnd()
{
}

double SIX_Utility::GetMilliseconds()
{
	return 0.0f;
}

double SIX_Utility::GetGlobalSecond()
{
	return 0.0f;
}

#endif

//-- 异步加载plist
//-- 另外还在回调中做以下2步处理：
//-- 1、CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithDictionary(dict,pTexture)
//-- 2、CCSpriteFrameCache:sharedSpriteFrameCache():insertPlist(pszPlist)
bool SIX_Utility::addSpriteFramesWithPlistAsync(CCString *pszPlist,CCObject *target,SEL_CallFuncO selector)
{
	// -- 先获取全路径
	CCString *pszPath = CCString::createWithFormat("%s",CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszPlist->getCString()));
	
	// -- 根据plist取得dict，非线程安全
	CCDictionary *dict = CCDictionary::createWithContentsOfFile(pszPath->getCString());
	
	// -- 根据metadata取得textureFileName
	CCDictionary *metadataDict = dynamic_cast<CCDictionary*>(dict->objectForKey("metadata"));
	if (!metadataDict)
	{
		SIXLog("addSpriteFramesWithPlistAsync.metadataDict.Nil");
		dict->release();
		return false;
	}
	
	CCString *texturePath = CCString::createWithFormat("%s",metadataDict->valueForKey("textureFileName")->getCString());
	if (!texturePath)
	{
		SIXLog("addSpriteFramesWithPlistAsync.texturePath.A.Nil");
		dict->release();
		return false;
	}
	
	texturePath = CCString::createWithFormat("%s",CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(texturePath->getCString(),pszPath->getCString()));
	if (!texturePath)
	{
		SIXLog("texturePath.B.Nil");
		dict->release();
		return false;
	}
	
	// -- 异步加载
	CCTextureCache::sharedTextureCache()->addImageAsync(texturePath->getCString(),target,selector);
	
	dict->release();
	
	//SIXLog("[0x%08X]addSpriteFramesWithPlistAsync.pszPlist[%s].Done",SIX_Utility::GetInstance()->GetCurrentThreadId(),pszPlist->getCString());

	return true;
}

int SIX_Utility::s2n(char s)
{
	if (s>=48 && s<=57)
		return s-48;
	else if (s>=65 && s<=70)
		return s-55;
	return 0;
}

// 传入整数，返回个数，计算负号
int SIX_Utility::GetNumberLength(long long number)
{
	int len = (number<0)?1:0;
	CCString *pNumArr = CCString::createWithFormat("%lld",number);
	string numStr(pNumArr->getCString());
	len += numStr.length();
	pNumArr->release();
	return len;
}

// 根据数字获取精灵并添加批处理精灵
// Cool.Cat
bool SIX_Utility::AddSpriteBatchNodeByNumber(CCSpriteBatchNode *pBatchNode,const char *file,int cell,float padding,int bitcount,unsigned int num)
{
	if (cell<=0)
	{
		CCAssert(cell>0,"cell must more than zero");
		return false;
	}

	if (!pBatchNode)
	{
		CCAssert(pBatchNode,"pBatchNode nil");
		return false;
	}

	//// 必然被整除
	//int result = (int)(pBatchNode->getTexture()->getContentSize().width)%cell;
	//if (result!=0)
	//{
	//	CCAssert(result==0,"pBatchNode width isn't integer multiple for cell");
	//	return false;
	//}

	// 位宽
	float cell_width = (float)(pBatchNode->getTexture()->getContentSize().width/cell);
	float cell_height = pBatchNode->getTexture()->getContentSize().height;
	CCString *pNumArr = CCString::createWithFormat("%u",num);
	string numStr(pNumArr->getCString());
	// 位数不足要补0
	int zerofill = bitcount - numStr.length();
	if (zerofill>0)
		for (int i=0;i<zerofill;i++)
			numStr.insert(0,"0");
	for (unsigned int i=0;i<numStr.length();i++)
	{
		int value = s2n(numStr.at(i));
		CCSprite *pSpr = CCSprite::spriteWithFile(file,CCRect((float)(value*cell_width),0.0f,cell_width,cell_height));
		if (!pSpr)
		{
			CCAssert(pSpr,"pSpr nil");
			continue;
		}
		if (i==0)
			pSpr->setPosition(ccp(i*cell_width-pSpr->getContentSize().width/2,cell_height-pSpr->getContentSize().height/2));
		else
			pSpr->setPosition(ccp(i*(cell_width+padding)-pSpr->getContentSize().width/2,cell_height-pSpr->getContentSize().height/2));
		//pSpr->ignoreAnchorPointForPosition(true);
		pBatchNode->addChild(pSpr);
	}
	pNumArr->release();
	return true;
}

// -- 重复执行
CCAction *SIX_Utility::schedule(CCNode *node, SEL_CallFunc callback, float delay)
{
    CCDelayTime *pDelay = CCDelayTime::create(delay);
    CCCallFunc *callfunc = CCCallFunc::create(node,callback);
    CCActionInterval *sequence = dynamic_cast<CCActionInterval*>(CCSequence::createWithTwoActions(pDelay, callfunc));
    CCRepeatForever *action = CCRepeatForever::create(sequence);
    node->runAction(action);
    return action;
}

CCAction *SIX_Utility::schedule(CCNode *node, SEL_CallFuncN callback, float delay)
{
    CCDelayTime *pDelay = CCDelayTime::create(delay);
    CCCallFuncN *callfunc = CCCallFuncN::create(node,callback);
    CCActionInterval *sequence = dynamic_cast<CCActionInterval*>(CCSequence::createWithTwoActions(pDelay, callfunc));
    CCRepeatForever *action = CCRepeatForever::create(sequence);
    node->runAction(action);
    return action;
}

// -- 执行一次
CCAction *SIX_Utility::performWithDelay(CCNode *node, SEL_CallFunc callback, float delay)
{
    CCDelayTime *pDelay = CCDelayTime::create(delay);
    CCCallFunc *callfunc = CCCallFunc::create(node,callback);
    CCSequence *sequence = CCSequence::createWithTwoActions(pDelay, callfunc);
    node->runAction(sequence);
    return sequence;
}

CCAction *SIX_Utility::performWithDelay(CCNode *node, SEL_CallFuncN callback, float delay)
{
    CCDelayTime *pDelay = CCDelayTime::create(delay);
    CCCallFuncN *callfunc = CCCallFuncN::create(node,callback);
    CCSequence *sequence = CCSequence::createWithTwoActions(pDelay, callfunc);
    node->runAction(sequence);
    return sequence;
}

bool SIX_Utility::LoadHitBoxFromFile(const char *pccPath)
{
	//SIXLog("TID[0x%08X].LoadHitBoxFromFile.Begin[%s]",this->GetCurrentThreadId(),pccPath);
	const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pccPath);
	string pFileName(path);
	TiXmlDocument *xmlDoc = new TiXmlDocument();
	if (!xmlDoc->LoadFile(pFileName.c_str()))
	{
		SIXLog("导入配置文件失败！");
		CC_SAFE_DELETE_ARRAY(path);
		CC_SAFE_DELETE(xmlDoc);
		return false;
	}
	CC_SAFE_DELETE_ARRAY(path);
	TiXmlElement *rootElement = xmlDoc->RootElement();
	ParseXML(rootElement);
	CC_SAFE_DELETE(xmlDoc);
	//SIXLog("TID[0x%08X].LoadHitBoxFromFile.End[%s]",this->GetCurrentThreadId(),pccPath);
	return true;
}

void SIX_Utility::ParseXML(TiXmlElement *rootElement)
{
	if (!rootElement)
		return;

	TiXmlNode* pchild = rootElement->FirstChild();
	while (pchild)
	{
		if (!STRCMP(pchild->Value(),"Sprite"))
		{
			switch( pchild->Type())
			{
			case TiXmlNode::TINYXML_ELEMENT:
				{
					TiXmlNode* pFrameNode = pchild->FirstChild();
					while (pFrameNode)
					{
						// 查找Frame Name属性
						TiXmlAttribute* attrFrameName = pFrameNode->ToElement()->FirstAttribute();
						if(attrFrameName)
						{
							HITBOX_MAP *pHBox = new HITBOX_MAP();
							frameHBox.insert(FHITBOX_MAP::value_type(attrFrameName->Value(),pHBox));

							// 查找Pos节点
							TiXmlNode* pPosNode = pFrameNode->FirstChild();
							while (pPosNode)
							{
								// 查找Pos属性
								int idx = 0;
								POINT_INFO *pPoint = new POINT_INFO();
								TiXmlAttribute* attrPos = pPosNode->ToElement()->FirstAttribute();
								while (attrPos)
								{
									if (!STRCMP(attrPos->Name(),"idx"))
									{
										idx = atoi(attrPos->Value());									
									}
									else if (!STRCMP(attrPos->Name(),"x"))
									{
										pPoint->x = (float)atof(attrPos->Value());
									}
									else if (!STRCMP(attrPos->Name(),"y"))
									{
										pPoint->y = (float)atof(attrPos->Value());
									}
									attrPos = attrPos->Next();
								}

								pHBox->insert(HITBOX_MAP::value_type(idx,pPoint));
								
								pPosNode = pPosNode->NextSibling();
							}
						}
						// 下一个相邻节点
						pFrameNode = pFrameNode->NextSibling();
					}
					break;
				}
			}
		}
		// 下一个相邻节点
		pchild = pchild->NextSibling();
	}
}

//void SIX_Utility::ParseXML(SIX_XMLParser *pXML)
//{
//	SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet = pXML->GetXMLDataSet();
//
//	SIX_XmlDataSet *pDataSet = 0;
//
//	//SIXLog("ParseXML.GetChildrenCount[%d]",pXmlDataSet->GetChildrenCount());
//	CCARRAY_FOREACH_T(pXmlDataSet->GetChildren(),pDataSet,SIX_XmlDataSet*)
//	{
//		// 跳过Root和Comment
//		if (pDataSet->getKey().compareIgnoreCase("Element"))
//			continue;
//
//		if (pDataSet->pDataElement)
//		{
//			if (!pDataSet->getValue().compareIgnoreCase("Sprite"))
//			{
//				// get frame
//				string frameName;;
//				SIX_XmlDataSet *pDataSetFrame = 0;
//				CCARRAY_FOREACH_T(pDataSet->pNode->GetChildren(),pDataSetFrame,SIX_XmlDataSet*)
//				{
//					SIX_KV *pKVFrame = 0;
//					CCARRAY_FOREACH_T(pDataSetFrame->pDataElement->GetChildren(),pKVFrame,SIX_KV*)
//					{
//						if (!pKVFrame->getKey().compareIgnoreCase("name"))
//						{
//							frameName.clear();
//							//CCString *pFrameName = CCString::stringWithFormat("%s",pKVFrame->getValue().getCString());
//							frameName.append(pKVFrame->getValue().getCString());
//						}
//					}
//
//					// get pos
//					SIX_XmlDataSet *pDataSetPos = 0;
//					HITBOX_MAP *pHBox = new HITBOX_MAP();
//					int posCount = 0;
//					CCARRAY_FOREACH_T(pDataSetFrame->pNode->GetChildren(),pDataSetPos,SIX_XmlDataSet*)
//					{
//						unsigned int idx = 0;
//						POINT_INFO *pPoint = new POINT_INFO();
//						// 此处要做2次检测填充，否则CCArray::objectAtIndex(idx)当idx超过object子节点总数量时会引发CCAssert
//						for (int i=0;i<min(pDataSetPos->pDataElement->GetChildrenCount(),MAX_VERTEX_COUNT);i++)
//						{
//							SIX_KV *pKV = pDataSetPos->pDataElement->Get(i);
//							if (pKV)
//							{
//								if (!pKV->getKey().compareIgnoreCase("idx"))
//									idx = atoi(pKV->getValue().getCString());
//								else if (!pKV->getKey().compareIgnoreCase("x"))
//									pPoint->x = (float)strtod(pKV->getValue().getCString(),0);
//								else if (!pKV->getKey().compareIgnoreCase("y"))
//									pPoint->y = (float)strtod(pKV->getValue().getCString(),0);
//							}
//						}
//						posCount++;
//						pHBox->insert(HITBOX_MAP::value_type((idx==0)?posCount:idx,pPoint));
//					}
//
//					for (int i=posCount;i<MAX_VERTEX_COUNT;i++)
//					{
//						POINT_INFO *pPoint = new POINT_INFO(-1.0f,-1.0f);
//						pHBox->insert(HITBOX_MAP::value_type(i+1,pPoint));
//					}
//					if (frameName.length())
//					{
//						frameHBox.insert(FHITBOX_MAP::value_type(frameName,pHBox));
//					}
//				}
//			}
//		}
//	}
//}

HITBOX_MAP *SIX_Utility::GetHitBoxByFrameName(const char *frameName)
{
	if (!frameName)
		return 0;

	FHITBOX_ITER iter = frameHBox.find(frameName);
	if (iter==frameHBox.end())
		return 0;
	return iter->second;
}

void SIX_Utility::AddHitBox()
{
	for (FHITBOX_ITER iter = frameHBox.begin();iter!=frameHBox.end();)
	{
		HITBOX_MAP *pHitBox = iter->second;
		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(iter->first.c_str());
		if (pFrame)
		{
			//pFrame->getTexture()->setHitBox(pHitBox);
			pFrame->setObjName(iter->first.c_str());
			pFrame->setHitBox(pHitBox);
			frameHBox.erase(iter++);
			// pHitBox会在pFrame析构时销毁，所以不用在这里销毁
			// Cool.Cat
			//CC_SAFE_DELETE(pHitBox);
		}
		// 如果frame不存在，说明HBox配置文件有错误，我们就在这里先销毁
		else
		{
			frameHBox.erase(iter++);
			CC_SAFE_DELETE(pHitBox);
		}
	}
}

// 实际上这个函数只有当AddHitBox未调用时才有意义，可以释放掉HBox占用的map内存及自身指针；
// 如果已经调用了AddHitBox，那么在当时已经把HBox占用的map内存释放掉了，所以在这种情况下无意义。
// Cool.Cat
void SIX_Utility::ReleaseHitBox()
{
	for (FHITBOX_ITER iter = frameHBox.begin();iter!=frameHBox.end();)
	{
		HITBOX_MAP *pHitBox = iter->second;
		frameHBox.erase(iter++);
		CC_SAFE_DELETE(pHitBox);
	}
}

// 2D/3D纹理抗锯齿
void SIX_Utility::FixedTexParameters(CCTexture2D *pTexture)
{
	if (!pTexture)
		return;
	ccDirectorProjection mProjection = CCDirector::sharedDirector()->getProjection();
	if (mProjection==kCCDirectorProjection3D || mProjection==kCCDirectorProjectionDefault)
		pTexture->setAliasTexParameters();
	else
		pTexture->setAntiAliasTexParameters();
}

string SIX_Utility::NTOA(long long ip)
{
	struct in_addr in;
	memcpy(&in,&ip,4);
	return string(inet_ntoa(in));
}

bool SIX_Utility::IsSceneRunning(CCNode *pUIScene,const char *SceneName)
{
	if(!pUIScene || (pUIScene && !pUIScene->isRunning()) || !SceneName)
		return false;

	// 要检查是否在游戏场景
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return false;
	if (!pScene->getChildren())
		return false;
	CCObject *pObject = pScene->getChildren()->objectAtIndex(0);
	if (!pObject)
		return false;
	if (STRCMP(pObject->getObjName(),SceneName))
		return false;
	return true;
}

CCControlButton *SIX_Utility::CreateButtonWithFrameName(const char *pszSpriteFrameName)
{
	CCControlButton *pBtn = 0;
	if (!pszSpriteFrameName)
		return pBtn;
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    if (!pFrame)
		return 0;
	CCScale9Sprite *pScale9Sprite = CCScale9Sprite::createWithSpriteFrame(pFrame);
	if (!pScale9Sprite)
		return 0;
	pBtn = CCControlButton::create(pScale9Sprite);
	if (!pBtn)
		return 0;
	pBtn->ignoreAnchorPointForPosition(true);
	pBtn->setZoomFactor(1.05f);
	pBtn->setPreferredSize(pFrame->getTexture()->getContentSize());
	return pBtn;
}

CCControlButton *SIX_Utility::CreateButtonWithFile(const char *file,CCRect rc,const char *text,const char *fontName,int fontSize)
{
	CCControlButton *pBtn = 0;
	if (!file)
		return pBtn;

	CCScale9Sprite *pScale9Sprite = 0;
	if (rc.equals(CCRectZero))
		pScale9Sprite = CCScale9Sprite::create(file);
	else
		pScale9Sprite = CCScale9Sprite::create(file,rc);
	if (!pScale9Sprite)
		return 0;
	if (!text)
		pBtn = CCControlButton::create(pScale9Sprite);
	else
	{
		CCLabelTTF *pTextTTF = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(text).c_str(),fontName,(float)fontSize);
		pBtn = CCControlButton::create(pTextTTF,pScale9Sprite);
		SIX_Utility::GetInstance()->FixedTexParameters(pTextTTF->getTexture());
	}
	if (!pBtn)
		return 0;
	pBtn->ignoreAnchorPointForPosition(true);
	pBtn->setZoomFactor(1.05f);
	pBtn->setPreferredSize(pScale9Sprite->getOriginalSize());
	return pBtn;
}

CCControlButton *SIX_Utility::CreateButtonWithFileCell(const char *file,int cell,bool Hor)
{
	CCControlButton *pBtn = 0;
	if (!file || cell<=1 || cell>=5)
		return pBtn;

	// 四态九宫格
	CCScale9Sprite *pScale9SpriteNor = 0;
	CCScale9Sprite *pScale9SpriteHov = 0;
	CCScale9Sprite *pScale9SpriteSel = 0;
	CCScale9Sprite *pScale9SpriteDis = 0;

	float cell_width = 0.0f;
	float cell_height = 0.0f;
	if (!SplitSpriteWithCell(file,&pScale9SpriteNor,&pScale9SpriteHov,&pScale9SpriteSel,&pScale9SpriteDis,&cell_width,&cell_height,cell,Hor))
		return 0;

	// 必须要有常态，且长宽均不为零
	if (!pScale9SpriteNor || cell_width==0.0f || cell_height==0.0f)
		return 0;

	// 以常态创建按钮先~
	pBtn = CCControlButton::create(pScale9SpriteNor);
	if (!pBtn)
		return pBtn;

	// 高亮
	if (pScale9SpriteHov)
		pBtn->setBackgroundSpriteForState(pScale9SpriteHov,CCControlStateHighlighted);
	// 选中
	if (pScale9SpriteSel)
		pBtn->setBackgroundSpriteForState(pScale9SpriteSel,CCControlStateSelected);
	// 禁用
	if (pScale9SpriteDis)
		pBtn->setBackgroundSpriteForState(pScale9SpriteDis,CCControlStateDisabled);

	pBtn->ignoreAnchorPointForPosition(true);
	pBtn->setZoomFactor(1.05f);
	pBtn->setPreferredSize(CCSize(cell_width,cell_height));
	return pBtn;
}

bool SIX_Utility::SplitSpriteWithCell(const char *file,CCScale9Sprite **Nor,CCScale9Sprite **Hov,CCScale9Sprite **Sel,CCScale9Sprite **Dis,float *cell_width,float *cell_height,int cell,bool IsHor)
{
	if (*Nor || *Hov || *Sel || *Dis)
		return false;

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(file);
	float width = pTexture->getContentSize().width;
	float height = pTexture->getContentSize().height;
	*cell_width = width;
	*cell_height = height;

	// 横向切割
	if (IsHor)
	{
		*cell_width = width/cell;
		for (int i=0;i<cell;i++)
		{
			CCRect rect = CCRectZero;
			rect.origin.x = (i * width)/cell;
			rect.origin.y = 0;
			rect.size.width = *cell_width;
			rect.size.height = height;
			CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pTexture,rect);

			if (i==0)
				*Nor = CCScale9Sprite::createWithSpriteFrame(pFrame);
			else if (i==1)
				*Hov = CCScale9Sprite::createWithSpriteFrame(pFrame);
			else if (i==2)
				*Sel = CCScale9Sprite::createWithSpriteFrame(pFrame);
			else if (i==3)
				*Dis = CCScale9Sprite::createWithSpriteFrame(pFrame);
		}
	}
	// 纵向切割
	else
	{
		*cell_height = height/cell;
		for (int i=0;i<cell;i++)
		{
			CCRect rect = CCRectZero;
			rect.origin.x = 0;
			rect.origin.y = (i * height)/cell;
			rect.size.width = width;
			rect.size.height = *cell_height;
			CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pTexture,rect);

			if (i==0)
				*Nor = CCScale9Sprite::createWithSpriteFrame(pFrame);
			else if (i==1)
				*Hov = CCScale9Sprite::createWithSpriteFrame(pFrame);
			else if (i==2)
				*Sel = CCScale9Sprite::createWithSpriteFrame(pFrame);
			else if (i==3)
				*Dis = CCScale9Sprite::createWithSpriteFrame(pFrame);
		}	
	}
	return true;
}

const char *SIX_Utility::GetAppBasePath(const char *folder)
{
	CCString *pAppBasePath = 0;
#ifdef WIN32
	TCHAR tmp_path[1024]={0};
	memset(tmp_path,0,sizeof(tmp_path));
	GetModuleFileName(0,tmp_path, 1023);

	string szDir(SIX_Utility::GetInstance()->UnicodeToUtf8(tmp_path));

	int o1;
	o1=szDir.rfind('\\');

	if (folder && strlen(folder))
		pAppBasePath = CCString::createWithFormat("%s\\%s\\",szDir.substr(0,o1).c_str(),folder);
	else
		pAppBasePath = CCString::createWithFormat("%s\\",szDir.substr(0,o1).c_str());
	
#endif
	return pAppBasePath->getCString();
}