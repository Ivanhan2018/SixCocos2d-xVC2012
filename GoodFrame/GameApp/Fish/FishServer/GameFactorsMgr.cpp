#include "GameFactorsMgr.h"
#include "AwardPool.h"
#include "FishTable.h"
#include "EndlessLoopGuard.h"
#include "tinyxml/tinyxml.h"
#include<algorithm>
using namespace std;

extern TFishPos ARR_FISHPOS[];
extern int ARR_FISHPOS_COUNT;
extern TFishPos ARR_FISHPOS_WH0[];
extern int ARR_FISHPOS_WH0_COUNT;
extern TFishPos ARR_FISHPOS_WH1[];
extern int ARR_FISHPOS_WH1_COUNT;
extern TFishPos ARR_FISHPOS_WH2[];
extern int ARR_FISHPOS_WH2_COUNT;
extern vector<TFishPos> g_vec;
extern vector<TFishPos> g_vecWH0;
extern vector<TFishPos> g_vecWH1;
extern vector<TFishPos> g_vecWH2;
extern vector<TFishPos> g_vecRToL;
extern vector<TFishPos> g_vecWH0RToL;
extern vector<TFishPos> g_vecWH1RToL;
extern vector<TFishPos> g_vecWH2RToL;

PoolAndFish & PoolAndFish::Instance()
{
	static PoolAndFish g_PoolAndFish("PoolConfig\\PoolAndFish.xml");//奖池配置缓冲，只读取了xml文件一次
	return g_PoolAndFish;
}

/** Returns a std::stringVector that contains all the substd::strings delimited
   by the characters in the passed <code>delims</code> argument.
   @param 
   delims A list of delimiter characters to split by
   @param 
   maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
   parameters is > 0, the splitting process will stop after this many splits, left to right.
   */
std::vector<string> PoolAndFish::split( const std::string& str, const std::string& delims/* = "\t\n "*/, unsigned int maxSplits/* = 0*/)
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

//--[[
//获得圆上点的坐标
//参数说明：
//startP--轨迹起点坐标
//centerP--圆心坐标
//deltArg--相对于轨迹起点的辐角主值增量	
//]]
TPos PoolAndFish::GetCirclePos(TPos startP,TPos centerP,float deltArg)
{
	float startarg=atan2(startP.y-centerP.y,startP.x-centerP.x);//--轨迹起点相对于圆心的辐角主值
	float tempx=(startP.x-centerP.x)*(startP.x-centerP.x);
	float tempy=(startP.y-centerP.y)*(startP.y-centerP.y);
	float r=sqrt(tempx+tempy);//--圆的半径
	float x=r*cos(startarg+deltArg);//--圆上点相对于圆心的X坐标偏移
	float y=r*sin(startarg+deltArg);//圆上点相对于圆心的Y坐标偏移
	TPos ret;
	ret.x=centerP.x+x;
	ret.y=centerP.y+y;
	return ret;
}

vector<TFishPos> PoolAndFish::GetAxisymmetricFishPos(const vector<TFishPos>& vFishs)
{
	vector<TFishPos> retvFishs=vFishs;
	for(int i=0;i<retvFishs.size();i++)
	{
		retvFishs[i].x=1280-retvFishs[i].x;
	}
	return retvFishs;
}

bool PoolAndFish::LoadFishGroupType234(TiXmlElement* Node,TFishGroupType FishGroupType,vector<TFishPos> &vec)
{
	if(Node==NULL||FishGroupType<2||FishGroupType>4)
		return false;
	int ColNum=0;
	vector<string> vecFishKinds;
	const char*FishKinds=Node->Attribute("FishKinds");
	if(FishKinds!=NULL)
	{
		vecFishKinds=split(FishKinds,",");
		ColNum=vecFishKinds.size();
	}
	vector<string> vecstartPs;
	vector<TPos> vecstartPs1;
	const char*startPs=Node->Attribute("startPs");
	if(startPs!=NULL)
	{
		vecstartPs=split(startPs,";");
		if(ColNum!=vecstartPs.size())
			return false;
		for(int i=0;i<vecstartPs.size();i++)
		{
			vector<string> vec1=split(vecstartPs[i],",");
			if(vec1.size()==2)
			{
				TPos pos={atof(vec1[0].c_str()),atof(vec1[1].c_str())};
				vecstartPs1.push_back(pos);
			}
		}
		if(ColNum!=vecstartPs1.size())
			return false;
	}
	vector<string> vecRowNum;
	const char*RowNum=Node->Attribute("RowNum");
	if(RowNum!=NULL)
	{
		vecRowNum=split(RowNum,",");
		if(ColNum!=vecRowNum.size())
			return false;
	}
	//vector<TFishPos> vec;
	int deltY=0;
	const char*szdeltY=Node->Attribute("deltY");
	if(szdeltY!=NULL)
	{
		deltY=atof(szdeltY);
	}
	for(int j=0;j<ColNum;j++)
	{
		TPos startP=vecstartPs1[j];
		//中间的鱼
		{
			//TPos startPi=vecstartPs1[j];
			TFishPos fpos;
			fpos.x=vecstartPs1[j].x;
			fpos.y=vecstartPs1[j].y;
			fpos.FishKind=atoi(vecFishKinds[j].c_str());
			vec.push_back(fpos);
		}
		int num=atoi(vecRowNum[j].c_str())/2;
		//上面的鱼
		for (int i=1;i<=num;i++)
		{
			//FishGroupType=2
			float startPix=vecstartPs1[j].x;
			//FishGroupType=3
			if(FishGroupType==3)
				startPix=vecstartPs1[j].x-(i*deltY)*(i*deltY)*0.001;
			//FishGroupType=4
			if(FishGroupType==4)
				startPix=vecstartPs1[j].x+(i*deltY)*(i*deltY)*0.001;
			float startPiy=vecstartPs1[j].y+i*deltY;
			TFishPos fpos;
			fpos.x=startPix;
			fpos.y=startPiy;
			fpos.FishKind=atoi(vecFishKinds[j].c_str());
			vec.push_back(fpos);
		}
		//下面的鱼
		for (int i=1;i<=num;i++)
		{
			//FishGroupType=2
			float startPix=vecstartPs1[j].x;
			//FishGroupType=3
			if(FishGroupType==3)
				startPix=vecstartPs1[j].x-(i*deltY)*(i*deltY)*0.001;
			//FishGroupType=4
			if(FishGroupType==4)
				startPix=vecstartPs1[j].x+(i*deltY)*(i*deltY)*0.001;
			float startPiy=vecstartPs1[j].y-i*deltY;
			TFishPos fpos;
			fpos.x=startPix;
			fpos.y=startPiy;
			fpos.FishKind=atoi(vecFishKinds[j].c_str());
			vec.push_back(fpos);
		}
	}
	//m_vecAll2.push_back(vec);
	return true;
}

