#include "./PublicHead.h"
#include "./CompleteResult.h"

CCompleteResult::CCompleteResult(void)
{
	m_pServerHandle = 0;
	m_pTcpMsgTranSvr = 0;
	memset(m_szClassNameFlag, 0, sizeof(m_szClassNameFlag));

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

CCompleteResult::~CCompleteResult(void)
{
}

// 获得类名的标识
char* CCompleteResult::get_class_name_flag()
{
	return m_szClassNameFlag;
}

// 设置类名的标识
void CCompleteResult::set_class_name_flag(char* pClassNameFlag)
{
	if(pClassNameFlag)
		_snprintf(m_szClassNameFlag, sizeof(m_szClassNameFlag), "%s", pClassNameFlag);
}

void CCompleteResult::init()
{
	Internal = 0;  
	InternalHigh = 0; 
	Offset = 0;  
	OffsetHigh = 0;  

	//hEvent = NULL;
}

void CCompleteResult::set_service_handle(CServerHandle* pServerHandle)
{
	m_pServerHandle = pServerHandle;
}