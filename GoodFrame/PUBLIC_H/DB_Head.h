
#ifndef DB_HEAD_H
#define DB_HEAD_H

//--- 头文件区 -----------------------------------------
#include <string>
#include <vector>
#include <map>
#include <hash_map>
#include <algorithm>

#if 0
	// 提昌这样写，污染较轻
	using std::string;
	using std::wstring;
	using std::vector;
	using std::map;
	using std::hash_map;
	using std::pair;
	using std::find;
	//using std:
#else
	using namespace std;	// 这样写污染太重了！不提昌
#endif



//--- 定义区 -----------------------------------------

#define INVALID_FIELD_ID 0xffffffff  // 无效的字段索引值  
#define INVALID_ROW		 0xffffffff  // 无效的行  
#define INVALID_COL		 0xffffffff  // 无效的列  

#define SAFE_DELETE(x)				if (x)\
{\
	delete x;\
	x = 0;\
}

#define SAFE_DELETE_ARRAY(x)			if (x)\
{\
	delete [] x;\
	x = 0;\
}

#endif