//返回值
//	0			成功
//	1			没有加载文件或打开文件失败
int PoolAndFish::LoadData(const char *xmlFileName)
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
#define SetDOUBLE(Node,Attr) {const char*##Attr##=##Node##->Attribute(#Attr);if(##Attr##!=NULL)this->m_##Attr##=atof(##Attr##);}
#define SetDOUBLEx(Node,Attr,x) {const char*##Attr##=##Node##->Attribute(#Attr);if(##Attr##!=NULL)this->m_##Attr##_##x##=atof(##Attr##);}
#define SetINTx(Node,Attr,x) {const char*##Attr##=##Node##->Attribute(#Attr);if(##Attr##!=NULL)this->m_##Attr##_##x##=atoi(##Attr##);}
#define SetINT(Node,Attr) {const char*##Attr##=##Node##->Attribute(#Attr);if(##Attr##!=NULL)this->m_##Attr##=atoi(##Attr##);}
		TiXmlElement *root = m_xmlDoc->FirstChildElement("config");
		if (root)
		{
			TiXmlElement* Node1=root->FirstChildElement("PoolDrawAndDropWater");
			if(Node1)
			{
				const char*Vh0=Node1->Attribute("Vh0");
				if(Vh0!=NULL)
					this->m_Vh0=atof(Vh0);
				SetDOUBLE(Node1,Vl0)
				SetDOUBLE(Node1,V0)
				SetDOUBLE(Node1,V)
				SetDOUBLE(Node1,loVh)
				SetDOUBLE(Node1,hiVh)
				SetDOUBLE(Node1,loVl)
				SetDOUBLE(Node1,hiVl)
				SetDOUBLE(Node1,mul)
				SetDOUBLE(Node1,muh)
				SetDOUBLE(Node1,mu)
			}
			TiXmlElement* Node2=root->FirstChildElement("CollisionScore");
			if(Node2)
			{
				SetDOUBLE(Node2,pil)
				SetDOUBLE(Node2,pih)
			}
			TiXmlElement* Node3=root->FirstChildElement("GameFactors");
			if(Node3)
			{
				TiXmlElement* Node31=Node3->FirstChildElement("GameDifficulty_x1");
				if(Node31)
				{
					SetINTx(Node31,Difficulty,x1)
					SetINTx(Node31,Score,x1)
					SetINTx(Node31,Weight,x1)
					SetDOUBLEx(Node31,ProbValue,x1)
				}
				TiXmlElement* Node32=Node3->FirstChildElement("CannonGrade_x2");
				if(Node32)
				{
					SetINTx(Node32,CannonGrade,x2)
					SetINTx(Node32,Score,x2)
					SetINTx(Node32,Weight,x2)
					SetDOUBLEx(Node32,ProbValue,x2)
				}
				TiXmlElement* Node33=Node3->FirstChildElement("PoolWaterLevelRatio_x4");
				if(Node33)
				{
					SetINTx(Node33,Score,x4)
					SetINTx(Node33,Weight,x4)
					SetDOUBLEx(Node33,ProbValue,x4)
				}
				TiXmlElement* Node34=Node3->FirstChildElement("PlayerLuck_x6");
				if(Node34)
				{
					SetINTx(Node34,PlayerLuck,x6)
					SetINTx(Node34,Score,x6)
					SetINTx(Node34,Weight,x6)
					SetDOUBLEx(Node34,ProbValue,x6)
				}
				TiXmlElement* Node35=Node3->FirstChildElement("PlayerProfit_x7");
				if(Node35)
				{
					SetINTx(Node35,PlayerProfit,x7)
					SetINTx(Node35,Score,x7)
					SetINTx(Node35,Weight,x7)
					SetDOUBLEx(Node35,ProbValue,x7)
				}
				TiXmlElement* Node36=Node3->FirstChildElement("PlayerNewFlag_x8");
				if(Node36)
				{
					SetINTx(Node36,PlayerNewFlag,x8)
					SetINTx(Node36,Score,x8)
					SetINTx(Node36,Weight,x8)
					SetDOUBLEx(Node36,ProbValue,x8)
				}
				TiXmlElement* Node37=Node3->FirstChildElement("PlayerGameTime_x9");
				if(Node37)
				{
					SetINTx(Node37,PlayerGameTime,x9)
					SetINTx(Node37,Score,x9)
					SetINTx(Node37,Weight,x9)
					SetDOUBLEx(Node37,ProbValue,x9)
				}
				TiXmlElement* Node38=Node3->FirstChildElement("FishGameFactor_x5");
				if(Node38)
				{
					SetINTx(Node38,FishNumOfAck,x5)
					SetINTx(Node38,Score,x5)
					SetINTx(Node38,Weight,x5)
					SetDOUBLEx(Node38,ProbValue,x5)
				}
			}
			TiXmlElement* Node4=root->FirstChildElement("FishStateMgr");
			if(Node4)
			{
				//SetINT(Node4,SwitchSceneTime)
				SetINT(Node4,CaptureTime)
				SetINT(Node4,OffTime)
				SetINT(Node4,CaptureBuildTraceTime)
				SetINT(Node4,OffBuildTraceTime)
				SetDOUBLE(Node4,IsFishProb)
				vector<string> vecSeq;
				const char*TypeSeq=Node4->Attribute("TypeSeq");
				if(TypeSeq!=NULL)
				{
					vecSeq=PoolAndFish::split(TypeSeq,",");
				}
				for(int i=0;i<vecSeq.size();i++)
				{
					m_vecTypeSeq.push_back(atoi(vecSeq[i].c_str()));
				}
				if(m_vecTypeSeq.size()==0)
				{
					int TypeSeq[8]={1,2,3,1,2,4,1,5};
					vector<int> vec(TypeSeq,TypeSeq+8);
					m_vecTypeSeq=vec;
				}
			}
			TiXmlElement* Node401=root->FirstChildElement("AllFishGroupTypeSeq");
			if(Node401)
			{
				TiXmlElement* Node=Node401->FirstChildElement("FishGroupTypeSeq");
				for(Node;Node;Node=Node->NextSiblingElement("FishGroupTypeSeq"))
				{
					int Num=0;
					vector<OffFishState::TFishGroupTypeSeqElem> vSeq;
					vector<string> vecSeq;
					const char*Seq=Node->Attribute("Seq");
					if(Seq!=NULL)
					{
						vecSeq=split(Seq,";");
						Num=vecSeq.size();
					}
					for(int i=0;i<vecSeq.size();i++)
					{
						vector<string> vec1=split(vecSeq[i],",");
						if(vec1.size()==2)
						{
							OffFishState::TFishGroupTypeSeqElem SeqElem={atoi(vec1[0].c_str()),_atoi64(vec1[1].c_str())};
							vSeq.push_back(SeqElem);
						}
					}
					if(vSeq.size()>0)
					{
						m_vecAllFishGroupTypeSeq.push_back(vSeq);
					}
				}

			}
			TiXmlElement* Node5=root->FirstChildElement("AllFishGroupType1");
			if(Node5)
			{
				//<FishGroupType1 FishKinds="4,5,6,12" startPs="-600,360;-550,360;-500,360;-250,360" RowNum="30,25,20,1" centerP="-300,360"></FishGroupType1>
				SetINTx(Node5,FishMoveSecs,1)
				TiXmlElement* Node=Node5->FirstChildElement("FishGroupType1");
				for(Node;Node;Node=Node->NextSiblingElement("FishGroupType1"))
				{
					int ColNum=0;
					vector<string> vecFishKinds;
					const char*FishKinds=Node->Attribute("FishKinds");
					if(FishKinds!=NULL)
					{
						vecFishKinds=split(FishKinds,",");
						ColNum=vecFishKinds.size();
					}
					vector<string> vecstartPs;
					vector<TPos> vecstartPs1;
					const char*startPs=Node->Attribute("startPs");
					if(startPs!=NULL)
					{
						vecstartPs=split(startPs,";");
						if(ColNum!=vecstartPs.size())
							continue;
						for(int i=0;i<vecstartPs.size();i++)
						{
							vector<string> vec1=split(vecstartPs[i],",");
							if(vec1.size()==2)
							{
								TPos pos={atof(vec1[0].c_str()),atof(vec1[1].c_str())};
								vecstartPs1.push_back(pos);
							}
						}
						if(ColNum!=vecstartPs1.size())
							continue;
					}
					vector<string> vecRowNum;
					const char*RowNum=Node->Attribute("RowNum");
					if(RowNum!=NULL)
					{
						vecRowNum=split(RowNum,",");
						if(ColNum!=vecRowNum.size())
							continue;
					}
					vector<TFishPos> vec;
					if(ColNum<2)
						continue;
					TPos centerP;
					const char*szcenterP=Node->Attribute("centerP");
					if(szcenterP!=NULL)
					{
						vector<string> vec1=split(szcenterP,",");
						if(vec1.size()==2)
						{
							centerP.x=atof(vec1[0].c_str());
							centerP.y=atof(vec1[1].c_str());
						}
						else
							continue;
					}
					//圆上的鱼
					for(int j=0;j<ColNum-1;j++)
					{
						TPos startPj=vecstartPs1[j];
						int numj=atoi(vecRowNum[j].c_str());
						float deltArg=M_PI*2.f/numj;
						for (int i=0;i<numj;i++)
						{
							TPos startPji=GetCirclePos(startPj,centerP,deltArg*i);
							TFishPos fpos;
							fpos.x=startPji.x;
							fpos.y=startPji.y;
							fpos.FishKind=atoi(vecFishKinds[j].c_str());
							vec.push_back(fpos);
						}
					}
					//中间的鱼
					TFishPos fpos;
					fpos.x=vecstartPs1[ColNum-1].x;
					fpos.y=vecstartPs1[ColNum-1].y;
					fpos.FishKind=atoi(vecFishKinds[ColNum-1].c_str());
					vec.push_back(fpos);
				m_vecAll1.push_back(vec);
			}
			if(m_vecAll1.size()>0)
			{
				g_vec=m_vecAll1[0];
				g_vecRToL=GetAxisymmetricFishPos(g_vec);
			}
		}//if(Node5)
			TiXmlElement* Node6=root->FirstChildElement("AllFishGroupType2");
			if(Node6)
			{
				//<FishGroupType2 FishKinds="1,2,3,4,5" startPs="-420,360;-340,360;-260,360;-180,360;-100,360" RowNum="9,9,9,9,9" deltY="60" /> 
				SetINTx(Node6,FishMoveSecs,2)
					TiXmlElement* Node=Node6->FirstChildElement("FishGroupType2");
				for(Node;Node;Node=Node->NextSiblingElement("FishGroupType2"))
				{
					vector<TFishPos> vec;
					bool ret=LoadFishGroupType234(Node,2,vec);
					if(!ret)
						continue;
					m_vecAll2.push_back(vec);
				}
				if(m_vecAll2.size()>0)
				{
					g_vecWH0=m_vecAll2[0];
					g_vecWH0RToL=GetAxisymmetricFishPos(g_vecWH0);
				}
			}//if(Node6)
			TiXmlElement* Node7=root->FirstChildElement("AllFishGroupType3");
			if(Node7)
			{
				//<FishGroupType3 FishKinds="1,2,3,4,5" startPs="-420,360;-340,360;-260,360;-180,360;-100,360" RowNum="9,9,9,9,9" deltY="60" /> 
				SetINTx(Node7,FishMoveSecs,3)
				TiXmlElement* Node=Node7->FirstChildElement("FishGroupType3");
				for(Node;Node;Node=Node->NextSiblingElement("FishGroupType3"))
				{
					vector<TFishPos> vec;
					bool ret=LoadFishGroupType234(Node,3,vec);
					if(!ret)
						continue;
					m_vecAll3.push_back(vec);
				}
				if(m_vecAll3.size()>0)
				{
					g_vecWH2=m_vecAll3[0];
					g_vecWH2RToL=GetAxisymmetricFishPos(g_vecWH2);
				}
			}//if(Node7)
			TiXmlElement* Node8=root->FirstChildElement("AllFishGroupType4");
			if(Node8)
			{
				//<FishGroupType4 FishKinds="1,2,3,4,5" startPs="-420,360;-340,360;-260,360;-180,360;-100,360" RowNum="9,9,9,9,9" deltY="60" /> 
				SetINTx(Node8,FishMoveSecs,4)
					TiXmlElement* Node=Node8->FirstChildElement("FishGroupType4");
				for(Node;Node;Node=Node->NextSiblingElement("FishGroupType4"))
				{
					vector<TFishPos> vec;
					bool ret=LoadFishGroupType234(Node,4,vec);
					if(!ret)
						continue;
					m_vecAll4.push_back(vec);
				}
				if(m_vecAll4.size()>0)
				{
					g_vecWH1=m_vecAll4[0];
					g_vecWH1RToL=GetAxisymmetricFishPos(g_vecWH1);
				}
			}//if(Node8)
			TiXmlElement* Node801=root->FirstChildElement("AllFishGroupType5");
			if(Node801)
			{
				//<FishGroupType5 FishMoveSecs="50" FishMoveDist="3000" startPs="1297,251,3;1297,354,3" /> 
				TiXmlElement* Node=Node801->FirstChildElement("FishGroupType5");
				for(Node;Node;Node=Node->NextSiblingElement("FishGroupType5"))
				{
					tagFishGroupType5 item;
					const char*FishMoveSecs=Node->Attribute("FishMoveSecs");
					if(FishMoveSecs!=NULL)
						item.FishMoveSecs=atoi(FishMoveSecs);
					const char*FishMoveDist=Node->Attribute("FishMoveDist");
					if(FishMoveDist!=NULL)
						item.arg1=TPoint(-atoi(FishMoveDist),0);
					const char*startPs=Node->Attribute("startPs");
					if(startPs!=NULL)
					{
						vector<string> vec=split(startPs,";");
						for(int i=0;i<vec.size();i++)
						{
							vector<string> vec1=split(vec[i],",");
							if(vec1.size()==3)
							{
								TFishPos pos={atof(vec1[0].c_str()),atof(vec1[1].c_str()),atof(vec1[2].c_str())};
								item.Arr_Pos.push_back(pos);
							}
						}
					}
					m_vecFishGroupType5.push_back(item);
					//add by Ivan_han 20130805
					item.arg1=TPoint(-item.arg1.x,-item.arg1.y);
					item.Arr_Pos=GetAxisymmetricFishPos(item.Arr_Pos);
					m_vecFishGroupType5LToR.push_back(item);
				}
			}//if(Node801)
			TiXmlElement* Node9=root->FirstChildElement("AllFishGroupType104");
			if(Node9)
			{
				TiXmlElement* Node=Node9->FirstChildElement("FishGroupType104");
				for(Node;Node;Node=Node->NextSiblingElement("FishGroupType104"))
				{
					//<FishGroupType104 FishKind="1" Arr_Pos_Count="7" Arr_Pos="0,0;-60,0;-50,30;0,50;30,40;30,-40;-50,-40" /> 
					tagFishGroupType104 item;
					const char*FishKind=Node->Attribute("FishKind");
					if(FishKind!=NULL)
						item.FishKind=atoi(FishKind);
					const char*Arr_Pos=Node->Attribute("Arr_Pos");
					if(Arr_Pos!=NULL)
					{
						vector<string> vec=split(Arr_Pos,";");
						for(int i=0;i<vec.size();i++)
						{
							vector<string> vec1=split(vec[i],",");
							if(vec1.size()==2)
							{
								TPos pos={atof(vec1[0].c_str()),atof(vec1[1].c_str())};
								item.Arr_Pos.push_back(pos);
							}
						}
					}
					m_vecFishGroupType104.push_back(item);
				}
			}//if(Node9)
			TiXmlElement* Node10=root->FirstChildElement("AllFishGroupType105");
			if(Node10)
			{
				TiXmlElement* Node=Node10->FirstChildElement("FishGroupType105");
				for(Node;Node;Node=Node->NextSiblingElement("FishGroupType105"))
				{
					//<FishGroupType105 FishKind="1" Arr_Pos_Count="7" Arr_Pos="-4000,-3500,-3000,-2500,-2000,-1000,0" /> 
					tagFishGroupType105 item;
					const char*FishKind=Node->Attribute("FishKind");
					if(FishKind!=NULL)
						item.FishKind=atoi(FishKind);
					const char*Arr_Pos=Node->Attribute("Arr_Pos");
					if(Arr_Pos!=NULL)
					{
						vector<string> vec=split(Arr_Pos,",");
						for(int i=0;i<vec.size();i++)
						{
								long long pos=atol(vec[i].c_str());
								item.Arr_Pos.push_back(pos);
						}
					}
					m_vecFishGroupType105.push_back(item);
				}
			}//if(Node10)
			for(int i=0;i<3;i++)
				m_vecAll104[i]=GetAll104(i+1);
			for(int i=0;i<10;i++)
				m_vecAll105[i]=GetAll105(i+1);

		}
