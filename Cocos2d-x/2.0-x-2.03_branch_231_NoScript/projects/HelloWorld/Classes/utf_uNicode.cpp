//
//  utf_uNicode.cpp
//  XXDDZ
//
//  Created by Eldder on 13-11-20.
//
//

#include "utf_uNicode.h"


////utf_8转换为unicode
//TCHAR* utf8_to_unicode::utf8TO_Unicode(const char* _nickName, int wdatalength){
//    
//    wchar_t unicode[wdatalength];
//    for (int i = 0; i< wdatalength; i++) {
//        unicode[i] = (_nickName[0+i*3] & 0x1F) << 12;
//        unicode[i] |= (_nickName[1+i*3] & 0x3F) << 6;
//        unicode[i] |= (_nickName[2+i*3] & 0x3F);
//    }
//    
//    TCHAR nickname[wdatalength];
//    memset(nickname, 0, wdatalength);
//    for (int k = 0; k<wdatalength; k++) {
//        nickname[k] = unicode[k];
//    }
//    
//    return nickname;
//}
//
//
//
////unicode_utf_8
//int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,
//                            int outSize)
//{
//    if ( unic <= 0x0000007F )
//    {
//        // * U-00000000 - U-0000007F:  0xxxxxxx
//        *pOutput     = (unic & 0x7F);
//        return 1;
//    }
//    else if ( unic >= 0x00000080 && unic <= 0x000007FF )
//    {
//        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
//        *(pOutput+1) = (unic & 0x3F) | 0x80;
//        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
//        return 2;
//    }
//    else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
//    {
//        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
//        *(pOutput+2) = (unic & 0x3F) | 0x80;
//        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
//        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
//        return 3;
//    }
//    else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
//    {
//        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//        *(pOutput+3) = (unic & 0x3F) | 0x80;
//        *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;
//        *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;
//        *pOutput     = ((unic >> 18) & 0x07) | 0xF0;
//        return 4;
//    }
//    else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
//    {
//        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//        *(pOutput+4) = (unic & 0x3F) | 0x80;
//        *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;
//        *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;
//        *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;
//        *pOutput     = ((unic >> 24) & 0x03) | 0xF8;
//        return 5;
//    }
//    else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )
//    {
//        // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//        *(pOutput+5) = (unic & 0x3F) | 0x80;
//        *(pOutput+4) = ((unic >>  6) & 0x3F) | 0x80;
//        *(pOutput+3) = ((unic >> 12) & 0x3F) | 0x80;
//        *(pOutput+2) = ((unic >> 18) & 0x3F) | 0x80;
//        *(pOutput+1) = ((unic >> 24) & 0x3F) | 0x80;
//        *pOutput     = ((unic >> 30) & 0x01) | 0xFC;
//        return 6;
//    }
//    
//    return 0;
//}
//
//TCHAR* utf8_to_unicode::char_to_tchar( char* _data,TCHAR* _target , int wdatasize){
//    
//    _TCHAR_ myretgame[wdatasize];
//    
//    //旧密码
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    
//    wchar_t asd1[wdatasize];
//    mbstowcs(asd1, _data, wdatasize);
//    //改变wchar_t的字节数
//    int wc1;
//    for (int i = 0 ; i < wdatasize; i++) {
//        wc1 = *(&asd1[i]);
//        if (wc1 > 0xFFFF)
//        {
//            wc1 -= 0x00010000L;
//            myretgame[i] = 0xD800 | (wc1 >> 10);
//            myretgame[i] = 0xDC00 | (wc1 & 0x03FF);
//        }
//        else
//        {
//            myretgame[i] = wc1;
//        }
//    }
//    
//#endif
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    //改变wchar_t的字节数
//    for (int i = 0 ; i < wdatasize; i++) {
//        myretgame[i] =_data[i];
//    }
//#endif
//    
//    return myretgame;
//}
//
//
////分离中英文字符串
//TCHAR* utf8_to_unicode::stringwithch_en(const char* _nickname , int &wdatasize){
//    
//    wchar_t unicode[256] ;
//    memset(unicode, 0, 256*2);
//    
//    int m = 0;
//    for (int k = 0; k< strlen(_nickname); k++) {
//        if (_nickname[k] > 255 || _nickname[k] < 0) {
//            printf(" 我的数据%d\n" , k);
//            unicode[k] = (_nickname[0+k] & 0x1F) << 12;
//            unicode[k] |= (_nickname[1+k] & 0x3F) << 6;
//            unicode[k] |= (_nickname[2+k] & 0x3F);
//            k = k+2;
//            m++;
//        }else{
//            unicode[k] = _nickname[k];
//        }
//    }
//    
//    int kk = del_zero(unicode, strlen(_nickname));
//    TCHAR result[256] ;
//    memset(result, 0, kk*2);
//    
//    for (int m = 0; m < kk; m++) {
//        result[m] = unicode[m];
//    }
//    
//    wdatasize = kk;
//    return result;
//    
//}
//
//
//int utf8_to_unicode::del_zero(wchar_t *p,int n)
//{
//    //wchar_t p[11] = {'1','2',0,0,0,'3',0,0,0,'2','1'};
//    
//    
//    int i,j,len=n;
//    for(i=0;i<len;i++){
//        if(p[i]==0){
//            for(j=i;j<len;j++){
//                p[j]=p[j+1];
//                
//            }
//            len--;
//            i = i-1;
//            
//        }
//    }
//    return len;
//}
//
//
//
//
//TCHAR* utf8_to_unicode::String2TCHAR(const char* str , int &datalength){
//    
//    wchar_t unicode[datalength];
//    memset(unicode, 0, datalength*4);
//    
//    int m = 0;
//    for (int i = 0; i < datalength; i++) {
//        
//        if (str[i] > 255 || str[i] < 0) {
//            unicode[i] = (str[0+i] & 0xFF)  << 8;
//            unicode[i] = str[0+i] & 0xFF ;
//            i = i+1;
//            m++;
//        }else{
//            unicode[i] = str[i];
//        }
//    }
//    
//    int kk = del_zero(unicode, strlen(str));
//    TCHAR result[kk] ;
//    memset(result, 0, kk*2);
//    
//    for (int m = 0; m < kk; m++) {
//        result[m] = unicode[m];
//        
//    }
//    datalength = kk;
//    return result;
//    
//}