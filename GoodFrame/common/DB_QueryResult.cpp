#include "DB_QueryResult.h"

CDB_QueryResult::CDB_QueryResult()
{
	m_RowsNum = INVALID_ROW;
	m_ColsNum = INVALID_COL;

	m_FieldName.clear();
	m_Items.clear();
}

CDB_QueryResult::~CDB_QueryResult()
{
	// �ͷ��ֶ���
	m_FieldName.swap(FIELD_VEC());
	m_FieldName.clear();

	// �ͷ��ֶ�ֵ
	for (m_Iter=m_Items.begin();m_Iter!=m_Items.end();)
	{
		FIELD_INFO *pField = m_Iter->second;
		m_Items.erase(m_Iter++);

		if (pField->uDataLen && pField->pData)
			SAFE_DELETE_ARRAY(pField->pData);

		SAFE_DELETE(pField);
	}

	m_Items.swap(ITEM_MAP());	// swap ��ʽ���ͷ� vector
	m_Items.clear();
}

// ���û�����ֶ�����
void CDB_QueryResult::SetFieldName(UINT colNum, char* pszName)
{
	if (colNum>=m_FieldName.size())	// ����ֶ�����
		m_FieldName.push_back(pszName);	
	else							// �����ֶ�����
		m_FieldName[colNum] = pszName;
}

// �����ֶ�����ֵ����ֶ�����
int CDB_QueryResult::GetFieldName(UINT colIdx, string* pName)
{
	if (colIdx>=m_FieldName.size())
		return 10;	// ����ʧ��

	*pName = m_FieldName.at(colIdx);

	return 0;
}

// ����е�����ֵ
UINT CDB_QueryResult::GetFieldIdx(char* pszColName)
{
	// �ֶ��������ִ�Сд
	// Cool.Cat@2013-03-12
	//FIELD_VEC_ITER iter =  ::find(m_FieldName.begin(),m_FieldName.end(), pszColName);
	FIELD_VEC_ITER iter =  find_if(m_FieldName.begin(),m_FieldName.end(), Compare(pszColName));
	if (iter!=m_FieldName.end())
		return (UINT)(iter - m_FieldName.begin());

	return INVALID_FIELD_ID;
}

// ����һ���ֶ�ֵ
int CDB_QueryResult::AddFieldValue(ULONGLONG rowIdx, FIELD_INFO *pField)
{
	if(!pField)
		return 10;

	m_Items.insert(ITEM_MAP::value_type(rowIdx, pField));

	return 0;
}

// ���ָ���ֶε���Ϣ
FIELD_INFO* CDB_QueryResult::GetFieldValue(ULONGLONG rowIdx, UINT colIdx)
{
	m_Range = m_Items.equal_range(rowIdx);

	for (m_Iter = m_Range.first;m_Iter!=m_Range.second;m_Iter++)
	{
		if (m_Iter->second->uColId == colIdx)
		{
			FIELD_INFO* pFieldInfo = m_Iter->second;
			assert(pFieldInfo);
			return pFieldInfo;
		}
	}

	assert(FALSE);	// δ�ҵ���صļ�¼
	return 0;
}

// ���ָ���ֶε���Ϣ
FIELD_INFO* CDB_QueryResult::GetFieldValue(ULONGLONG rowIdx, char* pszColName)
{
	UINT uId = GetFieldIdx(pszColName);
	if(INVALID_FIELD_ID==uId)
	{
		assert(FALSE);
		return NULL;
	}

	return GetFieldValue(rowIdx, uId);
}

// �����ֶ���Ϣ��� INT ֵ���� windwos ϵͳ�У�����32λϵͳ����64λϵͳ��INT ���ȶ���4���ֽ�
int CDB_QueryResult::Get_INT(CDB_QueryResult *pItem, char* pszFieldName, int iRow, INT& fieldValue)
{
	if(!pItem)
		return 10;	// pItem �ǿ�ֵ

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// �ֶ����ƿ��ܴ���

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_LONGLONG:	// �洢����������һЩ��ѯ�� INT ǿת�� LONGLONG����ɲ����ݣ��˴������д���
		{
			fieldValue = (INT)(_atoi64((char*)pFieldInfo->pData));
			return 0;
		}

	case MYSQL_TYPE_TINY:
	case MYSQL_TYPE_SHORT:
	case MYSQL_TYPE_LONG:
		{
			fieldValue = atoi((char*)pFieldInfo->pData);
			return 0;
		}
	}

	printf("�ֶ� %s �����ʹ��� \n", pszFieldName);
	assert(FALSE);			
	return 50;	// ���Ͳ���ȷ
}

