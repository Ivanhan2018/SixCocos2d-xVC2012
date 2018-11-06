/********************************************************************
	created:	2013/02/26
	created:	26:2:2013   15:29
	filename: 	E:\SVN_2013\GoodFrame\common\DB_QueryResult.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	DB_QueryResult
	file ext:	h
	author:		��ѩ���ṩԴ�룬�������ӡ��޸ġ����� 
	
	purpose:	��MYSQL_RES��������
*********************************************************************/

#ifndef DB_QUERY_RESULT
#define DB_QUERY_RESULT

#include <winsock.h>
#include <assert.h>

#include "../../MySQL5.5/include/mysql.h"

#include <DB_Head.h>
#include "./EasyDataTime.h"

//--- �ṹ��ö���� -----------------------------------------
struct FIELD_INFO 
{
	FIELD_INFO()
	{
		uColId = uDataLen = 0;
		fieldType = MYSQL_TYPE_NULL;
		pData = 0;
		uDataLen = NULL;
	}

	UINT uColId;		// �е����
	enum_field_types fieldType;	// �е�����
	UINT uDataLen;		// ��ʵ���ݳ���
	BYTE *pData;		// ��ʵ����
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

public:	//--- ���ú���--------------------------------------------------------------------------

	// ����ֶε�����
	unsigned int GetColsNum() const {return m_ColsNum;}

	// �����ֶε�����
	void SetColsNum(UINT cols){m_ColsNum = cols;}

	// ���ý����������
	void SetRowsNum(ULONGLONG rows){m_RowsNum = rows;}

	// ��ý����������
	my_ulonglong GetRowsNum() const {return m_RowsNum;}

	/* --------------------------------------------------------------------------
	����˵�������û�����ֶ�����
	���������
		colNum	�������ֶ�����
		name	�ֶ�����
	--------------------------------------------------------------------------*/
	void SetFieldName(UINT colNum, char* pszName);

	/* --------------------------------------------------------------------------
	����˵���������ֶ�����ֵ����ֶ�����
	���������
		colIdx	�ֶ�����ֵ
	����������
		strName	�ֶ�����
	����ֵ��
		�ɹ��򷵻� TRUE�����򷵻� FALSE ��
	--------------------------------------------------------------------------*/
	int GetFieldName(UINT colIdx, string* pName);

	/* --------------------------------------------------------------------------
	����˵��������е�����ֵ
	���������
		colName	�ֶ�����
	����ֵ��
		�ɹ��򷵻� ����ֵ��
		������ INVALID_FIELD_ID ���ʾ��Ч���ֶ�����ֵ ��
	--------------------------------------------------------------------------*/
	UINT GetFieldIdx(char* pszColName);

	/* --------------------------------------------------------------------------
	����˵��������һ���ֶ�ֵ
	���������
		rowIdx	��������ڵ���
		pField	�ֶε���ʵ��Ϣ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	int AddFieldValue(ULONGLONG rowIdx, FIELD_INFO *pField);

	/* --------------------------------------------------------------------------
	����˵�������ָ���ֶε���Ϣ
	���������
		rowIdx	��������ڵ���
		colIdx	�ֶ����ڽ��������
	����ֵ��
		�ɹ��򷵻� FIELD_INFO* ָ��ֵ��
		ʧ�ܷ���0ֵ��
	--------------------------------------------------------------------------*/
	FIELD_INFO* GetFieldValue(ULONGLONG rowIdx,UINT colIdx);

	/* --------------------------------------------------------------------------
	����˵�������ָ���ֶε���Ϣ
	���������
		rowIdx	��������ڵ���
		colName	�ֶ���
	����ֵ��
		�ɹ��򷵻� FIELD_INFO* ָ��ֵ��
		ʧ�ܷ���0ֵ��
	--------------------------------------------------------------------------*/
	FIELD_INFO* GetFieldValue(ULONGLONG rowIdx, char* pszColName);

public:	//--- �����ֶ���Ϣ��ø������͵�ֵ------------------------------------------------------

	/* --------------------------------------------------------------------------
	����˵���������ֶ���Ϣ��� INT ֵ���� windwos ϵͳ�У�����32λϵͳ����64λϵͳ��INT ���ȶ���4���ֽ�
	���������
		pItem			�������ָ��
		pszFieldName	�ֶ���
		iRow			�ڼ���
	����������
		fieldValue  �ֶ�ֵ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pItem �ǿ�ֵ
			20	�ֶ����ƿ��ܴ���
			50	���Ͳ���ȷ
	--------------------------------------------------------------------------*/
	static int Get_INT(CDB_QueryResult *pItem, char* pszFieldName, int iRow, INT& fieldValue);

	/* --------------------------------------------------------------------------
	����˵�����������ֶ���Ϣ��� LONGLONG ֵ
	���������
		pItem			�������ָ��
		pszFieldName	�ֶ���
		iRow			�ڼ���
	����������
		fieldValue  �ֶ�ֵ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pItem �ǿ�ֵ
			20	�ֶ����ƿ��ܴ���
			50	���Ͳ���ȷ
	--------------------------------------------------------------------------*/
	static int Get_LONGLONG(CDB_QueryResult *pItem, char* pszFieldName, int iRow, LONGLONG& fieldValue);

