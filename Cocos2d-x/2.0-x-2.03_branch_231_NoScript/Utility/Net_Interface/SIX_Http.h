/***********************************************
Name：HTTP交互模块
Desc：实现Post/Get交互，基于Curl
	  如果要支持HTTPS协议，请重新编译Curl
Auth：Cool.Cat@2013-04-02
***********************************************/
#pragma once
#include <SIX_Interface.h>
#include <CCLuaEngine.h>
#include <network\HttpClient.h>
#include <vector>
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_HTTP:public CCObject{
	public:
		SIX_HTTP(){}
		~SIX_HTTP(){}
		void Get(const char* url/*,void *handler*/);
		void Post(const char* url/*,void *handler*/,const char *data,unsigned int len);
		void onHttpRequestCompleted(CCNode *sender, void *data);
		void executeCallback(int responseCode, const char* resp,unsigned int len,const char *cbName="onSuccessed");
	//public:
	//	int m_nHandler;
};
