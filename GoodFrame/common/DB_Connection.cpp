
#include "PublicHead.h"
#include "DB_Connection.h"

CDB_Connection::CDB_Connection(void)
{
	m_bIsConnected = FALSE;
}


CDB_Connection::~CDB_Connection(void)
{
}

void CDB_Connection::Init(char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, BOOL bReconnect, UINT uTimeout)
{
	CThreadGuard guard(&m_lock);

	m_uPort = uPort;
	m_strHost = pszHost;
	m_strDB = pszDB;
	m_strUser = pszUser;
	m_pass = pszPass;
	m_strCharset = pszCharset;

	m_bReconnect = bReconnect;
	m_uTimeout = uTimeout;

	m_bIsConnected = FALSE;

};

void CDB_Connection::DoPing()
{
	CThreadGuard guard(&m_lock);

	if (!IsConnected())
		return;

	m_stTunnel.mysql_ping();
}

// 解析结果集
void CDB_Connection::ParseResult(CDB_QueryResult *pResult,MYSQL_RES *pRes)
{
	if (!pResult || !pRes)
		return;

	// 行数
	ULONGLONG rows = m_stTunnel.mysql_num_rows(pRes);

	// 列数
	UINT cols = m_stTunnel.mysql_num_fields(pRes);

	pResult->SetRowsNum(rows);
	pResult->SetColsNum(cols);

	enum_field_types t_type = MYSQL_TYPE_NULL;

	// 列名
	MYSQL_FIELD *fields = 0;
	for(int i = 0; fields = mysql_fetch_field(pRes);++i)
		pResult->SetFieldName(i,fields->name);	// 获得列名


	for (ULONGLONG i=0;i<rows;i++)	// 遍历所有的行
	{
		MYSQL_ROW row = m_stTunnel.mysql_fetch_row(pRes);	// 检索结果集的下一行
		if (!row)
			break;

		unsigned long *pLen = m_stTunnel.mysql_fetch_lengths(pRes);	// 返回结果集内当前行的列的长度，以列的数组形式呈现

		// 对于结果集，返回所有MYSQL_FIELD结构的数组。每个结构提供了结果集中1列的字段定义。
		// 返回值，关于结果集所有列的MYSQL_FIELD结构的数组。
		MYSQL_FIELD *fields = m_stTunnel.mysql_fetch_fields(pRes);

		for (UINT j=0;j<cols;j++)	// 遍历所有的列
		{
			FIELD_INFO *pField = new FIELD_INFO();
			pField->uColId = j;

			// 字段类型暂时未用到，待以后添加
			// Cool.Cat@2013-02-18
			pField->fieldType = fields[j].type;

			// 字段值在MYSQL_ROW中
			pField->uDataLen = pLen[j];
			pField->pData = new BYTE[pField->uDataLen+1];
			memcpy(pField->pData,row[j],pField->uDataLen);
			pField->pData[pField->uDataLen] = 0;	// 最后一个字符置为0值

			pResult->AddFieldValue(i,pField);

			#if 0	// 本段测试用
				BOOL bIsNum = IS_NUM(fields->type);	// 是否数字类型，但似乎不对呀??? 字串值它也是 1
				BOOL bIsLongData = IS_LONGDATA(fields->type);	// 是否大数（MYSQL_TYPE_TINY_BLOB 与 MYSQL_TYPE_STRING），但似乎不对呀??? 无论什么值都是 0
				int  iMaxLength = fields->max_length;		// 但似乎不对呀??? 无论什么值都是 1

				int iTmp = 0;
			#endif
		}
	}
}

// 连接
BOOL CDB_Connection::DoConnect()
{
	CThreadGuard guard(&m_lock);

	if (IsConnected())
		return m_bIsConnected;

	if (!m_stTunnel.mysql_init())
		goto error;

	// 设置字符集
	if (m_strCharset.length())
		m_stTunnel.mysql_options(MYSQL_SET_CHARSET_NAME,m_strCharset.c_str());

	// 设置断线重连
	if (m_bReconnect)
		m_stTunnel.mysql_options(MYSQL_OPT_RECONNECT,"true");

	// 设置Session超时
	if (m_uTimeout)
	{
		char timeoutStr[MAX_PATH] = {0};
		_snprintf(timeoutStr,MAX_PATH-1,"/*!40101 set @@session.wait_timeout=%d */",m_uTimeout);
		m_stTunnel.mysql_options(MYSQL_INIT_COMMAND,timeoutStr);
	}

	// 连接MySQL(允许多结果集返回)
	if (!m_stTunnel.mysql_real_connect(m_strHost.c_str(),m_strUser.c_str(),m_pass.c_str(),m_strDB.c_str(),m_uPort,0,CLIENT_MULTI_RESULTS))
		goto error;

	m_bIsConnected = TRUE;

error:
	printf("DoConnect[%s:%u][%s][%s][%s]...\n",m_strHost.c_str(),m_uPort,m_strUser.c_str(),m_pass.c_str(),m_strDB.c_str());
	if (m_bIsConnected)
		printf("DoConnect.Successed!\n");
	else
		printf("DoConnect.Error![%d][%s]\n",m_stTunnel.mysql_errno(),m_stTunnel.mysql_error().c_str());
	return m_bIsConnected;
}

