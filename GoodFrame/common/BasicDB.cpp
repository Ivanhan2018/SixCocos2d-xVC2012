
#include "./BasicDB.h"
//#include "./PublicHead.h"
//#include "./CoreServer.h"

CBasicDB::CBasicDB(void)
{
	m_bIsDB = TRUE;
}

CBasicDB::~CBasicDB(void)
{
}

// 初始化
int CBasicDB::init_db(int iConnectNum, char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect, UINT uTimeout)
{
	int iNumber = 1;

	// 获得推送消息线程的数量
	int iTaskNum = m_stTaskSinkEx.get_thread_num();	//  数据库任务消息推送线程数量

	//原则上此值最好 >= 数据库任务消息推送线程数量，就可以保证每每数据库任务都拥有一个数据库连接
	if(iConnectNum<iTaskNum)
		iNumber = iTaskNum;
	else
		iNumber = iConnectNum;

	m_stConnPool.Init(iNumber, pszHost, uPort, pszDB, pszUser, pszPass, pszCharset, bReconnect, uTimeout);

	int iUninitNum, iIdleNum, iUsingNum;
	m_stConnPool.GetPoolElementNum(iUninitNum, iIdleNum, iUsingNum);

	return 0;
};

// 启动数据库任务
int CBasicDB::start_db()
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
int CBasicDB::db_heartbeat()
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
int CBasicDB::stop_db()
{
	m_stConnPool.stop();

	return 0;
}

void CBasicDB::test(string* strVal)
{
	string strTmp = "Sony";
	*strVal = strTmp;
}