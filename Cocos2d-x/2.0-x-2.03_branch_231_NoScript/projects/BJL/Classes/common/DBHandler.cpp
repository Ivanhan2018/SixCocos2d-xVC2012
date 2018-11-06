#include "DBHandler.h"
#include "cocos2d.h"
#include <string>
using namespace std;
using namespace cocos2d;
static DBHandler* handler = NULL;

/**���DBHandler��������*/
DBHandler * DBHandler::sharedDBHandler()
{
	if(!handler)
	{
		return new DBHandler();
	}
	return handler;
}

/**���캯��*/
DBHandler::DBHandler(void)
{
	handler = this;
	pDB = NULL;
	open();
}

/**��������*/
DBHandler::~DBHandler(void)
{
	close();
}

/**sqlite3_exec�Ļص�����*/
int isExisted( void * para, int n_column, char ** column_value, char ** column_name ) 
{ 
	bool *isExisted_=(bool*)para; 
	*isExisted_=(**column_value)!='0'; 
	return 0; 
}

/**�ж����ݿ����Ƿ������Ϊname�ı�����һ��boolֵ��yesΪ����
������nameΪ����
*/
bool DBHandler::isTableExisted(char *name)
{
	char *errMsg = NULL;   //������Ϣ
	bool isExisted_; 
	char temp[100] = "select count(type) from sqlite_master where type='table' and name='";
	char* sqlstr = strcat(temp, name);
	sqlstr = strcat(sqlstr, "'");
	int count = sqlite3_exec( pDB, sqlstr, isExisted, &isExisted_, &errMsg ); 
	return isExisted_; 
}

/**�����Ƿ����ĳ����¼
������nameΪ������IDΪ��¼�ı��
*/
bool DBHandler::isRecordExisted(char *name, int ID)
{
	char *errMsg = NULL;   //������Ϣ
	bool isExisted_; 
	char tempStr[100];
	sprintf(tempStr, "select count(*) from %s where dwUserID = %d", name, ID);
	sqlite3_exec( pDB, tempStr , isExisted, &isExisted_, &errMsg ); 
	return isExisted_;
}

bool DBHandler::isRecordExisted(char *tableName, char *fieldName, char *fieldValue, bool isText)
{
	char *errMsg = NULL;   //������Ϣ
	bool isExisted_; 
	char tempStr[100];
	if(isText == true){
		sprintf(tempStr, "select count(*) from %s where %s = \'%s\'", tableName, fieldName, fieldValue);
	}else{
		sprintf(tempStr, "select count(*) from %s where %s = %s", tableName, fieldName, fieldValue);
	}
	sqlite3_exec( pDB, tempStr , isExisted, &isExisted_, &errMsg ); 
	return isExisted_;
}

/**�����ݿ�*/
int DBHandler::open()
{
	string path = /*CCFileUtils::sharedFileUtils()->getWritablePath()+*/"User.db";
	result = sqlite3_open(path.c_str(), &pDB);
	sqlite3_busy_timeout(pDB, SQL_BUSY_SLEEP_MIC);
	return result;
}

/**ִ��ĳ��sql����
������sql 
*/
int DBHandler::execute(char const *sql)
{
	char *errMsg = NULL;   //������Ϣ
	result = sqlite3_exec(pDB, sql, NULL, NULL, &errMsg);
	do 
	{
		if(result == SQLITE_BUSY)
		{
			result = sqlite3_exec(pDB, sql, NULL, NULL, &errMsg);
			continue;
		}
		break;
	} while (1);
	return result;
}

/**�ر����ݿ�*/
void DBHandler::close()
{
	sqlite3_close(pDB);
}

/**��ȡ���ݿ����*/
sqlite3 *DBHandler::getDB()
{
	return pDB;
}

/**��ȡ����row��col�е�intֵ
������ table����
row�к�
col�к�
����ֵ��int
*/
int DBHandler::getInt(char const *table, int row, int col)
{
	int res = 0;
	sqlite3_stmt *stmt;
	int index = 0;
	char str[50] = "select * from ";
	char *sql; 
	sql = strcat(str, table);
	int rv = sqlite3_prepare(pDB, sql, 50, &stmt, NULL);
	rv = sqlite3_step(stmt);
	while(rv == SQLITE_ROW)
	{
		if(index==row)
		{
			res = sqlite3_column_int64(stmt, col);
			rv = sqlite3_finalize(stmt);
			return res;
		}
		rv = sqlite3_step(stmt);
		index++;
	}
	rv = sqlite3_finalize(stmt);
	return res;
}


sqlite3_int64 DBHandler::getInt64(char const *table, int row, int col)
{
	sqlite3_int64 res = 0;
	sqlite3_stmt *stmt;
	int index = 0;
	char str[50] = "select * from ";
	char *sql; 
	sql = strcat(str, table);
	int rv = sqlite3_prepare(pDB, sql, 50, &stmt, NULL);
	rv = sqlite3_step(stmt);
	while(rv == SQLITE_ROW)
	{
		if(index==row)
		{
			res = sqlite3_column_int(stmt, col);
			rv = sqlite3_finalize(stmt);
			return res;
		}
		rv = sqlite3_step(stmt);
		index++;
	}
	rv = sqlite3_finalize(stmt);
	return res;
}

