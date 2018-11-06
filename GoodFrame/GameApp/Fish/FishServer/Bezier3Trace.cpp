#include "Bezier3Trace.h"
#include "tinyxml/tinyxml.h"
#include "ServerCurve.h"
//#include "TimeInterval.h"

CBezier3TraceCache m_Bezier3TraceCache[3]={CBezier3TraceCache("FishTrace/fish_one.xml"),CBezier3TraceCache("FishTrace/fish_S.xml"),CBezier3TraceCache("FishTrace/fish_U.xml")};

//------------------------------------------------------------------------------------------------------
//三阶贝塞尔曲线轨迹缓冲
//------------------------------------------------------------------------------------------------------
CBezier3TraceCache::CBezier3TraceCache(const char *xmlFileName/*=NULL*/)
{
	if(xmlFileName!=NULL)
		LoadData(xmlFileName);
}

CBezier3TraceCache::~CBezier3TraceCache()
{
	m_vecBezier3TraceCache.clear();
}

//返回值
//	0			成功
//	1			打开文件失败
//	2			已经载入数据了
int CBezier3TraceCache::LoadData(const char *xmlFileName)
{
	if( !m_vecBezier3TraceCache.empty() )
		return 2;

	//CTimeInterval timeInterval(true, __FUNCTION__);	// 打印时间间隔

	TiXmlDocument* m_xmlDoc = new TiXmlDocument(xmlFileName);
	if (!m_xmlDoc->LoadFile())
	{
		delete m_xmlDoc;
		return 1;
	}
	else
	{

		TiXmlElement *root = m_xmlDoc->FirstChildElement("RealPath");
		if (root)
		{

			TiXmlElement* Node=root->FirstChildElement("locus");
			for(Node;Node;Node=Node->NextSiblingElement("locus"))
			{
				//comment="上10下1.ini" Count="3" pos0="(1180,1114)" pos1="(1042,605)" pos2="(124,-75)" pos3="(-367,-151)"
				CBezier3TraceNode item;
				const char*comment=Node->Attribute("comment");
				if(comment!=NULL)
					strcpy(item.m_szComment,comment);
				const char*Count=Node->Attribute("Count");
				if(Count!=NULL)
					item.m_nCount=(int)atoi(Count);
				const char*pos0=Node->Attribute("pos0");
				if(pos0!=NULL)
				{
					int x=0,y=0;
					sscanf(pos0,"(%d,%d)",&x,&y);
					item.m_pos0=TPoint(x,y);
				}
				const char*pos1=Node->Attribute("pos1");
				if(pos1!=NULL)
				{
					int x=0,y=0;
					sscanf(pos1,"(%d,%d)",&x,&y);
					item.m_pos1=TPoint(x,y);
				}	
				const char*pos2=Node->Attribute("pos2");
				if(pos2!=NULL)
				{
					int x=0,y=0;
					sscanf(pos2,"(%d,%d)",&x,&y);
					item.m_pos2=TPoint(x,y);
				}	
				const char*pos3=Node->Attribute("pos3");
				if(pos3!=NULL)
				{
					int x=0,y=0;
					sscanf(pos3,"(%d,%d)",&x,&y);
					item.m_pos3=TPoint(x,y);
				}
				item.m_EntryTime=getBezier3EntryTime(item.m_pos0,item.m_pos1,item.m_pos2,item.m_pos3);
				item.m_DepartureTime=getBezier3DepartureTime(item.m_pos0,item.m_pos1,item.m_pos2,item.m_pos3);
				m_vecBezier3TraceCache.push_back(item);
			}
		}

	}
	delete m_xmlDoc;
	return 0;
}


const CBezier3TraceNode * CBezier3TraceCache::getBezier3Trace(int index)
{
	if(index>=0 && index<m_vecBezier3TraceCache.size())
	{
		return &(m_vecBezier3TraceCache[index]);
	}
	return NULL;
}

