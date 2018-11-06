
#include "./PublicHead.h"
#include "GeneralDB.h"

CGeneralDB::CGeneralDB(void)
{
	m_bIsDB = TRUE;
}

CGeneralDB::~CGeneralDB(void)
{
}

// 初始化
int CGeneralDB::init_db(char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect, UINT uTimeout)
{
	int iNumber = m_iWorkerNum;

	// 连接池的数量就是工人的数量
	m_stConnPool.Init(iNumber, pszHost, uPort, pszDB, pszUser, pszPass, pszCharset, bReconnect, uTimeout);

	int iUninitNum, iIdleNum, iUsingNum;
	m_stConnPool.GetPoolElementNum(iUninitNum, iIdleNum, iUsingNum);

	return 0;
};

// 启动数据库任务
int CGeneralDB::start_db()
{
	int iRes = m_stConnPool.start() ;
	if(0!=iRes)
		return 10;	// 连接数据库失败

	iRes = start();	// 启动任务模块，此句不能省略
	if(0!=iRes)
		return 20;	// 启动数据库任务失败

	return 0;
}

// 向数据库发心跳包，因为数据库在长时间得不到访问就会自动断线
int CGeneralDB::db_heartbeat()
{
	int iRes = 0;

	vector<CONNECT_INFO> vecAllConnect;
	m_stConnPool.GetAllConnect(&vecAllConnect);	// 获得所有的连接

	vector<CONNECT_INFO>::iterator iter = vecAllConnect.begin();
	for( ; iter!=vecAllConnect.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;

		if(connInfo.pConn->IsConnected() && CONNECT_STATE::CS_UNINIT != connInfo.connectState)
			connInfo.pConn->DoPing();
	}

	return iRes;
}

// 停止
int CGeneralDB::stop_db()
{
	m_stConnPool.stop();

	return 0;
}

void CGeneralDB::test(string* strVal)
{
	string strTmp = "Sony";
	*strVal = strTmp;
}