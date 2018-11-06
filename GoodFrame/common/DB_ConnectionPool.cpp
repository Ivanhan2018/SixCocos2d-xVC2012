
#include "DB_ConnectionPool.h"

CDB_ConnectionPool::CDB_ConnectionPool(void)
{
	m_iConnectNum = 1;
}

CDB_ConnectionPool::~CDB_ConnectionPool(void)
{
}

// ��ʼ��
void CDB_ConnectionPool::Init(int iConnectNum, char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect, UINT uTimeout)
{
	m_iConnectNum = iConnectNum;

	// �������ӳ�
	for(int i=0; i<m_iConnectNum; i++)
	{
		CONNECT_INFO connInfo;
		connInfo.pConn = new CDB_Connection;
		if(connInfo.pConn)
		{
			connInfo.pConn->Init(pszHost, uPort, pszDB, pszUser, pszPass, pszCharset, uTimeout, FALSE);
			connInfo.connectState = CS_UNINIT;	// ��δ��ʼ��
			m_vecConn.push_back(connInfo);
		}
	}
};

// ����
int CDB_ConnectionPool::start()
{
	CThreadGuard guard(&m_lockConn);

	// �������ӳ�
	BOOL bFlag = FALSE;
	vector<CONNECT_INFO>::iterator iter = m_vecConn.begin();
	for( ; iter!=m_vecConn.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;
	
		bFlag = connInfo.pConn->DoConnect();
		if(!bFlag)
		{
			printf("�������ݿ�ʧ�� \n");
			return 10;	// DoConnect ʧ��
		}

		connInfo.connectState = CS_IDLE;	// ����
	}

	return 0;
}

// ֹͣ
int CDB_ConnectionPool::stop()
{
	CThreadGuard guard(&m_lockConn);

	// �������ӳ�
	BOOL bFlag = FALSE;
	vector<CONNECT_INFO>::iterator iter = m_vecConn.begin();
	for( ; iter!=m_vecConn.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;

		connInfo.pConn->Destroy();
		connInfo.connectState = CS_UNINIT;	// ��δ��ʼ��
	}

	return 0;
}

// ������е�����
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

// ���ӳ���
CDB_Connection* CDB_ConnectionPool::Retrieve()
{
	CThreadGuard guard(&m_lockConn);

	vector<CONNECT_INFO>::iterator iter = m_vecConn.begin();
	for( ; iter!=m_vecConn.end(); iter++)
	{
		CONNECT_INFO& connInfo = *iter;

		if(CS_IDLE == connInfo.connectState)
		{
			connInfo.connectState = CS_USING;	// ����ʹ��
			return connInfo.pConn;
		}
	}

	return NULL;
}

/* --------------------------------------------------------------------------
����˵�������ӹ��
���������
	pConnection ����
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10 δ�ҵ��βε� pConnection
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
			connInfo.connectState = CS_IDLE;	// ����ʹ��
			return 0;
		}
	}

	return 10;	// δ�ҵ��βε� pConnection
}

// ��ó��м���Ԫ�ص�����
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

		if(CS_UNINIT==connInfo.connectState)	// ��δ��ʼ��
			iUninitNum++;
		else if(CS_IDLE==connInfo.connectState)	// ����
			iIdleNum++;
		else if(CS_USING==connInfo.connectState)	// ����ʹ��
			iUsingNum++;
	}

}

