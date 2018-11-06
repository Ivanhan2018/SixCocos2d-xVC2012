/********************************************************************
	created:	2013/03/04
	created:	4:3:2013   11:21
	filename: 	e:\SVN_2013\GoodFrame\DB_Test\DB_Test\DB_ConnectionPool.h
	file path:	e:\SVN_2013\GoodFrame\DB_Test\DB_Test
	file base:	DB_ConnectionPool
	file ext:	h
	author:		�����
	
	purpose:	���ӳ�
*********************************************************************/

#ifndef DB_CONNECTION_POOL
#define DB_CONNECTION_POOL

#include ".\DB_Connection.h"

enum __declspec(dllexport) CONNECT_STATE // ����״̬
{   
	CS_UNINIT	= 0,	// ��δ��ʼ��
	CS_IDLE		= 1,	// ����
	CS_USING	= 2,	// ����ʹ��
};

struct __declspec(dllexport) CONNECT_INFO	// ������Ϣ
{
	CONNECT_INFO()
	{
		connectState = CS_UNINIT;
		pConn = NULL;
	}

	CONNECT_STATE	connectState;	// ����״̬
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
	����˵������ʼ��
	���������
		iConnectNum	��������ע��Ӧ��ȡֵ��������>=(�����߳�+2)
		strHost		������ַ
		uPort		�˿�
		strDB		���ݿ���
		strUser		���ݿ��û������� root
		strPass		���ݿ�����
		strCharset	���ݿ��ַ���
		bReconnect	���ݿ���ߺ��Ƿ�����
		uTimeout	�Ự���г�ʱ
	--------------------------------------------------------------------------*/
	void Init(int iConnectNum, char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect=TRUE, UINT uTimeout=28800);

	/* --------------------------------------------------------------------------
	����˵��������
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	DoConnect ʧ��
	--------------------------------------------------------------------------*/
	int start();

	// ֹͣ
	int stop();

	/* --------------------------------------------------------------------------
	����˵����������е�����
	����������
		pVecAllConnect	��������
	--------------------------------------------------------------------------*/
	CDB_Connection* GetAllConnect(vector<CONNECT_INFO>* pVecAllConnect);

	/* --------------------------------------------------------------------------
	����˵������ó��м���Ԫ�ص�����
	����������
		iUninitNum	��δ��ʼ����Ԫ������
		iIdleNum	���е�Ԫ������
		iUsingNum	����ʹ�õ�Ԫ������
	--------------------------------------------------------------------------*/
	void GetPoolElementNum(int& iUninitNum, int& iIdleNum, int& iUsingNum);

private:
	// ���ӳ���
	CDB_Connection* Retrieve();

	// ���ӹ��
	int Recycle(CDB_Connection*& pConnection);

private:
	vector<CONNECT_INFO>	m_vecConn;
	int m_iConnectNum;

	CCriticalSpection m_lockConn;	// �� m_vecConn
};

#endif