//
//  activity_chargetotal_data.cpp
//  g++ -o activity_chargetotal_data -std=c++11 activity_chargetotal_data.cpp
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


// 累计充值类型活动的配置
struct Activity_ChargeTotal_Config
{
	int ID;
	int ActivityID;
	int SubID;
	int	Charge;      // 充值额度
	int	AwardID;     // 奖励
	int	CostID;      // 消耗的物品ID,包含货币
	int	CostNum;     // 消耗的道具数量
	int	Limit;       // 可以购买或者领取多少次
	string Desc;     // 描述 
};

std::map<std::tuple<int,int,int>,Activity_ChargeTotal_Config> m_mapChargeTotalCache;//key=ActivityID+SubID+AwardID

int LoadDataChargeTotalItem(const char * pszFilePath)		//“从文件中读取数据”
{
	//if( !m_mapTaskCache.empty() )
		//return 2;//2已经载入数据了

	FILE * fp =fopen(pszFilePath, "r");
	if( fp == NULL )
		return 1;//1打开文件失败

	char szName[200] = {0};
	Activity_ChargeTotal_Config item;
	int n = 0;
	n = fscanf(fp, "%s", szName);
	while( n > 0 && !feof(fp) )
	{
	    char szTemp[200] = {0};
		n = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%s\r\n", &item.ID, &item.ActivityID, &item.SubID, &item.Charge, &item.AwardID, &item.CostID, &item.CostNum, &item.Limit, szTemp);
		if( n > 0 )
		{
			item.Desc=u2a(szTemp).c_str();
			m_mapChargeTotalCache.insert( std::make_pair(std::tuple<int,int,int>(item.ActivityID,item.SubID,item.AwardID), item) );
		}
	}
	fclose(fp);
	return 0;//0成功
}

const struct Activity_ChargeTotal_Config * Activity_ChargeTotal_GetActivityConfigByAwardIndex(int activityID,int subID,int awardIndex)
{
	std::map<std::tuple<int,int,int>,Activity_ChargeTotal_Config>::const_iterator it;
	it = m_mapChargeTotalCache.find(std::tuple<int,int,int>(activityID,subID,awardIndex));
	if( it != m_mapChargeTotalCache.end() )
		return &(it->second);
	return NULL;
}

int main(int argc, char **argv)
{
    const char* szCSV[]={"type_activity_30.csv","type_activity_31.csv","type_activity_101.csv","type_activity_102.csv","type_activity_103.csv","type_activity_104.csv"};
    for(auto const &s : szCSV)
	{
	   int nReturn =LoadDataChargeTotalItem(s);
	   printf("LoadDataChargeTotalItem(%s)=%d\n",s,nReturn);
	}

    int arr[][3]={{30,1,71705},{31,1,632},{101,1,70597},{102,4,70910},{103,4,70910},{104,1,70940}};
	for(auto &s : arr)
	{
		const Activity_ChargeTotal_Config * pItem=Activity_ChargeTotal_GetActivityConfigByAwardIndex(s[0],s[1],s[2]);
		if(pItem)
		{
			printf("pItem=[%x],key=[%d,%d,%d],value=[%d,%d,%d,%d,%d,%d,%d,%d,%s]\n",pItem,pItem->ActivityID,pItem->SubID,pItem->AwardID, \
			*((int *)pItem),*((int *)pItem+1),*((int *)pItem+2),*((int *)pItem+3), \
			*((int *)pItem+4),*((int *)pItem+5),*((int *)pItem+6),*((int *)pItem+7), \
			pItem->Desc.c_str() \
			);
		}			
	}	
#ifdef _MSC_VER
	system("pause");
#endif	

	return 0;
}