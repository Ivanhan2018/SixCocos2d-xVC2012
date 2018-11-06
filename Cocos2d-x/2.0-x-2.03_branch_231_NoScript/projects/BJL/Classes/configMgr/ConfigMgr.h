//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName     :   ConfigMgr
//  Version      :   1.0
//  Creater      :   zhouwei
//  Date         :   2013.09.11
//  Comment    	 :   资源管理中心
//
//////////////////////////////////////////////////////////////////////////////////////


#ifndef __CONFIGMGR_READER_H__
#define __CONFIGMGR_READER_H__
 
#include "ans/AnsSingleton.h"
#include "serializers/TinyXmlReader.h"

struct SeverConfigInfo
{
	int			m_nGolbalBankruptcy;			//--破产值
	bool		m_isGameBankrupcy;				//--小游戏破产
	string		m_channelStr;					//渠道名称

	int			nServerEnter[6];
	char		szTitle[64];					// 公告标题
	char		szContent[512];					// 公告内容

	bool		m_bToAndroid;					//是否进入android界面
	bool     m_isGameRun;					//是否进入小游戏
};

struct VersionInfo
{
	int m_nHighVersion;
	int m_nMiddleVersion;
	int m_nLowVersion;
};

class ConfigMgr  : public ans::Singleton<ConfigMgr> 
{
private:
	SINGLETON_FRIEND_SUB(ConfigMgr);
public:
	ConfigMgr();

public:
	//中文文本资源
	const char* text(const char* key);
	SeverConfigInfo m_Config;
	VersionInfo m_VersionInfo;

private:
	TinyXmlReader m_TinyXmlReader;
};

#endif //#define __CONFIGMGR_READER_H__
