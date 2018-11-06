/********************************************************************
	created:	2013/02/26
	created:	26:2:2013   15:24
	filename: 	E:\SVN_2013\GoodFrame\common\DB_Tunnel.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	DB_Tunnel
	file ext:	h
	author:		��ѩ��
	
	purpose:	MySQL C API���򻯷�װ
*********************************************************************/


#ifndef DB_TUNNEL_H
#define DB_TUNNEL_H

#include <winsock.h>
#include <assert.h>

#include <string>

#include "../../MySQL5.5/include/mysql.h"

#include "./DB_QueryResult.h"

class __declspec(dllexport) CDB_Tunnel
{
public:
	CDB_Tunnel(void);
	~CDB_Tunnel(void);

public:


	// ��ʼ��
	bool mysql_init();

	// ��������
	int	mysql_options(enum mysql_option option,const char *arg);

	// ����
	bool mysql_real_connect(const char *host,const char *user,const char *passwd,const char *db,unsigned int port,const char *socket,unsigned long flag);

	// ѡ�����ݿ�
	int	mysql_select_db(const char *db);

	// ͳ��
	string mysql_stat();

	// ��ѯ
	int	 mysql_real_query(const char *q,unsigned long length);

	// KeepLive
	void mysql_ping();

	// ��ȡMySQL�������Ϣ
	string mysql_get_server_info();

	// ��ȡMySQL��Ϣ
	string mysql_info();

	// ��ȡMySQL��������
	string mysql_error();

	// ��ȡMySQL������
	unsigned int mysql_errno();

	// �ر�
	void mysql_close();

	// ����SQL�����ַ�(�����ǵ����ӵĵ�ǰ�ַ���)
	unsigned long mysql_escape_string(char *to,const char *from,unsigned long from_length);

	// ����SQL�����ַ�(���ǵ����ӵĵ�ǰ�ַ���)
	unsigned long mysql_real_escape_string(char *to,const char *from,unsigned long length);

	// ��ȡ��һ�β���ID
	my_ulonglong mysql_insert_id();

	// ��ȡ��Ӱ�������
	my_ulonglong mysql_affected_rows();

	// �ڿͻ��˴洢�����
	MYSQL_RES *mysql_store_result();

	// �ڷ���˴洢�����
	MYSQL_RES *mysql_use_result();

	// �����������һ����¼
	INT mysql_next_result();

	// ��ȡ���queryӰ�������
	unsigned int mysql_field_count();

	// �ƶ���ָ�뵽ָ����������(0��mysql_num_rows()-1)
	void mysql_data_seek(MYSQL_RES *res,my_ulonglong idx);

	// �ƶ���ָ�뵽ָ�����ֶ���(0��mysql_num_fields()-1)
	unsigned int mysql_field_seek(MYSQL_RES *result,unsigned int idx);

	// ��ȡ�����������
	my_ulonglong mysql_num_rows(MYSQL_RES *res);

	// ��ȡ������ֶ�����
	unsigned int mysql_num_fields(MYSQL_RES *res);


	// ��ȡ��ǰ����ÿ���ֶε����ݵĳ���
	unsigned long *mysql_fetch_lengths(MYSQL_RES *res);

	// �����������һ��
	MYSQL_ROW mysql_fetch_row(MYSQL_RES *res);

	// ��ȡ������ֶ���Ϣ
	MYSQL_FIELD *mysql_fetch_field(MYSQL_RES *res);

	MYSQL_FIELD *mysql_fetch_fields(MYSQL_RES *res);

	MYSQL_FIELD *mysql_fetch_field_direct(MYSQL_RES *res, unsigned int idx);

	// �ͷŽ����
	void mysql_free_result(MYSQL_RES *res);

protected:
	MYSQL* m_mysql;
};

#endif