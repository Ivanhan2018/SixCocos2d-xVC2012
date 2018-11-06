#include "./PublicHead.h"
#include "./ChennelNoMgr.h"
#include "./CommTcpServer.h"

CChennelNoMgr::CChennelNoMgr(void)
{
	m_lChannelNo = 0;
}

CChennelNoMgr::~CChennelNoMgr(void)
{
	CThreadGuardWrite guard(&m_lock);

	// 移除所有的元素
	size_t sizeTmp = m_mapServerHandle.size();

	m_mapServerHandle.clear();
}

// 注意：函数之间不能嵌套，因为 CThreadGuardWrite 不能嵌套

// 能否把 CServerHandle* 的出池与归池也放到 CChennelNoMgr 里面来呢 ???

/* --------------------------------------------------------------------------
函数说明：增加一个对端服务
传入参数：
	pServerHandle	对端服务指针
传出参数：
返回值：
    成功则返回通道号，否则返回 INVALID_CHANNEL_NO 。
--------------------------------------------------------------------------*/
LONGLONG CChennelNoMgr::add(CServerHandle* pServerHandle)
{
	CThreadGuardWrite guard(&m_lock);

	if(!pServerHandle)
		return 10;

	::InterlockedIncrement64(&m_lChannelNo);	// 通道自动增 1 

	m_mapServerHandle.insert(PAIR_TYPE(m_lChannelNo, pServerHandle));

	return m_lChannelNo;
}

/* --------------------------------------------------------------------------
函数说明：设置主动关闭的对端
传入参数：
	pServerHandle	对端服务指针
传出参数：
返回值：
    成功则返回0，否则返回错误码 。
--------------------------------------------------------------------------*/
int CChennelNoMgr::set_power_close_peer(LONGLONG lChannelNo)
{
	CThreadGuardWrite guard(&m_lock);

	if(INVALID_CHANNEL_NO==lChannelNo)
		return 10;

	MAP_TYPE::iterator iter = m_mapServerHandle.find(lChannelNo);

	if( iter != m_mapServerHandle.end())	// 找到了
	{
		CServerHandle* pServerHandle = (CServerHandle*)(*iter).second;
		if(pServerHandle && pServerHandle->is_valid())
		{
			//printf("需要删除打印:set_power_close_peer端口号 %d \n",lChannelNo);
			pServerHandle->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);	// 服务端主动关闭客户端
			pServerHandle->m_iPowerClosePeerTime = ::GetTickCount64();
		}
	}

	return 0;
}

// 检查主动关闭对端超时
int CChennelNoMgr::check_power_close_peer()
{
	vector<LONGLONG> vecOverTimePeer;	// 超时的对端数组

	{
		CThreadGuardRead guard(&m_lock);	// 先用“读”的方式找出主动关闭超时的对端，这样的好处是速度快，不会阻塞别的“读”

		LONGLONG lCurrent = GetTickCount64();	// 当前的时间
		CServerHandle* pServerHandle = NULL;

		MAP_TYPE::iterator iter = m_mapServerHandle.begin();

		for( ;  iter != m_mapServerHandle.end(); iter++ )
		{
			pServerHandle = (CServerHandle*)(*iter).second;

			if(pServerHandle->is_valid() &&					// 对端有效
				pServerHandle->m_iPowerClosePeerTime>0 &&	// 主动关闭对端的时间合法
				lCurrent - pServerHandle->m_iPowerClosePeerTime > CCommTcpServer::INITIATIVE_CLOSE_PEER_OVER_TIME	// 超时
				)	
			{
				LONGLONG lFirst = (*iter).first;

				vecOverTimePeer.push_back(lFirst);	// 加入超时的对端数组
			}
		}
	}	// 析构会自动解锁 m_lock

	{	// vecOverTimePeer.size() 大于零的概率其实是不大的 
		CThreadGuardWrite guard(&m_lock);
		int iSize = (int)vecOverTimePeer.size();
		if(iSize>0)
		{
			for(int i=0; i<iSize; i++)
			{
				LONGLONG lChannelNo = vecOverTimePeer[i];
				
				MAP_TYPE::iterator iter = m_mapServerHandle.find(lChannelNo);

				if( iter != m_mapServerHandle.end())	// 找到了
				{
					CServerHandle* pServerHandle = (CServerHandle*)(*iter).second;
					if(pServerHandle && pServerHandle->is_valid())
					{
						m_mapServerHandle.erase(iter);	// 移除

						//printf("需要删除打印:check_power_close_peer端口号 %d \n",lChannelNo);
						pServerHandle->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
						pServerHandle->close(pServerHandle->get_close_type());			// 强制关闭
					}
				}
			}
		}
	}	// 析构会自动解锁 m_lock


	return 0;
}