#undef SetDOUBLE
#undef SetDOUBLEx
#undef SetINTx
#undef SetINT
	}
	delete m_xmlDoc;
	this->m_HasLoadOK=true;
	return 0;	
}

TFishMoveSecs PoolAndFish::GetFishMoveSecs(TFishGroupType FishGroupType)const
{
#define RtnSecs(t,SecsMin,SecsMax) {if(##t##==FishGroupType && m_FishMoveSecs_##t##>##SecsMin## && m_FishMoveSecs_##t##<##SecsMax##)return m_FishMoveSecs_##t##;}
	//if(FishGroupType==1 && m_FishMoveSecs_1>20 && m_FishMoveSecs_1<51)
	//	return m_FishMoveSecs_1;
	//if(FishGroupType==2 && m_FishMoveSecs_2>20 && m_FishMoveSecs_2<51)
	//	return m_FishMoveSecs_2;
	//if(FishGroupType==3 && m_FishMoveSecs_3>20 && m_FishMoveSecs_3<51)
	//	return m_FishMoveSecs_3;
	//if(FishGroupType==4 && m_FishMoveSecs_4>20 && m_FishMoveSecs_4<51)
	//	return m_FishMoveSecs_4;
	RtnSecs(1,20,51)
	RtnSecs(2,20,51)
	RtnSecs(3,20,51)
	RtnSecs(4,20,51)
	//add by Ivan_han 20130823
	if(FishGroupType>=11 && FishGroupType<=14)
	{
		return GetFishMoveSecs(FishGroupType%10);
	}
	if((FishGroupType>=5 && FishGroupType<=7)||(FishGroupType>=15 && FishGroupType<=17))
	{
			int nSize=m_vecFishGroupType5LToR.size();
			if(nSize>1)
			{
				int index=FishGroupType%10-5; 
				tagFishGroupType5 vFishs=m_vecFishGroupType5LToR[index];
				return vFishs.FishMoveSecs;
			}
			else
				return 20;
	}
#undef RtnSecs
	return 20;
}

