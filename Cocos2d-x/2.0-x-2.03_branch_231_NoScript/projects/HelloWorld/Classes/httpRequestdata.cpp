//
//  httpRequestdata.cpp
//  XXDDZ
//
//  Created by Eldder on 14-1-16.
//
//

#include "httpRequestdata.h"
#include "md5.h"


CCHttpRequest* httpRequestdata::sendHTTPData(string _method , string prama){

    CCHttpRequest* request = new CCHttpRequest();
    string  datastring = "" ;
    
    string initMd5string = "";
    initMd5string.append(_method);
    initMd5string.append(prama);
    initMd5string.append("86CFAED5C6D9AE10897D4935A85ED9A545915A9E");
    
    string Md5String = MD5(initMd5string).toString();
    
    CCLog("%s" , Md5String.c_str());
    CCLog("%s", prama.c_str());
    
    datastring.assign("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                      "<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">\n"
                      "<soap:Body>\n"
                      "<GetWay xmlns=\"http://tempuri.org/\">\n"
                      "<method>");
    datastring.append(_method);
    datastring.append("</method>\n");
    datastring.append("<param>");
    datastring.append(prama);
    datastring.append("</param>\n");
    datastring.append("<sign>");
    datastring.append(Md5String);
    datastring.append("</sign>\n");
    datastring.append("</GetWay>\n"
                      "</soap:Body>\n"
                      "</soap:Envelope>\n");
    
    request->setUrl("http://dtt.dudgame.com/WS/WSMobileService.asmx");
    request->setRequestType(CCHttpRequest::kHttpPost);
    std::vector<std::string> headers;
    headers.push_back("Content-Type: text/xml; charset=utf-8"); //WebServer褰撲腑鏁版嵁鏂囦欢澶寸被鍨嬭鏄?    headers.push_back("SOAPAction: http://tempuri.org/GetWay");
    //datastring.append(MD5("usersign6505").toString());
    request->setRequestData(datastring.data(), strlen(datastring.data()));
    //request->setHeaders(headers);//error C2039: “setHeaders”: 不是“cocos2d::extension::CCHttpRequest”的成员
    return request;
}

