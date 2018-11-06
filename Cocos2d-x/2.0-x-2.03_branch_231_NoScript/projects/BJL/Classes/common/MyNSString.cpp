#include "MyNSString.h"
#include "Define.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import <Foundation/Foundation.h>
#include "private.h"
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>  
#else  
#include<unistd.h>   
#include<sys/types.h>  
#include<strings.h>  
#include <netinet/in.h>
#endif  

#include <limits.h>  
#include <locale.h>  


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <iconv.h>
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../../../iconv/include/iconv.h"
#else
#include "iconv.h"
#endif

#include <stdio.h>  
#include <string.h>  
#include <malloc.h>  
#include <memory.h>  

#ifdef WIN32  
//#if 0
#define uint8_t  unsigned __int8  
#define uint16_t unsigned __int16  
#define uint32_t unsigned __int32  
#define uint64_t unsigned __int64  

#define int8_t  __int8  
#define int16_t __int16  
#define int32_t __int32  
#else
#define uint8_t  unsigned char  
#define uint16_t unsigned short  
#define uint32_t unsigned __int32  
#define uint64_t unsigned __int64  

#define int8_t  char  
#define int16_t short  
#define int32_t __int32  
#define CP_UTF8                   65001       // UTF-8 translation

#endif 
#define OUTLEN 255
//����ת��:��һ�ֱ���תΪ��һ�ֱ���
#ifdef WIN32  
int code_convert(char *from_charset,char *to_charset,const char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	iconv_t cd;
	int rc;
	const char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;
	memset(outbuf,0,outlen);
	if (iconv(cd,pin,&inlen,pout,&outlen)==-1)
		return -1;
	iconv_close(cd);
	return 0;
}
#else
int code_convert(char *from_charset,char *to_charset,const char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	iconv_t cd;
	int rc;
	char *in = new char[2048];
	memcpy(in, inbuf, inlen);
	char **pin = &in;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;
	memset(outbuf,0,outlen);
	if (iconv(cd,pin,&inlen,pout,&outlen)==-1)
		return -1;
	iconv_close(cd);
	return 0;
}
#endif 

//UNICODE��תΪGB2312��
int u2g(const char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
}

//GB2312��תΪUNICODE��
int g2u(const char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
}

int unicode_to_utf8(uint16_t *in, int insize, uint8_t **out)  
{  
	int i = 0;  
	int outsize = 0;  
	int charscount = 0;  
	uint8_t *result = NULL;  
	uint8_t *tmp = NULL;  

	charscount = insize / sizeof(uint16_t);  
	result = (uint8_t *)malloc(charscount * 3 + 1);  
	memset(result, 0, charscount * 3 + 1);  
	tmp = result;  

	for (i = 0; i < charscount; i++)  
	{  
		uint16_t unicode = in[i];  

		if (unicode >= 0x0000 && unicode <= 0x007f)  
		{  
			*tmp = (uint8_t)unicode;  
			tmp += 1;  
			outsize += 1;  
		}  
		else if (unicode >= 0x0080 && unicode <= 0x07ff)  
		{  
			*tmp = 0xc0 | (unicode >> 6);  
			tmp += 1;  
			*tmp = 0x80 | (unicode & (0xff >> 2));  
			tmp += 1;  
			outsize += 2;  
		}  
		else if (unicode >= 0x0800 && unicode <= 0xffff)  
		{  
			*tmp = 0xe0 | (unicode >> 12);  
			tmp += 1;  
			*tmp = 0x80 | (unicode >> 6 & 0x00ff);  
			tmp += 1;  
			*tmp = 0x80 | (unicode & (0xff >> 2));  
			tmp += 1;  
			outsize += 3;  
		}  

	}  

	*tmp = '\0';  
	*out = result;  
	return 0;  
}  

