/********************************************************************
	created:	2013/02/26
	created:	26:2:2013   15:24
	filename: 	E:\SVN_2013\GoodFrame\common\DB_Tunnel.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	DB_Tunnel
	file ext:	h
	author:		曹雪垠
	
	purpose:	MySQL C API、简化封装
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


	// 初始化
	bool mysql_init();

	// 参数设置
	int	mysql_options(enum mysql_option option,const char *arg);

	// 连接
	bool mysql_real_connect(const char *host,const char *user,const char *passwd,const char *db,unsigned int port,const char *socket,unsigned long flag);

	// 选择数据库
	int	mysql_select_db(const char *db);

	// 统计
	string mysql_stat();

	// 查询
	int	 mysql_real_query(const char *q,unsigned long length);

	// KeepLive
	void mysql_ping();

	// 获取MySQL服务端信息
	string mysql_get_server_info();

	// 获取MySQL信息
	string mysql_info();

	// 获取MySQL错误描述
	string mysql_error();

	// 获取MySQL错误码
	unsigned int mysql_errno();

	// 关闭
	void mysql_close();

	// 过滤SQL特殊字符(不考虑到连接的当前字符集)
	unsigned long mysql_escape_string(char *to,const char *from,unsigned long from_length);

	// 过滤SQL特殊字符(考虑到连接的当前字符集)
	unsigned long mysql_real_escape_string(char *to,const char *from,unsigned long length);

	// 获取上一次插入ID
	my_ulonglong mysql_insert_id();

	// 获取受影响的行数
	my_ulonglong mysql_affected_rows();

	// 在客户端存储结果集
	MYSQL_RES *mysql_store_result();

	// 在服务端存储结果集
	MYSQL_RES *mysql_use_result();

	// 遍历结果集下一条记录
	INT mysql_next_result();

	// 获取最后query影响的列数
	unsigned int mysql_field_count();

	// 移动行指针到指定的数据行(0～mysql_num_rows()-1)
	void mysql_data_seek(MYSQL_RES *res,my_ulonglong idx);

	// 移动列指针到指定的字段列(0～mysql_num_fields()-1)
	unsigned int mysql_field_seek(MYSQL_RES *result,unsigned int idx);

	// 获取结果集总行数
	my_ulonglong mysql_num_rows(MYSQL_RES *res);

	// 获取结果集字段总数
	unsigned int mysql_num_fields(MYSQL_RES *res);


	// 获取当前行中每个字段的内容的长度
	unsigned long *mysql_fetch_lengths(MYSQL_RES *res);

	// 遍历结果集下一行
	MYSQL_ROW mysql_fetch_row(MYSQL_RES *res);

	// 获取结果集字段信息
	MYSQL_FIELD *mysql_fetch_field(MYSQL_RES *res);

	MYSQL_FIELD *mysql_fetch_fields(MYSQL_RES *res);

	MYSQL_FIELD *mysql_fetch_field_direct(MYSQL_RES *res, unsigned int idx);

	// 释放结果集
	void mysql_free_result(MYSQL_RES *res);

protected:
	MYSQL* m_mysql;
};

#endif