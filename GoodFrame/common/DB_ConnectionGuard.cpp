
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
		m_pConnectionPool->Recycle(m_pConn);	// ���ӹ��
		m_pConn = NULL;
	}
}

// �������
CDB_Connection* CDB_ConnectionGuard::get_connection()
{
	if(m_pConnectionPool)
	{
		m_pConn = m_pConnectionPool->Retrieve();	// ���ӳ���
		return m_pConn;
	}

	return NULL;
}