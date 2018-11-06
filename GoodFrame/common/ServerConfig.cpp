#include "StdAfx.h"
#include ".\BaseConfig.h"

#include <string>

CBaseConfig::CBaseConfig(void)
{
}

CBaseConfig::~CBaseConfig(void)
{
}

// 从客户端的配制文件中读取参数
void CBaseConfig::read_client_config(char* szConfigName)
{
	// 获得本进程的完整路径和文件名，尤其在DLL中用得多；

	using std::string;

	char buf[256] = {0}; 

	GetModuleFileName(NULL,buf,sizeof(buf));

	string strTemp = buf;
	string::size_type  pos = 0;

	pos = strTemp.rfind('\\', strTemp.length());	// 从 strTemp 的尾部开始向头部查找指定的字符

	string strPathFile = strTemp.substr(0, pos+1);	

	strPathFile = strPathFile + szConfigName;

	// --- 最基本的参数 --------------------------------------------
	GetPrivateProfileString("BASE", "ip", "127.0.0.1", m_BaseConfig.szIP, sizeof(m_BaseConfig.szIP), strPathFile.c_str());
	m_BaseConfig.port = GetPrivateProfileInt("BASE", "port", 5150, strPathFile.c_str());

	// 读 IO 端口的消息的长度，默认为 10k
	m_BaseConfig.ioReadMessageLen = GetPrivateProfileInt("BASE", "IOReadMessageLen", 5120, strPathFile.c_str());	

	//// 在消息池中每条消息的长度，暂时不要此句
	//m_BaseConfig.iEveryMsgBlockLen = GetPrivateProfileInt("BASE", "EveryMsgBlockLen", 512, strPathFile.c_str());	

	// 无心跳至死的时间，以秒为单位
	m_BaseConfig.iNoHeartToDieTime = GetPrivateProfileInt("BASE", "NoHeartToDieTime", 300, strPathFile.c_str());				

	// --- 测试部分 --------------------------------------------

	// 简单的显示读到的消息
	m_BaseConfig.bShow = GetPrivateProfileInt("TEST", "show", 1, strPathFile.c_str());

	// 收到消息后回发
	m_BaseConfig.bRestore = GetPrivateProfileInt("TEST", "restore", 0, strPathFile.c_str());

	// 连续发包的总数
	m_BaseConfig.lContinueSendNum = GetPrivateProfileInt("TEST", "ContinueSendNum", 1, strPathFile.c_str()); 

	// 连发n个包后要休息一会
	m_BaseConfig.lContinueSendSpace = GetPrivateProfileInt("TEST", "ContinueSendSpace", 10000, strPathFile.c_str());

	// 休息时间，以 ms 为单位
	m_BaseConfig.lRest = GetPrivateProfileInt("TEST", "Rest", 20, strPathFile.c_str());	

	// 固意发送错误包的方式
	m_BaseConfig.iErrorPackegType =  GetPrivateProfileInt("TEST", "ErrorPackegType", 0, strPathFile.c_str());

	// 小间隔时间，即前后两个包在此时间内收到才算连续，以 ms 为单位
	m_BaseConfig.iFluxSmallIntervalTime = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxSmallIntervalTime", 50, strPathFile.c_str());	
}