// 移除一个对端服务
CServerHandle* CChennelNoMgr::remove_one(LONGLONG lChannelNo)
{
	CThreadGuardWrite guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServerHandle = NULL;

	iter = m_mapServerHandle.find(lChannelNo);

	if( iter != m_mapServerHandle.end())	// 找到了
	{
		pServerHandle = (CServerHandle*)(*iter).second;
		m_mapServerHandle.erase(iter);	// 移除
	}

	return pServerHandle;
}

// 移除一个对端服务
int CChennelNoMgr::remove_one(CServerHandle* pServerHandle)
{
	CThreadGuardWrite guard(&m_lock);

	int iResult = 10;
	CServerHandle* pTmp = NULL;
	MAP_TYPE::iterator iter = m_mapServerHandle.begin();
	int iCount = 0;

	// 对端服务列表赋值
	for(; iter != m_mapServerHandle.end(); iter++)
	{
		pTmp = (CServerHandle*)(*iter).second;

		if(pTmp == pServerHandle && pTmp->is_valid())
		{
			m_mapServerHandle.erase(iter);
			return 0;
		}
	}

	return iResult;
}

// 由通道号获得对端服务指针
CServerHandle* CChennelNoMgr::find(LONGLONG lChannelNo)
{
	CThreadGuardRead guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServerHandle = NULL;

	iter = m_mapServerHandle.find(lChannelNo);

	if( iter != m_mapServerHandle.end())	// 找到了
	{
		pServerHandle = (CServerHandle*)(*iter).second;
	}

	return pServerHandle;
}

// 指定的对端服务是否有效
BOOL CChennelNoMgr::is_valid(LONGLONG lChannelNo)
{
	if(INVALID_CHANNEL_NO==lChannelNo)
		return FALSE;

	CThreadGuardRead guard(&m_lock);

	MAP_TYPE::iterator iter;
	CServerHandle* pServerHandle = NULL;
	BOOL bValid = FALSE;

	iter = m_mapServerHandle.find(lChannelNo);

	if( iter != m_mapServerHandle.end())	// 找到了
	{
		pServerHandle = (CServerHandle*)(*iter).second;
		bValid =  pServerHandle->is_valid();
	}

	return bValid;
}

/* --------------------------------------------------------------------------
函数说明：获得所有有效的对端服务
传出参数：
	vecServerHandle	有效的对端服务的列表
返回值：
    有效的对端服务的数量
--------------------------------------------------------------------------*/
int CChennelNoMgr::get_all_valid(vector<CServerHandle*>& vecServerHandle)
{
	CThreadGuardRead guard(&m_lock);

	CServerHandle* pServerHandle = NULL;
	MAP_TYPE::iterator iter = m_mapServerHandle.begin();
	int iCount = 0;

	// 对端服务列表赋值
	for(; iter != m_mapServerHandle.end(); iter++)
	{
		pServerHandle = (CServerHandle*)(*iter).second;

		if(pServerHandle->is_valid())
		{
			vecServerHandle.push_back(pServerHandle);
			iCount++;
		}
	}

	return iCount;
}


/* --------------------------------------------------------------------------
函数说明：获得所有有效对端的通道号
传出参数：
	vecChannelNo	有效对端的通道号数组
返回值：
    有效的对端服务的数量
--------------------------------------------------------------------------*/
int CChennelNoMgr::get_all_valid(vector<LONGLONG>& vecChannelNo)
{
	CThreadGuardRead guard(&m_lock);

	LONGLONG lChannelNo = INVALID_CHANNEL_NO;
	CServerHandle* pServerHandle = NULL;

	MAP_TYPE::iterator iter = m_mapServerHandle.begin();
	int iCount = 0;

	// 对端服务列表赋值
	for(; iter != m_mapServerHandle.end(); iter++)
	{
		lChannelNo = (LONGLONG)(*iter).first;
		pServerHandle = (CServerHandle*)(*iter).second;

		if(pServerHandle->is_valid())
		{
			vecChannelNo.push_back(lChannelNo);
			iCount++;
		}
	}

	return iCount;
}