	/* --------------------------------------------------------------------------
	����˵���������ֶ���Ϣ��� float ֵ
	���������
		pItem			�������ָ��
		pszFieldName	�ֶ���
		iRow			�ڼ���
	����������
		fieldValue  �ֶ�ֵ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pItem �ǿ�ֵ
			20	�ֶ����ƿ��ܴ���
			50	���Ͳ���ȷ
	--------------------------------------------------------------------------*/
	static int Get_float(CDB_QueryResult *pItem, char* pszFieldName, int iRow, float& fieldValue);

	/* --------------------------------------------------------------------------
	����˵���������ֶ���Ϣ��� double ֵ
	���������
		pItem			�������ָ��
		pszFieldName	�ֶ���
		iRow			�ڼ���
	����������
		fieldValue  �ֶ�ֵ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pItem �ǿ�ֵ
			20	�ֶ����ƿ��ܴ���
			50	���Ͳ���ȷ
	--------------------------------------------------------------------------*/
	static int Get_double(CDB_QueryResult *pItem, char* pszFieldName, int iRow, double& fieldValue);

	/* --------------------------------------------------------------------------
	����˵���������ֶ���Ϣ��� String ֵ
	���������
		pItem			�������ָ��
		pszFieldName	�ֶ���
		iRow			�ڼ���
	����������
		fieldValue  �ֶ�ֵ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pItem �ǿ�ֵ
			20	�ֶ����ƿ��ܴ���
			50	���Ͳ���ȷ
	--------------------------------------------------------------------------*/
	static	int Get_string(CDB_QueryResult *pItem, char* pszFieldName, int iRow, string& fieldValue);
	
	/* --------------------------------------------------------------------------
	����˵���������ֶ���Ϣ��� char ֵ
	���������
		pItem			�������ָ��
		pszFieldName	�ֶ���
		iRow			�ڼ���
		iFieldMaxLen	�������ֶ�ֵ��fieldValue���������󳤶�
	����������
		fieldValue  �ֶ�ֵ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pItem �ǿ�ֵ
			20	�ֶ����ƿ��ܴ���
			50	���Ͳ���ȷ
			70  Խ�������ֶ����ݳ��� iFieldLen ��������Ȼ��� fieldValue ������Ϊ iFieldMaxLen ���ڵ�ֵ
	--------------------------------------------------------------------------*/
	static int Get_Char(CDB_QueryResult *pItem, char* pszFieldName, int iRow, char* fieldValue, int iFieldMaxLen);

	/* --------------------------------------------------------------------------
	����˵���������ֶ���Ϣ��ö����Ƶ�ֵ
	���������
		pFieldInfo	�ֶ���Ϣ
	����������
		pData		�����Ƶ�ֵ
		iDataLen	�����Ƶ�ֵ�ĳ��ȣ����ֽ�Ϊ��λ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	��ע��
	    MySQL �н� binary ��Ϊ MYSQL_TYPE_STRING ���ͣ��� varbinary ��Ϊ MYSQL_TYPE_VAR_STRING ���͡�
	--------------------------------------------------------------------------*/
	static int Get_Binary(CDB_QueryResult *pItem, char* pszFieldName, int iRow, BYTE*& pData, int& iDataLen);

	/* --------------------------------------------------------------------------
	����˵���������ֶ���Ϣ��û��ʱ��
	���������
		pFieldInfo	�ֶ���Ϣ
	����������
		pSystemTime	�ֶ��ڵ�ʱ����Ϣ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	--------------------------------------------------------------------------*/
	static int Get_DateTime(FIELD_INFO* pFieldInfo, EASY_DATA_TIME& easyDataTime);

	// �����ֶ���Ϣ��� BLOB ֵ��
	// ��δ��......����Ҫ�˽� MYSQL_BIND �ȣ�
	//// http://blog.csdn.net/charlie_2010/article/details/6147259
	static  int Get_DateTime(CDB_QueryResult *pItem, char* pszFieldName, int iRow, EASY_DATA_TIME& easyDataTime);

	static int Get_BLOB(CDB_QueryResult *pItem, char* pszFieldName, int iRow, BYTE*& pData, int& iDataLen);

protected:
	
	ULONGLONG	m_RowsNum;	// ����
	
	UINT	m_ColsNum;	// ����
	
	typedef std::vector<string> FIELD_VEC;	// ����
	typedef FIELD_VEC::iterator FIELD_VEC_ITER;

	FIELD_VEC m_FieldName;

	// ����������Ϣ
	typedef std::multimap<ULONGLONG, FIELD_INFO*> ITEM_MAP;
	typedef ITEM_MAP::iterator ITEM_ITER;
	typedef pair<ITEM_ITER,ITEM_ITER> RANGE_MAP;

	ITEM_MAP m_Items;
	ITEM_ITER m_Iter;
	RANGE_MAP m_Range;
};
//--- typedef �� -----------------------------------------
typedef std::vector<CDB_QueryResult*> MYSQL_MULTI_RES;

//--- ���� -----------------------------------------
class MySqlMultiResGuard	// ���������ػ�
{
public:
	MySqlMultiResGuard()	{	pMultiRes = 0;	}

	~MySqlMultiResGuard()
	{
		if(!pMultiRes)
			return;

		// �ͷŶ�����
		for (int i=0; i<pMultiRes->size(); i++)
		{
			CDB_QueryResult *pItem = (CDB_QueryResult*)(pMultiRes->at(i));

			SAFE_DELETE(pItem);	// ע�⣺Ҫ�ͷ�
		}

		pMultiRes->swap(MYSQL_MULTI_RES());	// swap ��ʽ���ͷ� vector
		pMultiRes->clear();
		pMultiRes = NULL;
	}

	// ��ö��������ػ�������0ֵ��ʾ��ȷ
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