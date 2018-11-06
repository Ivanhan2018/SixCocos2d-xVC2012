/********************************************************************
	created:	2013/02/26
	created:	26:2:2013   15:30
	filename: 	E:\SVN_2013\GoodFrame\common\DB_Connection.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	DB_Connection
	file ext:	h
	author:		曹雪垠提供源码，侯国江添加、修改、整合  
	
	purpose:	继承DBTunnel的C API并加入扩展，	connect/ping/query做加锁包装
*********************************************************************/

#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <string>
#include <vector>

#include "./DB_QueryResult.h"
#include "./DB_Tunnel.h"
#include "./ThreadGuard.h"

struct FIELD_AUTO_OUTPUT	// 字段名称与类型自动输出
{
	FIELD_AUTO_OUTPUT(){ memset(this, 0, sizeof(*this));	}

	int	  iType;			// 字段类型
	char  szTypeName[32];	// 类型名称
	char  szFieldName[256];	// 字段名
	char  szPrefix[16];		// 前缀
	char  szStructName[32];		// 结构或类的对象名称
	char  szCode[256];			// 代码
	char  szBracket[32];		// 字串的括号
};

// 数据库连接类
class __declspec(dllexport) CDB_Connection : public CDB_Tunnel
{
public:
	CDB_Connection(void);
	~CDB_Connection(void);

public:

	void Init(char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, BOOL bReconnect=TRUE, UINT uTimeout=28800);

	// 连接
	BOOL DoConnect();

	// 销毁前的操作
	void Destroy();

	void DoPing();

	// 同步执行查询语句，没有结果集的查询，如 Insert、Update、Delete 等语句就不会产生结果集
	int DoQuery_NoRes(char* pszQuery, int iLen);

	// 同步执行查询语句，有一个结果集
	int DoQuery_SingleRes(char* pszQuery, int iLen, CDB_QueryResult *pResult);

	// 同步执行查询语句，多个结果集
	int DoQuery_MultiRes(char* pszQuery, int iLen, MYSQL_MULTI_RES* pMultiRes);

	// 是否连接到数据库 ???
	BOOL IsConnected(){return m_bIsConnected;}

	// 输出字段格式到文件
	int OutputField(char* pszTableName, char* pszInstName, vector<FIELD_AUTO_OUTPUT>& vecAutoOutput);

private:
	// 解析结果集
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

	string m_strHeartbeat;	// 心跳内容

	CCriticalSpection m_lock;
};

#endif