int PoolAndFish::GetCaptureTime()const
{
	if(m_CaptureTime<TIME_CHANGE_SCENE)
		return TIME_CHANGE_SCENE;
	return m_CaptureTime;
}

int PoolAndFish::GetOffTime()const
{
	if(m_OffTime<TIME_CHANGE_SCENE)
		return TIME_CHANGE_SCENE;
	return m_OffTime;
}

int PoolAndFish::GetCaptureBuildTraceTime()const
{
	//return 300;
	if(m_CaptureBuildTraceTime<300)
		return TIME_BUILD_TRACE;
	return m_CaptureBuildTraceTime;
}

int PoolAndFish::GetOffBuildTraceTime()const
{
	if(m_OffBuildTraceTime<TIME_REGULAR_FISH)
		return TIME_REGULAR_FISH;
	return m_OffBuildTraceTime;
}

TProbValue PoolAndFish::GetIsFishProb()const
{
	if(m_IsFishProb<0.5||m_IsFishProb>1)
		return 0.5;
	return m_IsFishProb;
}

//获取某种鱼的所有列阵鱼群轨迹
vector<tagFishGroupType104> PoolAndFish::GetAll104(TFishKind FishKind) const
{
	vector<tagFishGroupType104> ret;
	vector<tagFishGroupType104>::const_iterator it;
	for( it = m_vecFishGroupType104.begin(); it != m_vecFishGroupType104.end(); ++it )
	{
		if( it->FishKind == FishKind )
			ret.push_back( *it );
	}
	return ret;
}

