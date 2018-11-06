#include "StdAfx.h"
#include ".\BaseConfig.h"

#include <string>

CBaseConfig::CBaseConfig(void)
{
}

CBaseConfig::~CBaseConfig(void)
{
}

// �ӿͻ��˵������ļ��ж�ȡ����
void CBaseConfig::read_client_config(char* szConfigName)
{
	// ��ñ����̵�����·�����ļ�����������DLL���õöࣻ

	using std::string;

	char buf[256] = {0}; 

	GetModuleFileName(NULL,buf,sizeof(buf));

	string strTemp = buf;
	string::size_type  pos = 0;

	pos = strTemp.rfind('\\', strTemp.length());	// �� strTemp ��β����ʼ��ͷ������ָ�����ַ�

	string strPathFile = strTemp.substr(0, pos+1);	

	strPathFile = strPathFile + szConfigName;

	// --- ������Ĳ��� --------------------------------------------
	GetPrivateProfileString("BASE", "ip", "127.0.0.1", m_BaseConfig.szIP, sizeof(m_BaseConfig.szIP), strPathFile.c_str());
	m_BaseConfig.port = GetPrivateProfileInt("BASE", "port", 5150, strPathFile.c_str());

	// �� IO �˿ڵ���Ϣ�ĳ��ȣ�Ĭ��Ϊ 10k
	m_BaseConfig.ioReadMessageLen = GetPrivateProfileInt("BASE", "IOReadMessageLen", 5120, strPathFile.c_str());	

	//// ����Ϣ����ÿ����Ϣ�ĳ��ȣ���ʱ��Ҫ�˾�
	//m_BaseConfig.iEveryMsgBlockLen = GetPrivateProfileInt("BASE", "EveryMsgBlockLen", 512, strPathFile.c_str());	

	// ������������ʱ�䣬����Ϊ��λ
	m_BaseConfig.iNoHeartToDieTime = GetPrivateProfileInt("BASE", "NoHeartToDieTime", 300, strPathFile.c_str());				

	// --- ���Բ��� --------------------------------------------

	// �򵥵���ʾ��������Ϣ
	m_BaseConfig.bShow = GetPrivateProfileInt("TEST", "show", 1, strPathFile.c_str());

	// �յ���Ϣ��ط�
	m_BaseConfig.bRestore = GetPrivateProfileInt("TEST", "restore", 0, strPathFile.c_str());

	// ��������������
	m_BaseConfig.lContinueSendNum = GetPrivateProfileInt("TEST", "ContinueSendNum", 1, strPathFile.c_str()); 

	// ����n������Ҫ��Ϣһ��
	m_BaseConfig.lContinueSendSpace = GetPrivateProfileInt("TEST", "ContinueSendSpace", 10000, strPathFile.c_str());

	// ��Ϣʱ�䣬�� ms Ϊ��λ
	m_BaseConfig.lRest = GetPrivateProfileInt("TEST", "Rest", 20, strPathFile.c_str());	

	// ���ⷢ�ʹ�����ķ�ʽ
	m_BaseConfig.iErrorPackegType =  GetPrivateProfileInt("TEST", "ErrorPackegType", 0, strPathFile.c_str());

	// С���ʱ�䣬��ǰ���������ڴ�ʱ�����յ������������� ms Ϊ��λ
	m_BaseConfig.iFluxSmallIntervalTime = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxSmallIntervalTime", 50, strPathFile.c_str());	
}