// 销毁前的操作
void CDB_Connection::Destroy()
{
	CThreadGuard guard(&m_lock);

	if (IsConnected())
	{
		// 释放MySQL连接资源
		m_stTunnel.mysql_close();
		m_bIsConnected = FALSE;
		printf("[%s]连接释放[0x%08X]...\n",
			__FUNCTION__,
			this);
	}
}

/* --------------------------------------------------------------------------
函数说明：同步执行查询语句，没有结果集的查询，如 Insert、Update、Delete 等语句就不会产生结果集
传入参数：
	query	查询语句
返回值：
    成功则返回 0，失败返回错误码如下：
		10	已经断开连接啦
		20	mysql_real_query 失败
		30	居然有结果集，应该使用 DoQuery_SingleRes 或 DoQuery_MultiRes 函数
--------------------------------------------------------------------------*/
int CDB_Connection::DoQuery_NoRes(char* pszQuery, int iLen)
{
	CThreadGuard guard(&m_lock);

	if (!IsConnected())
		return 10;		// 已经断开连接啦

	// 如果查询成功，返回0。如果出现错误，返回非0值
	int iRes = m_stTunnel.mysql_real_query(pszQuery, iLen);
	if (0 != iRes)
	{
		printf("[%s]err[%s]\n", __FUNCTION__, m_stTunnel.mysql_error().c_str());
		return 20;	// mysql_real_query 失败
	}

	MYSQL_RES *res = m_stTunnel.mysql_store_result();
	if(res)
		return 30;	// 居然有结果集，应该使用 DoQuery_SingleRes 或 DoQuery_MultiRes 函数

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：同步执行查询语句，有一个结果集
传入参数：
	strQuery	查询语句
传出参数：
	queryResult     查询结果
	MYSQL_MULTI_RES	多个查询结果集
返回值：
    成功则返回 0，失败返回错误码如下：
		10	已经断开连接啦
		20	mysql_real_query 失败
		50	无结果集，应该用 DoQuery_NoRes 函数
		80  出现了多结果集，应该用 DoQuery_MultiRes 函数
--------------------------------------------------------------------------*/
int CDB_Connection::DoQuery_SingleRes(char* pszQuery, int iLen, CDB_QueryResult *pResult)
{
	CThreadGuard guard(&m_lock);

	if (!IsConnected())
		return 10;		// 已经断开连接啦

	// 如果查询成功，返回0。如果出现错误，返回非0值
	int iRes = m_stTunnel.mysql_real_query(pszQuery, iLen);
	if (0 != iRes)
	{
		printf("[%s]err[%s]\n", __FUNCTION__, m_stTunnel.mysql_error().c_str());
		return 20;	// mysql_real_query 失败
	}

	MYSQL_RES *res = m_stTunnel.mysql_store_result();

	if (!res)	// 无结果集，例如 Insert、Update、Delete
	{
		return 50;	// 无结果集，应该用 DoQuery_NoRes 函数
	}

	ParseResult(pResult, res);	// 解析结果集

	m_stTunnel.mysql_free_result(res);	

	int nextResult = m_stTunnel.mysql_next_result();	// 下一个结果集
	if (nextResult==-1)	// -1 表示无结果集，是正确的。
		return 0;

	if (0!=nextResult)	// 上一句既不等于-1，这一句又不等于0，表示还有结果集
	{
		return 80;  // 出现了多结果集，应该用 DoQuery_MultiRes 函数
	}

	res = m_stTunnel.mysql_store_result();
	if (0 != res)	// 下一个结果集非空，表示有多个结果集
	{
		return 80;  // 出现了多结果集，应该用 DoQuery_MultiRes 函数
	}

	// 下一个结果集非空，是正确的
	return 0;
}

/* --------------------------------------------------------------------------
函数说明：同步执行查询语句，多个结果集
传入参数：
	strQuery	查询语句
传出参数：
	queryResult     查询结果
	MYSQL_MULTI_RES	多个查询结果集
返回值：
    成功则返回 0，失败返回错误码如下：
		10	已经断开连接啦
		20	mysql_real_query 失败
		40  无结果集、又没有影响行数，出错了
--------------------------------------------------------------------------*/
int CDB_Connection::DoQuery_MultiRes(char* pszQuery, int iLen, MYSQL_MULTI_RES* pMultiRes)
{
	CThreadGuard guard(&m_lock);

	if (!IsConnected())
		return 10;		// 已经断开连接啦

	// 如果查询成功，返回0。如果出现错误，返回非0值
	int iRes = m_stTunnel.mysql_real_query(pszQuery, iLen);
	if (0 != iRes)
	{
		printf("[%s]err[%s]\n", __FUNCTION__, m_stTunnel.mysql_error().c_str());
		return 20;	// mysql_real_query 失败
	}

	// 例如 Insert、Update、Delete无返回，所以结果集会为空
	// 因此要用mysql_affected_rows()来获取影响的行数
	MYSQL_RES *res = m_stTunnel.mysql_store_result();

	if (!res)	// 无结果集，例如 Insert、Update、Delete
	{
		// 返回被最新的UPDATE、DELETE、INSERT查询影响的行数。
		ULONGLONG affected_rows = m_stTunnel.mysql_affected_rows();

		if (affected_rows)	// 影响了行数，例如 Insert、Update、Delete
		{
			CDB_QueryResult *pResult = new CDB_QueryResult();
			pResult->SetRowsNum(1);
			pMultiRes->push_back(pResult);
		
			return 0;	// 成功的
		}

		// 无结果集、又没有影响行数，应该是出错了。。。
		printf("[%s]DoQuery.Err[%s]\n",
			__FUNCTION__,
			m_stTunnel.mysql_error().c_str());

		return 40;	// 无结果集、又没有影响行数，出错了
	}

	CDB_QueryResult *pResult = new CDB_QueryResult();
	ParseResult(pResult,res);
	pMultiRes->push_back(pResult);
	m_stTunnel.mysql_free_result(res);	

	// 可能返回有多个结果集
	while (TRUE)
	{
		int nextResult = m_stTunnel.mysql_next_result();	// 下一个结果集
		if (nextResult==-1)
			break;
		if (nextResult!=0)
		{
			printf("[%s]DoQuery.Err[%s]\n",
				__FUNCTION__,
				m_stTunnel.mysql_error().c_str());
			break;
		}

		// 多个结果集
		res = m_stTunnel.mysql_store_result();
		if (res!=0)
		{
			pResult = new CDB_QueryResult();
			ParseResult(pResult,res);
			pMultiRes->push_back(pResult);

			m_stTunnel.mysql_free_result(res);

			continue;
		}
	}

	return 0;
}

// 输出字段格式到文件
int CDB_Connection::OutputField(char* pszTableName, char* pszInstName, vector<FIELD_AUTO_OUTPUT>& vecAutoOutput)
{
	CThreadGuard guard(&m_lock);

	if (!IsConnected())
		return 10;		// 已经断开连接啦

	if(!pszInstName)
		return 20;	// 实例（对象与指针）名为空

	string strTmp = "select * from ";
	string strQuery = strTmp + pszTableName;

	// 如果查询成功，返回0。如果出现错误，返回非0值
	int iRes = m_stTunnel.mysql_real_query(strQuery.c_str(), (int)strQuery.length());
	if (0 != iRes)
	{
		printf("[%s]err[%s]\n", __FUNCTION__, m_stTunnel.mysql_error().c_str());
		return 20;	// mysql_real_query 失败
	}

	MYSQL_RES *pRes = m_stTunnel.mysql_store_result();

	if (!pRes)	// 无结果集，例如 Insert、Update、Delete
	{
		return 50;	// 无结果集，应该用 DoQuery_NoRes 函数
	}

	ULONGLONG rows = m_stTunnel.mysql_num_rows(pRes);	// 行数
	UINT cols = m_stTunnel.mysql_num_fields(pRes);	// 列数

	enum_field_types t_type = MYSQL_TYPE_NULL;

	MYSQL_FIELD *fields = 0;	// 列名
	for(int i = 0; fields = mysql_fetch_field(pRes);++i)	// 遍历每一个字段
	{
		FIELD_AUTO_OUTPUT tmpPut;

		_snprintf(tmpPut.szFieldName, sizeof(tmpPut.szFieldName), "%s", fields->name);
		tmpPut.iType = fields->type;

		switch(tmpPut.iType)	// 根据类型赋值前缀
		{
		case MYSQL_TYPE_TINY:
		case MYSQL_TYPE_SHORT:
		case MYSQL_TYPE_LONG:
			{
				_snprintf(tmpPut.szTypeName, sizeof(tmpPut.szTypeName), "int");
				_snprintf(tmpPut.szPrefix, sizeof(tmpPut.szPrefix), "i");
				_snprintf(tmpPut.szStructName, sizeof(tmpPut.szStructName), "%s%s", tmpPut.szPrefix, tmpPut.szFieldName);
				_snprintf(tmpPut.szCode, sizeof(tmpPut.szCode), "iRes = CDB_QueryResult::Get_INT(pItem, \"%s\", iRow, %s%s)", 
						  tmpPut.szFieldName, pszInstName, tmpPut.szStructName);
					
				break;
			}
		case MYSQL_TYPE_LONGLONG:
		case MYSQL_TYPE_INT24:
			{
				_snprintf(tmpPut.szTypeName, sizeof(tmpPut.szTypeName), "long long");
				_snprintf(tmpPut.szPrefix, sizeof(tmpPut.szPrefix), "l");
				_snprintf(tmpPut.szStructName, sizeof(tmpPut.szStructName), "%s%s", tmpPut.szPrefix, tmpPut.szFieldName);
				_snprintf(tmpPut.szCode, sizeof(tmpPut.szCode), "iRes = CDB_QueryResult::Get_LONGLONG(pItem, \"%s\", iRow, %s%s)", 
						  tmpPut.szFieldName, pszInstName, tmpPut.szStructName);
				break;
			}
		case MYSQL_TYPE_FLOAT:
			{
				_snprintf(tmpPut.szTypeName, sizeof(tmpPut.szTypeName), "float");
				_snprintf(tmpPut.szPrefix, sizeof(tmpPut.szPrefix), "f");
				_snprintf(tmpPut.szStructName, sizeof(tmpPut.szStructName), "%s%s", tmpPut.szPrefix, tmpPut.szFieldName);
				_snprintf(tmpPut.szCode, sizeof(tmpPut.szCode), "iRes = CDB_QueryResult::Get_float(pItem, \"%s\", iRow, %s%s)", 
						  tmpPut.szFieldName, pszInstName, tmpPut.szStructName);
				break;
			}
		case MYSQL_TYPE_DOUBLE:
			{
				_snprintf(tmpPut.szTypeName, sizeof(tmpPut.szTypeName), "double");
				_snprintf(tmpPut.szPrefix, sizeof(tmpPut.szPrefix), "d");
				_snprintf(tmpPut.szStructName, sizeof(tmpPut.szStructName), "%s%s", tmpPut.szPrefix, tmpPut.szFieldName);
				_snprintf(tmpPut.szCode, sizeof(tmpPut.szCode), "iRes = CDB_QueryResult::Get_double(pItem, \"%s\", iRow, %s%s)", 
						  tmpPut.szFieldName, pszInstName, tmpPut.szStructName);
				break;
			}
		case MYSQL_TYPE_VARCHAR:
		case MYSQL_TYPE_VAR_STRING:
		case MYSQL_TYPE_STRING:
			{
				_snprintf(tmpPut.szTypeName, sizeof(tmpPut.szTypeName), "char");
				_snprintf(tmpPut.szBracket, sizeof(tmpPut.szBracket), "[STRING_LEN]");
				_snprintf(tmpPut.szPrefix, sizeof(tmpPut.szPrefix), "sz");
				_snprintf(tmpPut.szStructName, sizeof(tmpPut.szStructName), "%s%s", tmpPut.szPrefix, tmpPut.szFieldName);
				_snprintf(tmpPut.szCode, sizeof(tmpPut.szCode), "iRes = CDB_QueryResult::Get_Char(pItem, \"%s\", iRow, %s%s, sizeof(%s%s)-1 )", 
						  tmpPut.szFieldName, pszInstName, tmpPut.szStructName, pszInstName, tmpPut.szStructName);
				break;
			}
		case MYSQL_TYPE_TIMESTAMP:	// 例句 2013-02-27 16:26:09
		case MYSQL_TYPE_DATETIME:	// 例句 2013-03-04 17:42:27
			{
				_snprintf(tmpPut.szTypeName, sizeof(tmpPut.szTypeName), "EASY_DATA_TIME");
				_snprintf(tmpPut.szPrefix, sizeof(tmpPut.szPrefix), "time");
				_snprintf(tmpPut.szStructName, sizeof(tmpPut.szStructName), "%s%s", tmpPut.szPrefix, tmpPut.szFieldName);
				_snprintf(tmpPut.szCode, sizeof(tmpPut.szCode), "iRes = CDB_QueryResult::Get_DateTime(pItem, \"%s\", iRow, %s%s)", 
					      tmpPut.szFieldName, pszInstName, tmpPut.szStructName);
				break;
			}
		}

		vecAutoOutput.push_back(tmpPut);
	}

	return 0;
}

