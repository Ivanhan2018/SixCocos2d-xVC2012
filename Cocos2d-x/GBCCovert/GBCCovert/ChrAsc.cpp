#include "stdafx.h"
#include "ChrAsc.h"

#include<string.h>

//由内码（与汉字的GBK内码一致）求得一字符，多对一函数
const char * ChrFromAnsi(short CharCode)
{
	static 	char str[80]={0};
	memset(&str[0],0,2);
	if((CharCode>32 && CharCode<128)||((char)(CharCode)>32 && (char)(CharCode)<128))
	{
		memset(&str[0],(char)(CharCode),1);
		memset(&str[1],0,1);
		return str;
	}
	if((char)(CharCode>>8)>32 && (char)(CharCode>>8)<128)
	{
		memset(&str[0],(char)(CharCode>>8),1);
		memset(&str[1],0,1);
		return str;
	}
	memset(&str[0],(char)(CharCode>>8),1);
	memset(&str[1],(char)(CharCode),1);
	return str;
}

//求字符的内码
short AscFromChr(const char *str)
{
	int n=strlen(str);
	if(n==0||n>2)
		return 0;
	if(n==1)
		return str[0];
	if(n==2)
		//return ((unsigned char)str[0])*256+((unsigned char)str[1]);
		return (((short)(unsigned char)str[0])<<8)|((short)(unsigned char)str[1]);
	return 0;
}

//将wstring类型的字符串，转换成string
string WstringToString(wstring source)
{
	LPCWSTR tempSource=source.c_str();

	DWORD   size   =   WideCharToMultiByte(CP_THREAD_ACP,   
		0,   
		tempSource,   
		-1,   
		NULL,   
		0,   
		NULL,   NULL);   

	char*   dest   =   new   char[size];   

	WideCharToMultiByte(CP_THREAD_ACP,   
		0,   
		tempSource,   
		-1,   
		dest,   
		size,   
		NULL,   NULL);   

	string strResult=dest;

	delete[] dest;

	return strResult;


}


//转换string到wstring
wstring StringToWstring(string source)
{
	LPCSTR tempSource=source.c_str();
	int nLen=source.size();

	if(nLen<=0)
		return L"";

	DWORD   size   =  MultiByteToWideChar(CP_ACP, 0,tempSource, nLen, 0, 0);
	WCHAR *   dest   =   new   WCHAR [size+1];  

	MultiByteToWideChar(CP_ACP, 0,tempSource, nLen, dest, size);

	dest[size] = 0;

	if( dest[0] == 0xFEFF) // skip Oxfeff
	{
		for(int i = 0; i < size; i ++) 
			dest[i] = dest[i+1]; 
	}

	wstring strResult=dest;
	delete[] dest;
	return strResult;
}