//获取某种鱼的所有列队鱼群轨迹
vector<tagFishGroupType105> PoolAndFish::GetAll105(TFishKind FishKind) const
{
	vector<tagFishGroupType105> ret;
	vector<tagFishGroupType105>::const_iterator it;
	for( it = m_vecFishGroupType105.begin(); it != m_vecFishGroupType105.end(); ++it )
	{
		if( it->FishKind == FishKind )
			ret.push_back( *it );
	}
	return ret;
}


GameFactorsMgr::GameFactorsMgr(CAwardPool *pAwardPool/*=NULL*/)
{
	m_pAwardPool=pAwardPool;
	m_PoolAlgorithmType=0;
	m_GameFactors.push_back(&m_GameDifficulty);
	m_GameFactors.push_back(&m_CannonGrade);
	m_GameFactors.push_back(&m_PoolWaterLevelRatio);
	m_GameFactors.push_back(&m_PlayerLuck);
	m_GameFactors.push_back(&m_PlayerProfit);
	m_GameFactors.push_back(&m_PlayerNewFlag);
	m_GameFactors.push_back(&m_PlayerGameTime);
	m_GameFactors.push_back(&m_FishGameFactor);
}

GameFactorsMgr::~GameFactorsMgr(void)
{

}

void GameFactorsMgr::setMU(TCollisionScoreValue mu)
{
	m_mu=mu;
}

