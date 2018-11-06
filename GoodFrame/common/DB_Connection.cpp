
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

// ���������
void CDB_Connection::ParseResult(CDB_QueryResult *pResult,MYSQL_RES *pRes)
{
	if (!pResult || !pRes)
		return;

	// ����
	ULONGLONG rows = m_stTunnel.mysql_num_rows(pRes);

	// ����
	UINT cols = m_stTunnel.mysql_num_fields(pRes);

	pResult->SetRowsNum(rows);
	pResult->SetColsNum(cols);

	enum_field_types t_type = MYSQL_TYPE_NULL;

	// ����
	MYSQL_FIELD *fields = 0;
	for(int i = 0; fields = mysql_fetch_field(pRes);++i)
		pResult->SetFieldName(i,fields->name);	// �������


	for (ULONGLONG i=0;i<rows;i++)	// �������е���
	{
		MYSQL_ROW row = m_stTunnel.mysql_fetch_row(pRes);	// �������������һ��
		if (!row)
			break;

		unsigned long *pLen = m_stTunnel.mysql_fetch_lengths(pRes);	// ���ؽ�����ڵ�ǰ�е��еĳ��ȣ����е�������ʽ����

		// ���ڽ��������������MYSQL_FIELD�ṹ�����顣ÿ���ṹ�ṩ�˽������1�е��ֶζ��塣
		// ����ֵ�����ڽ���������е�MYSQL_FIELD�ṹ�����顣
		MYSQL_FIELD *fields = m_stTunnel.mysql_fetch_fields(pRes);

		for (UINT j=0;j<cols;j++)	// �������е���
		{
			FIELD_INFO *pField = new FIELD_INFO();
			pField->uColId = j;

			// �ֶ�������ʱδ�õ������Ժ����
			// Cool.Cat@2013-02-18
			pField->fieldType = fields[j].type;

			// �ֶ�ֵ��MYSQL_ROW��
			pField->uDataLen = pLen[j];
			pField->pData = new BYTE[pField->uDataLen+1];
			memcpy(pField->pData,row[j],pField->uDataLen);
			pField->pData[pField->uDataLen] = 0;	// ���һ���ַ���Ϊ0ֵ

			pResult->AddFieldValue(i,pField);

			#if 0	// ���β�����
				BOOL bIsNum = IS_NUM(fields->type);	// �Ƿ��������ͣ����ƺ�����ѽ??? �ִ�ֵ��Ҳ�� 1
				BOOL bIsLongData = IS_LONGDATA(fields->type);	// �Ƿ������MYSQL_TYPE_TINY_BLOB �� MYSQL_TYPE_STRING�������ƺ�����ѽ??? ����ʲôֵ���� 0
				int  iMaxLength = fields->max_length;		// ���ƺ�����ѽ??? ����ʲôֵ���� 1

				int iTmp = 0;
			#endif
		}
	}
}