// �����ֶ���Ϣ��� LONGLONG ֵ
int CDB_QueryResult::Get_LONGLONG(CDB_QueryResult *pItem, char* pszFieldName, int iRow, LONGLONG& fieldValue)
{
	if(!pItem)
		return 10;	// pItem �ǿ�ֵ

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// �ֶ����ƿ��ܴ���

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_LONGLONG:
	case MYSQL_TYPE_INT24:
		{
			fieldValue = (LONGLONG)(_atoi64((char*)pFieldInfo->pData));
			return 0;
		}
	}

	printf("�ֶ� %s �����ʹ��� \n", pszFieldName);
	assert(FALSE);			
	return 50;	// ���Ͳ���ȷ
}

// �����ֶ���Ϣ��� float ֵ
int CDB_QueryResult::Get_float(CDB_QueryResult *pItem, char* pszFieldName, int iRow, float& fieldValue)
{
	if(!pItem)
		return 10;	// pItem �ǿ�ֵ

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// �ֶ����ƿ��ܴ���

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_FLOAT:
		{
			fieldValue = atof((char*)pFieldInfo->pData);
			return 0;
		}
	}

	printf("�ֶ� %s �����ʹ��� \n", pszFieldName);
	assert(FALSE);			
	return 50;	// ���Ͳ���ȷ
}

// �����ֶ���Ϣ��� double ֵ
int CDB_QueryResult::Get_double(CDB_QueryResult *pItem, char* pszFieldName, int iRow, double& fieldValue)
{
	if(!pItem)
		return 10;	// pItem �ǿ�ֵ

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// �ֶ����ƿ��ܴ���

	_CRT_DOUBLE dblval; 

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_DOUBLE:
		{
			int iRes = _atodbl(&dblval, (char*)pFieldInfo->pData);
			if(0==iRes)
			{
				fieldValue = dblval.x;
				return 0;
			}
			else
			{
				assert(FALSE);
				return 30;		// _atodbl ת��ʧ��
			}
		}
	}

	printf("�ֶ� %s �����ʹ��� \n", pszFieldName);
	assert(FALSE);			
	return 50;	// ���Ͳ���ȷ
}

// �����ֶ���Ϣ��� String ֵ��
int CDB_QueryResult::Get_string(CDB_QueryResult *pItem, char* pszFieldName, int iRow, string& fieldValue)
{
	if(!pItem)
		return 10;	// pItem �ǿ�ֵ

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// �ֶ����ƿ��ܴ���

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_VARCHAR:
	case MYSQL_TYPE_VAR_STRING:
	case MYSQL_TYPE_STRING:
		{
			fieldValue = (char*)pFieldInfo->pData;
			return 0;
		}
	}

	printf("�ֶ� %s �����ʹ��� \n", pszFieldName);
	assert(FALSE);			
	return 50;	// ���Ͳ���ȷ
}

// �����ֶ���Ϣ��� char ֵ��
int CDB_QueryResult::Get_Char(CDB_QueryResult *pItem, char* pszFieldName, int iRow, char* fieldValue, int iFieldMaxLen)
{
	int iRes = 0;
	string strResult;

	iRes = Get_string(pItem, pszFieldName, iRow, strResult);
	if(0==iRes)
	{
		if(strResult.length()>iFieldMaxLen)
		{
			memcpy_s(fieldValue, iFieldMaxLen-2, strResult.c_str(), iFieldMaxLen-2);
			fieldValue[iFieldMaxLen-1] = 0;

			return 70;	// Խ�������ֶ����ݳ��� iFieldLen ��
		}

		_snprintf(fieldValue, iFieldMaxLen, "%s", strResult.c_str());
	}

	return iRes;
}

// �����ֶ���Ϣ��ö����Ƶ�ֵ
// ��ע��MySQL �н� binary ��Ϊ MYSQL_TYPE_STRING ���ͣ��� varbinary ��Ϊ MYSQL_TYPE_VAR_STRING ���͡�
int CDB_QueryResult::Get_Binary(CDB_QueryResult *pItem, char* pszFieldName, int iRow, BYTE*& pData, int& iDataLen)
{
	if(!pItem)
		return 10;	// pItem �ǿ�ֵ

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// �ֶ����ƿ��ܴ���

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_VAR_STRING:
	case MYSQL_TYPE_STRING:
		{
			pData = (BYTE*)pFieldInfo->pData;
			iDataLen = pFieldInfo->uDataLen;
			return 0;	// ��������
		}
	}

	printf("�ֶ� %s �����ʹ��� \n", pszFieldName);
	assert(FALSE);			
	return 50;	// ���Ͳ���ȷ
}

