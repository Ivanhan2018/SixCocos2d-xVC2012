//
//  TaskDisplay.cpp
//  g++ -o TaskDisplay -std=c++11 TaskDisplay.cpp
//
//  Created by hxh on 19-9-21.
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
using namespace std;

#ifdef WIN32//_MSC_VER
#include <windows.h>
std::string GBK_To_UTF8(const std::string &source)
{
	enum {GB2312 = 936};
	
	unsigned long len = ::MultiByteToWideChar(GB2312, NULL, source.c_str(), -1, NULL, NULL);
	if (len == 0)
		return std::string();
	wchar_t *wide_char_buffer = new wchar_t[len];
	::MultiByteToWideChar(GB2312, NULL, source.c_str(), -1, wide_char_buffer, len);
	
	len = ::WideCharToMultiByte(CP_UTF8, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
	if (len == 0)
	{
		delete [] wide_char_buffer;
		return std::string();
	}
	char *multi_byte_buffer = new char[len];
	::WideCharToMultiByte(CP_UTF8, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);
	
	std::string dest(multi_byte_buffer);
	delete [] wide_char_buffer;
	delete [] multi_byte_buffer;
	return dest;
}
 
std::string UTF8_To_GBK(const std::string &source)
{
	enum {GB2312 = 936};
 
	unsigned long len = ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL);
	if (len == 0)
		return std::string();
	wchar_t *wide_char_buffer = new wchar_t[len];
	::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, wide_char_buffer, len);
	
	len = ::WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
	if (len == 0)
	{
		delete [] wide_char_buffer;
		return std::string();
	}
	char *multi_byte_buffer = new char[len];
	::WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);
	
	std::string dest(multi_byte_buffer);
	delete [] wide_char_buffer;
	delete [] multi_byte_buffer;
	return dest;
}
    #define u2a(str) UTF8_To_GBK(str)
#else
	#define u2a(str) std::string(str)
#endif


//“任务配置表”结点
struct TaskItem
{
 int  m_nTaskID;
 char m_szTaskName[16];
 int  m_nTaskLevel;
};

std::map<int,TaskItem>  m_mapTaskCache;

int LoadDataTaskItem(char * pszFilePath)		//“从文件中读取数据”
{
	if( !m_mapTaskCache.empty() )
		return 2;//2已经载入数据了

	FILE * fp =fopen(pszFilePath, "r");
	if( fp == NULL )
		return 1;//1打开文件失败

	char szName[200] = {0};
	TaskItem item;
	int n = 0;
	n = fscanf(fp, "%s", szName);
	while( n > 0 && !feof(fp) )
	{
	    char szTemp[200] = {0};
		n = fscanf(fp, "%d,%[^','],%d\n", &item.m_nTaskID, szTemp, &item.m_nTaskLevel);
		if( n > 0 )
		{
			strcpy(item.m_szTaskName,u2a(szTemp).c_str());
			m_mapTaskCache.insert( std::make_pair(item.m_nTaskID, item) );
		}
	}
	fclose(fp);
	return 0;//0成功
}

struct TaskItem * FindTaskItem(int nTaskID)
{
	std::map<int,TaskItem>::const_iterator it;
	it = m_mapTaskCache.find( nTaskID );
	if( it != m_mapTaskCache.end() )
		return (struct TaskItem *)&(it->second);
	return NULL;
}

const struct TaskItem * FindTaskItemC(int nTaskID)
{
	std::map<int,TaskItem>::const_iterator it;
	it = m_mapTaskCache.find( nTaskID );
	if( it != m_mapTaskCache.end() )
		return &(it->second);
	return NULL;
}

int main(int argc, char **argv)
{
	char sz1[100]={0};
	char sz2[100]={0};
	if(argc>1)
	{
        strcpy(sz1,argv[1]);
	}
	else
	{
		printf("输入key：");
		scanf("%s",sz1);		
	}
	
	if(argc>2)
	{
        strcpy(sz2,argv[2]);
	}
	else
	{
		strcpy(sz2,"TaskDisplay.csv");
	}
	
    int key=atoi(sz1);
  
	//std::wcout.imbue(std::locale("chs"));//加上去
	int nReturn =LoadDataTaskItem(sz2);//载入“任务配置表”
	//assert( nReturn != 1 && L"打开文件失败" );

	const TaskItem * pItem=FindTaskItemC(key);
	//TaskItem * pItem=FindTaskItem(key);
	printf("key=[%d],value=[%s,%d]\n",pItem->m_nTaskID,pItem->m_szTaskName,pItem->m_nTaskLevel);
	
#ifdef _MSC_VER
	system("pause");
#endif	

	return 0;
}