void GameFactorsMgr::updateCollisionScore()
{
	//Pi=μ*（x1*y1+x2*y2+……+xn*yn）/（y1+y2+……+yn）
	TCollisionScoreValue a=0,b=0;
	for(int i=0;i<m_GameFactors.size();i++)
	{
		a+=(m_GameFactors[i]->m_Score)*(m_GameFactors[i]->m_Weight);
		b+=m_GameFactors[i]->m_Weight;
	}
	m_CollisionScore=m_mu*a/b;
}

TCollisionScoreValue GameFactorsMgr::getCollisionScore()const
{
	return m_CollisionScore;
}

void GameFactorsMgr::updateProbValue()
{
	static int Ns[5]={0,1,2,5,10};
	static int Ws[5]={220,100,0,0,0};
	TProbValue w=1+m_PlayerProfit.m_ProbValue+m_PlayerNewFlag.m_ProbValue+m_PlayerGameTime.m_ProbValue;
	Ws[2]=50*w;
	Ws[3]=20*w;
	Ws[4]=10*w;
	//N-玩家条件击毙倍率
	int index=GameFactorsMgr::SelectByProb(Ns,Ws,5);
	TProbValue N=Ns[index];
	//printf("N=%f\n",N);
#if 1
	//P=D*F*C*N
	m_ProbValue=m_GameDifficulty.m_ProbValue*m_FishGameFactor.m_ProbValue*m_PoolWaterLevelRatio.m_ProbValue*N;
#else
	/*
	//P=C
	m_ProbValue=m_PoolWaterLevelRatio.m_ProbValue;
	*/
	////P=F
	//m_ProbValue=m_FishGameFactor.m_ProbValue;
	//P=D
	m_ProbValue=m_GameDifficulty.m_ProbValue;
#endif
}

TProbValue GameFactorsMgr::getProbValue()const
{
	return m_ProbValue;
}

//取[nMin,nMax]之间的随机整数
int GameFactorsMgr::GetRand(const int nMin,const int nMax)
{
	if ( nMin > nMax)
		return nMin;
	return rand()%(nMax-nMin+1)+nMin;
}

//取[lo,hi]之间的随机双精度实数
TAwardPoolValue GameFactorsMgr::GetRandEx(const TAwardPoolValue lo,const TAwardPoolValue hi)
{
#if 0
	typedef struct
	{
		union 
		{
			struct
			{
				int lo32;
				int hi32;
			};
			long long m_ld;
		};
	}int64;
	int64 LO,HI,RET;
	LO.m_ld=lo*1000;
	HI.m_ld=hi*1000;
	RET.hi32=GetRand(LO.hi32,HI.hi32);
	RET.lo32=GetRand(LO.lo32,HI.lo32);
	RET.m_ld=RET.m_ld/1000;
	return RET.m_ld;
#else
	int min=lo;
	int max=hi;
	int ret=GetRand(min,max);
	return ret;
#endif
}

