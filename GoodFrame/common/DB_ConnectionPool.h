/********************************************************************
	created:	2013/03/04
	created:	4:3:2013   11:21
	filename: 	e:\SVN_2013\GoodFrame\DB_Test\DB_Test\DB_ConnectionPool.h
	file path:	e:\SVN_2013\GoodFrame\DB_Test\DB_Test
	file base:	DB_ConnectionPool
	file ext:	h
	author:		侯国江
	
	purpose:	连接池
*********************************************************************/

#ifndef DB_CONNECTION_POOL
#define DB_CONNECTION_POOL

#include ".\DB_Connection.h"

enum __declspec(dllexport) CONNECT_STATE // 连接状态
{   
	CS_UNINIT	= 0,	// 还未初始化
	CS_IDLE		= 1,	// 空闲
	CS_USING	= 2,	// 正在使用
};

struct __declspec(dllexport) CONNECT_INFO	// 连接信息
{
	CONNECT_INFO()
	{
		connectState = CS_UNINIT;
		pConn = NULL;
	}

	CONNECT_STATE	connectState;	// 连接状态
	CDB_Connection* pConn;
};

class __declspec(dllexport) CDB_ConnectionGuard;

class __declspec(dllexport) CDB_ConnectionPool
{
public:
	friend class CDB_ConnectionGuard;

public:
	CDB_ConnectionPool(void);
	~CDB_ConnectionPool(void);

public:

	/* --------------------------------------------------------------------------
	函数说明：初始化
	传入参数：
		iConnectNum	连接数，注意应该取值：连接数>=(任务线程+2)
		strHost		主机地址
		uPort		端口
		strDB		数据库名
		strUser		数据库用户名，如 root
		strPass		数据库密码
		strCharset	数据库字符集
		bReconnect	数据库断线后是否重连
		uTimeout	会话空闲超时
	--------------------------------------------------------------------------*/
	void Init(int iConnectNum, char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect=TRUE, UINT uTimeout=28800);

	/* --------------------------------------------------------------------------
	函数说明：启动
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	DoConnect 失败
	--------------------------------------------------------------------------*/
	int start();

	// 停止
	int stop();

	/* --------------------------------------------------------------------------
	函数说明：获得所有的连接
	传出参数：
		pVecAllConnect	连接数组
	--------------------------------------------------------------------------*/
	CDB_Connection* GetAllConnect(vector<CONNECT_INFO>* pVecAllConnect);

	/* --------------------------------------------------------------------------
	函数说明：获得池中几种元素的数量
	传出参数：
		iUninitNum	还未初始化的元素数量
		iIdleNum	空闲的元素数量
		iUsingNum	正在使用的元素数量
	--------------------------------------------------------------------------*/
	void GetPoolElementNum(int& iUninitNum, int& iIdleNum, int& iUsingNum);

private:
	// 连接出池
	CDB_Connection* Retrieve();

	// 连接归池
	int Recycle(CDB_Connection*& pConnection);

private:
	vector<CONNECT_INFO>	m_vecConn;
	int m_iConnectNum;

	CCriticalSpection m_lockConn;	// 锁 m_vecConn
};

#endif