/*********************************************************
Name：常用宏定义
Desc：常用宏定义
Auth：Cool.Cat@2013-03-15
*********************************************************/
#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <cocos2d.h>
#include <xorstr.h>
#include <string>
#include <vector>
using namespace std;
typedef std::vector<std::string> MP;

#include <SIX_Utility.h>

USING_NS_CC;

// ---------------------------
// 内存泄漏检测部分
// ---------------------------
#ifdef CHECK_MEM_LEAK
#ifdef _DEBUG
	// _CRTDBG_ALLOC_MEM_DF	程序退出时自动调用_CrtDumpMemoryLeaks()
	#define ML_INIT(f)	atexit(f);/*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);*/
	#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
	#define DEBUG_CLIENTBLOCK
	#define	ML_INIT(f)
#endif
#define _CRTDBG_MAP_ALLOC
//#define _CRTDBG_MAP_ALLOC_NEW
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
	#define new DEBUG_CLIENTBLOCK
#endif
#else
	#define	ML_INIT(f)
#endif
// ---------------------------

#define	CREATE_UTILITY	SIX_Utility *UT = SIX_Utility::GetInstance();
#define USING_UTILITY	extern SIX_Utility *UT;

#ifdef WIN32
#define SIXLog(fmt,...)	CCLog(SIX_Utility::GetInstance()->G2U("[%s](%d) ==> "##fmt).c_str(),__FUNCTION__,__LINE__,##__VA_ARGS__);
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define SIXLog(fmt,...)	CCLog(SIX_Utility::GetInstance()->G2U("[%s](%d) ==> "fmt).c_str(),__FUNCTION__,__LINE__,##__VA_ARGS__);
#else
#define SIXLog(fmt,...)
#endif
#endif

#define INTERFACE_GLOBALNAME	/*Interface.*/XorStr<0xF6,11,0x0053F956>("\xBF\x99\x8C\x9C\x88\x9D\x9D\x9E\x9B\xD1"+0x0053F956).s
#define SCRIPT_PATH				/*Script*/XorStr<0x12,7,0x3902D8F5>("\x41\x70\x66\x7C\x66\x63"+0x3902D8F5).s
#define REV_ADDR(T,x)			(T*)(*(unsigned long*)x);

#ifdef WIN32
#define STRCMP(x,y)	_stricmp(x,y)
#else
#define STRCMP(x,y)	strcasecmp(x,y)
#endif

#define CONSTRUCTOR(__cls_name__,...)				\
	public: __cls_name__(){							\
		__VA_ARGS__;								\
		/*SIXLog(__FUNCTION__);*/					\
	}
#define DESTRUCTOR(__cls_name__,...)				\
	public:virtual ~__cls_name__(){					\
		__VA_ARGS__;								\
		/*SIXLog(__FUNCTION__);*/					\
	}

#define CC_PURE_VIRTUAL_FUNC(__varType__,__varName__,__varFunc__)	\
	public:virtual __varType__ get##__varFunc__() const=0;			\
	public:virtual void set##__varFunc__(__varType__ __varName__)=0;

#define CCARRAY_FOREACH_T(__array__, __object__,__type__)                                                               \
    if ((__array__) && (__array__)->data->num > 0)																		\
    for(CCObject** arr = (__array__)->data->arr, **end = (__array__)->data->arr + (__array__)->data->num-1;				\
    arr <= end && (((__object__) = (__type__)*arr) != NULL/* || true*/);                                                \
    arr++)

#define CCARRAY_FOREACH_REVERSE_T(__array__, __object__,__type__)														\
    if ((__array__) && (__array__)->data->num > 0)																		\
    for(CCObject** arr = (__array__)->data->arr + (__array__)->data->num-1, **end = (__array__)->data->arr;				\
    arr >= end && (((__object__) = (__type__)*arr) != NULL/* || true*/);												\
    arr--)

#define ENUM_BEGIN(__E__)								\
	struct __E__{										\
		public:											\
		__E__(int value = 0) : _value((__Enum__)value){}\
		__E__& operator=(int value){					\
			this->_value = (__Enum__)value;				\
			return *this;								\
		}												\
		operator int() const {							\
			return this->_value;						\
		}												\
		enum __Enum__ {
#define ENUM_BEGIN_BASED(__E__,__B__)					\
	struct __E__:public __B__{							\
		public:											\
		__E__(int value = 0) : _value((__Enum__)value){}\
		__E__& operator=(int value){					\
			this->_value = (__Enum__)value;				\
			return *this;								\
		}												\
		operator int() const {							\
			return this->_value;						\
		}												\
		enum __Enum__ {
#define ENUM_END()										\
		};												\
	private:											\
		__Enum__ _value;								\
	};