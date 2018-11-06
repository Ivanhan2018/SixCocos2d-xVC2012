
/********************************************************************
	created:	2013/03/08
	created:	8:3:2013   13:19
	filename: 	E:\SVN_2013\GoodFrame\common\BasicDB.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	BasicDB
	file ext:	h
	author:		�����
	
	purpose:	�������ݿ��࣬һ�����ݿ������Ա���Ϊ����
*********************************************************************/

#ifndef BASIC_DB_H
#define BASIC_DB_H

#include "./ThreadGuard.h"
#include "./BasicLogic.h"
#include "./DB_ConnectionGuard.h"

#include <list>
using std::list;

class __declspec(dllexport) CBasicDB : public CBasicLogic
{
public:
	CBasicDB(void);
	~CBasicDB(void);

public:
	/* --------------------------------------------------------------------------
	����˵������ʼ����ע���� start_db ����֮ǰִ�б�����
	���������
		iConnectNum	���ݿ����������ԭ���ϴ�ֵ��� >= ���ݿ�������Ϣ�����߳��������Ϳ��Ա�֤ÿÿ���ݿ�����ӵ��һ�����ݿ�����
		strHost		���ݿ�ĵ�ַ�����ִ���ʽ���� 127.0.0.1
		uPort		���ݿ�Ķ˿ڣ��� 3306
		strDB		���ݿ������� six_divistions
		strUser		���ݿ��û������� root
		strPass		���ݿ�����
		strCharset	���ݿ��ַ���
		bReconnect	���ݿ���ߺ��Ƿ�����
		uTimeout	�Ự���г�ʱ
	--------------------------------------------------------------------------*/
	int init_db(int iConnectNum, char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect=TRUE, UINT uTimeout=28800);
	
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

	void test(string* pVal);

public:
	CDB_ConnectionPool m_stConnPool;	// ���ӳ�
};

#endif