//
//  DailySignManager.h
//  SignForXmlData
//
//  Created by XXY on 14-1-15.
//
//

#ifndef __SignForXmlData__DailySignManager__
#define __SignForXmlData__DailySignManager__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/CCSAXParser.h"
#else
#include "CCSAXParser.h"
#endif

using namespace std;

USING_NS_CC;

class DDDXMLManager  :public CCObject, public CCSAXDelegator
{
    
public:
    
    static DDDXMLManager * parserWithDataString(const char *tmxString);
    
    bool initHXmlParse(const char* tmxString);
    
    //  使用 CCSAXDelegator 重写3个回调函数
    
    void startElement(void *ctx, const char *name, const char **atts);
    
    void endElement(void *ctx, const char *name);
    
    void textHandler(void *ctx, const char *ch, int len);
    
    std::string root_name;
    
    bool isJumpHeadData;
    
    CCDictionary *mDataDic;
    
    CCDictionary *mArrDic;
    
    void ShowManagerData();
    
private:
    
    void AnalisyDataString(string DataString);
    
    CCArray *AnalyDataIfArrayData(string DataString);
    
    void AnalyDataIfArrayDicData(string DataString);
    
    std::string KeyForCurrentArray(string DataString);
    
    CCDictionary *AnalisyDataIfDictionaryData(string DataString);
    
    std::string startXmlElement;//用来记录每个key前字段
    
    std::string endXmlElement;//用来记录每个key后字段
    
    std::string currString;//记录每个value的值
    
}; ;

#endif /* defined(__SignForXmlData__DailySignManager__) */
