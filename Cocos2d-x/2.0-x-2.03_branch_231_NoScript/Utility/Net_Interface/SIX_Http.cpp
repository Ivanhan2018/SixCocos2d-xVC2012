#include "SIX_Http.h"
USING_NS_CC_EXT;

void SIX_HTTP::Get(const char* url/*,void *handler*/)
{
	SIXLog("Get");
	SIX_HTTP *myHttpClient=new SIX_HTTP();
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl(url);
	//myHttpClient->m_nHandler=(int)handler;
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(myHttpClient, callfuncND_selector(SIX_HTTP::onHttpRequestCompleted));
	CCHttpClient::getInstance()->send(request);
	request->release();
}

void SIX_HTTP::Post(const char* url/*,void *handler*/,const char *data,unsigned int len)
{
	SIXLog("Post");
	SIX_HTTP *myHttpClient=new SIX_HTTP();
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl(url);
	request->setRequestData(data,len);
	//myHttpClient->m_nHandler=(int)handler;
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(myHttpClient, callfuncND_selector(SIX_HTTP::onHttpRequestCompleted));
	CCHttpClient::getInstance()->send(request);
	request->release();
}

void SIX_HTTP::onHttpRequestCompleted(CCNode *sender, void *resp) 
{
	SIXLog("onHttpRequestCompleted");

	CCHttpResponse *response = (CCHttpResponse*)resp;

	if (!response)
		return;

	this->executeCallback(
		response->getResponseCode(),
		response->isSucceed()?response->getResponseData()->data():response->getErrorBuffer(),
		response->isSucceed()?response->getResponseData()->size():strlen(response->getErrorBuffer()),
		response->isSucceed()?"onSuccessed":"onError");
}

void SIX_HTTP::executeCallback(int responseCode, const char* data,unsigned int len,const char *cbName)
{
	SIXLog("executeCallback");
	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	lua_State* m_state = pEngine->getLuaState();
	lua_pushinteger(m_state, responseCode);
	lua_pushstring(m_state,data);
	lua_pushnumber(m_state,len);
	//pEngine->executeFunctionByHandler(this->m_nHandler, 2);
	pEngine->executeGlobalFunction(cbName,3);
}
