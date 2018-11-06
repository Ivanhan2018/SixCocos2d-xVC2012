#include "Config.h"
#include "tinyxml/tinyxml.h"

/** Returns a std::stringVector that contains all the substd::strings delimited
   by the characters in the passed <code>delims</code> argument.
   @param 
   delims A list of delimiter characters to split by
   @param 
   maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
   parameters is > 0, the splitting process will stop after this many splits, left to right.
   */
std::vector<string> split( const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	std::vector<string> ret;
	unsigned int numSplits = 0;

	// Use STL methods 
	size_t start, pos;
	start = 0;
	do 
	{
		pos = str.find_first_of(delims, start);
		if (pos == start)
		{
			// Do nothing
			start = pos + 1;
		}
		else if (pos == std::string::npos || (maxSplits && numSplits == maxSplits))
		{
			// Copy the rest of the std::string
			ret.push_back( str.substr(start) );
			break;
		}
		else
		{
			// Copy up to delimiter
			ret.push_back( str.substr(start, pos - start) );
			start = pos + 1;
		}
		// parse up to next real data
		start = str.find_first_not_of(delims, start);
		++numSplits;

	} while (pos != std::string::npos);
	return ret;
}

SangongConfig::SangongConfig(const char *xmlFileName/*=0*/)
{
	memset(this,0,sizeof(*this));
	m_BankerProb=0.8f;
	if(xmlFileName!=NULL)
		LoadData(xmlFileName);
}

SangongConfig & SangongConfig::Instance()
{
	static SangongConfig g_SangongConfig("SangongConfig\\SangongConfig.xml");//配置缓冲，只读取了xml文件一次
	return g_SangongConfig;
}

//返回值
//	0			成功
//	1			没有加载文件或打开文件失败
int SangongConfig::LoadData(const char *xmlFileName)
{
	if(xmlFileName==NULL)
		return 1;
	TiXmlDocument* m_xmlDoc = new TiXmlDocument(xmlFileName);
	if (!m_xmlDoc->LoadFile())
	{
		delete m_xmlDoc;
		return 1;
	}
	else
	{
#define SetINT(Node,Attr) {const char*##Attr##=##Node##->Attribute(#Attr);if(##Attr##!=NULL)this->m_##Attr##=atoi(##Attr##);}
#define SetDOUBLE(Node,Attr) {const char*##Attr##=##Node##->Attribute(#Attr);if(##Attr##!=NULL)this->m_##Attr##=atof(##Attr##);}
		TiXmlElement *root = m_xmlDoc->FirstChildElement("config");
		if (root)
		{
			TiXmlElement* Node1=root->FirstChildElement("GameStateMgr");
			if(Node1)
			{
				SetINT(Node1,CallBankerTime)
				SetINT(Node1,CallBankerEndTime)
				SetINT(Node1,CallScoreTime)
				SetINT(Node1,CallScoreEndTime)
				SetINT(Node1,ShowCardTime)
			}
			TiXmlElement* Node2=root->FirstChildElement("Strategy");
			if(Node2)
			{
				SetDOUBLE(Node2,BankerProb)
			}
			TiXmlElement* Node3=root->FirstChildElement("FixCard");
			if(Node3)
			{
				SetINT(Node3,Enable)
				vector<string> vecBanker;
				const char*Banker=Node3->Attribute("Banker");
				if(Banker!=NULL)
				{
					vecBanker=split(Banker,",");
				}
				vector<string> vecNoBanker;
				const char*NoBanker=Node3->Attribute("NoBanker");
				if(NoBanker!=NULL)
				{
					vecNoBanker=split(NoBanker,",");
				}
				if(vecBanker.size()==MAX_COUNT && vecNoBanker.size()==MAX_COUNT)
				{
					for(int i=0;i<MAX_COUNT;i++)
					{
						char* pp=NULL;
						m_cbBankerCardData[i]=strtol(vecBanker[i].c_str(),&pp,16);
						m_cbNoBankerCardData[i]=strtol(vecNoBanker[i].c_str(),&pp,16);
					}
				}
				else
				{
					m_Enable=0;
				}

			}
		}
#undef SetINT
#undef SetDOUBLE
	}
	delete m_xmlDoc;
	this->m_HasLoadOK=true;
	return 0;	
}

int SangongConfig::GetCallBankerTime()const
{
	if(m_CallBankerTime<1000 || m_CallBankerTime>15000)
		return TIME_CALL_BANKER;
	return m_CallBankerTime;
}

int SangongConfig::GetCallBankerEndTime()const
{
	if(m_CallBankerEndTime<1000 || m_CallBankerEndTime>15000)
		return TIME_CALL_BANKER_END;
	return m_CallBankerEndTime;
}

int SangongConfig::GetCallScoreTime()const
{
	if(m_CallScoreTime<1000 || m_CallScoreTime>15000)
		return TIME_CALL_SCORE;
	return m_CallScoreTime;
}

int SangongConfig::GetCallScoreEndTime()const
{
	if(m_CallScoreEndTime<1000 || m_CallScoreEndTime>15000)
		return TIME_CALL_SCORE_END;
	return m_CallScoreEndTime;
}


int SangongConfig::GetShowCardTime()const
{
	if(m_ShowCardTime<1000 || m_ShowCardTime>15000)
		return TIME_SHOW_CARD;
	return m_ShowCardTime;
}