int utf8_to_unicode(uint8_t *in, uint16_t **out, int *outsize)  
{  
	uint8_t *p = in;  
	uint16_t *result = NULL;  
	int resultsize = 0;  
	uint8_t *tmp = NULL;  

	result = (uint16_t *)malloc(strlen((int8_t *)in) * 2 + 2); /* should be enough */  
	memset(result, 0, strlen((int8_t *)in) * 2 + 2);  
	tmp = (uint8_t *)result;  

	while(*p)  
	{  
		if (*p >= 0x00 && *p <= 0x7f)  
		{  
			*tmp = *p;  
			tmp++;  
			*tmp = '\0';  
			resultsize += 2;  
		}  
		else if ((*p & (0xff << 5))== 0xc0)  
		{  
			uint16_t t = 0;  
			uint8_t t1 = 0;  
			uint8_t t2 = 0;  

			t1 = *p & (0xff >> 3);  
			p++;  
			t2 = *p & (0xff >> 2);  

			*tmp = t2 | ((t1 & (0xff >> 6)) << 6);//t1 >> 2;  
			tmp++;  

			*tmp = t1 >> 2;//t2 | ((t1 & (0xff >> 6)) << 6);  
			tmp++;  

			resultsize += 2;  
		}  
		else if ((*p & (0xff << 4))== 0xe0)  
		{  
			uint16_t t = 0;  
			uint8_t t1 = 0;  
			uint8_t t2 = 0;  
			uint8_t t3 = 0;  

			t1 = *p & (0xff >> 3);  
			p++;  
			t2 = *p & (0xff >> 2);  
			p++;  
			t3 = *p & (0xff >> 2);  

			//Little Endian  
			*tmp = ((t2 & (0xff >> 6)) << 6) | t3;//(t1 << 4) | (t2 >> 2);  
			tmp++;  

			*tmp = (t1 << 4) | (t2 >> 2);//((t2 & (0xff >> 6)) << 6) | t3;  
			tmp++;  
			resultsize += 2;  
		}  

		p++;  
	}  

	*tmp = '\0';  
	tmp++;  
	*tmp = '\0';  
	resultsize += 2;  

	*out = result;  
	*outsize = resultsize;   
	return 0;  
}  
//char* QXUtf82Unicode(const char* utf, size_t unicode_number)  
//{   
//}

string MyNSString::CreateMD5WithString(string str)
{
	return "";
}

string MyNSString::CreateStringWithTCHAR(TCHART *tchar, int size)
{
	return "";
}

void MyNSString::CreateTCHARWithString(const char *src, int size, TCHART *dest)
{
	for(int i = 0 ; i < size ; i++)
	{
		dest[i] = src[i];
	}
}

int MyNSString::GBKToUTF8(string &gbkStr)
{

	iconv_t iconvH;
	iconvH = iconv_open("utf-8", "gb2312");
	if (iconvH == 0)
	{
		return -1;
	}
	size_t strLength = gbkStr.length();


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	const char* strChar = (gbkStr.c_str());
	const char** pin = &strChar;
#else if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	char* strChar = const_cast<char*>(gbkStr.c_str());
	char** pin = &strChar;
#endif

	//const char* strChar = (gbkStr.c_str());
	//const char** pin = &strChar;

	char *outbuf = (char *)malloc(strLength*4);
	char *pBuff = outbuf;
	memset(outbuf, 0, strLength*4);

	size_t outLength = strLength*4;

	if(-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
	{
		iconv_close(iconvH);
		return -1;
	}
	gbkStr = pBuff;
	iconv_close(iconvH);
	return 0;
}

int MyNSString::wc2mbs(TCHART *wc,unsigned int wc_size,char *mbs)  
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		NSString *result = [NSString CreateStringWithTHCAR:wc size:wc_size];
		memcpy(mbs, [result UTF8String], [result length]*3);
		string str = mbs;
		CCLog("%s", mbs);
		CCLog("%d", [result length]);
		CCLog("%d", strlen(mbs));
		//        MyNSString::GBKToUTF8(str);
		//        memcpy(mbs, str.c_str(), str.length());
		return [result length];
	}
#endif
	int mbs_size;
#if (defined WIN32) ||  (defined _WIN32)  
	setlocale(LC_ALL,"chs");  
#else  
	setlocale(LC_ALL,"zh_CN.gbk");  
#endif  
#if (defined WIN32) ||  (defined _WIN32)   
	//#if 0
	if(wc_size==0)  
		wc_size=UINT_MAX;  

	mbs_size=wcstombs(0,wc,wc_size);  

	if(mbs!=0)  
		mbs_size=wcstombs(mbs,wc,wc_size); 
#else  
	uint8_t *myMbs = (uint8_t *)malloc(255);
	memset(myMbs, 0, 255);
	unicode_to_utf8(wc, wc_size, &myMbs);
	memcpy(mbs, myMbs, wc_size);
	free(myMbs);

	//wc_size = mbs_size;
	//int charSize = sizeof(TCHART);
	//for(int i = 0 ; i < wc_size ; i++)
	//{
	//	mbs[2*i+1] = (char)(wc[i]<<8);
	//	mbs[2*i] = (char)(wc[i]&0xff);
	//}
