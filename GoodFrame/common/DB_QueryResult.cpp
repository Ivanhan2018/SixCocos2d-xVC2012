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
	// 释放字段名
	m_FieldName.swap(FIELD_VEC());
	m_FieldName.clear();

	// 释放字段值
	for (m_Iter=m_Items.begin();m_Iter!=m_Items.end();)
	{
		FIELD_INFO *pField = m_Iter->second;
		m_Items.erase(m_Iter++);

		if (pField->uDataLen && pField->pData)
			SAFE_DELETE_ARRAY(pField->pData);

		SAFE_DELETE(pField);
	}

	m_Items.swap(ITEM_MAP());	// swap 方式的释放 vector
	m_Items.clear();
}

// 设置或添加字段名称
void CDB_QueryResult::SetFieldName(UINT colNum, char* pszName)
{
	if (colNum>=m_FieldName.size())	// 添加字段名称
		m_FieldName.push_back(pszName);	
	else							// 设置字段名称
		m_FieldName[colNum] = pszName;
}

// 根据字段索引值获得字段名称
int CDB_QueryResult::GetFieldName(UINT colIdx, string* pName)
{
	if (colIdx>=m_FieldName.size())
		return 10;	// 索引失败

	*pName = m_FieldName.at(colIdx);

	return 0;
}

// 获得列的索引值
UINT CDB_QueryResult::GetFieldIdx(char* pszColName)
{
	// 字段名不区分大小写
	// Cool.Cat@2013-03-12
	//FIELD_VEC_ITER iter =  ::find(m_FieldName.begin(),m_FieldName.end(), pszColName);
	FIELD_VEC_ITER iter =  find_if(m_FieldName.begin(),m_FieldName.end(), Compare(pszColName));
	if (iter!=m_FieldName.end())
		return (UINT)(iter - m_FieldName.begin());

	return INVALID_FIELD_ID;
}

// 增加一个字段值
int CDB_QueryResult::AddFieldValue(ULONGLONG rowIdx, FIELD_INFO *pField)
{
	if(!pField)
		return 10;

	m_Items.insert(ITEM_MAP::value_type(rowIdx, pField));

	return 0;
}

// 获得指定字段的信息
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

	assert(FALSE);	// 未找到相关的记录
	return 0;
}

// 获得指定字段的信息
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

// 根据字段信息获得 INT 值，在 windwos 系统中，无论32位系统还是64位系统，INT 长度都是4个字节
int CDB_QueryResult::Get_INT(CDB_QueryResult *pItem, char* pszFieldName, int iRow, INT& fieldValue)
{
	if(!pItem)
		return 10;	// pItem 是空值

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// 字段名称可能错误

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_LONGLONG:	// 存储过程里面会把一些查询的 INT 强转成 LONGLONG，造成不兼容，此处作折中处理
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

	printf("字段 %s 的类型错误 \n", pszFieldName);
	assert(FALSE);			
	return 50;	// 类型不正确
}

// 根据字段信息获得 LONGLONG 值
int CDB_QueryResult::Get_LONGLONG(CDB_QueryResult *pItem, char* pszFieldName, int iRow, LONGLONG& fieldValue)
{
	if(!pItem)
		return 10;	// pItem 是空值

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// 字段名称可能错误

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_LONGLONG:
	case MYSQL_TYPE_INT24:
		{
			fieldValue = (LONGLONG)(_atoi64((char*)pFieldInfo->pData));
			return 0;
		}
	}

	printf("字段 %s 的类型错误 \n", pszFieldName);
	assert(FALSE);			
	return 50;	// 类型不正确
}

// 根据字段信息获得 float 值
int CDB_QueryResult::Get_float(CDB_QueryResult *pItem, char* pszFieldName, int iRow, float& fieldValue)
{
	if(!pItem)
		return 10;	// pItem 是空值

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// 字段名称可能错误

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_FLOAT:
		{
			fieldValue = atof((char*)pFieldInfo->pData);
			return 0;
		}
	}

	printf("字段 %s 的类型错误 \n", pszFieldName);
	assert(FALSE);			
	return 50;	// 类型不正确
}

// 根据字段信息获得 double 值
int CDB_QueryResult::Get_double(CDB_QueryResult *pItem, char* pszFieldName, int iRow, double& fieldValue)
{
	if(!pItem)
		return 10;	// pItem 是空值

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// 字段名称可能错误

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
				return 30;		// _atodbl 转换失败
			}
		}
	}

	printf("字段 %s 的类型错误 \n", pszFieldName);
	assert(FALSE);			
	return 50;	// 类型不正确
}

// 根据字段信息获得 String 值，
int CDB_QueryResult::Get_string(CDB_QueryResult *pItem, char* pszFieldName, int iRow, string& fieldValue)
{
	if(!pItem)
		return 10;	// pItem 是空值

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// 字段名称可能错误

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

	printf("字段 %s 的类型错误 \n", pszFieldName);
	assert(FALSE);			
	return 50;	// 类型不正确
}

