
#include "DB_ConnectionGuard.h"


CDB_ConnectionGuard::CDB_ConnectionGuard(CDB_ConnectionPool* pConnectionPool)
{
	m_pConnectionPool = pConnectionPool;
	m_pConn = NULL;
}


CDB_ConnectionGuard::~CDB_ConnectionGuard(void)
{
	if(m_pConn)
	{
		m_pConnectionPool->Recycle(m_pConn);	// 连接归池
		m_pConn = NULL;
	}
}

// 获得连接
CDB_Connection* CDB_ConnectionGuard::get_connection()
{
	if(m_pConnectionPool)
	{
		m_pConn = m_pConnectionPool->Retrieve();	// 连接出池
		return m_pConn;
	}

	return NULL;
}