/**��ȡ����row��col�е�doubleֵ
������table����
row�к�
col�к�
����ֵ��double
*/
double DBHandler::getDouble(char const *table, int row, int col)
{
	double res = 0.0;
	sqlite3_stmt *stmt;
	int index = 0;
	char str[50] = "select * from ";
	char *sql; 
	sql = strcat(str, table);
	int rv = sqlite3_prepare(pDB, sql, 50, &stmt, NULL);
	rv = sqlite3_step(stmt);
	while(rv == SQLITE_ROW)
	{
		if(index==row)
		{
			res = sqlite3_column_double(stmt, col);
			rv = sqlite3_finalize(stmt);
			return res;
		}
		rv = sqlite3_step(stmt);
		index++;
	}
	rv = sqlite3_finalize(stmt);
	return res;
}

/**��ȡ����row��col�е��ַ���ֵ
������table����
row�к�
col�к�
����ֵ���ַ���
*/
const unsigned char * DBHandler::getText(char const *table, int row, int col)
{
	const unsigned char *res = {'\0'};
	sqlite3_stmt *stmt;
	int index = 0;
	char str[50] = "select * from ";
	char *sql; 
	sql = strcat(str, table);
	int rv = sqlite3_prepare(pDB, sql, 50, &stmt, NULL);
	rv = sqlite3_step(stmt);
	while(rv == SQLITE_ROW)
	{
		if(index==row)
		{
			res = sqlite3_column_text(stmt, col);
			break;
		}
		rv = sqlite3_step(stmt);
		index++;
	}
	char temp[32];
	sprintf(temp, "%s", res);
	res = ( unsigned char * )( void * )temp;
	rv = sqlite3_finalize(stmt);
	return res;
}

/**���µ�ǰ�û���ǰ�ؿ���һЩ������Ϣ
������levelID�ؿ���
userID�û������
time��ǰ�ؿ�����ʱ��
star��ǰ�ؿ�����������
money��ǰ�ؿ����ý��
score��ǰ�ؿ����ķ���
����ֵ���������ݽ����
*/
int  DBHandler::updateValueInfo(int levelID, int userID, float time, int star, int money, int score)
{
	int res = 0;
	char *errMsg = NULL;   //������Ϣ
	bool isExisted_; 
	char tempStr[100];
	sprintf(tempStr, "select count(*) from levelInfo where (levelID=%d and userID=%d)", levelID, userID);
	sqlite3_exec( pDB, tempStr , isExisted, &isExisted_, &errMsg ); 
	if(!isExisted_)
	{
		char sql[100];
		sprintf(sql, "insert into levelInfo(levelID,userID,time,star,money,score)values(%d,%d,%f,%d,%d,%d)", levelID, userID, time, star, money, score);
		res = this->execute(sql);
	}else
	{
		char sql[100];
		sqlite3_stmt *stmt;
		float timeRecord;
		sprintf(sql, "select time from levelInfo where (levelID=%d and userID=%d)", levelID, userID);
		int rv = sqlite3_prepare(pDB, sql, 100, &stmt, NULL);
		rv = sqlite3_step(stmt);
		if(rv == SQLITE_ROW)
		{
			timeRecord = sqlite3_column_double(stmt, 0);
		}
		sqlite3_finalize(stmt);
		if(time<timeRecord)
		{	
			char sqlChar[150];
			sprintf(sqlChar, "update levelInfo set levelID=%d,userID=%d,time=%f,star=%d,money=%d,score=%d where(levelID=%d and userID=%d)", levelID, userID, time, star, money, score, levelID, userID);
			res = this->execute(sqlChar);
		}
	}
	return res;
}

/**�����û���Ϣ
������userID�û����
*/
void DBHandler::updateUserInfo(int userID)
{
	char sql[100];
	sqlite3_stmt *stmt;
	int score;
	sprintf(sql, "select sum(score) from levelInfo where userID=%d", userID);
	int rv = sqlite3_prepare(pDB, sql, 100, &stmt, NULL);
	rv = sqlite3_step(stmt);
	if(rv == SQLITE_ROW)
	{
		score = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);
	int totalScore = this->getInt("userInfo", userID-1, 3);
	int money = this->getInt("userInfo", 0, 2);
	int totalMoney = this->getInt("userInfo", userID-1, 2);
	totalMoney+=money;
	if(totalScore<score)
	{	
		char sqlChar[150];
		sprintf(sqlChar, "update userInfo set totalMoney=%d,totalScore=%d where(ID=%d)", totalMoney, score, userID);
		rv = this->execute(sqlChar);
	}else
	{
		char sqlChar[150];
		sprintf(sqlChar, "update userInfo set totalMoney=%d where(ID=%d)", totalMoney, userID);
		rv = this->execute(sqlChar);
	}
	this->execute("update userInfo set totalMoney=0,totalScore=0,identifier='' where ID=1");
}