
#include "DB_ConnectionPool.h"

CDB_ConnectionPool::CDB_ConnectionPool(void)
{
	m_iConnectNum = 1;
}

CDB_ConnectionPool::~CDB_ConnectionPool(void)
{
}

// 初始化
void CDB_ConnectionPool::Init(int iConnectNum, char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect, UINT uTimeout)
{
	m_iConnectNum = iConnectNum;

	// 建立连接池
	for(int i=0; i<m_iConnectNum; i++)
	{
		CONNECT_INFO connInfo;
		connInfo.pConn = new CDB_Connection;
		if(connInfo.pConn)
		{
			connInfo.pConn->Init(pszHost, uPort, pszDB, pszUser, pszPass, pszCharset, uTimeout, FALSE);
			connInfo.connectState = CS_UNINIT;	// 还未初始化
			m_vecConn.push_back(connInfo);
		}
	}
};

// 启动
int CDB_ConnectionPool::start()
{
	CThreadGuard guard(&m_lockConn);

	// 启动连接池
	BOOL bFlag = FALSE;
	vector<CONNECT_INFO>::iterator iter = m_vecConn.begin();
	for( ; iter!=m_vecConn.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;
	
		bFlag = connInfo.pConn->DoConnect();
		if(!bFlag)
		{
			printf("连接数据库失败 \n");
			return 10;	// DoConnect 失败
		}

		connInfo.connectState = CS_IDLE;	// 空闲
	}

	return 0;
}

// 停止
int CDB_ConnectionPool::stop()
{
	CThreadGuard guard(&m_lockConn);

	// 启动连接池
	BOOL bFlag = FALSE;
	vector<CONNECT_INFO>::iterator iter = m_vecConn.begin();
	for( ; iter!=m_vecConn.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;

		connInfo.pConn->Destroy();
		connInfo.connectState = CS_UNINIT;	// 还未初始化
	}

	return 0;
}

// 获得所有的连接
CDB_Connection* CDB_ConnectionPool::GetAllConnect(vector<CONNECT_INFO>* pVecAllConnect)
{
	CThreadGuard guard(&m_lockConn);

	vector<CONNECT_INFO>::iterator iter = m_vecConn.begin();
	for( ; iter!=m_vecConn.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;

		pVecAllConnect->push_back(connInfo);
	}

	return NULL;
}

// 连接出池
CDB_Connection* CDB_ConnectionPool::Retrieve()
{
	CThreadGuard guard(&m_lockConn);

	vector<CONNECT_INFO>::iterator iter = m_vecConn.begin();
	for( ; iter!=m_vecConn.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;

		if(CS_IDLE == connInfo.connectState)
		{
			connInfo.connectState = CS_USING;	// 正在使用
			return connInfo.pConn;
		}
	}

	return NULL;
}

/* --------------------------------------------------------------------------
函数说明：连接归池
传入参数：
	pConnection 连接
返回值：
    成功则返回 0，失败返回错误码如下：
		10 未找到形参的 pConnection
--------------------------------------------------------------------------*/
int CDB_ConnectionPool::Recycle(CDB_Connection*& pConnection)
{
	CThreadGuard guard(&m_lockConn);

	vector<CONNECT_INFO>::iterator iter = m_vecConn.begin();
	for( ; iter!=m_vecConn.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;

		if(pConnection == connInfo.pConn)
		{
			connInfo.connectState = CS_IDLE;	// 正在使用
			return 0;
		}
	}

	return 10;	// 未找到形参的 pConnection
}

// 获得池中几种元素的数量
void CDB_ConnectionPool::GetPoolElementNum(int& iUninitNum, int& iIdleNum, int& iUsingNum)
{
	CThreadGuard guard(&m_lockConn);

	iUninitNum = 0;
	iIdleNum = 0; 
	iUsingNum = 0;

	vector<CONNECT_INFO>::iterator iter = m_vecConn.begin();
	for( ; iter!=m_vecConn.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;

		if(CS_UNINIT==connInfo.connectState)	// 还未初始化
			iUninitNum++;
		else if(CS_IDLE==connInfo.connectState)	// 空闲
			iIdleNum++;
		else if(CS_USING==connInfo.connectState)	// 正在使用
			iUsingNum++;
	}

}

