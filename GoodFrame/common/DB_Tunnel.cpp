
#include "./PublicHead.h"
#include "./DB_Tunnel.h"
#include "./DB_QueryResult.h"

#ifdef _DEBUG
	#pragma comment(lib, "../../MySQL5.5/lib/debug/mysqlclient.lib")
#else
	#pragma comment(lib, "../../MySQL5.5/lib/mysqlclient.lib")
#endif

CDB_Tunnel::CDB_Tunnel(void)
{
	m_mysql = NULL;
}


CDB_Tunnel::~CDB_Tunnel(void)
{
}


bool CDB_Tunnel::mysql_init()
{
	if (m_mysql)
		return true;
	//m_mysql = ::mysql_init(0);
	m_mysql = new MYSQL();
	return ::mysql_init(m_mysql)?true:false;
}

int CDB_Tunnel::mysql_options(enum mysql_option option,const char *arg)
{
	return ::mysql_options(m_mysql,option,arg);
}

bool CDB_Tunnel::mysql_real_connect(const char *host,const char *user,const char *passwd,const char *db,unsigned int port,const char *socket,unsigned long flag)
{
	if (!m_mysql)
		return false;
	//m_mysql = ::mysql_real_connect(m_mysql,host,user,passwd,db,port,socket,flag);
	return ::mysql_real_connect(m_mysql,host,user,passwd,db,port,socket,flag)?true:false;
}

int CDB_Tunnel::mysql_select_db(const char *db)
{
	if (!m_mysql)
		return 0;
	return ::mysql_select_db(m_mysql,db);
}

string CDB_Tunnel::mysql_stat()
{
	if (!m_mysql)
		return "";
	return ::mysql_stat(m_mysql);
}

int CDB_Tunnel::mysql_real_query(const char *q,unsigned long length)
{
	if (!m_mysql)
		return 0;
	return ::mysql_real_query(m_mysql,q,length);
}

void CDB_Tunnel::mysql_ping()
{
	if (!m_mysql)
		return;
	::mysql_ping(m_mysql);
}

string CDB_Tunnel::mysql_get_server_info()
{
	if (!m_mysql)
		return "";
	return ::mysql_get_server_info(m_mysql);
}

string CDB_Tunnel::mysql_info()
{
	if (!m_mysql)
		return "";
	return ::mysql_info(m_mysql);
}

string CDB_Tunnel::mysql_error()
{
	if (!m_mysql)
		return "";
	return ::mysql_error(m_mysql);
}

unsigned int CDB_Tunnel::mysql_errno()
{
	if (!m_mysql)
		return 0;
	return ::mysql_errno(m_mysql);
}

void CDB_Tunnel::mysql_close()
{
	if (!m_mysql)
		return;
	::mysql_close(m_mysql);
	::mysql_thread_end();
}

void CDB_Tunnel::mysql_free_result(MYSQL_RES *res)
{
	if (!res)
		return;
	::mysql_free_result(res);
}

void CDB_Tunnel::mysql_data_seek(MYSQL_RES *res,my_ulonglong idx)
{
	if (!res)
		return;
	::mysql_data_seek(res,idx);
}

unsigned int CDB_Tunnel::mysql_field_seek(MYSQL_RES *res,unsigned int idx)
{
	if (!res)
		return 0;
	return ::mysql_field_seek(res,idx);
}

my_ulonglong CDB_Tunnel::mysql_num_rows(MYSQL_RES *res)
{
	if (!res)
		return 0;
	return ::mysql_num_rows(res);
}

unsigned int CDB_Tunnel::mysql_num_fields(MYSQL_RES *res)
{
	if (!res)
		return 0;
	return ::mysql_num_fields(res);
}

unsigned int CDB_Tunnel::mysql_field_count()
{
	if (!m_mysql)
		return 0;
	return ::mysql_field_count(m_mysql);
}

unsigned long* CDB_Tunnel::mysql_fetch_lengths(MYSQL_RES *res)
{
	if (!res)
		return 0;
	return ::mysql_fetch_lengths(res);
}

unsigned long CDB_Tunnel::mysql_escape_string(char *to,const char *from,unsigned long length)
{
	return ::mysql_escape_string(to,from,length);
}

unsigned long CDB_Tunnel::mysql_real_escape_string(char *to,const char *from, unsigned long length)
{
	if (!m_mysql)
		return 0;
	return ::mysql_real_escape_string(m_mysql,to,from,length);
}

my_ulonglong CDB_Tunnel::mysql_insert_id()
{
	if (!m_mysql)
		return 0;
	return ::mysql_insert_id(m_mysql);
}

my_ulonglong CDB_Tunnel::mysql_affected_rows()
{
	if (!m_mysql)
		return 0;
	return ::mysql_affected_rows(m_mysql);
}

MYSQL_RES* CDB_Tunnel::mysql_store_result()
{
	if (!m_mysql)
		return 0;
	return ::mysql_store_result(m_mysql);
}

MYSQL_RES* CDB_Tunnel::mysql_use_result()
{
	if (!m_mysql)
		return 0;
	return ::mysql_use_result(m_mysql);
}

INT CDB_Tunnel::mysql_next_result()
{
	if (!m_mysql)
		return 0;
	return ::mysql_next_result(m_mysql);
}

MYSQL_ROW CDB_Tunnel::mysql_fetch_row(MYSQL_RES *res)
{
	if (!res)
		return 0;
	return ::mysql_fetch_row(res);
}

MYSQL_FIELD* CDB_Tunnel::mysql_fetch_field(MYSQL_RES *res)
{
	if (!res)
		return 0;
	return ::mysql_fetch_field(res);
}

MYSQL_FIELD* CDB_Tunnel::mysql_fetch_fields(MYSQL_RES *res)
{
	if (!res)
		return 0;
	return ::mysql_fetch_fields(res);
}

MYSQL_FIELD* CDB_Tunnel::mysql_fetch_field_direct(MYSQL_RES *res,unsigned int idx)
{
	if (!res)
		return 0;
	return ::mysql_fetch_field_direct(res,idx);
}
