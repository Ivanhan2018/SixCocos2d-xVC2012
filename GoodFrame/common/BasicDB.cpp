
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

// ��ʼ��
int CBasicDB::init_db(int iConnectNum, char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect, UINT uTimeout)
{
	int iNumber = 1;

	// ���������Ϣ�̵߳�����
	int iTaskNum = m_stTaskSinkEx.get_thread_num();	//  ���ݿ�������Ϣ�����߳�����

	//ԭ���ϴ�ֵ��� >= ���ݿ�������Ϣ�����߳��������Ϳ��Ա�֤ÿÿ���ݿ�����ӵ��һ�����ݿ�����
	if(iConnectNum<iTaskNum)
		iNumber = iTaskNum;
	else
		iNumber = iConnectNum;

	m_stConnPool.Init(iNumber, pszHost, uPort, pszDB, pszUser, pszPass, pszCharset, bReconnect, uTimeout);

	int iUninitNum, iIdleNum, iUsingNum;
	m_stConnPool.GetPoolElementNum(iUninitNum, iIdleNum, iUsingNum);

	return 0;
};

// �������ݿ�����
int CBasicDB::start_db()
{
	int iRes = m_stConnPool.start() ;
	if(0!=iRes)
		return 10;	// �������ݿ�ʧ��

	iRes = start();	// ��������ģ�飬�˾䲻��ʡ��
	if(0!=iRes)
		return 20;	// �������ݿ�����ʧ��

	return 0;
}

// �����ݿⷢ����������Ϊ���ݿ��ڳ�ʱ��ò������ʾͻ��Զ�����
int CBasicDB::db_heartbeat()
{
	int iRes = 0;

	vector<CONNECT_INFO> vecAllConnect;
	m_stConnPool.GetAllConnect(&vecAllConnect);	// ������е�����

	vector<CONNECT_INFO>::iterator iter = vecAllConnect.begin();
	for( ; iter!=vecAllConnect.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;

		if(connInfo.pConn->IsConnected() && CONNECT_STATE::CS_UNINIT != connInfo.connectState)
			connInfo.pConn->DoPing();
	}

	return iRes;
}

// ֹͣ
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