#include "JsonHelper.h"
#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

Json::Value JsonHelper::getJsonFromFile(const char *filename)
{
	Json::Reader reader;
	const char* pszFullPath = filename;

	unsigned long size;
	char *pFileContent = (char *)CCFileUtils::sharedFileUtils()->getFileData(pszFullPath, "rb", &size);
	string jsonfile;
	jsonfile.assign(pFileContent, size);

	CCAssert( size > 0, "file is open fail!");
	Json::Value root;
	if(!reader.parse(jsonfile, root, false))
	{
		CCAssert(false, "Json::Reader Parse error!");
	}
	return root;
}

Json::Value JsonHelper::getJsonFromData(const char *data, int size)
{
	Json::Reader reader;
	string jsonfile;
	jsonfile.assign(data, size);
	//CCAssert( size > 0, "file is open fail!");
	Json::Value root;
	if(!reader.parse(jsonfile, root, false))
	{
		return NULL;
		CCAssert(false, "Json::Reader Parse error!");
	}
	return root;
}