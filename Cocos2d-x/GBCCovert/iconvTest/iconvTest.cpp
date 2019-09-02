// iconvTest.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include "../../2.0-x-2.03_branch_231_NoScript/cocos2dx/platform/third_party/win32/iconv/iconv.h"

#pragma comment(lib,"libiconv.lib")
 
char* utf16ToUtf8(const wchar_t* ws, size_t wcharCount) {
    static char buf[10001];
 
    size_t dstlen = 10000;
    iconv_t conv = iconv_open("UTF8", "UTF16");
    if(conv==(iconv_t)-1) {
        throw "utf16ToUtf8 conv -1";
    }
    size_t srcLen = wcharCount*2;
    iconv(conv, (const char**)&ws, &srcLen, (char**)&buf, &dstlen);
    iconv_close(conv);
    return buf;
}
 
void testUtf16ToUtf8() {
    char data[]={0x00, 0x63, 0x00, 0x6f}; // "co" 的UTF16 字符串
    //char data[]={0x63, 0x00, 0x6f, 0x00};
    char* s = utf16ToUtf8((wchar_t*)data, 2);
    printf("s:%s \n", s);
}
 

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		testUtf16ToUtf8();
		//return 0;
	}
	catch(...)
	{
		printf("ERROR \n");
	}

	system("pause");
	return 0;
}

