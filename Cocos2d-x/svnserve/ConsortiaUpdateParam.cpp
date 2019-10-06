//
//  ConsortiaUpdateParam.cpp
//  g++ -o ConsortiaUpdateParam -std=c++11 ConsortiaUpdateParam.cpp
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

//Tab for ConsortiaUpdateParam.csv
struct TabConsortiaUpdateParamItem
{
 int m_nLevel;
 int m_nIsRoyal;
 int m_nneedMoney;
 int m_nneedGODian;
 int m_nneedExp;
 int m_nneedCredit;
 int m_nMaxUserNum;
 int m_nFoodRate;
 int m_nWoodRate;
 int m_nIronRate;
 int m_nSkinRate;
 int m_nincrease;
 int m_nFoodRate2;
 int m_nWoodRate2;
 int m_nIronRate2;
 int m_nSkinRate2;
};

std::map<int,TabConsortiaUpdateParamItem> m_mapConsortiaUpdateParamCache;

int LoadDataConsortiaUpdateParamItem(const char * pszFilePath)		//“从文件中读取数据”
{
	if( !m_mapConsortiaUpdateParamCache.empty() )
		return 2;//2已经载入数据了

	FILE * fp =fopen(pszFilePath, "r");
	if( fp == NULL )
		return 1;//1打开文件失败

	char szName[200] = {0};
	TabConsortiaUpdateParamItem item;
	int n = 0;
	n = fscanf(fp, "%s", szName);
	while( n > 0 && !feof(fp) )
	{
n = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
&item.m_nLevel,&item.m_nIsRoyal,&item.m_nneedMoney,&item.m_nneedGODian,&item.m_nneedExp,&item.m_nneedCredit,&item.m_nMaxUserNum,&item.m_nFoodRate,&item.m_nWoodRate,&item.m_nIronRate,&item.m_nSkinRate,&item.m_nincrease,&item.m_nFoodRate2,&item.m_nWoodRate2,&item.m_nIronRate2,&item.m_nSkinRate2);
		if( n > 0 )
		{
			m_mapConsortiaUpdateParamCache.insert( std::make_pair(item.m_nLevel, item) );
		}
	}
	fclose(fp);
	return 0;//0成功
}

const struct TabConsortiaUpdateParamItem * FindConsortiaUpdateParamItem(int nLevel)
{
	if(m_mapConsortiaUpdateParamCache.empty())//没载入数据
	{
		LoadDataConsortiaUpdateParamItem("ConsortiaUpdateParam.csv");
	}
	std::map<int,TabConsortiaUpdateParamItem>::const_iterator it;
	it = m_mapConsortiaUpdateParamCache.find( nLevel );
	if( it != m_mapConsortiaUpdateParamCache.end() )
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
		strcpy(sz2,"ConsortiaUpdateParam.csv");
	}
	
    int key=atoi(sz1);

	int nReturn =LoadDataConsortiaUpdateParamItem(sz2);//载入“配置表”

	const TabConsortiaUpdateParamItem * pItem=FindConsortiaUpdateParamItem(key);
    if(pItem)
	{
		printf("pItem=[%x],key=[%d],value=[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n",pItem,pItem->m_nLevel, \
		*((int *)pItem),*((int *)pItem+1),*((int *)pItem+2),*((int *)pItem+3), \
		*((int *)pItem+4),*((int *)pItem+5),*((int *)pItem+6),*((int *)pItem+7), \
		*((int *)pItem)+8,*((int *)pItem+9),*((int *)pItem+10),*((int *)pItem+11), \
		*((int *)pItem)+12,*((int *)pItem+13),*((int *)pItem+14),*((int *)pItem+15) \	
		);
	}
#ifdef _MSC_VER
	system("pause");
#endif	

	return 0;
}