// �ӷ���˵������ļ��ж�ȡ����
void CBaseConfig::read_service_config(char* szConfigName)
{
	// ��ñ����̵�����·�����ļ�����������DLL���õöࣻ

	using std::string;

	char buf[256] = {0}; 

	GetModuleFileName(NULL,buf,sizeof(buf));

	string strTemp = buf;
	string::size_type  pos = 0;

	pos = strTemp.rfind('\\', strTemp.length());	// �� strTemp ��β����ʼ��ͷ������ָ�����ַ�

	string strPathFile = strTemp.substr(0, pos+1);	

	strPathFile = strPathFile + szConfigName;

	// --- ������Ĳ��� --------------------------------------------
	GetPrivateProfileString("BASE", "ip", "127.0.0.1", m_BaseConfig.szIP, sizeof(m_BaseConfig.szIP), strPathFile.c_str());
	m_BaseConfig.port = GetPrivateProfileInt("BASE", "port", 5150, strPathFile.c_str());

	// �� IO �˿ڵ���Ϣ�ĳ��ȣ�Ĭ��Ϊ 10k
	m_BaseConfig.ioReadMessageLen = GetPrivateProfileInt("BASE", "IOReadMessageLen", 5120, strPathFile.c_str());	

	//// ����Ϣ����ÿ����Ϣ�ĳ��ȣ���ʱ��Ҫ�˾�
	//m_BaseConfig.iEveryMsgBlockLen = GetPrivateProfileInt("BASE", "EveryMsgBlockLen", 512, strPathFile.c_str());	

	// ������������ʱ�䣬����Ϊ��λ
	m_BaseConfig.iNoHeartToDieTime = GetPrivateProfileInt("BASE", "NoHeartToDieTime", 300, strPathFile.c_str());	

	// --- ���ݿⲿ�� --------------------------------------------

	// ʹ�����ݿ�
	m_BaseConfig.useDB = GetPrivateProfileInt("DB", "UseDB", 0, strPathFile.c_str());				

	// --- ���Բ��� --------------------------------------------

	// �򵥵���ʾ��������Ϣ
	m_BaseConfig.bShow = GetPrivateProfileInt("TEST", "show", 1, strPathFile.c_str());

	// �յ���Ϣ��ط�
	m_BaseConfig.bRestore = GetPrivateProfileInt("TEST", "restore", 0, strPathFile.c_str());

	// ��������������
	m_BaseConfig.lContinueSendNum = GetPrivateProfileInt("TEST", "ContinueSendNum", 1, strPathFile.c_str()); 

	// ����n������Ҫ��Ϣһ��
	m_BaseConfig.lContinueSendSpace = GetPrivateProfileInt("TEST", "ContinueSendSpace", 10000, strPathFile.c_str());

	// ��Ϣʱ�䣬�� ms Ϊ��λ
	m_BaseConfig.lRest = GetPrivateProfileInt("TEST", "Rest", 20, strPathFile.c_str());	

	// С���ʱ�䣬��ǰ���������ڴ�ʱ�����յ������������� ms Ϊ��λ
	m_BaseConfig.iFluxSmallIntervalTime = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxSmallIntervalTime", 50, strPathFile.c_str());	

	// ���ⷢ�ʹ�����ķ�ʽ
	m_BaseConfig.iErrorPackegType =  GetPrivateProfileInt("TEST", "ErrorPackegType", 0, strPathFile.c_str());

	// --- �������ر��� --------------------------------------------

	// ����ʱ�䣬�� ms Ϊ��λ�������� ms ���һ�������Ƿ����
	m_BaseConfig.iFluxOverLoadingContinueTime = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxOverLoadingContinueTime", 2000, strPathFile.c_str());	

	// �������������ޣ����� byte/ms Ϊ��λ����ÿ�������������
	m_BaseConfig.iFluxOverLoading = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxOverLoading", 4096, strPathFile.c_str());	

	// ��ʾÿ�εļ��
	m_BaseConfig.bFluxOverLoadingShow = GetPrivateProfileInt("FLUX_OVER_LOADING_PROTECT", "FluxOverLoadingShow", 0, strPathFile.c_str());	

	// --- ���ӹ��ر��� --------------------------------------------

	// С���ʱ�䣬��ǰ�������ͻ�������������ڴ�ʱ�����յ������������� ms Ϊ��λ
	m_BaseConfig.iContinueSmallIntervalTime = GetPrivateProfileInt("CONTINUE_OVER_LOADING_PROTECT", "ContinueSmallIntervalTime", 50, strPathFile.c_str());	

	// ����ʱ�䣬�� ms Ϊ��λ�������� ms ���һ�������Ƿ����
	m_BaseConfig.iContinueOverLoadingContinueTime = GetPrivateProfileInt("CONTINUE_OVER_LOADING_PROTECT", "ContinueOverLoadingContinueTime", 1000, strPathFile.c_str());	

	// ���ӹ��ص����ޣ��� ��/s Ϊ��λ����ÿ�����������
	m_BaseConfig.iContinueOverLoading = GetPrivateProfileInt("CONTINUE_OVER_LOADING_PROTECT", "ContinueOverLoading", 500, strPathFile.c_str());	

	// ��ʾÿ�εļ��
	m_BaseConfig.bContinueOverLoadingShow = GetPrivateProfileInt("CONTINUE_OVER_LOADING_PROTECT", "ContinueOverLoadingShow", 0, strPathFile.c_str());				// ��ʾÿ�εļ��
}

BASE_CONFIG* CBaseConfig::GetBaseConfig()
{
	return &m_BaseConfig;
}