// 从服务端的配制文件中读取参数
void CBaseConfig::read_service_config(char* szConfigName)
{
	// 获得本进程的完整路径和文件名，尤其在DLL中用得多；

	using std::string;

	char buf[256] = {0}; 

	GetModuleFileName(NULL,buf,sizeof(buf));

	string strTemp = buf;
	string::size_type  pos = 0;

	pos = strTemp.rfind('\\', strTemp.length());	// 从 strTemp 的尾部开始向头部查找指定的字符

	string strPathFile = strTemp.substr(0, pos+1);	

	strPathFile = strPathFile + szConfigName;

	// --- 最基本的参数 --------------------------------------------
	GetPrivateProfileString("BASE", "ip", "127.0.0.1", m_BaseConfig.szIP, sizeof(m_BaseConfig.szIP), strPathFile.c_str());
	m_BaseConfig.port = GetPrivateProfileInt("BASE", "port", 5150, strPathFile.c_str());

	// 读 IO 端口的消息的长度，默认为 10k
	m_BaseConfig.ioReadMessageLen = GetPrivateProfileInt("BASE", "IOReadMessageLen", 5120, strPathFile.c_str());	

	//// 在消息池中每条消息的长度，暂时不要此句
	//m_BaseConfig.iEveryMsgBlockLen = GetPrivateProfileInt("BASE", "EveryMsgBlockLen", 512, strPathFile.c_str());	

	// 无心跳至死的时间，以秒为单位
	m_BaseConfig.iNoHeartToDieTime = GetPrivateProfileInt("BASE", "NoHeartToDieTime", 300, strPathFile.c_str());	

	// --- 数据库部分 --------------------------------------------

	// 使用数据库
	m_BaseConfig.useDB = GetPrivateProfileInt("DB", "UseDB", 0, strPathFile.c_str());				

	// --- 测试部分 --------------------------------------------

	// 简单的显示读到的消息
	m_BaseConfig.bShow = GetPrivateProfileInt("TEST", "show", 1, strPathFile.c_str());

	// 收到消息后回发
	m_BaseConfig.bRestore = GetPrivateProfileInt("TEST", "restore", 0, strPathFile.c_str());

	// 连续发包的总数
	m_BaseConfig.lContinueSendNum = GetPrivateProfileInt("TEST", "ContinueSendNum", 1, strPathFile.c_str()); 

	// 连发n个包后要休息一会
	m_BaseConfig.lContinueSendSpace = GetPrivateProfileInt("TEST", "ContinueSendSpace", 10000, strPathFile.c_str());

	// 休息时间，以 ms 为单位
	m_BaseConfig.lRest = GetPrivateProfileInt("TEST", "Rest", 20, strPathFile.c_str());	

	// 小间隔时间，即前后两个包在此时间内收到才算连续，以 ms 为单位
	m_BaseConfig.iFluxSmallIntervalTime = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxSmallIntervalTime", 50, strPathFile.c_str());	

	// 固意发送错误包的方式
	m_BaseConfig.iErrorPackegType =  GetPrivateProfileInt("TEST", "ErrorPackegType", 0, strPathFile.c_str());

	// --- 流量过载保护 --------------------------------------------

	// 连续时间，以 ms 为单位，即多少 ms 检查一次流量是否过载
	m_BaseConfig.iFluxOverLoadingContinueTime = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxOverLoadingContinueTime", 2000, strPathFile.c_str());	

	// 过载流量的上限，，以 byte/ms 为单位，即每毫秒允许的流量
	m_BaseConfig.iFluxOverLoading = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxOverLoading", 4096, strPathFile.c_str());	

	// 显示每次的检测
	m_BaseConfig.bFluxOverLoadingShow = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxOverLoadingShow", 0, strPathFile.c_str());	

	// --- 连接过载保护 --------------------------------------------

	// 小间隔时间，即前后两个客户端请求的连接在此时间内收到才算连续，以 ms 为单位
	m_BaseConfig.iContinueSmallIntervalTime = GetPrivateProfileInt("CONTINUE_OVER_LOADING_PROTECT", "ContinueSmallIntervalTime", 50, strPathFile.c_str());	

	// 连续时间，以 ms 为单位，即多少 ms 检查一次连接是否过载
	m_BaseConfig.iContinueOverLoadingContinueTime = GetPrivateProfileInt("CONTINUE_OVER_LOADING_PROTECT", "ContinueOverLoadingContinueTime", 1000, strPathFile.c_str());	

	// 连接过载的上限，以 个/s 为单位，即每秒允许的连接
	m_BaseConfig.iContinueOverLoading = GetPrivateProfileInt("CONTINUE_OVER_LOADING_PROTECT", "ContinueOverLoading", 500, strPathFile.c_str());	

	// 显示每次的检测
	m_BaseConfig.bContinueOverLoadingShow = GetPrivateProfileInt("CONTINUE_OVER_LOADING_PROTECT", "ContinueOverLoadingShow", 0, strPathFile.c_str());				// 显示每次的检测
}

BASE_CONFIG* CBaseConfig::GetBaseConfig()
{
	return &m_BaseConfig;
}