
#ifndef DB_HEAD_H
#define DB_HEAD_H

//--- ͷ�ļ��� -----------------------------------------
#include <string>
#include <vector>
#include <map>
#include <hash_map>
#include <algorithm>

#if 0
	// �������д����Ⱦ����
	using std::string;
	using std::wstring;
	using std::vector;
	using std::map;
	using std::hash_map;
	using std::pair;
	using std::find;
	//using std:
#else
	using namespace std;	// ����д��Ⱦ̫���ˣ������
#endif



//--- ������ -----------------------------------------

#define INVALID_FIELD_ID 0xffffffff  // ��Ч���ֶ�����ֵ  
#define INVALID_ROW		 0xffffffff  // ��Ч����  
#define INVALID_COL		 0xffffffff  // ��Ч����  

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