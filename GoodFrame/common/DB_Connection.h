/********************************************************************
	created:	2013/02/26
	created:	26:2:2013   15:30
	filename: 	E:\SVN_2013\GoodFrame\common\DB_Connection.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	DB_Connection
	file ext:	h
	author:		��ѩ���ṩԴ�룬�������ӡ��޸ġ�����  
	
	purpose:	�̳�DBTunnel��C API��������չ��	connect/ping/query��������װ
*********************************************************************/

#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <string>
#include <vector>

#include "./DB_QueryResult.h"
#include "./DB_Tunnel.h"
#include "./ThreadGuard.h"

struct FIELD_AUTO_OUTPUT	// �ֶ������������Զ����
{
	FIELD_AUTO_OUTPUT(){ memset(this, 0, sizeof(*this));	}

	int	  iType;			// �ֶ�����
	char  szTypeName[32];	// ��������
	char  szFieldName[256];	// �ֶ���
	char  szPrefix[16];		// ǰ׺
	char  szStructName[32];		// �ṹ����Ķ�������
	char  szCode[256];			// ����
	char  szBracket[32];		// �ִ�������
};

// ���ݿ�������
class __declspec(dllexport) CDB_Connection : public CDB_Tunnel
{
public:
	CDB_Connection(void);
	~CDB_Connection(void);

public:

	void Init(char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, BOOL bReconnect=TRUE, UINT uTimeout=28800);

	// ����
	BOOL DoConnect();

	// ����ǰ�Ĳ���
	void Destroy();

	void DoPing();

	// ͬ��ִ�в�ѯ��䣬û�н�����Ĳ�ѯ���� Insert��Update��Delete �����Ͳ�����������
	int DoQuery_NoRes(char* pszQuery, int iLen);

	// ͬ��ִ�в�ѯ��䣬��һ�������
	int DoQuery_SingleRes(char* pszQuery, int iLen, CDB_QueryResult *pResult);

	// ͬ��ִ�в�ѯ��䣬��������
	int DoQuery_MultiRes(char* pszQuery, int iLen, MYSQL_MULTI_RES* pMultiRes);

	// �Ƿ����ӵ����ݿ� ???
	BOOL IsConnected(){return m_bIsConnected;}

	// ����ֶθ�ʽ���ļ�
	int OutputField(char* pszTableName, char* pszInstName, vector<FIELD_AUTO_OUTPUT>& vecAutoOutput);

private:
	// ���������
	void ParseResult(CDB_QueryResult *pResult,MYSQL_RES *pRes);

private:
	CDB_Tunnel m_stTunnel;

private:
	UINT m_uPort;

	string m_strHost;
	string m_strDB;
	string m_strUser;
	string m_pass;
	string m_strCharset;

	UINT m_uTimeout;

	BOOL m_bReconnect;
	BOOL m_bIsConnected;

	string m_strHeartbeat;	// ��������

	CCriticalSpection m_lock;
};

#endif