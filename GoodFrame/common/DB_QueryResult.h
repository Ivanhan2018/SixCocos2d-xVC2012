/********************************************************************
	created:	2013/02/26
	created:	26:2:2013   15:29
	filename: 	E:\SVN_2013\GoodFrame\common\DB_QueryResult.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	DB_QueryResult
	file ext:	h
	author:		曹雪垠提供源码，侯国江添加、修改、整合 
	
	purpose:	由MYSQL_RES解析而来
*********************************************************************/

#ifndef DB_QUERY_RESULT
#define DB_QUERY_RESULT

#include <winsock.h>
#include <assert.h>

#include "../../MySQL5.5/include/mysql.h"

#include <DB_Head.h>
#include "./EasyDataTime.h"

//--- 结构、枚举区 -----------------------------------------
struct FIELD_INFO 
{
	FIELD_INFO()
	{
		uColId = uDataLen = 0;
		fieldType = MYSQL_TYPE_NULL;
		pData = 0;
		uDataLen = NULL;
	}

	UINT uColId;		// 列的序号
	enum_field_types fieldType;	// 列的类型
	UINT uDataLen;		// 真实内容长度
	BYTE *pData;		// 真实内容
};

class __declspec(dllexport) CDB_QueryResult
{
public:
	//class friend CDB_Connection;
	struct Compare
	{
		Compare(char *colName)
		{
			pszColName = colName;
		}

		bool operator()(string& key)
		{
			return !_stricmp(pszColName.c_str(),key.c_str());
		}
	private:
		string pszColName;
	};
public:
	CDB_QueryResult();
	~CDB_QueryResult();

public:	//--- 常用函数--------------------------------------------------------------------------

	// 获得字段的列数
	unsigned int GetColsNum() const {return m_ColsNum;}

	// 设置字段的列数
	void SetColsNum(UINT cols){m_ColsNum = cols;}

	// 设置结果集的行数
	void SetRowsNum(ULONGLONG rows){m_RowsNum = rows;}

	// 获得结果集的行数
	my_ulonglong GetRowsNum() const {return m_RowsNum;}

	/* --------------------------------------------------------------------------
	函数说明：设置或添加字段名称
	传入参数：
		colNum	新增的字段索引
		name	字段名称
	--------------------------------------------------------------------------*/
	void SetFieldName(UINT colNum, char* pszName);

	/* --------------------------------------------------------------------------
	函数说明：根据字段索引值获得字段名称
	传入参数：
		colIdx	字段索引值
	传出参数：
		strName	字段名称
	返回值：
		成功则返回 TRUE，否则返回 FALSE 。
	--------------------------------------------------------------------------*/
	int GetFieldName(UINT colIdx, string* pName);

	/* --------------------------------------------------------------------------
	函数说明：获得列的索引值
	传入参数：
		colName	字段名称
	返回值：
		成功则返回 索引值。
		若返回 INVALID_FIELD_ID 则表示无效的字段索引值 。
	--------------------------------------------------------------------------*/
	UINT GetFieldIdx(char* pszColName);

	/* --------------------------------------------------------------------------
	函数说明：增加一个字段值
	传入参数：
		rowIdx	结果集所在的行
		pField	字段的真实信息
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int AddFieldValue(ULONGLONG rowIdx, FIELD_INFO *pField);

	/* --------------------------------------------------------------------------
	函数说明：获得指定字段的信息
	传入参数：
		rowIdx	结果集所在的行
		colIdx	字段所在结果集的列
	返回值：
		成功则返回 FIELD_INFO* 指针值，
		失败返回0值。
	--------------------------------------------------------------------------*/
	FIELD_INFO* GetFieldValue(ULONGLONG rowIdx,UINT colIdx);

	/* --------------------------------------------------------------------------
	函数说明：获得指定字段的信息
	传入参数：
		rowIdx	结果集所在的行
		colName	字段名
	返回值：
		成功则返回 FIELD_INFO* 指针值，
		失败返回0值。
	--------------------------------------------------------------------------*/
	FIELD_INFO* GetFieldValue(ULONGLONG rowIdx, char* pszColName);

public:	//--- 根据字段信息获得各种类型的值------------------------------------------------------

	/* --------------------------------------------------------------------------
	函数说明：根据字段信息获得 INT 值，在 windwos 系统中，无论32位系统还是64位系统，INT 长度都是4个字节
	传入参数：
		pItem			结果集的指针
		pszFieldName	字段名
		iRow			第几行
	传出参数：
		fieldValue  字段值
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pItem 是空值
			20	字段名称可能错误
			50	类型不正确
	--------------------------------------------------------------------------*/
	static int Get_INT(CDB_QueryResult *pItem, char* pszFieldName, int iRow, INT& fieldValue);

	/* --------------------------------------------------------------------------
	函数说明：根根据字段信息获得 LONGLONG 值
	传入参数：
		pItem			结果集的指针
		pszFieldName	字段名
		iRow			第几行
	传出参数：
		fieldValue  字段值
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pItem 是空值
			20	字段名称可能错误
			50	类型不正确
	--------------------------------------------------------------------------*/
	static int Get_LONGLONG(CDB_QueryResult *pItem, char* pszFieldName, int iRow, LONGLONG& fieldValue);

