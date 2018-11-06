/***********************************************
Name��HTTP����ģ��
Desc��ʵ��Post/Get����������Curl
	  ���Ҫ֧��HTTPSЭ�飬�����±���Curl
Auth��Cool.Cat@2013-04-02
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