// ����
BOOL CDB_Connection::DoConnect()
{
	CThreadGuard guard(&m_lock);

	if (IsConnected())
		return m_bIsConnected;

	if (!m_stTunnel.mysql_init())
		goto error;

	// �����ַ���
	if (m_strCharset.length())
		m_stTunnel.mysql_options(MYSQL_SET_CHARSET_NAME,m_strCharset.c_str());

	// ���ö�������
	if (m_bReconnect)
		m_stTunnel.mysql_options(MYSQL_OPT_RECONNECT,"true");

	// ����Session��ʱ
	if (m_uTimeout)
	{
		char timeoutStr[MAX_PATH] = {0};
		_snprintf(timeoutStr,MAX_PATH-1,"/*!40101 set @@session.wait_timeout=%d */",m_uTimeout);
		m_stTunnel.mysql_options(MYSQL_INIT_COMMAND,timeoutStr);
	}

	// ����MySQL(�������������)
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

// ����ǰ�Ĳ���
void CDB_Connection::Destroy()
{
	CThreadGuard guard(&m_lock);

	if (IsConnected())
	{
		// �ͷ�MySQL������Դ
		m_stTunnel.mysql_close();
		m_bIsConnected = FALSE;
		printf("[%s]�����ͷ�[0x%08X]...\n",
			__FUNCTION__,
			this);
	}
}

/* --------------------------------------------------------------------------
����˵����ͬ��ִ�в�ѯ��䣬û�н�����Ĳ�ѯ���� Insert��Update��Delete �����Ͳ�����������
���������
	query	��ѯ���
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10	�Ѿ��Ͽ�������
		20	mysql_real_query ʧ��
		30	��Ȼ�н������Ӧ��ʹ�� DoQuery_SingleRes �� DoQuery_MultiRes ����
--------------------------------------------------------------------------*/
int CDB_Connection::DoQuery_NoRes(char* pszQuery, int iLen)
{
	CThreadGuard guard(&m_lock);

	if (!IsConnected())
		return 10;		// �Ѿ��Ͽ�������

	// �����ѯ�ɹ�������0��������ִ��󣬷��ط�0ֵ
	int iRes = m_stTunnel.mysql_real_query(pszQuery, iLen);
	if (0 != iRes)
	{
		printf("[%s]err[%s]\n", __FUNCTION__, m_stTunnel.mysql_error().c_str());
		return 20;	// mysql_real_query ʧ��
	}

	MYSQL_RES *res = m_stTunnel.mysql_store_result();
	if(res)
		return 30;	// ��Ȼ�н������Ӧ��ʹ�� DoQuery_SingleRes �� DoQuery_MultiRes ����

	return 0;
}

/* --------------------------------------------------------------------------
����˵����ͬ��ִ�в�ѯ��䣬��һ�������
���������
	strQuery	��ѯ���
����������
	queryResult     ��ѯ���
	MYSQL_MULTI_RES	�����ѯ�����
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10	�Ѿ��Ͽ�������
		20	mysql_real_query ʧ��
		50	�޽������Ӧ���� DoQuery_NoRes ����
		80  �����˶�������Ӧ���� DoQuery_MultiRes ����
--------------------------------------------------------------------------*/
int CDB_Connection::DoQuery_SingleRes(char* pszQuery, int iLen, CDB_QueryResult *pResult)
{
	CThreadGuard guard(&m_lock);

	if (!IsConnected())
		return 10;		// �Ѿ��Ͽ�������

	// �����ѯ�ɹ�������0��������ִ��󣬷��ط�0ֵ
	int iRes = m_stTunnel.mysql_real_query(pszQuery, iLen);
	if (0 != iRes)
	{
		printf("[%s]err[%s]\n", __FUNCTION__, m_stTunnel.mysql_error().c_str());
		return 20;	// mysql_real_query ʧ��
	}

	MYSQL_RES *res = m_stTunnel.mysql_store_result();

	if (!res)	// �޽���������� Insert��Update��Delete
	{
		return 50;	// �޽������Ӧ���� DoQuery_NoRes ����
	}

	ParseResult(pResult, res);	// ���������

	m_stTunnel.mysql_free_result(res);	

	int nextResult = m_stTunnel.mysql_next_result();	// ��һ�������
	if (nextResult==-1)	// -1 ��ʾ�޽����������ȷ�ġ�
		return 0;

	if (0!=nextResult)	// ��һ��Ȳ�����-1����һ���ֲ�����0����ʾ���н����
	{
		return 80;  // �����˶�������Ӧ���� DoQuery_MultiRes ����
	}

	res = m_stTunnel.mysql_store_result();
	if (0 != res)	// ��һ��������ǿգ���ʾ�ж�������
	{
		return 80;  // �����˶�������Ӧ���� DoQuery_MultiRes ����
	}

	// ��һ��������ǿգ�����ȷ��
	return 0;
}

/* --------------------------------------------------------------------------
����˵����ͬ��ִ�в�ѯ��䣬��������
���������
	strQuery	��ѯ���
����������
	queryResult     ��ѯ���
	MYSQL_MULTI_RES	�����ѯ�����
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10	�Ѿ��Ͽ�������
		20	mysql_real_query ʧ��
		40  �޽��������û��Ӱ��������������
--------------------------------------------------------------------------*/
int CDB_Connection::DoQuery_MultiRes(char* pszQuery, int iLen, MYSQL_MULTI_RES* pMultiRes)
{
	CThreadGuard guard(&m_lock);

	if (!IsConnected())
		return 10;		// �Ѿ��Ͽ�������

	// �����ѯ�ɹ�������0��������ִ��󣬷��ط�0ֵ
	int iRes = m_stTunnel.mysql_real_query(pszQuery, iLen);
	if (0 != iRes)
	{
		printf("[%s]err[%s]\n", __FUNCTION__, m_stTunnel.mysql_error().c_str());
		return 20;	// mysql_real_query ʧ��
	}

	// ���� Insert��Update��Delete�޷��أ����Խ������Ϊ��
	// ���Ҫ��mysql_affected_rows()����ȡӰ�������
	MYSQL_RES *res = m_stTunnel.mysql_store_result();

	if (!res)	// �޽���������� Insert��Update��Delete
	{
		// ���ر����µ�UPDATE��DELETE��INSERT��ѯӰ���������
		ULONGLONG affected_rows = m_stTunnel.mysql_affected_rows();

		if (affected_rows)	// Ӱ�������������� Insert��Update��Delete
		{
			CDB_QueryResult *pResult = new CDB_QueryResult();
			pResult->SetRowsNum(1);
			pMultiRes->push_back(pResult);
		
			return 0;	// �ɹ���
		}

		// �޽��������û��Ӱ��������Ӧ���ǳ����ˡ�����
		printf("[%s]DoQuery.Err[%s]\n",
			__FUNCTION__,
			m_stTunnel.mysql_error().c_str());

		return 40;	// �޽��������û��Ӱ��������������
	}

	CDB_QueryResult *pResult = new CDB_QueryResult();
	ParseResult(pResult,res);
	pMultiRes->push_back(pResult);
	m_stTunnel.mysql_free_result(res);	

	// ���ܷ����ж�������
	while (TRUE)
	{
		int nextResult = m_stTunnel.mysql_next_result();	// ��һ�������
		if (nextResult==-1)
			break;
		if (nextResult!=0)
		{
			printf("[%s]DoQuery.Err[%s]\n",
				__FUNCTION__,
				m_stTunnel.mysql_error().c_str());
			break;
		}

		// ��������
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

// ����ֶθ�ʽ���ļ�
int CDB_Connection::OutputField(char* pszTableName, char* pszInstName, vector<FIELD_AUTO_OUTPUT>& vecAutoOutput)
{
	CThreadGuard guard(&m_lock);

	if (!IsConnected())
		return 10;		// �Ѿ��Ͽ�������

	if(!pszInstName)
		return 20;	// ʵ����������ָ�룩��Ϊ��

	string strTmp = "select * from ";
	string strQuery = strTmp + pszTableName;

	// �����ѯ�ɹ�������0��������ִ��󣬷��ط�0ֵ
	int iRes = m_stTunnel.mysql_real_query(strQuery.c_str(), (int)strQuery.length());
	if (0 != iRes)
	{
		printf("[%s]err[%s]\n", __FUNCTION__, m_stTunnel.mysql_error().c_str());
		return 20;	// mysql_real_query ʧ��
	}

	MYSQL_RES *pRes = m_stTunnel.mysql_store_result();

	if (!pRes)	// �޽���������� Insert��Update��Delete
	{
		return 50;	// �޽������Ӧ���� DoQuery_NoRes ����
	}

	ULONGLONG rows = m_stTunnel.mysql_num_rows(pRes);	// ����
	UINT cols = m_stTunnel.mysql_num_fields(pRes);	// ����

	enum_field_types t_type = MYSQL_TYPE_NULL;

	MYSQL_FIELD *fields = 0;	// ����
	for(int i = 0; fields = mysql_fetch_field(pRes);++i)	// ����ÿһ���ֶ�
	{
		FIELD_AUTO_OUTPUT tmpPut;

		_snprintf(tmpPut.szFieldName, sizeof(tmpPut.szFieldName), "%s", fields->name);
		tmpPut.iType = fields->type;

		switch(tmpPut.iType)	// �������͸�ֵǰ׺
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
		case MYSQL_TYPE_TIMESTAMP:	// ���� 2013-02-27 16:26:09
		case MYSQL_TYPE_DATETIME:	// ���� 2013-03-04 17:42:27
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