	/* --------------------------------------------------------------------------
	函数说明：根据字段信息获得 float 值
	传入参数：
		pItem			结果集的指针
		pszFieldName	字段名
		iRow			第几行
	传出参数：
		fieldValue  字段值
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pItem 是空值
			20	字段名称可能错误
			50	类型不正确
	--------------------------------------------------------------------------*/
	static int Get_float(CDB_QueryResult *pItem, char* pszFieldName, int iRow, float& fieldValue);

	/* --------------------------------------------------------------------------
	函数说明：根据字段信息获得 double 值
	传入参数：
		pItem			结果集的指针
		pszFieldName	字段名
		iRow			第几行
	传出参数：
		fieldValue  字段值
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pItem 是空值
			20	字段名称可能错误
			50	类型不正确
	--------------------------------------------------------------------------*/
	static int Get_double(CDB_QueryResult *pItem, char* pszFieldName, int iRow, double& fieldValue);

	/* --------------------------------------------------------------------------
	函数说明：根据字段信息获得 String 值
	传入参数：
		pItem			结果集的指针
		pszFieldName	字段名
		iRow			第几行
	传出参数：
		fieldValue  字段值
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pItem 是空值
			20	字段名称可能错误
			50	类型不正确
	--------------------------------------------------------------------------*/
	static	int Get_string(CDB_QueryResult *pItem, char* pszFieldName, int iRow, string& fieldValue);
	
	/* --------------------------------------------------------------------------
	函数说明：根据字段信息获得 char 值
	传入参数：
		pItem			结果集的指针
		pszFieldName	字段名
		iRow			第几行
		iFieldMaxLen	传出的字段值（fieldValue）允许的最大长度
	传出参数：
		fieldValue  字段值
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pItem 是空值
			20	字段名称可能错误
			50	类型不正确
			70  越界啦，字段内容超过 iFieldLen 啦，但依然会给 fieldValue 赋长度为 iFieldMaxLen 以内的值
	--------------------------------------------------------------------------*/
	static int Get_Char(CDB_QueryResult *pItem, char* pszFieldName, int iRow, char* fieldValue, int iFieldMaxLen);

	/* --------------------------------------------------------------------------
	函数说明：根据字段信息获得二进制的值
	传入参数：
		pFieldInfo	字段信息
	传出参数：
		pData		二进制的值
		iDataLen	二进制的值的长度，以字节为单位
	返回值：
		成功则返回 0，失败返回错误码如下：
	备注：
	    MySQL 中将 binary 视为 MYSQL_TYPE_STRING 类型，将 varbinary 视为 MYSQL_TYPE_VAR_STRING 类型。
	--------------------------------------------------------------------------*/
	static int Get_Binary(CDB_QueryResult *pItem, char* pszFieldName, int iRow, BYTE*& pData, int& iDataLen);

	/* --------------------------------------------------------------------------
	函数说明：根据字段信息获得获得时间
	传入参数：
		pFieldInfo	字段信息
	传出参数：
		pSystemTime	字段内的时间信息
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	static int Get_DateTime(FIELD_INFO* pFieldInfo, EASY_DATA_TIME& easyDataTime);

	// 根据字段信息获得 BLOB 值，
	// 还未做......，需要了解 MYSQL_BIND 等，
	//// http://blog.csdn.net/charlie_2010/article/details/6147259
	static  int Get_DateTime(CDB_QueryResult *pItem, char* pszFieldName, int iRow, EASY_DATA_TIME& easyDataTime);

	static int Get_BLOB(CDB_QueryResult *pItem, char* pszFieldName, int iRow, BYTE*& pData, int& iDataLen);

protected:
	
	ULONGLONG	m_RowsNum;	// 行数
	
	UINT	m_ColsNum;	// 列数
	
	typedef std::vector<string> FIELD_VEC;	// 列名
	typedef FIELD_VEC::iterator FIELD_VEC_ITER;

	FIELD_VEC m_FieldName;

	// 行数、列信息
	typedef std::multimap<ULONGLONG, FIELD_INFO*> ITEM_MAP;
	typedef ITEM_MAP::iterator ITEM_ITER;
	typedef pair<ITEM_ITER,ITEM_ITER> RANGE_MAP;

	ITEM_MAP m_Items;
	ITEM_ITER m_Iter;
	RANGE_MAP m_Range;
};
//--- typedef 区 -----------------------------------------
typedef std::vector<CDB_QueryResult*> MYSQL_MULTI_RES;

//--- 类区 -----------------------------------------
class MySqlMultiResGuard	// 多结果集的守护
{
public:
	MySqlMultiResGuard()	{	pMultiRes = 0;	}

	~MySqlMultiResGuard()
	{
		if(!pMultiRes)
			return;

		// 释放多结果集
		for (int i=0; i<pMultiRes->size(); i++)
		{
			CDB_QueryResult *pItem = (CDB_QueryResult*)(pMultiRes->at(i));

			SAFE_DELETE(pItem);	// 注意：要释放
		}

		pMultiRes->swap(MYSQL_MULTI_RES());	// swap 方式的释放 vector
		pMultiRes->clear();
		pMultiRes = NULL;
	}

	// 获得多结果集的守护，返回0值表示正确
	int GetMultiRes(MYSQL_MULTI_RES*& pMultiRes)
	{
		pMultiRes = new MYSQL_MULTI_RES;
		if(!pMultiRes)
			return 10;
		return 0;
	}

private:
	MYSQL_MULTI_RES* pMultiRes;
};
#endif