
/********************************************************************
	created:	2013/03/4
	created:	4:3:2013   22:33
	filename: 	E:\SVN_2013\GoodFrame\common\DB_ConnectionGuard.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	DB_ConnectionGuard
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef DB_CONNECTION_GUARD_H
#define DB_CONNECTION_GUARD_H

#include "DB_ConnectionPool.h"

// 连接守护，这样连接出池不用担心归池的问题，更安全
class __declspec(dllexport) CDB_ConnectionGuard
{
public:
	CDB_ConnectionGuard(CDB_ConnectionPool* pConnectionPool);
	~CDB_ConnectionGuard(void);

	// 获得连接
	CDB_Connection* CDB_ConnectionGuard::get_connection();

private:
	CDB_ConnectionPool* m_pConnectionPool;
	CDB_Connection*		m_pConn;
};

#endif