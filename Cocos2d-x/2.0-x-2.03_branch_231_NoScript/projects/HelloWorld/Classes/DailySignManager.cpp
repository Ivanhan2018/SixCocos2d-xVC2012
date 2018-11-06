//
//  DailySignManager.cpp
//  SignForXmlData
//
//  Created by XXY on 14-1-15.
//
//

#include "DailySignManager.h"

DDDXMLManager * DDDXMLManager::parserWithDataString(const char *tmxString)
{
    DDDXMLManager *pRet = new DDDXMLManager();
    if(pRet->initHXmlParse(tmxString))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool DDDXMLManager::initHXmlParse(const char* tmxString)
{
    
    mDataDic = CCDictionary::create();
    mArrDic = CCDictionary::create();
    
    CCSAXParser _par;
    
    if (false == _par.init("UTF-8") )
    {
        CCLog("-----璇蜂娇鐢╱tf-8鏍煎紡!");
        return false;
    }
    _par.setDelegator(this);
    bool bRet = false;
    unsigned long size = strlen(tmxString);
    char* pBuffer = (char*)tmxString;
    if (pBuffer != NULL && size > 0)
    {
        bRet = _par.parse(pBuffer, size);
    }

    return bRet;
}

//鍥炶皟鍑芥暟

void DDDXMLManager::startElement(void *ctx, const char *name, const char **atts)

{
    
    CC_UNUSED_PARAM(ctx);
    
    startXmlElement = (char*)name;
    if(!isJumpHeadData){//璺宠繃鏁版嵁澶?        //CCLog("------璺宠繃root name");
        isJumpHeadData=true;
        root_name = startXmlElement;
        return;
    }
    
    //CCLog("-startElement----%s",startXmlElement.c_str());
    
}

void DDDXMLManager::endElement(void *ctx, const char *name)

{
    CC_UNUSED_PARAM(ctx);
    
    endXmlElement = (char*)name;
    if(endXmlElement==root_name){//鏁版嵁灏?        CCLog("璇诲彇xml缁撴潫");
        isJumpHeadData=false;
        root_name="";
        return;
    }
    
    //CCLog("-endElement----%s",endXmlElement.c_str());
}
//閿€煎鐨勭粨鏉熷瓧娈?
void DDDXMLManager::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    if (currString.length()>0) {
        currString.append(string((char*)ch,0,len));
    }else{
        currString = string((char*)ch,0,len);
    }
}

void DDDXMLManager::ShowManagerData(){
    CCLog("鑾峰彇鏁版嵁涓?s",currString.c_str());
    AnalisyDataString(currString);
}

void DDDXMLManager::AnalisyDataString(string DataString){
    while (true) {
        int posStart = 0;
        int posEnd = 0;
        if ((posStart = DataString.find_last_of('[')) != DataString.npos) {
            posEnd = DataString.find(']', posStart);
            string ArrStr = DataString.substr(posStart+1,posEnd-posStart-1);
            string StartStr = DataString.substr(0, posStart);
            AnalyDataIfArrayDicData(ArrStr);
            string EndStr = DataString.substr(posEnd+1);
            StartStr.append("\"ARRAY\"");
            StartStr.append(EndStr);
            DataString = StartStr;
            //CCLog("缁勮瀛楃涓蹭负 %s", DataString.c_str());
        }else{
           break; 
        }
    }
    
    int pos = 0;
    while ((pos = DataString.find('"')) != DataString.npos) {
        DataString = DataString.substr(pos+1);
        int pos2 = DataString.find('"');
        string key = DataString.substr(0,pos2);
        //CCLog("key = %s",key.c_str());
        DataString = DataString.substr(pos2+1);
        int pos3 = DataString.find('"');
        DataString = DataString.substr(pos3+1);
        int pos4 = DataString.find('"');
        string Valve = DataString.substr(0,pos4);
        //CCLog("Valve = %s",Valve.c_str());
        DataString = DataString.substr(pos4+1);
        mDataDic->setObject(CCString::create(Valve), key);
    }
}

string DDDXMLManager::KeyForCurrentArray(string DataString){
    int startPos = DataString.find_last_of('"');
    DataString = DataString.substr(0,startPos-1);
    int endPos = DataString.find_last_of('"');
    string key = DataString.substr(endPos+1);
    //CCLog("Key %s", key.c_str());
    return key.length() > 0? key : "ARRAYITEM";
}

void DDDXMLManager::AnalyDataIfArrayDicData(string DataString){
    int flg = 0;
    while (true) {
        int posStart = 0;
        int posEnd = 0;
        if ((posStart = DataString.find_last_of('{')) != DataString.npos) {
            posEnd = DataString.find('}', posStart);
            string DicStr = DataString.substr(posStart+1,posEnd-posStart-1);
            string StartStr = DataString.substr(0, posStart);
            char Key[20];sprintf(Key, "Item%d",flg);
            mArrDic->setObject(AnalisyDataIfDictionaryData(DicStr), Key);
            DataString = StartStr;
            flg++;
        }else{
            break;
        }
    }
}

CCArray *DDDXMLManager::AnalyDataIfArrayData(string DataString){
    CCArray *arr =CCArray::createWithCapacity(10);
    arr->retain();
        while (true) {
            int posStart = 0;
            int posEnd = 0;
            if ((posStart = DataString.find_last_of('{')) != DataString.npos) {
                posEnd = DataString.find('}', posStart);
                string DicStr = DataString.substr(posStart+1,posEnd-posStart-1);
                string StartStr = DataString.substr(0, posStart);
                arr->addObject(AnalisyDataIfDictionaryData(DicStr));
                DataString = StartStr;
            }else{
                break; 
            }
        }
        return arr;
}

CCDictionary *DDDXMLManager::AnalisyDataIfDictionaryData(string DataString){
    CCDictionary *dic = CCDictionary::create();
    dic->retain();
        int pos = 0;
        while ((pos = DataString.find('"')) != DataString.npos) {
            DataString = DataString.substr(pos+1);
            int pos2 = DataString.find('"');
            string key = DataString.substr(0,pos2);
           // CCLog("key = %s",key.c_str());
            DataString = DataString.substr(pos2+1);
            int pos3 = DataString.find('"');
            DataString = DataString.substr(pos3+1);
            int pos4 = DataString.find('"');
            string Valve = DataString.substr(0,pos4);
            //CCLog("Valve = %s",Valve.c_str());
            DataString = DataString.substr(pos4+1);
            dic->setObject(CCString::create(Valve), key);
        }
        return dic;
}
