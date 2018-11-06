
#ifndef GENERAL_DB_H
#define GENERAL_DB_H

#include "./GeneralWork.h"

#include "./ThreadGuard.h"
#include "./BasicLogic.h"
#include "./DB_ConnectionGuard.h"

#include <list>
using std::list;

class __declspec(dllexport) CGeneralDB : public CGeneralWork
{
public:
	enum{
		ERR_GB_01 = 10,		// 
		};
public:
	CGeneralDB(void);
	~CGeneralDB(void);

public:
	/* --------------------------------------------------------------------------
	����˵������ʼ����ע���� start_db ����֮ǰִ�б�����
	���������
		strHost		���ݿ�ĵ�ַ�����ִ���ʽ���� 127.0.0.1
		uPort		���ݿ�Ķ˿ڣ��� 3306
		strDB		���ݿ������� six_divistions
		strUser		���ݿ��û������� root
		strPass		���ݿ�����
		strCharset	���ݿ��ַ���
		bReconnect	���ݿ���ߺ��Ƿ�����
		uTimeout	�Ự���г�ʱ
	--------------------------------------------------------------------------*/
	int init_db(char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect=TRUE, UINT uTimeout=28800);
	
	/* --------------------------------------------------------------------------
	����˵�����������ݿ�����ע���� Init_db ����ִ��֮�����ִ�б�����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	�������ݿ�ʧ�ܣ�������ݿ��IPֵ��˿�ֵ�Ƿ���ȷ��
			20	�������ݿ�����ʧ��
	--------------------------------------------------------------------------*/
	int start_db();

	// ֹͣ
	int stop_db();

	// �����ݿⷢ����������Ϊ���ݿ��ڳ�ʱ��ò������ʾͻ��Զ�����
	int db_heartbeat();

	// ��ʼ��һЩֵ��ͨ���� start_db ����֮��ִ��
	virtual int init_after_start_db() = 0;

	void test(string* pVal);

public:
	CDB_ConnectionPool m_stConnPool;	// ���ӳ�
};

#endif