//根据概率选择，返回true的概率为p
bool GameFactorsMgr::SelectBoolByProb(TProbValue p)
{
	if(p>=1)
		return true;
	if(p<=0)
		return false;
	int P=(int)(p*1000+0.5); 
	int randNum = GetRand(0,1000);
	if(randNum<P)
		return true;
	return false;
}

//根据概率选择
int GameFactorsMgr::SelectByProb(int arr[],int arrProb[],int count,int total/*=0*/)
{
	if(total==0)
	{
		for(int i=0;i<count;i++)
		{
			total+=arrProb[i];
		}
	}
	int kind=0;
	int iRand =rand()%total;
	for(int i=0;i<count;i++)
	{
		if (iRand < arrProb[i])
		{
			kind=arr[i];
			break;
		}
		else
		{
			iRand -= arrProb[i];
		}
	}
	return kind;
}


//根据概率生成鱼或炸弹
TFishKind GameFactorsMgr::GetFishKindByProb(int RandType/*=0*/)
{
	static int ARR_FISH[] = {1,2,3,4,5,6,7,8,9,10,12,15,18,20,25,30,40};
	static int ARR_FISH_PROB[]={30,30,25,25,20,20,15,15,15,15,2,9,9,9,6,6,6};
	static int ARR_FISH_COUNT = sizeof(ARR_FISH)/sizeof(int);
	static int ARR_BOMB[] = {101,102,103,104,105,106,107,108,109,110,111,112,113,134,135,137,140,146,148};
	static int ARR_BOMB_PROB[] = {4,4,4,3,3,3,2,2,2,2,1,1,10,0,0,0,0,0,0};
	static int ARR_BOMB_COUNT = sizeof(ARR_BOMB)/sizeof(int); 
	TProbValue IsFishProb=PoolAndFish::Instance().GetIsFishProb();

	//add by Ivan_han 20130717
	static bool IsOk=false;
	static int total_fish=257;
	static int total_bomb=31;
	if(!IsOk)
	{	
		//鱼
		int Total_fish=0;
		for (int i=0; i<ARR_FISH_COUNT; i++)
		{	
			const CTabFishItem *pFishLocalInfo=CTabFishCache::Instance().Find(ARR_FISH[i]);
			if(pFishLocalInfo)
			{
				ARR_FISH_PROB[i]=pFishLocalInfo->m_nGenProb;
				Total_fish += ARR_FISH_PROB[i];
			}
		}
		if(Total_fish>0)
			total_fish=Total_fish;
		//炸弹
		int Total_bomb=0;
		for (int i=0; i<ARR_BOMB_COUNT; i++)
		{	
			const CTabFishItem *pFishLocalInfo=CTabFishCache::Instance().Find(ARR_BOMB[i]);
			if(pFishLocalInfo)
			{
				ARR_BOMB_PROB[i]=pFishLocalInfo->m_nGenProb;
				Total_bomb += ARR_BOMB_PROB[i];
			}
		}
		if(Total_bomb>0)
			total_bomb=Total_bomb;
		IsOk=true;
	}	

	int kind=0;
	if(RandType==1)
	{
		//鱼
		kind=SelectByProb(ARR_FISH,ARR_FISH_PROB,ARR_FISH_COUNT,total_fish);
		return kind;
	}
	if(RandType==2)
	{
		//炸弹
		kind=SelectByProb(ARR_BOMB,ARR_BOMB_PROB,ARR_BOMB_COUNT,total_bomb);
		return kind;
	}
	if(SelectBoolByProb(IsFishProb))
	{
		//鱼
		kind=SelectByProb(ARR_FISH,ARR_FISH_PROB,ARR_FISH_COUNT,total_fish);
		return kind;
	}
	else
	{
		//炸弹
		kind=SelectByProb(ARR_BOMB,ARR_BOMB_PROB,ARR_BOMB_COUNT,total_bomb);
		return kind;
	}
	return 0;
}

//根据概率生成小鱼、大鱼、炸弹
TFishKind GameFactorsMgr::GetFishKindByProbEx(int type)
{
	if(type==1)
	{
		for(int i=0;i<100;i++)
		{
			int FishKind=GetFishKindByProb(1);
			if(FishKind<12)
				return FishKind;
		}
		return 1;
	}
	if(type==2)
	{
		for(int i=0;i<100;i++)
		{
			int FishKind=GetFishKindByProb(1);
			if(FishKind>10)
				return FishKind;
		}
		return 12;
	}
	if(type==3)
	{
		for(int i=0;i<100;i++)
		{
			int FishKind=GetFishKindByProb(2);
			if(FishKind>100)
				return FishKind;
		}
		return 101;
	}
	return 1;
}

