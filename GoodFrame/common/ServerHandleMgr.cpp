#include "./PublicHead.h"
#include "./ServerHandleMgr.h"

CServerHandleMgr::CServerHandleMgr(void)
{
	m_lChannelNo = 0;
}

CServerHandleMgr::~CServerHandleMgr(void)
{
	CThreadGuardWrite guard(&m_lock);

	// 移除所有的元素
	size_t sizeTmp = m_mapServiceHandle.size();

	m_mapServiceHandle.clear();
}

// 注意：函数之间不能嵌套，因为 CThreadGuardWrite 不能嵌套

// 能否把 CServerHandle* 的出池与归池也放到 CServerHandleMgr 里面来呢 ???

/* --------------------------------------------------------------------------
函数说明：增加一个对端服务
传入参数：
	pServiceHandle	对端服务指针
传出参数：
返回值：
    成功则返回通道号，否则返回 INVALID_CHANNEL_NO 。
--------------------------------------------------------------------------*/
LONGLONG CServerHandleMgr::add(CServerHandle* pServiceHandle)
{
	CThreadGuardWrite guard(&m_lock);

	if(!pServiceHandle)
		return 10;

	::InterlockedIncrement64(&m_lChannelNo);	// 通道自动增 1 

	m_mapServiceHandle.insert(PAIR_TYPE(m_lChannelNo, pServiceHandle));

	return m_lChannelNo;
}

// 移除一个对端服务
CServerHandle* CServerHandleMgr::remove_one(LONGLONG lChannelNo)
{
	CThreadGuardWrite guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServiceHandle = NULL;

	iter = m_mapServiceHandle.find(lChannelNo);

	if( iter != m_mapServiceHandle.end())	// 找到了
	{
		pServiceHandle = (CServerHandle*)(*iter).second;

		m_mapServiceHandle.erase(iter);	// 移除
	}

	return pServiceHandle;
}

/* --------------------------------------------------------------------------
函数说明：移除所有的对端服务
传出参数：
	vecServiceHandle	被移除的对端服务列表
返回值：
    被移除的对端服务的数量
--------------------------------------------------------------------------*/
int CServerHandleMgr::remove_all(vector<CServerHandle*>& vecServiceHandle)
{
	CThreadGuardWrite guard(&m_lock);

	CServerHandle* pServiceHandle = NULL;
	MAP_TYPE::iterator iter = m_mapServiceHandle.begin();
	int iCount = 0;

	// 对端服务列表赋值
	for(; iter != m_mapServiceHandle.end(); iter++)
	{
		pServiceHandle = (CServerHandle*)(*iter).second;

		vecServiceHandle.push_back(pServiceHandle);

		iCount++;
	}

	return iCount;
}

// 由通道号获得对端服务指针
CServerHandle* CServerHandleMgr::find(LONGLONG lChannelNo)
{
	CThreadGuardRead guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServiceHandle = NULL;

	iter = m_mapServiceHandle.find(lChannelNo);

	if( iter != m_mapServiceHandle.end())	// 找到了
	{
		pServiceHandle = (CServerHandle*)(*iter).second;
	}

	return pServiceHandle;
}

// 指定的对端服务是否有效
BOOL CServerHandleMgr::is_valid(LONGLONG lChannelNo)
{
	CThreadGuardRead guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServiceHandle = NULL;
	BOOL bValid = FALSE;

	iter = m_mapServiceHandle.find(lChannelNo);

	if( iter != m_mapServiceHandle.end())	// 找到了
	{
		pServiceHandle = (CServerHandle*)(*iter).second;
		bValid =  pServiceHandle->is_valid();
	}

	return bValid;
}