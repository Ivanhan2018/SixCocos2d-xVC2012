//
//  activity_store_data.cpp
//  g++ -o activity_store_data -std=c++11 activity_store_data.cpp
//
//  Created by hxh on 19-9-21.
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tuple>
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


// 商城类型活动的配置
struct ActivityStore_Config
{
	int ID;
	int ActivityID;
	int SubID;
	int	AwardID;     // 奖励	
	int	MoneyID;     // 货币ID,999是指现金,单位分
	int	ChargeID;    // 现金购买价格
	int	Limit;       // 可以购买或者领取多少次	
	string Desc;     // 描述 
	string Icon;     // 发送给前端使用,图标
	string Rebate;   // 发送给前端使用的显示折扣	
};

std::map<std::tuple<int,int,int>,ActivityStore_Config> m_mapStoreCache;//key=ActivityID+SubID+ChargeID
std::map<std::tuple<int,int,int>,ActivityStore_Config> m_mapStoreCache1;//key=ActivityID+SubID+(ID-1)

int LoadDataStoreItem(const char * pszFilePath)		//“从文件中读取数据”
{
	//if( !m_mapStoreCache.empty() )
		//return 2;//2已经载入数据了

	FILE * fp =fopen(pszFilePath, "r");
	if( fp == NULL )
		return 1;//1打开文件失败

	char szName[200] = {0};
	ActivityStore_Config item;
	int n = 0;
	n = fscanf(fp, "%s", szName);
	while( n > 0 && !feof(fp) )
	{
	    char szTemp1[200] = {0};
	    char szTemp2[200] = {0};
	    char szTemp3[200] = {0};		
		n = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%[^','],%[^','],%s\r\n", &item.ID, &item.ActivityID, &item.SubID, &item.AwardID, &item.MoneyID,&item.ChargeID, &item.Limit, szTemp1, szTemp2, szTemp3);
		if( n > 0 )
		{
			item.Desc=u2a(szTemp1).c_str();
			item.Icon=u2a(szTemp2).c_str();	
			item.Rebate=u2a(szTemp3).c_str();
			m_mapStoreCache.insert( std::make_pair(std::tuple<int,int,int>(item.ActivityID,item.SubID,item.ChargeID), item) );			
			m_mapStoreCache1.insert( std::make_pair(std::tuple<int,int,int>(item.ActivityID,item.SubID,item.ID-1), item) );
		}
	}
	fclose(fp);
	return 0;//0成功
}

const struct ActivityStore_Config * ActivityStore_GetConfigByChargeID(int activityID,int subID,int chargeID)
{
	std::map<std::tuple<int,int,int>,ActivityStore_Config>::const_iterator it;
	it = m_mapStoreCache.find(std::tuple<int,int,int>(activityID,subID,chargeID));
	if( it != m_mapStoreCache.end() )
		return &(it->second);
	return NULL;
}

const struct ActivityStore_Config * ActivityStore_GetStoreItemConfig(int activityID,int subID,int itemIndex)
{
	std::map<std::tuple<int,int,int>,ActivityStore_Config>::const_iterator it;
	it = m_mapStoreCache1.find(std::tuple<int,int,int>(activityID,subID,itemIndex));
	if( it != m_mapStoreCache1.end() )
		return &(it->second);
	return NULL;
}

int main(int argc, char **argv)
{
    const char* szCSV[]={"type_activity_105.csv","type_activity_106.csv","type_activity_107.csv","type_activity_109.csv"};
    for(auto const &s : szCSV)
	{
	   int nReturn =LoadDataStoreItem(s);
	   printf("LoadDataStoreItem(%s)=%d\n",s,nReturn);
	}

    int arr[][3]={{105,1,10},{106,1,20},{107,1,28},{109,1,33}};
	for(auto &s : arr)
	{
		const ActivityStore_Config * pItem=ActivityStore_GetConfigByChargeID(s[0],s[1],s[2]);
		if(pItem)
		{
			printf("pItem=[%x],key=[%d,%d,%d],value=[%d,%d,%d,%d,%d,%d,%d,%s,%s,%s]\n",pItem,pItem->ActivityID,pItem->SubID,pItem->ChargeID, \
			*((int *)pItem),*((int *)pItem+1),*((int *)pItem+2),*((int *)pItem+3), \
			*((int *)pItem+4),*((int *)pItem+5),*((int *)pItem+6),pItem->Desc.c_str(), \
			pItem->Icon.c_str(),pItem->Rebate.c_str() \
			);
		}			
	}	
    int arr1[][3]={{105,1,1},{106,1,5},{107,1,7},{109,1,4}};
	for(auto &s : arr1)
	{
		const ActivityStore_Config * pItem=ActivityStore_GetStoreItemConfig(s[0],s[1],s[2]);
		if(pItem)
		{
			printf("pItem=[%x],key=[%d,%d,%d],value=[%d,%d,%d,%d,%d,%d,%d,%s,%s,%s]\n",pItem,pItem->ActivityID,pItem->SubID,pItem->ChargeID, \
			*((int *)pItem),*((int *)pItem+1),*((int *)pItem+2),*((int *)pItem+3), \
			*((int *)pItem+4),*((int *)pItem+5),*((int *)pItem+6),pItem->Desc.c_str(), \
			pItem->Icon.c_str(),pItem->Rebate.c_str() \
			);
		}			
	}	
#ifdef _MSC_VER
	system("pause");
#endif	

	return 0;
}