#endif  
	string str = mbs;
	if(str != ""){
		MyNSString::GBKToUTF8(str);
		memcpy(mbs, str.c_str(), str.length());
	}
	return mbs_size;  
}
void MyNSString::UnicodeTouchUtf8(const char* pOut, wchar_t *pText)
{
	//char* pchar = (char *)pText;
	//pOut[0] =(0xE0|((pchar[1] & 0xF0) >>4));
	//pOut[1] =(0x80|((pchar[1] & 0x0F) <<4))+((pchar[0] & 0xC0) >>6);
	//pOut[2] =(0x80|(pOut[0]&0x3F));
	return;
	
}
int MyNSString::mbs2wc(const char *mbs,unsigned int mbs_size,TCHART *wc)  
{
	char mbsOut[1024] = {0};
	u2g(mbs,strlen(mbs),mbsOut,mbs_size);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		NSString *mbsString = [NSString stringWithUTF8String:mbs];
		[NSString CreateTCHARWithString:mbsString size:[mbsString length] TCHART:wc];
		return mbs_size;
	}
#endif

	int wc_size;  
#if (defined WIN32) ||  (defined _WIN32)  
	setlocale(LC_ALL,"chs");  
#else  
	setlocale(LC_ALL,"zh_CN.gbk");  
#endif  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//#if 0
	if(mbs_size==0)  
		mbs_size=UINT_MAX;  

	wc_size=mbstowcs(0,mbsOut,mbs_size);  
	if(wc!=0)  
		wc_size=mbstowcs(wc,mbsOut,mbs_size);  
#else
//uint8_t *myMbs = (uint8_t *)malloc(1024);
	//memset(myMbs, 0, 1024);
	//memcpy(myMbs, mbsOut, mbs_size);
	//uint16_t *myWc = (uint16_t *)malloc(1024);
	//memset(myWc, 0, 1024);
	//utf8_to_unicode(myMbs, &myWc, &wc_size);
	////for(int i = 0 ; i < wc_size ; i++)
	////{
	////	wc[i] = myWc[i];
	////}
	//memcpy(wc, myWc, wc_size);
	//free(myMbs);
	//free(myWc);

	wc_size = mbs_size;
	for(int i = 0 ; i < wc_size ; i++)
	{
		wc[i] = mbsOut[i];
	}

#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
{
	uint8_t *myMbs = (uint8_t *)malloc(1024);
	memset(myMbs, 0, 1024);
	memcpy(myMbs, mbsOut, mbs_size);
	uint16_t *myWc = (uint16_t *)malloc(1024);
	memset(myWc, 0, 1024);
	utf8_to_unicode(myMbs, &myWc, &wc_size);
	//QXUtf82Unicode(mbs,mbs_size);
	memcpy(wc, myWc, wc_size);
	free(myMbs);
	wc_size = mbs_size;
	for(int i = 0 ; i < wc_size ; i++)
	{
		wc[i] = mbs[i];
	}
	CCLOG("	AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

}
#endif
	return wc_size;  
}  


//int MyNSString::wc2mbs(TCHART *wc,unsigned int wc_size,char *mbs)  
//{  
//	int mbs_size;  
//#if (defined WIN32) ||  (defined _WIN32)  
//	setlocale(LC_ALL,"chs");  
//#else  
//	setlocale(LC_ALL,"zh_CN.gbk");  
//#endif  
//	if(wc_size==0)  
//		wc_size=UINT_MAX;  
//
//	mbs_size=wcstombs(0,wc,wc_size);  
//
//	if(mbs!=0)  
//		mbs_size=wcstombs(mbs,wc,wc_size);  
//
//	return mbs_size;  
//}  
//
//int MyNSString::mbs2wc(const char *mbs,unsigned int mbs_size,TCHART *wc)  
//{  
//	mbs_size*=2;
//	int wc_size;  
//#if (defined WIN32) ||  (defined _WIN32)  
//	setlocale(LC_ALL,"chs");  
//#else  
//	setlocale(LC_ALL,"zh_CN.gbk");  
//#endif  
//	if(mbs_size==0)  
//		mbs_size=UINT_MAX;  
//
//	wc_size=mbstowcs(0,mbs,mbs_size);  
//	if(wc!=0)  
//		wc_size=mbstowcs(wc,mbs,mbs_size);  
//	return wc_size;  
//}  