// �����ֶ���Ϣ��û��ʱ��
int CDB_QueryResult::Get_DateTime(CDB_QueryResult *pItem, char* pszFieldName, int iRow, EASY_DATA_TIME& easyDataTime)
{
	if(!pItem)
		return 10;	// pItem �ǿ�ֵ

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// �ֶ����ƿ��ܴ���

	char szDateTime[32];
	memset(szDateTime, 0, sizeof(szDateTime));
	memcpy(szDateTime, (char*)pFieldInfo->pData, pFieldInfo->uDataLen);

	char* pPos = szDateTime;
	char  szTmp[12] = {0};
	memset(szTmp, 0, sizeof(szTmp));

	switch(pFieldInfo->fieldType)
	{
		case MYSQL_TYPE_YEAR:
			{
				easyDataTime.iYear = atoi(szDateTime);
				return 0;
			}
		case MYSQL_TYPE_DATE:	//���� "2013-03-15"
			{
				// ȡֵ 2013
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 4);
				easyDataTime.iYear = atoi(szTmp);

				// ȡֵ  03
				pPos += 5;
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iMon = atoi(szTmp);

				// ȡֵ 15
				pPos += 3;
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iDay = atoi(szTmp);

				return 0;
			}
		case MYSQL_TYPE_TIME:	// ���� "10:35:56"
			{
				// ȡֵ 10
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iHour = atoi(szTmp);

				// ȡֵ  35
				pPos += 3;
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iMin = atoi(szTmp);

				// ȡֵ 56
				pPos += 3;
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iSec = atoi(szTmp);

				return 0;
			}
		case MYSQL_TYPE_TIMESTAMP:	// ���� 2013-02-27 16:26:09
		case MYSQL_TYPE_DATETIME:	// ���� 2013-03-04 17:42:27
		{
			

			// ȡֵ 2013
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 4);
			easyDataTime.iYear = atoi(szTmp);

			// ȡֵ  03
			pPos += 5;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iMon = atoi(szTmp);

			// ȡֵ 15
			pPos += 3;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iDay = atoi(szTmp);


			//////////////////////////////////
			// ȡֵ 17
			pPos += 3;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iHour = atoi(szTmp);

			// ȡֵ  42
			pPos += 3;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iMin = atoi(szTmp);

			// ȡֵ 27
			pPos += 3;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iSec = atoi(szTmp);

			return 0;
		}
	}

	printf("�ֶ� %s �����ʹ��� \n", pszFieldName);
	assert(FALSE);			
	return 50;	// ���Ͳ���ȷ
}

// �����ֶ���Ϣ��� BLOB ֵ��
// ��δ��......����Ҫ�˽� MYSQL_BIND �ȣ�
// http://blog.csdn.net/charlie_2010/article/details/6147259
int CDB_QueryResult::Get_BLOB(CDB_QueryResult *pItem, char* pszFieldName, int iRow, BYTE*& pData, int& iDataLen)
{
	if(!pItem)
		return 10;	// pItem �ǿ�ֵ

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// �ֶ����ƿ��ܴ���

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_TINY_BLOB:
	case MYSQL_TYPE_MEDIUM_BLOB:
	case MYSQL_TYPE_LONG_BLOB:
	case MYSQL_TYPE_BLOB:
		{
			// ������BLOB �ֶεĶ�ȡ��д�� ???

			return 0;	// ��������
		}
	}

	printf("�ֶ� %s �����ʹ��� \n", pszFieldName);
	assert(FALSE);			
	return 50;	// ���Ͳ���ȷ
}


/*
MYSQL_TYPE_DECIMAL, 
MYSQL_TYPE_NULL,   
MYSQL_TYPE_TIMESTAMP,
MYSQL_TYPE_NEWDATE, 
MYSQL_TYPE_BIT,         Ҫ���� ??? 
MYSQL_TYPE_NEWDECIMAL=246,
MYSQL_TYPE_ENUM=247,
MYSQL_TYPE_SET=248,
MYSQL_TYPE_GEOMETRY=255
*/