// 根据字段信息获得 char 值，
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

			return 70;	// 越界啦，字段内容超过 iFieldLen 啦
		}

		_snprintf(fieldValue, iFieldMaxLen, "%s", strResult.c_str());
	}

	return iRes;
}

// 根据字段信息获得二进制的值
// 备注：MySQL 中将 binary 视为 MYSQL_TYPE_STRING 类型，将 varbinary 视为 MYSQL_TYPE_VAR_STRING 类型。
int CDB_QueryResult::Get_Binary(CDB_QueryResult *pItem, char* pszFieldName, int iRow, BYTE*& pData, int& iDataLen)
{
	if(!pItem)
		return 10;	// pItem 是空值

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// 字段名称可能错误

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_VAR_STRING:
	case MYSQL_TYPE_STRING:
		{
			pData = (BYTE*)pFieldInfo->pData;
			iDataLen = pFieldInfo->uDataLen;
			return 0;	// 正常返回
		}
	}

	printf("字段 %s 的类型错误 \n", pszFieldName);
	assert(FALSE);			
	return 50;	// 类型不正确
}

// 根据字段信息获得获得时间
int CDB_QueryResult::Get_DateTime(CDB_QueryResult *pItem, char* pszFieldName, int iRow, EASY_DATA_TIME& easyDataTime)
{
	if(!pItem)
		return 10;	// pItem 是空值

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// 字段名称可能错误

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
		case MYSQL_TYPE_DATE:	//例句 "2013-03-15"
			{
				// 取值 2013
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 4);
				easyDataTime.iYear = atoi(szTmp);

				// 取值  03
				pPos += 5;
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iMon = atoi(szTmp);

				// 取值 15
				pPos += 3;
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iDay = atoi(szTmp);

				return 0;
			}
		case MYSQL_TYPE_TIME:	// 例句 "10:35:56"
			{
				// 取值 10
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iHour = atoi(szTmp);

				// 取值  35
				pPos += 3;
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iMin = atoi(szTmp);

				// 取值 56
				pPos += 3;
				memset(szTmp, 0, sizeof(szTmp));
				memcpy(szTmp, pPos, 2);
				easyDataTime.iSec = atoi(szTmp);

				return 0;
			}
		case MYSQL_TYPE_TIMESTAMP:	// 例句 2013-02-27 16:26:09
		case MYSQL_TYPE_DATETIME:	// 例句 2013-03-04 17:42:27
		{
			

			// 取值 2013
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 4);
			easyDataTime.iYear = atoi(szTmp);

			// 取值  03
			pPos += 5;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iMon = atoi(szTmp);

			// 取值 15
			pPos += 3;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iDay = atoi(szTmp);


			//////////////////////////////////
			// 取值 17
			pPos += 3;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iHour = atoi(szTmp);

			// 取值  42
			pPos += 3;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iMin = atoi(szTmp);

			// 取值 27
			pPos += 3;
			memset(szTmp, 0, sizeof(szTmp));
			memcpy(szTmp, pPos, 2);
			easyDataTime.iSec = atoi(szTmp);

			return 0;
		}
	}

	printf("字段 %s 的类型错误 \n", pszFieldName);
	assert(FALSE);			
	return 50;	// 类型不正确
}

// 根据字段信息获得 BLOB 值，
// 还未做......，需要了解 MYSQL_BIND 等，
// http://blog.csdn.net/charlie_2010/article/details/6147259
int CDB_QueryResult::Get_BLOB(CDB_QueryResult *pItem, char* pszFieldName, int iRow, BYTE*& pData, int& iDataLen)
{
	if(!pItem)
		return 10;	// pItem 是空值

	FIELD_INFO* pFieldInfo = NULL;
	pFieldInfo = pItem->GetFieldValue(iRow, pszFieldName);
	if(!pszFieldName)
		return 20;	// 字段名称可能错误

	switch(pFieldInfo->fieldType)
	{
	case MYSQL_TYPE_TINY_BLOB:
	case MYSQL_TYPE_MEDIUM_BLOB:
	case MYSQL_TYPE_LONG_BLOB:
	case MYSQL_TYPE_BLOB:
		{
			// 待做：BLOB 字段的读取与写入 ???

			return 0;	// 正常返回
		}
	}

	printf("字段 %s 的类型错误 \n", pszFieldName);
	assert(FALSE);			
	return 50;	// 类型不正确
}


/*
MYSQL_TYPE_DECIMAL, 
MYSQL_TYPE_NULL,   
MYSQL_TYPE_TIMESTAMP,
MYSQL_TYPE_NEWDATE, 
MYSQL_TYPE_BIT,         要做不 ??? 
MYSQL_TYPE_NEWDECIMAL=246,
MYSQL_TYPE_ENUM=247,
MYSQL_TYPE_SET=248,
MYSQL_TYPE_GEOMETRY=255
*/
