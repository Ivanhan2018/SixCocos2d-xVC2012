/*
 
 ˽��
 �����������˽�з���
 
 */
#pragma once
#include "Define.h"
#include <string>
using namespace std;
//#pragma mark -
//#pragma mark NSString(NSStringMD5)

class MyNSString
{
public:
	static string CreateMD5WithString(string str);
	static string CreateStringWithTCHAR(TCHART *tchar, int size);
	static int GBKToUTF8(string &gbkStr);
	static void CreateTCHARWithString(const char *src, int size, TCHART *dest);
	static int wc2mbs(TCHART *wc,unsigned int wc_size, char *mbs);
	//static int wc2mbs1(TCHART *wc,unsigned int wc_size, char *mbs);
	static int mbs2wc(const char *mbs,unsigned int mbs_size,TCHART *wc);


	static void UnicodeTouchUtf8(const char* pOut, wchar_t *pText); //将utf-8转Unicode

private:

};