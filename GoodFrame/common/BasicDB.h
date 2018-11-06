
/********************************************************************
	created:	2013/03/08
	created:	8:3:2013   13:19
	filename: 	E:\SVN_2013\GoodFrame\common\BasicDB.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	BasicDB
	file ext:	h
	author:		侯国江
	
	purpose:	基本数据库类，一切数据库任务都以本类为父类
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
	函数说明：初始化，注意在 start_db 函数之前执行本函数
	传入参数：
		iConnectNum	数据库的连接数，原则上此值最好 >= 数据库任务消息推送线程数量，就可以保证每每数据库任务都拥有一个数据库连接
		strHost		数据库的地址，是字串形式，如 127.0.0.1
		uPort		数据库的端口，如 3306
		strDB		数据库名，如 six_divistions
		strUser		数据库用户名，如 root
		strPass		数据库密码
		strCharset	数据库字符集
		bReconnect	数据库断线后是否重连
		uTimeout	会话空闲超时
	--------------------------------------------------------------------------*/
	int init_db(int iConnectNum, char* pszHost, UINT uPort, char* pszDB, char* pszUser, char* pszPass, char* pszCharset, bool bReconnect=TRUE, UINT uTimeout=28800);
	
	/* --------------------------------------------------------------------------
	函数说明：启动数据库任务，注意在 Init_db 函数执行之后才能执行本函数
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	连接数据库失败，检查数据库的IP值与端口值是否正确。
			20	启动数据库任务失败
	--------------------------------------------------------------------------*/
	int start_db();

	// 停止
	int stop_db();

	// 向数据库发心跳包，因为数据库在长时间得不到访问就会自动断线
	int db_heartbeat();

	void test(string* pVal);

public:
	CDB_ConnectionPool m_stConnPool;	// 连接池
};

#endif