//取出一个击中的鱼,计算击毙概率P，返回true表示该鱼被击毙,false表示该鱼不被击毙
bool GameFactorsMgr::OnCalcProbValue(int iSeatNo,TFishID FishID,TFishKind nFishKind,TFishNumOfAck FishNumOfAck,unsigned int nHitFishCount,TFallIntegral *pG,vector<TFishID> &vOtherDeadFishID, int &iFeats)
{
	iFeats = 0;	// 功勋
	if(iSeatNo<0||iSeatNo>=GAME_PLAYER_COUNT)
		return false;
#if 0
	//m_PoolAlgorithmType=0
	bool ret=SelectBoolByProb(0.8);
#else
	//m_PoolAlgorithmType=2
	//计算击毙概率P
	m_FishGameFactor.updateFishGameFactor(FishID,nFishKind,FishNumOfAck,nHitFishCount);
	m_FishGameFactor.updateProbValue();
	m_PoolWaterLevelRatio.updatePoolWaterLevelRatio(m_pAwardPool->m_V,m_pAwardPool->m_Vh,m_pAwardPool->m_Vl);
	m_PoolWaterLevelRatio.updateProbValue();
	TWinIntegral nPlayerProfit=m_PlayerFactorInfo[iSeatNo].m_PlayerProfitInfo.m_PlayerProfit;
	m_PlayerProfit.updatePlayerProfit(nPlayerProfit);
	m_PlayerProfit.updateProbValue();
	bool bPlayerNewFlag=m_PlayerFactorInfo[iSeatNo].m_PlayerNewFlagInfo.m_PlayerNewFlag;
	m_PlayerNewFlag.updatePlayerNewFlag(bPlayerNewFlag);
	m_PlayerNewFlag.updateProbValue();
	unsigned long long llPlayerGameTime=m_PlayerFactorInfo[iSeatNo].m_PlayerGameTimeInfo.m_PlayerGameTime;
	m_PlayerGameTime.updatePlayerGameTime(llPlayerGameTime);
	m_PlayerGameTime.updateProbValue();
	updateProbValue();
	bool ret=SelectBoolByProb(m_ProbValue);
	//printf("击毙概率P=%f,D=%f,F(%d,F2=%d,F3=%d)=%f,C=%f,V=%f,Vh=%f,Vl=%f,N1=%f,N2=%f,N3=%f\n",m_ProbValue,m_GameDifficulty.m_ProbValue,nFishKind,FishNumOfAck,nHitFishCount,m_FishGameFactor.m_ProbValue,m_PoolWaterLevelRatio.m_ProbValue,m_PoolWaterLevelRatio.m_V,m_PoolWaterLevelRatio.m_Vh,m_PoolWaterLevelRatio.m_Vl,m_PlayerProfit.m_ProbValue,m_PlayerNewFlag.m_ProbValue,m_PlayerGameTime.m_ProbValue);
#endif
	if(ret)
	{
       	const CTabFishItem *pFishLocalInfo=CTabFishCache::Instance().Find(nFishKind);
		if(pFishLocalInfo)
		{
			iFeats = pFishLocalInfo->m_nMerit;		// 功勋数量
			//*pG=m_pFishLocalInfo->m_nFishMulti;
			//被击毙的是普通鱼或龙虾炸弹
			if(nFishKind/100==0||nFishKind%100>=12)
			{
				*pG=pFishLocalInfo->m_nFishMulti;
			}
			//被击毙的是炸弹
			else
			{
				//获取桌子指针
				CFishTable* pTable=m_pAwardPool->get_fish_table();
				if(!pTable)
					return ret;

				//被击毙的是全屏炸弹
				if(nFishKind%100==11)
				{
					//屏幕内所有的鱼
					*pG=pTable->getFishTraceMgr().CheckFishTrace(0,vOtherDeadFishID);

				}
				//被击毙的是同类炸弹鱼
				else
				{
					//屏幕内所有的同类鱼
					*pG=pTable->getFishTraceMgr().CheckFishTrace(nFishKind%100,vOtherDeadFishID);
					//add by Ivan_han 20130731
					*pG+=pFishLocalInfo->m_nFishMulti;
				}
			}
		}
	}
	return ret;
}

//攻击结算
TFallIntegral GameFactorsMgr::OnAttackSettlement(int iSeatNo,const vector<TFishID> &vFishID,const vector<TFishKind> &vFishKind,const vector<TFishNumOfAck> &vFishNumOfAck,vector<TFishID> &vDeadFishID,TGunGrade GunGrade, int &iFeats)
{
	if(m_pAwardPool==NULL)
		return 0;
	TFallIntegral G=0;
	iFeats = 0; // 功勋
	vDeadFishID.clear();
	for(int i=0;i<vFishID.size();i++)
	{
		if(vFishKind[i]==0)
			continue;
		int iFeatsNeer = 0;
		TFallIntegral dG=0;
		vector<TFishID> vOtherDeadFishID;
		bool isDead=OnCalcProbValue(iSeatNo,vFishID[i],vFishKind[i],vFishNumOfAck[i],vFishID.size(),&dG,vOtherDeadFishID, iFeatsNeer);
		dG=dG*GunGrade;
		if(isDead)
		{
			bool ret=m_pAwardPool->Pop(dG);
			if(!ret)
			{
				return G;
			}
			else
			{
				vDeadFishID.push_back(vFishID[i]);
				if(vOtherDeadFishID.size()>0)
					vDeadFishID.insert(vDeadFishID.end(),vOtherDeadFishID.begin(),vOtherDeadFishID.end());
				G+=dG;
				iFeats+=iFeatsNeer;
			}
		}
	}
	return G;
}